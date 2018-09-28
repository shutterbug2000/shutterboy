//shutterboy2000 ROM handler

#include <stdlib.h>
#include <stdio.h>

#include "rom.h"

FILE* romfile;

//Open rom
void openRom(char* name){
	romfile = fopen(name,"rb");
	fseek(romfile, 0L, SEEK_END);
	romsize=ftell(romfile);
	rewind(romfile);
	romdata = malloc(romsize);
	memset(romdata,1,romsize);
	fread(romdata,1,romsize,romfile);
	//printf("%x",romdata[0x102]);
}

//Read a byte from ROM
unsigned char readRom(unsigned short position){
	//printf("%x\n",position);
	//printf("%x\n",romdata[position]);
	return romdata[position];
}