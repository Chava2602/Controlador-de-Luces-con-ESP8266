//Google Assistant Home Automation
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Luz1            D1
#define Luz2            D2
#define Luz3            D3
#define Luz4            D4
#define Luz5            D5

#define WLAN_SSID       ""        // SSID
#define WLAN_PASS       ""        //password

// Adafruit.io Setup 

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    " "     // Username
#define AIO_KEY         " "    // Auth Key

//WIFI CLIENT
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Luz1"); // Feeds name should be same everywhere
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Luz2");
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Luz3");
Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Luz4");
Adafruit_MQTT_Subscribe Light5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Luz5");

void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(Luz1, OUTPUT);
  pinMode(Luz2, OUTPUT);
  pinMode(Luz3, OUTPUT);
  pinMode(Luz4, OUTPUT);
  pinMode(Luz5, OUTPUT);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&Light4);
  mqtt.subscribe(&Light5);
}

void loop() {
 
  MQTT_connect();
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(Luz1, Light1_State);
      
    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(Luz2, Light2_State);
    }
    if (subscription == &Light3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light3.lastread);
      int Light3_State = atoi((char *)Light3.lastread);
      digitalWrite(Luz3, Light3_State);
    }
    if (subscription == &Light4) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light4.lastread);
      int Light4_State = atoi((char *)Light4.lastread);
      digitalWrite(Luz4, Light4_State);      
    }
    if (subscription == &Light5) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light5.lastread);
      int Light5_State = atoi((char *)Light5.lastread);
      digitalWrite(Luz5, Light5_State);
    }
  }
  
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
