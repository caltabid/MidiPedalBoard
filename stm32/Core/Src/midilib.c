/*
 * midilib.c
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#include "midilib.h"
#include "usb_device.h"
#include "usbd_midi_if.h"

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void sendMidiNote(uint8_t noteOnOff, uint8_t channel, uint8_t pitch, uint8_t velocity)
{
  midiEventPacket_t MidiMsg = {0x08 | noteOnOff, 0x80 | channel, pitch, velocity};
  sendMidiMessage(&MidiMsg.type, 4);
  USBD_MIDI_SendPacket();
}

// Event type hard-coded (0x0B = control change, aka "MIDI CC").
// First parameter is the channel (0-15), combined with the event type.
// Second parameter is the "control change" number (0-119, see top link to midi.org).
// Third parameter is the control value (0-127).

void sendMidiCC(uint8_t channel, uint8_t control, uint8_t value)
{
    midiEventPacket_t MidiMsg = {0x0B, 0xB0 | channel, control, value};
    sendMidiMessage(&MidiMsg.type, 4);
    USBD_MIDI_SendPacket();
}
