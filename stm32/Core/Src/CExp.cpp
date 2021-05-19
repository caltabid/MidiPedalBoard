/*
 * CExp.cpp
 *
 *  Created on: May 15, 2021
 *      Author: caltabid
 */

#include "CExp.h"
#include "midilib.h"

#define DEBOUNCE_RELOAD 50;
#define abs(x) (((x)>0)?(x):-(x))

CExp::CExp()
{
  this->OldValue=0;
  this->Debounce = 0;
}

CExp::~CExp()
{
}

void CExp::Init(GPIO_TypeDef *ADCPort, uint16_t ADCPin, GPIO_TypeDef *LedPort, uint16_t LedPin, uint16_t *pADCvalue, uint8_t CC)
{
  this->ADCPort=ADCPort;
  this->ADCPin =ADCPin ;
  this->LedPort=LedPort;
  this->LedPin =LedPin ;
  this->pADCvalue=pADCvalue;
  this->CC=CC;
}

void CExp::Prepare(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  this->NewValue = *this->pADCvalue;
  /*Configure As input pull down */
  GPIO_InitStruct.Pin = this->ADCPin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(this->ADCPort, &GPIO_InitStruct);
  HAL_GPIO_WritePin(this->LedPort, this->LedPin, (GPIO_PinState)1); // LED high (and also off)
}

int CExp::Update(void)
{
  int NewValue, Activated;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  Activated=HAL_GPIO_ReadPin(this->ADCPort, this->ADCPin);
  if (Activated==1) { // jack is inserted
     HAL_GPIO_WritePin(this->LedPort, this->LedPin, (GPIO_PinState)0); // LED on
  }
  /* Reset channel to ADC */
  GPIO_InitStruct.Pin = this->ADCPin;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(this->ADCPort, &GPIO_InitStruct);
  if (this->Debounce) {
    this->Debounce--;
  }
  if (Activated) {
    NewValue = this->FIR.Update(this->NewValue);
    if ((abs(this->OldValue - NewValue)>16) && (this->OldValue>>5 != NewValue>>5) && (this->Debounce==0)) {
      sendMidiCC(0, this->CC, NewValue>>5); // 12 to 7 bit conversion
      this->OldValue = NewValue;
      this->Debounce = DEBOUNCE_RELOAD;
      return 1;
    }
  }
  return 0;
}
