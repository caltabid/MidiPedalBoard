/*
 * midilib.h
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#ifndef __MIDI_LIB_H
#define __MIDI_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

typedef struct {
  uint8_t type, command_channel, pitch, velocity;
} midiEventPacket_t;

void sendMidiNote(uint8_t noteOnOff, uint8_t channel, uint8_t pitch, uint8_t velocity);
void sendMidiCC(uint8_t channel, uint8_t control, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif  /* __MIDI_LIB_H */
