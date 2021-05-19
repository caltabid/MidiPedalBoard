/*
 * CDebounce.h
 *
 *  Created on: May 14, 2021
 *      Author: caltabid
 */

#ifndef SRC_CDEBOUNCE_H_
#define SRC_CDEBOUNCE_H_

class CDebounce
{
private:
  int current_tick, reload;
  int oldValue;
public:
  CDebounce();
  virtual ~CDebounce();
  void Init(int ticks, int oldValue);
  int GetDebouncedNewValue(int NewValue);
};

#endif /* SRC_CDEBOUNCE_H_ */
