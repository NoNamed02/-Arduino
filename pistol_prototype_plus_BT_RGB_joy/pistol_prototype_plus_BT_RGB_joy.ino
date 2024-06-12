#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h> // 블투

#define BT_RXD 8
#define BT_TXD 7
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

MPU6050 mpu(0x68);
unsigned long last_time = 0;
unsigned long print_interval = 300;

int BallSW_A = 6;
int reload_btn = 5;
int shot_btn = 4;
bool is_reload = false;
bool shot = false;
int reload_time = 2000;

#define BLUE 11
#define GREEN 10
#define RED 9

void setup() {
  pinMode(12, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  pinMode(BallSW_A, INPUT_PULLUP);
  pinMode(reload_btn, INPUT_PULLUP);
  pinMode(shot_btn, INPUT_PULLUP);

  Wire.begin();
  
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // 연결 실패 시 멈춤
  }
  Serial.begin(9600); // 블루투스 통신을 위한 시리얼 통신 설정
}

void loop() {
  int redValue;
  int greenValue;
  int blueValue;
  if (is_reload) {
    redValue = 0;
    greenValue = 0;
    blueValue = 255;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
  } else {
    redValue = 255;
    greenValue = 0;
    blueValue = 0;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
  }
  
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float ax_rad = ax / 16384.0;
  float ay_rad = ay / 16384.0;
  float az_rad = az / 16384.0;
  
  float ax_deg = ax_rad * 180.0 / PI;
  float ay_deg = ay_rad * 180.0 / PI;
  float az_deg = az_rad * 180.0 / PI;
  
  unsigned long current_time = millis();
  if (current_time - last_time >= print_interval) {
    if (ax_deg < -40)
      Serial.println("mouse_move_right");
    else if (ax_deg > 40)
      Serial.println("mouse_move_left");
      
    if(analogRead(A0)> 900){
      Serial.println("W");
    }
    else if(analogRead(A0) < 100){
      Serial.println("S");
    }
    else if(analogRead(A1)> 900){
      Serial.println("A");
    }
    else if(analogRead(A1) < 100){
      Serial.println("D");
    }
    last_time = current_time;
  }

  // 버튼들 설정(볼 스위치 포함)
  if (digitalRead(shot_btn) == LOW && !shot) {
    Serial.println("mouse_left_click");
    shot = true; // shot 상태 업데이트
  } else if (digitalRead(shot_btn) == HIGH) {
    shot = false; // 버튼이 다시 놓였을 때 shot 상태 초기화
  }

  if (digitalRead(reload_btn) == LOW) { // 장전 버튼
    is_reload = true;
    //Serial.println("reload_btn");
  }
  if (digitalRead(BallSW_A) != LOW && is_reload == true && reload_time >= 2000) {
    Serial.println("R"); // 탄창 충격 감지
    is_reload = false;
    reload_time = 0;
  }
  if(reload_time < 2000){
    reload_time++;  
  }
}
