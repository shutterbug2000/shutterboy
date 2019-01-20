//shutterboy2000 memory handler

#include "memory.h"
#include "rom.h"
#include "cpu.h"

//read byte
unsigned char readByte(unsigned short position){
	switch(position){
		case 0x0000 ... 0x3FFF:{
			return readRom(position);
			break;
		}
		case 0x4000 ... 0x7FFF:{
			//printf("%x\n",readRom(position));
			return readRom(position);
			break;
		}
		case 0x8000 ... 0xBFFF:{
            //printf("AAAA: %x %x",PC,readByte(PC));
            return 0;
		}
		case 0xC000 ... 0xDFFF:{
			return wram[position-0xC000];
			break;
		}
		case 0xE000 ... 0xFDFF:{
			return wram[position-0xE000];
			break;
		}
		case 0xFE00 ... 0xFE9F:{
            //printf("AAAA: %x %x",PC,readByte(PC));
            return 0;
		}
		case 0xFF44:{
			return 0x90;
			break;
		}
		case 0xFF80 ... 0xFFFE:{
			return hram[position-0xFF80];
			break;
		}
		/* case 0xFF00 ... 0xFFFF:{
			printf("Unhandled read region: %x\n",position);
			system("pause");
			break;
		} */
		default:{
			printf("Unknown read region: %x\nCurrent PC: %x",position, PC);
			exit(0);
			return 0xFF;
		}
	}
}

unsigned short readWord(unsigned short position){
	switch(position){
		case 0x0000 ... 0x3FFF:{
			return (readRom(position+1)<<8) | readRom(position);
			break;
		}
		case 0x4000 ... 0x7FFF:{
			//printf("%x\n",readRom(position));
			return (readRom(position+1)<<8) | readRom(position);
			break;
		}
		case 0xC000 ... 0xDFFF:{
			return (wram[(position-0xC000)+1]<<8) | wram[position-0xC000];
			break;
		}
		case 0xFF31 ... 0xFF32:{
			return 0xFFFF;
			break;
		}
		case 0xFF44:{
			return 0x9090;
			break;
		}
		case 0xFF80 ... 0xFFFE:{
			return (hram[(position-0xFF80)+1]<<8) | hram[position-0xFF80];
			break;
		}
		/* case 0xFF00 ... 0xFFFF:{
			printf("Unhandled read region: %x\n",position);
			system("pause");
			break;
		} */
		default:{
			printf("Unknown read region: %x",position);
			exit(0);
			return 0xFF;
		}
	}
}

//write byte
unsigned char writeByte(unsigned short  position, unsigned char value){
	switch(position){
		case 0x0000 ... 0x3FFF:{
			//wram[position]=value;
			printf("Write to %x is not supported!",position);
			exit(0);
			break;
		}
		case 0x8000 ... 0x9FFF:{
			//wram[position]=value;
			//printf("Video is NOT emulated!");
			break;
		}
		case 0xC000 ... 0xDFFF:{
			wram[position-0xC000]=value;
			break;
		}
 		case 0xE000 ... 0xFDFF:{
			wram[position-0xE000]=value;
			break;
		}
		case 0xFF01:{
            printf("%c",value); //FOR TEST ROMS.
            //printf("%x",PC); //FOR TESTING.
            //system("pause");
            break;
		}
		case 0xFF02:{break;}
		case 0xFF07 ... 0xFF0F:{break;}
		case 0xFF20 ... 0xFF47:{break;}
		case 0xFF80 ... 0xFFFE:{
			hram[position-0xFF80]=value;
			break;
		}
		case 0xFFFF ... 0xFFFF:{break;}
		/* case 0xFF00 ... 0xFFFF:{
			printf("Unhandled write region: %x\n",position);
			system("pause");
			break;
		} */
		default:{
			printf("Unknown write region: %x\n",position);
			exit(0);
		}
	}
}
