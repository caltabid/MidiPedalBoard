/*
 * CFIR.cpp
 *
 *  Created on: May 15, 2021
 *      Author: Daniele Caltabiano
 */

#include "CFIR.h"

CFIR::CFIR()
{
  Initialized=0;
}

CFIR::~CFIR()
{
}

int CFIR::Update(int NewValue)
{
  int i, acc;

  if (!this->Initialized) {
    for (i=0; i<FIR_STAGES; i++) {
      this->oldValues[i]=NewValue;
    }
    return NewValue;
  }
  acc=NewValue;
  for (i=1; i<FIR_STAGES; i++) {
    acc+=this->oldValues[i-1];
    this->oldValues[i-1]=this->oldValues[i];
  }
  acc+=this->oldValues[FIR_STAGES-1];
  this->oldValues[FIR_STAGES-1]=NewValue;
  acc/=FIR_STAGES+1;
  return acc;
}
