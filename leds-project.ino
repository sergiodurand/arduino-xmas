// https://create.arduino.cc/projecthub/user16726/breakoutbros-halloween-day-special-stranger-things-board-f760e1
// Picture of this project: arduino-leds.jpg
//      https://github.com/sergiodurand/arduino-xmas/blob/master/arduino-leds.jpg

int DELAY=1000;

typedef struct { // Create a structure to convert Binary of the PORTs for the corresponding Letter
  byte portd;
  byte portb;
} letter_data_t;


const letter_data_t letter[] = {
  {B00000100,B11111110}, //A
  {B00000100,B11111101}, //B
  {B00000100,B11111011}, //C
  {B00000100,B11110111}, //D
  {B00000100,B11101111}, //E
  {B00001000,B11111110}, //F
  {B00001000,B11111101}, //G
  {B00001000,B11111011}, //H
  {B00001000,B11110111}, //I
  {B00001000,B11101111}, //J
  {B00010000,B11111110}, //K
  {B00010000,B11111101}, //L
  {B00010000,B11111011}, //M
  {B00010000,B11110111}, //N
  {B00010000,B11101111}, //O
  {B00100000,B11111110}, //P
  {B00100000,B11111101}, //Q
  {B00100000,B11111011}, //R
  {B00100000,B11110111}, //S
  {B00100000,B11101111}, //T
  {B01000000,B11111110}, //U
  {B01000000,B11111101}, //V
  {B01000000,B11111011}, //W
  {B01000000,B11110111}, //X
  {B01000000,B11101111}, //Y
  {B10000000,B11111111}, //Z
  {B00000000,B00000000}  //26 = 0ff
};

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT); 
}

void loop() {
  char phrase[30]= "";

  // OFF
  PORTD = letter[26].portd; //Turn off the LEDs
  PORTB = letter[26].portb; //Turn off the LEDs
  delay(DELAY);
  
  all_leds();
  all_leds_r();
  
  strcpy(phrase,"ABCDE FGHIJ KLMNO PQRST UVWXY Z");

  if (strlen(phrase) != 0) {
    int i;
    for(i=0; i<strlen(phrase); i++) {
      if (phrase[i] == ' ') {
        // Space = OFF
        PORTD = letter[26].portd; //Turn off the LEDs
        PORTB = letter[26].portb; //Turn off the LEDs
      } else {
        PORTD = letter[phrase[i]-'A'].portd;
        PORTB = letter[phrase[i]-'A'].portb;
      }
      delay(DELAY);
    }
  }  
}

void all_leds() {
  int i;
  for (i=0; i<26; i++) {
    PORTD = letter[i].portd;
    PORTB = letter[i].portb;
    delay(100);
  }
  PORTD = letter[26].portd; //Turn off the LEDs
  PORTB = letter[26].portb; //Turn off the LEDs
}

void all_leds_r() {
  int i;
  for (i=25; i>=0; i--) {
    PORTD = letter[i].portd;
    PORTB = letter[i].portb;
    delay(100);
  }
  PORTD = letter[26].portd; //Turn off the LEDs
  PORTB = letter[26].portb; //Turn off the LEDs
}
