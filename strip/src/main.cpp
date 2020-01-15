
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

// #include "colors.h"
// #include "strip.h"

#include "secrets.h"

#define HTTP_PORT 80

const char* ssid = SSID;
const char* password = PASSWORD;

WiFiServer server(HTTP_PORT);

void make_get_request(String server, uint16_t port, String endpoint)
{
  WiFiClient client;

  if (client.connect(server.c_str(), port))
  {
    client.println(String("GET /") + endpoint);
    client.println(String("Host: ") + server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("Unable to connect to server");
  }
}

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED);

  Serial.println("Wifi connection established");

  server.begin();

  Serial.print("Server available at IP ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  auto client = server.available();
  if (client)
  {
    bool blank = true;
    Serial.println("Request recieved");

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        
        if (c == '\n')
        {
          if (blank)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Connection-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<h1>Hello World!</h1>");
            break;
          }
          else
          {
            blank = true;
          }
        }
        else
        {
          blank = false;
        }
        
      }
    }

    client.stop();
    delay(1);
  }
}