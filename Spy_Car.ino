/*
 *       GOOD MORNING!!! 
 * Program by T.A.Vignesh
 * Project Name: Arduino Bluetooth Car
 */
 
//L298 module Connection   
  const int motorA1  = 5;  //Pin 5 of Arduino to L298 module 
  const int motorA2  = 6;  //Pin 6 to Arduino to L298 module
  const int motorB1  = 10; //Pin 10 to Arduino to L298 module
  const int motorB2  = 9;  //Pin 9 to Arduino to L298 module
//Other Connections
  const int frontlights  = 3; //Front leds connected to Arduino Pin 12
  const int backlights = 8;   //Back leds connected to Arduino pin 8
  const int declights = 7;
  const int buzzer = 8 ;       //Buzzer to Arduino UNO Pin 3
  const int gassens = 11;
  const int flamesens = 4;
//Useful Variables
  int state;          //For Bluetooth module input
  int vSpeed=200;     // Default speed, from 0 to 225

void setup() {
    // Set pins as outputs and inputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(backlights, OUTPUT);
    pinMode(frontlights, OUTPUT);
    pinMode(declights, OUTPUT); 
    pinMode(buzzer, OUTPUT);
    pinMode(flamesens, INPUT);
    pinMode(gassens, INPUT);
    pinMode(7, OUTPUT);
    pinMode(2, OUTPUT);         
    Serial.begin(9600);       // Initialize serial communication at 9600 bits per second:
}
 
void loop() {   
  //Save input data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();   
    }

    if (digitalRead(flamesens) == LOW){
      digitalWrite(2, HIGH);
      Serial.write("E");
    } else {
      digitalWrite(2, LOW);
      Serial.write("e");
    }
  

    if (digitalRead(gassens) == LOW){
      digitalWrite(7, HIGH);
      Serial.write("F");
    } else {
      digitalWrite(7, LOW);
      Serial.write("f");
    }

  //Change speed if state is equal from 0 to 9 and q. Values must be from 0 to 225
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=28.3;}
    else if (state == '2'){
      vSpeed=56.6;}
    else if (state == '3'){
      vSpeed=84.9;}
    else if (state == '4'){
      vSpeed=113.2;}
 	  else if (state == '5'){
      vSpeed=121.5;}
    else if (state == '6'){
      vSpeed=159.1;}
    else if (state == '7'){
      vSpeed=187.5;}
    else if (state == '8'){
      vSpeed=215.9;}
    else if (state == '9'){
      vSpeed=244.2;}
    else if (state == 'q'){
      vSpeed=255;}
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward
    if (state == 'F') {
    	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    else if (state == 'G') {
    	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
      analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    else if (state == 'I') {
      analogWrite(motorA1, 0);      analogWrite(motorA2, 0); 
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
    	analogWrite(motorA1, 0); analogWrite(motorA2, vSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    else if (state == 'H') {
    	analogWrite(motorA1, 0); analogWrite(motorA2, vSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
    }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    else if (state == 'J') {
    	analogWrite(motorA1, 0); analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
    	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0);      analogWrite(motorB2, vSpeed); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
    	analogWrite(motorA1, 0);      analogWrite(motorA2, vSpeed); 
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 		
    }
  /************************HeadLights On*****************************/
  //If state is equal with letter 'W', turn leds on
    else if (state == 'W') {  
         digitalWrite(frontlights, HIGH);
         state='n';
    }
  /************************HeadLights Off*****************************/
  //If state is equal with letter 'w', turn leds off
    else if (state == 'w') {
      digitalWrite(frontlights, LOW);
      state='n';
    }
  /************************Back Lights On*****************************/
  //If state is equal with letter 'U', turn leds on
    else if (state == 'U') {
         digitalWrite(backlights, HIGH);
      state='n';
    }
  /************************Back Lights Off*****************************/
  //If state is equal with letter 'u', turn leds off
    else if (state == 'u') {
         digitalWrite(backlights, LOW);
      state='n';
    }
  /**********************Horn On***************************/
  //If state is equal with letter 'V', play horn sound
    else if (state == 'V'){
         tone(buzzer, 1000);   //Buzzer on
      state='n';  
    }
  /**********************Horn Off***************************/
  //If state is equal with letter 'v', off horn sound
    else if (state == 'v'){
         noTone(buzzer);    //Buzzer off 
      state='n';  
    }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S' | state == 'f' | state == 'b' | state == 'r' | state == 'l'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }
 /************************Decorative Lights On*****************************/
  //If state is equal with letter 'X', turn leds on
    else if (state == 'X') {
         digitalWrite(declights, HIGH);
      state='n';
    }
  /************************Decorative Lights Off*****************************/
  //If state is equal with letter 'x', turn leds off
    else if (state == 'x') {
         digitalWrite(declights, LOW);
      state='n';
    }    
}
