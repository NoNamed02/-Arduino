int BallSW_A = 6;

void setup() {
  pinMode(BallSW_A, INPUT_PULLUP);
  Serial.begin(9600);  // 시리얼 통신을 초기화합니다.
}

void loop() {
  if (switchState == LOW) { // 만약 볼 스위치A가 ON이 되면
    Serial.println("LLLLLLLLLL"); // LLLLLLLLLL을 시리얼 모니터에 출력합니다.
  }
  delay(500); // 너무 빠르게 출력되지 않도록 딜레이를 추가합니다.
}
