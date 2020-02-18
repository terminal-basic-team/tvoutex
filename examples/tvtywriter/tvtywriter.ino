#include <TVoutEx.h>
#include <utility/Font4x6.h>
#include <TVoutPrint.hpp>

static constexpr const uint8_t HRES = 128;
static constexpr const uint8_t VRES = 144;

// Implicit singleton, use TVoutEx::instance() for access to object,
// previously allocated on the stack, heap or in static memory as below
static TVoutEx tvout;
static uint8_t videoBuffer[TVoutEx::bufferSize(HRES, VRES)];
static TVoutPrint tvPrint;

void setup()
{
  Serial.begin(115200);
  tvout.begin(PAL, HRES, VRES, videoBuffer);
  tvout.selectFont(font4x6);
}

void loop()
{
  if (Serial.available() > 0) {
    int c = Serial.read();
    tvPrint.write(c);
    if (c == '\r')
      tvPrint.write('\n');
  }
}
