#include "Secret.h"
#include <ESP8266WiFi.h>

using namespace Secret;

namespace WF
{

    IPAddress local_IP(IP[0], IP[1], IP[2], IP[3]);
    IPAddress gateway(GATEWAY[0], GATEWAY[1], GATEWAY[2], GATEWAY[3]);
    IPAddress subnet(255, 255, 254, 0);
    IPAddress primaryDNS(8, 8, 8, 8);
    IPAddress secondaryDNS(8, 8, 4, 4);
    WiFiServer server(SERVER_PORT);

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

        // Start the server
        server.begin();
        Console.println("Server started");

        // Print the IP address
        Console.println(WiFi.localIP());
    }
}