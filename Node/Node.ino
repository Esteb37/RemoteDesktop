#include <ESP8266WiFi.h>
#include <HTTP.h>
#include <WifiSetup.h>

bool isRunning = false;

void setup()
{
  Serial.begin(115200);
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
    switch (getCommand(req))
    {
    case CMD::START:
      if (!isRunning)
      {
        isRunning = true;
        sendResponse(client, 200, "OK");
      }
      else
      {
        sendResponse(client, 400, "Already running");
      }
      break;
    case CMD::STOP:
      if (isRunning)
      {
        isRunning = false;
        sendResponse(client, 200, "OK");
      }
      else
      {
        sendResponse(client, 400, "Already stopped");
      }
      break;

    case CMD::STATUS:
      if (isRunning)
      {
        sendResponse(client, 200, "RUNNING");
      }
      else
      {
        sendResponse(client, 200, "IDLE");
      }
      break;
    default:
      sendResponse(client, 400, "Unknown command");
      break;
    }
  }

  // Read Serial
  while (Serial.available())
  {
    if (Serial.find("COMMAND: DONE"))
    {
      Serial.println("COMMAND: DONE");
      isRunning = false;
    }
  }

  delay(1);
}
