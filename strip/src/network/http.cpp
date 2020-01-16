
#include "../../config.h"
#include "http.h"

HTTP::Server::Server(uint16_t port)
    : m_server(WiFiServer(port))
{  }

void HTTP::Server::run()
{
    while (true) process();
}

bool HTTP::Server::process()
{
    auto client = m_server.available();
    
    if (!client) return false;

    auto request = Request(client);
    auto response = Response(client);

    while (client.connected())
    {
        if (client.available())
        {
            if (!request.handle_incoming())
            {
                response.handle();

                break;
            }
        }
    }

    client.stop();

    return true;
}

HTTP::Request::Request(WiFiClient& client)
    : m_client(client), m_line_blank(true)
{  }

bool HTTP::Request::handle_incoming()
{
    char c = m_client.read();

    if (c == '\n')
    {
        if (m_line_blank) return true;
    }
    else if (c != '\r')
    {
        m_line_blank = false;
    }

    write(c);

    return false;
}

void HTTP::Request::write(char c)
{
    if (c == '\n')
    {

    }
    else
    {
        
    }
    
}