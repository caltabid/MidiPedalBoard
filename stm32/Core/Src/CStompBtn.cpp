/*
 * CStompBtn.cpp
 *
 *  Created on: May 14, 2021
 *      Author: Daniele Caltabiano
 */

#include "CStompBtn.h"
#include "midilib.h"

CStompBtn::CStompBtn()
{
}

CStompBtn::~CStompBtn()
{
}

void CStompBtn::Init(GPIO_TypeDef *BtnPort, uint16_t BtnPin, GPIO_TypeDef *LedPort, uint16_t LedPin, uint8_t CC, uint8_t OldValue, uint8_t State)
{
  this->BtnPort  = BtnPort ;
  this->BtnPin   = BtnPin  ;
  this->LedPort  = LedPort ;
  this->LedPin   = LedPin  ;
  this->CC       = CC      ;
  this->OldValue = OldValue;
  this->State    = State   ;
  this->Debounce.Init(100, 0);
}

int CStompBtn::Update(int Polarity) // 0: active, 1: bypass
{
  int NewValue, CurrentValue, ret=0, Command;

  NewValue = !HAL_GPIO_ReadPin(this->BtnPort, this->BtnPin); // Btn pin is pulled up at Vdd
  CurrentValue = this->Debounce.GetDebouncedNewValue(NewValue);
  if ((CurrentValue != this->OldValue)) {
    if (CurrentValue) { // rising edge
      this->State = !this->State; // toggle state
      if (this->CC>0) {
        Command = Polarity?!this->State:this->State;
        sendMidiCC(0, this->CC, 127*Command);
      }
      ret=1;
    }
    this->OldValue = CurrentValue;
  }
  HAL_GPIO_WritePin(this->LedPort, this->LedPin, (GPIO_PinState)this->State); // always refresh led status
  return ret;
}

int CStompBtn::GetState(void)
{
  return this->State;
}
