#include "Types.h"
#include <String.h>

#ifndef IS_NODE
#define Console Serial
#define Node Serial1
#endif

#ifdef IS_NODE

#define Console Serial
#define Node Serial

#include <ESP8266WiFi.h>

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
}

void sendOK(WiFiClient client, String message)
{
    sendResponse(client, 200, message);
}

void sendError(WiFiClient client)
{
    sendResponse(client, 400, "Error");
}

void sendError(WiFiClient client, String message)
{
    sendResponse(client, 400, message);
}

#endif

CMD getCommand(String req)
{
    int start = req.indexOf("/");
    int end = req.indexOf(" ", start);
    String command = req.substring(start + 1, end);
    return cmd(command);
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
