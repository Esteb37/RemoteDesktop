#ifndef IS_NODE

#include "../Common/Comm.h"
#include "../Common/Secret.h"
#include <Keyboard.h>

namespace INO
{

#define SWITCH 12

  void powerOn()
  {
    Console.println("Powering On");
    digitalWrite(SWITCH, LOW);
    delay(1000);
    digitalWrite(SWITCH, HIGH);
    nodeStatus(STAT::POWERED);
  }

  void inputNIP()
  {
    Console.println("Inputting NIP");
    Keyboard.write(' ');
    delay(1000);
    Keyboard.print(Secret::NIP);
    Keyboard.write(KEY_RETURN);
    nodeStatus(STAT::LOGGED);
  }

  ERR waitForStatus(STAT stat)
  {
    for (int i = 0; i < 5; i++)
    {

      String line = Console.readStringUntil('\n');

      CMD command = getCommand(line);

      if (command == CMD::SETSTAT && getStat(line) == stat)
      {
        return ERR::NONE;
      }
      else if (command == CMD::FAILURE)
      {
        return getErr(line);
      }

      delay(1000);
    }

    return ERR::NO_SERIAL;
  }

  void triggerAutomation()
  {
    powerOn();
    delay(30000);
    inputNIP();

    Console.println("Waiting for automation");

    STAT statuses[] = {LOGON, WIFI, PARSEC};

    for (STAT status : statuses)
    {

      Console.println("Waiting for " + str(status));
      ERR failure = waitForStatus(status);
      if (failure != ERR::NONE)
      {
        nodeFailure(failure);
        return;
      }
      else
      {
        nodeStatus(status);
      }
    }

    nodeCommand(CMD::DONE);
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
        triggerAutomation();
      }
      Node.flush();
    }
  }
}

#endif
