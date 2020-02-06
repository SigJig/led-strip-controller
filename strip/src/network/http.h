
#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

namespace HTTP
{
    class Server
    {
    public:
        Server(uint16_t port);

        void process();

    protected:
        WiFiServer m_server;
    };

    class Request
    {
    public:
        Request(WiFiClient& client);

        void write(char c);
        bool handle_incoming();

        String method;
        
        uint16_t status_code;
        String status_text;

        String endpoint;

    protected:
        WiFiClient& m_client;
        bool m_line_blank;
    };

    class Response
    {
    public:
        Response(WiFiClient& client);

        void handle();

    protected:
        WiFiClient& m_client;
    };
};

#endif // HTTP_H