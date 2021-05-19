/*
 * PwmLed.h
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#ifndef SRC_PWMLED_H_
#define SRC_PWMLED_H_

#include "stm32f4xx_hal.h"

class CPwmLed
{
protected:
  GPIO_TypeDef *LedPort;
  uint16_t LedPin;
  int Mode, Period, Duty;
  int Pulses, CountPulse, CountPeriod;
public:
  CPwmLed();
  virtual ~CPwmLed();
  void Init(GPIO_TypeDef *LedPort, uint16_t LedPin);
  void Set(int Mode, int Period, int Duty); // Mode: 0 for PWM, 1 for oneShot
  void Pulse(void); // send one pulse of Duty Cycles (if mode=1)
  void Update(void);
};

#endif /* SRC_PWMLED_H_ */
