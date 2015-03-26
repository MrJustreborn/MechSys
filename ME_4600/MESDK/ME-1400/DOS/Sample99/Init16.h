#ifndef INIT16_H
#define INIT16_H



// ME1400A Register Set
#define ME1400_PORT_A			0x00
#define ME1400_PORT_B			0x01
#define ME1400_PORT_C			0x02
#define ME1400_PORT_CONTROL	    0x03
#define ME1400_TIMER_0		    0x04
#define ME1400_TIMER_1		    0x05
#define ME1400_TIMER_2		    0x06
#define ME1400_TIMER_CONTROL	0x07

// ME14B Register Set
#define ME1400_PORT_BA		    0x08
#define ME1400_PORT_BB		    0x09
#define ME1400_PORT_BC		    0x0A
#define ME1400_PORT_BCONTROL	0x0B
#define ME1400_TIMER_B0		    0x0C
#define ME1400_TIMER_B1		    0x0D
#define ME1400_TIMER_B2		    0x0E
#define ME1400_TIMER_BCONTROL	0x0F

// Initialisation Register Set
#define PartA(X)    (X>>4)
#define PartB(X)    (X>>0)
#define ME1400_TIMERINTERNCLOCK_10MHZ   0x08
#define ME1400_TIMERINTERNCLOCK_1MHZ    0x00
#define ME1400_TIMERCLOCKSOURCE0_SUBD   0x04
#define ME1400_TIMERCLOCKSOURCE0_INTERN 0x00
#define ME1400_TIMERCLOCKSOURCE1_SUBD   0x02
#define ME1400_TIMERCLOCKSOURCE1_OUT0   0x00
#define ME1400_TIMERCLOCKSOURCE2_SUBD   0x01
#define ME1400_TIMERCLOCKSOURCE2_OUT1   0x00

#define ME1400_MULTIPIN_IRQ             0x00
#define ME1400_MULTIPIN_INTERNALCLOCK   0x01


// ME14A Register Set
#define ME14_PORT_A			0x00
#define ME14_PORT_B			0x01
#define ME14_PORT_C			0x02
#define ME14_PORT_CONTROL	0x03
#define ME14_TIMER_0		0x04
#define ME14_TIMER_1		0x05
#define ME14_TIMER_2		0x06
#define ME14_TIMER_CONTROL	0x07

// ME14B Register Set
#define ME14_PORT_BA		0x08
#define ME14_PORT_BB		0x09
#define ME14_PORT_BC		0x0A
#define ME14_PORT_BCONTROL	0x0B
#define ME14_TIMER_B0		0x0C
#define ME14_TIMER_B1		0x0D
#define ME14_TIMER_B2		0x0E
#define ME14_TIMER_BCONTROL	0x0F

#endif
