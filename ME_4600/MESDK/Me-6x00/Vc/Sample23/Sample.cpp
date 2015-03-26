
/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


#define BUFFER_SIZE (16*1024)   // must be less or equal 64 K
#define VALUE_RANGE 65536


int iBoardNumber = 0;
int iChannel = 0;
int iTicks;
double dFreq = 50000;
char cMode = AO6x00_TRIGGER_TIMER   ;
short psBuffer[4][BUFFER_SIZE];




//------ callback0 ------
void _cdecl callback0( void* pArgs )
{
  if(!me6x00AOContinuousEx(0, 0, BUFFER_SIZE, psBuffer[ 0 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback1 ------
void _cdecl callback1( void* pArgs )
{
  if(!me6x00AOContinuousEx(0, 1, BUFFER_SIZE, psBuffer[ 1 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback2 ------
void _cdecl callback2( void* pArgs )
{
  if(!me6x00AOContinuousEx(0, 2, BUFFER_SIZE, psBuffer[ 2 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback3 ------
void _cdecl callback3( void* pArgs )
{
  if(!me6x00AOContinuousEx(0, 3, BUFFER_SIZE, psBuffer[ 3 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ main ------
int main(void)
{
    printf("ContinuousEx at 4 channels\n");

    // provides API functions of the ME-6x00 DLL
    meOpen();


    printf("-----------------------------------------------------------\n");
    {
        printf("to prevent deadlooks at AOReset AOStart should be called\n");

        if(!me6x00AOStart(iBoardNumber, iChannel))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOReset...\n");
        for (iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOReset(iBoardNumber, iChannel) )
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
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
        for (iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOSetTimer(iBoardNumber, iChannel, iTicks) )
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOSetTrigger...\n");
        for (iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOSetTrigger(iBoardNumber, iChannel, cMode))
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("Generate waveform\n");

        for( int i = 0; i < BUFFER_SIZE; i++ )        // rectangle
            psBuffer[0][i] = (i < BUFFER_SIZE/2) ? VALUE_RANGE-1 : 0;

        for( i = 0; i < BUFFER_SIZE; i++ )            // triangle
        {
            if( i <= BUFFER_SIZE/2)
                psBuffer[1][i] = (short)(0.5 + (double)i * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
            else
                psBuffer[1][i] = VALUE_RANGE - (short)(0.5 + (double)(i - BUFFER_SIZE/2) * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
        }

        for( i = 0; i < BUFFER_SIZE; i++ )            // sinus
        {
            double val = (sin( (double)i / (double)BUFFER_SIZE * 2.0 * 3.14159 ) + 1.0) * (double)(VALUE_RANGE) / 2.0;
            psBuffer[2][i] = (short)val;
        }

        for( i = 0; i < BUFFER_SIZE; i++ )            // pos ramp
            psBuffer[3][i] = i * VALUE_RANGE / BUFFER_SIZE;
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOContinuousEx (preload)...\n");

        if(!me6x00AOContinuousEx(iBoardNumber, 0, BUFFER_SIZE, psBuffer[0], 0, callback0, NULL))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
        Sleep( 1 );

        if(!me6x00AOContinuousEx(iBoardNumber, 1, BUFFER_SIZE, psBuffer[1], 0, callback1, NULL))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
        Sleep( 1 );

        if(!me6x00AOContinuousEx(iBoardNumber, 2, BUFFER_SIZE, psBuffer[2], 0, callback2, NULL))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
        Sleep( 1 );

        if(!me6x00AOContinuousEx(iBoardNumber, 3, BUFFER_SIZE, psBuffer[3], 0, callback3, NULL))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
        Sleep( 1 );
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOStart...\n");
        printf("to start press a key!\n");
        getch();

        for (iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOStart(iBoardNumber, iChannel))
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
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

        for (iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOStopEx(iBoardNumber, iChannel) )
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }

    meClose();

    return(0);
}
