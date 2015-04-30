// TestAOContinuousInterrupt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>

#include <stdio.h>
#include <conio.h>

#include "..\_osi\defs.h"

#include "..\_osi\Common_2.h"

#include "..\me3000.h"


int main(int argc, char* argv[])
{
    char error_text[256];

    if( !me3000AOReset(0) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOReset - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    if( !me3000AOSetTrigger(0, AO3000_TRIGGER_TIMER) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOSetTrigger - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    if( !me3000AOSetTimer(0, 99) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOSetTimer - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    if( !me3000AOSetMode(0, 0, AO3000_MINUS_10, AO3000_TRANSPARENT) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOSetMode - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }


    short ps_buffer[200000];

    for(int index = 0; index < 200000; index++)
    {
        if(index % 2000 < 1000)
        {
            ps_buffer[index] = 0;
        }
        else
        {
            ps_buffer[index] = 4095;
        }
    }

    me3000AOContinuousEx(0, AO3000_INTERRUPT, 200000, &ps_buffer[0],    AO3000_INFINITE, 10, NULL);

    printf( "Signal is being output - Square wave with 15 Hz\n\n"

            "Press any key to terminate\n"                          );

    _getch();

    me3000AOStop(0);

    return(0);
}
