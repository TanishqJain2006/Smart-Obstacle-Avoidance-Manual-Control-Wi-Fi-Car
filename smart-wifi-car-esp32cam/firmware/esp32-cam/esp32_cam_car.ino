/****************************************************
   ESP32-CAM Wi-Fi Controlled Robot Car
   (16-Pin AI Thinker Module)
   with Live Streaming and Obstacle Detection
   Compatible with ESP32 Core v3.3.2 (IDF 5.5)
****************************************************/

#include "esp_camera.h"
#include <WiFi.h>
#include "camera_pins.h"

// ======= CAMERA MODEL =======
#define CAMERA_MODEL_AI_THINKER

// ======= MOTOR DRIVER PINS =======
#define IN1 13
#define IN2 15
#define IN3 14
#define IN4 2
#define ENA 16
#define ENB 4

// ======= SERIAL COMM (from other ESP32) =======
#define RX_PIN 3   // default hardware RX of ESP32-CAM

// ======= WIFI CONFIG =======
const char* ssid = "Team_02";
const char* password = "Tanishq12";

// ======= GLOBAL VARIABLES =======
WiFiServer server(80);
String command = "";

void startCameraServer();
void stopMotors();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void checkSerial();

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors(); // Start stopped

  // Connect Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi Connected!");
  Serial.print("🌐 IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("❌ Camera Init Failed");
    return;
  }

  startCameraServer();
  server.begin();

  Serial.println("📷 Camera Ready!");
  Serial.print("Stream at: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  checkSerial(); // listens for "OBSTACLE"

  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/forward") != -1) moveForward();
  else if (request.indexOf("/backward") != -1) moveBackward();
  else if (request.indexOf("/left") != -1) turnLeft();
  else if (request.indexOf("/right") != -1) turnRight();
  else if (request.indexOf("/stop") != -1) stopMotors();

  // Simple web control interface
  String html = "<html><body style='text-align:center;'>";
  html += "<h2>ESP32-CAM Wi-Fi Bot</h2>";
  html += "<img src='http://" + WiFi.localIP().toString() + ":81/stream' width='320'><br><br>";
  html += "<a href='/forward'><button>↑ Forward</button></a><br><br>";
  html += "<a href='/left'><button>← Left</button></a> ";
  html += "<a href='/stop'><button>■ Stop</button></a> ";
  html += "<a href='/right'><button>→ Right</button></a><br><br>";
  html += "<a href='/backward'><button>↓ Backward</button></a>";
  html += "</body></html>";

  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  client.print(html);
  delay(10);
}

// ======= MOVEMENT FUNCTIONS =======
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
  Serial.println("🚗 Forward");
}
void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
  Serial.println("🚙 Backward");
}
void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
  Serial.println("↩️ Left");
}
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
  Serial.println("↪️ Right");
}
void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  Serial.println("🛑 Stopped");
}

// ======= OBSTACLE DETECTION (Serial) =======
void checkSerial() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg == "OBSTACLE") {
      stopMotors();
      Serial.println("⚠️ OBSTACLE DETECTED — BOT STOPPED ⚠️");
    }
  }
}

// ======= CAMERA SERVER =======
#include "esp_timer.h"
#include "esp_http_server.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void startCameraServer() {
  extern void startCameraServer();
}
