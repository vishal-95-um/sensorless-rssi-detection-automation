#include <WiFi.h>

// wifi stuff
const char* ssid = "Enter your wifi ssid";
const char* password = "password";

// buffer and vars
int circle = 3;
int rssi[5];
int idx = 0;
bool buffer_full = false;
int avg = 0;

// bulb config
int bulb_pin = 22;
bool bulb_state = false;
unsigned long current_time = 0;

void setup() {
  Serial.begin(115200);

  // connect wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi.....");
    delay(500);
  }
  Serial.println("Connected to WiFi Successfully");

  // bulb pin setup
  pinMode(bulb_pin, OUTPUT);
  digitalWrite(bulb_pin, HIGH); // off initially (relay logic)
}

void loop() {
  int current_rssi = 0;
  bool found = false;

  // scan wifi
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    if (WiFi.SSID(i) == ssid) {
      current_rssi = WiFi.RSSI(i);
      Serial.print("RSSI: ");
      Serial.println(current_rssi);
      found = true;
      break;
    }
  }

  if (found) {
    // update buffer
    rssi[idx] = current_rssi;
    idx = (idx + 1) % circle;

    if (idx == 0) buffer_full = true;

    if (buffer_full) {
      // avg calc
      avg = 0;
      for (int i = 0; i < circle; i++) {
        avg += rssi[i];
      }
      avg = avg / circle;

      // main logic - rssi jump = movement
      if (abs(avg - current_rssi) > 8) {
        Serial.println("Human detected, Turning ON  Bukb for 5 seconds");
        bulb_state = true;
        digitalWrite(bulb_pin, LOW);
        current_time = millis();
      } else {
        Serial.println("No Human Detected Yet");
      }
    } else {
      Serial.println("Processing....");
    }
  } else {
    Serial.println("No ssid found yet");
  }

  // turn off after 5 sec
  if (bulb_state && (millis() - current_time) > 5000) {
    digitalWrite(bulb_pin, HIGH);
    bulb_state = false;
  }

  delay(500);
}
