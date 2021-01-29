void setup() {
  // put your setup code here, to run once:
  pinMode(23, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value;
  value = digitalRead(23);
  Serial.println(value);
  delay(1000);
}
