//shutterboy2000 CPU

#include "cpu.h"
#include "memory.h"
#include "flags.h"

void initCpu(){
	AF=0x1B0;
	BC=0x0013;
	DE=0x00D8;
	HL=0x014D;
	SP=0xFFFE;
	PC=0x0100;

	interrupts = 1;
}

void load16(union Register *reg, unsigned short value){
	reg->reg=value;
//	reg->hi = readByte(value & 0xff);
}

void load8(unsigned char *reg, unsigned char value){
	////printf("a %x\n",value);
	*reg=value;
	////printf("b %x\n",reg);
//	reg->hi = readByte(value & 0xff);
}

void jump(unsigned short value){
	//printf("%x",value);
	//system("pause");
	PC=value;
}

void jumpR(signed char value){
	PC+=value;
	PC+=2;
}

void inc16(unsigned short *reg){
	*reg+=1;
}

void dec16(unsigned short *reg){
	*reg-=1;
}

void inc8(unsigned char *reg){
	//printf("aa %x\n",*reg);
	//printf("aa %x\n",E);
	*reg+=1;

	if((*reg & 0xf) == 0){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

	//printf("ab %x\n",*reg);
	//printf("aa %x\n",E);
	if(*reg==0){
		flagset(ZFLAG);
		//printf("%x\n",F);
		//printf("%x\n",flagget(ZFLAG));
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagclear(NFLAG);

}

void incMem(unsigned short position){
	//printf("aa %x\n",*reg);
	//printf("aa %x\n",E);
	unsigned char value = readByte(position);
	value++;

	if((value & 0xf) == 0){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

    writeByte(position,value);
	//printf("ab %x\n",*reg);
	//printf("aa %x\n",E);
	if(value==0){
		flagset(ZFLAG);
		//printf("%x\n",F);
		//printf("%x\n",flagget(ZFLAG));
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagclear(NFLAG);

}

void decMem(unsigned short position){
	//printf("aa %x\n",*reg);
	//printf("aa %x\n",E);
	unsigned char value = readByte(position);
	value--;

	if((value & 0xf) == 0xf){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

    writeByte(position,value);
	//printf("ab %x\n",*reg);
	//printf("aa %x\n",E);
	if(value==0){
		flagset(ZFLAG);
		//printf("%x\n",F);
		//printf("%x\n",flagget(ZFLAG));
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagclear(NFLAG);

}

void dec8(unsigned char *reg){
	//printf("aa %x\n",*reg);

	*reg-=1;

	if((*reg & 0xf) == 0xf){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

	//printf("ab %x\n",*reg);
	//system("pause");
	if(*reg==0){
		flagset(ZFLAG);
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagset(NFLAG);

}

void sub8(unsigned char *reg, unsigned char value){
	if(*reg < value){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

    if(((*reg) & 0xf) < (value & 0xf)){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

	//printf("aa %x\n",*reg);
	*reg-=value;

	//printf("ab %x\n",*reg);
	//system("pause");
	if(*reg==0){
		flagset(ZFLAG);
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagset(NFLAG);

}

void sbc8(unsigned char *reg, unsigned char value){
    char cVal = flagget(CFLAG);

    flagclear(CFLAG | HFLAG);

	if(*reg < cVal){
		flagset(CFLAG);
	}

    if(((*reg) & 0xf) < (cVal & 0xf)){
		flagset(HFLAG);
	}

	if((*reg - cVal) < value){
		flagset(CFLAG);
	}

    if(((*reg - cVal) & 0xf) < (value & 0xf)){
		flagset(HFLAG);
	}


	//printf("aa %x\n",*reg);
	*reg = (*reg - value - cVal);

	//printf("ab %x\n",*reg);
	//system("pause");
	if(*reg==0){
		flagset(ZFLAG);
		//exit(0);
	}else{
		flagclear(ZFLAG);
	}

	flagset(NFLAG);

}

void cmp8(unsigned char *reg, unsigned char value){

	flagclear(ZFLAG | HFLAG | CFLAG);

	flagset(NFLAG);

	if(((*reg) & 0xf) < (value & 0xf)){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

	if(*reg<value){
		flagset(CFLAG);
	}

	if(*reg==value){
		flagset(ZFLAG);
	}

}

void add(unsigned char *reg, unsigned char value){
	if((unsigned short)(*reg+value) > 0xFF){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	if(((*reg & 0xf)+(value & 0xf)) > 0xF){
		flagset(HFLAG);
	}else{
		flagclear(HFLAG);
	}

	*reg+=value;

	if(*reg==0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}

	flagclear(NFLAG);

}

void adc8(unsigned char *reg, unsigned char value){
    char cVal = flagget(CFLAG);

    flagclear(CFLAG | HFLAG);

	if((unsigned short)(*reg+(value+cVal)) > 0xFF){
		flagset(CFLAG);
	}

	if(((*reg+cVal & 0xf)+((value) & 0xf)) > 0xF){
		flagset(HFLAG);
	}

	if((unsigned short)(*reg+cVal) > 0xFF){
		flagset(CFLAG);
	}

	if(((*reg & 0xf)+(cVal & 0xf)) > 0xF){
		flagset(HFLAG);
	}

	*reg+=(value+cVal);

	if(*reg==0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}

	flagclear(NFLAG);

}

void add16(unsigned short *reg, unsigned short value){
    if(((*reg & 0xfff) + (value & 0xfff)) > 0xfff){
        flagset(HFLAG);
    }else{
        flagclear(HFLAG);
    }

	if((unsigned int)(*reg+value) > 0xFFFF){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	*reg+=value;

	flagclear(NFLAG);

}

void and(unsigned char *reg, unsigned char value){

	flagclear(NFLAG | CFLAG);

	flagset(HFLAG);

	*reg &= value;

	if(*reg==0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}

}

void xor(unsigned char *reg, unsigned char value){

	flagclear(NFLAG | CFLAG | HFLAG);

	*reg ^= value;

	if(*reg==0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}

}

void or(unsigned char *reg, unsigned char value){

	flagclear(NFLAG | CFLAG | HFLAG);

	*reg |= value;

	if(*reg==0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}

}

void pushStack16(unsigned short value){
	SP-=2;
	writeByte(SP+1, value>>8);
	writeByte(SP, value & 0xff);
}

unsigned short popStack16(){
	unsigned short ret = readWord(SP);
	SP+=2;
	return ret;
}

void call(unsigned short value){
	pushStack16(PC+3);
	PC=value;
}

void callConditional(unsigned short value, unsigned char flag, unsigned char compare){
    if(flagget(flag) == compare){
        pushStack16(PC+3);
        PC=value;
    }else{
        PC+=3;
    }
}

void ret(){
	PC=popStack16();
}

void shl(unsigned char* value){
	if(*value & 0x1){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = *value >> 1;

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void bit(unsigned char* value, unsigned char bit){

	flagclear(NFLAG);
	flagset(HFLAG);

	if((*value & (1 << bit)) == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void resetBit(unsigned char* value, unsigned char bit){
	*value &= ~(1 << bit);
}

void setBit(unsigned char* value, unsigned char bit){
	*value |= (1 << bit);
}

void rr(unsigned char* value){
    char cVal = flagget(CFLAG) << 7;

    if(*value & 1){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = *value >> 1;

	*value = *value | cVal;

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void rl(unsigned char* value){
    char cVal = flagget(CFLAG);

    if(*value & 0x80){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = *value << 1;

	*value = *value | cVal;

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void sla(unsigned char* value){
    if(*value & 0x80){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = *value << 1;

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void sra(unsigned char* value){
    if(*value & 0x1){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

    char tmp = (*value & 0x80);

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = *value >> 1;

	*value |= tmp;

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void rlc(unsigned char* value){
    if(*value & 0x80){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = ((*value << 1) | (*value >> 7));

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void rrc(unsigned char* value){
    if(*value & 1){
		flagset(CFLAG);
	}else{
		flagclear(CFLAG);
	}

	flagclear(NFLAG);
	flagclear(HFLAG);

	*value = ((*value >> 1) | (*value << 7));

	if(*value == 0){
		flagset(ZFLAG);
	}else{
		flagclear(ZFLAG);
	}
}

void swap(unsigned char *reg){
    flagclear(NFLAG | CFLAG | HFLAG);

    //this shouldn't matter, the only way to get 0 by swapping is to swap a 0.
    if(*reg == 0){
        flagset(ZFLAG);
    }else{
        flagclear(ZFLAG);
    }

    //printf("1: %x\n", *reg);
	*reg = (*reg << 4) | ((*reg & 0xf0) >> 4);
	//printf("2: %x\n", *reg);
}

//execute opcode
void runOpcode(){
	switch(readByte(PC)){

		case 0x0:{
			PC++;
			////printf("a");
			break;
		}

		case 0x1:{
			load16(&BC,readWord(PC+1));
			PC+=3;
			break;
		}

		case 0x2:{
			writeByte(BC,A);
			PC++;
			break;
		}

		case 0x03:{
			inc16(&BC);
			PC++;
			break;
		}

		case 0x04:{
            inc8(&B);
			PC++;
			break;
		}

		case 0x5:{
			dec8(&B);
			PC++;
			break;
		}

		case 0x6:{
			unsigned char tmp;
			load8(&B,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0x7:{
			flagclear(CFLAG | ZFLAG | NFLAG | HFLAG);
			if(A & 0x80){
				flagset(CFLAG);
			}else{
                flagclear(CFLAG);
			}
			A = ((A << 1) | (A >> 7));

			PC++;
			break;
		}

		case 0x8:{

			writeByte(readWord(PC+1)+1,SP>>8);
			writeByte(readWord(PC+1),SP & 0xff);
			//printf("ccccee: %x %x\n",SP,readWord(readWord(PC+1)));
			PC+=3;
			break;
		}

		case 0xA:{
			load8(&A,readByte(BC));
			PC++;
			break;
		}

		case 0x0C:{
			inc8(&C);
			PC++;
			break;
		}

		case 0xD:{
			dec8(&C);
			PC++;
			break;
		}

		case 0xE:{
			unsigned char tmp;
			load8(&C,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xF:{
			flagclear(CFLAG | ZFLAG | NFLAG | HFLAG);
			if(A & 1){
				flagset(CFLAG);
			}else{
                flagclear(CFLAG);
			}
			A = ((A >> 1) | (A << 7));
			PC++;
			break;
		}

		case 0x11:{
			load16(&DE,readWord(PC+1));
			//printf("%x\n",DE);
			//printf("%x\n",readByte(PC+1));
			//printf("%x\n",readByte(PC+2));
			PC+=3;
			break;
		}

		case 0x12:{
			writeByte(DE,A);
			PC++;
			break;
		}

		case 0x13:{
			inc16(&DE);
			PC++;
			break;
		}

		case 0x14:{
			inc8(&D);
			PC++;
			break;
		}

		case 0x15:{
			dec8(&D);
			PC++;
			break;
		}

		case 0x16:{
			unsigned char tmp;
			load8(&D,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0x17:{
			char tmp = A;

			A <<= 1;

			if(flagget(CFLAG)){
			A |= 1;
			}

			flagclear(CFLAG | ZFLAG | NFLAG | HFLAG);

			if(tmp & 0x80){
				flagset(CFLAG);
			}else{
                flagclear(CFLAG);
			}

			PC++;
			break;
		}

		case 0x18:{
			//printf("%x\n",F);
			jumpR(readByte(PC+1));
			//printf("%x\n",PC);
			//exit(0);
			break;
		}

		case 0x1A:{
			load8(&A,readByte(DE));
			PC++;
			break;
		}

		case 0x1C:{
			inc8(&E);
			PC++;
			break;
		}

		case 0x1D:{
			dec8(&E);
			PC++;
			break;
		}

		case 0x1E:{
			unsigned char tmp;
			load8(&E,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0x1F:{
			char tmp = A;

			A >>= 1;

			if(flagget(CFLAG)){
			A |= 0x80;
			}

			flagclear(CFLAG | ZFLAG | NFLAG | HFLAG);

			if(tmp & 1){
				flagset(CFLAG);
			}else{
                flagclear(CFLAG);
			}

			PC++;
			break;
		}

		case 0x20:{
			//printf("%x\n",F);
			if(flagget(ZFLAG)==0){
				jumpR(readByte(PC+1));
			}else{
				//exit(0);
				PC+=2;
			}
			//exit(0);
			break;
		}

		case 0x21:{
			////printf("%x\n",readByte(PC+1));
			load16(&HL,readWord(PC+1));
			//printf("%x\n",HL);
            //if(PC==0xC626) {printf("%x %x\n",HL, PC); pause=1; system("pause");}
			//exit(0);
			PC+=3;
			break;
		}

		case 0x22:{
			writeByte(HL,A);
			inc16(&HL);
			PC++;
			break;
		}

		case 0x23:{
			inc16(&HL);
			PC++;
			break;
		}

		case 0x24:{
			inc8(&H);
			PC++;
			break;
		}

		case 0x25:{
			dec8(&H);
			PC++;
			break;
		}

		case 0x26:{
			unsigned char tmp;
			load8(&H,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0x28:{
			//printf("%x\n",F);
			if(flagget(ZFLAG)==1){
				jumpR(readByte(PC+1));
			}else{
				//exit(0);
				PC+=2;
			}
			//printf("%x\n",PC);
			//exit(0);
			break;
		}

		case 0x29:{
			add16(&HL,HL);
			PC++;
			break;
		}

		case 0x2A:{
			//printf("%x\n",H);
            //printf("%x\n",L);
            //if(PC==0xC631) {printf("%x %x\n",HL, PC); system("pause");}
			load8(&A,readByte(HL));
			inc16(&HL);
			////printf("%x",A);
			//exit(0);
			PC++;
			break;
		}

		case 0x2C:{
			inc8(&L);
			PC++;
			break;
		}

		case 0x2D:{
			dec8(&L);
			PC++;
			break;
		}

		case 0x2E:{
			unsigned char tmp;
			load8(&L,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0x2F:{
			flagset(NFLAG | HFLAG);
            A = ~A;
			PC+=1;
			break;
		}

		case 0x30:{
			//printf("%x\n",F);
			if(flagget(CFLAG)==0){
				jumpR(readByte(PC+1));
			}else{
				//exit(0);
				PC+=2;
			}
			//printf("%x\n",PC);
			//exit(0);
			break;
		}

		case 0x31:{
			load16(&SP,readWord(PC+1));
			//printf("%x",SP);
			//system("pause");
			PC+=3;
			break;
		}

		case 0x32:{
			writeByte(HL,A);
			dec16(&HL);
			PC++;
			break;
		}

		case 0x33:{
			inc16(&SP);
			PC++;
			break;
		}

		case 0x34:{
			incMem(HL);
			PC++;
			break;
		}

		case 0x35:{
			decMem(HL);
			PC++;
			break;
		}

		case 0x36:{
		    printf("%x",HL);
			writeByte(HL,readByte(PC+1)); //This might be wrong.
			PC+=2;
			break;
		}

		case 0x37:{
			flagclear(NFLAG | HFLAG);
			flagset(CFLAG);
			PC+=1;
			break;
		}

		case 0x38:{
			//printf("%x\n",F);
			if(flagget(CFLAG)==1){
				jumpR(readByte(PC+1));
			}else{
				//exit(0);
				PC+=2;
			}
			//printf("%x\n",PC);
			//exit(0);
			break;
		}

		case 0x39:{
			add16(&HL,SP);
			PC++;
			break;
		}

		case 0x3A:{
			////printf("%x\n",H);
			////printf("%x\n",L);
			load8(&A,readByte(HL));
			dec16(&HL);
			////printf("%x",A);
			//exit(0);
			PC++;
			break;
		}

		case 0x3B:{
			dec16(&SP);
			PC++;
			break;
		}

		case 0x3C:{
            inc8(&A);
			PC++;
			break;
		}

		case 0x3D:{
			dec8(&A);
			PC++;
			break;
		}

		case 0x3E:{
			load8(&A,readByte(PC+1));
			PC+=2;
			break;
		}

        case 0x3F:{
            flagclear(NFLAG | HFLAG);
			if(flagget(CFLAG)){
                flagclear(CFLAG);
			}else{
                flagset(CFLAG);
			}
			PC+=1;
			break;
		}

		case 0x40:{
			load8(&B,B);
			PC++;
			break;
		}

		case 0x41:{
			load8(&B,C);
			PC++;
			break;
		}

		case 0x42:{
			load8(&B,D);
			PC++;
			break;
		}

		case 0x43:{
			load8(&B,E);
			PC++;
			break;
		}

		case 0x44:{
			load8(&B,H);
			PC++;
			break;
		}

		case 0x45:{
			load8(&B,L);
			PC++;
			break;
		}

		case 0x46:{
			load8(&B,readByte(HL));
			PC++;
			break;
		}

		case 0x47:{
			load8(&B,A);
			PC++;
			break;
		}

		case 0x48:{
			load8(&C,B);
			PC++;
			break;
		}

		case 0x49:{
			load8(&C,C);
			PC++;
			break;
		}

		case 0x4A:{
			load8(&C,D);
			PC++;
			break;
		}

		case 0x4B:{
			load8(&C,E);
			PC++;
			break;
		}

		case 0x4C:{
			load8(&C,H);
			PC++;
			break;
		}

		case 0x4D:{
			load8(&C,L);
			PC++;
			break;
		}

		case 0x4E:{
			load8(&C,readByte(HL));
			PC++;
			break;
		}

		case 0x4F:{
			load8(&C,A);
			PC++;
			break;
		}

		case 0x50:{
			load8(&D,B);
			PC++;
			break;
		}

		case 0x51:{
			load8(&D,C);
			PC++;
			break;
		}

		case 0x52:{
			load8(&D,D);
			PC++;
			break;
		}

		case 0x53:{
			load8(&D,E);
			PC++;
			break;
		}

		case 0x54:{
			load8(&D,H);
			PC++;
			break;
		}

		case 0x55:{
			load8(&D,L);
			PC++;
			break;
		}

		case 0x56:{
			load8(&D,readByte(HL));
			PC++;
			break;
		}

		case 0x57:{
			load8(&D,A);
			PC++;
			break;
		}

		case 0x58:{
			load8(&E,B);
			PC++;
			break;
		}

		case 0x59:{
			load8(&E,C);
			PC++;
			break;
		}

		case 0x5A:{
			load8(&E,D);
			PC++;
			break;
		}

		case 0x5B:{
			load8(&E,E);
			PC++;
			break;
		}

		case 0x5C:{
			load8(&E,H);
			PC++;
			break;
		}

		case 0x5D:{
			load8(&E,L);
			PC++;
			break;
		}

		case 0x5E:{
			load8(&E,readByte(HL));
			PC++;
			break;
		}

		case 0x5F:{
			load8(&E,A);
			PC++;
			break;
		}

		case 0x60:{
			load8(&H,B);
			PC++;
			break;
		}

		case 0x61:{
			load8(&H,C);
			PC++;
			break;
		}

		case 0x62:{
			load8(&H,D);
			PC++;
			break;
		}

		case 0x63:{
			load8(&H,E);
			PC++;
			break;
		}

		case 0x64:{
			load8(&H,H);
			PC++;
			break;
		}

		case 0x65:{
			load8(&H,L);
			PC++;
			break;
		}

		case 0x66:{
			load8(&H,readByte(HL));
			PC++;
			break;
		}

		case 0x67:{
			load8(&H,A);
			PC++;
			break;
		}

		case 0x68:{
			load8(&L,B);
			PC++;
			break;
		}

		case 0x69:{
			load8(&L,C);
			PC++;
			break;
		}

		case 0x6A:{
			load8(&L,D);
			PC++;
			break;
		}

		case 0x6B:{
			load8(&L,E);
			PC++;
			break;
		}

		case 0x6C:{
			load8(&L,H);
			PC++;
			break;
		}

		case 0x6D:{
			load8(&L,L);
			PC++;
			break;
		}

		case 0x6E:{
			load8(&L,readByte(HL));
			PC++;
			break;
		}

		case 0x6F:{
			load8(&L,A);
			PC++;
			break;
		}

		case 0x70:{
			writeByte(HL,B);
			PC++;
			break;
		}

		case 0x71:{
			writeByte(HL,C);
			PC++;
			break;
		}

		case 0x72:{
			writeByte(HL,D);
			PC++;
			break;
		}

		case 0x73:{
			writeByte(HL,E);
			PC++;
			break;
		}

		case 0x74:{
			writeByte(HL,H);
			PC++;
			break;
		}

		case 0x75:{
			writeByte(HL,L);
			PC++;
			break;
		}

		case 0x76:{
			//TODO
			PC++;
			break;
		}

		case 0x77:{
			writeByte(HL,A);
			PC++;
			break;
		}

		case 0x78:{
			load8(&A,B);
			PC++;
			break;
		}

		case 0x79:{
			load8(&A,C);
			PC++;
			break;
		}

		case 0x7A:{
			load8(&A,D);
			PC++;
			break;
		}

		case 0x7B:{
			load8(&A,E);
			PC++;
			break;
		}

		case 0x7C:{
			load8(&A,H);
			PC++;
			break;
		}

		case 0x7D:{
			load8(&A,L);
			PC++;
			break;
		}

		case 0x7E:{
			load8(&A,readByte(HL));
			PC++;
			break;
		}

		case 0x7F:{
			load8(&A,A);
			PC++;
			break;
		}

		case 0x80:{
			add(&A,B);
			PC++;
			break;
		}
		case 0x81:{
			add(&A,C);
			PC++;
			break;
		}

		case 0x82:{
			add(&A,D);
			PC++;
			break;
		}

		case 0x83:{
			add(&A,E);
			PC++;
			break;
		}

		case 0x84:{
			add(&A,H);
			PC++;
			break;
		}

		case 0x85:{
			add(&A,L);
			PC++;
			break;
		}

		case 0x86:{
			add(&A,readByte(HL));
			PC++;
			break;
		}

		case 0x87:{
			add(&A,A);
			PC++;
			break;
		}

		case 0x88:{
			adc8(&A,B);
			PC++;
			break;
		}

		case 0x89:{
			adc8(&A,C);
			PC++;
			break;
		}

		case 0x8A:{
			adc8(&A,D);
			PC++;
			break;
		}

		case 0x8B:{
			adc8(&A,E);
			PC++;
			break;
		}

		case 0x8C:{
			adc8(&A,H);
			PC++;
			break;
		}

		case 0x8D:{
			adc8(&A,L);
			PC++;
			break;
		}

		case 0x8E:{
			adc8(&A,readByte(HL));
			PC++;
			break;
		}

		case 0x8F:{
			adc8(&A,A);
			PC++;
			break;
		}

		case 0x90:{
			sub8(&A,B);
			PC+=1;
			break;
		}

		case 0x91:{
			sub8(&A,C);
			PC+=1;
			break;
		}

		case 0x92:{
			sub8(&A,D);
			PC+=1;
			break;
		}

		case 0x93:{
			sub8(&A,E);
			PC+=1;
			break;
		}

		case 0x94:{
			sub8(&A,H);
			PC+=1;
			break;
		}

		case 0x95:{
			sub8(&A,L);
			PC+=1;
			break;
		}

		case 0x96:{
			sub8(&A,readByte(HL));
			PC+=1;
			break;
		}

		case 0x97:{
			sub8(&A,A);
			PC+=1;
			break;
		}

		case 0x98:{
			sbc8(&A,B);
			PC+=1;
			break;
		}

		case 0x99:{
			sbc8(&A,C);
			PC+=1;
			break;
		}

		case 0x9A:{
			sbc8(&A,D);
			PC+=1;
			break;
		}

		case 0x9B:{
			sbc8(&A,E);
			PC+=1;
			break;
		}

		case 0x9C:{
			sbc8(&A,H);
			PC+=1;
			break;
		}

		case 0x9D:{
			sbc8(&A,L);
			PC+=1;
			break;
		}

		case 0x9E:{
			sbc8(&A,readByte(HL));
			PC+=1;
			break;
		}

		case 0x9F:{
			sbc8(&A,A);
			PC+=1;
			break;
		}

		case 0xA0:{
			and(&A,B);
			PC++;
			break;
		}
		case 0xA1:{
			and(&A,C);
			PC++;
			break;
		}

		case 0xA2:{
			and(&A,D);
			PC++;
			break;
		}

		case 0xA3:{
			and(&A,E);
			PC++;
			break;
		}

		case 0xA4:{
			and(&A,H);
			PC++;
			break;
		}

		case 0xA5:{
			and(&A,L);
			PC++;
			break;
		}

		case 0xA6:{
			and(&A,readByte(HL));
			PC++;
			break;
		}

		case 0xA7:{
			and(&A,A);
			PC++;
			break;
		}

		case 0xA8:{
			xor(&A,B);
			PC++;
			break;
		}

		case 0xA9:{
			xor(&A,C);
			PC++;
			break;
		}
		case 0xAA:{
			xor(&A,D);
			PC++;
			break;
		}

		case 0xAB:{
			xor(&A,E);
			PC++;
			break;
		}

		case 0xAC:{
			xor(&A,H);
			PC++;
			break;
		}

		case 0xAD:{
			xor(&A,L);
			PC++;
			break;
		}

		case 0xAE:{
			xor(&A,readByte(HL));
			PC++;
			break;
		}

		case 0xAF:{
			xor(&A,A);
			PC++;
			break;
		}

		case 0xB0:{
			or(&A,B);
			PC++;
			break;
		}
		case 0xB1:{
			or(&A,C);
			PC++;
			break;
		}

		case 0xB2:{
			or(&A,D);
			PC++;
			break;
		}

		case 0xB3:{
			or(&A,E);
			PC++;
			break;
		}

		case 0xB4:{
			or(&A,H);
			PC++;
			break;
		}

		case 0xB5:{
			or(&A,L);
			PC++;
			break;
		}

		case 0xB6:{
			or(&A,readByte(HL));
			PC++;
			break;
		}

		case 0xB7:{
			or(&A,A);
			PC++;
			break;
		}

		case 0xB8:{
			cmp8(&A, B);
			PC+=2;
			break;
		}

		case 0xB9:{
			cmp8(&A, C);
			PC+=2;
			break;
		}

		case 0xBA:{
			cmp8(&A, D);
			PC+=2;
			break;
		}

		case 0xBB:{
			cmp8(&A, E);
			PC+=2;
			break;
		}

		case 0xBC:{
			cmp8(&A, H);
			PC+=2;
			break;
		}

		case 0xBD:{
			cmp8(&A, L);
			PC+=2;
			break;
		}

		case 0xBE:{
			cmp8(&A, readByte(HL));
			PC+=2;
			break;
		}

		case 0xBF:{
			cmp8(&A, A);
			PC+=2;
			break;
		}

		case 0xC0:{
			if(flagget(ZFLAG)==0){
				ret();
			}else{
				PC+=1;
			}
			break;
		}

		case 0xC1:{
			BC = popStack16();
			PC+=1;
			break;
		}

		case 0xC3:{
			jump(readWord(PC+1));
			//PC+=3;
			break;
		}

		case 0xC4:{
			if(flagget(ZFLAG)==0){
				call(readWord(PC+1));
			}else{
				PC+=3;
			}
			break;
		}

		case 0xC5:{
			pushStack16(BC);
			PC+=1;
			break;
		}

		case 0xC6:{
			add(&A,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xC8:{
			if(flagget(ZFLAG)==1){
				ret();
			}else{
				PC+=1;
			}
			break;
		}

		case 0xC9:{
		    //printf("%x %x %x\n",PC,SP,readWord(SP));
		    //system("pause");
		    //if(PC == 0xC8D3){system("pause");}
			ret();
			break;
		}

		case 0xCB:{
		    //printf("CB %x\n",readByte(PC+1));
			switch(readByte(PC+1)){
                case 0x00:{
					rlc(&B);
					PC+=2;
					break;
				}
                case 0x01:{
					rlc(&C);
					PC+=2;
					break;
				}
				case 0x02:{
					rlc(&D);
					PC+=2;
					break;
				}
				case 0x03:{
					rlc(&E);
					PC+=2;
					break;
				}
				case 0x04:{
					rlc(&H);
					PC+=2;
					break;
				}
				case 0x05:{
					rlc(&L);
					PC+=2;
					break;
				}
				case 0x06:{
                    unsigned char tmp = readByte(HL);
					rlc(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x07:{
					rlc(&A);
					PC+=2;
					break;
				}
				case 0x08:{
					rrc(&B);
					PC+=2;
					break;
				}
				case 0x09:{
					rrc(&C);
					PC+=2;
					break;
				}
				case 0x0A:{
					rrc(&D);
					PC+=2;
					break;
				}
				case 0x0B:{
					rrc(&E);
					PC+=2;
					break;
				}
				case 0x0C:{
					rrc(&H);
					PC+=2;
					break;
				}
				case 0x0D:{
					rrc(&L);
					PC+=2;
					break;
				}
				case 0x0E:{
                    unsigned char tmp = readByte(HL);
					rrc(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x0F:{
					rrc(&A);
					PC+=2;
					break;
				}
				case 0x10:{
					rl(&B);
					PC+=2;
					break;
				}
				case 0x11:{
					rl(&C);
					PC+=2;
					break;
				}
				case 0x12:{
					rl(&D);
					PC+=2;
					break;
				}
				case 0x13:{
					rl(&E);
					PC+=2;
					break;
				}
				case 0x14:{
					rl(&H);
					PC+=2;
					break;
				}
				case 0x15:{
					rl(&L);
					PC+=2;
					break;
				}
				case 0x16:{
					unsigned char tmp = readByte(HL);
					rl(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x17:{
					rl(&A);
					PC+=2;
					break;
				}
				case 0x18:{
					rr(&B);
					PC+=2;
					break;
				}
				case 0x19:{
					rr(&C);
					PC+=2;
					break;
				}
				case 0x1A:{
					rr(&D);
					PC+=2;
					break;
				}
				case 0x1B:{
					rr(&E);
					PC+=2;
					break;
				}
				case 0x1C:{
					rr(&H);
					PC+=2;
					break;
				}
				case 0x1D:{
					rr(&L);
					PC+=2;
					break;
				}
				case 0x1E:{
					unsigned char tmp = readByte(HL);
					rr(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x1F:{
					rr(&A);
					PC+=2;
					break;
				}
				case 0x20:{
					sla(&B);
					PC+=2;
					break;
				}
				case 0x21:{
					sla(&C);
					PC+=2;
					break;
				}
				case 0x22:{
					sla(&D);
					PC+=2;
					break;
				}
				case 0x23:{
					sla(&E);
					PC+=2;
					break;
				}
				case 0x24:{
					sla(&H);
					PC+=2;
					break;
				}
				case 0x25:{
					sla(&L);
					PC+=2;
					break;
				}
				case 0x26:{
					unsigned char tmp = readByte(HL);
					sla(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x27:{
					sla(&A);
					PC+=2;
					break;
				}
				case 0x28:{
					sra(&B);
					PC+=2;
					break;
				}
				case 0x29:{
					sra(&C);
					PC+=2;
					break;
				}
				case 0x2A:{
					sra(&D);
					PC+=2;
					break;
				}
				case 0x2B:{
					sra(&E);
					PC+=2;
					break;
				}
				case 0x2C:{
					sra(&H);
					PC+=2;
					break;
				}
				case 0x2D:{
					sra(&L);
					PC+=2;
					break;
				}
				case 0x2e:{
					unsigned char tmp = readByte(HL);
					sra(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x2F:{
					sra(&A);
					PC+=2;
					break;
				}
				case 0x30:{
					swap(&B);
					PC+=2;
					break;
				}
				case 0x31:{
					swap(&C);
					PC+=2;
					break;
				}
				case 0x32:{
					swap(&D);
					PC+=2;
					break;
				}
				case 0x33:{
					swap(&E);
					PC+=2;
					break;
				}
				case 0x34:{
					swap(&H);
					PC+=2;
					break;
				}
				case 0x35:{
					swap(&L);
					PC+=2;
					break;
				}
				case 0x36:{
					unsigned char tmp = readByte(HL);
					swap(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x37:{
					swap(&A);
					PC+=2;
					break;
				}
				case 0x38:{
					shl(&B);
					PC+=2;
					break;
				}
				case 0x39:{
					shl(&C);
					PC+=2;
					break;
				}
				case 0x3A:{
					shl(&D);
					PC+=2;
					break;
				}
				case 0x3B:{
					shl(&E);
					PC+=2;
					break;
				}
				case 0x3C:{
					shl(&H);
					PC+=2;
					break;
				}
				case 0x3D:{
					shl(&L);
					PC+=2;
					break;
				}
				case 0x3e:{
					unsigned char tmp = readByte(HL);
					shl(&tmp);
                    writeByte(HL,tmp);
					PC+=2;
					break;
				}
				case 0x3F:{
					shl(&A);
					PC+=2;
					break;
				}
				case 0x40 ... 0x7f:{
				    unsigned char tmp;
				    switch(readByte(PC+1) & 0x7)
                    {
                        case 0x0:
                        bit(&B, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x1:
                        bit(&C, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x2:
                        bit(&D, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x3:
                        bit(&E, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x4:
                        bit(&H, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x5:
                        bit(&L, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x6:
                        tmp = readByte(HL);
                        bit(&tmp, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x7:
                        bit(&A, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                    }


					PC+=2;
					break;
				}

                case 0x80 ... 0xbf:{
				    unsigned char tmp;
				    switch(readByte(PC+1) & 0x7)
                    {
                        case 0x0:
                        resetBit(&B, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x1:
                        resetBit(&C, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x2:
                        resetBit(&D, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x3:
                        resetBit(&E, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x4:
                        resetBit(&H, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x5:
                        resetBit(&L, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x6:
                        tmp = readByte(HL);
                        resetBit(&tmp, ((readByte(PC+1) >> 3) & 0x7) );
                        writeByte(HL, tmp);
                        break;
                        case 0x7:
                        resetBit(&A, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                    }


					PC+=2;
					break;
				}
				case 0xc0 ... 0xff:{
				    unsigned char tmp;
				    switch(readByte(PC+1) & 0x7)
                    {
                        case 0x0:
                        setBit(&B, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x1:
                        setBit(&C, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x2:
                        setBit(&D, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x3:
                        setBit(&E, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x4:
                        setBit(&H, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x5:
                        setBit(&L, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                        case 0x6:
                        tmp = readByte(HL);
                        setBit(&tmp, ((readByte(PC+1) >> 3) & 0x7) );
                        writeByte(HL, tmp);
                        break;
                        case 0x7:
                        setBit(&A, ((readByte(PC+1) >> 3) & 0x7) );
                        break;
                    }


					PC+=2;
					break;
				}
				default:{
					printf("Unknown opcode cb%x %x\n", readByte(PC+1), PC);
					exit(0);
					break;
				}
			}
			break;
		}

		case 0xCC:{
            callConditional(readWord(PC+1),ZFLAG,1);
		}

		case 0xCD:{
			call(readWord(PC+1));
			//PC+=3;
			break;
		}

		case 0xCE:{
			add(&A,readByte(PC+1)+flagget(CFLAG));
			PC+=2;
			break;
		}

		case 0xD0:{
			if(flagget(CFLAG)==0){
				ret();
			}else{
				PC+=1;
			}
			break;
		}

		case 0xD1:{
			DE = popStack16();
			PC+=1;
			break;
		}

		case 0xD5:{
			pushStack16(DE);
			PC+=1;
			break;
		}

		case 0xD6:{
			sub8(&A,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xD8:{
			if(flagget(CFLAG)==1){
				ret();
			}else{
				PC+=1;
			}
			break;
		}

		case 0xE0:{
		    //printf("Write to FF00 %x\n",PC);
			writeByte(readByte(PC+1)+0xFF00,A);
			PC+=2;
			break;
		}

		case 0xE1:{
			HL = popStack16();
            //if(PC==0xC660) {printf("bbbb: %x %x\n",HL, PC); system("pause");}
			PC+=1;
			break;
		}

		case 0xE5:{
			pushStack16(HL);
			PC+=1;
			break;
		}

		case 0xE6:{
			and(&A,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xE8:{
			add16(&SP,readByte(PC+1));
			flagclear(ZFLAG);
			if((unsigned short)(sp.lo+readByte(PC+1)) > 0xFF){
                flagset(CFLAG);
            }else{
                flagclear(CFLAG);
            }

            if(((sp.lo & 0xf)+(readByte(PC+1) & 0xf)) > 0xF){
                flagset(HFLAG);
            }else{
                flagclear(HFLAG);
            }
			PC+=2;
			break;
		}

		case 0xE9:{
			jump(HL);
			//PC+=3;
			break;
		}

		case 0xEA:{
			writeByte(readWord(PC+1),A);
			PC+=3;
			break;
		}

		case 0xED:{
			printf("Unknown opcode %x %x\n! Either the game or this emulator has a bug! REPORT THIS AS A BUG TO GITHUB!",readByte(PC),PC);
			exit(0);
			break;
		}

		case 0xEE:{
			xor(&A,readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xF0:{
			unsigned char ptr = readByte(PC+1);
			load8(&A,readByte(ptr+0xFF00));
			PC+=2;
			break;
		}

		case 0xF1:{
			AF = popStack16();
			PC+=1;
			break;
		}

		case 0xF5:{
			pushStack16(AF);
			PC+=1;
			break;
		}

		case 0xF3:{
			interrupts = 0;
			PC++;
			break;
		}

		case 0xF9:{
		    //if(PC==0xC65F) {printf("aaaa: %x %x\n",readWord(HL), PC); system("pause");}
			load16(&SP,HL);
			//printf("%x\n",PC-1);
			//system("pause");
			PC+=1;
			break;
		}

		case 0xFA:{
			unsigned short ptr = readWord(PC+1);
			load8(&A,readByte(ptr));
			PC+=3;
			break;
		}

		case 0xFE:{
			cmp8(&A, readByte(PC+1));
			PC+=2;
			break;
		}

		case 0xFF:{
            call(0x38);
		}

		default:{
			printf("Unimplemented opcode %x %x\n",readByte(PC),PC);
			exit(0);
			break;
		}
	}
}
