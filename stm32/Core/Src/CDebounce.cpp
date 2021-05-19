/*
 * CDebounce.cpp
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#include "CDebounce.h"

CDebounce::CDebounce()
{
}

CDebounce::~CDebounce()
{
}

void CDebounce::Init(int ticks, int oldValue)
{
  this->current_tick=0;
  this->reload=ticks;
  this->oldValue=oldValue;
}

int CDebounce::GetDebouncedNewValue(int NewValue)
{
  if (this->current_tick) { // debounce
    this->current_tick--;
  } else if (NewValue != this->oldValue) { // update new value
    this->oldValue=NewValue;
    this->current_tick=this->reload;
  }
  return this->oldValue;
}
