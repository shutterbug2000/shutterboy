//shutterboy2000 CPU - header

union Register 
{
	unsigned short reg;
	struct
	{
		unsigned char lo,hi;
	};
};

union Register af;
union Register bc;
union Register de;
union Register hl;
union Register pc;
union Register sp;

#define AF af.reg
#define BC bc.reg
#define DE de.reg
#define HL hl.reg
#define PC pc.reg
#define SP sp.reg

#define A af.hi
#define F af.lo
#define B bc.hi
#define C bc.lo
#define D de.hi
#define E de.lo
#define H hl.hi
#define L hl.lo

unsigned char interrupts;

void initCpu();