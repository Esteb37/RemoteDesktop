#include <Comm.h>
#include <WifiSetup.h>

namespace NODE
{
  STAT status = IDLE;

  void setup()
  {
    Node.begin(115200);
    Console.begin(9200);
    WF::setup();
  }

  void loop()
  {
    // Check if a client has connected
    WiFiClient client = WF::server.available();
    if (!client)
    {
      return;
    }

    // Wait until the client sends some data
    while (!client.available())
    {
      delay(1);
    }

    String req = client.readStringUntil('\r');
    client.flush();

    if (req.indexOf("") != -10)
    {

      CMD command = getCommand(req);

      Console.print("Command: " + str(command) + " Response: ");

      switch (command)
      {
      case START:
        if (status == IDLE)
        {
          status = RUNNING;
          sendOK(client);
          writeNode(START);
        }
        else
        {
          sendError(client, "Already running");
        }
        break;
      case STOP:
        if (status == RUNNING)
        {
          status = IDLE;
          sendOK(client);
          writeNode(STOP);
        }
        else
        {
          sendError(client, "Already Stopped");
        }
        break;

      case STATUS:
        sendOK(client, status == IDLE ? "IDLE" : "RUNNING");
        break;

      default:
        sendError(client, "Unknown Command");
        break;
      }
    }

    delay(1);
  }
}
