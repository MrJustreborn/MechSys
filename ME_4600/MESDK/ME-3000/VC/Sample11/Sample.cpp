// TestAOGenerateSignal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>

#include <stdio.h>
#include <conio.h>

#include "..\meDefs.h"
#include "..\me3000.h"


int main(int argc, char* argv[])
{
    char error_text[256];

    char buffer[128];

    if( !me3000AOReset(0) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOReset - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    int i_channel;

    int i_signal_type;

    int i_range;

    int i_minimum;

    int i_maximum;

    double d_frequency;

    while(TRUE)
    {
        printf( "Channel (0 - 3) (RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%d", &i_channel) == 1)&&(0 <= i_channel)&&(i_channel <= 3) )
        {
            break;
        }
    }

    while(TRUE)
    {
        printf( "Signal type\n\n"
                "    1) Square wave\n"
                "    2) Triangle\n"
                "    3) Saw tooth\n"
                "    4) Sinus\n\n"
                    "(RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%d", &i_signal_type) == 1)&&(1 <= i_signal_type)&&(i_signal_type <= 4) )
        {
            --i_signal_type;

            break;
        }
    }

    while(TRUE)
    {
        printf( "Range\n\n"
                "    1)   0 V - +10 V\n"
                "    2)  -5 V -  +5 V\n"
                "    3) -10 V - +10 V\n\n"
                    "(RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%d", &i_range) == 1)&&(1 <= i_range)&&(i_range <= 3) )
        {
            break;
        }
    }

    switch(i_range)
    {
    case 1:

        i_range = AO3000_PLUS_10;

        break;

    case 2:

        i_range = AO3000_MINUS_5;

        break;

    case 3:

        i_range = AO3000_MINUS_10;

        break;
    }

    while(TRUE)
    {
        printf( "Minimum (0 - 4095) (RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%d", &i_minimum) == 1)&&(0 <= i_minimum)&&(i_minimum <= 4095) )
        {
            break;
        }
    }

    while(TRUE)
    {
        printf( "Maximum (0 - 4095) (RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%d", &i_maximum) == 1)&&(0 <= i_maximum)&&(i_maximum <= 4095) )
        {
            break;
        }
    }


    while(TRUE)
    {
        printf( "Frequency Hz (0.1 - 75000.0) (RETURN to exit): ");

        gets(&buffer[0]);

        printf("\n\n");

        if(buffer[0] == 0)
        {
            return(-1);
        }

        if( (sscanf(&buffer[0], "%lf", &d_frequency) == 1)&&(0.1 <= d_frequency)&&(d_frequency <= 75000.0) )
        {
            break;
        }
    }


    if( !me3000AOGenerateSignal(0, i_channel, i_signal_type, i_range, i_minimum, i_maximum, d_frequency) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOGenerateSignal - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    printf("Press any key to terminate\n");

    _getch();

    if( !me3000AOStop(0) )
    {
        me3000GetDriverErrorString(&error_text[0]);

        printf("me3000AOStop - ERROR - %s\n", &error_text[0]);

        _getch();

        return(-1);
    }

    return 0;
}
