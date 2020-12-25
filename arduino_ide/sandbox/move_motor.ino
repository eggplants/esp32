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
    change_speed(0,128);
    forward(PIN_IN1, PIN_IN2);
    delay(5000);

    brake(PIN_IN1, PIN_IN2);
    delay(1000);
}

void change_speed(int channel, int speed)
{
    ledcWrite(channel, speed);
}


void stop(int in1, int in2)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}

void brake(int in1, int in2)
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
}

void forward(int in1, int in2)
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void backward(int in1, int in2)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
}
