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
  uint8_t pin; // Teensy pin number for input
  uint8_t LED;
  int modifier_key;
  int keycode; // Key code to send when above pin is closed
  Bounce bounce; // Using the Bounce timer library - this is a bounce object
} ButtonMap;


#define NUMBER_OF_BUTTONS 14
/* common modifier keys:
MODIFIERKEY_CTRL	MODIFIERKEY_RIGHT_CTRL	- Control Key
MODIFIERKEY_SHIFT	MODIFIERKEY_RIGHT_SHIFT	- Shift Key
MODIFIERKEY_ALT	MODIFIERKEY_RIGHT_ALT	- Alt Key
MODIFIERKEY_GUI	MODIFIERKEY_RIGHT_GUI	- Windows (PC) or Clover (Mac)
Use 0 if no modifier

KEY_MEDIA_RECORD
*/
ButtonMap panel_buttons [NUMBER_OF_BUTTONS] {
  // input pin, out LED pin, modifier key, key, Bounce object]
  { 2, 23, MODIFIERKEY_RIGHT_ALT, KEY_F5,  Bounce() }, // col 1
  { 3, 22, MODIFIERKEY_RIGHT_ALT, KEY_F6,  Bounce() }, // col 1
  { 4, 21, MODIFIERKEY_RIGHT_ALT, KEY_F7,  Bounce() }, // col 1
  { 5, 20, MODIFIERKEY_RIGHT_ALT, KEY_F8,  Bounce() }, // col 1
  { 6, 17, MODIFIERKEY_RIGHT_ALT, KEY_F9,  Bounce() }, // col 2
  { 7, 16, MODIFIERKEY_RIGHT_ALT, KEY_F10, Bounce() }, // col 2
  { 8, 15, MODIFIERKEY_RIGHT_ALT, KEY_F11, Bounce() }, // col 2
  { 9, 14, MODIFIERKEY_RIGHT_ALT, KEY_F12, Bounce() }, // col 2
  { 10, 0, MODIFIERKEY_SHIFT, KEY_F4, Bounce() }, // col 3
  { 11, 0, MODIFIERKEY_SHIFT, KEY_F6, Bounce() }, // col 3
  { 12, 0, MODIFIERKEY_SHIFT, KEY_F7, Bounce() }, // col 3
  { 28, 0, MODIFIERKEY_SHIFT, KEY_F8, Bounce() }, // col 3
  { 29, 0, MODIFIERKEY_CTRL, KEY_F10, Bounce() },
  { 30, 0, MODIFIERKEY_CTRL, KEY_F11, Bounce() },

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

    // outputs:
    if (0 != panel_buttons[input_count].LED){
      pinMode(panel_buttons[input_count].LED, OUTPUT);
      PanelLED(input_count, LOW);
    }
  }

}

void loop() {
  for (input_count=0; input_count<NUMBER_OF_BUTTONS; input_count++){

    panel_buttons[input_count].bounce.update(); // update each button
    if ( panel_buttons[input_count].bounce.fell()){ // see if it was pressed

//       Serial.print("But ");
  //    Serial.println(input_count);

  // light the LED for this button:
      SingleLED(input_count);
  // press some buttons:
      if(0 != panel_buttons[input_count].modifier_key){
        Keyboard.press(panel_buttons[input_count].modifier_key);
        delay( KEY_DELAY);
      }
      Keyboard.press(panel_buttons[input_count].keycode);
      delay( KEY_DELAY);  // typing too rapidly can overwhelm a PC
      Keyboard.release(panel_buttons[input_count].keycode);
      delay( KEY_DELAY);

      if(0 != panel_buttons[input_count].modifier_key){
        Keyboard.release(panel_buttons[input_count].modifier_key);
        delay( KEY_DELAY);
      }

    }
}

  delay(20);
}

/*
  param which input
  param true = on, false = off
 */
void PanelLED( uint8_t button_number, int state){
  Serial.print("LED");
  Serial.println(panel_buttons[button_number].LED);
  digitalWrite(panel_buttons[button_number].LED, state);
}

void SingleLED (uint8_t button_number) {

  if (0 != panel_buttons[button_number].LED){
    for (int this_LED=0; this_LED<NUMBER_OF_BUTTONS; this_LED++){
      if (this_LED == button_number){
          digitalWrite(panel_buttons[this_LED].LED, HIGH);
      } else {
          digitalWrite(panel_buttons[this_LED].LED, LOW);
      }
    }
  }
}
