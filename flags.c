//shutterboy flag handler

#include "cpu.h"

void flagset(unsigned char flags){
	F |= flags;
}

void flagclear(unsigned char flags){
	F &= ~flags;
}

unsigned char flagget(unsigned char flags){
	return (F & flags) ? 1 : 0;
}