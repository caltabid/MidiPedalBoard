/*
 * CFIR.h
 *
 *  Created on: May 15, 2021
 *      Author: caltabid
 */

#ifndef SRC_CFIR_H_
#define SRC_CFIR_H_

#define FIR_STAGES 50

class CFIR
{
protected:
  int Initialized;
  int oldValues[FIR_STAGES];
public:
  CFIR();
  virtual ~CFIR();
  int Update(int NewValue);
};

#endif /* SRC_CFIR_H_ */
