/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#include <Bounce2.h>



#define DEBOUNCE_PERIOD 10

// timer objects for animations:
typedef struct {
  uint8_t pin; // Teensy pin number
  int keycode; // Key code to send when above pin is closed
  Bounce bounce; // Using the Bounce timer library - this is a bounce object
} ButtonMap;


ButtonMap panel_buttons [] {
  { 2, KEY_F5,  Bounce() },
  { 3, KEY_F6,  Bounce() },
  { 4, KEY_F7,  Bounce() },
  { 5, KEY_F8,  Bounce() },
  { 6, KEY_F9,  Bounce() },
  { 7, KEY_F10, Bounce() },
  { 8, KEY_F11, Bounce() },
  { 9, KEY_F12, Bounce() }
};

int count = 0;



void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("start!");


// digitalWrite(   panel_buttons[0].pin ,HIGH);
//
  for (int input_count=0; input_count<8; input_count++){
  //  pinMode( panel_buttons[0].pin ,INPUT);
    pinMode( panel_buttons[0].pin, INPUT_PULLUP);
    panel_buttons[0].bounce.attach(panel_buttons[0].pin);
    panel_buttons[0].bounce.interval(DEBOUNCE_PERIOD);
  }

}

void loop() {

  panel_buttons[0].bounce.update(); // not scanning shole array - just first button
//  panel_buttons[0].state = panel_buttons[0].bounce.rose();
/*
  if (HIGH == digitalRead(panel_buttons[0].pin)){
    Serial.println("PRESS");
  } else {
    Serial.println("OPEN");
  }
*/
  if ( panel_buttons[0].bounce.fell()){
  // Your computer will receive these characters from a USB keyboard.
//  Keyboard.print("Hello World ");
//  Keyboard.println(count);

  // You can also send to the Arduino Serial Monitor
  Serial.println(count);
   // increment the count
  count = count + 1;
} else {
  //  Serial.println("nope");
}


  // typing too rapidly can overwhelm a PC
  delay(40);
}
