
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
int iChannel = 0;
int iTicks;
double dFreq = 10000;
char cMode = AO6x00_TRIGGER_EXT_HIGH;
short psBuffer[BUFFER_SIZE];



int main(void)
{
    printf("WrapAround at 1 channels external trigger\n");

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
        if(!me6x00AOReset(iBoardNumber, iChannel))
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
            double val = (sin( (double)(64*i) / (double)BUFFER_SIZE * 2.0 * 3.14159) + 1.0) * (double)(VALUE_RANGE) / 2.0;
            psBuffer[i] = (short)val;
        }
    }
    printf("-----------------------------------------------------------\n");
    {
        printf("AOWrapAround...\n");

        if(!me6x00AOWrapAround(iBoardNumber, iChannel, BUFFER_SIZE, psBuffer) )
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
            if(!me6x00AOStart(iBoardNumber, iChannel))
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
            if(!me6x00AOStop(iBoardNumber, iChannel))
                printf("\t... failed\n");
            else
                printf("\t... ok\n");
        }
    }


    meClose();

    printf("press any key to exit!\n");
    getch();

    return(0);
}
