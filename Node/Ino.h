#include <Keyboard.h>

namespace INO
{
  void setup()
  {
    Keyboard.begin();

    Serial.begin(115200);
  }

  void loop()
  {
    // Check for "COMMAND: RUN"
    if (Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n');

      if (command.indexOf("COMMAND: RUN") != -1)
      {
        triggerAutomation();
      }
    }
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
}
