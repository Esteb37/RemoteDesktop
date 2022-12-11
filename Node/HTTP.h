#include <ESP8266WiFi.h>

String COMMAND_LIST[] = {"START", "STOP", "STATUS"};

enum CMD
{
    START = 0,
    STOP,
    STATUS,
    UNKNOWN
};

enum STATUS
{
    IDLE,
    RUNNING,
    ERROR
};

CMD getCommand(String req)
{
    for (uint8_t i = 0; i < COMMAND_LIST->length(); i++)
    {

        String command = COMMAND_LIST[i];

        req.toUpperCase();

        command = "/" + command;

        uint8_t index = req.indexOf(command);

        if (index != -1 && (req[index + command.length()] == req.length() || req[index + command.length()] == ' '))
        {
            return (CMD)i;
        }
    }

    return CMD::UNKNOWN;
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
