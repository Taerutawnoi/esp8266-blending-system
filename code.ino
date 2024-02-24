#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "[template id]"
#define BLYNK_TEMPLATE_NAME "[template name]"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "[blynk token]"; //put your blynk token here
char ssid[] = "[ssid]"; //wifi ssid (wifi name)
char pass[] = "[pass]"; //wifi password

#define RELAY_PIN D1 // Change this to the pin your relay is connected to (D1 on NodeMCU)
#define LED 2

bool manualControl = false;
bool blendRunningV1 = false;
bool blendRunningV2 = false;
bool blendRunningV3 = false;
unsigned long blendStartTimeV1;
unsigned long blendStartTimeV2;
unsigned long blendStartTimeV3;
unsigned long blendTimeV1; // Duration of blending in milliseconds for V1
unsigned long blendTimeV2; // Duration of blending in milliseconds for V2
unsigned long blendTimeV3; // Duration of blending in milliseconds for V3

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED, HIGH);
}

void loop() {
  Blynk.run();

  // Check if manual control is enabled
  if (manualControl) {
    Blynk.virtualWrite(V1, 0); // Ensure V1 is set to off when manual control is enabled
    Blynk.virtualWrite(V2, 0); // Ensure V2 is set to off when manual control is enabled
    Blynk.virtualWrite(V3, 0); // Ensure V3 is set to off when manual control is enabled
  }

  // Check if blending process for V1 is running
  if (blendRunningV1 && !manualControl) {
    unsigned long currentTime = millis() - blendStartTimeV1;

    if (currentTime < blendTimeV1) {
      if (currentTime % 6000 < 5000) { // 5 seconds ON, 1 second OFF
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED, LOW);
      } else {
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED, HIGH);
      }
    } else {
      blendRunningV1 = false;
      Serial.println("Blend Finished for V1");
    }
  }

  // Check if blending process for V2 is running
  if (blendRunningV2 && !manualControl) {
    unsigned long currentTime = millis() - blendStartTimeV2;

    if (currentTime < blendTimeV2) {
      if (currentTime % 6000 < 5000) { // 5 seconds ON, 1 second OFF
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED, LOW);
      } else {
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED, HIGH);
      }
    } else {
      blendRunningV2 = false;
      Serial.println("Blend Finished for V2");
    }
  }

  // Check if blending process for V3 is running
  if (blendRunningV3 && !manualControl) {
    unsigned long currentTime = millis() - blendStartTimeV3;

    if (currentTime < blendTimeV3) {
      if (currentTime % 6000 < 5000) { // 5 seconds ON, 1 second OFF
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED, LOW);
      } else {
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED, HIGH);
      }
    } else {
      blendRunningV3 = false;
      Serial.println("Blend Finished for V3");
    }
  }
}

// BLYNK_WRITE for V0 to control manual on/off
BLYNK_WRITE(V0) { //เปิด-ปิด เอง
  int pinValue = param.asInt();
  if (pinValue == 1) {
    manualControl = true;
    digitalWrite(RELAY_PIN, LOW); // Turn on relay
    digitalWrite(LED, LOW); // Turn on LED
  } else {
    manualControl = false;
    digitalWrite(RELAY_PIN, HIGH); // Turn off relay
    digitalWrite(LED, HIGH); // Turn off LED
  }
}

// BLYNK_WRITE for V1 to start blending process for 8 minutes
BLYNK_WRITE(V1) { // แกงส้ม
  int pinValue = param.asInt();
  if (pinValue == 1 && !manualControl) { // Start blending only if not in manual control mode
    blendRunningV1 = true;
    blendStartTimeV1 = millis();
    blendTimeV1 = 8 * 60 * 1000; // Set blending duration to 8 minutes
  }
}

// BLYNK_WRITE for V2 to start blending process for 5 minutes
BLYNK_WRITE(V2) { //แกงเผ็ด
  int pinValue = param.asInt();
  if (pinValue == 1 && !manualControl) { // Start blending only if not in manual control mode
    blendRunningV2 = true;
    blendStartTimeV2 = millis();
    blendTimeV2 = 5 * 60 * 1000; // Set blending duration to 5 minutes
  }
}

// BLYNK_WRITE for V3 to start blending process for 6 minutes
BLYNK_WRITE(V3) { // แกงกะทิ
  int pinValue = param.asInt();
  if (pinValue == 1 && !manualControl) { // Start blending only if not in manual control mode
    blendRunningV3 = true;
    blendStartTimeV3 = millis();
    blendTimeV3 = 6 * 60 * 1000; // Set blending duration to 6 minutes
  }
}
