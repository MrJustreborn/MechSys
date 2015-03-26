
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
double dFreq = 5000;
int iShape = AO_COSINUS;

double dAmplitude = 8.0;
double dOffset = 0.0;


//------ main ------
int main(void)
{
    printf("AOWaveGen 1 channels\n");

    // provides API functions of the ME-6x00 DLL
    meOpen();

/*
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
        if(!me6x00AOReset(iBoardNumber, iChannel) )
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
    }

*/

    { //int me6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape,
      //                    int iMin, int iMax, double iFreq);
      printf("-----------------------------------------------------------\n");
      printf("AOWaveGen\n");




      if( !me6x00AOWaveGen(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq) )
        printf("me6x00AOWaveGen: ERROR!\n");
      printf("-----------------------------------------------------------\n\n");
    }

/*
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
        printf("AOContinuous (reload)...\n");
        printf("to stop press a key!\n");

        while( !kbhit() )
        {
            //printf(".");
            if(!me6x00AOContinuous(iBoardNumber, iChannel, BUFFER_SIZE, psBuffer))
                printf("\t... failed\n");
        }
        getch();
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOStop...\n");
        if(!me6x00AOStop(iBoardNumber, iChannel) )
            printf("\t... failed\n");
        else
            printf("\t... ok\n");

    }
*/
    meClose();

    return(0);
}
