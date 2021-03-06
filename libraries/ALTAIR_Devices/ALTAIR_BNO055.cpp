/**************************************************************************/
/*!
    @file     ALTAIR_BNO055.cpp
    @author   Justin Albert (jalbert@uvic.ca)
    @license  GPL

    This is the class for the ALTAIR Adafruit BNO055 orientation sensor, 
    located on the mast.  This class derives from the ALTAIR_OrientSensor 
    generic orientation sensor base class.

    Justin Albert  jalbert@uvic.ca     began on 6 Sep. 2018

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include "ALTAIR_BNO055.h"

/**************************************************************************/
/*!
 @brief  Constructor.
*/
/**************************************************************************/
ALTAIR_BNO055::ALTAIR_BNO055( byte    adafruitSensorID          ) :
                     _theBNO055(      adafruitSensorID          )
{
}

/**************************************************************************/
/*!
 @brief  Default constructor.
*/
/**************************************************************************/
ALTAIR_BNO055::ALTAIR_BNO055(                                   ) :
                     _theBNO055(      DEFAULT_BNO055_ADAFRUITID )
{
}

/**************************************************************************/
/*!
 @brief  Return the type and health.
*/
/**************************************************************************/
uint8_t ALTAIR_BNO055::typeAndHealth(                           )
{
  uint8_t system_status, self_test_results, system_error;
  _theBNO055.getSystemStatus(&system_status, &self_test_results, &system_error);
  if (system_error == 0) {
       return ((uint8_t) bno055_healthy);
    } else {
       return ((uint8_t) bno055_unhealthy);
    }
}

/**************************************************************************/
/*!
 @brief  Initialize the orientation sensor during the setup routine.
*/
/**************************************************************************/
void ALTAIR_BNO055::initialize(                                 ) 
{
    Serial.println(F("BNO055 orientation sensor initialization..."));
    if (!_theBNO055.begin()) {
        // There was a problem detecting the BNO055 ... check your connections 
        Serial.println(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
        while(1);
    }
    delay(1000);    // is this necessary? -- why is this here??? -- I don't remember why!!!
    _theBNO055.setExtCrystalUse(true);
}

/**************************************************************************/
/*!
 @brief  Prints out orientation info.
*/
/**************************************************************************/
void ALTAIR_BNO055::printInfo(                                  )
{
    /* Get a new sensor event */ 
    sensors_event_t event; 
    _theBNO055.getEvent(&event);
  
    /* Display the floating point data */
    Serial.print(F("X: "));
    Serial.print(event.orientation.x, 4);
    Serial.print(F("\tY: "));
    Serial.print(event.orientation.y, 4);
    Serial.print(F("\tZ: "));
    Serial.print(event.orientation.z, 4);
    Serial.println();
}


