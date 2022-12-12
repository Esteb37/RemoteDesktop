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
    for (int i = 0; i < 5; i++)
    {
      Console.println("REMOTE_DESKTOP");
      delay(1000);
      if (readConsole() == CMD::LOGON)
      {
        return;
      }
    }

    writeNode(CMD::FAILURE);
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
