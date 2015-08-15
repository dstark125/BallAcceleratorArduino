
#define PIN_SCE   7 // SCE - Chip select, pin 3 on LCD.
#define PIN_RESET 6 // RST - Reset, pin 4 on LCD.
#define PIN_DC    5 // DC - Data/Command, pin 5 on LCD.
#define PIN_SDIN  4 // DN(MOSI) - Serial data, pin 6 on LCD.
#define PIN_SCLK  3 // SCLK - Serial clock, pin 7 on LCD.

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48

int PIN_MOSFET_GATE[4] = {32,33,34,35};
int PIN_DETECTOR_OUT[10]    = {24,26,29,31,27,25,23,28,30,22};
int PIN_DETECTOR_STATUS[10] = {37,39,41,43,45,36,38,40,42,44};
int PIN_MOSFET_STATUS[4] = {46,47,48,49};

unsigned long timeToReset = 0, timerInit = 0, timerDif = 0;  //Global variable declaration
int count = 0, i = 0, j = 0, hashkey = 0, entrySpeed = 0, exitSpeed = 0, max1 = 5000, max2 = 5000;

int delay_table[4][125][3];
unsigned long hold_table[2][5][2];
int hold_2_1 = 0;

static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};


void setup() {                
  pinMode(PIN_DETECTOR_OUT[0], INPUT);  //Set up pins to outputs or inputs
  pinMode(PIN_DETECTOR_OUT[1], INPUT);
  pinMode(PIN_DETECTOR_OUT[2], INPUT);
  pinMode(PIN_DETECTOR_OUT[3], INPUT);
  pinMode(PIN_DETECTOR_OUT[4], INPUT);
  pinMode(PIN_DETECTOR_OUT[5], INPUT);  //Set up pins to outputs or inputs
  pinMode(PIN_DETECTOR_OUT[6], INPUT);
  pinMode(PIN_DETECTOR_OUT[7], INPUT); 
  pinMode(PIN_DETECTOR_OUT[8], INPUT); 
  pinMode(PIN_DETECTOR_OUT[9], INPUT);
      
  pinMode(PIN_DETECTOR_STATUS[0], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[1], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[2], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[3], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[4], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[5], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[6], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[7], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[8], OUTPUT);
  pinMode(PIN_DETECTOR_STATUS[9], OUTPUT);
  
  pinMode(PIN_MOSFET_GATE[0], OUTPUT);
  pinMode(PIN_MOSFET_GATE[1], OUTPUT);
  pinMode(PIN_MOSFET_GATE[2], OUTPUT);
  pinMode(PIN_MOSFET_GATE[3], OUTPUT);
  
  pinMode(PIN_MOSFET_STATUS[0], OUTPUT);
  pinMode(PIN_MOSFET_STATUS[1], OUTPUT);
  pinMode(PIN_MOSFET_STATUS[2], OUTPUT);
  pinMode(PIN_MOSFET_STATUS[3], OUTPUT);
  
  digitalWrite(PIN_MOSFET_GATE[0], LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MOSFET_STATUS[0], LOW);
  digitalWrite(PIN_MOSFET_GATE[1], LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MOSFET_STATUS[1], LOW);
  digitalWrite(PIN_MOSFET_GATE[2], LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MOSFET_STATUS[2], LOW);
  digitalWrite(PIN_MOSFET_GATE[3], LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MOSFET_STATUS[3], LOW);
 
  digitalWrite(PIN_DETECTOR_STATUS[0], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[1], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[2], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[3], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[4], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[5], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[6], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[7], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[8], HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS[9], HIGH);  //Initialize pins that need to be initialized   
    
   
  Serial.begin(9600);  
  delay(500);
  Serial.println("Starting.\nInitializing delay tables.");
  
  //Hash key is h() = (speed - 40)/3
  //This explains the math you will see in the for loop
  //table [hashkey][0] is the delay time
  //table [hashkey][1] is the exit speed
  //table [hashkey][2] is the direction
   for (i = 0; i < 125; i++){
      for  (j = 0; j < 4; j++){
         if (i < 25){
            switch (j){
              case 0:
                 delay_table [0][i][0] = ((i * 3) + 40) * .92;
                 break;
              case 1:
                 delay_table [1][i][0] = ((i * 3) + 40) * .96;
                 break;
              case 2:
                 delay_table [2][i][0] = ((i * 3) + 40) * 1.05;
                 break;
              case 3:
                 delay_table [3][i][0] = ((i * 3) + 40) * .92;
                 break;
            }
         }
         else if (i < 50){
            switch (j){
              case 0:
                 delay_table [0][i][0] = ((i * 3) + 40) * .94;
                 break;
              case 1:
                 delay_table [1][i][0] = ((i * 3) + 40) * .98;
                 break;
              case 2:
                 delay_table [2][i][0] = ((i * 3) + 40) * 1.07;
                 break;
              case 3:
                 delay_table [3][i][0] = ((i * 3) + 40) * .94;
                 break;
            }
         }
         else if (i < 75){
            switch (j){
              case 0:
                 delay_table [0][i][0] = ((i * 3) + 40) * .96;
                 break;
              case 1:
                 delay_table [1][i][0] = ((i * 3) + 40) * 1.0;
                 break;
              case 2:
                 delay_table [2][i][0] = ((i * 3) + 40) * 1.09;
                 break;
              case 3:
                 delay_table [3][i][0] = ((i * 3) + 40) * .96;
                 break;
            }
         }
         else if (i < 100){
            switch (j){
              case 0:
                 delay_table [0][i][0] = ((i * 3) + 40) * .98;
                 break;
              case 1:
                 delay_table [1][i][0] = ((i * 3) + 40) * 1.02;
                 break;
              case 2:
                 delay_table [2][i][0] = ((i * 3) + 40) * 1.11;
                 break;
              case 3:
                 delay_table [3][i][0] = ((i * 3) + 40) * .98;
                 break;
            }
         }
         else{
            switch (j){
              case 0:
                 delay_table [0][i][0] = ((i * 3) + 40) * 1.0;
                 break;
              case 1:
                 delay_table [1][i][0] = ((i * 3) + 40) * 1.04;
                 break;
              case 2:
                 delay_table [2][i][0] = ((i * 3) + 40) * 1.13;
                 break;
              case 3:
                 delay_table [3][i][0] = ((i * 3) + 40) * 1.00;
                 break;
            }
         }
         delay_table [j][i][1] = 5000;
         delay_table [j][i][2] = 1;
      }
   }
  
  //(entrySpeed - 40)/3;
  
//  for (i = 0; i < 125; i++){
//      Serial.print("Index: ");
//      Serial.print(i);
//      Serial.print(" Delay: ");
//      Serial.print(delay_table[0][i][0]);
//      Serial.print(" Out Speed: ");
//      Serial.print(delay_table[0][i][1]);
//      Serial.print(" Init Direction: ");
//      Serial.print(delay_table[0][i][2]);
//      Serial.print("\n");
//  }
  
  
  delay(1000); //Wait for PWM pins to start and ISRs to enter and everything to even out before we loop
  Serial.println("Ready");

  LcdInitialise();
  LcdClear();
  LcdString("Hello World!");
  
}




void loop() {
  //Check for entry into the first side
  if (checkBreak(PIN_DETECTOR_OUT[0])){  //Check for the first detector in the main loop.  After that we jump into this if statement state and handle all other detectors and the magnet
    timerInit = millis();  //Get the time stamp for the first detector break
    digitalWrite(PIN_MOSFET_STATUS[0], HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE[0], HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS[0], LOW);    //Show that the beam has been broken
    
    while (!checkBreak(PIN_DETECTOR_OUT[1]) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //Hash key is h() = (speed - 40)/3
    //This explains the math you will see in the for loop
    //table [hashkey][0] is the delay time
    //table [hashkey][1] is the exit speed
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[0][hashkey][0]; //Based on the entry speed, set the time to reset 
    digitalWrite(PIN_DETECTOR_STATUS[1], LOW);    //Show that the beam has been broken
    printEntry(0);   
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE[0], LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MOSFET_STATUS[0], LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 0 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT[2]) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_MOSFET_STATUS[1], HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE[1], HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS[2], LOW);    //Show that the beam has been broken
    adjustDelay(0);
    delay_table[0][hashkey][1] = exitSpeed;  
    printExit(0);
    
    //********************************************************************************************************************
    
    while (!checkBreak(PIN_DETECTOR_OUT[3]) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[1] [hashkey][0]; //Based on the entry speed, set the time to reset 
    digitalWrite(PIN_DETECTOR_STATUS[3], LOW);    //Show that the beam has been broken
    printEntry(1);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE[1], LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MOSFET_STATUS[1], LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 1 Off\n");
    
    /*while (hold_table[0][4][1]){
      if (hold_table[0][4][0] < micros()){
        hold_table[0][4][1] = 0;
      }
    }*/
    
    //while (hold_table[0][4][0] < micros() && !checkBreak(PIN_DETECTOR_OUT[4]) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    while (!checkBreak(PIN_DETECTOR_OUT[4]) && (millis() - timeToReset) < 2000){
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_DETECTOR_STATUS[4], LOW);    //Show that the beam has been broken
    adjustDelay(1);
    delay_table[1][hashkey][1] = exitSpeed;    
    printExit(1);
    Serial.println("-----------------------------------------\n");  //Nice formatting
       
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[0], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[1], HIGH);  //Reset status LEDs that we are not going to checking
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[2], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[3], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[4], HIGH);
 
    if (exitSpeed < max1){
      max1 = exitSpeed;
      Serial.print("***************************************\nNew max speed for side 1 found! : ");  //Display info
      Serial.print(max1);
      Serial.print(" milliseconds.\nIn feet/second: ");
      Serial.println(1000 / (max1 * 1.6)); //Gives us feet/second for the 7.5 inch section
      Serial.println("***************************************\n");  //Nice formatting  
    }  
    detectFalseBreak();    
  }      

  //********************************************************************************************************************  
  //********************************************************************************************************************  
  //Checking other side
  //********************************************************************************************************************
  //********************************************************************************************************************  
      
  
 
  if (checkBreak(PIN_DETECTOR_OUT[5])){ 
    timerInit = millis();  //Get the time stamp for the first detector break
    digitalWrite(PIN_MOSFET_STATUS[2], HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE[2], HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS[5], LOW);    //Show that the beam has been broken
    
    while (!checkBreak(PIN_DETECTOR_OUT[6]) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[2] [hashkey][0]; //Based on the entry speed, set the time to reset
    digitalWrite(PIN_DETECTOR_STATUS[6], LOW);    //Show that the beam has been broken
    printEntry(2);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE[2], LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MOSFET_STATUS[2], LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 2 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT[7]) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_MOSFET_STATUS[3], HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE[3], HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS[7], LOW);    //Show that the beam has been broken
    adjustDelay(2);
    delay_table[2][hashkey][1] = exitSpeed;
    printExit(2);
    
    //********************************************************************************************************************
    
    while (!checkBreak(PIN_DETECTOR_OUT[8]) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[3][hashkey][0]; //Based on the entry speed, set the time to reset
    digitalWrite(PIN_DETECTOR_STATUS[8], LOW);    //Show that the beam has been broken
    printEntry(3);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE[3], LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MOSFET_STATUS[3], LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 3 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT[9]) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_DETECTOR_STATUS[9], LOW);    //Show that the beam has been broken
    adjustDelay(3); 
    delay_table[3][hashkey][1] = exitSpeed;    
    printExit(3);
    Serial.println("-----------------------------------------\n");  //Nice formatting
    
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[5], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[6], HIGH);  //Reset status LEDs that we are not going to checking
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[7], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[8], HIGH);
    delay(5);
    digitalWrite(PIN_DETECTOR_STATUS[9], HIGH); 
  
    if (exitSpeed < max2){
      max2 = exitSpeed;
      Serial.print("***************************************\nNew max speed for side 2 found! : ");  //Display info
      Serial.print(max2);
      Serial.print(" milliseconds.\nIn feet/second: ");
      Serial.println(1000 / (max2 * 1.6)); //Gives us feet/second for the 7.5 inch section
      Serial.println("***************************************\n");  //Nice formatting  
    }
    detectFalseBreak();
  }

}

//void accelerate(startPin){
  
//}


void detectFalseBreak(){
  int i = 0;
  for (i = 0; i < 10; i++){
    while (checkBreak(PIN_DETECTOR_OUT[i])){
      Serial.print("False break found on detector: ");  //Display info
      Serial.println(i);  //Display info
    } 
  }
}


//This function checks if a beam is broken based on which pin is passed in.  It returns a 1 if there is a break.
int checkBreak(int pin){
  if (digitalRead (pin)){ //If the signal drops out
    if (digitalRead (pin)){
      //Serial.print("! Break detected on pin: "); //Print
      //Serial.println(pin);
      return 1;
    }
  }
  return 0; 
} 


void printExit (int location){
  Serial.print("Exit speed for ");  //Display info
  Serial.print(location);
  Serial.print(" was: ");
  Serial.print(exitSpeed);
  Serial.print(" milliseconds.\nIn feet/second: ");
  Serial.println(1000 / (exitSpeed * 1.6)); //Gives us feet/second for the 7.5 inch section  
}


void printEntry (int location){  //We can print entryspeed, hashkey, and time to reset easily because they are global variables.
  Serial.print("Entry speed for ");  //Display info
  Serial.print(location);
  Serial.print(" was: ");
  Serial.print(entrySpeed);
  Serial.print(" milliseconds.\nIn feet/second: ");
  Serial.println(1000 / (entrySpeed * 4.8)); //Gives us feet/second for the 2.5 inch section
  Serial.print("Hashkey: "); 
  Serial.println(hashkey);
  Serial.print("Time to reset set to: "); 
  Serial.println(delay_table[location][hashkey][0]);  
}


void adjustDelay (int location){
  if (delay_table[location][hashkey][2]){ //If we are moving the delay closer to the electromagnet
    if ((exitSpeed - delay_table[location][hashkey][1]) < 0){ //Say the exit time was 230 milliseconds and the last exit time was 235 milliseconds, we are going faster and want to go even faster
      delay_table[location][hashkey][0]++;
      Serial.println("F - TM - D+");   
    }
    else if ((exitSpeed - delay_table[location][hashkey][1]) > 0){ //Say the exit time was 240 milliseconds and the last exit time was 235 milliseconds, we are going slower and want to reverse the direction
      delay_table[location][hashkey][0]--;
      delay_table[location][hashkey][2] = 0;
      Serial.println("S - TM - D- - SD");   
    }
  }
  else{  //We are moving the delay back towards the beam break
     if ((exitSpeed - delay_table[location][hashkey][1]) < 0){ //Say the exit time was 230 milliseconds and the last exit time was 235 milliseconds, we are going faster and want to go even faster
      delay_table[location][hashkey][0]--;
      Serial.println("F - TB - D-");   
    }
    else if ((exitSpeed - delay_table[location][hashkey][1]) > 0){ //Say the exit time was 240 milliseconds and the last exit time was 235 milliseconds, we are going slower and want to reverse the direction
      delay_table[location][hashkey][0]++;
      delay_table[location][hashkey][2] = 1;
      Serial.println("S - TB - D+ - SD");
    }
  }
}




void LcdCharacter(char character)
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
}

void LcdString(char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

/*

*/





