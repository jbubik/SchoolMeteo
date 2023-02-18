#include <Arduino.h>
#include <MHZ.h>


// pin for uart reading
#define MH_Z19_RX 2 // D7
#define MH_Z19_TX 3 // D6

MHZ co2(MH_Z19_RX, MH_Z19_TX, MHZ19B);

void setupSensor()
{
    co2.setDebug(true);
    co2.setAutoCalibrate(false);
    co2.setRange(RANGE_5K);
}

int co2Sensor()
{
   int ppm_uart = co2.readCO2UART();
    if (ppm_uart<0){
        return(-ppm_uart);
    }
    return (ppm_uart);
}

int tmpSensor()
{
    uint16_t temperature = co2.getLastTemperature();
    return (temperature);
}