/**************************************************************************/
/*!
    @file     ALTAIR_GenTelInt.h
    @author   Justin Albert (jalbert@uvic.ca)
    @license  GPL

    This is the Generic Telemetry Interface base class for ALTAIR.
    Note that the transceiver-specific classes (e.g. DNT900, SHX,
    RFM23BP, etc.) derive from this class.  Essentially all
    functionality (i.e. anything that isn't entirely specific to a 
    given transceiver) is abstracted to and available within this 
    interface.  Note that when necessary, inputs default to those
    for the DNT900. 
    Justin Albert  jalbert@uvic.ca     began on 8 Oct. 2017

    @section  HISTORY

    v1.0  - First version
*/
/**************************************************************************/

#ifndef  ALTAIR_GenTelInt_h
#define  ALTAIR_GenTelInt_h

#include "Arduino.h"

#define  FAKE_RSSI_VAL     127
#define  MAX_TERM_LENGTH   255
#define  MAX_READ_TRIES    100
#define  TX_START_BYTE    0xFA
#define  RX_START_BYTE    0xFC
#define  CALL_SIGN_STRING     " VE7XJA STATION ALTAIR "
#define  END_MESSAGE_STRING   " OVER "

typedef  enum { dnt900 ,
                shx144 ,
                rfm23bp } radio_t;

class    TinyGPSPlus;

class ALTAIR_GenTelInt {
  public:
    virtual bool         send(unsigned char aChar)                 = 0;
    virtual bool         send(const uint8_t* aString)              = 0;
            bool         sendGPS(TinyGPSPlus& gps)                    ;
    virtual bool         sendStart()                               { return send((unsigned char)  TX_START_BYTE      ) ; }
    virtual bool         sendAsIndivChars(const uint8_t* aString)  = 0;
    virtual bool         sendCallSign()                            { return send((const uint8_t*) CALL_SIGN_STRING   ) ; }
    virtual bool         sendEndMessage()                          { return send((const uint8_t*) END_MESSAGE_STRING ) ; }
    virtual bool         available()                               = 0; // If a byte is available for reading, returns true.
    virtual bool         isBusy()                                  = 0;
    virtual bool         initialize(const char* aString = "")      = 0;
    virtual byte         read()                                    = 0;
            byte*        readALTAIRData()                             ;
    virtual const char*  radioName()                               = 0;
    virtual radio_t      radioType()                               = 0;
    virtual char         lastRSSI()                                = 0; // The RSSI value of most recently received message,
                                                                        // return value is in dBm, response of +127 means 
                                                                        // failed to get the last RSSI value.

  protected:
    ALTAIR_GenTelInt()                                                ;


  private:
  
};
#endif

