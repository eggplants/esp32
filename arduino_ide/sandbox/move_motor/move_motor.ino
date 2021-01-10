#define PIN_IN1  19
#define PIN_IN2  18
//#define PIN_VREF_ADO A17 // PIN27
#define PIN_VREF_ADC A10 // PIN4
#define PIN_VREF_CHANNEL 1

void setup(){
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    ledcAttachPin(PIN_VREF_ADC, PIN_VREF_CHANNEL);
}

void loop()
{
    changeSpeed(255);
    forward(PIN_IN1, PIN_IN2);
    delay(1000);
    changeSpeed(255);
    delay(5000);
    brake(PIN_IN1, PIN_IN2);
}

void changeSpeed(int speed)
{
    ledcWrite(PIN_VREF_CHANNEL, speed);
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
