#ifndef IS_NODE

#include "Comm.h"
#include "Secret.h"
#include <Keyboard.h>

namespace INO
{

#define SWITCH 12

  void inputNIP()
  {
    Keyboard.write(' ');
    delay(1000);
    Keyboard.print(Secret::NIP);
    Keyboard.write(KEY_RETURN);
    nodeStatus(STAT::LOGGED);
  }

  void powerOn()
  {
    digitalWrite(SWITCH, LOW);
    delay(1000);
    digitalWrite(SWITCH, HIGH);
    nodeStatus(STAT::POWERED);
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

    STAT statuses[] = {LOGON, WIFI, PARSEC};

    for (STAT status : statuses)
    {
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

  void checkStatus()
  {
    if (Console.available() > 0)
    {
      String req = Console.readStringUntil('\n');
      CMD command = getCommand(req);
      if (command == CMD::SETSTAT)
      {
        STAT status = getStat(req);
        Node.println(str(command) + "+" + str(status));
      }
      else if (command == CMD::FAILURE)
      {
        Node.println(str(command));
      }
    }
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
