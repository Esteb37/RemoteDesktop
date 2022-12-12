#ifndef IS_NODE

#include "Comm.h"
#include "Keys.h"
#include "Secret.h"

namespace INO
{

#define SWITCH 12

  void powerOn()
  {
    digitalWrite(SWITCH, LOW);
    delay(1000);
    digitalWrite(SWITCH, HIGH);
  }

  void triggerAutomation()
  {

    inputNIP();

    for (int i = 0; i < 5; i++)
    {
      delay(2000);
      if (readConsole() == CMD::LOGON)
      {
        writeNode(CMD::DONE);
        return;
      }
    }

    writeNode(CMD::FAILURE);
  }

  void setup()
  {

    pinMode(SWITCH, OUTPUT);

    Node.begin(115200);
    Console.begin(9600);
    Keyboard.begin();

    delay(1000);

    Console.println("Ready");
  }

  void loop()
  {
    digitalWrite(SWITCH, HIGH);

    if (Node.available() > 0)
    {
      CMD command = readNode();

      if (command == CMD::START)
      {
        powerOn();
        delay(30000);
        triggerAutomation();
      }
      Node.flush();
    }
  }
}

#endif
