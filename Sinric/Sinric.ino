// Credits ########################################################################################
// https://www.youtube.com/watch?v=b5yr-H6jJAc
// Tech StudyCell



#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <ArduinoJson.h> // https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <StreamString.h>

#include <AceButton.h> // https://github.com/bxparks/AceButton
using namespace ace_button;
WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "sua-api-key/your-api-key" // API KEY
#define MySSID "Wifissid" // NOME REDE
#define MyWifiPassword "password" // SENHA WIFI
#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

// TODOS BOTAO NA SEQUENCIA IRAM DESARMAR E ATIVAR NA MESMA SEQUENCIA OS BOTOES VIRTUAIS 
// ALL BUTTON IN THE SEQUENCE WILL DISARM AND ACTIVATE THE VIRTUAL BUTTONS IN THE SAME SEQUENCE
//Relays - Botao virtal Home/Alexa 
const int RELAY1_PIN = 23;
const int RELAY2_PIN = 22;
const int RELAY3_PIN = 21;
const int RELAY4_PIN = 19;
const int RELAY5_PIN = 18;
const int RELAY6_PIN = 5;
const int RELAY7_PIN = 25;
const int RELAY8_PIN = 26;

// TODOS BOTAO NA SEQUENCIA IRAM DESARMAR E ATIVAR NA MESMA SEQUENCIA OS BOTOES VIRTUAIS 
// ALL BUTTON IN THE SEQUENCE WILL DISARM AND ACTIVATE THE VIRTUAL BUTTONS IN THE SAME SEQUENCE
// Switch Botao Fisico
const int BUTTON1_PIN = 13;
const int BUTTON2_PIN = 12;
const int BUTTON3_PIN = 14;
const int BUTTON4_PIN = 27;
const int BUTTON5_PIN = 33;
const int BUTTON6_PIN = 32;
const int BUTTON7_PIN = 15;
const int BUTTON8_PIN = 4;

//ID Sinric - ID'S CONTA SINRIC
String device_ID_1 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_2 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_3 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_4 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_5 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_6 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_7 = "XXXXXXXXXXXXXXXXXXXXXXXX";
String device_ID_8 = "XXXXXXXXXXXXXXXXXXXXXXXX";




ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);
ButtonConfig config5;
AceButton button5(&config5);
ButtonConfig config6;
AceButton button6(&config6);
ButtonConfig config7;
AceButton button7(&config7);
ButtonConfig config8;
AceButton button8(&config8);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);
void handleEvent5(AceButton*, uint8_t, uint8_t);
void handleEvent6(AceButton*, uint8_t, uint8_t);
void handleEvent7(AceButton*, uint8_t, uint8_t);
void handleEvent8(AceButton*, uint8_t, uint8_t);

void setPowerStateOnServer(String deviceId, String value);

void turnOn(String deviceId) {
  if (deviceId == device_ID_1) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY1_PIN, LOW);
  }
  if (deviceId == device_ID_2) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY2_PIN, LOW);
  }
  if (deviceId == device_ID_3) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY3_PIN, LOW);
  }
  if (deviceId == device_ID_4) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY4_PIN, LOW);
  }
    if (deviceId == device_ID_5) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY5_PIN, LOW);
  }
  if (deviceId == device_ID_6) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY6_PIN, LOW);
  }
  if (deviceId == device_ID_7) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY7_PIN, LOW);
  }
  if (deviceId == device_ID_8) 
  {
    Serial.print("ON ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY8_PIN, LOW);
  }

}

void turnOff(String deviceId) {
  if (deviceId == device_ID_1)
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY1_PIN, HIGH);
  }
  if (deviceId == device_ID_2)
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY2_PIN, HIGH);
  }
  if (deviceId == device_ID_3) 
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY3_PIN, HIGH);
  }
  if (deviceId == device_ID_4) 
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY4_PIN, HIGH);
  }
  if (deviceId == device_ID_5)
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY5_PIN, HIGH);
  }
  if (deviceId == device_ID_6)
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY6_PIN, HIGH);
  }
  if (deviceId == device_ID_7) 
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY7_PIN, HIGH);
  }
  if (deviceId == device_ID_8) 
  {
    Serial.print("OFF ID: ");
    Serial.println(deviceId);
    Serial.print("\n");
    digitalWrite(RELAY8_PIN, HIGH);
  }

}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      isConnected = false;
      WiFiMulti.addAP(MySSID, MyWifiPassword);
      Serial.printf("Servidor desconectado\n");
      WiFi.reconnect();
      break;
    case WStype_CONNECTED: {
        isConnected = true;
        Serial.printf("Servidor conectado\n", payload);
        Serial.printf("Esperando ação servidor\n");
        Serial.print("\n");
      }
      break;
    case WStype_TEXT: {
        Serial.printf("Enviado pelo servidor\n%s", payload);
#if ARDUINOJSON_VERSION_MAJOR == 5
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6
        DynamicJsonDocument json(1024);
        deserializeJson(json, (char*) payload);
#endif
        String deviceId = json ["deviceId"];
        String action = json ["action"];

        if(action == "action.devices.commands.OnOff") { 
            String value = json ["value"]["on"];
            Serial.println(value); 
            
          if (value == "true") {
            turnOn(deviceId);
          } else {
            turnOff(deviceId);
          }
        }
        else if (action == "test") {
          Serial.println("Recebendo\n");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("Obter comprimento binário: %u\n", length);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  WiFiMulti.addAP(MySSID, MyWifiPassword);

  if (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("\n");
    Serial.print("Conectando ao Wifi : ");
    Serial.println(MySSID);
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.print("WiFi Conectado.\n");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());
  }
  pinMode(BUTTON1_PIN, INPUT_PULLUP); 
  pinMode(BUTTON2_PIN, INPUT_PULLUP); 
  pinMode(BUTTON3_PIN, INPUT_PULLUP); 
  pinMode(BUTTON4_PIN, INPUT_PULLUP); 
  pinMode(BUTTON5_PIN, INPUT_PULLUP); 
  pinMode(BUTTON6_PIN, INPUT_PULLUP); 
  pinMode(BUTTON7_PIN, INPUT_PULLUP); 
  pinMode(BUTTON8_PIN, INPUT_PULLUP); 
  
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);
  pinMode(RELAY5_PIN, OUTPUT);
  pinMode(RELAY6_PIN, OUTPUT);
  pinMode(RELAY7_PIN, OUTPUT);
  pinMode(RELAY8_PIN, OUTPUT);
  
  digitalWrite(RELAY1_PIN, HIGH);  
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
  digitalWrite(RELAY4_PIN, HIGH);
  digitalWrite(RELAY5_PIN, HIGH);
  digitalWrite(RELAY6_PIN, HIGH);
  digitalWrite(RELAY7_PIN, HIGH);  
  digitalWrite(RELAY8_PIN, HIGH);  
  
  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);
  config5.setEventHandler(button5Handler);
  config6.setEventHandler(button6Handler);
  config7.setEventHandler(button7Handler);
  config8.setEventHandler(button8Handler);
  
  button1.init(BUTTON1_PIN);
  button2.init(BUTTON2_PIN);
  button3.init(BUTTON3_PIN);
  button4.init(BUTTON4_PIN);
  button5.init(BUTTON5_PIN);
  button6.init(BUTTON6_PIN);
  button7.init(BUTTON7_PIN);
  button8.init(BUTTON8_PIN);
  
  webSocket.begin("iot.sinric.com", 80, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  webSocket.setReconnectInterval(5000);
}

void loop() {

  button1.check();
  button2.check();
  button3.check();
  button4.check();
  button5.check();
  button6.check();
  button7.check();
  button8.check();
  webSocket.loop();
  
    if(isConnected) {
      uint64_t now = millis();
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  } 
}

void setPowerStateOnServer(String deviceId, String value) {
#if ARDUINOJSON_VERSION_MAJOR == 5
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6
  DynamicJsonDocument root(1024);
#endif

  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
#if ARDUINOJSON_VERSION_MAJOR == 5
  root.printTo(databuf);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6
  serializeJson(root, databuf);
#endif
  webSocket.sendTXT(databuf);
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_1, "ON");
      digitalWrite(RELAY1_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_1, "OFF");
      digitalWrite(RELAY1_PIN, HIGH);
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_2, "ON");
      digitalWrite(RELAY2_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_2, "OFF");
      digitalWrite(RELAY2_PIN, HIGH);
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_3, "ON");
      digitalWrite(RELAY3_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_3, "OFF");
      digitalWrite(RELAY3_PIN, HIGH);
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_4, "ON");
      digitalWrite(RELAY4_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_4, "OFF");
      digitalWrite(RELAY4_PIN, HIGH);
      break;
  }
}

void button5Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT5");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_5, "ON");
      digitalWrite(RELAY5_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_5, "OFF");
      digitalWrite(RELAY5_PIN, HIGH);
      break;
  }
}

void button6Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT6");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_6, "ON");
      digitalWrite(RELAY6_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_6, "OFF");
      digitalWrite(RELAY6_PIN, HIGH);
      break;
  }
}

void button7Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT7");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_7, "ON");
      digitalWrite(RELAY7_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_7, "OFF");
      digitalWrite(RELAY7_PIN, HIGH);
      break;
  }
}

void button8Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT8");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("PRESSIONADO\n"); 
      setPowerStateOnServer(device_ID_8, "ON");
      digitalWrite(RELAY8_PIN, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("LIBERADO\n"); 
      setPowerStateOnServer(device_ID_8, "OFF");
      digitalWrite(RELAY8_PIN, HIGH);
      break;
  }
}
