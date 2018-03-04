/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#include <Bounce2.h>



#define DEBOUNCE_PERIOD 10
#define KEY_DELAY 40
int input_count = 0;
// timer objects for animations:
typedef struct {
  uint8_t pin; // Teensy pin number
  int keycode; // Key code to send when above pin is closed
  Bounce bounce; // Using the Bounce timer library - this is a bounce object
} ButtonMap;


#define NUMBER_OF_BUTTONS 8
ButtonMap panel_buttons [NUMBER_OF_BUTTONS] {
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

// populate the Bounce timer thingies in the panel button array
  for (input_count=0; input_count<NUMBER_OF_BUTTONS; input_count++){
    pinMode( panel_buttons[input_count].pin, INPUT_PULLUP);
    panel_buttons[input_count].bounce.attach(panel_buttons[input_count].pin);
    panel_buttons[input_count].bounce.interval(DEBOUNCE_PERIOD);
  }

}

void loop() {
  for (input_count=0; input_count<NUMBER_OF_BUTTONS; input_count++){

    panel_buttons[input_count].bounce.update(); // update each button
    if ( panel_buttons[input_count].bounce.fell()){ // see if it was pressed
       Keyboard.print("But ");
      Keyboard.println(input_count);
      /*
      Keyboard.press(panel_buttons[input_count].keycode);
      delay( KEY_DELAY);  // typing too rapidly can overwhelm a PC
      Keyboard.release(panel_buttons[input_count].keycode);
      delay( KEY_DELAY);  // typing too rapidly can overwhelm a PC
      */

    }
}
/*
  // You can also send to the Arduino Serial Monitor
  Serial.println(count);
   // increment the count
  count = count + 1;
} else {
  //  Serial.println("nope");
}
*/


  delay(20);
}
