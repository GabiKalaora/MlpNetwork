package componentsaudittest

import (
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"net/http"
	"os"
	"strings"
	"time"
)

type AuditViewer struct {
	token               string
	auditlogClintID     string
	auditlogClintSecret string
	auditlogAuthURL     string
	auditlogURL         string
}

func NewAuditViewer() *AuditViewer {
	return &AuditViewer{
		auditlogClintID:     os.Getenv("AUDITLOG_CLIENTID"),
		auditlogClintSecret: os.Getenv("AUDITLOG_CLIENT_SECRET"),
		auditlogAuthURL:     os.Getenv("AUDITLOG_AUTH_URL"),
		auditlogURL:         os.Getenv("AUDITLOG_URL"),
	}
}

func (t *AuditViewer) GetLog(cluster_id string, component_type string, timeRange int) (string, error) {
	httpClient := http.Client{Timeout: 3 * time.Minute}

	token, err := authorize(*t, httpClient)
	if err != nil {
		return "", err
	}
	t.token = token

	t1, t2 := getTimeInterval(timeRange)
	auditlogQueryURL := fmt.Sprint(t.auditlogURL, t1, t2)
	fullMsg := ""

	for i := 1; i <= 20; i++ {
		time.Sleep(3 * time.Second)
		fmt.Printf("try #%d for getting logs\n", i)
		logs, err := getAuditLogMessages(*t, auditlogQueryURL, httpClient)
		if err != nil {
			return "", err
		}
		fullMsg, err = filterLogs(component_type, cluster_id, logs)
		if err != nil {
			log.Printf("encounterd an error when trying to filter the logs: %v", err)
		}
		if len(fullMsg) > 0 {
			return fullMsg, nil
		}
	}
	return "", nil
}

type AuditLog struct {
	MessageUUID    string    `json:"message_uuid"`
	Time           time.Time `json:"time"`
	Tenant         string    `json:"tenant"`
	OrgID          string    `json:"org_id"`
	SpaceID        string    `json:"space_id"`
	AppOrServiceID string    `json:"app_or_service_id"`
	AlsServiceID   string    `json:"als_service_id"`
	User           string    `json:"user"`
	Category       string    `json:"category"`
	FormatVersion  string    `json:"format_version"`
	Message        string    `json:"message"`
}

type AuditMessage struct {
	Uuid          string        `json:"uuid"`
	User          string        `json:"user"`
	Time          string        `json:"time"`
	Data          string        `json:"data"`
	Attributes    []interface{} `json:"attributes"`
	Id            string        `json:"id"`
	Category      string        `json:"category"`
	Tenant        string        `json:"tenant"`
	CustomDetails interface{}   `json:"custom_details"`
}

type Auth struct {
	AccessToken string `json:"access_token"`
	TokenType   string `json:"token_type"`
	ExpiresIn   int    `json:"expires_in"`
	Scope       string `json:"scope"`
	Jti         string `json:"jti"`
}

func getTimeInterval(timeRange int) (string, string) {
	format := time.RFC3339
	time1 := time.Now().UTC().Add(-time.Minute * time.Duration(timeRange)).Format(format)
	time2 := time.Now().UTC().Format(format)

	return time1, time2
}

func authorize(auditViewer AuditViewer, httpClient http.Client) (string, error) {
	request, err := http.NewRequest("POST", auditViewer.auditlogAuthURL, nil)
	if err != nil {
		return "", err
	}

	request.SetBasicAuth(auditViewer.auditlogClintID, auditViewer.auditlogClintSecret)
	resp, err := httpClient.Do(request)
	if err != nil || resp.StatusCode != http.StatusOK {
		return "", err
	}
	defer resp.Body.Close()

	// write auth resp in Auth obj and return AccessToken
	var auth Auth
	json.NewDecoder(resp.Body).Decode(&auth)
	return auth.AccessToken, nil
}

func getAuditLogMessages(auditViewer AuditViewer, url string, httpClient http.Client) ([]AuditLog, error) {
	request, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return nil, err
	}
	request.Header.Add("Authorization", "Bearer "+auditViewer.token)
	resp, err := httpClient.Do(request)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	var auditLogs []AuditLog
	if resp.StatusCode != http.StatusOK {
		return auditLogs, errors.New("Wrong status code") // AuditLog should be nil in this stage
	}
	// place all logs in auditlogs
	err = json.NewDecoder(resp.Body).Decode(&auditLogs)
	if err != nil {
		return auditLogs, err
	}
	return auditLogs, nil
}

func filterLogs(component string, clusterID string, logs []AuditLog) (string, error) {
	for _, logRecord := range logs {
		var logMessage AuditMessage
		err := json.Unmarshal([]byte(logRecord.Message), &logMessage)
		if err != nil {
			return "", err
		}
		foundComponent := strings.Contains(logMessage.Uuid, component)
		foundClusterID := strings.Contains(logMessage.Data, clusterID)

		if foundClusterID && foundComponent {
			return logMessage.Data, nil
		}
	}
	return "", errors.New("didn't find any relevant logs")
}
