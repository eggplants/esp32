#define ECHO 32 // Echo Pin
#define TRIG 33 // Trigger Pin

double Duration = 0;
double Distance = 0; //距離

void setup()
{
    Serial.begin(9600);
    pinMode( ECHO, INPUT );
    pinMode( TRIG, OUTPUT );
}

void loop()
{
    digitalWrite(TRIG, LOW); 
    delayMicroseconds(2); 
    digitalWrite( TRIG, HIGH ); //超音波を出力
    delayMicroseconds( 10 ); //
    digitalWrite( TRIG, LOW );
    Duration = pulseIn( ECHO, HIGH ); //センサからの入力
    if (Duration > 0)
    {
        Duration = Duration/2; //往復距離を半分にする
        Distance = Duration*340*100/1000000; // 音速を340m/sに設定
        Serial.print("Distance:");
        Serial.print(Distance);
        Serial.println(" cm");
    }
    delay(500);
}
