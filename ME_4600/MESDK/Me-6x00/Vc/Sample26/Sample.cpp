/*      Sample02.cpp : Text based (Console)         */
/*      program to test continuous mode             */

/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


#define BUFFER_SIZE 16384
#define VALUE_RANGE 65536

BOOL channelActive[ 4 ];
HANDLE hThread[ 4 ];

//------ threadFun ------
DWORD WINAPI threadFun( void* pArgs )
{
  SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );

  int ch = (int)pArgs;
  printf("Channel 0%d\n", ch );
  printf("-----------\n\n" );

  if( !me6x00AOStop(0, ch) )
  { printf("me6x00AOStop: ERROR!\n");
    ExitThread( 0 );
  }

  char buffer[64];
  double dFreq;
  int ticks;

  printf("frequency [0.00769..500000 Hz]: ");
  gets(buffer);
  sscanf(buffer, "%lf", &dFreq);
  ticks = me6x00FrequencyToTimer(dFreq);
  if( !me6x00AOSetTimer(0, ch, ticks) )
  { printf("me6x00AOSetTimer: ERROR!\n");
    ExitThread( 0 );
  }

  short psBuffer[ BUFFER_SIZE ];
  for( int i = 0; i < BUFFER_SIZE; i++ )
    switch( ch )
    {
      case 0: // rectangle
          psBuffer[ i ] = (i < BUFFER_SIZE/2) ? VALUE_RANGE-1 : 0;
        break;

      case 1: // triangle
        if( i <= BUFFER_SIZE/2)
          psBuffer[ i ] = (short)(0.5 + (double)i * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
        else
          psBuffer[ i ] = VALUE_RANGE - (short)(0.5 + (double)(i - BUFFER_SIZE/2) * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
        break;

      case 2: // sinus
      { double val = (sin( (double)i / (double)BUFFER_SIZE * 2.0 * 3.14159 ) + 1.0) * (double)(VALUE_RANGE) / 2.0;
        psBuffer[ i ] = (short)val;
        break;
      }

      case 3: // pos ramp
        psBuffer[ i ] = i * VALUE_RANGE / BUFFER_SIZE;
        break;
    }

  while( channelActive[ ch ])
  {
    if( !me6x00AOContinuous(0, ch, BUFFER_SIZE, psBuffer) )
      printf("me6x00AOContinuous: ERROR!\n");
    Sleep( 10 );
  }

  printf( "\n test at channel %d finished!\n", ch );

  ExitThread( 0 );
  return 0;
}

//------ main ------
int main(void)
{
  printf("\ntest contiuous mode on me6x00 board\n" );
  printf("===================================\n\n" );

  SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

  // calls the initialize function
  meOpen();

  int version;
  if( !me6x00GetBoardVersion(0, &version) )
  {
    printf("\nNo ME6x00 board found!\n");
    meClose();
    return 0;
  }
  printf("Any ME6x00 board found!\n");

  for( int i = 0; i < 4; ++i )
  { channelActive[ i ] = FALSE;
    hThread[ i ] = NULL;
    if( !me6x00AOReset(0, i) )
      printf("me6x00AOReset: ERROR!\n");
  }

  printf("Enter channel num to start/stop test or 'e' to end program!\n");
  printf("press a key [0..3, 'E']: ");

  BOOL toClose = FALSE;
  do
  { if( kbhit() )
    { char key = toupper( getch() );
      switch( key )
      {
        case 'E':
          for( i = 0; i < 4; ++i )
            channelActive[ i ] = FALSE;
          toClose = TRUE;
          break;

        case '0':
        case '1':
        case '2':
        case '3':
        { int ch = key - '0';

          if( channelActive[ ch ] )
            channelActive[ ch ] = FALSE;
          else
          { channelActive[ ch ] = TRUE;
            DWORD threadId;
            hThread[ ch ] = CreateThread( NULL, 4096, &threadFun, (void*)ch,
                                          0, &threadId );
          }
          break;
        }
      }
    }
    else
      Sleep( 10 );
  } while( !toClose );

  for( i = 0; i < 4; ++i )
  { if( hThread[ i ] )
      WaitForSingleObject( hThread[ i ], INFINITE );
  }

  meClose();
  return 0;
}
