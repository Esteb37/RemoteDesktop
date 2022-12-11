#include <ESP8266WiFi.h>
#include <Types.h>

HardwareSerial Node = Serial1;
Serial_ Console = Serial;

CMD getCommand(String req)
{
    for (uint8_t i = 0; i < UNKNOWN; i++)
    {

        String command = str((CMD)i);

        command = "/" + command;

        req.toUpperCase();

        uint8_t index = req.indexOf(command);

        if (index != -1 && (req[index + command.length()] == req.length() || req[index + command.length()] == ' '))
        {
            return (CMD)i;
        }
    }

    return CMD::UNKNOWN;
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

void sendResponse(WiFiClient client, int code, String message)
{
    client.println("HTTP/1.1 " + String(code) + " " + message);
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(message);
    client.println();
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

    return UNKNOWN;
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

    return UNKNOWN;
}