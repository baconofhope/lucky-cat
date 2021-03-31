#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#include <Servo.h>
Servo servo;
int SPIN = A0;
int pos = 0;   

int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  pinMode(SPIN,OUTPUT);
  servo.attach(SPIN); //analog pin 0
  servo.write(200);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  int state = 0;
}

void dunk(int times) {
 for (int t = 0; t <= times-1; t += 1) {
  for (pos = 20; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(12);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 100; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
 }
}

void loop() {

  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     
    switch (results.value) {
     case 0xFFFFFFFF:
      dunk(1);
     break;

     case 0xFD8877:
      dunk(2);
     break;

     case 0xFD48B7:
      dunk(3);
     break;
    }
    
     irrecv.resume(); // Receive the next value
    }
    

}
