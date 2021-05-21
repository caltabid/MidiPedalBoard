/*
 * Process.cpp
 *
 *  Created on: 21 May 2021
 *      Author: Daniele Caltabiano
 */



#include "Process.h"
#include "CAllDevices.h"

CAllDevices AllDevices;

void ProcessInit(void)
{

}

void ProcessExecute(void)
{
  AllDevices.Update();
}
