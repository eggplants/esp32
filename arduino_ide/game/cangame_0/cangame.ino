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
#define PIN_IN1 0
#define PIN_IN2 2

#define PIN_VREF_CHANNEL 1

// TONE: https://tomari.org/main/java/oto.html
#define A 27.500
#define As 29.135
#define B 30.868
#define C 32.703
#define Cs 34.648
#define D 36.708
#define EB 38.891
#define Ds 38.891
#define E 41.203
#define F 43.654
#define Fs 46.249
#define G 48.999
#define Gs 51.913
#define A 55.000
#define As 58.270
#define B 61.735
#define C2 65.406
#define Cs2 69.296
#define D2 73.416
#define Ds2 77.782
#define E2 82.407
#define F2 87.307
#define Fs2 92.499
#define G2 97.999
#define Gs2 103.826
#define A2 110.000
#define As2 116.541
#define B2 123.471
#define C3 130.813
#define Cs3 138.591
#define D3 146.832
#define Ds3 155.563
#define E3 164.814
#define F3 174.614
#define Fs3 184.997
#define G3 195.998
#define Gs3 207.652
#define A3 220.000
#define As3 233.082
#define B3 246.942
#define C4 261.626
#define Cs4 277.183
#define D4 293.665
#define Ds4 311.127
#define E4 329.628
#define F4 349.228
#define Fs4 369.994
#define G4 391.995
#define Gs4 415.305
#define A4 440.000
#define As4 466.164
#define B4 493.883
#define C5 523.251
#define Cs5 554.365
#define D5 587.330
#define Ds5 622.254
#define E5 659.255
#define F5 698.456
#define Fs5 739.989
#define G5 783.991
#define Gs5 830.609
#define A5 880.000
#define As5 932.328
#define B5 987.767
#define C6 1046.502
#define Cs6 1108.731
#define D6 1174.659
#define Ds6 1244.508
#define E6 1318.510
#define F6 1396.913
#define Fs6 1479.978
#define G6 1567.982
#define Gs6 1661.219
#define A6 1760.000
#define As6 1864.655
#define B6 1975.533
#define C7 2093.005
#define Cs7 2217.461
#define D7 2349.318
#define Ds7 2489.016
#define E7 2637.020
#define F7 2793.826
#define Fs7 2959.955
#define G7 3135.963
#define Gs7 3322.438
#define A7 3520.000
#define As7 3729.310
#define B7 3951.066
#define C8 4186.009
#define TONE_SPEED 600


//////////
// MAIN //
//////////

/* TIPS:
 * Deepsleepで残したいデータは属性`RTC_SLOW_ATTR`
 * ボタンの状態を見てDeepsleepする場合は`deepSleep()`
 */

RTC_SLOW_ATTR int buttonStat = 0;

///////////
// SETUP //
///////////

void setup()
{
  Serial.begin(9600);
  // LED
  pinMode(LED, OUTPUT);
  // keep turning on
  ledOn();

  // BUTTON
  pinMode(BUTTON, INPUT_PULLUP);
  buttonStat = digitalRead(BUTTON);
  while(buttonStat==digitalRead(BUTTON)){}

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
  changeSpeed(255);
  beep();delay(500);beep();delay(500);
  hide();
  beep();delay(500);beep();delay(500);
}

//////////
// LOOP //
//////////

void loop()
{
//  chkSonic();
  beep();delay(500);beep();delay(500);
  normal(); // normal: 60sec, kicked ? p_win: p_lose
  forward();
  delay(2000);
  beep();delay(500);beep();delay(500);
  star();   // star: 60sec, kicked ? p_lose: p_win
  delay(100);
  halt();
}

//////////
// FUNC //
//////////

void hide()
{
  forward();
  delay(100000);
  halt();
}

void normal()
{
  //int r = randStartime() + 30;
  int r = 60;
  for(int i=0;i < r; i++)
  {
//    deepSleepChk();
    Serial.printf("n[%04d/%04d]: %f\n", i, r, measureDistCm());
    if(measureDistCm() >= 10.0)
    {
      delay(1000);
      // 連続2回10以上なら缶は存在しない
      if(measureDistCm() >= 10.0)
      {
          playMusic("prelude");
          while(buttonStat!=digitalRead(BUTTON)){}
          ESP.restart();
      }
    }
    delay(1000);
  }
}

void star()
{
//  deepSleepChk();
//  playMusic("power_up");
  beep();delay(500);beep();delay(500);
  //int r = randStartime();
  int r = 60;
  for(int i=0;i < r;i++)
  {
//    deepSleepChk();
    Serial.printf("s[%04d/%04d]: %f\n", i, r, measureDistCm());
    if(measureDistCm() >= 10.0)
    {
      delay(1000);
      // 連続3回10以上なら缶は存在しない
      if(measureDistCm()>=10.0)
      {
        delay(500);
        if(measureDistCm()>=10.0){
          playMusic("baddy");
          while(buttonStat!=digitalRead(BUTTON)){}
          ESP.restart();
        }
      }
    }
    delay(1000);
  }
//  playMusic("power_down");
  beep();delay(500);beep();delay(500);
}

void deepSleepChk() {
  int pushed = digitalRead(BUTTON);
  if (pushed != buttonStat){
//    digitalWrite(LED, LOW);
//    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, buttonStat);
//    beep();
//    esp_deep_sleep_start();
  ESP.restart();
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

void tone(double freq)
{
  ledcWriteTone(SPEAKER_CHANNEL, freq);
  delay(TONE_SPEED);
  ledcWriteTone(SPEAKER_CHANNEL, 0);
}

void playMusic(char *title)
{
  if(title=="test")
  {
    tone(C4); tone(D4); tone(E4); tone(F4);
    tone(G4); tone(A4); tone(B4); tone(C5);
    tone(C5); tone(B4); tone(A4); tone(G4);
    tone(F4); tone(E4); tone(D4); tone(C4);
  }else if(title=="baddy")
  {
    tone(C3); tone(D5); tone(D5); tone(Ds5);
    tone(D5); tone(C5); tone(D5); tone(Fs5);
  }else if(title=="prelude")
  {
    tone(C4); tone(E5); tone(G5);
    tone(C5); tone(E5); tone(G4);
  }else if(title=="ba_ding")
  {
    tone(B5); tone(E6);
  }else if(title=="power_up")
  {
    tone(G4); tone(C5); tone(E5);
    tone(G5); tone(E5); tone(G5);
  }else if(title=="power_down")
  {
    tone(G5); tone(Ds5); tone(C5);
    tone(G4); tone(B5); tone(C5);
  }else{
    playMusic("test");
  }
}

void chkSonic()
{
  while(true)
  {
    Serial.printf("%f\n", measureDistCm());
    delay(100);
  }
}
