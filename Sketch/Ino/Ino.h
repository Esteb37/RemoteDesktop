#ifndef IS_NODE

#include "../Common/Comm.h"
#include "../Common/Secret.h"
#include <Keyboard.h>

namespace INO
{

#define SWITCH 12

  void powerOn()
  {
    digitalWrite(SWITCH, LOW);
    delay(500);
    digitalWrite(SWITCH, HIGH);
    delay(30000);
    nodeStatus(STAT::POWERED);
  }

  void inputNIP()
  {
    Keyboard.write(' ');
    delay(1000);
    Keyboard.print(Secret::NIP);
    Keyboard.write(KEY_RETURN);
    nodeStatus(STAT::LOGGED);
  }

  void shutOff()
  {
    digitalWrite(SWITCH, LOW);
    delay(5000);
    digitalWrite(SWITCH, HIGH);
    nodeStatus(STAT::IDLE);
  }

  ERR waitForStatus(STAT stat)
  {

    long start = millis();

    while (millis() - start < 10000)
    {

      if (Console.available() > 0)
      {

        String line = Console.readStringUntil('\n');

        line.trim();

        CMD command = getCommand(line);

        if (command == CMD::SETSTAT && getStat(line) == stat)
        {
          return ERR::NONE;
        }
        else if (command == CMD::FAILURE)
        {
          return getErr(line);
        }
      }
    }

    return ERR::NO_SERIAL;
  }

  void triggerAutomation()
  {
    powerOn();
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
        consoleCommand(CMD::AK);
      }
    }

    nodeStatus(STAT::HOSTING);
  }

  void setup()
  {

    pinMode(SWITCH, OUTPUT);
    Node.begin(115200);
    Console.begin(9600);
    Keyboard.begin();

    delay(3000);

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
      else if (command == CMD::SHUTOFF)
      {
        shutOff();
      }
      Node.flush();
    }

    if (Console.available() > 0)
    {
      String line = Console.readStringUntil('\n');
      line.trim();
      CMD command = getCommand(line);
      if (command == CMD::SETSTAT)
      {
        nodeStatus(getStat(line));
      }
      else if (command == CMD::FAILURE)
      {
        nodeFailure(getErr(line));
      }
    }
  }
}

#endif
