// Define stepper motor connections:

int bytes_read = 0; //characters that are stored from incoming data
int incomingByte = 0; // for incoming serial data
int waiting = 0; //open or closed communication
int got = 0; //about to got a message
//Positions of all are set equal to zero at start.
int incoming[54] = {}; // Motor #1-10 positions, 5 digits to each motor, 51 52 AND 53 are for relay on/off
int relay[4] = {2, 3, 4, 5};
int onoff[4] = {0, 0, 0, 0};
int motoPins[10]= {22, 23, 28, 29, 34, 35, 40, 41, 46, 47}; //Each Motor has 3 pins assigned to it.  EX. Pins 22,23,24 --> Step, Direction, Enable
long poses[10]=   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //Desired Positions of motors 1-10
long o_poses[10]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //Current Positions of motors 1-10
long compare[10]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //Displacement between Current and Desired Positions of motors 1-10
long maximum = 0;  //Used to measure maximum displacement (Minimum steps to take to get every motor where it needs to go)
long minimum = 0;  //A helper to measure maximum displacement (if the absolute maximum value is a negative number)
byte i = 0;        //This is a global variable counter.  Somehow this takes up less SRAM than local variables being used for counters (Using local variables in this code corrupts the long arrays)

void setup() {
        // Declare pins as output:
        for (int q = 0; q < 4; q++) {
                pinMode(q+2,OUTPUT);
                digitalWrite(relay[q],HIGH);
        }
        for (int j = 22; j < 52; j++) {
                pinMode(j, OUTPUT);
                digitalWrite(motoPins[j] + 2, HIGH);
        }
        //Setup for Serial Communication
        Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
        delay(500);
}
void loop() {
        Serial.println("o"); //This character tells LabVIEW that arduino is ready for incoming data


        while (waiting == 0) {
                //Arduino will read anything available, but not store anything yet.  It is waiting for LabVIEW to send a "begin storing" command
                if (Serial.available() > 0) {
                        got = Serial.read();
                        if (got == 33) { //33 is the character ! . Arduino is waiting to receive this before storing any data received.
                                waiting = 1; //Arduino is no longer waiting, and kicks out of this loop.
                        }
                }
        }


        while (bytes_read < 54) //We'll receive and store 54 characters.  This will move the specified motor to the specified position.  Then clear the stored characters and reset.
        {
                if (Serial.available() > 0) {
                        incomingByte = Serial.read() - 48;
                        if (incomingByte >= 0 && incomingByte <= 9) {
                                incoming[bytes_read] = incomingByte;
                                bytes_read++;
                        }
                }
        }

        waiting = 0; //Sets up to wait for new data once the full loop finishes.
        bytes_read = 0; //Resets the counter for storing data, so it will go through that loop again once the full loop finishes.

        for (i = 0; i < 10; i++) {
                poses[i] = incoming[i * 5] * 10000L + incoming[i * 5 + 1] * 1000 + incoming[i * 5 + 2] * 100 + incoming[i * 5 + 3] * 10 + incoming[i * 5 + 4] * 1;
                //1-5 stored characters get mushed into a 5 digit number and stored.  Then 6-10, 11-15, and so on until 36-40.  8 5-digit numbers total get stored to desired positions.
                compare[i] = poses[i] - o_poses[i]; //Finds the displacement for each motor and stores it.
                maximum = max(maximum, compare[i]); //These two lines find the min and max steps between all motor displacements.
                minimum = min(minimum, compare[i]); //
                if (compare[i] != 0) {
                        digitalWrite(motoPins[i] + 4, LOW); //If the motor needs to be moved, arduino powers it on.
                        if (compare[i] < 0) {
                                digitalWrite(motoPins[i] + 2, LOW); //arduino sets the direction the motor will turn
                        }                    //
                        else {               //
                                digitalWrite(motoPins[i] + 2, HIGH); //
                        }
                }
        }
        minimum = -1 * minimum;      //These two lines find the absolute max displacement for the motors.
        maximum = max(maximum, minimum); //


        for (i = 0; i < 3; i++) {
                onoff[i] = incoming[50+i];
                if (onoff[i] == 1) {
                        digitalWrite(relay[i],LOW);
                }
                else {
                        digitalWrite(relay[i],HIGH);
                }
        }

        for (long p = 0; p < maximum + 1; p++) { //This loop takes takes one step for each motor at the same time.  Motors that are powered off will not move.  Once a motor has reached its destination, arduino powers it off.
                for (i = 0; i < 10; i++) {
                        if (compare[i] == 0) {
                                digitalWrite(motoPins[i] + 4, HIGH); //If the motor is where it needs to be, power off.  Otherwise take a step.
                        }
                        if (compare[i] < 0) {
                                digitalWrite(motoPins[i], HIGH);
                        }
                        else if (compare[i] > 0) {
                                digitalWrite(motoPins[i], LOW);
                        }
                }
                delayMicroseconds(100);

                for (i = 0; i < 10; i++) {
                        if (compare[i] < 0) {
                                digitalWrite(motoPins[i], LOW);
                                compare[i]++; //Remember that a step was taken
                        }
                        else {
                                digitalWrite(motoPins[i], HIGH);
                                compare[i]--; //Remember that a step was taken
                        }
                }
                delayMicroseconds(100);

        }
        for (i = 0; i < 10; i++) {
                o_poses[i] = poses[i]; //Now that all the motors have reached their destinations, set desired positions to current positions.
        }

        maximum = 0; //Reset the max displacement for the next loop
        minimum = 0; //Reset the min displacement for the next loop

}
