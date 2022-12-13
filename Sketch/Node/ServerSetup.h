#ifdef IS_NODE

#ifndef SERVERSETUP_H
#define SERVERSETUP_H

#include "../Common/Secret.h"
#include "Handlers.h"
#include "Responses.h"
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

using namespace Secret;

namespace NODE
{
    void onStart(bool);
    void onStop(bool);
    void onGetStat(bool);
}

namespace SERVER
{
    BearSSL::ESP8266WebServerSecure https(SERVER_PORT + 1);
    ESP8266WebServer http(SERVER_PORT);

    void setCrossOrigin(bool use_https = false)
    {
        if (use_https)
        {
            https.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
            https.sendHeader(F("Access-Control-Max-Age"), F("600"));
            https.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
            https.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
        }
        else
        {
            http.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
            http.sendHeader(F("Access-Control-Max-Age"), F("600"));
            http.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
            http.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
        }
    };

    void on(String command, std::function<void(bool)> handler)
    {

        https.on(command, HTTP_GET, [handler]()
                 { handler(true); });

        http.on(command, HTTP_GET, [handler]()
                { handler(false); });
    }

    void setup()
    {

        https.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));

        http.on("/", HTTP_GET, []()
                { sendOK("NodeMCU"); });

        https.on("/", HTTP_GET, []()
                 { sendOK("NodeMCU", true); });

        http.on("/favicon.ico", HTTP_GET, []()
                { sendOK(""); });

        https.on("/favicon.ico", HTTP_GET, []()
                 { sendOK("", true); });

        on(str(CMD::START), NODE::onStart);

        on(str(CMD::STOP), NODE::onStop);

        on(str(CMD::GETSTAT), NODE::onGetStat);

        http.onNotFound([]()
                        { sendNotFound(false); });

        https.onNotFound([]()
                         { sendNotFound(true); });

        https.begin();
        Console.println("HTTPS Server started");

        http.begin();
        Console.println("HTTP Server started");
    }

}

#endif

#endif