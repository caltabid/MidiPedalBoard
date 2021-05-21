/*
 * Process.h
 *
 *  Created on: 21 May 2021
 *      Author: Daniele Caltabiano
 */

#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_

#ifdef __cplusplus
  #define EXTERNC extern "C"
#else
  #define EXTERNC
#endif

EXTERNC void ProcessInit(void);
EXTERNC void ProcessExecute(void);

#endif /* INC_PROCESS_H_ */
