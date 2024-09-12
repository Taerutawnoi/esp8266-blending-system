#define BLYNK_TEMPLATE_ID "YOUR TEMPLATE ID"
#define BLYNK_TEMPLATE_NAME "YOUR TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN "YOUR AUTH TOKEN"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>

#define LED 2
#define Relay D1 //Pin that Relay Connected to

//Part of Timer Function
int sec = 0;
int mins = 0;
int trig = 0;

unsigned long record = 0;
unsigned long times = 0;
//End of The Part of Timer Function

//ส่วนของฟังชั่นโหมด
unsigned long ksom_sum = 60000;
unsigned long kkati_sum = 50000;
unsigned long kped_sum = 30000;
unsigned long watermelon_sum = 15000;
unsigned long banana_sum = 20000;
unsigned long strawberry_sum = 15000;

bool ksom_trig = false;
bool kkati_trig = false;
bool kped_trig = false;
bool watermelon_trig = false;
bool banana_trig = false;
bool strawberry_trig = false;
//จบส่วนของฟังชั่นโหมด

//LED and Relay State
bool LEDstate = false;
bool RelayState = false;
//-------------------

// Your Blynk Auth Token
char auth[] = "YOUR AUTH TOKEN";  // Replace with your Blynk Auth Token

// Flag for Wi-Fi reset
bool shouldResetWiFi = true;

void setup() {
  // Start Serial for debugging
  Serial.begin(9600);

  // Initialize WiFiManager
  WiFiManager wifiManager;

  // Force Wi-Fi configuration every boot
  if (shouldResetWiFi) {
    wifiManager.resetSettings(); // This clears the stored Wi-Fi credentials
  }

  // Set custom hotspot SSID and password
  wifiManager.autoConnect("ESP8266-WIFI-BOOT-SETUP", "nodemcu8266");

  // Check if connected to Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");

    // Connect to Blynk
    Blynk.config(auth);
    Blynk.connect();

    // Check if connected to Blynk
    if (Blynk.connected()) {
      Serial.println("Connected to Blynk!");
    } else {
      Serial.println("Failed to connect to Blynk.");
    }
  } else {
    Serial.println("Failed to connect to WiFi.");
  }

  pinMode(LED, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(LED, HIGH);
  digitalWrite(Relay, HIGH);
}

void loop() {
  // Run Blynk if connected
  if (Blynk.connected()) {
    Blynk.run();
  }

  if (LEDstate && RelayState && times > 0 && millis() - record >= times) {
    timedfinal();
  }

  if (LEDstate && RelayState && ksom_trig && millis() - record >= ksom_sum) {
    timedfinal();
    ksom_trig = false;
  }

  if (LEDstate && RelayState && kkati_trig && millis() - record >= kkati_sum) {
    timedfinal();
    kkati_trig = false;
  }

  if (LEDstate && RelayState && kped_trig && millis() - record >= kped_sum) {
    timedfinal();
    kped_trig = false;
  }

  if (LEDstate && RelayState && watermelon_trig && millis() - record >= watermelon_sum) {
    timedfinal();
    watermelon_trig = false;
  }

  if (LEDstate && RelayState && banana_trig && millis() - record >= banana_sum) {
    timedfinal();
    banana_trig = false;
  }

  if (LEDstate && RelayState && strawberry_trig && millis() - record >= strawberry_sum) {
    timedfinal();
    strawberry_trig = false;
  }
}

//Timer Function
void timedstart() {
  times = (mins * 60 + sec) * 1000;
  if (times > 0) {
    digitalWrite(LED, LOW);
    digitalWrite(Relay, LOW);
    LEDstate = true;
    RelayState = true;
    Serial.print("Timed Task Started\n");

    record = millis();
  }
}

void timedfinal() {
  digitalWrite(LED, HIGH);
  digitalWrite(Relay, HIGH);
  LEDstate = false;
  RelayState = false;
  Serial.print("Timed Task Finished\n");

  trig = 0;
  Blynk.virtualWrite(V0, 0);
  times = 0;
}

BLYNK_WRITE(V2) {
  sec = param.asInt();
}

BLYNK_WRITE(V3) {
  mins = param.asInt();
}
//End of Timer Function

BLYNK_WRITE(V0) {
  //Timer Func
  trig = param.asInt();
  if (trig == 2) {
    timedstart();
  }
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  if (pinValue == 2) {
    digitalWrite(LED, HIGH);
    digitalWrite(Relay, HIGH);
    LEDstate = false;
    RelayState = false;
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    sec = 0;
    mins = 0;
    trig = 0;
    record = 0;
    times = 0;
    ksom_trig = false;
    kkati_trig = false;
    kped_trig = false;
    watermelon_trig = false;
    banana_trig = false;
    strawberry_trig = false;
  }

  if (pinValue == 1) {
    digitalWrite(LED, LOW);
    digitalWrite(Relay, LOW);
    LEDstate = true;
    RelayState = true;
  } else if (pinValue == 0) {
    digitalWrite(LED, HIGH);
    digitalWrite(Relay, HIGH);
    LEDstate = false;
    RelayState = false;
  }
}

//ส่วนของฟังชั่นโหมด
void ksom() { //ปั่นแกงส้ม
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Som\n");

  ksom_trig = true;
  record = millis();
}

void kkati() { //ปั่นแกงกะทิ
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Kati\n");

  kkati_trig = true;
  record = millis();
}

void kped() { //ปั่นแกงเผ็ด
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Kati\n");

  kped_trig = true;
  record = millis();
}

void watermelon() { //ปั่นแกงเผ็ด
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Kati\n");

  watermelon_trig = true;
  record = millis();
}

void banana() { //ปั่นแกงเผ็ด
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Kati\n");

  banana_trig = true;
  record = millis();
}

void strawberry() { //ปั่นแกงเผ็ด
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  LEDstate = true;
  RelayState = true;
  Serial.print("Start Blending Kaeng Kati\n");

  strawberry_trig = true;
  record = millis();
}
//จบส่วนของฟังชั่นโหมด

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    ksom();
  }

  if (pinValue == 2) {
    kkati();
  }

  if (pinValue == 3) {
    kped();
  }

  if (pinValue == 4) {
    watermelon();
  }

  if (pinValue == 5) {
    banana();
  }

  if (pinValue == 6) {
    strawberry();
  }
}
