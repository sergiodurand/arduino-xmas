/*

  The purpose of this code is to light specific LED based on
  each letter from a string.

  The circuit has 26 LEDS which represent all the 26 letters from
  the latin alphabet.

  This is the "Shift Version" source code. It uses only one 32 bit
  variable to represent a letter. All the variations is done using
  bitwise right shift operator.

  There are another two versions of this code:
  Alternative code 1: it uses an array with 26 positions to represent each letter.
                      All the 26 positions is already definied and ready to use.
  Alternative code 2: it does not use any variable to represent the letters.
                      The value that represets the letter is passed directly
                      to the shiftOut function.
                      
  Any resemblance to the Strange Things is not purely coincidental.

*/

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

unsigned long int letter = 0b10000000000000000000000000000000;
unsigned char OFF = 0b00000000;
unsigned char ON  = 0b11111111;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Serial.begin(9600);
  //Serial.println("Hello Serial!");
}

void on() {
  int i;
  digitalWrite(latchPin, LOW);
  for (i=0; i<4; i++)
    shiftOut(dataPin, clockPin, LSBFIRST, ON);
  digitalWrite(latchPin, HIGH);
}

void off() {
  int i;
  digitalWrite(latchPin, LOW);
  for (i=0; i<4; i++)
    shiftOut(dataPin, clockPin, LSBFIRST, OFF);
  digitalWrite(latchPin, HIGH);
}

void begin() {
  int i;
  for (i=0; i<4; i++) {
    on();
    delay(200);
    off();
    delay(200);
  }
  for (i=0; i<26; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 8);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 16);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 24);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
  for (i=25; i>=0; i--) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 8);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 16);
    shiftOut(dataPin, clockPin, LSBFIRST, letter >> i >> 24);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}

void light_letter(unsigned long int letter) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, letter);
  shiftOut(dataPin, clockPin, LSBFIRST, letter >> 8);
  shiftOut(dataPin, clockPin, LSBFIRST, letter >> 16);
  shiftOut(dataPin, clockPin, LSBFIRST, letter >> 24);
  digitalWrite(latchPin, HIGH);
  delay(1000);  
}

void loop() {
  begin();
  char phrase[] = "AB CD";
  
  //int x = strlen(phrase);
  //Serial.print("strlen of phrase: ");
  //Serial.println(x);
  //Serial.println(phrase);
  //light_letter(x-1);

  int i;  
  for (i=0; i<strlen(phrase); i++) {
    switch (phrase[i]) {
      case 'A':
        light_letter(letter);
	break;
      case 'B':
        light_letter(letter >> 1);
	break;
      case 'C':
        light_letter(letter >> 2);
	break;
      case 'D':
        light_letter(letter >> 3);
	break;
      case ' ':
	off();
        delay(1000);
	break;
      default:
	off();
    }
  }
}

