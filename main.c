#include "memory.h"
#include "cpu.h"
#include "rom.h"

int main(){
	//return 0;
	initCpu();

	//F = 0;
	//openRom("/home/pi/shutterboy/roms/test/cpu_instrs/individual/06-ld r,r.gb");
	openRom("c:/Users/jstok/Documents/shutterboy/shutterboy/roms/test/cpu_instrs/individual/03-op sp,hl.gb");

	while(1){
		//printf("%x\n",PC);
		//printf("%x\n",SP);
		//if(readByte(0xc01b)!=0xF6){
		//	system("pause");
		//}
		//printf("%x %x %x\n",readByte(PC),PC,SP);
		//printf("a = %x\n",A);
		//if(SP==0x8000) {printf("%x %x",PC,readByte(PC)); system("pause");}

		//if(pause) {printf("Paused: %x\n", PC); system("pause");}

		//if(PC==0xc092) {printf("%x %x\n",SP,readWord(SP)); system("pause");}
		//if(PC==0xC668) {printf("%x %x\n",HL, PC); system("pause");}
		//if(PC==0xC62E) {printf("ccccdd: %x %x\n",SP, PC); system("pause");}
		//if(PC==0xC657) {printf("cccccc: %x %x\n",readWord(0xDFEF), PC); system("pause");}
		//if(HL==2) {printf("%x %x\n",HL, PC); system("pause");}
		//if(HL==0xDFEF) {printf("ddd: %x %x\n",HL, PC); system("pause");}
		//if(HL>=0xFE90 && HL<=0xFEa0) {printf("%x %x\n",HL, PC); system("pause");}

		runOpcode();
		//runOpcode();
	}

	return 0;
}
