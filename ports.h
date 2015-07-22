//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __PORTS_H
#define __PORTS_H

enum Ports
{
    PortA,
    PortB
};

void init_hw();

void set_port(int port, int id);
void reset_port(int port, int id);
int get_port(int port, int id);



//--------------------------------------------------------------
#endif 
