//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __PORTS_H
#define __PORTS_H

#include <stm32f4xx_gpio.h>
#include "defines.h"

/*
enum Ports
{
    PortA,
    PortB,
    PortC
};
*/

typedef GPIO_TypeDef * PortType;
void init_hw();

void set_port(PortType port, int id);
void reset_port(PortType port, int id);
int get_port(PortType port, int id);



//--------------------------------------------------------------
#endif 
