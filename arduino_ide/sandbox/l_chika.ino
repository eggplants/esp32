#define LED 5
#define WAIT 500


void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(WAIT);                      // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(WAIT);
}
