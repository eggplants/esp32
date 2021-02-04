/////////
// PIN //
/////////

// LED
#define LED 27

// SPEAKER
#define SPEAKER 13
#define SPEAKER_CHANNEL 0


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

///////////
// SETUP //
///////////

void setup()
{
  Serial.begin(9600);

  // LED
  pinMode(LED, OUTPUT);
  // ON
  digitalWrite(LED, HIGH);
  
  // SPEAKER
  ledcSetup(0,12000, 8);
  ledcAttachPin(SPEAKER, SPEAKER_CHANNEL);

}

//////////
// LOOP //
//////////

void loop()
{
  playMusic("prelude"); // win
  delay(2000);
  playMusic("baddy");  // lose
  delay(2000);

}

//////////
// FUNC //
//////////

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
  }else{
    playMusic("test");
  }
}
