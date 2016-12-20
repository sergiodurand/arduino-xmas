// WiFi module from:
// https://github.com/bportaluri/WiFiEsp

// WiFi control was based on example found at:
// https://github.com/bportaluri/WiFiEsp/tree/master/examples/WebClientRepeating

// LED control was based on example found at:
// https://create.arduino.cc/projecthub/user16726/breakoutbros-halloween-day-special-stranger-things-board-f760e1

// This program make use of pins:
//          Arduino pin 2 or A1 -> ESP-12 TX
//          Arduino pin 3 or A0 -> ESP-12 RX

#include "WiFiEsp.h"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(A1, A0); // RX, TX
#endif

char ssid[] = "***SSID***";      // your network SSID (name)
char pass[] = "***secret***";    // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//char server[] = "pyxmas.mybluemix.net";
char server[] = "stranger-christmas.mybluemix.net";
String phrase_to_led = "";

// Initialize the Ethernet client object
WiFiEspClient client;

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
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    while (true);
  }

  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
  }

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
  PORTD = letter[26].portd;
  PORTB = letter[26].portb;
  
  while (client.available()) {
    char c = client.read();
    if (c == '#') {
      while (client.available()) {
        c = client.read();
        Serial.println(c);
        if (c == '#') {
          ack();
          break;
        }
        phrase_to_led = phrase_to_led + c;
      }
    }
  }

  int i;
  for (i=0; i<phrase_to_led.length(); i++) {
    if (phrase_to_led.charAt(i) == ' ') {
      PORTD = letter[26].portd;
      PORTB = letter[26].portb;
    } else {
      PORTD = letter[26].portd;
      PORTB = letter[26].portb;
      delay(100);
      PORTD = letter[phrase_to_led.charAt(i)-'A'].portd;
      PORTB = letter[phrase_to_led.charAt(i)-'A'].portb;
    }      
    delay(700);
  }
  phrase_to_led = "";
  PORTD = letter[26].portd;
  PORTB = letter[26].portb;
  
  //delay(5000);
  all_leds();
  httpRequest();
}

void ack() {
  Serial.println("ACK OK");
    client.stop();
  if (client.connect(server, 80)) {
    client.println(F("GET /queue/poll/ HTTP/1.1"));
    client.println(F("Host: stranger-christmas.mybluemix.net"));
    client.println("Connection: close");
    client.println();
  }
}

void all_leds() {
  int i;
  for (i=0; i<26; i++) {
    PORTD = letter[i].portd;
    PORTB = letter[i].portb;
    delay(100);
  }
  PORTD = letter[26].portd;
  PORTB = letter[26].portb;
}

void httpRequest() {
  client.stop();
  if (client.connect(server, 80)) {
    //client.println(F("GET /getuino HTTP/1.1"));
    client.println(F("GET /queue/peek/ HTTP/1.1"));
    //client.println(F("Host: pyxmas.mybluemix.net"));
    client.println(F("Host: stranger-christmas.mybluemix.net"));
    client.println("Connection: close");
    client.println();
  }
}

