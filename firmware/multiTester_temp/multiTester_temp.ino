
#include <ps2dev.h>

//inputs
const int buttonA = 10;
const int buttonB = 11;
const int buttonC = 12;
  
  //input state storage
  int buttonStateA = 0;
  int buttonStateB = 0;
  int buttonStateC = 0;

PS2dev keyboard(3,2); // PS2dev object (2:data, 3:clock)
int enabled = 0; // pseudo variable for state of "keyboard"

void ack() {
  //acknowledge commands
  while(keyboard.write(0xFA));
}

int keyboardcommand(int command) {
  unsigned char val;
  switch (command) {
  case 0xFF: //reset
    ack();
    //the while loop lets us wait for the host to be ready
    while(keyboard.write(0xAA)!=0);
    break;
  case 0xFE: //resend
    ack();
    break;
  case 0xF6: //set defaults
    //enter stream mode
    ack();
    break;
  case 0xF5: //disable data reporting
    //FM
    enabled = 0;
    ack();
    break;
  case 0xF4: //enable data reporting
    //FM
    enabled = 1;
    ack();
    break;
  case 0xF3: //set typematic rate
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  case 0xF2: //get device id
    ack();
    keyboard.write(0xAB);
    keyboard.write(0x83);
    break;
  case 0xF0: //set scan code set
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  case 0xEE: //echo
    //ack();
    keyboard.write(0xEE);
    break;
  case 0xED: //set/reset LEDs
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  }
}

void setup() {
  //inputs
  pinMode(buttonA, INPUT);    
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);

  // send the keyboard start up
  while(keyboard.write(0xAA)!=0);
  delay(10);
}

void loop() {
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
  else{ //send keypresses accordingly using scancodes
  // secancodes: http://www.computer-engineering.org/ps2keyboard/scancodes2.html
 */ 
 
if(buttonStateA == HIGH){
  keyboard.write(0x1E); // \
  keyboard.write(0xF0); //  |- send 'a'
  keyboard.write(0x1E); // /
  delay (1000); // wait 1 second
  }
if(buttonStateA == LOW){
  keyboard.write(0xF0); //  |- send 'a'
  keyboard.write(0x1E); // /
  delay (1000); // wait 1 second
}
}


