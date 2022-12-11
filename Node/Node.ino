#include <ESP8266WiFi.h>

const char *ssid = "***REMOVED***";
const char *password = "***REMOVED***";
const char *host = "***REMOVED***"; // it will tell you the IP once it starts up

// Set your Static IP address
IPAddress local_IP(***REMOVED***);
// Set your Gateway IP address
IPAddress gateway(***REMOVED***);

IPAddress subnet(255, 255, 254, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WiFiServer server(***REMOVED***); // just pick any port number you like

bool isRunning = false;

void sendResponse(WiFiClient client, int code, String message)
{
  client.println("HTTP/1.1 " + String(code) + " " + message);
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(message);
  client.println();
}

void setup()
{

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
  }

  Serial.begin(115200);
  delay(10);
  Serial.println(WiFi.localIP());

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Check if a client has connected

  WiFiClient client = server.available();
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
    uint8_t index = req.indexOf("/RUN");

    if (index != -1 && (req[index + 4] == req.length() || req[index + 4] == ' '))
    {
      Serial.println("COMMAND: RUN");
    }
    else
    {
      sendResponse(client, 404, "Not found");
    }
  }

  // Read Serial
  while (Serial.available())
  {
    if (Serial.find("COMMAND: DONE"))
    {
      Serial.println("COMMAND: DONE");
      sendResponse(client, 200, "OK");
    }
  }

  delay(1);
}
