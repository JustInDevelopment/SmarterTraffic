const int outPin = 2; // Using FAST_IO
const int inPin = 3; // Using FAST_IO
#define PIR_MOTION_SENSOR 4

void setup() {

  Serial.begin(115200);
  pinMode(outPin, OUTPUT_FAST);
  pinMode(inPin, INPUT_FAST);
  pinsInit();
}

void loop()
{

    if(isPeopleDetected())//if it detects the moving people?
    sonic();
  else{}
  
}

void sonic(){

  long duration, inches, cm;

  fastDigitalWrite(outPin, LOW);
  waitMicros(2);
  fastDigitalWrite(outPin, HIGH);
  waitMicros(10);
  fastDigitalWrite(outPin, LOW);

  duration = pulseIn(inPin, HIGH); // calls fastGpioPciDigitalRead

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}
boolean isPeopleDetected()
{
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  if(sensorValue == HIGH)//if the sensor value is HIGH?
  {
    return true;//yes,return true
  }
  else
  {
    return false;//no,return false
  }
}
void waitMicros(int val)
{
  unsigned long a = micros();
  unsigned long b = micros();
  while((b-a) < val)
  {
    b = micros();
    if(a>b)
    {
      break;
    }
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void pinsInit()
{
  pinMode(PIR_MOTION_SENSOR, INPUT);
}


