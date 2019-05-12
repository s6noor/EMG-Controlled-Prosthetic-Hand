// Capstone: EMG Controlled Prosthetic Hand
// Main Author: Sidrah Noor
// Team Members: Tong Xu, Naushaba Fatima
// Board: Arduino UNO
// Programmer: AVRISP mkll
// Note: This is the demo code for a single finger movement. 
// Explanation of code:  The code reads the value / position of the actuator from index sensor. The two servo pins are used to move the Actuator. 
//The primary input is an EMG signal that varies from 0 - 628, when the sensor value is high, it indicates a change in position.         

///////////////////////////////////////////////////// Variable Declaration ////////////////////////////////////////////////////////////////////

        int indexsensor = A0; //connected to P
        int indexservo0mplus = 3; //conneted to M+
        int indexservo1mminus = 4; //connected to M-
        int MIN = 14; //actuator value ranges from 14 to 600, 950 -1000 when it is fully open otherwise closed
        int MAX = 800;
        int sensMax = 600;
        int prevActuator = 0;
        int prevSensor = 0;
        
///////////////////////////////////////////////////// Initial Setup //////////////////////////////////////////////////////////////////////////        
        void setup() {
          Serial.begin(9600); // initialize serial communication at 9600 bits per second:
          pinMode(indexsensor, INPUT);
          pinMode(indexservo0mplus, OUTPUT);
          pinMode(indexservo1mminus, OUTPUT);
          digitalWrite(indexservo0mplus, HIGH);
          digitalWrite(indexservo1mminus, LOW);
        
        }
        
        void loop() {
        
          int sensorValue = analogRead(A4); //read the EMG sensor value
          Serial.println(sensorValue);
           delay(25);
           
          //  sensorValue = constrain(sensorValue, MIN, MAX);
          int actuatorState = analogRead(indexsensor);  //read the current position of the actuator
        
          if (actuatorState < MAX && sensorValue < sensMax) { //if the actuator is closed, and the sensor value is not telling it to change
            digitalWrite(indexservo1mminus, HIGH); //remain close
            digitalWrite(indexservo0mplus, LOW);
            delay(50);
            loop();
          }
        
          if (actuatorState > MAX && sensorValue < sensMax) { //if the actuator is open, and the sensor value is not telling it to change
            digitalWrite(indexservo1mminus, LOW); //remain open
            digitalWrite(indexservo0mplus, HIGH);   
            delay(50);
            loop();        
          }

          if (actuatorState < MAX && sensorValue > sensMax) { //if the actuator is closed, and the sensor value is telling it to change
           while(actuatorState <MAX){
            digitalWrite(indexservo1mminus, LOW); // open
            digitalWrite(indexservo0mplus, HIGH);
            actuatorState = analogRead(indexsensor);  //read the current position of the actuator
           }
            loop();
        
          }

          if (actuatorState > MAX && sensorValue > sensMax) { //if the actuator is open, and the sensor value is telling it to change
            while (actuatorState > MAX){
            digitalWrite(indexservo1mminus, HIGH); //close
            digitalWrite(indexservo0mplus, LOW);
            actuatorState = analogRead(indexsensor);  //read the current position of the actuator
            }
            loop();
     }

  
        }
