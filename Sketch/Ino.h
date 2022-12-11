#include <Arduino.h>
#include <Comm.h>
#include <Keyboard.h>

namespace INO
{
  void setup()
  {
    Keyboard.begin();
    Node.begin(115200);
    Console.begin(9200);
  }

  void loop()
  {
    CMD command = readNode();

    if (command == START)
    {
      Console.println("STARTING");
    }
  }

  void triggerAutomation()
  {
  }
}
