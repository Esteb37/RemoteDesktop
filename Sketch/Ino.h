#ifndef IS_NODE

#include "Comm.h"
#include "Keys.h"
#include "Secret.h"

namespace INO
{

  void triggerAutomation()
  {

    inputNIP();

    for (int i = 0; i < 5; i++)
    {
      delay(2000);
      if (readConsole() == CMD::LOGON)
      {
        runPython();
        writeNode(CMD::DONE);
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
      Node.flush();
    }
  }
}

#endif
