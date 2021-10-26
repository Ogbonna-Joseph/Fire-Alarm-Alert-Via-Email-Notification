#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFiClient.h>


const char* ssid = "JOSEPH";
const char* password = "00000000";
String serverName = "https://maker.ifttt.com/trigger/door_status/with/key/pEbV6M8QVTmc9S43r2jfrWmy488E8hi61OqZr4lun4B";

int buzzer = 8;
int LED = 7;
int flame_sensor = 4;
int flame_detected;


WebServer server(80);

void sendemail(){
  
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
  }



void control(){
 flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    sendemail();
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
    sendemail();
  }
    
  
  }

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
  // Serial port for debugging purposes
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  control();
   server.handleClient();
  }
