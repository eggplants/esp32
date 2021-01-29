#define BUTTON 12
#define LED 25

RTC_SLOW_ATTR int bootCnt = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  bootCnt +=1;
  Serial.printf("Boot: %02d\n", bootCnt);
}

void loop() {
  sleep_chk();
}

void sleep_chk() {
  int pushed = digitalRead(BUTTON);
  if (pushed == 1){
    digitalWrite(LED, LOW);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, (pushed==1) ? 1 : 0);
    while (pushed == 1){
      pushed = digitalRead(BUTTON);
    }
    Serial.printf("%d\n", pushed);
    esp_deep_sleep_start();
  }
}
