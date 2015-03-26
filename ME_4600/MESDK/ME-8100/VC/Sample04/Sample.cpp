
/* These are system header files  */
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/* These are the me8100 header files    */
#include ".\..\DLLInit.h"

/* Prototypes   */
void ChkErr (int iErrorCode);       // defines the error handler routine
void _stdcall IrqHandler (int iContext);   //user defined interrupt service routine

/*  Define Global Variables   */
int iBoardNumber;           // declare the BoardNumber variable
long count=0;		// IRQ Counter



/* ------------------------  Main Program ------------------------------- */
void main(void)
{
    iBoardNumber = 0;      // select board 
    int iContext = 0;
    int iMask = 0xFFFF;
    int iValue;
    int iOutValue = 1;

    meOpen ();  // calls the initialize function

    // Set Outputs to zero.  For testing, conntect outputs to inputs
    ChkErr (me8100DOSetWord (iBoardNumber, REGISTER_SET_A, 0));
    ChkErr (me8100DIOSetIntMode(iBoardNumber, REGISTER_SET_A, INTERRUPT_ON_BIT_CHANGE));

    // enable the interrupt
    ChkErr (me8100EnableInt (iBoardNumber, REGISTER_SET_A, IrqHandler, iContext));
    ChkErr (me8100DIOSetTristateOFF (iBoardNumber, REGISTER_SET_A));
    ChkErr (me8100SetSinkSourceMode (iBoardNumber, REGISTER_SET_A, SOURCE_MODE));

    // set the mask to define the bits to be monitored (0xFFFF = all bits)
    ChkErr (me8100DIOSetMask (iBoardNumber, REGISTER_SET_A, iMask));

    for(int i=0; (i<1000)&&(!kbhit()); i++)
    {
        count=0;
        Sleep(1000);
        printf("Irq per Second: %4d\n", count);

        // when the outputs are connected to the inputs, this causes an interrupt
        // out value sets bit 0 high to cause an interrupt
        ChkErr (me8100DOSetWord (iBoardNumber, REGISTER_SET_A, 0x00));
        Sleep(1);

        // out value sets bit 0 high to cause an interrupt
        ChkErr (me8100DOSetWord (iBoardNumber, REGISTER_SET_A, 0xFF));
    }

    ChkErr (me8100DIGetIntStatus (iBoardNumber, REGISTER_SET_A, &iValue));
    printf ("Interrupt bit pattern: %04x \n", iValue);

    ChkErr (me8100DisableInt (iBoardNumber, REGISTER_SET_A));

    printf ("Press any key to continue...\n");
    getch();

    meClose ();
}

void ChkErr (int iErrorCode) 
{
    if (iErrorCode != 1)
    {
        printf("*** Error Ocurred ***\n");
    }
}


void _stdcall IrqHandler(int iContext)
{
	count++;
    printf("*\n");
}
