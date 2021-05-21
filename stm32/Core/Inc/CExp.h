/*
 * CExp.h
 *
 *  Created on: May 15, 2021
 *      Author: Daniele Caltabiano
 */

#ifndef SRC_CEXP_H_
#define SRC_CEXP_H_

#include "CFIR.h"
#include "stm32f4xx_hal.h"

class CExp
{
protected:
  GPIO_TypeDef *ADCPort, *LedPort;
  uint16_t ADCPin, LedPin;
  uint16_t *pADCvalue;
  uint8_t CC;
  CFIR FIR;
  int NewValue, OldValue, Debounce;
public:
  CExp();
  virtual ~CExp();
  void Init(GPIO_TypeDef *ADCPort, uint16_t ADCPin, GPIO_TypeDef *LedPort, uint16_t LedPin, uint16_t *pADCvalue, uint8_t CC);
  void Prepare(void);
  int Update(void);
};

#endif /* SRC_CEXP_H_ */
