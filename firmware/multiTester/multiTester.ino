/*
 * IDers Multitester
 * By: Glenn Lopez
 */

//libraries
#include <LiquidCrystal.h>
#include <ps2dev.h>

//inputs
const int buttonA = 10;
const int buttonB = 11;
const int buttonC = 12;
	
	//input state storage
	int buttonStateA = 0;
	int buttonStateB = 0;
	int buttonStateC = 0;

//outputs
LiquidCrystal lcd(8, 9, 5, 4, 6, 7); 
PS2dev keyboard(3,2); 
int enabled = 0;
unsigned char c;


//PS2 Keybaord Aknowledge
void ack(){while(keyboard.write(0xFA));}

//keyboard command
int keyboardcommand(int command)
{
  	unsigned char val;
  	switch (command)
  	{
  	case 0xFF:
    ack();
    while(keyboard.write(0xAA)!=0);		 break;

  	case 0xFE:
    ack();									           break;

  	case 0xF6:
    ack();									           break;

  	case 0xF5:
    enabled = 0;
    ack();									           break;

  	case 0xF4:
    enabled = 1;
    ack();									           break;

  	case 0xF3:
    ack();
    keyboard.read(&val);
    ack();									           break;

  	case 0xF2:
    ack();
    keyboard.write(0xAB);
    keyboard.write(0x83);					     break;

  	case 0xF0:
    ack();
    keyboard.read(&val); 
    ack();									           break;

  	case 0xEE:
    keyboard.write(0xEE);					     break;

  	case 0xED:
    ack();
    keyboard.read(&val);
    ack();									           break;
  }
}

void setup()
{
	//inputs
	pinMode(buttonA, INPUT);		
	pinMode(buttonB, INPUT);
	pinMode(buttonC, INPUT);

	//outputs
	while(keyboard.write(0xAA)!=0);
  delay(100);
  lcd.begin(16, 2);
}

void loop(){
  //read config peripheral analog first!

	//read the button states second!
	buttonStateA = digitalRead(buttonA);
	buttonStateB = digitalRead(buttonB);
	buttonStateC = digitalRead(buttonC);




/*
unsigned char c;
//if host device wants to send a command:
if( (digitalRead(3)==LOW) || (digitalRead(2) == LOW)) {
while(keyboard.read(&c)) ;
keyboardcommand(c);
}
*/




  //testLCDtop();
  //testLCDbottom();
  testKeyboard();
}




/**       TEMP. TEST FUNCTIONS        **/
//tests keyboard command
void testKeyboard(){
  if (buttonStateA == HIGH){
    keyboard.write(0x1E);
    delay(1500);
  }
}

//tests lcd output
void testLCDtop(){
  lcd.setCursor(0, 0);
  lcd.print("MLB Test");
}

void testLCDbottom(){
  lcd.setCursor(0, 1);
  delay(600);
  lcd.print("Select to Start");
}