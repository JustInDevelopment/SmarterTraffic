const int outPin = 2; // Using FAST_IO
const int inPin = 3; // Using FAST_IO

void setup() {

  Serial.begin(115200);
  pinMode(outPin, OUTPUT_FAST);
  pinMode(inPin, INPUT_FAST);
}

void loop()
{

//sonicPing use here after pir goes off
}

void sonicPing(){
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
