
/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


#define BUFFER_SIZE (32*1024)   // must be less or equal 64 K
#define VALUE_RANGE 65536


int iBoardNumber = 0;
int iChannel = 0;
int iTicks;
double dFreq = 100000;
char cMode = AO6x00_TRIGGER_TIMER;
short psBuffer[BUFFER_SIZE];



//------ callback ------
void _cdecl callback( void* pArgs )
{
    if(!me6x00AOContinuousEx(iBoardNumber, iChannel, BUFFER_SIZE, psBuffer, 0, NULL, NULL ))
        printf("me6x00AOContinuousEx: ERROR!\n");
}


//------ main ------
int main(void)
{
    printf("ContinuousEx at 1 channels\n");

    // provides API functions of the ME-6x00 DLL
    meOpen();


    printf("-----------------------------------------------------------\n");
    {
        printf("to prevent deadlooks at AOReset AOStart should be called before\n");

        if(!me6x00AOStart(iBoardNumber, iChannel))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOReset...\n");
        if(!me6x00AOReset(iBoardNumber, iChannel) )
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("FrequencyToTimer...\n");
        iTicks = me6x00FrequencyToTimer(dFreq);
        printf("\tticks at frequency %f Hz: %u\n", dFreq, iTicks);
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOSetTimer...\n");
        if(!me6x00AOSetTimer(iBoardNumber, iChannel, iTicks) )
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOSetTrigger...\n");
        if(!me6x00AOSetTrigger(iBoardNumber, iChannel, cMode))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("Generate waveform\n");

        for(int i = 0; i < BUFFER_SIZE; i++ )  // sinus
        {
            double val = (sin( (double)i / (double)BUFFER_SIZE * 2.0 * 3.14159 ) + 1.0) * (double)(VALUE_RANGE) / 2.0;
            psBuffer[i] = (short)val;
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOContinuousEx (preload)...\n");

        if(!me6x00AOContinuousEx(iBoardNumber, iChannel, BUFFER_SIZE, psBuffer, 0, callback, NULL))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOStart...\n");
        printf("to start press a key!\n");
        getch();

        if(!me6x00AOStart(iBoardNumber, iChannel))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("wait (reload)...\n");
        printf("to stop press a key!\n");

        while( !kbhit() )
        {
            // do anything
        }
        getch();
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOStopEx...\n");
        if(!me6x00AOStopEx(iBoardNumber, iChannel) )
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }

    meClose();

    return(0);
}
