/* Example sketch to control a stepper motor with TB6600 stepper motor driver and Arduino without a library: continuous rotation. More info: https://www.makerguides.com */
// Define stepper motor connections:

int bytes_read = 0;
int incomingByte = 0; // for incoming serial data
int waiting = 0; //open or closed communication
int got = 0; //about to got a message
//Positions of all are set equal to zero at start.
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;
int incoming[4] = { 0, 0, 0, 0}; // Motor #1-7, per,cent, open
int dirPins[7] = {2, 4, 6, 8, 10, 12, 14};
int stepPins[7] = {3, 5, 7, 9, 11, 13, 15};
int poses[7] = {pos1, pos2, pos3, pos4, pos5, pos6, pos7};
void setup() {
  // Declare pins as output:
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
   pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);
   pinMode(14, OUTPUT);
   pinMode(15, OUTPUT);

  // Set the spinning direction CW/CCW:
  digitalWrite(dirPins[0], HIGH);
  digitalWrite(dirPins[1], HIGH);
  digitalWrite(dirPins[2], HIGH);
  digitalWrite(dirPins[3], HIGH);
  digitalWrite(dirPins[4], HIGH);
  digitalWrite(dirPins[5], HIGH);
  digitalWrite(dirPins[6], HIGH);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}
void loop() {
 while (waiting == 0) {
  //communication is open in this loop. We're listening for a queue right now.
  Serial.println("o");
  if (Serial.available() > 0) {
    got = Serial.read();
    if (got == 33){ //33 is the character ! .  We're waiting to receive this before communication can begin.
    Serial.println("?"); //We'll send ? to labVIEW to let it know communication can start.
    waiting = 1;
    }
    }
  }
  for (int i = 0; i<7; i++) {
 while (bytes_read < 4) //We'll receive and store 4 characters.  This will move the specified motor to the specified position.  Then clear the stored characters and reset.
 {
    if (Serial.available() > 0) {
       incomingByte = Serial.read() - 48;
       if (incomingByte > -1 && incomingByte <10) {
       incoming[bytes_read] = incomingByte;
      bytes_read ++;
       }
       else if (incomingByte != -38){
        Serial.println("Invalid Input.");
       }
    }
 }
      bytes_read = 0;
       if (incoming[0]-1 == i){
         poses[i] = incoming[1]*100+incoming[2]*10+incoming[3]*1;
       }
}
      waiting = 0;
     // Serial.print("Stored data: ");
     // for (int i = 0; i<4; i++) {
      // Serial.print(incoming[i]);
     // }
      for (int i = 0; i<7; i++) {
       Serial.print(" ");
       Serial.print("motor ");
       Serial.print(i+1);
       Serial.print(" set to:");
       Serial.println(poses[i]);
       delay(75);
      }
      for (int i = 0; i<4; i++) {
        incoming[i] = 0;
      }
      }
