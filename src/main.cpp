#include <Arduino.h>
#include "disp_max72.h"
#include "sens_mhz19b.h"
#include "disp_strip.h"

uint32_t startTimeAnim = 0;
uint32_t spanTimeAnim = 1 * 1000;
uint32_t startTimeMeasurement = 0;
uint32_t spanTimeMeasurement = 1L * 60L * 1000L;
RgbColor rangeC[] = {RgbColor(0, 255, 0),
                     RgbColor(0, 255, 0),
                     RgbColor(255, 255, 0),
                     RgbColor(255, 0, 0),
                     RgbColor(255, 0, 0)};
int rangeV[] = {0, 600, 1000, 2000, 10000};
int co2val = 325;
RgbColor clrPt1, clrPt2;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial attach
  Serial.println("SchoolMeteo v0.0");
  setupMatrix();
  txtMatrix(" wait", 0);
  setupSensor();
  setupStrip();
  clrPt1 = rangeC[1];
  clrPt2 = rangeC[1];
}

void recalculate()
{
  uint8_t i;
  intMatrix((uint16_t)co2val);
  for (i = 0; i < (uint8_t)(sizeof(rangeC) / sizeof(rangeC[0])); i++)
  {
    if ((co2val >= rangeV[i]) && (co2val < rangeV[i + 1]))
    {
      clrPt1 = clrPt2;
      clrPt2 = RgbColor::LinearBlend(rangeC[i], rangeC[i + 1], ((float)(co2val - rangeV[i]) / (rangeV[i + 1] - rangeV[i])));
      return;
    }
  }
}

void loop(void)
{
  RgbColor tmpclr;
  int tmpco2;
  if ((startTimeMeasurement == 0) && (millis() < spanTimeMeasurement))
  {
    if (millis() > (startTimeAnim + spanTimeAnim))
    {
      co2val += 75;
      recalculate();
      startTimeAnim = millis();
    }
  }
  else
  {
    if (millis() > (startTimeMeasurement + spanTimeMeasurement))
    {
      tmpco2 = co2Sensor();
      if (tmpco2 >= 400)
      {
        co2val = tmpco2;
        recalculate();
        if (startTimeMeasurement == 0)
        {
          clrPt1 = clrPt2;
          spanTimeMeasurement = 30L * 1000L;
          spanTimeAnim = 30L * 1000L;
        }
        startTimeMeasurement = millis();
        startTimeAnim = millis();
      };
    }
  }
  tmpclr = RgbColor::LinearBlend(clrPt1, clrPt2, (float)(millis() - startTimeAnim) / (spanTimeAnim));
  shiftStrip(&tmpclr);
  barMatrix((float)(millis() - startTimeMeasurement) / (spanTimeMeasurement));

  return;
}
