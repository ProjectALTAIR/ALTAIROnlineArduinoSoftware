/**************************************************************************/
/*!
    @file     ALTAIR_ServoMotor.h
    @author   Justin Albert (jalbert@uvic.ca)
    @license  GPL

    This is the base class for the three ALTAIR servo motors: the 
    propulsion Axle rotation servo motor (A); the balloon helium Bleed 
    valve servo motor (B); and the Cutdown and parafoil steering servo 
    motor (C).  Servo A is a Corona CS238MG (actually, its older product 
    code is CS-238HV, but I believe it is the same device:
    https://hobbyking.com/en_us/corona-cs238mg-metal-gear-servo-4-6kg-0-14sec-22g.html
    ); Servo B is a Corona DS538HV
    https://hobbyking.com/en_us/corona-ds538hv-digital-metal-gear-servo-8kg-0-12sec-58g.html
    ; and servo C is a HobbyKing brand SW5513-6MA sail winch servo:
    https://hobbyking.com/en_us/sail-winch-servo-13kg-0-7sec-360deg-55g.html
    .  All three servos have been modified to include an analogue 
    encoder voltage output (from the potentiometer inside each servo)
    to report the servo's position via that analogue voltage.

    Justin Albert  jalbert@uvic.ca     began on 2 Sep. 2018

    @section  HISTORY

    v1.0  - First version
*/
/**************************************************************************/

#ifndef ALTAIR_ServoMotor_h
#define ALTAIR_ServoMotor_h

#include "Arduino.h"

#define   ALTAIRSERVO_VOLTSPERADU                        (0.0049)

class ALTAIR_ServoMotor {
  public:

    ALTAIR_ServoMotor(                              byte  posADCPin      )                                                             ;

    bool                     isInitialized(                              ) {  return         _isInitialized                            ; }

    float                    reportSetting(                              ) {  return         _setting                                  ; }
    virtual float            maxSafeSetting(                             )                  = 0                                        ;
    virtual float            minSafeSetting(                             )                  = 0                                        ;
    bool                     incrementSetting(                           )                                                             ;   // Increase setting by 1.    Returns true if successful.
    bool                     decrementSetting(                           )                                                             ;   // Decrease setting by 1.    Returns true if successful.
    bool                     halfIncrementSetting(                       )                                                             ;   // Increase setting by 0.5.  Returns true if successful.
    bool                     halfDecrementSetting(                       )                                                             ;   // Decrease setting by 0.5.  Returns true if successful.
    bool                     setSettingTo(          float newSetting     )                                                             ;   // Returns true if successful.

    float                    reportPosition(                             ) {  return  ALTAIRSERVO_VOLTSPERADU * analogRead(_posADCPin) ; } // Determine and report present position (in volts).

    void                     initializePinMode(                          )                                                             ;
    void                     initializePWMRegister(                      )                                                             ;

  protected:
    void                     setPWMPin(             byte  pwmPin         ) { _pwmPin        = pwmPin                                   ; }
    virtual void             resetPWMRegister     (                      )                  = 0                                        ;
    void                     initializeSetting(     float initialSetting ) { _setting       = initialSetting                           ; }
    void                     setInitialized(                             ) { _isInitialized = true                                     ; }

  private:
    bool                     _isInitialized                                                                                            ;

    float                    _setting                                                                                                  ; // present PWM setting of the servo

    byte                     _pwmPin                                                                                                   ;
    byte                     _posADCPin                                                                                                ;
};
#endif    //   ifndef ALTAIR_ServoMotor_h
