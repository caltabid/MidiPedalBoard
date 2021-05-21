/*
 * CPot.h
 *
 *  Created on: May 15, 2021
 *      Author: Daniele Caltabiano
 */

#ifndef SRC_CPOT_H_
#define SRC_CPOT_H_

#include "CFIR.h"
#include "stm32f4xx_hal.h"

class CPot
{
protected:
  uint16_t *pADCvalue;
  uint8_t CC;
  CFIR FIR;
  int OldValue;
  int Debounce;
public:
  CPot();
  virtual ~CPot();
  void Init(uint16_t *pADCvalue, uint8_t CC);
  int Update(void);
  int GetState(void);
};

#endif /* SRC_CPOT_H_ */
