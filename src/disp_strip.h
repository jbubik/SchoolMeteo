#include <Arduino.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 1;  // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 7;     // make sure to set this to the correct pin, ignored for Esp8266
#define colorSaturation 255

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setupStrip()
{
    strip.Begin();
    strip.ClearTo(RgbColor(colorSaturation,0,0));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(0,colorSaturation,0));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(0,0,colorSaturation));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(colorSaturation,colorSaturation,0));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(colorSaturation,0,colorSaturation));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(0,colorSaturation,colorSaturation));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
    strip.ClearTo(RgbColor(colorSaturation,colorSaturation,colorSaturation));strip.Show();delay(50);
    strip.ClearTo(RgbColor(0,0,0));strip.Show();delay(300);
}

void shiftStrip(RgbColor *color)
{
    RgbColor tmpcolor = *color;
    tmpcolor.Darken(255-colorSaturation);
    strip.ShiftRight(1);
    strip.SetPixelColor(0, tmpcolor);
    strip.Show();
}
