#include <WiFi.h>
#include <HTTPClient.h>

// ================= CÀI ĐẶT CÁ NHÂN =================
#define WIFI_SSID "YOUR_WIFI_NAME"       
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"      

#define BOT_TOKEN "YOUR_BOT_TOKEN" 
#define CHAT_ID "YOUR_CHAT_ID"               
// ===================================================

const int DOOR_SENSOR_PIN = 2; 
const int BUZZER_PIN      = 3; 
const int ONBOARD_LED     = 8; 

const unsigned long WARN_TIME  = 10000; 
const unsigned long ALARM_TIME = 20000; 

unsigned long doorOpenStartTime = 0;
bool isDoorOpen = false;
bool telegramSent = false; 

void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Sửa chuẩn lại đường dẫn API Telegram
    String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) + "/sendMessage?chat_id=" + String(CHAT_ID) + "&text=" + message;
    
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.printf("-> Ket qua Telegram: (Ma HTTP: %d)\n", httpCode);
    } else {
      Serial.printf("-> Loi ket noi: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, HIGH);

  Serial.print("Dang ket noi WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi ket noi thanh cong!");

  sendTelegramMessage("He%20thong%20canh%20bao%20tu%20kem%20da%20ONLINE!");
}

void loop() {
  int sensorState = digitalRead(DOOR_SENSOR_PIN);

  if (sensorState == HIGH) {
    if (!isDoorOpen) {
      isDoorOpen = true;
      doorOpenStartTime = millis();
      telegramSent = false;
      Serial.println("\n>>> [PHAT HIEN] CUA TU DANG HO! Bat dau dem giay...");
    }

    unsigned long openDuration = millis() - doorOpenStartTime;

    if (openDuration >= ALARM_TIME) {
      digitalWrite(BUZZER_PIN, HIGH); 
      digitalWrite(ONBOARD_LED, LOW); 

      if (!telegramSent) {
        Serial.println(">>> DANG GUI TIN NHAN TELEGRAM...");
        sendTelegramMessage("BAO%20DONG:%20Cua%20tu%20kem%20dang%20mo%20qua%2020%20giay!");
        telegramSent = true; 
      }
    } 
    else if (openDuration >= WARN_TIME) {
      digitalWrite(BUZZER_PIN, HIGH); delay(100); digitalWrite(BUZZER_PIN, LOW); delay(900);
    } 
    else {
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(ONBOARD_LED, HIGH); 
    }
  } 
  else {
    if (isDoorOpen) {
      isDoorOpen = false;
      digitalWrite(BUZZER_PIN, LOW);   
      digitalWrite(ONBOARD_LED, HIGH); 
      Serial.println("\n>>> [AN TOAN] 2 CANH CUA DA DONG KIN!\n");
      
      if (telegramSent) {
        sendTelegramMessage("AN%20TOAN:%20Tu%20kem%20da%20duoc%20dong%20kin.");
        telegramSent = false;
      }
    }
  }
}