#include <Keyboard.h> // The main library for sending keystrokes.

void setup()
{
  Keyboard.begin(); // Initialise the library.
}

// Loop around waiting for a button press on pin 2.
// When the button is pressed, go to the function triggerAutomation.
void loop()
{
  delay(5000);
  triggerAutomation();
}

void triggerAutomation()
{
  Keyboard.press(' ');
  delay(100);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("5714");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
}
