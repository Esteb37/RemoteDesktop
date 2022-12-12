#include "Types.h"
#include <ESP8266WiFi.h>
#include <String.h>

#define Console Serial
#define Node Serial1

CMD getCommand(String req)
{
    int start = req.indexOf("/");
    int end = req.indexOf(" ", start);
    String command = req.substring(start + 1, end);
    return cmd(command);
}

void sendResponse(WiFiClient client, int code, String message)
{
    client.println("HTTP/1.1 " + String(code) + " " + message);
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(message);
    client.println();
}

void sendOK(WiFiClient client)
{
    sendResponse(client, 200, "OK");
    Console.println("OK");
}

void sendOK(WiFiClient client, String message)
{
    sendResponse(client, 200, message);
    Console.println("OK - " + message);
}

void sendError(WiFiClient client)
{
    sendResponse(client, 400, "Error");
    Console.println("Error");
}

void sendError(WiFiClient client, String message)
{
    sendResponse(client, 400, message);
    Console.println("Error - " + message);
}

void writeNode(CMD command)
{
    Node.println("/" + str(command));
}

CMD readConsole()
{
    if (Console.available() > 0)
    {
        String line = Console.readStringUntil('\n');
        line.trim();
        if (line.length() > 0)
        {
            return getCommand(line);
        }
    }

    return CMD::UNKNOWN;
}

CMD readNode()
{
    if (Node.available() > 0)
    {
        String line = Node.readStringUntil('\n');
        line.trim();
        if (line.length() > 0)
        {
            return getCommand(line);
        }
    }

    return CMD::UNKNOWN;
}
