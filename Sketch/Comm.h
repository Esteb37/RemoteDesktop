#include "Types.h"
#include <String.h>

#ifndef IS_NODE
#define Console Serial
#define Node Serial1
#endif

#ifdef IS_NODE

#define Console Serial
#define Node Serial

#include "WifiSetup.h"

using namespace WF;

void sendResponse(int code, String message)
{
    setCrossOrigin();
    server.send(code, "text/plain", message);
}

void sendOK()
{
    sendResponse(200, "OK");
}

void sendOK(String message)
{
    sendResponse(200, message);
}

void sendError()
{
    sendResponse(400, "Error");
}

void sendError(String message)
{
    sendResponse(400, message);
}

void sendNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void sendResponseHTTPS(int code, String message)
{
    setCrossOriginHTTPS();
    serverHTTPS.send(code, "text/plain", message);
}

void sendOKHTTPS()
{
    sendResponseHTTPS(200, "OK");
}

void sendOKHTTPS(String message)
{
    sendResponseHTTPS(200, message);
}

void sendErrorHTTPS()
{
    sendResponseHTTPS(400, "Error");
}

void sendErrorHTTPS(String message)
{
    sendResponseHTTPS(400, message);
}

void sendNotFoundHTTPS()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    serverHTTPS.send(404, "text/plain", message);
}

#endif

CMD getCommand(String req)
{
    int start = req.indexOf("/");
    int end = req.indexOf(" ", start);
    return cmd(req.substring(start + 1, end));
}

STAT getStat(String req)
{
    int start = req.indexOf("+");
    int end = req.indexOf(" ", start);
    return stat(req.substring(start + 1, end));
}

ERR getErr(String req)
{
    int start = req.indexOf("+");
    int end = req.indexOf(" ", start);
    return err(req.substring(start + 1, end));
}

void nodeCommand(CMD command)
{
    Node.println(str(command));
}

void nodeStatus(STAT status)
{
    Node.println(str(CMD::SETSTAT) + "+" + str(status));
}

void nodeFailure(ERR failure)
{
    Node.println(str(CMD::FAILURE) + "+" + str(failure));
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
