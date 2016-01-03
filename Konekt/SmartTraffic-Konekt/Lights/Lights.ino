

void setup() {
  pinMode(D02,OUTPUT);
  pinMode(D03,OUTPUT);
  digitalWrite(D02, HIGH);
  digitalWrite(D03, LOW);

  SerialUSB.begin(9600); /* USB UART */
  Serial2.begin(9600); /* TTL UART */
  SerialUSB.println("Konekt Dash Hello World Example Started!");
  SerialCloud.begin(115200); /* Konekt Cloud */
  SerialCloud.println("Setup Started"); /* one-time message */
}

void loop() {
    
    //D2 Red
    if (digitalRead(D02) == HIGH)
    {
      SerialCloud.println("Red Light");
       digitalWrite(D02, LOW);
       digitalWrite(D03, HIGH);
       
    }else{
      SerialCloud.println("Green Light");
      digitalWrite(D03, LOW);
      digitalWrite(D02, HIGH);
    }

  delay(30000);
 
  char currChar;
  /* we don't loop sending data, since we don't want to eat up
   * a lot of data on our SIM! */

  /* the code here will pass data between Cloud<-->UART */

  
  while (SerialUSB.available()) 
  {
  }

  while (Serial2.available()) {
    SerialCloud.write(Serial2.read());
  }

  while (SerialCloud.available()) {
    currChar = (char)SerialCloud.read();
    SerialUSB.write(currChar);
    Serial2.write(currChar);
  }

  delay(5);
  
  
}
