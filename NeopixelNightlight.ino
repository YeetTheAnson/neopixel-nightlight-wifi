#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

AsyncWebServer server(80);

unsigned long startTime;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  startTime = millis();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String uptime = String((millis() - startTime) / 1000);
    String html = "<html><body><h1>ESP32 Uptime</h1><p>Uptime: " + uptime + " seconds</p></body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  delay(500);
}
