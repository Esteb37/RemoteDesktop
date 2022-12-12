#ifdef IS_NODE
#include "Comm.h"
#include "WifiSetup.h"

namespace NODE
{
  STAT status = STAT::IDLE;
  ERR error = ERR::NONE;

  void onStart()
  {
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

  void onStartHTTPS()
  {
    if (status == STAT::IDLE)
    {
      status = STAT::RUNNING;
      sendOKHTTPS();
      nodeCommand(CMD::START);
    }
    else
    {
      sendError("Already Running");
    }
  }

  void onStopHTTPS()
  {
    if (status == STAT::RUNNING)
    {
      status = STAT::IDLE;
      sendOKHTTPS();
      nodeCommand(CMD::STOP);
    }
    else
    {
      sendError("Already Stopped");
    }
  }

  void onGetStatHTTPS()
  {
    if (status != STAT::ERROR)
    {
      sendOKHTTPS(str(status));
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

    serverHTTPS.on("/", HTTP_GET, []()
                   { sendOKHTTPS("NodeMCU"); });

    serverHTTPS.on(str(CMD::FAVICON), HTTP_GET, []()
                   { sendOKHTTPS(""); });

    serverHTTPS.on(str(CMD::START), HTTP_GET, onStartHTTPS);

    serverHTTPS.on(str(CMD::STOP), HTTP_GET, onStopHTTPS);

    serverHTTPS.on(str(CMD::GETSTAT), HTTP_GET, onGetStatHTTPS);

    serverHTTPS.onNotFound(sendNotFoundHTTPS);

    serverHTTPS.begin();

    Console.println("HTTPS Server started");

    server.on("/", HTTP_GET, []()
              { sendOK("NodeMCU"); });

    server.on(str(CMD::FAVICON), HTTP_GET, []()
              { sendOK(""); });

    server.on(str(CMD::START), HTTP_GET, onStart);

    server.on(str(CMD::STOP), HTTP_GET, onStop);

    server.on(str(CMD::GETSTAT), HTTP_GET, onGetStat);

    server.onNotFound(sendNotFound);

    server.begin();

    Console.println("HTTP Server started");
  }

  void loop()
  {

    serverHTTPS.handleClient();
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
