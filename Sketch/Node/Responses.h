#ifdef IS_NODE
#ifndef RESPONSES_H
#define RESPONSES_H

#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

namespace SERVER
{

    extern BearSSL::ESP8266WebServerSecure https;
    extern ESP8266WebServer http;

    void setCrossOrigin(bool use_https);

    void sendResponse(int code, String message, bool using_https = false)
    {
        setCrossOrigin(using_https);
        if (using_https)
        {
            https.send(code, "text/plain", message);
        }
        else
        {
            http.send(code, "text/plain", message);
        }
    }

    void sendOK(bool https = false)
    {
        sendResponse(200, "OK", https);
    }

    void sendOK(String message, bool https = false)
    {
        sendResponse(200, message, https);
    }

    void sendError(bool https = false)
    {
        sendResponse(400, "Error", https);
    }

    void sendError(String message, bool https = false)
    {
        sendResponse(400, message, https);
    }

    void sendNotFound(bool using_https = false)
    {

        if (using_https)
        {
            String message = "File Not Found\n\n";
            message += "URI: ";
            message += https.uri();
            message += "\nMethod: ";
            message += (https.method() == HTTP_GET) ? "GET" : "POST";
            message += "\nArguments: ";
            message += https.args();
            message += "\n";
            for (uint8_t i = 0; i < https.args(); i++)
            {
                message += " " + https.argName(i) + ": " + https.arg(i) + "\n";
            }
            https.send(404, "text/plain", message);
        }
        else
        {
            String message = "File Not Found\n\n";
            message += "URI: ";
            message += http.uri();
            message += "\nMethod: ";
            message += (http.method() == HTTP_GET) ? "GET" : "POST";
            message += "\nArguments: ";
            message += http.args();
            message += "\n";
            for (uint8_t i = 0; i < http.args(); i++)
            {
                message += " " + http.argName(i) + ": " + http.arg(i) + "\n";
            }
            http.send(404, "text/plain", message);
        }
    }
}

#endif
#endif