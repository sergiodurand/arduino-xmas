/*

  The purpose of this code is to light specific LED based on
  each letter from a string.

  The circuit has 26 LEDS which represent all the 26 letters from
  the latin alphabet.

  This is the "Array Version" source code. Each letter is already
  definied in the "alpha" array. It was used the binary representation
  to get a better view of which LED will be on. It could be initialized
  using hexdecimal or decimal notation as well.

  There are other two versions of this code:
  Alternative code 1: it uses only one 32 bit variable to represent a letter.
                      All the variations is done using bitwise right shift operator.
  Alternative code 2: it does not use any variable to represent the letters.
                      The value that represets the letter is passed directly
                      to the shiftOut function.
                      
  Any resemblance to the Strange Things is not purely coincidental.

*/

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

unsigned long int alpha[26] = {
	0b10000000000000000000000000000000,
	0b01000000000000000000000000000000,
	0b00100000000000000000000000000000,
	0b00010000000000000000000000000000,
	0b00001000000000000000000000000000,
	0b00000100000000000000000000000000,
	0b00000010000000000000000000000000,
	0b00000001000000000000000000000000,
	0b00000000100000000000000000000000,
	0b00000000010000000000000000000000,
	0b00000000001000000000000000000000,
	0b00000000000100000000000000000000,
	0b00000000000010000000000000000000,
	0b00000000000001000000000000000000,
	0b00000000000000100000000000000000,
	0b00000000000000010000000000000000,
	0b00000000000000001000000000000000,
	0b00000000000000000100000000000000,
	0b00000000000000000010000000000000,
	0b00000000000000000001000000000000,
	0b00000000000000000000100000000000,
	0b00000000000000000000010000000000,
	0b00000000000000000000001000000000,
	0b00000000000000000000000100000000,
	0b00000000000000000000000010000000,
	0b00000000000000000000000001000000
};

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
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 8);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 16);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 24);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
  for (i=25; i>=0; i--) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 8);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 16);
    shiftOut(dataPin, clockPin, LSBFIRST, alpha[i] >> 24);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}

void light_letter(int pos) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, alpha[pos]);
  shiftOut(dataPin, clockPin, LSBFIRST, alpha[pos] >> 8);
  shiftOut(dataPin, clockPin, LSBFIRST, alpha[pos] >> 16);
  shiftOut(dataPin, clockPin, LSBFIRST, alpha[pos] >> 24);
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
        light_letter(0);
	break;
      case 'B':
        light_letter(1);
	break;
      case 'C':
        light_letter(2);
	break;
      case 'D':
        light_letter(3);
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

