#define TRIG 32
#define ECHO 33

double Duration = 0;
double Distance = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
}

void sendTriggerPulse()
{
    digitalWrite(TRIG, LOW); 
    delayMicroseconds(2); 
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
}

void loop()
{
    sendTriggerPulse();
    Duration = pulseIn(ECHO, HIGH);
    if (Duration > 0)
    {
        Duration = Duration / 2;
        Distance = Duration * 340 * 100 / 1000000;
        Serial.printf("Distance: %f cm\n", Distance);
    }
    delay(500);
}
