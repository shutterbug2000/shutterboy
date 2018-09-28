//shutterboy flag handler -- header

#define CFLAG 0x10
#define HFLAG 0x20
#define NFLAG 0x40
#define ZFLAG 0x80

void flagset(unsigned char flags);

void flagclear(unsigned char flags);

unsigned char flagget(unsigned char flags);