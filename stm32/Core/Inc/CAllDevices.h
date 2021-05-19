/*
 * AllDevices.h
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#ifndef SRC_CALLDEVICES_H_
#define SRC_CALLDEVICES_H_

#include "CStompBtn.h"
#include <CPwmLed.h>
#include "CPot.h"
#include "CExp.h"

class CAllDevices
{
protected:
  CStompBtn StompLooper;
  CStompBtn StompsL1[9];
  CStompBtn StompsL2[9];
  CPot Pot[8];
  CExp Exp[2];
  CPwmLed LedMain;
  uint8_t uart_tx_dat;
  uint16_t *ADCbuffer;
public:
  CAllDevices();
  virtual ~CAllDevices();
  void Update(void);
};

#endif /* SRC_CALLDEVICES_H_ */
