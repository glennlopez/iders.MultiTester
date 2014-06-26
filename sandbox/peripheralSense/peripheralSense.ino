#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 5, 4, 6, 7);

//global variables
int option = 0;

//setup routine
void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);
}

void loop(){
   //read analog signal
   int peripheralSenseA = analogRead(A0);

   //serial monitor read-out
   Serial.println(peripheralSenseA);
   delay(1000);


   /*
    * CABLE TEST ROUTINE - EDIT or ADD RANGE ONLY 
    * Note: peripheralSenseA must have 10* resolution
    * Minimum is 0 max is 1032 (5v - 0v bias signal)
    */
   
   //1v signal
    while(peripheralSenseA >=200 && peripheralSenseA <=210){
      option = 1;
      break;
   }

   //2v signal
    while(peripheralSenseA >=405 && peripheralSenseA <= 415){
      option = 2;
      break;
   }

   //3v signal
   while(peripheralSenseA >= 615 && peripheralSenseA <= 625){
      option = 3;
      break;
   }

   //4v signal
   while(peripheralSenseA >= 817 && peripheralSenseA <= 827){
      option = 4;
      break;
   }


   /*
    * CABLE TEST RESPONSE - DO NOT EDIT
    * choses which test function routine to excecute as per
    * cable test routine above 
    */
   
   switch(option){
      case 1:                          
         lcd.clear();
         funcOne();          
      break;

      case 2:
         lcd.clear();
         funcTwo(); 
      break;

      case 3:
        lcd.clear();
        funcThree();
      break;

      case 4:
        lcd.clear();
        funcFour();
      break;

      default:
         lcd.clear();
         lcd.setCursor(0, 0);
            lcd.print("Error:");

         lcd.setCursor(0, 1);
            lcd.print("Nothing plugged!");
  }
  //resets cable test response when break; occurs
  option = 0;
}




/*
 * TEST FUNCTION ROUTINE: ~ADD NEW FUNCTIONS BELOW~
 * instead of using a dipswitch I automated the test config routine by embeding a 
 * voltage divider inside the cables and having the uC read the bias 
 * voltage coming out of those cables.
 */

void funcOne(){
    lcd.setCursor(0, 0);
      lcd.print("function 1");

    lcd.setCursor(0, 1);
      lcd.print("vsense = 1v");
}

void funcTwo(){
    lcd.setCursor(0, 0);
      lcd.print("function 2");

    lcd.setCursor(0, 1);
      lcd.print("vsense = 2v");
}

void funcThree(){
    lcd.setCursor(0, 0);
      lcd.print("function 3");

    lcd.setCursor(0, 1);
      lcd.print("vsense = 3v");  
}

void funcFour(){
    lcd.setCursor(0, 0);
      lcd.print("function 4");

    lcd.setCursor(0, 1);
      lcd.print("vsense = 4v");  
}
