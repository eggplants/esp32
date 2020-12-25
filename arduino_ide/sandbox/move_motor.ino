#define PIN_IN1  25
#define PIN_IN2  26
#define PIN_VREF_CHANNEL A17

void setup(){
    ledcSetup(0, 12800, 8);
    ledcAttachPin(PIN_VREF_CHANNEL, 0);
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
}

void loop()
{
    ledcWrite(0,128);
    digitalWrite(PIN_IN1,HIGH);
    digitalWrite(PIN_IN2,LOW);
    delay(5000);

    digitalWrite(PIN_IN1,HIGH);
    digitalWrite(PIN_IN2,HIGH);
    delay(1000);
//    // 逆回転
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(5000);
//
//    // ブレーキ
//    digitalWrite(PIN_IN1,HIGH);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(2000);
//
//    // モーターの回転速度を最大にする
//    ledcWrite(0,128);
//
//    // 逆回転
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(5000);
//
//    // ストップ
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,LOW);
//    delay(2000);
}
