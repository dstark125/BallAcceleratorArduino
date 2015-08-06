
#include <plib.h>
#include <pins.h>
#include <variables.h>

void setup() {                
  pinMode(PIN_DETECTOR_OUT_1_1, INPUT);  //Set up pins to outputs or inputs
  pinMode(PIN_DETECTOR_OUT_1_2, INPUT);
  pinMode(PIN_DETECTOR_OUT_1_3, INPUT);
  pinMode(PIN_DETECTOR_OUT_1_4, INPUT);
  pinMode(PIN_DETECTOR_OUT_1_5, INPUT);
  pinMode(PIN_DETECTOR_OUT_2_1, INPUT);  //Set up pins to outputs or inputs
  pinMode(PIN_DETECTOR_OUT_2_2, INPUT);
  pinMode(PIN_DETECTOR_OUT_2_3, INPUT);
  pinMode(PIN_DETECTOR_OUT_2_4, INPUT);
  pinMode(PIN_DETECTOR_OUT_2_5, INPUT);
  
  pinMode(PIN_DETECTOR_VIN_1_1, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_1_2, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_1_3, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_1_4, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_1_5, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_2_1, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_2_2, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_2_3, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_2_4, OUTPUT);
  pinMode(PIN_DETECTOR_VIN_2_5, OUTPUT);
    
  pinMode(PIN_DETECTOR_STATUS_1_1, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_1_2, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_1_3, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_1_4, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_1_5, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_2_1, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_2_2, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_2_3, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_2_4, OUTPUT);
  pinMode(PIN_DETECTOR_STATUS_2_5, OUTPUT);
  
  pinMode(PIN_MOSFET_GATE_1, OUTPUT);
  pinMode(PIN_MOSFET_GATE_2, OUTPUT);
  pinMode(PIN_MOSFET_GATE_3, OUTPUT);
  pinMode(PIN_MOSFET_GATE_4, OUTPUT);
  
  pinMode(PIN_MAGNET_STATUS_1, OUTPUT);
  pinMode(PIN_MAGNET_STATUS_2, OUTPUT);
  pinMode(PIN_MAGNET_STATUS_3, OUTPUT);
  pinMode(PIN_MAGNET_STATUS_4, OUTPUT);


  /*
  This code example enables the Timer3 interrupts, loads the Timer3 period
  register, and starts the timer.
  When a Timer3 period match interrupt occurs, the interrupt service routine must clear
  the Timer3 interrupt status flag in software.
  */
  T3CON = 0x0; // Stop the timer and clear the control register,
  // prescaler at 1:1,internal clock source
  TMR3 = 0x0; // Clear the timer register
  //PR3 = 0x1F40; // Load the period register to 8,000 decimal - 80mhz / 8,000 = 10khz - 10 detectors
  //PR3 = 0x0FA0; // Load the period register to 4,000 decimal - 80mhz / 4,000 = 20khz - 10 detectors
  //PR3 = 0x0BB8; // Load the period register to 3,000 decimal - 80mhz / 3,000 = 26khz - 10 detectors
  //PR3 = 0x3E80; // Load the period register to 16,000 decimal - 80mhz / 16,000 = 5khz - 10 detectors
  PR3 = 0x29AA; // Load the period register to 10,066 decimal - 80mhz / 10,066 = 7.5khz - 10 detectors
  //PR3 = 0x4E20; // Load the period register to 20,000 decimal - 80mhz / 20,000 = 4khz - 2 detectors
  IPC3SET = 0x0000000C; // Set priority level = 3
  IPC3SET = 0x00000001; // Set subpriority level = 1
  // Can be done in a single operation by assigning PC2SET = 0x0000000D
  IFS0CLR = 0x00001000; // Clear the timer interrupt status flag
  IEC0SET = 0x00001000; // Enable timer interrupts
  T3CONSET = 0x8000; // Start the timer
  
  //  Another way to set up the timer, not interupts though still need to figure it out
  //  CloseTimer3(); //Close the timer to reset it
  //  OpenTimer3(T3_ON | T3_PS_1_1, 40000); //Open the timer at the 80Mhz/40000 frequency, 2000khz (and default multiplier)

  //set up timer2 on pic32
  CloseTimer2(); //Close the timer to reset it
  OpenTimer2(T2_ON | T2_PS_1_1, 2105); //Open the timer at the 80Mhz/2105 frequency (and default multiplier)

  //Set up pwm pin 3 on pic32
  CloseOC1(); //Close the PWM pin
  OpenOC1(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); //Open the PWM pin with timer 2 as the source and 100% duty cycle
  SetDCOC1PWM(PR2 / 2); //Set the duty cycle of PWM pin to half of the period
  
  //Set up pwm pin 5 on pic32  
  CloseOC2(); //Close the PWM pin
  OpenOC2(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); //Open the PWM pin with timer 2 as the source and 100% duty cycle
  SetDCOC2PWM(PR2 / 2); //Set the duty cycle of PWM pin to half of the period
  
    //Set up pwm pin 6 on pic32  
  CloseOC3(); //Close the PWM pin
  OpenOC3(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); //Open the PWM pin with timer 2 as the source and 100% duty cycle
  SetDCOC3PWM(PR2 / 2); //Set the duty cycle of PWM pin to half of the period
  
    //Set up pwm pin 9 on pic32  
  CloseOC4(); //Close the PWM pin
  OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); //Open the PWM pin with timer 2 as the source and 100% duty cycle
  SetDCOC4PWM(PR2 / 2); //Set the duty cycle of PWM pin to half of the period
  
    //Set up pwm pin 10 on pic32  
  CloseOC5(); //Close the PWM pin
  OpenOC5(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); //Open the PWM pin with timer 2 as the source and 100% duty cycle
  SetDCOC5PWM(PR2 / 2); //Set the duty cycle of PWM pin to half of the period
  
  digitalWrite(PIN_MOSFET_GATE_1, LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MAGNET_STATUS_1, LOW);
  digitalWrite(PIN_MOSFET_GATE_2, LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MAGNET_STATUS_2, LOW);
  digitalWrite(PIN_MOSFET_GATE_3, LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MAGNET_STATUS_3, LOW);
  digitalWrite(PIN_MOSFET_GATE_4, LOW);  //Initialize pins that need to be initialized
  digitalWrite(PIN_MAGNET_STATUS_4, LOW);
 
  digitalWrite(PIN_DETECTOR_STATUS_1_1, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_1_2, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_1_3, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_1_4, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_1_5, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_2_1, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_2_2, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_2_3, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_2_4, HIGH);  //Initialize pins that need to be initialized
  digitalWrite(PIN_DETECTOR_STATUS_2_5, HIGH);  //Initialize pins that need to be initialized   
    
   
  Serial.begin(9600);  
  delay(500);
  Serial.println("Starting.\nInitializing delay tables.");
  
  //Hash key is h() = (speed - 40)/3
  //This explains the math you will see in the for loop
  //table [hashkey][0] is the delay time
  //table [hashkey][1] is the exit speed
  //table [hashkey][2] is the direction
  for (i = 0; i < 125; i++){
    for (int j = 0; j < 4; j++){
      delay_table [j][i][0] = ((i * 3) + 40) * 1;
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
}




void loop() {
  //Check for entry into the first side
  if (checkBreak(PIN_DETECTOR_OUT_1_1)){  //Check for the first detector in the main loop.  After that we jump into this if statement state and handle all other detectors and the magnet
    timerInit = millis();  //Get the time stamp for the first detector break
    digitalWrite(PIN_MAGNET_STATUS_1, HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE_1, HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS_1_1, LOW);    //Show that the beam has been broken
    
    while (!checkBreak(PIN_DETECTOR_OUT_1_2) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //Hash key is h() = (speed - 40)/3
    //This explains the math you will see in the for loop
    //table [hashkey][0] is the delay time
    //table [hashkey][1] is the exit speed
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[0][hashkey][0]; //Based on the entry speed, set the time to reset 
    digitalWrite(PIN_DETECTOR_STATUS_1_2, LOW);    //Show that the beam has been broken
    printEntry(1);   
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE_1, LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MAGNET_STATUS_1, LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 1 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT_1_3) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_MAGNET_STATUS_2, HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE_2, HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS_1_3, LOW);    //Show that the beam has been broken
    adjustDelay(0);
    delay_table[0][hashkey][1] = exitSpeed;  
    printExit(1);
    
    //********************************************************************************************************************
    
    while (!checkBreak(PIN_DETECTOR_OUT_1_4) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[1] [hashkey][0]; //Based on the entry speed, set the time to reset 
    digitalWrite(PIN_DETECTOR_STATUS_1_4, LOW);    //Show that the beam has been broken
    printEntry(2);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE_2, LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MAGNET_STATUS_2, LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 2 Off\n");
    
    /*while (hold_table[0][4][1]){
      if (hold_table[0][4][0] < micros()){
        hold_table[0][4][1] = 0;
      }
    }*/
    
    //while (hold_table[0][4][0] < micros() && !checkBreak(PIN_DETECTOR_OUT_1_5) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    while (!checkBreak(PIN_DETECTOR_OUT_1_5) && (millis() - timeToReset) < 2000){
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_DETECTOR_STATUS_1_5, LOW);    //Show that the beam has been broken
    adjustDelay(1);
    delay_table[1][hashkey][1] = exitSpeed;    
    printExit(2);
    Serial.println("-----------------------------------------\n");  //Nice formatting
       
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_1_1, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_1_2, HIGH);  //Reset status LEDs that we are not going to checking
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_1_3, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_1_4, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_1_5, HIGH);
 
    if (exitSpeed < max1){
      max1 = exitSpeed;
      Serial.print("***************************************\nNew max speed for side 1 found! : ");  //Display info
      Serial.print(max1);
      Serial.print(" milliseconds.\nIn feet/second: ");
      Serial.println(1000 / (max1 * 1.6)); //Gives us feet/second for the 7.5 inch section
      Serial.println("***************************************\n");  //Nice formatting  
    }  
        
  }      

//********************************************************************************************************************  
//********************************************************************************************************************  
//Checking other side
//********************************************************************************************************************
//********************************************************************************************************************  
  
//  if (hold_table[1][0][1]){
//    if (hold_table[1][0][0] < micros()){
//      hold_table[1][0][1] = 0;
//      //Serial.println("Hold table is less than micros()");
//    }
//  }
  
  
  //Serial.println(hold_table[1][0][1]);
  //hold_table[1][0][1] = 0;
  //Check for entry into the second side  
  //if (!hold_table[1][0][1] && checkBreak(PIN_DETECTOR_OUT_2_1)){  //Check for the first detector in the main loop.  After that we jump into this if statement state and handle all other detectors and the magnet
  //if (hold_table[1][0][0] < micros() && checkBreak(PIN_DETECTOR_OUT_2_1)){  //Check for the first detector in the main loop.  After that we jump into this if statement state and handle all other detectors and the magnet
  if (checkBreak(PIN_DETECTOR_OUT_2_1)){ 
    timerInit = millis();  //Get the time stamp for the first detector break
    digitalWrite(PIN_MAGNET_STATUS_3, HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE_3, HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS_2_1, LOW);    //Show that the beam has been broken
    
    while (!checkBreak(PIN_DETECTOR_OUT_2_2) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[2] [hashkey][0]; //Based on the entry speed, set the time to reset
    digitalWrite(PIN_DETECTOR_STATUS_2_2, LOW);    //Show that the beam has been broken
    printEntry(3);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE_3, LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MAGNET_STATUS_3, LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 3 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT_2_3) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_MAGNET_STATUS_4, HIGH); //Set the electromagnet to "on"
    digitalWrite(PIN_MOSFET_GATE_4, HIGH);        //Set the electromagnet status led on
    digitalWrite(PIN_DETECTOR_STATUS_2_3, LOW);    //Show that the beam has been broken
    adjustDelay(2);
    delay_table[2][hashkey][1] = exitSpeed;
    printExit(3);
    
    //********************************************************************************************************************
    
    while (!checkBreak(PIN_DETECTOR_OUT_2_4) && (millis() - timerInit) < 1500){  //Wait for the next beam break or time out at 1.5 seconds
    }
    
    timerDif = millis();  
    entrySpeed = timerDif - timerInit;  //Get the difference in time between the first beam break and second beam break
    //hashkey = (entrySpeed - 40)/3;
    hashkey = constrain((entrySpeed - 40)/3, 0, 124);
    timeToReset = timerDif + delay_table[3][hashkey][0]; //Based on the entry speed, set the time to reset
    digitalWrite(PIN_DETECTOR_STATUS_2_4, LOW);    //Show that the beam has been broken
    printEntry(4);
    
    while (timeToReset > millis()){ //Do nothing while we wait for the reset time
    } 
    
    digitalWrite(PIN_MOSFET_GATE_4, LOW);        //Shut off the mosfet to the electromagnet 
    digitalWrite(PIN_MAGNET_STATUS_4, LOW); //Turn off the electromagnet status LED
    Serial.print("Electromagnet 4 Off\n");
    
    while (!checkBreak(PIN_DETECTOR_OUT_2_5) && (millis() - timeToReset) < 2000){  //Wait for the next beam break or time out at 2 seconds after it was supposed to reset        
    }
    
    timerInit = millis();
    exitSpeed = timerInit - timerDif;
    digitalWrite(PIN_DETECTOR_STATUS_2_5, LOW);    //Show that the beam has been broken
    adjustDelay(3); 
    delay_table[3][hashkey][1] = exitSpeed;    
    printExit(4);
    Serial.println("-----------------------------------------\n");  //Nice formatting
    
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_2_1, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_2_2, HIGH);  //Reset status LEDs that we are not going to checking
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_2_3, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_2_4, HIGH);
    delay(50);
    digitalWrite(PIN_DETECTOR_STATUS_2_5, HIGH); 
  
    if (exitSpeed < max2){
      max2 = exitSpeed;
      Serial.print("***************************************\nNew max speed for side 2 found! : ");  //Display info
      Serial.print(max2);
      Serial.print(" milliseconds.\nIn feet/second: ");
      Serial.println(1000 / (max2 * 1.6)); //Gives us feet/second for the 7.5 inch section
      Serial.println("***************************************\n");  //Nice formatting  
    }  
  }    
}


//This function checks if a beam is broken based on which pin is passed in.  It returns a 1 if there is a break.
int checkBreak(int pin){
  if (digitalRead (pin)){ //If the signal drops out
    if (digitalRead (pin)){
      //Serial.print("! Break detected on pin: "); //Print
      Serial.println(pin);
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
  Serial.println(delay_table[location - 1][hashkey][0]);  
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


//The false break blip up above 1v happens right after we bit bang it in the ISR right?
//And last for ~3 microseconds? About? idk

extern "C"{
  void __ISR(_TIMER_3_VECTOR, ipl3) Timer3Handler(void){
    count++;
    switch (count){
      case 1:
          digitalWrite(PIN_DETECTOR_VIN_1_1, LOW);
          digitalWrite(PIN_DETECTOR_VIN_1_1, HIGH);
          //delayMicroseconds(3);
      break;
      case 2:
          digitalWrite(PIN_DETECTOR_VIN_1_2, LOW);
          digitalWrite(PIN_DETECTOR_VIN_1_2, HIGH);
      break;
      case 3:
          digitalWrite(PIN_DETECTOR_VIN_1_3, LOW);
          digitalWrite(PIN_DETECTOR_VIN_1_3, HIGH);
      break;
      case 4:
          digitalWrite(PIN_DETECTOR_VIN_1_4, LOW);
          digitalWrite(PIN_DETECTOR_VIN_1_4, HIGH);
      break;
      case 5:
          digitalWrite(PIN_DETECTOR_VIN_1_5, LOW);
          digitalWrite(PIN_DETECTOR_VIN_1_5, HIGH);
          delayMicroseconds(30);
          //hold_table[0][4][1] = 1;
          //hold_table[0][4][0] = micros() + 500;
      break;
      case 6:
          digitalWrite(PIN_DETECTOR_VIN_2_1, LOW);
          digitalWrite(PIN_DETECTOR_VIN_2_1, HIGH);
          delayMicroseconds(30);
          //hold_table[1][0][1] = 1;
          //hold_table[1][0][0] = micros() + 500;
          //hold_2_1 = micros() + 200;
          //Serial.println(micros());
      break;
      case 7:
          digitalWrite(PIN_DETECTOR_VIN_2_2, LOW);
          digitalWrite(PIN_DETECTOR_VIN_2_2, HIGH);
      break;
      case 8:
          digitalWrite(PIN_DETECTOR_VIN_2_3, LOW);
          digitalWrite(PIN_DETECTOR_VIN_2_3, HIGH);
      break;
      case 9:
          digitalWrite(PIN_DETECTOR_VIN_2_4, LOW);
          digitalWrite(PIN_DETECTOR_VIN_2_4, HIGH);
      break;
      case 10:
        count = 0;
          digitalWrite(PIN_DETECTOR_VIN_2_5, LOW);
          digitalWrite(PIN_DETECTOR_VIN_2_5, HIGH);
      break;
    }
    //Serial.println(count);
    IFS0CLR  = 0x00001000;  // Clear Timer interrupt status flag
  }
}



/*

*/




