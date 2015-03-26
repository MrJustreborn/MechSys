#define HIGH_BYTE(ax)	(ax >> 8)
#define LOW_BYTE(ax)		(ax & 0xff)

/* Define Function Prototypes */
void setup_int_vect(void);
