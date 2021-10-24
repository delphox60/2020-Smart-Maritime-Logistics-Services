const char *ssid = "your_ssid";
const char *password = "your_pass"; 

void setup() {
    Serial.begin(115200);

    // delete old config
    WiFi.disconnect(true);
    delay(1000);
    WiFi.onEvent(WiFiEvent);
    WiFi.begin(ssid, password);
    Serial.println("Wait for WiFi... ");
}
 
WiFi.onEvent(WiFiEvent);
 
 
 typedef enum {
    WIFI_EVENT_STAMODE_CONNECTED = 0,
    WIFI_EVENT_STAMODE_DISCONNECTED,
    WIFI_EVENT_STAMODE_AUTHMODE_CHANGE,
    WIFI_EVENT_STAMODE_GOT_IP,
    WIFI_EVENT_STAMODE_DHCP_TIMEOUT,
    WIFI_EVENT_SOFTAPMODE_STACONNECTED,
    WIFI_EVENT_SOFTAPMODE_STADISCONNECTED,
    WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED,
    WIFI_EVENT_MAX
} WiFiEvent_t;
 
 
WiFi.begin(ssid, password);
 

 

WIFI CLIENT (HTTP REQUEST)
 

 
 
const char *ssid = "your_ssid";
const char *password = "your_pass";
 
const char* host = "hardcopyworld.com";
 

 
void setup() {
  ......
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  ......
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
 
Serial.println(WiFi.localIP());
 

 
void loop() {
  delay(5000);
  ......
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // We now create a URI for the request
  String url = "/";
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
 

 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 

 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
 
 
 

 
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 
 

 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 

 

  

 
 
 

 
const char *ssid = "your_ssid";
const char *password = "your_pass";
ESP8266WebServer server ( 80 );
const int led = 13;
 
 

 
void setup ( void ) {
  ......
  WiFi.begin ( ssid, password );
  ......
  server.on ( "/", handleRoot );
  server.on ( "/test.svg", drawGraph );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  ......
  server.begin();
  ......
} 

server.begin();
 

 
void loop ( void ) {
  server.handleClient();
}
 
 
ESP8266WebServer server = ESP8266WebServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void setup() {
    ......
    WiFiMulti.addAP("your_ssid", "your_pass");
    ......
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    ......
    // handle index
    server.on("/", []() {
        // send index.html
        server.send(200, "text/html", html_string);
    });
    server.begin();
    ......
} 

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
    switch(type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED: {
            ......
            webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
            if(payload[0] == '#') {
                // decode rgb data
                uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);
                analogWrite(LED_RED,    ((rgb >> 16) & 0xFF));
                analogWrite(LED_GREEN,  ((rgb >> 8) & 0xFF));
                analogWrite(LED_BLUE,   ((rgb >> 0) & 0xFF));
            }
            break;
    }
}
