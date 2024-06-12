int BallSW_A = 6;
int reload_btn = 5;
bool is_reload = false;

void setup() {
  pinMode(BallSW_A, INPUT_PULLUP);
  pinMode(reload_btn, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(reload_btn) == LOW) { // 장전 버튼
    Serial.println("LOW_reload");
  }
  if (digitalRead(BallSW_A) == HIGH) {
    Serial.println("HIGH"); // 탄창 충격 감지
  }
}
