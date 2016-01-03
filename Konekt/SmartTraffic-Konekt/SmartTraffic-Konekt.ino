/* Konekt Dash Hello World
*
* Author: Patrick F. Wilbur <hello@konekt.io> <pdub@pdub.net>
*
* Purpose: This program demonstrates interactive serial mode,
* a mechanism for performing cable replacement serial passthrough
* over cellular to the cloud. This example works out-of-the-box
* with zero configuration.
*
* License: Copyright (c) 2015 Konekt, Inc. All Rights Reserved.
*
* Released under the MIT License (MIT)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
*/
#include "timer.h"

//
#define GREEN 23
#define RED 22
//

void ChangeLight(){
  if(digitalRead(RED) == HIGH){
    ChangeGreen();
  }else if(digitalRead(GREEN) == HIGH){
    ChangeRed();
  }
  
}

void ChangeGreen(){
   digitalWrite(RED, LOW);
   digitalWrite(GREEN, HIGH);
}

void ChangeRed(){
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
}

void setup() {

  digitalWrite(RED, HIGH);
  
  SerialUSB.begin(9600); /* USB UART */
  Serial2.begin(9600); /* TTL UART */
  //SerialUSB.println("Konekt Dash Hello World Example Started!");
  SerialCloud.begin(115200); /* Konekt Cloud */
  //SerialCloud.println("Hello, World!"); /* one-time message */
  
  
  Timer timeinput = new Timer();
  timeinput.start();
  long TimerSet = timeinput.getElapsedTime();
  
}

void loop() {

  if( timeinput.getElapsedTime() >= (TimerSet + 90000) ){
    TimerSet = timeinput.getElapsedTime();
    ChangeLight();
    
  }
  
  char currChar;
  /* we don't loop sending data, since we don't want to eat up
   * a lot of data on our SIM! */

  /* the code here will pass data between Cloud<-->UART */

  while (SerialUSB.available()) {
    SerialCloud.write(SerialUSB.read());
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
