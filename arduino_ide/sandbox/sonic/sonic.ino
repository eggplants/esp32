#define TRIG 32
#define ECHO 33

void setup()
{
    Serial.begin(9600);
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
}

void sendTriggerPulse()
{
    digitalWrite(TRIG, LOW); 
    delayMicroseconds(2); 
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
}

void loop()
{
  double d = measureDistCm();
  Serial.println(d);
  Serial.printf("isFar: bool -> %s\n", isFar(10.0)?"t":"f");
  delay(1000);
}

bool isFar(double dist)
{
  double d = measureDistCm();
  if(d == -1)
  {
    return false;
  }else if(d >= dist){
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
