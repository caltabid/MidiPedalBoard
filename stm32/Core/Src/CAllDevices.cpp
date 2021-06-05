/*
 * AllDevices.cpp
 *
 *  Created on: May 14, 2021
 *      Author: Daniele Caltabiano
 */

#include "CAllDevices.h"
#include "main.h"
#include "usb_device.h"
#include "usbd_midi_if.h"
#include "CAllDevices.h"

CAllDevices::CAllDevices()
{
  int i;

  uint8_t StompCCvalues[2][9] = {
    {51, 52, 53, 54, 55, 56, 57, 58, 59}, // standard stomps
    {61, 62, 63, 64, 65, 66, 67, 68, 69}, // Looper control (undo, play once, pre/post, rec/overdub, play/stop, 1/2 speed, reverse
  };
  uint8_t ExpCCvalues[2] = {16, 17};
  uint8_t PotCCvalues[8] = {18, 19, 20, 21, 22, 23, 24, 0};
  this->StompLooper.Init(StompBtn05_GPIO_Port, StompBtn05_Pin, StompLED05_GPIO_Port, StompLED05_Pin, 0, 0, 0, 0);

  this->StompsL1[0].Init(StompBtn01_GPIO_Port, StompBtn01_Pin, StompLED01_GPIO_Port, StompLED01_Pin, StompCCvalues[0][0], 0, 0, 0);
  this->StompsL1[1].Init(StompBtn02_GPIO_Port, StompBtn02_Pin, StompLED02_GPIO_Port, StompLED02_Pin, StompCCvalues[0][1], 0, 0, 0);
  this->StompsL1[2].Init(StompBtn03_GPIO_Port, StompBtn03_Pin, StompLED03_GPIO_Port, StompLED03_Pin, StompCCvalues[0][2], 0, 0, 0);
  this->StompsL1[3].Init(StompBtn04_GPIO_Port, StompBtn04_Pin, StompLED04_GPIO_Port, StompLED04_Pin, StompCCvalues[0][3], 0, 0, 0);
  this->StompsL1[4].Init(StompBtn06_GPIO_Port, StompBtn06_Pin, StompLED06_GPIO_Port, StompLED06_Pin, StompCCvalues[0][4], 0, 0, 0);
  this->StompsL1[5].Init(StompBtn07_GPIO_Port, StompBtn07_Pin, StompLED07_GPIO_Port, StompLED07_Pin, StompCCvalues[0][5], 0, 0, 0);
  this->StompsL1[6].Init(StompBtn08_GPIO_Port, StompBtn08_Pin, StompLED08_GPIO_Port, StompLED08_Pin, StompCCvalues[0][6], 0, 0, 0);
  this->StompsL1[7].Init(StompBtn09_GPIO_Port, StompBtn09_Pin, StompLED09_GPIO_Port, StompLED09_Pin, StompCCvalues[0][7], 0, 0, 0);
  this->StompsL1[8].Init(StompBtn10_GPIO_Port, StompBtn10_Pin, StompLED10_GPIO_Port, StompLED10_Pin, StompCCvalues[0][8], 0, 0, 0);

  this->StompsL2[0].Init(StompBtn01_GPIO_Port, StompBtn01_Pin, StompLED01_GPIO_Port, StompLED01_Pin, StompCCvalues[1][0], 0, 0, 0);
  this->StompsL2[1].Init(StompBtn02_GPIO_Port, StompBtn02_Pin, StompLED02_GPIO_Port, StompLED02_Pin, StompCCvalues[1][1], 0, 0, 0);
  this->StompsL2[2].Init(StompBtn03_GPIO_Port, StompBtn03_Pin, StompLED03_GPIO_Port, StompLED03_Pin, StompCCvalues[1][2], 0, 0, 0);
  this->StompsL2[3].Init(StompBtn04_GPIO_Port, StompBtn04_Pin, StompLED04_GPIO_Port, StompLED04_Pin, StompCCvalues[1][3], 0, 0, 0);
  this->StompsL2[4].Init(StompBtn06_GPIO_Port, StompBtn06_Pin, StompLED06_GPIO_Port, StompLED06_Pin, StompCCvalues[1][4], 0, 0, 1);
  this->StompsL2[5].Init(StompBtn07_GPIO_Port, StompBtn07_Pin, StompLED07_GPIO_Port, StompLED07_Pin, StompCCvalues[1][5], 0, 0, 1);
  this->StompsL2[6].Init(StompBtn08_GPIO_Port, StompBtn08_Pin, StompLED08_GPIO_Port, StompLED08_Pin, StompCCvalues[1][6], 0, 0, 1);
  this->StompsL2[7].Init(StompBtn09_GPIO_Port, StompBtn09_Pin, StompLED09_GPIO_Port, StompLED09_Pin, StompCCvalues[1][7], 0, 0, 1);
  this->StompsL2[8].Init(StompBtn10_GPIO_Port, StompBtn10_Pin, StompLED10_GPIO_Port, StompLED10_Pin, StompCCvalues[1][8], 0, 0, 1);

  this->LedMain.Init(LD_PWR_GPIO_Port, LD_PWR_Pin);
  this->LedMain.Set(0, 1000, 200);
  this->ADCbuffer = getADCbuffer();

  for (i=0; i<8; i++) {
    this->Pot[i].Init(&this->ADCbuffer[2+i], PotCCvalues[i]);
  }
  this->Exp[0].Init(GPIOB, GPIO_PIN_0, LD_Exp1_GPIO_Port, LD_Exp1_Pin, &this->ADCbuffer[0], ExpCCvalues[0]);
  this->Exp[1].Init(GPIOB, GPIO_PIN_1, LD_Exp2_GPIO_Port, LD_Exp2_Pin, &this->ADCbuffer[1], ExpCCvalues[1]);
}

CAllDevices::~CAllDevices()
{
}

void CAllDevices::Update(void)
{
  int i, Mode, StompPolarity, EnablePot;
  CStompBtn *ActiveLayer;

  //Wait USB configuration when USB connection error has occurred.
  if(USBD_STATE_CONFIGURED != hUsbDeviceFS.dev_state) {
    this->LedMain.Set(0, 400, 200);
    while(1){
      HAL_Delay(1);
      this->LedMain.Update();
      if(USBD_STATE_CONFIGURED == hUsbDeviceFS.dev_state) {
        this->LedMain.Set(0, 1000, 200);
        break;
      }
    }
  }

  this->Exp[0].Prepare();
  this->Exp[1].Prepare();
  this->StompLooper.Update(0);
  if (this->StompLooper.GetState()) {
    ActiveLayer=this->StompsL2;
  } else {
    ActiveLayer=this->StompsL1;
  }
  Pot[7].Update();
  Mode = Pot[7].GetState();
  StompPolarity = Mode>=64;
  EnablePot = (Mode<10) || (Mode>117);
  for (i=0; i<9; i++) {
    if (ActiveLayer[i].Update(StompPolarity)) this->LedMain.Pulse();
  }
  if (EnablePot) {
    for (i=0; i<7; i++) {
      if (Pot[i].Update()) this->LedMain.Pulse();
    }
  }
  if (Exp[0].Update()) this->LedMain.Pulse();
  if (Exp[1].Update()) this->LedMain.Pulse();
  this->LedMain.Update();
  USBD_MIDI_SendPacket();

  if( FUNC_SUCCESS == midiGetFromUsbRx(0, &uart_tx_dat) ) {
    this->LedMain.Pulse();

    //      while(!isUartReady[cable_num]);
    //      sendUart(cable_num, &uart_tx_dat);
  }
}


