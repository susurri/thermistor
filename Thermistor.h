#ifndef THERMISTOR_H
#define THERMISTOR_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <math.h>

#define ADC_BITS 10

/* 
-- k0 = 273.15
-- t0 = 25.0
-- r0 = 100.0
-- r = r0 * exp(b * (1/(t+k0) - 1/(t0 + k0)))
--
-- b = log (r/r0) / (1/(t+k0) - 1/(t0 + k0))
-- 
-- log (r/r0) = b * (1/(t + k0) - 1/(t0 + k0))
-- log (r/r0) / b + 1/(t0 + k0) = 1/(t + k0)
-- t  = 1 / (log (r/r0) / b + 1/(t0 + k0) ) - k0
*/

class Thermistor {
  public:
    Thermistor(double r0, double r1, unsigned int pin);
    double readTempC(void);
  private:
    unsigned int _pin;
    double _r0, _r1;
    virtual double bConstant(double temp);
    double readResistor(void);
  protected:
    double a,b,c;
};

class Thermistor_NXFT15WF104FA2B : public Thermistor {
  public:
    Thermistor_NXFT15WF104FA2B(double r1, unsigned int pin);
};

class Thermistor_NXFT15WB473FA2B : public Thermistor {
  public:
    Thermistor_NXFT15WB473FA2B(double r1, unsigned int pin);
};

class Thermistor_103AT : public Thermistor {
  public:
    Thermistor_103AT(double r1, unsigned int pin);
  private:
    double bConstant(double);
};

#endif
