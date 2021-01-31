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
#define BUTTON 26

// MOTOR
#define PIN_VREF_ADC A10 // PIN 4
#define PIN_VREF_CHANNEL 1
#define PIN_IN1 0
#define PIN_IN2 2

//////////
// MAIN //
//////////

/* TIPS:
 * Deepsleepで残したいデータは属性`RTC_SLOW_ATTR`
 * ボタンの状態を見てDeepsleepする場合は`deepSleep()`
 */

RTC_SLOW_ATTR int buttonStat = 0;


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

  // Start
  playMusic("ba_ding");
  buttonStat = digitalRead(BUTTON);
}

int cnt = 0;

void loop()
{
  normal(); // normal: (60~150)sec, kicked ? p_win: p_lose
  star();   // star: (30, 120)sec, kicked ? p_lose: p_win
  delay(100);
}

//////////
// FUNC //Serial.println(measureDistCm());
//////////

void normal()
{
  int r = randStartime() + 30;
  for(int i=0;i < r; i++)
  {
    deepSleepChk();
    Serial.printf("%04d: %f\n", i, measureDistCm());
    if(measureDistCm() >= 10.0)
    {
      while(true)
      {
        playMusic("prelude");
        deepSleepChk();
      }
    }
    delay(1000);
  }
}

void star()
{
  playMusic("power_up");
  deepSleepChk();
  forward();
  int r = randStartime();
  for(int i=0;i < r;i++)
  {
    deepSleepChk();
    if(measureDistCm() >= 10.0)
    {
      halt();
      while(true)
      {
        deepSleepChk();
        playMusic("dadadadum");
      }
    }
    delay(1000);
  }
  halt();
  playMusic("power_down");
}

void deepSleepChk() {
  int pushed = digitalRead(BUTTON);
  if (pushed != buttonStat){
    digitalWrite(LED, LOW);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, buttonStat);
    esp_deep_sleep_start();
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

int randStartime()
{
  int r = random(0, 9);
  return (10 * r) + 30;
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
