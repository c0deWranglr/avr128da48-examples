/*
 * logging.h
 *
 * Created: 6/7/2020 2:50:54 PM
 *  Author: j0jen
 */ 


#ifndef LOGGING_H_
#define LOGGING_H_

#define USART1_BAUD_RATE(BAUD_RATE)     ((float)(64 * 4000000 / (16 * (float)BAUD_RATE)) + 0.5)

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

void logging_init(void);

void log_char(char c);

void log_str(char *str);


#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H_ */