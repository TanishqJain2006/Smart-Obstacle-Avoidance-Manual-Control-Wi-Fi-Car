// === ESP32-DevKit V1 Ultrasonic Sensor Transmitter ===
// Sends "OBSTACLE" or "CLEAR" to ESP32-CAM via Serial TX
#define TRIG_PIN 12
#define ECHO_PIN 14
#define SAFE_DISTANCE 20 // in cm

long duration;
int distance;

void setup() {
  Serial.begin(9600);          // TX -> CAM RX
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  distance = duration * 0.034 / 2;
  if (distance == 0 || distance > 200) distance = 200;

  if (distance < SAFE_DISTANCE) {
    Serial.println("OBSTACLE");
  } else {
    Serial.println("CLEAR");
  }

  delay(150);
}
