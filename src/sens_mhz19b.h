#include <Arduino.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>

// pin for uart reading
#define MH_Z19_RX 2 // D7
#define MH_Z19_TX 3 // D6
#define MH_Z19_DEBUG 1

SoftwareSerial mySerial(MH_Z19_RX, MH_Z19_TX);
MHZ19 co2;

void setupSensor()
{
    mySerial.begin(9600);
    co2.printCommunication(false, MH_Z19_DEBUG);
    co2.begin(mySerial);
    char fwver[4];
    co2.getVersion(fwver);
    Serial.print("MHZ sensor firmware version: ");
    Serial.print(fwver[0]);
    Serial.print(".");
    Serial.print(fwver[1]);
    Serial.print(".");
    Serial.print(fwver[2]);
    Serial.print(".");
    Serial.println(fwver[3]);
    if (co2.getABC())
    {
        Serial.println("MHZ sensor ABC: on");
    }
    else
    {
        Serial.println("MHZ sensor ABC: off");
    }
    byte acc=co2.getAccuracy();
    Serial.print("MHZ sensor Accuracy: ");
    Serial.println(acc);
    int rnge=co2.getRange();
    Serial.print("MHZ sensor Range: ");
    Serial.println(rnge);
    byte ta=co2.getTempAdjustment();
    Serial.print("MHZ sensor Temperature Adjustment: ");
    Serial.println(ta);
    Serial.println("MHZ sensor set Range 10000ppm");
    co2.setRange(10000);
    delay(1000);
    /*
    int ppm_uart = co2.getCO2(false);
    Serial.print("MHZ sensor CO2 ppm:");
    Serial.println(ppm_uart);

    Serial.println("MHZ sensor calibrate zero (400ppm)");
    co2.calibrateZero();
    delay(30000);
    
    ppm_uart = co2.getCO2(false);
    Serial.print("MHZ sensor CO2 ppm:");
    Serial.println(ppm_uart);
    */
    Serial.println("MHZ sensor set ABC off now & every 24H");
    co2.autoCalibration(false, 24);
}

int co2Sensor()
{
    int ppm_uart = co2.getCO2(false);
    if (ppm_uart < 0)
    {
        return (-ppm_uart);
    }
    Serial.print("MHZ sensor CO2 ppm:");
    Serial.println(ppm_uart);
    return (ppm_uart);
}

int tmpSensor()
{
    uint16_t temperature = co2.getTemperature(false);
    return (temperature);
}