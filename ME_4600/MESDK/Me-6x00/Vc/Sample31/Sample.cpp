
/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


#define BUFFER_SIZE (8*1024)    // less or equal size of FIFO 8 K
#define VALUE_RANGE 65536

int iBoardNumber = 0;
int iChannel;
int iTicks;
double dFreq = 100000;
char cMode = AO6x00_TRIGGER_TIMER   ;
short psBuffer[4][BUFFER_SIZE];


int main(void)
{
    printf("WrapAround at 1 channels\n");

    // provides API functions of the ME-6x00 DLL
    meOpen();

    printf("-----------------------------------------------------------\n");
    {
        printf("to prevent deadlooks at AOReset AOStart should be called\n");

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
        for(iChannel=0; iChannel<4; iChannel++)
        {
            if(!me6x00AOSetTimer(iBoardNumber, iChannel, iTicks))
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOSetTrigger...\n");
        for(iChannel=0; iChannel<4; iChannel++)
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
        for(iChannel=0; iChannel<4; iChannel++)
        {
            printf("AOWrapAround...\n");
            
            if(!me6x00AOWrapAround(iBoardNumber, iChannel, BUFFER_SIZE, psBuffer[iChannel]) )
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOStart...\n");
        printf("to start press a key!\n");
        getch();

        if(!me6x00AOStart4(iBoardNumber))
            printf("\t... failed\n");
        else
            printf("\t... ok\n");
    }
    printf("-----------------------------------------------------------\n");
    {
        char ch;

        printf("AOStop...\n");
        printf("to stop press 's' or any other key to exit without stop WrapAround!\n");
        ch = getch();
        ch = toupper(ch);
        printf("%c %x",ch,ch);

        if (ch ==0x53)
        {
            for (iChannel=0; iChannel<4; iChannel++)
            {
                if(!me6x00AOStop(iBoardNumber, iChannel) )
                    printf("\t... failed\n");
                else
                    printf("\t... ok\n");
            }
        }
    }

    meClose();

    printf("press any key to exit!\n");
    getch();

    return(0);
}
