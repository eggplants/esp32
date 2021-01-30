#define PIN_IN1  0
#define PIN_IN2  2
#define PIN_VREF_ADC A10 // PIN 4
#define PIN_VREF_CHANNEL 1

void setup(){
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    ledcAttachPin(PIN_VREF_ADC, PIN_VREF_CHANNEL);
    changeSpeed(255);
}

void loop()
{
    forward(PIN_IN1, PIN_IN2);
    delay(1000);
    changeSpeed(255);
    delay(5000);
    halt(PIN_IN1, PIN_IN2);
}

void changeSpeed(int speed)
{
    ledcWrite(PIN_VREF_CHANNEL, speed);
}


void halt(int in1, int in2)
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
