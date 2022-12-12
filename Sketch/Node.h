#ifdef IS_NODE
#include "Comm.h"
#include "WifiSetup.h"

namespace NODE
{
  STAT status = STAT::IDLE;
  ERR error = ERR::NONE;

  void setup()
  {
    Node.begin(115200);
    WF::setup();
  }

  void loop()
  {

    WiFiClient client = WF::server.available();
    if (!client)
    {
      return;
    }

    if (client.available())
    {

      String req = client.readStringUntil('\r');
      client.flush();

      if (req.indexOf("") != -10)
      {

        CMD command = getCommand(req);

        if (command != CMD::FAVICON)
        {
          switch (command)
          {
          case CMD::START:
            if (status == STAT::IDLE)
            {
              status = STAT::RUNNING;
              sendOK(client);
              nodeCommand(CMD::START);
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
              nodeCommand(CMD::STOP);
            }
            else
            {
              sendError(client, "Already Stopped");
            }
            break;

          case CMD::GETSTAT:
            if (status != STAT::ERROR)
            {
              sendOK(client, str(status));
            }
            else
            {
              sendError(client, str(error));
            }
            break;

          default:
            sendError(client, "Unknown Command");
            break;
          }
        }
      }

      delay(1);
    }

    if (Node.available() > 0)
    {
      String line = Node.readStringUntil('\n');
      CMD command = getCommand(line);
      if (command == CMD::SETSTAT)
      {
        status = getStat(line);
      }
      else if (command == CMD::FAILURE)
      {
        status = STAT::ERROR;
        error = getErr(line);
      }
    }
  }
}

#endif
