#include <Arduino.h>

#define OUT_R 3
#define OUT_G 5
#define OUT_B 6
#define OUT_W 9

class Color
{
public:
  Color(uint8_t pin)
    : m_pin(pin)
  {
    pinMode(this->m_pin, OUTPUT);
  }

  void set_signal(uint8_t signal)
  {
    this->m_signal = signal;
  }

  uint8_t get_signal()
  {
    return this->m_signal;
  }

  void show()
  {
    analogWrite(this->m_pin, this->m_signal);
  }

private:
  const uint8_t m_pin;

  uint8_t m_signal = 0;
};

struct RGB
{
  double r, g, b;
};

double dmap(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Color colors[4] = { OUT_R, OUT_G, OUT_B, OUT_W };

RGB hsv_rgb(double hue, uint8_t sat, uint8_t val)
{
  auto f = [&](uint8_t n)
  {
    double a = (n + hue / 60.0);
    double k = (int)a % 6 + (a - int(a));
    return val - val * sat * max(min(min(k, 4 - k), 1), 0);
  };

  return {f(5), f(3), f(1)};
}

uint8_t to_sig(double val)
{
  return val * 255;
}

void setup()
{
  Serial.begin(9600);

  colors[3].set_signal(200);
  colors[2].set_signal(255);
}

void loop()
{
  static uint16_t hue = 0;

  hue = (hue + 1) % 360;

  RGB rgb = hsv_rgb(hue, 1, 1);

  colors[0].set_signal(to_sig(rgb.r));
  colors[1].set_signal(to_sig(rgb.g));
  colors[2].set_signal(to_sig(rgb.b));
  colors[3].set_signal(0);

  Serial.print("Red: ");
  Serial.print(rgb.r);
  Serial.print(", Green: ");
  Serial.print(rgb.g);
  Serial.print(", Blue: ");
  Serial.println(rgb.b);

  for (uint8_t i = 0; i < 4; i++)
  {
    colors[i].show();
  }

  delay(1);
}