#ifdef IS_NODE
#include "Comm.h"
#include "WifiSetup.h"

namespace NODE
{
  STAT status = STAT::IDLE;

  void setup()
  {
    WF::setup();
  }

  void loop()
  {

    WiFiClient client = WF::server.available();
    if (!client)
    {
      return;
    }

    while (!client.available())
    {
      delay(1);
    }

    String req = client.readStringUntil('\r');
    client.flush();

    if (req.indexOf("") != -10)
    {

      CMD command = getCommand(req);

      if (command != CMD::FAVICON)
      {
        Console.print("HTTP Command: " + str(command) + "\tResponse: ");

        switch (command)
        {
        case CMD::START:
          if (status == STAT::IDLE)
          {
            status = STAT::RUNNING;
            sendOK(client);
            writeNode(CMD::START);
          }
          else
          {
            sendError(client, "Already running");
          }
          break;
        case CMD::STOP:
          if (status == STAT::RUNNING)
          {
            status = STAT::IDLE;
            sendOK(client);
            writeNode(CMD::STOP);
          }
          else
          {
            sendError(client, "Already Stopped");
          }
          break;

        case CMD::GETSTAT:
          sendOK(client, status == STAT::IDLE ? "IDLE" : "RUNNING");
          break;

        default:
          sendError(client, "Unknown Command");
          break;
        }
      }
    }

    delay(1);
  }
}

#endif
