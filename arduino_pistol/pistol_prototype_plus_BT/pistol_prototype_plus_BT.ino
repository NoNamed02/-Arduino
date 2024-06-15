#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h> // 블투

#define BT_RXD 8
#define BT_TXD 7
SoftwareSerial bluetooth(BT_RXD, BT_TXD);


MPU6050 mpu(0x68); // 기본 I2C 주소는 0x68입니다.
unsigned long last_time = 0;

int BallSW_A = 6;
int reload_btn = 5;
int shot_btn = 4;
bool is_reload = false;
bool shot = false;

void setup() {
  pinMode(BallSW_A, INPUT_PULLUP);
  pinMode(reload_btn, INPUT_PULLUP);
  pinMode(shot_btn, INPUT_PULLUP);

  Serial.begin(9600); // 블루투스 통신을 위한 시리얼 통신 설정
  Wire.begin();
  
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // 연결 실패 시 멈춤
  }
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float ax_rad = ax / 16384.0;
  float ay_rad = ay / 16384.0;
  float az_rad = az / 16384.0;
  
  float ax_deg = ax_rad * 180.0 / PI;
  float ay_deg = ay_rad * 180.0 / PI;
  float az_deg = az_rad * 180.0 / PI;
/*
  if (millis() > last_time + 200) {
    Serial.print("ax: ");
    Serial.print(ax_deg);
    Serial.print(", ay: ");
    Serial.print(ay_deg);
    Serial.print(", az: ");
    Serial.println(az_deg);
    last_time = millis();
  }
*/
  if(ax_deg < -40)
    Serial.println("mouse_move_right");
  if(ax_deg > 40)
    Serial.println("mouse_move_left");

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
  if (digitalRead(BallSW_A) == HIGH && is_reload == true) {
    Serial.println("R"); // 탄창 충격 감지
    is_reload = false;
  }
}
