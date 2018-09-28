//shutterboy2000 memory handler header

unsigned char wram[0x2000];

unsigned char hram[0x7f];

unsigned char readByte(unsigned short position);

unsigned char writeByte(unsigned short position, unsigned char value);