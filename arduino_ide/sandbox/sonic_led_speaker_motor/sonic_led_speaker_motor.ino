#define LED 27

#define SPEAKER 13
#define SPEAKER_CHANNEL 0

#define TRIG 32
#define ECHO 33

#define PIN_IN1  19
#define PIN_IN2  18
#define PIN_VREF_ADC A10 // PIN 4
#define PIN_VREF_CHANNEL 1

double Duration = 0;
double Distance = 0;

void setup()
{
    // START SERIAL COMM
    Serial.begin(9600);

    // LED
    pinMode(LED, OUTPUT);

    // SPEAKER
    ledcSetup(0,12000, 8);
    ledcAttachPin(SPEAKER, SPEAKER_CHANNEL);

    // SONIC
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);

    // MOTOR
    pinMode(PIN_IN1, OUTPUT); 
    pinMode(PIN_IN2, OUTPUT);
    ledcAttachPin(PIN_VREF_ADC, 1);
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
        beep();
    }
    changeSpeed(255);
    forward();
    delay(5000);
    stop();
    lChila();
}

void beep()
{
  ledcWrite(SPEAKER_CHANNEL, 128);
  delay(500);
  ledcWrite(SPEAKER_CHANNEL, 0);
}


void lChila()
{
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
}

void sendTriggerPulse()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
}

void changeSpeed(int speed)
{
  ledcWrite(PIN_VREF_CHANNEL, speed); 
}

void stop()
{
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);
}

void brake()
{
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, HIGH);
}

void forward()
{
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
}

void backward()
{
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
}
