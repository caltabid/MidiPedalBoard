/*
 * CStompBtn.h
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#ifndef SRC_CSTOMPBTN_H_
#define SRC_CSTOMPBTN_H_

#include "CDebounce.h"
#include "stm32f4xx_hal.h"


class CStompBtn
{
protected:
  CDebounce Debounce;
  GPIO_TypeDef *BtnPort;
  uint16_t BtnPin;
  GPIO_TypeDef *LedPort;
  uint16_t LedPin;
  uint8_t CC;
  uint8_t OldValue, State;
public:
  CStompBtn();
  virtual ~CStompBtn();
  void Init(GPIO_TypeDef *BtnPort, uint16_t BtnPin, GPIO_TypeDef *LedPort, uint16_t LedPin, uint8_t CC, uint8_t OldValue, uint8_t State);
  int Update(int Polarity);
  int GetState(void);
};

#endif /* SRC_CSTOMPBTN_H_ */