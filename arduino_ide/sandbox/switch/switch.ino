#define BUTTON 18

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("%d\n", digitalRead(BUTTON));
}
