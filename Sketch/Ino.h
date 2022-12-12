#ifndef IS_NODE

#include "Comm.h"
#include <Keyboard.h>

namespace INO
{
  void setup()
  {
    Keyboard.begin();
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

#endif
