/*
 * CPot.cpp
 *
 *  Created on: May 15, 2021
 *      Author: caltabid
 */

#include "CPot.h"
#include "midilib.h"

#define DEBOUNCE_RELOAD 50;
#define abs(x) (((x)>0)?(x):-(x))

CPot::CPot()
{
  this->OldValue=0;
  this->Debounce = 0;
}

CPot::~CPot()
{
}

void CPot::Init(uint16_t *pADCvalue, uint8_t CC)
{
  this->pADCvalue=pADCvalue;
  this->CC=CC;
}

int CPot::Update(void)
{
  int NewValue;

  if (this->Debounce) {
    this->Debounce--;
  }
  NewValue = *(this->pADCvalue);
  NewValue = this->FIR.Update(NewValue);
  if ((abs(this->OldValue - NewValue)>16) && (this->OldValue>>5 != NewValue>>5) && (this->Debounce==0)) {
    if (this->CC) {
      sendMidiCC(0, this->CC, NewValue>>5); // 12 to 7 bit conversion
    }
    this->OldValue = NewValue;
    this->Debounce = DEBOUNCE_RELOAD;
    return 1;
  }
  return 0;
}

int CPot::GetState(void)
{
  return this->OldValue>>5;
}
