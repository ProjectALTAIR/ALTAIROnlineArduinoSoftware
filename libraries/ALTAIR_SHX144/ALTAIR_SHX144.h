/**************************************************************************/
/*!
    @file     ALTAIR_SHX144.h
    @author   Justin Albert (jalbert@uvic.ca)
    @license  GPL

    This is the telemetry interface class for the ALTAIR SHX1-144-5
    radio transceiver, which operates at 144 MHz.  This class derives 
    from the ALTAIR_GenTelInt generic telemetry interface base class.

    Justin Albert  jalbert@uvic.ca     began on 15 Oct. 2017

    @section  HISTORY

    v1.0  - First version
*/
/**************************************************************************/
#ifndef ALTAIR_SHX144_h
#define ALTAIR_SHX144_h

#include "ALTAIR_GenTelInt.h"

class ALTAIR_SHX144 : public ALTAIR_GenTelInt {
  public:
    bool    send(unsigned char aChar);
    bool    send(const uint8_t* aString);
    bool    sendAsIndivChars(const uint8_t* aString);
    bool    available();                       // if a byte is available for reading, returns true
    bool    isBusy();
    bool    initialize(const char* aString = "");
    byte    read();
    char    lastRSSI();                        // The RSSI value of most recently received message,
                                               // return value is in dBm, response of +127 means 
                                               // failed to get the last RSSI value.
    ALTAIR_SHX144(const char serialID, const char fakeShxProgramRxPin, const char shxProgramPin, const char shxBusyPin);

  protected:
    ALTAIR_SHX144();

  private:

    char _serialID;
    char _fakeShxProgramRxPin;
    char _shxProgramPin;
    char _shxBusyPin;
  
};
#endif
