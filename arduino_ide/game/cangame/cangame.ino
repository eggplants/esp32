/////////
// PIN //
/////////

// LED
#define LED 27

// SPEAKER
#define SPEAKER 13
#define SPEAKER_CHANNEL 0

// SONIC
#define TRIG 32
#define ECHO 33

// POWER SWITCH
#define BUTTON 18

// MOTOR
#define PIN_VREF_ADC A10 // PIN 4
#define PIN_VREF_CHANNEL 1
#define PIN_IN1 0
#define PIN_IN2 2

//////////
// MAIN //
//////////

/* 
 *  
 * TIPS:
 * Deepsleepで残したいデータは属性`RTC_SLOW_ATTR`
 * ボタンの状態を見てDeepsleepする場合は`deepSleep()`
 * 
 */

void setup()
{
  Serial.begin(9600);
  // LED
  pinMode(LED, OUTPUT);
  // keep turning on
  ledOn();

  // BUTTON
  pinMode(BUTTON, INPUT_PULLUP);

  // SPEAKER
  ledcSetup(0,12000, 8);
  ledcAttachPin(SPEAKER, SPEAKER_CHANNEL);

  // SONIC
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  // try 
  sendTriggerPulse();

  // MOTOR
  pinMode(PIN_IN1, OUTPUT); 
  pinMode(PIN_IN2, OUTPUT);
  ledcAttachPin(PIN_VREF_ADC, PIN_VREF_CHANNEL);
  // Set speed as max
  changeSpeed(255);
}

int cnt = 0;

void loop()
{
  deepSleep();
  Serial.println(measureDistCm());
  if(isFar(10.0))
  {
//    tone(27.0);/
  }else{
//    tone(3951.0);/
  }
//  double dist = measureDistCm();
//  if(dist > 0)
//  {
//    beep();
//  }else{
//    beep();delay(100);beep();
//  }
}

//////////
// FUNC //
//////////

bool isFar(double dist)
{
  double d = measureDistCm();
  if(d == -1)
  {
    return false;
  }else if(d >= dist)
  {
    return true;
  }else{
    return false;
  }
  
}

double measureDistCm()
{
  sendTriggerPulse();
  double duration = pulseIn(ECHO, HIGH);
  double distance = 0;
  if (duration > 0)
  {
    duration = duration / 2;
    distance = duration * 340 * 100 / 1000000;
  }else{
    distance = -1.0;
  }
  return distance;
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

void ledOff()
{
  digitalWrite(LED, LOW);
}

void ledOn()
{
  digitalWrite(LED, HIGH);
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

void halt()
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

void deepSleep()
{
  int pushed = digitalRead(BUTTON);
  if (pushed == 1){
    digitalWrite(LED, LOW);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, (pushed==1) ? 1 : 0);
    while (pushed == 1){
      pushed = digitalRead(BUTTON);
    }
    Serial.printf("%d\n", pushed);
    esp_deep_sleep_start();
  }
}