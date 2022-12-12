#ifdef IS_NODE
#include "Comm.h"
#include "WifiSetup.h"

namespace NODE
{
  STAT status = STAT::IDLE;
  ERR error = ERR::NONE;

  void onStart()
  {
    Console.println("Triggered start");
    if (status == STAT::IDLE)
    {
      status = STAT::RUNNING;
      sendOK();
      nodeCommand(CMD::START);
    }
    else
    {
      sendError("Already Running");
    }
  }

  void onStop()
  {
    if (status == STAT::RUNNING)
    {
      status = STAT::IDLE;
      sendOK();
      nodeCommand(CMD::STOP);
    }
    else
    {
      sendError("Already Stopped");
    }
  }

  void onGetStat()
  {
    if (status != STAT::ERROR)
    {
      sendOK(str(status));
    }
    else
    {
      sendError(str(error));
    }
  }

  void setup()
  {
    Node.begin(115200);
    WF::setup();

    server.on("/", HTTP_GET, []()
              { sendOK("NodeMCU"); });

    server.on(str(CMD::FAVICON), HTTP_GET, []()
              { sendOK(""); });

    server.on(str(CMD::START), HTTP_GET, onStart);

    server.on(str(CMD::STOP), HTTP_GET, onStop);

    server.on(str(CMD::GETSTAT), HTTP_GET, onGetStat);

    server.onNotFound(sendNotFound);

    server.begin();
  }

  void loop()
  {
    server.handleClient();

    delay(1);

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
