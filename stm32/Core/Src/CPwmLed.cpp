/*
 * PwmLed.cpp
 *
 *  Created on: May 14, 2021
 *      Author: Daniele Caltabiano
 */

#include <CPwmLed.h>

CPwmLed::CPwmLed()
{
}

CPwmLed::~CPwmLed()
{
}

void CPwmLed::Init(GPIO_TypeDef *LedPort, uint16_t LedPin)
{
  this->LedPort=LedPort;
  this->LedPin=LedPin;
  this->Mode=1;
  this->Period=0;
  this->Duty=0;
  this->Pulses=0;
  this->CountPulse=0;
  this->CountPeriod=0;
}

void CPwmLed::Set(int Mode, int Period, int Duty) // Mode: 0 for PWM, 1 for oneShot
{
  this->Mode=Mode;
  this->Period=Period;
  this->Duty=Duty;
  this->Pulses=0;
  this->CountPulse=0;
  this->CountPeriod=0;
}

void CPwmLed::Pulse(void) // send one pulse of Duty Cycles
{
  this->Pulses=1;
  this->CountPulse=0;
  this->CountPeriod=0;
}

void CPwmLed::Update(void)
{
  if (this->Pulses) {
    this->CountPulse++;
    HAL_GPIO_WritePin(this->LedPort, this->LedPin, (GPIO_PinState)(this->CountPulse<this->Duty));
    if (this->CountPulse>2*this->Duty) {
      this->Pulses--;
      this->CountPulse=0;
    }
  }
  if (this->Mode==0) {
    this->CountPeriod++;
    if (this->CountPeriod>=this->Period) {
      this->CountPeriod=0;
      this->Pulse();
    }
  }

}
