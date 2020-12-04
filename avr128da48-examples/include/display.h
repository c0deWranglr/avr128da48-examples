/*
 * display.h
 *
 * Created: 12/3/2020 8:12:43 PM
 *  Author: j0jen
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_


#include "config.h"

#include "OLEDC_Click.h"
#include "OLEDC_shapes.h"
//#include "OLEDC_colors.h"

#define UPPER                           96
#define LOWER                           0
#define BACKGROUND						0x0000

void display_init(void);
void clear_screen(void);

#endif /* DISPLAY_H_ */