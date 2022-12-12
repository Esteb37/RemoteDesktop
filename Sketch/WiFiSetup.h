#ifndef WIFISETUP_H
#define WIFISETUP_H

#include "Secret.h"
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

using namespace Secret;

namespace WF
{

    IPAddress local_IP(IP[0], IP[1], IP[2], IP[3]);
    IPAddress gateway(GATEWAY[0], GATEWAY[1], GATEWAY[2], GATEWAY[3]);
    IPAddress subnet(255, 255, 254, 0);
    IPAddress primaryDNS(8, 8, 8, 8);
    IPAddress secondaryDNS(8, 8, 4, 4);
    BearSSL::ESP8266WebServerSecure serverHTTPS(SERVER_PORT + 1);
    ESP8266WebServer server(SERVER_PORT);

    void secureRedirect(String path)
    {
        server.sendHeader("Location", String("https://esp8266.local" + path), true);
        server.send(301, "text/plain", "");
    }

    void setCrossOrigin()
    {
        server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
        server.sendHeader(F("Access-Control-Max-Age"), F("600"));
        server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
        server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
    };

    void setCrossOriginHTTPS()
    {
        serverHTTPS.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
        serverHTTPS.sendHeader(F("Access-Control-Max-Age"), F("600"));
        serverHTTPS.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
        serverHTTPS.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
    };

    void setup()
    {

        if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
        {
            Console.println("STA Failed to configure");
        }

        delay(10);
        Console.println(WiFi.localIP());

        // Connect to WiFi network
        Console.println();
        Console.println();
        Console.print("Connecting to ");
        Console.println(SSID);

        WiFi.begin(SSID, PASSWORD);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Console.print(".");
        }
        Console.println("");
        Console.println("WiFi connected");

        serverHTTPS.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));

        // Print the IP address
        Console.println(WiFi.localIP());

        if (MDNS.begin("esp8266"))
        {
            Serial.println("MDNS responder started");
        }
    }
}

#endif