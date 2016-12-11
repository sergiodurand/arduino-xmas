/*
   The purpose of this code is only to check if all the components
   are working accordingly.
   
   It will just light some LEDs based on the 'data' variable.
   Note that 'data' was initialized using binary notation for a better
   view of which LED will be on or off. It could be initialized using
   hexdecimal or decimal notation as well.
*/

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  unsigned long int data = 0b11001100101010100011001101010101; // 0xCCAA3355 or 3433706325
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data);       // shiftOut works with 8 bits.
  shiftOut(dataPin, clockPin, LSBFIRST, data >> 8);  // we need to shift data
  shiftOut(dataPin, clockPin, LSBFIRST, data >> 16); // to send all the 32 bits to
  shiftOut(dataPin, clockPin, LSBFIRST, data >> 24); // the 4 x shift register IC (74hc595)
  digitalWrite(latchPin, HIGH);
  delay(1500);
}
