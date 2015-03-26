
/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


#define AO_VALUE_MAX    0xFFFF
#define MAX_ERR_STR     0xFF


int main(void)
{
    int iBoardNumber = 0;
    int iChannel = 0;
    int iValue;
    char szErrString[MAX_ERR_STR];
    double dVoltage;

    printf("AOSingle\n");

    // provides API functions of the ME-6x00 DLL
    meOpen();


    printf("AOSingle ...\n");

    dVoltage = 7.5;

    if ((dVoltage<(-10.0)) || (dVoltage>10.0))
    {
        printf("Value outside range (-10 .. +10)\n");
    }
    else
    {
        printf("Try to output %f Volt\n", dVoltage);

        iValue = (int)((dVoltage+10.0)*((double)(AO_VALUE_MAX))/20.0);

        if(!me6x00AOSingle(iBoardNumber, iChannel, iValue))
        {
            printf("\t... failed\n");
            me6x00GetDrvErrMess(szErrString ,MAX_ERR_STR);
            printf("Error: %s \n", szErrString);
        }
        else
        {
            printf("\t... ok\n");
        }
    }


    getch();

    meClose();

    return(0);
}
