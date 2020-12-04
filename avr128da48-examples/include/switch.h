/*
 * switch.h
 *
 * Created: 6/7/2020 2:50:26 PM
 *  Author: j0jen
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#define SWITCH_DOWN_bm      (0x01);
#define SWITCH_ON_bm        (0x02);
#define SWITCH_CHANGE_bm    (0x04);

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

void switch_init(void);

void evaluate_press(void);

bool is_on(void);
bool is_change(void);

#ifdef __cplusplus
}
#endif

#endif /* SWITCH_H_ */