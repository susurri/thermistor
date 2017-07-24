#include <Thermistor.h>

Thermistor::Thermistor(double r0, double r1, unsigned int pin) {
  _r0 = r0;
  _r1 = r1;
  _pin = pin;
  analogReference(EXTERNAL);
}

// Murata
Thermistor_NXFT15WF104FA2B::Thermistor_NXFT15WF104FA2B(double r1, unsigned int pin) : Thermistor(100.0, r1, pin) {
  a = -0.00409482;
  b = 2.29587;
  c = 4145.26;
}

Thermistor_NXFT15WB473FA2B::Thermistor_NXFT15WB473FA2B(double r1, unsigned int pin) : Thermistor(47.0, r1, pin) {
  a = -0.00298036;
  b = 2.06953;
  c = 3953.96;
}

//Semitec 103AT
Thermistor_103AT::Thermistor_103AT(double r1, unsigned int pin) : Thermistor(10.0, r1, pin) {
//  a = -0.00885594;
//  b = 2.76635;
//  c = 3266.09;
}

double Thermistor::bConstant(double t) {
  return (a * t * t + b * t + c);
}

double Thermistor_103AT::bConstant(double t) {
  double a = 2.81169e-05;
  double b = -0.0113725;
  double c = 2.72286;
  double d = 3268.96;
  return (a * t * t * t + b * t * t + c * t + d);
}

double Thermistor::readTempC(void) {
  double t, t_prev, delta_t;
  double k0 = 273.15;
  double t0 = 25.0;
  int i;

  double r = readResistor();

  t  = 1 / (log (r/_r0) / bConstant(t0) + 1/(t0 + k0) ) - k0;
  for( i = 0; i < 100; i++) {
#ifdef DEBUG
    Serial.print("temperature iteration: ");
    Serial.println(t);
#endif
    t_prev = t;
    t  = 1 / (log (r/_r0) / bConstant(t_prev) + 1/(t0 + k0) ) - k0;
    delta_t = t - t_prev;
    if (-0.01 < delta_t && delta_t < 0.01) break;
  } 
  return t;
}

double Thermistor::readResistor() {
  int val;
  double v_ratio, r;
  val = analogRead(_pin);
  v_ratio = (double)val / (1 << ADC_BITS);
  r = v_ratio * _r1 / (1 - v_ratio);
#ifdef DEBUG
    Serial.print("analogRead: ");
    Serial.println(val);
    Serial.print("v_ratio: ");
    Serial.println(v_ratio, 6);
    Serial.print("r: ");
    Serial.println(r);
#endif
  return r;
// r/(r1 + r) * Vref = V
// r * Vref = V * (r1 + r)
// r = (V/Vref) * (r1 + r)
// r * (1 - V/Vref) = V/Vref * r1
// r = (V/Vref * r1)/(1 - V/Vref)
// V/Vref = val / 1024
// Vratio := V/vref = val / 1024
// r = Vratio * r1 / (1 - Vratio)
}
