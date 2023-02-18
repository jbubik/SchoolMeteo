#include <Arduino.h>
#include <MD_MAX72xx.h>


// --------------------
// MAX72xx hardware definitions and properties
// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
//
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 13  // or SCK
#define DATA_PIN 11 // or MOSI
#define CS_PIN 10   // or SS

#define USE_LOCAL_FONT 1
#define MY_INTENSITY MAX_INTENSITY * 0

uint8_t grPPM[] = {7,
                   0x0f, 0xe5, 0x27, 0xe0, 0x2f, 0xe5,0x07};

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES); // SPI hardware interface
// MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Arbitrary pins

void setupMatrix()
{
  uint16_t i;
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MY_INTENSITY);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  for (i = mx.getColumnCount() - 1; i--;)
  {
    mx.setColumn(i, 0xff);
    delay(50);
    mx.setColumn(i, 0x0);
    delay(1);
  };
  for (i = 0; i <= 7; i++)
  {
    mx.setRow(i, 0xff);
    delay(50);
    mx.setRow(i, 0x0);
    delay(1);
  }
}

void txtMatrix(char *text, uint8_t *graphics)
{
  uint16_t wp = mx.getColumnCount() - 1;
  uint8_t i, j;
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();

  while (*text)
  {
    wp -= mx.setChar(wp, *text) + 1;
    text++;
  }
  if (graphics != NULL)
  {
    i = *graphics;
    graphics++;
    for (j = 0; j < i; j++)
    {
      mx.setColumn(wp--, *graphics);
      graphics++;
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return;
}

void intMatrix(uint16_t num)
{
  char b[10];
  sprintf(b, "%i", num);
  txtMatrix(&(b[0]), grPPM);
  return;
}

void barMatrix(float ratio)
{
  uint8_t a = 0xff << (uint8_t)(ratio * 8);
  mx.setColumn(0, a);
  // mx.setColumn(1, a);
}