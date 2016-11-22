#include <Sparki.h>  // include the robot library
#include "pitches.h" // include a list of pitches

#define STOPCODE 88
void setup() {
  sparki.servo(SERVO_CENTER); // center the servo
}

// /------^-----\
// |            |
// |  1   2   3 |
// |  4   5   6 |
// |  7   8   9 |
// | 10   0  23 |
// |     79     |
// | 31  27  26 |
// |            |
// \____________/


void printVar(const char* tex, float val){
  sparki.clearLCD();
  sparki.print(tex); 
  sparki.print(": "); 
  sparki.println(val);
  sparki.updateLCD();
}


void colorNote(int note)
{
 switch(note){
    case 131:
    case 523:
    case 262: sparki.RGB(RGB_RED); break;
    case 147:
    case 294: sparki.RGB(RGB_ORANGE); break;
    case 165:
    case 330: sparki.RGB(RGB_YELLOW); break;
    case 175:
    case 349: sparki.RGB(RGB_GREEN); break;
    case 196:
    case 392: sparki.RGB(RGB_BLUE); break;
    case 220:
    case 440: sparki.RGB(RGB_INDIGO); break;
    case 247:
    case 494: sparki.RGB(RGB_VIOLET); break;

 }
}


// magnetometer
void magnet() {
    int IRCode;
  do{  
  sparki.clearLCD(); // wipe the screen
  
  float x  = sparki.magX();   // measure the accelerometer x-axis
  float y  = sparki.magY();   // measure the accelerometer y-axis
  float z  = sparki.magZ();   // measure the accelerometer z-axis

  // write the measurements to the screen
  sparki.println("Magnetometer");
  sparki.print("Mag X: "); 
  sparki.println(x);

  sparki.print("Mag Y: "); 
  sparki.println(y);
  
  sparki.print("Mag Z: "); 
  sparki.println(z);
  
  sparki.updateLCD(); // display all of the information written to the screen
  delay(100);
        IRCode = sparki.readIR(); 
  }while(IRCode != STOPCODE);

}


// light sensor

void printLight() {
    int IRCode;
  do{  
  sparki.clearLCD(); // wipe the screen
  
  int left   = sparki.lightLeft();   // measure the left light sensor
  int center = sparki.lightCenter(); // measure the center light sensor
  int right  = sparki.lightRight();  // measure the right light sensor

  // write the measurements to the screen
  sparki.println("Light sensors");
  sparki.print("Left   "); 
  sparki.println(left);

  sparki.print("Center ");
  sparki.println(center);
  
  sparki.print("Right  ");
  sparki.println(right);
  
  sparki.updateLCD(); // display all of the information written to the screen
  delay(100);
          IRCode = sparki.readIR(); 
  }while(IRCode != STOPCODE);

}


// accelerometer

void accelerometer() {

    int IRCode;
  do{  
  sparki.clearLCD(); // wipe the screen
  
  float x  = sparki.accelX();   // measure the accelerometer x-axis
  float y  = sparki.accelY();   // measure the accelerometer y-axis
  float z  = sparki.accelZ();   // measure the accelerometer z-axis

  // write the measurements to the screen
    sparki.println("Accelerometer");
  sparki.print("Accel X: "); 
  sparki.println(x);

  sparki.print("Accel Y: "); 
  sparki.println(y);
  
  sparki.print("Accel Z: "); 
  sparki.println(z);
  
  sparki.updateLCD(); // display all of the information written to the screen
  delay(100);
      IRCode = sparki.readIR(); 
  }while(IRCode != STOPCODE);

  
}

//////////////////////
// Theremin   //
//////////////////////
// button 6
//
// 
//
// 


void theremin(){
  sparki.RGB(RGB_BLUE);
 int cm ;
  int IRCode;
  do{  
    int cm = 100+sparki.ping()*15; // measures the distance with Sparki's eyes
    //100 
    sparki.beep(cm,70);

    sparki.RGB(min(cm/10,100), 20, min((100-cm*10)/100,100));
    printVar("note (Hz)", 100 + cm*10);
    delay(100); //give enough time to enter radius
    IRCode = sparki.readIR(); 
  }while(IRCode != STOPCODE);

  
  }

  
//////////////////////
// CIRCLE   //
//////////////////////
// button 26
//
// 
//
// 


void doCircle(){
  sparki.RGB(RGB_RED);
  sparki.clearLCD();
  sparki.println("Radius (dm)? "); 
  sparki.updateLCD();
  int IRCode;
  do{  
    delay(100); 
    IRCode = sparki.readIR(); 
  }while(IRCode <0 || IRCode>9);

  makeCircle(IRCode*10); 
  
  }

void makeCircle(int r)
{
  int IRCode;
  float semiAsse = 4.6;
  sparki.RGB(RGB_GREEN); // turn the light green
  sparki.clearLCD();
  sparki.print("Semiasse: "); 
  sparki.println(semiAsse); // tells the distance to the computer  
  sparki.print("Radius: "); 
  sparki.println(r); // tells the distance to the computer
  sparki.print("V Ratio: "); 
  sparki.println(100*(r-semiAsse)/(r+semiAsse)); // tells the distance to the computer
  sparki.updateLCD();
  /*
  for(int i=1;i<4;i++){
      sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
      sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 100*(r-semiAsse)/(r+semiAsse));
      delay(5000*i);
      sparki.motorStop(MOTOR_LEFT);
      sparki.motorStop(MOTOR_RIGHT);
      delay(5000);
  }*/ 
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 100*(r-semiAsse)/(r+semiAsse));
  do{  
    delay(500); //give enough time to make the drawing

    IRCode = sparki.readIR(); 
  }while(IRCode != STOPCODE);
  sparki.motorStop(MOTOR_LEFT);
  sparki.motorStop(MOTOR_RIGHT);
}

/*******************************************
 Melody
 
This example shows how to make a short melody
with Sparki's buzzer.

This example is based on the Arduino example
by Tom Igoe.
********************************************/
// button 7


void melody() {
  // play each note in the arrays
  // notes in the melody:
  // fra martino
int melody[] = { 
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
   NOTE_E4, NOTE_F4, NOTE_G4,
   NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
   NOTE_D4, NOTE_G3, NOTE_C4, 
    NOTE_D4, NOTE_G3, NOTE_C4, 
  };
/*

 RGB_RED     100, 0,   0
 RGB_ORANGE  90,  100, 0
 RGB_YELLOW  60,  100, 0
 RGB_GREEN   0,   100, 0
 RGB_BLUE    0,   0,   100
 RGB_PINK    90,  0,   100
 RGB_INDIGO  20,  0,   100
 RGB_VIOLET  60,  0,   100
 RGB_WHITE   60,  100, 90
 RGB_OFF 
 
*/
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 2,
    4, 4, 2,
    8,8,8,8,4,4,
    8,8,8,8,4,4,
    4, 4, 2,
    4, 4, 2,
 };

 //printVar("size of melody",sizeof(melody)/sizeof(melody[0]));
 int  melodyLen=sizeof(melody)/sizeof(melody[0]);
  for (int thisNote = 0; thisNote<melodyLen  ; thisNote++) {

    // calculate the note duration as 1 second divided by note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    colorNote(melody[thisNote]);
    sparki.beep(melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    sparki.noBeep();
  }
}
//////////////////////
// TEST IR code     //
//////////////////////
// button 31
//
// print received IR code
//
void printIRcode()
{
  int code;

  do{
    code = sparki.readIR(); // read any IR code Sparki has seen
    if(code != -1){ // if Sparki has recently seen in IR code
      //sparki.clearLCD(); // wipe the screen
      printVar("Received code: ",code);
      //sparki.print("Received code: "); // Say we've receved a code...
      //sparki.println(code); // ... and what that code's nubmer was
      }
      //sparki.updateLCD(); // refresh the LCD
  }while(code != STOPCODE);
}

//////////////////////
// EDGE AVOIDANCE   //
//////////////////////
// button 2
//
// 
//
void edgeAvoid()
{
  int IRCode;

      printVar("edge Avoidance ",1);


  do{
    sparki.RGB(RGB_GREEN); // turn the light green
    int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
    int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
    
    int threshold = 200; // if below this value, no surface underneath
    
    if (edgeLeft < threshold) // if no surface underneath left sensor
    {
      sparki.RGB(RGB_RED);
      sparki.moveBackward();
      delay(500);
      sparki.moveRight(20); // turn right
    }
  
    if (edgeRight < threshold) // if no surface underneath right sensor
    {
      sparki.RGB(RGB_RED);
      sparki.moveBackward();
      delay(500);
      sparki.moveLeft(20); // turn left
    }
  
    sparki.moveForward(); // move forward
    delay(100); // wait 0.1 seconds
    
    IRCode = sparki.readIR(); 
 
  }while(IRCode != STOPCODE);
}

//////////////////////
// WALL AVOIDANCE   //
//////////////////////
// button 1
//
//
//
void wallAvoid()
{
  int IRCode;
  int cm ;
  do{
    sparki.RGB(RGB_GREEN); // turn the light green
    sparki.moveForward(); // move Sparki forward
    cm = sparki.ping(); // measures the distance with Sparki's eyes
    sparki.clearLCD();
    sparki.print("Distance: "); 
    sparki.print(cm); // tells the distance to the computer
    sparki.println(" cm"); 
    sparki.updateLCD();
    if(cm != -1) // make sure its not too close or too far
    { 
        if(cm < 20) // if the distance measured is less than 10 centimeters
        {
            sparki.RGB(RGB_RED); // turn the light red
            //sparki.beep(); // beep!
            sparki.moveBackward(10); // back up 10 centimeters
            sparki.moveRight(30); // rotate right 30 degrees
        }
    }

    delay(100); // wait 0.1 seconds (100 milliseconds)
      IRCode = sparki.readIR();
     
 
  }while(IRCode != STOPCODE);
}

//////////////////////
// light follow     //
//////////////////////
// button 4
//
// 
//
void followLight()
{
  int IRCode;
  do{
    int left   = sparki.lightLeft();   // measure the left light sensor
    int center = sparki.lightCenter(); // measure the center light sensor
    int right  = sparki.lightRight();  // measure the right light sensor
   
    if ( (center > left) && (center > right) ){  // if the center light is the strongest
      sparki.moveForward(); // move Sparki Forward
    }
   
    if ( (left > center) && (left > right) ){    // if the left light is the strongest
      sparki.moveLeft(); // move Sparki Left
    }
   
    if ( (right > center) && (right > left) ){   // if the right light is the strongest
      sparki.moveRight(); // move Sparki Right
    }
   
    delay(100); // wait 0.1 seconds
    IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}


//////////////////////
// sorrisi          //
//////////////////////
//
// BUTTON 0

int blinkCounter;
 
int x = 0; //integer to keep track of how much Sparki's eyes have moved 
 
boolean lookRight; //flag to trigger looking right
boolean lookLeft; //flag to trigger looking left
boolean lookCenterFromRight; //flag to tell Sparki to look back at the middle after looking right
boolean lookCenterFromLeft; //flag to tell Sparki to look back at the middle after looking left

void makeSmiles()
{
  int IRCode;
  do{

 
 sparki.clearLCD(); // wipe the LCD clear
 
 //start drawing eyes code
 if(blinkCounter > 195)
 blinkEyes();
 else if(lookRight || lookCenterFromRight)
 lookEyes();
 else
 drawEyes();
 //end drawing eyes code
 
 sparki.updateLCD(); // put the drawings on the screen
 
 delay(100); // delay for the animation
 
 blinkCounter ++; //make counter count up
 if(blinkCounter == 200){
 blinkCounter = 0; //reset counter
 }
 
 if(blinkCounter == 100)
 {
 lookRight = true; 
 }
  IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}




void drawEyes()
{
 sparki.drawCircle(32, 25, 20); //eye 1
 sparki.drawCircle(96, 25, 20); //eye 2
 
 sparki.drawCircleFilled(32, 25, 5); //pupil 1
 sparki.drawCircleFilled(96, 25, 5); //pupil 2
 
 sparki.drawLine(15,15, 49,15);//eyelid 1
 sparki.drawLine(79,15, 112,15);//eyelid 2 
}
 
void blinkEyes()
{
 sparki.drawCircle(32, 25, 20); //eye 1
 sparki.drawCircle(96, 25, 20); //eye 2
 
 sparki.drawLine(12,24, 52,24);//eyelid 1
 sparki.drawLine(76,24, 115,24);//eyelid 2 
 
 sparki.drawLine(12,25, 52,25);//eyelid 3
 sparki.drawLine(76,25, 115,25);//eyelid 4 
}
 
void lookEyes()
{
 sparki.drawCircle(32, 25, 20); //eye 1
 sparki.drawCircle(96, 25, 20); //eye 2
 
 sparki.drawCircleFilled(32 + x, 25, 5); //pupil 1 (add X to change position
 sparki.drawCircleFilled(96 + x, 25, 5); //pupil 2 (add X to change position
 
 sparki.drawLine(15,15, 49,15);//eyelid 1
 sparki.drawLine(79,15, 112,15);//eyelid 2 
 
 if(lookRight)
 {
 sparki.moveRight(3); //actually move Sparki
 x++; //move pupils the to the right
  if(x >= 15)//keep the pupils inside the eyes
  {
  lookRight = false; //done looking right
  lookCenterFromRight = true; //now look back to the center
  }
 }
 
 if(lookCenterFromRight)
 {
 x--; //move the pupils to the left
 if(x == 0) //if Sparki is looking back at the center
 lookCenterFromRight = false; //turn off looking to center
 }
}

// end sorrisi









//////////////////////
// Hill climb       //
//////////////////////
// button 5
//
// RISE SLOPES
//
// 
void hillClimb()
{
  int IRCode;
  do{
    sparki.RGB(RGB_ORANGE); // turn the light green
        float x = sparki.accelX();
        float y = sparki.accelY();
     
        // is Sparki already facing downhill or uphill?
        if ( (x < 1) && (x > -1) )
        {
          if ( y < 0 ) // if sparki is facing uphill
          {
            sparki.moveForward();
          }
          if ( y > 0 ) // if sparki is facing downhill
          {
            sparki.moveBackward();
          }      
        }
        else{ // if Sparki is not facing uphill or downhill, have Sparki turn until it is
          sparki.RGB(RGB_RED);
          if ( x > 1 ) // if tilted right
          {
            sparki.moveLeft();
          }
          if ( x < -1 ) // if tilted left
          {
            sparki.moveRight();
          }   
        }
        delay(100);
      IRCode = sparki.readIR();
     
 
  }while(IRCode != STOPCODE);
}


//////////////////////
// LINE FOLLOW      //
//////////////////////
// button 3
//
// line following example
//
// 
void lineFollow() {
  int threshold = 700;
  
 int IRCode;
  do{ 
      int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
      int lineCenter = sparki.lineCenter(); // measure the center IR sensor
      int lineRight  = sparki.lineRight();  // measure the right IR sensor

     if ( lineCenter < threshold ) // if line is below left line sensor
      {  
        sparki.moveForward(); // move forward
      }
      else{
        if ( lineLeft < threshold ) // if line is below left line sensor
        {  
          sparki.moveLeft(); // turn left
        }
      
        if ( lineRight < threshold ) // if line is below right line sensor
        {  
          sparki.moveRight(); // turn right
        }
      }
    
      sparki.clearLCD(); // wipe the screen
      
      sparki.print("Line Left: "); // show left line sensor on screen
      sparki.println(lineLeft);
      
      sparki.print("Line Center: "); // show center line sensor on screen
      sparki.println(lineCenter);
      
      sparki.print("Line Right: "); // show right line sensor on screen
      sparki.println(lineRight);
      
      sparki.updateLCD(); // display all of the information written to the screen
    
      delay(100); // wait 0.1 seconds
    
    
      IRCode = sparki.readIR();
     
 
  }while(IRCode != STOPCODE);
}


//////////////////////
// bouncing ball    //
//////////////////////
// button 10
//
// 
//
// 
void bounceBall() {
  int IRCode;

  // starting position
  int x = 1;
  int y = 32;

  // starting velocity
  int vx = rand() % 4 + 1;
  int vy = rand() % 2 ;

  do{ 
       sparki.clearLCD(); // wipe the LCD clear

       // bouncing
       if ( x < 1 || x > 126) //changed this
       vx = -vx;
       if ( y < 1 || y > 62) //changed this
       vy = -vy;
       
       // go on      
       x = x + vx; 
       y = y + vy;
      
       sparki.drawCircleFilled(x,y, 5); // small filled circle vertically centered     
       sparki.updateLCD(); // put the drawings on the screen
       
       delay(80); // delay for the animation
    

  ////
  IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}

 
//////////////////////
// draw pixels    //
//////////////////////
// button 23
//
// 
//
// 
void drawSnow() {
  int IRCode;
  do{ 
       sparki.clearLCD(); // wipe the LCD clear
        for(int i=0;i<20;i++)
          sparki.drawPixel(rand() % 126 + 1,rand() % 61 + 1);
     
       sparki.updateLCD(); // put the drawings on the screen
       delay(500); // delay for the animation
    

  ////
  IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}



//////////////////////
// Ultrasonic sensor    //
//////////////////////
// button 27
//
// http://arcbotics.com/lessons/signal-filtering-techniques/
//
// 
void readDistance()
{
  int IRCode;
  do{ 
    sparki.clearLCD();
    float cm=0; 
    for(int i=0; i<3; i++)
    {
      cm +=sparki.ping();
      delay(20); 
    }// measures the distance with Sparki's eyes
    
    sparki.print("Distance: "); 
    sparki.print(cm/3); // tells the distance to the computer
    sparki.println(" cm"); 
    
    if(cm != -1) // make sure its not too close or too far
    { 
        if(cm < 10) // if the distance measured is less than 10 centimeters
        {
            //sparki.beep(); // beep!
        }
    }
    sparki.updateLCD();
    delay(500); // wait 0.1 seconds (100 milliseconds)
    
  IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}
///////////////////////


//////////////////////
// MAZE SOLVER    //
//////////////////////
// button 9
//
// 
//
// 
//for sensors
int edgeLeft;
int edgeRight;
int threshold;
int lineCenter;

//for wall finding
boolean foundLWall;
int wallFindType = 0;
int turnCount = 0;

boolean foundWall;
boolean foundDeadEnd;
//for calibrating
boolean foundLeftWall = false; 
boolean calibrated = false; 
boolean rightWall = false;

void mazeSolve()
{
    int IRCode;
  threshold = 700;
  do{ 
  sparki.clearLCD();

  readSensors();

  if(calibrated == false)
  {
    calibrateSparki();
  }
  else{

    if(foundDeadEnd && wallFindType == 0){
      sparki.moveRight(90);
      sparki.moveBackward(4);
      sparki.moveForward();
    }
    else if(foundLWall){
      wallFindType = 0;
      sparki.moveForward();
    }
    else if(foundLWall == false && wallFindType == 0){
      sparki.moveStop();
      wallFindType = 1; //now we enter the wall finding routine
      sparki.moveForward(.5);
    }
    if( wallFindType > 0 ){
      wallFind();
    }
  }
    IRCode = sparki.readIR();
  }while(IRCode != STOPCODE);
}
/*
  void readSensors(){
    foundLWall = false;
    foundDeadEnd = false;
    edgeLeft = sparki.edgeLeft();
    edgeRight = sparki.edgeRight();
    lineCenter = sparki.lineCenter();

    if(edgeLeft < threshold){
      foundLWall = true;
    }
    if(edgeLeft < threshold && lineCenter < threshold){
      foundLWall = false;
      foundDeadEnd = true;
    }
  }*/

  void wallFind(){
    switch(wallFindType){
    case 1: //Sparki might just be off track a little, search around 10 degrees
      while(foundLWall == false && turnCount < 5){ //as long as we haven't found a wall or turned 10 degrees yet
        sparki.moveRight(1);
        turnCount ++;
        readSensors();
      }
      if(turnCount >= 5){
        sparki.moveLeft(5);//turn back to original position
      }
      else{ //otherwise Sparki found a wall
        wallFindType = 0;
        turnCount = 0;
        return;
      }
      turnCount = 0;
      while(foundLWall == false && turnCount < 5){
        sparki.moveLeft(1);
        turnCount ++;
        readSensors();
      }
      if(turnCount >= 5){
        sparki.moveRight(5);//turn back to original position
        wallFindType = 2;//move on to next wall finding type
      }
      else{//otherwise Sparki found a wall
        sparki.println(turnCount);
        wallFindType = 0;
        turnCount = 0;
        return;
      }
      turnCount = 0;
      break;
    case 2://we didn't just lose the wall, there was a turn, check for 90 degree turn
      sparki.moveForward(7);
      sparki.moveLeft(90);
      sparki.moveStop();
      wallFindType = 0;
      break;
    default:
      break;
    }
  }

void readSensors()
{
  foundLWall = false;
  foundDeadEnd = false;
  edgeLeft = sparki.edgeLeft();
  edgeRight = sparki.edgeRight();
  lineCenter = sparki.lineCenter();
 
  if( edgeLeft < threshold )
  {
    foundLWall = true;
  }
  if( edgeLeft < threshold && lineCenter < threshold )
  {
    foundLWall = false;
    foundDeadEnd = true;
  }
}

void calibrateSparki()
{
  rightWall = false; //variable so we know if Sparki found the right wall
 
  if( foundLeftWall == false && calibrated == false ) //if Sparki hasn't found a left wall and hasn't been calibrated yet
  {
    sparki.moveLeft(1); //turn Sparki to the left a tiny bit
 
    if ( edgeLeft < threshold ) // if there is a line below left edge sensor
    {
      foundLeftWall = true; //Sparki found the left wall
    }
  }
 
  if( foundLeftWall == true && calibrated == false ) //if Sparki found a wall but isn't calibrated yet
  {
    if( rightWall == false )
    {
      sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 15); //move forward while rotating to the right a little
      sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 55); //move forward while rotating to the right a little
     }
 
    if( edgeLeft < threshold && edgeRight < threshold ) //if there is a wall beneath both sensors we're at -30 degrees from the wall
    { //this is also called a "known good" position because we know, no matter where Sparki started, where it is now in relation to the wall
      rightWall = true;
      //turn 28 degrees clockwise and scoot back close to the beginning
      sparki.moveForward();
      delay(1000); //this variable got changed a little
      sparki.moveRight(24); //this variable got changed a little
      sparki.moveBackward();
      delay(1000);
      sparki.motorStop(MOTOR_LEFT);
      sparki.motorStop(MOTOR_RIGHT);
      calibrated = true; //set calibrate flag to true so we exit calibrated code
    }
  }
}
// END OF MAZE SOLVE
////////////////////////////////////





//////////////////////
//    MAIN LOOP     //
//////////////////////
void loop() {
  
  //Scan for IR Receiver
  int code = sparki.readIR();
   // if there is a valid remote button press
  if(code != -1){
    sparki.moveStop(); // stop the motor
    sparki.RGB(RGB_OFF); // clear the RGB
//    program = false; // turn off the starter program
    sparki.clearLCD();
    sparki.print("IR code: ");
    sparki.println(code);
  } 
    
    
    
    sparki.updateLCD();
    
  switch(code){

    /// read sensors
    case 15: printIRcode(); break;
    case 28: accelerometer(); break;
    case 16: magnet(); break;
    case 18: readDistance(); break;

    case 33: printLight(); break;

    /// LCD
    case 69: bounceBall(); break;
    case 20: makeSmiles(); break;
    case 13: drawSnow(); break; 
    
    /// Navigation
    case 12: wallAvoid(); break;
    case 68: edgeAvoid(); break;
    case 67: lineFollow(); break;

    
    case 72: followLight(); break;
    case 64:  hillClimb(); break;
    case 82:  mazeSolve(); break;
    
    // music
    case 71: melody(); break;
    case 66:  theremin(); break;    

    // make circle of given radius
    case 23: doCircle(); break;
    



    // remote control
    
    /// stop and return
    case STOPCODE: // return here   
    case 79: // stop moves
             sparki.moveStop();
             sparki.gripperStop(); 
             sparki.servo(SERVO_CENTER); break;
             break;    
    
    case 130: sparki.moveForward(); break;
    case 131: sparki.moveBackward(); break;
    case 25: sparki.moveRight(); break;
    case 29: sparki.moveLeft(); break;
    
    // Gripper Buttons
    case 74:  sparki.gripperOpen(); 
              delay(1000);
              sparki.gripperStop(); 
              break;
    case 76:  sparki.gripperClose(); 
              delay(1000);
              sparki.gripperStop(); 
              break;


    // Servo
    case 17: sparki.servo(SERVO_LEFT); break;
    case 83: sparki.servo(SERVO_RIGHT); break;              

  }  
}
