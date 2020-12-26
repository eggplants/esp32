#define LED 12
#define WAIT 500


void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(WAIT);
    digitalWrite(LED, LOW);
    delay(WAIT);
}
