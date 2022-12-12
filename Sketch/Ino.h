#ifndef IS_NODE

#include "Comm.h"
#include "Secret.h"
#include <Keyboard.h>

using namespace Secret;

namespace INO
{

  void triggerAutomation()
  {
    Keyboard.write(' ');
    delay(1000);
    Keyboard.print(NIP);
    Keyboard.write(KEY_RETURN);
  }

  void setup()
  {
    Node.begin(115200);
    Console.begin(9600);
    Keyboard.begin();

    while (!Console)
    {
      delay(1);
    }

    Console.println("Ready");
  }

  void loop()
  {
    if (Node.available() > 0)
    {
      CMD command = readNode();

      if (command == CMD::START)
      {
        triggerAutomation();
      }
    }
  }
}

#endif
