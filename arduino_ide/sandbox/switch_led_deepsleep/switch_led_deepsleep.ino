#define BUTTON 12 // 18だと復帰できない
#define LED 27

RTC_SLOW_ATTR int bootCnt = 0;
RTC_SLOW_ATTR int buttonStat = 0;


// deepsleep ? LEDOFF : LEDON

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(BUTTON, INPUT_PULLUP);
  delay(1000);
  buttonStat = digitalRead(BUTTON);
  Serial.println(buttonStat);
  bootCnt +=1;
  Serial.printf("Boot: %02d\n", bootCnt);
}

void loop() {
  int pushed = digitalRead(BUTTON);
  Serial.printf("%d\n", pushed);
  sleep_chk();
}

void sleep_chk() {
  int pushed = digitalRead(BUTTON);
  if (pushed != buttonStat){
    digitalWrite(LED, LOW);
    // GPIO_NUM_18だと復帰できない
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, buttonStat);
    esp_deep_sleep_start();
  }
}
