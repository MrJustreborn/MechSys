/*-----------------------------------------------------------------------------
    File: WinTest.C
-------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    Windows application program for development and testing of the
    32-Bit driver for ME3000 running on Windows NT 4.0

    This program is based in the GENERIC sample program of the
    Windows NT SDK

    Version 0.001:      16.12.97    Basic frame, mk
            0.901:      24.02.98    Preliminary working version
            1.000:      25.03.98    Release of version 1
            1.001:      28.05.98    DAC Reset: SetMode added
                                    ADC channel: menu modified dependant on
                                                 the state of diff./se mode
            1.002:      09.06.98    diff./se mode: allocate a buffer for the
                                                   menu string
            1.003:      26.06.98    diff./se mode added to single conti
            1.007:      990202      max board is 32
            1.009:      990806      new trigger mode
            1.010/011:  990806      win98 driver improvements
            2.000       991221      vec model of board x not only board 1

    To build it you have to include the Library VERSION.LIB from the VC directory.
    And you have to edit the winTest.rc file because you don't have a version
    control file.

-------------------------------------------------------------------------------
    Author: Max Kormaier                                        (c) 1998   MK
-----------------------------------------------------------------------------*/

#define APPNAME     "ME3000 Test"
#define RESAPPNAME  "WinTest"

// Windows Header Files:
#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <winver.h>

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

// ME3000 Header Files
#include ".\..\meDefs.h"
#include ".\..\me3000.h"


// Local Header Files
#include "Sample.h"



// Switch to toggle between single/multiple instances(s)
//------------------------------------------------------------------------
#define ENABLE_SINGLE_INSTANCE (1==0)

// Makes it easier to determine appropriate code paths:
#if defined (WIN32)
   #define IS_WIN32 TRUE
#else
   #define IS_WIN32 FALSE
#endif
#define IS_NT      IS_WIN32 && (BOOL)(GetVersion() < 0x80000000)
#define IS_WIN32S  IS_WIN32 && (BOOL)(!(IS_NT) && (LOBYTE(LOWORD(GetVersion()))<4))
#define IS_WIN95 (BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32


#define M_PI        3.14159265358979323846
#define M_2PI       6.28318530718
#define PLOT_ADC 1
#define PLOT_DAC 0




// Global Variables:

HWND                hWndMain;           // Handle to main window
HINSTANCE           hInst;              // current instance
char                szAppName[100];     // Name of the app
char                szResAppName[25];   // Named reference used in rc file
char                szTitle[100];       // The title bar text
char                szAppTitle[100];    // The title bar text

char                szBigText[2048];
char                szText[256];
char                szText1[100];

int                 giBoardNumber      = 0;

ULONG               glExtIrqCount      = 0;
ULONG               glCounterAIrqCount = 0;
ULONG               glCounterBIrqCount = 0;

short               gsSingleValue;
short               gsCounterValue;

// Buffer
//------------------------------------------------------------------------
#define BUFFER_SIZE 262145 // 256 * 1k + 1

short               gsDACBuffer[BUFFER_SIZE];
short               gsBuffer[BUFFER_SIZE];
double              gdVoltData[BUFFER_SIZE];
POINT               pPoint[BUFFER_SIZE];
//------------------------------------------------------------------------

int                 giSizeOfPlotData = 0;

int                 giADCRange      =    AI3000_MINUS_10;
int                 giADCMode       =    AI3000_SINGLE_ENDED;
int                 giADCChannel    = 0;
int                 giChanListEntry = 0;

ME_PLX9050_INFO     gBoardData;

FARPROC             lpfnEDITDLGProc;
HWND                hEDITDLG;
int                 giEditType;
int                 giADCSize       = 4;
int                 giADCCount      = 1024;
int                 giADCDelay      = 100;
int                 giDACDelay      = 100;
int                 giDACSize       = 4096;
int                 giDACLoops      = -1;
int                 giADCLoops      = -1;
int                 giDACCount      = 1024; //204800;
int                 giDutyCycle     = 50;
int                 giInverted      = PWM3000_NORMAL;
int                 giCNTEndVal_A   = 5;
int                 giCNTEndVal_B   = 5;
int                 giCNTStartVal_A = 1;
int                 giCNTStartVal_B = 1;
int                 giScanForEver   = 0;
int                 giScanToDisk    = 0;
int                 giNewPlot       = 0;
int                 giContinuous    = 0;
int                 giTriggerMode   = AI3000_TRIGGER_TIMER;
int                 giDACTrigger    = AO3000_TRIGGER_TIMER;
int                 giTriggerConti  = 0;
int                 giAOStop        = 1;
int                 giPlotData      = 1;
int                 giPlotMode      = PLOT_ADC;

int                 giPortASetToggle[16];
int                 giPortBSetToggle[16];

int                 giChannelList[256];


int                 giDACChannel = 0;
int                 giDACRange   = AO3000_MINUS_10;
int                 giDACMode    = AO3000_TRANSPARENT;


double              gdHalfRange     = 10.0;
double              gdADCOffset     = 10.0;
double              gdADCFrequency  = 50000.0;
double              gdDACFrequency  = 100000.0;
double              gdPWMFrequency  = 10000;
RECT                gClientRect;

// Foward declarations of functions included in this code module:
ATOM                MyRegisterClass(CONST WNDCLASS*);
BOOL                InitApplication(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL                CenterWindow (HWND, HWND);
LPTSTR              GetStringRes (int id);
int                 SetDAC(char*);
int                 ReadSIORegister(char);
int                 WriteSIORegister(char*);
int                 ReadSIO(int,char*);
int                 WriteSIO(int,char*);
int                 WriteDIOByte(int, int, char*);
int                 WriteDIOWord(int, char*);
void                GetADCSetup(int, char *);
void                GetDACSetup(int, char *);
void                GetPWMSetup(int, char *);
void                GetCNTSetup(int, char *);
void                ShowBoardInfo(int);
int                 meCleanUp(void);

int                 PrepareNextPlot(short *, int);
int                 PrepareDACPlot(short *, int);
int                 PlotADCData(HWND, LPPAINTSTRUCT, HDC);
int                 PlotDACData(HWND, LPPAINTSTRUCT, HDC);
int                 SetChannelMenu(HMENU hMenu,int iType);


BOOL FAR PASCAL     EDITDLGProc (HWND , WORD, WORD , LONG );
//------------------------------------------------------------------

void _stdcall ExternInterruptHandler(void);

void _stdcall AOContinuousHandler(void);

void _stdcall CounterAInterruptHandler(void);
void _stdcall CounterBInterruptHandler(void);

void _stdcall AIMultipleHandler(short*, int);
void _stdcall AISingleHandler(short*);


int CheckOSVersion(void);

int CheckOSVersion(void)
{
    OSVERSIONINFO osVer;

    // verify presence of Windows 95
    //-----------------------------------------
    osVer.dwOSVersionInfoSize = sizeof( osVer );
    if( !GetVersionEx( &osVer ))
    {
        return FALSE;
    }

    // Use this values to identify th OS
    //
    // VER_PLATFORM_WIN32s          Win32s on Windows 3.1.
    //
    // VER_PLATFORM_WIN32_WINDOWS   Win32 on Windows 95.
    //
    // VER_PLATFORM_WIN32_NT        Win32 on Windows NT.
    //-------------------------------------------------------------

    if( osVer.dwPlatformId != VER_PLATFORM_WIN32_NT )
    {
        MessageBox( NULL,
                    "This version requires Windows NT 4.0!",
                    "WinTest for ME3000", MB_OK | MB_ICONSTOP);
        return FALSE;
    }

    return TRUE;
}




//
//  FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//  PURPOSE: Entry point for the application.
//
//  COMMENTS:
//
// This function initializes the application and processes the
// message loop.
//
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    MSG msg;
    HANDLE hAccelTable;


    // Check, if we are running the correct OS.
    // Decisions, what's correct are made inside the routine.
    //--------------------------------------------------------------------
    /*
    if (!CheckOSVersion())
    {
        return (FALSE);
    }
    */

   // Initialize global strings
   lstrcpy (szAppName, APPNAME);
   lstrcpy (szResAppName, RESAPPNAME);
   LoadString (hInstance, IDS_APP_TITLE, szAppTitle, 100);
   wsprintf(szTitle,"%s conneced to board %d",szAppTitle,0);

   if (!hPrevInstance)
   {
      // Perform instance initialization:
      if (!InitApplication(hInstance))
      {
         return (FALSE);
      }
   }

   // Perform application initialization:
   if (!InitInstance(hInstance, nCmdShow))
   {
      return (FALSE);
   }

   hAccelTable = LoadAccelerators (hInstance, szResAppName);

   // Main message loop:
   while (GetMessage(&msg, NULL, 0, 0)) {
      if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }

   return (msg.wParam);

   lpCmdLine; // This will prevent 'unused formal parameter' warnings
}

//
//  FUNCTION: MyRegisterClass(CONST WNDCLASS*)
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(CONST WNDCLASS *lpwc)
{
   HANDLE  hMod;
   FARPROC proc;
   WNDCLASSEX wcex;

   hMod = GetModuleHandle ("USER32");
   if (hMod != NULL)
   {

#if defined (UNICODE)
      proc = GetProcAddress (hMod, "RegisterClassExW");
#else
      proc = GetProcAddress (hMod, "RegisterClassExA");
#endif

      if (proc != NULL)
      {

         wcex.style         = lpwc->style;
         wcex.lpfnWndProc   = lpwc->lpfnWndProc;
         wcex.cbClsExtra    = lpwc->cbClsExtra;
         wcex.cbWndExtra    = lpwc->cbWndExtra;
         wcex.hInstance     = lpwc->hInstance;
         wcex.hIcon         = lpwc->hIcon;
         wcex.hCursor       = lpwc->hCursor;
         wcex.hbrBackground = lpwc->hbrBackground;
         wcex.lpszMenuName  = lpwc->lpszMenuName;
         wcex.lpszClassName = lpwc->lpszClassName;

         // Added elements for Windows 95:
         wcex.cbSize = sizeof(WNDCLASSEX);
         wcex.hIconSm = LoadIcon(wcex.hInstance, "WINTEST");

         return (*proc)(&wcex);//return RegisterClassEx(&wcex);
      }
   }
   return (RegisterClass(lpwc));
}


//
//  FUNCTION: InitApplication(HANDLE)
//
//  PURPOSE: Initializes window data and registers window class
//
//  COMMENTS:
//
//       In this function, we initialize a window class by filling out a data
//       structure of type WNDCLASS and calling either RegisterClass or
//       the internal MyRegisterClass.
//
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

#if ENABLE_SINGLE_INSTANCE
    HWND      hwnd;

    // Win32 will always set hPrevInstance to NULL, so lets check
    // things a little closer. This is because we only want a single
    // version of this app to run at a time
    hwnd = FindWindow (szAppName, szTitle);

    if (hwnd)
    {
        // We found another version of ourself. Lets defer to it:
        if (IsIconic(hwnd))
        {
            ShowWindow(hwnd, SW_RESTORE);
        }
        SetForegroundWindow (hwnd);

        // If this app actually had any functionality, we would
        // also want to communicate any action that our 'twin'
        // should now perform based on how the user tried to
        // execute us.
        return FALSE;
    }
#endif

    // Fill in window class structure with parameters that describe
    // the main window.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, szResAppName);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    // Since Windows95 has a slightly different recommended
    // format for the 'Help' menu, lets put this in the alternate menu like this:
    wc.lpszMenuName  = szResAppName;
    wc.lpszClassName = szAppName;

    // Register the window class and return success/failure code.
    if (IS_WIN95)
    {
        return MyRegisterClass(&wc);
    }
    else
    {
        return RegisterClass(&wc);
    }
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow( szAppName,
                         szTitle,
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                         NULL, NULL, hInstance, NULL);


    if (!hWnd)
    {
      return (FALSE);
    }

    hWndMain = hWnd;


    CheckMenuItem(GetMenu(hWnd), IDM_SELECT_BOARD_1,  MF_CHECKED);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return (TRUE);
}


//-----------------------------------------------------------------------------
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  MESSAGES:
//
//  WM_COMMAND          - process the application menu
//  WM_PAINT            - Paint the main window
//  WM_DESTROY          - post a quit message and return
//  WM_DISPLAYCHANGE    - message sent to Plug & Play systems when the
//                        display changes
//  WM_RBUTTONDOWN      - Right mouse click -- put up context menu here
//                        if appropriate
//  WM_NCRBUTTONUP      - User has clicked the right button on the
//                        application's system menu
//
//
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int         wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC         hdc;
    POINT       pnt;
    HMENU       hMenu;
    BOOL        bGotHelp;
    int         iVal;
    int         i;

    switch (message)
    {

        case WM_COMMAND:
             wmId    = LOWORD(wParam); // Remember, these are...
             wmEvent = HIWORD(wParam); // ...different for Win32!

            // Parse the menu selections:
            //-------------------
            switch (wmId)
            {

                case IDM_ABOUT:
                   DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
                   break;

                case IDM_EXIT:
                    // Clean up what we may have started and don' exit if
                    // one process is still active
                    //------------------------------------------------------------
                    if (meCleanUp()) return 0;

                    DestroyWindow (hWnd);
                    break;

                case IDM_HELPTOPICS: // Only called in Windows 95
                   bGotHelp = WinHelp (hWnd, APPNAME".HLP",
                                       HELP_FINDER,(DWORD)0);
                   if (!bGotHelp)
                   {
                      MessageBox (GetFocus(), GetStringRes(IDS_NO_HELP),
                                  szAppName, MB_OK|MB_ICONHAND);
                   }
                   break;

                case IDM_HELPCONTENTS: // Not called in Windows 95
                   bGotHelp = WinHelp (hWnd, APPNAME".HLP",
                                       HELP_CONTENTS,(DWORD)0);
                   if (!bGotHelp)
                   {
                      MessageBox (GetFocus(), GetStringRes(IDS_NO_HELP),
                                  szAppName, MB_OK|MB_ICONHAND);
                   }
                   break;

                case IDM_HELPSEARCH: // Not called in Windows 95
                   if (!WinHelp(hWnd, APPNAME".HLP", HELP_PARTIALKEY,
                               (DWORD)(LPSTR)""))
                   {
                      MessageBox (GetFocus(), GetStringRes(IDS_NO_HELP),
                                  szAppName, MB_OK|MB_ICONHAND);
                   }
                   break;

                case IDM_HELPHELP: // Not called in Windows 95
                   if(!WinHelp(hWnd, (LPSTR)NULL, HELP_HELPONHELP, 0))
                   {
                      MessageBox (GetFocus(), GetStringRes(IDS_NO_HELP),
                                  szAppName, MB_OK|MB_ICONHAND);
                   }
                   break;




                // Here are all the other possible menu options,

                case IDM_CLEAR_PLOT:
                    giPlotData = 0;
                    GetClientRect(hWndMain, &gClientRect);
                    InvalidateRect(hWndMain,&gClientRect,TRUE);
                    SendMessage(hWndMain,WM_PAINT,0,0);
                    break;

                case IDM_DLL_VERSION:
                {
                    int iVersion = me3000GetDLLVersion();
                    wsprintf(szText,"ME3000 DLL Version: %04x.%04x ",
                             iVersion >> 16,
                             iVersion & 0xFFFF);
                    MessageBox (GetFocus(), szText, szAppName, MB_OK);
                }
                break;

                case IDM_DRIVER_VERSION:
                    if (me3000GetDriverVersion(szText1) == 1)
                    {
                        wsprintf(szText,"ME3000 Driver Version: %s", szText1);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    else
                    {
                        MessageBox (GetFocus(),
                                    "Error: Can't get Driver Version!",
                                    szAppName, MB_OK);
                    }
                    break;


                case IDM_DRIVER_TIMESTAMP:
                    if (me3000GetDriverTimeStamp(szText1) == 1)
                    {
                        wsprintf(szText,
                                 "ME3000 Driver Timestamp: %s", szText1);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    else
                    {
                        MessageBox (GetFocus(),
                                    "Error: Can't get Time Stamp!",
                                    szAppName, MB_OK);
                    }
                    break;


                case IDM_DLL_TIMESTAMP:
                    me3000GetDLLTimeStamp(szText1);
                    wsprintf(szText,
                             "ME3000 DLL Timestamp: %s", szText1);
                    MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    break;


                case IDM_APP_TIMESTAMP:
                    wsprintf(szText,
                        "WinTest Timestamp: %s", __TIMESTAMP__);
                    MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    break;

                case IDM_SELECT_BOARD_1:
                case IDM_SELECT_BOARD_2:
                case IDM_SELECT_BOARD_3:
                case IDM_SELECT_BOARD_4:
                case IDM_SELECT_BOARD_5:
                case IDM_SELECT_BOARD_6:
                case IDM_SELECT_BOARD_7:
                case IDM_SELECT_BOARD_8:
                case IDM_SELECT_BOARD_9:
                case IDM_SELECT_BOARD_10:
                case IDM_SELECT_BOARD_11:
                case IDM_SELECT_BOARD_12:
                case IDM_SELECT_BOARD_13:
                case IDM_SELECT_BOARD_14:
                case IDM_SELECT_BOARD_15:
                case IDM_SELECT_BOARD_16:
                case IDM_SELECT_BOARD_17:
                case IDM_SELECT_BOARD_18:
                case IDM_SELECT_BOARD_19:
                case IDM_SELECT_BOARD_20:
                case IDM_SELECT_BOARD_21:
                case IDM_SELECT_BOARD_22:
                case IDM_SELECT_BOARD_23:
                case IDM_SELECT_BOARD_24:
                case IDM_SELECT_BOARD_25:
                case IDM_SELECT_BOARD_26:
                case IDM_SELECT_BOARD_27:
                case IDM_SELECT_BOARD_28:
                case IDM_SELECT_BOARD_29:
                case IDM_SELECT_BOARD_30:
                case IDM_SELECT_BOARD_31:
                case IDM_SELECT_BOARD_32:
                    {
                        int i,j;

                        j=wmId;

                        for (i=IDM_SELECT_BOARD_1; i<=IDM_SELECT_BOARD_32; i++)
                        {
                            CheckMenuItem(GetMenu(hWnd), i,  MF_UNCHECKED);
                        }
                        CheckMenuItem(GetMenu(hWnd), j,  MF_CHECKED);
                        giBoardNumber = j-IDM_SELECT_BOARD_1;
                        wsprintf(szTitle,
                             "%s conneced to board %d",szAppTitle,giBoardNumber);
                        SetWindowText(hWnd,(LPSTR)szTitle);
                    }
                    break;

                case IDM_VEC_MODEL:
                    if (me3000GetVECModel(giBoardNumber, &iVal))
                    {
                        wsprintf(szText,"VEC model of Board %d: %d", giBoardNumber, iVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    break;


                case IDM_PCI_CONFIG:

                    if (me3000GetPCIConfiguration(giBoardNumber,&gBoardData) == 1)
                    {
                        wsprintf(szBigText,
                              "\n\tME3000 PCI Configuration Data of Board %d:\n\n"
                              "\tVendor ID:\t\t\t0x%x\t"
                              "\tDevice ID:\t\t\t0x%x\n"
                              "\tCommand:\t\t0x%x\t"
                              "\tStatus:\t\t\t0x%x\n"
                              "\tRevision:\t\t\t0x%x\t"
                              "\tClass:\t\t\t0x%x 0x%x 0x%x\n"
                              "\tCacheSize:\t\t0x%x\t"
                              "\tLatency:\t\t\t0x%x\n"
                              "\tHeaderType:\t\t0x%x\t"
                              "\tBIST:\t\t\t0x%x\n"
                              "\tMemMapped RT regs:\t0x%x"
                              "\tPortMapped RT regs:\t0x%x\n"
                              "\tXLINX regs (s0):\t\t0x%x"
                              "\tSIO regs   (s1):\t\t0x%x\n"
                              "\t(s2):\t\t\t0x%x"
                              "\t(s3):\t\t\t0x%x\n"
                              "\tCis:\t\t\t0x%x\n"
                              "\tSubVendor:\t\t0x%x\t"
                              "\tSubSystem:\t\t0x%x\n"
                              "\tROMaddr:\t\t\t0x%x\n"
                              "\tReserved[0]:\t\t0x%x\t"
                              "\tReserved[1]:\t\t0x%x\n"
                              "\tIRQ:\t\t\t%d\t"
                              "\tIPin:\t\t\t%d\n",
                              giBoardNumber,
                              gBoardData.VendorID,
                              gBoardData.DeviceID,
                              gBoardData.Command,
                              gBoardData.Status,
                              gBoardData.Revision,
                              gBoardData.Class[0],
                              gBoardData.Class[1],
                              gBoardData.Class[2],
                              gBoardData.CacheSize,
                              gBoardData.Latency,
                              gBoardData.HeaderType,
                              gBoardData.Bist,
                              gBoardData.BaseAddr[0],
                              gBoardData.BaseAddr[1],
                              gBoardData.BaseAddr[2],
                              gBoardData.BaseAddr[3],
                              gBoardData.BaseAddr[4],
                              gBoardData.BaseAddr[5],
                              gBoardData.Cis,
                              gBoardData.SubVendor,
                              gBoardData.SubSystem,
                              gBoardData.ROMAddr,
                              gBoardData.Reserved[0],
                              gBoardData.Reserved[1],
                              gBoardData.IRQ,
                              gBoardData.IPin);

                        MessageBox (GetFocus(), szBigText, szAppName, MB_OK);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    break;



                case IDM_SERIAL_NO:
                    if (me3000GetSerialNumber(giBoardNumber,&iVal))
                    {
                        wsprintf(szText,
                                 "Serial number of Board %d: 0x%0x",
                                 giBoardNumber, iVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    break;



                case IDM_IRQCOUNT_ALL:
                    {
                        ME3000_ISR Interrupts;

                        if (me3000GetInterrupts(giBoardNumber,&Interrupts))
                        {
                            wsprintf(szText,"\tInterrupt counter of board %d:\n\n"
                                     "\tISR:\t\t%d\n"
                                     "\tADC FIFO half full:\t%d\n"
                                     "\tChannel List:\t%d\n"
                                     "\tExtern:\t\t%d\n"
                                     "\tCounter A:\t\t%d\n"
                                     "\tCounter B:\t\t%d\n"
                                     "\tUART:\t\t%d\n"
                                     "\tDAC FIFO half full:\t%d\n",
                                     giBoardNumber,
                                     Interrupts.ISR,
                                     Interrupts.AdcFifo,
                                     Interrupts.ChanList,
                                     Interrupts.Extern,
                                     Interrupts.CountA,
                                     Interrupts.CountB,
                                     Interrupts.UART,
                                     Interrupts.DacFifo);

                            MessageBox (GetFocus(), szText, szAppName, MB_OK);
                        }
                        else
                        {
                            me3000ErrorMessage(szAppName);
                        }
                    }
                    break;


                case IDM_DRIVER_STATUS:
                    {
                        ME3000_DRIVER_STATUS Status;

                        if (me3000GetDriverStatus(giBoardNumber,&Status))
                        {
                            wsprintf(szText,"Driver status of board %d:\n\n"
                                     "Control 1:\t\t0x%04x\n"
                                     "Control 2:\t\t0x%04x\n"
                                     "Control 3:\t\t0x%04x\n"
                                     "IRQ Mask:\t\t0x%04x\n"
                                     "ISR Mask:\t\t0x%04x\n"
                                     "Status:\t\t0x%04x\n"
                                     "DAC Status:\t0x%04x\n"
                                     "Debug Word:\t0x%04x\n",
                                     giBoardNumber,
                                     Status.usControl1,
                                     Status.usControl2,
                                     Status.usControl3,
                                     Status.usIRQMask,
                                     Status.usISRMask,
                                     Status.usStatus,
                                     Status.usDACStatus,
                                     Status.ulDebugWord);

                            MessageBox (GetFocus(), szText, szAppName, MB_OK);
                        }
                        else
                        {
                            me3000ErrorMessage(szAppName);
                        }
                    }
                    break;

                // Debug functions
                //--------------------------------------------------------
                case IDM_DBG_BOARD:
                    ShowBoardInfo(giBoardNumber);
                    break;

                // Initialize ME3000
                //--------------------------------------------------------
                case IDM_INITIALIZE:
                    me3000Initialize(giBoardNumber);
                    break;


                // Perform a general reset
                //--------------------------------------------------------
                case IDM_RESET_BOARD:
                    me3000GeneralReset(giBoardNumber);
                    break;

                case IDM_BACKGROUND_PRIORITY:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                            me3000SetPriority(giBoardNumber,PRIORITY_HIGH);
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            me3000SetPriority(giBoardNumber,PRIORITY_LOW);
                        }
                    }
                    break;

                // Analog I/O functions
                //--------------------------------------------------------
                case IDM_READ_SINGLE:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // 28.05.98 MK: giADCMode added
                    //----------------------------------------------------
                    me3000AISingle(giBoardNumber,           // Borad no.
                                   giADCChannel,            // Channel no.
                                   giADCRange | giADCMode,  // Rangle and se/diff
                                   &gsSingleValue);         // Result
                    //----------------------------------------------------

                    sprintf(szText,"ADC channel %d = %d = 0x%x  %6.3f [V]",
                            giADCChannel,
                            gsSingleValue,
                            gsSingleValue,
                        ADC_TO_VOLT(gsSingleValue,gdHalfRange,gdADCOffset));

                    MessageBox (0, szText, szAppName, MB_OK);
                    giContinuous = 0;
                    break;


                case IDM_READ_SINGLE_CONTINOUS:
                    giContinuous = wParam;

                    // 26.06.98 MK: giADCMode added
                    //----------------------------------------------------
                    if (!me3000AISingleEx(giBoardNumber,   // Board no.
                                          giADCChannel,    // Chan no.
                                          giADCRange | giADCMode,   // Rangle and se/diff
                                          AI3000_INFINITE, // Repetitions
                                          giADCDelay,      // Delay
                                          &gsSingleValue,  // Value
                                          AISingleHandler))// Callback
                    //----------------------------------------------------
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;



                // AIQUICK operation
                //-------------------------------------------------------------
                case IDM_READ_QUICK_POLL:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIQuick(giBoardNumber,    // Board no.
                                      gsBuffer,         // Buffer
                                      giADCCount,       // Counter
                                      AI3000_POLLING))  // Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                case IDM_READ_QUICK_INT:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIQuick(giBoardNumber,     // Board no.
                                      gsBuffer,          // Buffer
                                      giADCCount,        // Counter
                                      AI3000_INTERRUPT)) // Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                case IDM_READ_QUICK_CONTINOUS_POLL:
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (!me3000AIQuickEx(giBoardNumber,   // Board no.
                                         gsBuffer,        // Buffer
                                         giADCCount,      // Counter
                                         AI3000_POLLING,  // Mode
                                         giADCLoops,      // Repetition counter
                                         giADCDelay,      // Delay
                                         AIMultipleHandler))// Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;



                case IDM_READ_QUICK_CONTINOUS_INT:
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (!me3000AIQuickEx(giBoardNumber,   // Board no.
                                         gsBuffer,        // Buffer
                                         giADCCount,      // Counter
                                         AI3000_INTERRUPT,// Mode
                                         giADCLoops,      // Repetition counter
                                         giADCDelay,      // Delay
                                         AIMultipleHandler)) // Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                // AIMULTIPLE operation
                //-------------------------------------------------------------
                case IDM_READ_MULTIPLE_POLL:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write a single channel list entry to the board
                    //----------------------------------------------------
                    if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                       giADCRange,
                                                       giADCMode,
                                                       &giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    if (! me3000AIAddToChannelList(giBoardNumber,
                                                   giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIMultiple(giBoardNumber,     // Board no.
                                         gsBuffer,          // Buffer
                                         giADCCount,        // Counter
                                         AI3000_POLLING))   // Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;



                case IDM_READ_MULTIPLE_INT:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write a single channel list entry to the board
                    //----------------------------------------------------
                    if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                       giADCRange,
                                                       giADCMode,
                                                       &giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    if (! me3000AIAddToChannelList(giBoardNumber,
                                                   giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIMultiple(giBoardNumber,         // Board no.
                                         gsBuffer,              // Buffer
                                         giADCCount,            // Counter
                                         AI3000_INTERRUPT))     // Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;



                case IDM_READ_MULTIPLE_CONTINOUS_POLL:
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write a single channel list entry to the board
                    //----------------------------------------------------
                    if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                       giADCRange,
                                                       giADCMode,
                                                       &giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    if (! me3000AIAddToChannelList(giBoardNumber,
                                                   giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (!me3000AIMultipleEx(giBoardNumber,     // Board no.
                                            gsBuffer,          // Buffer
                                            giADCCount,        // Counter
                                            AI3000_POLLING,    // Mode
                                            giADCLoops,        // Repetition counter
                                            giADCDelay,        // Delay
                                            AIMultipleHandler))// Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    break;


                case IDM_READ_MULTIPLE_CONTINOUS_INT:
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write a single channel list entry to the board
                    //----------------------------------------------------
                    if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                       giADCRange,
                                                       giADCMode,
                                                       &giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    if (! me3000AIAddToChannelList(giBoardNumber,
                                                   giChanListEntry))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (!me3000AIMultipleEx(giBoardNumber,     // Board no.
                                            gsBuffer,          // Buffer
                                            giADCCount,        // Counter
                                            AI3000_INTERRUPT,  // Mode
                                            giADCLoops,        // Repetition counter
                                            giADCDelay,        // Delay
                                            AIMultipleHandler))// Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    break;


                // AIScan operation
                //-------------------------------------------------------------
                case IDM_READ_SCAN_POLL:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIScan(giBoardNumber,     // Board no.
                                     gsBuffer,          // Buffer
                                     giADCSize,         // Size of chanlist
                                     giADCCount,        // Counter
                                AI3000_POLLING | giScanToDisk))// Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount*giADCSize);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                case IDM_READ_SCAN_INT:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    if (giScanForEver)
                    {
                        MessageBox(0,"SCAN_INFINITE is not allowed!",
                                   szAppName, MB_OK | MB_ICONSTOP);
                        giContinuous = 0;
                        return 0;
                    }

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer and ScanTimer allowed
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (me3000AIScan(giBoardNumber,     // Board no.
                                     gsBuffer,          // Buffer
                                     giADCSize,         // Size of chanlist
                                     giADCCount,        // Counter
                                     AI3000_INTERRUPT | giScanToDisk))// Mode
                    {
                        PrepareNextPlot(gsBuffer, giADCCount*giADCSize);
                    }
                    else
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;



                case IDM_READ_SCAN_CONTINOUS_POLL:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    if (!me3000AIScanEx(giBoardNumber,  // Board no.
                                        gsBuffer,       // Buffer
                                        giADCSize,      // Size of chanlist
                                        giADCCount,     // ChanList Counter
                        AI3000_POLLING | giScanToDisk | giScanForEver,// Mode
                                        giADCLoops,     // Repetition counter
                                        giADCDelay,     // Delay
                                        AIMultipleHandler))// Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                case IDM_READ_SCAN_CONTINOUS_INT:
                    if (giContinuous)
                    {
                        MessageBeep(MB_ICONEXCLAMATION);
                        return 0;
                    }
                    giContinuous = wParam;

                    // Setup trigger condition
                    //----------------------------------------------------
                    if (!me3000AISetTrigger(giBoardNumber,
                                            giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                        giContinuous = 0;
                        return 0;
                    }

                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer and ScanTimer allowed
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));

                    // Test von Bernau:
                    // me3000FileName(giBoardNumber,0,"c:\\METest\\metest3.dat");

                    if (!me3000AIScanEx(giBoardNumber,  // Board no.
                                        gsBuffer,       // Buffer
                                        giADCSize,      // Size of chanlist
                                        giADCCount,     // ChanLis Counter
                        AI3000_INTERRUPT | giScanToDisk | giScanForEver,// Mode
                                        giADCLoops,     // Repetition counter
                                        giADCDelay,     // Delay
                                        AIMultipleHandler))// Callback
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    giContinuous = 0;
                    break;


                case IDM_READ_SCAN_TO_DISK:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                            giScanToDisk = AI3000_SCAN_TO_DISK;
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            giScanToDisk = 0;
                        }
                    }
                    break;


                case IDM_READ_SCAN_FOR_EVER:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                            giScanForEver = AI3000_SCAN_INFINITE;
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            giScanForEver = 0;
                        }
                    }
                    break;

                case IDM_ADC_SIMULTANEOUS:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                            if (!me3000AISetSimultaneous(giBoardNumber,AI3000_ENABLE))
                            {
                                me3000ErrorMessage(szAppName);
                            }
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            if (!me3000AISetSimultaneous(giBoardNumber,AI3000_DISABLE))
                            {
                                me3000ErrorMessage(szAppName);
                            }
                        }
                    }
                    break;


                case IDM_ADC_STARTBYEXTERNTRIGGER:
                    // Clear the current channel list
                    //----------------------------------------------------
                    me3000AIClearChannelList(giBoardNumber);

                    // Write n channel list entries to the board
                    //----------------------------------------------------
                    for(i=0;i<giADCSize;i++)
                    {
                        if (! me3000AIMakeChannelListEntry(giADCChannel,
                                                           giADCRange,
                                                           giADCMode,
                                                           &giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }

                        if (! me3000AIAddToChannelList(giBoardNumber,
                                                       giChanListEntry))
                        {
                            me3000ErrorMessage(szAppName);
                            giContinuous = 0;
                            return 0;
                        }
                    }

                    // Setup Timer: ChannelTimer only
                    //---------------------------------------------------
                    me3000AISetTimer(giBoardNumber,
                                     0x0,
                                     me3000FrequencyToCounter(gdADCFrequency));



                    me3000AIClearDataFIFO(giBoardNumber);

                    if(!me3000AIStartByExternalTrigger(giBoardNumber,
                                                   giTriggerMode | giTriggerConti))
                    {
                        me3000ErrorMessage(szAppName);
                    }

                    MessageBox(0,"ADC is controlled by trigger. Press any key ...","",0);

                    me3000AIReadFIFO(giBoardNumber, gsBuffer, 2048);

                    PrepareNextPlot(gsBuffer, 2048);

                    break;


                case IDM_ADC_STOP:
                    me3000AIStop(giBoardNumber);
                    giContinuous = 0;
                    wsprintf(szTitle,
                             "%s conneced to board %d",szAppTitle,giBoardNumber);
                    SetWindowText(hWnd,(LPSTR)szTitle);
                    break;

                case IDM_SETUP_FREQ:
                    giEditType = 9;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_SETUP_COUNT:
                    giEditType = 10;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_SETUP_DELAY:
                    giEditType = 11;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_SETUP_SIZE:
                    giEditType = 12;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_SETUP_LOOPS:
                    giEditType = 13;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_TRIGGER_TIMER:
                    giTriggerMode  = AI3000_TRIGGER_TIMER;
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_HIGH,  MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_LOW,   MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    break;

                case IDM_TRIGGER_HIGH:
                    giTriggerMode = AI3000_TRIGGER_EXT_HIGH;
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_TIMER, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_LOW,   MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    break;

                case IDM_TRIGGER_LOW:
                    giTriggerMode = AI3000_TRIGGER_EXT_LOW;
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_HIGH,  MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_TRIGGER_TIMER, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    break;

                case IDM_TRIGGER_CONTI:
                    {
                        if (giTriggerConti)
                        {
                            giTriggerConti = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                        }
                        else
                        {
                            giTriggerConti = AI3000_TRIGGER_CONTI;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                        }
                    }
                    break;

                case IDM_ADC_0:
                case IDM_ADC_1:
                case IDM_ADC_2:
                case IDM_ADC_3:
                case IDM_ADC_4:
                case IDM_ADC_5:
                case IDM_ADC_6:
                case IDM_ADC_7:
                case IDM_ADC_8:
                case IDM_ADC_9:
                case IDM_ADC_A:
                case IDM_ADC_B:
                case IDM_ADC_C:
                case IDM_ADC_D:
                case IDM_ADC_E:
                case IDM_ADC_F:
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_3, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_4, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_6, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_7, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_8, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_9, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_A, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_B, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_C, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_D, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_E, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_ADC_F, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    giADCChannel = (int) (wParam-200);
                    break;

                case IDM_RANGE_MINUS_10:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        wParam, MF_CHECKED);

                    giADCRange = AI3000_MINUS_10;
                    gdHalfRange = 10.0;
                    gdADCOffset = 10.0;
                    break;

                case IDM_RANGE_MINUS_5:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_MINUS_5;
                    gdHalfRange = 5.0;
                    gdADCOffset = 5.0;
                    break;

                case IDM_RANGE_MINUS_2:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_MINUS_2;
                    gdHalfRange = 2.5;
                    gdADCOffset = 2.5;
                    break;

                case IDM_RANGE_MINUS_1:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_MINUS_1;
                    gdHalfRange = 1.25;
                    gdADCOffset = 1.25;
                    break;

                case IDM_RANGE_PLUS_10:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_PLUS_10;
                    gdHalfRange = 5;
                    gdADCOffset = 0;
                    break;

                case IDM_RANGE_PLUS_5:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_PLUS_5;
                    gdHalfRange = 2.5;
                    gdADCOffset = 0;
                    break;

                case IDM_RANGE_PLUS_2:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_PLUS_2;
                    gdHalfRange = 1.25;
                    gdADCOffset = 0;
                    break;

                case IDM_RANGE_PLUS_1:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_MINUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_RANGE_PLUS_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                    giADCRange = AI3000_PLUS_1;
                    gdHalfRange = 0.625;
                    gdADCOffset = 0;
                    break;

                case IDM_SET_SE_DIFF:
                    {
                        static int bToggle = FALSE;
                        if (bToggle == FALSE)
                        {
                            bToggle = TRUE;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                            giADCMode = AI3000_DIFFERENTIAL;

                            // 28.05.98 MK: modify menue
                            //--------------------------------------------
                            SetChannelMenu(GetMenu(hWnd),0);
                            //--------------------------------------------
                        }
                        else
                        {
                            bToggle = FALSE;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);

                            giADCMode = AI3000_SINGLE_ENDED;

                            // 28.05.98 MK: modify menue
                            //--------------------------------------------
                            SetChannelMenu(GetMenu(hWnd),1);
                            //--------------------------------------------
                        }
                    }
                    break;


                // Digital I/O functions
                //--------------------------------------------------------
                case IDM_PORTA_GET_BIT_0:
                case IDM_PORTA_GET_BIT_1:
                case IDM_PORTA_GET_BIT_2:
                case IDM_PORTA_GET_BIT_3:
                case IDM_PORTA_GET_BIT_4:
                case IDM_PORTA_GET_BIT_5:
                case IDM_PORTA_GET_BIT_6:
                case IDM_PORTA_GET_BIT_7:
                case IDM_PORTA_GET_BIT_8:
                case IDM_PORTA_GET_BIT_9:
                case IDM_PORTA_GET_BIT_A:
                case IDM_PORTA_GET_BIT_B:
                case IDM_PORTA_GET_BIT_C:
                case IDM_PORTA_GET_BIT_D:
                case IDM_PORTA_GET_BIT_E:
                case IDM_PORTA_GET_BIT_F:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_3, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_4, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_6, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_7, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_8, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_9, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_A, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_B, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_C, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_D, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_E, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_GET_BIT_F, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    {
                        int iBitVal;
                        int iBit = wParam-300;

                        me3000DIOSetPortDirection(giBoardNumber, PORTA, MEINPUT);

                        me3000DIGetBit(giBoardNumber, PORTA, iBit, &iBitVal);

                        if (iBitVal)
                        {
                            wsprintf(szText,"Port A bit %d is high.", iBit);
                        }
                        else
                        {
                            wsprintf(szText,"Port A bit %d is low.", iBit);
                        }
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_PORTB_GET_BIT_0:
                case IDM_PORTB_GET_BIT_1:
                case IDM_PORTB_GET_BIT_2:
                case IDM_PORTB_GET_BIT_3:
                case IDM_PORTB_GET_BIT_4:
                case IDM_PORTB_GET_BIT_5:
                case IDM_PORTB_GET_BIT_6:
                case IDM_PORTB_GET_BIT_7:
                case IDM_PORTB_GET_BIT_8:
                case IDM_PORTB_GET_BIT_9:
                case IDM_PORTB_GET_BIT_A:
                case IDM_PORTB_GET_BIT_B:
                case IDM_PORTB_GET_BIT_C:
                case IDM_PORTB_GET_BIT_D:
                case IDM_PORTB_GET_BIT_E:
                case IDM_PORTB_GET_BIT_F:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_3, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_4, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_6, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_7, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_8, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_9, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_A, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_B, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_C, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_D, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_E, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_GET_BIT_F, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                    {
                        int iBitVal;
                        int iBit = wParam-400;

                        me3000DIOSetPortDirection(giBoardNumber, PORTB, MEINPUT);

                        me3000DIGetBit(giBoardNumber, PORTB, iBit, &iBitVal);

                        if (iBitVal)
                        {
                            wsprintf(szText,"Port B bit %d is high.", iBit);
                        }
                        else
                        {
                            wsprintf(szText,"Port B bit %d is low.", iBit);
                        }
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;


                case IDM_PORTA_GET_LOW_BYTE:
                    {
                        int iByteVal;

                        me3000DIOSetPortDirection(giBoardNumber, PORTA, MEINPUT);

                        me3000DIGetByte(giBoardNumber, PORTA, LOW_BYTE, &iByteVal);

                        wsprintf(szText,"Port A Low Byte: 0x%x", iByteVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_PORTA_GET_HIGH_BYTE:
                    {
                        int iByteVal;

                        me3000DIOSetPortDirection(giBoardNumber, PORTA, MEINPUT);

                        me3000DIGetByte(giBoardNumber, PORTA, HIGH_BYTE, &iByteVal);

                        wsprintf(szText,"Port A High Byte: 0x%x", iByteVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_PORTB_GET_LOW_BYTE:
                    {
                        int iByteVal;

                        me3000DIOSetPortDirection(giBoardNumber, PORTB, MEINPUT);

                        me3000DIGetByte(giBoardNumber, PORTB, LOW_BYTE, &iByteVal);

                        wsprintf(szText,"Port B Low Byte: 0x%x", iByteVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_PORTB_GET_HIGH_BYTE:
                    {
                        int iByteVal;

                        me3000DIOSetPortDirection(giBoardNumber, PORTB, MEINPUT);

                        me3000DIGetByte(giBoardNumber, PORTB, HIGH_BYTE, &iByteVal);

                        wsprintf(szText,"Port B High Byte: 0x%x", iByteVal);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;


                case IDM_PORTA_GET_WORD:
                    {
                        int  iWord;

                        me3000DIOSetPortDirection(giBoardNumber, PORTA, MEINPUT);

                        if (me3000DIGetWord(giBoardNumber, PORTA, &iWord))
                        {
                            wsprintf(szText,"Port A = 0x%x", iWord);
                            MessageBox (GetFocus(), szText, szAppName, MB_OK);
                        }
                        else
                        {
                            me3000ErrorMessage(szAppName);
                        }

                    }
                    break;


                case IDM_PORTB_GET_WORD:
                    {
                        int  iWord;

                        me3000DIOSetPortDirection(giBoardNumber, PORTB, MEINPUT);

                        if (me3000DIGetWord(giBoardNumber, PORTB, &iWord))
                        {
                            wsprintf(szText,"Port B = 0x%x", iWord);
                            MessageBox(GetFocus(), szText, szAppName, MB_OK);
                        }
                        else
                        {
                            me3000ErrorMessage(szAppName);
                        }
                    }
                    break;


                case IDM_PORTA_SET_BIT_0:
                case IDM_PORTA_SET_BIT_1:
                case IDM_PORTA_SET_BIT_2:
                case IDM_PORTA_SET_BIT_3:
                case IDM_PORTA_SET_BIT_4:
                case IDM_PORTA_SET_BIT_5:
                case IDM_PORTA_SET_BIT_6:
                case IDM_PORTA_SET_BIT_7:
                case IDM_PORTA_SET_BIT_8:
                case IDM_PORTA_SET_BIT_9:
                case IDM_PORTA_SET_BIT_A:
                case IDM_PORTA_SET_BIT_B:
                case IDM_PORTA_SET_BIT_C:
                case IDM_PORTA_SET_BIT_D:
                case IDM_PORTA_SET_BIT_E:
                case IDM_PORTA_SET_BIT_F:
                    {
                        int  iBit = wParam-500;

                        me3000DIOSetPortDirection(giBoardNumber, PORTA, MEOUTPUT);

                        giPortASetToggle[iBit] = ~giPortASetToggle[iBit];

                        if (giPortASetToggle[iBit] == 0)
                        {
                            CheckMenuItem(GetMenu(hWnd),
                                          wParam, MF_UNCHECKED);
                            me3000DOSetBit(giBoardNumber, PORTA, iBit, 0);
                        }
                        else
                        {
                            CheckMenuItem(GetMenu(hWnd),
                                          wParam, MF_CHECKED);
                            me3000DOSetBit(giBoardNumber, PORTA, iBit, 1);
                        }
                    }
                    break;

                case IDM_PORTB_SET_BIT_0:
                case IDM_PORTB_SET_BIT_1:
                case IDM_PORTB_SET_BIT_2:
                case IDM_PORTB_SET_BIT_3:
                case IDM_PORTB_SET_BIT_4:
                case IDM_PORTB_SET_BIT_5:
                case IDM_PORTB_SET_BIT_6:
                case IDM_PORTB_SET_BIT_7:
                case IDM_PORTB_SET_BIT_8:
                case IDM_PORTB_SET_BIT_9:
                case IDM_PORTB_SET_BIT_A:
                case IDM_PORTB_SET_BIT_B:
                case IDM_PORTB_SET_BIT_C:
                case IDM_PORTB_SET_BIT_D:
                case IDM_PORTB_SET_BIT_E:
                case IDM_PORTB_SET_BIT_F:
                    {
                        int  iBit = wParam-600;

                        me3000DIOSetPortDirection(giBoardNumber, PORTB, MEOUTPUT);

                        giPortBSetToggle[iBit] = ~giPortBSetToggle[iBit];

                        if (giPortBSetToggle[iBit] == 0)
                        {
                            CheckMenuItem(GetMenu(hWnd),
                                          wParam, MF_UNCHECKED);
                            me3000DOSetBit(giBoardNumber, PORTB, iBit, 0);
                        }
                        else
                        {
                            CheckMenuItem(GetMenu(hWnd),
                                          wParam, MF_CHECKED);
                            me3000DOSetBit(giBoardNumber, PORTB, iBit, 1);
                        }
                    }
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTA_SET_LOW_BYTE:
                    giEditType = 5;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTA_SET_HIGH_BYTE:
                    giEditType = 6;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTB_SET_LOW_BYTE:
                    giEditType = 7;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTB_SET_HIGH_BYTE:
                    giEditType = 8;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTA_SET_WORD:
                    giEditType = 3;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // Note, that writing to the port is done by the
                // callback of the dialog
                //--------------------------------------------------------
                case IDM_PORTB_SET_WORD:
                    giEditType = 4;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_RESET_PORTA:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_3, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_4, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_6, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_7, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_8, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_9, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_A, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_B, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_C, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_D, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_E, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTA_SET_BIT_F, MF_UNCHECKED);
                    {
                        int i;

                        for (i=0;i<16;i++) giPortASetToggle[i] = 0;
                        me3000DOReset(giBoardNumber,PORTA);
                    }
                    break;


                case IDM_RESET_PORTB:
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_3, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_4, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_6, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_7, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_8, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_9, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_A, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_B, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_C, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_D, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_E, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                        IDM_PORTB_SET_BIT_F, MF_UNCHECKED);
                    {
                        int i;

                        for (i=0;i<16;i++) giPortBSetToggle[i] = 0;
                        me3000DOReset(giBoardNumber,PORTB);
                    }
                    break;


                // DAC functions
                //--------------------------------------------------------
                case IDM_DAC_RESET:
                    if(!me3000AOReset(giBoardNumber))
                    {
                        me3000ErrorMessage(szAppName);
                    }

                    // 28.05.98 MK: Setting of Mode after each DAC Reset
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    //----------------------------------------------------
                    break;


                case IDM_DAC_RANGE_MINUS_10:
                    giDACRange = AO3000_MINUS_10;
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_10, MF_CHECKED);
                    break;


                case IDM_DAC_RANGE_MINUS_5:
                    giDACRange = AO3000_MINUS_5;
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_PLUS_10, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_5, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_10, MF_UNCHECKED);
                    break;


                case IDM_DAC_RANGE_PLUS_10:
                    giDACRange = AO3000_PLUS_10;
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_PLUS_10, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_5, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_RANGE_MINUS_10, MF_UNCHECKED);
                    break;


                case IDM_DAC_MODE_BUFFERED:
                    giDACMode = AO3000_BUFFERED;
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_MODE_BUFFERED, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_MODE_TRANSPARENT, MF_UNCHECKED);
                    break;


                case IDM_DAC_MODE_TRANSPARENT:
                    giDACMode = AO3000_TRANSPARENT;
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_MODE_BUFFERED, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_MODE_TRANSPARENT, MF_CHECKED);
                    break;


                case IDM_DAC_TRIGGER_TIMER:
                    giDACTrigger = AO3000_TRIGGER_TIMER;
                    if(!me3000AOSetTrigger(giBoardNumber,giDACTrigger))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_TIMER, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_HIGH, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_LOW, MF_UNCHECKED);
                    break;


                case IDM_DAC_TRIGGER_HIGH:
                    giDACTrigger = AO3000_TRIGGER_EXT_HIGH;
                    if(!me3000AOSetTrigger(giBoardNumber,giDACTrigger))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_TIMER, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_HIGH, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_LOW, MF_UNCHECKED);
                    break;


                case IDM_DAC_TRIGGER_LOW:
                    giDACTrigger = AO3000_TRIGGER_EXT_LOW;
                    if(!me3000AOSetTrigger(giBoardNumber,giDACTrigger))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_TIMER, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_HIGH, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd),
                                  IDM_DAC_TRIGGER_LOW, MF_CHECKED);
                    break;

                case IDM_DAC_UPDATE:
                    me3000AOUpdate(giBoardNumber);
                    break;


                case IDM_DAC_0:
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_0, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_3, MF_UNCHECKED);
                    giDACChannel = 0;
                    break;


                case IDM_DAC_1:
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_1, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_3, MF_UNCHECKED);
                    giDACChannel = 1;
                    break;


                case IDM_DAC_2:
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_2, MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_3, MF_UNCHECKED);
                    giDACChannel = 2;
                    break;


                case IDM_DAC_3:
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_0, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_1, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_2, MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_3, MF_CHECKED);
                    giDACChannel = 3;
                    break;


                case IDM_DAC_SINGLE:
                    // Note, that writing to the DAC is done by the
                    // callback of the dialog
                    giEditType = 20;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_DAC_STOP:
                    if (giAOStop)
                        me3000AOStopEx(giBoardNumber);
                    else
                        me3000AOStop(giBoardNumber);

                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_WRAPAROUND,
                                  MF_UNCHECKED);
                    break;


                case IDM_DAC_WRAPAROUND:
                    // Clear the DAC FIFO
                    //----------------------------------------------------
                    if(!me3000AOClearDACFIFO(giBoardNumber))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }

#if 0
                    // Create the new DAC FIFO contents
                    //----------------------------------------------------
                    for (i=0;i<giDACSize;i++)
                    {
#if 0//-------------------------------------------------------------------
                        if (i & 1)
                        {
                            if(!me3000AOAddToDACFIFO(giBoardNumber,
                                MAKE_DACFIFOENTRY(0,i)))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                        else
                        {
                            if(!me3000AOAddToDACFIFO(giBoardNumber,
                                MAKE_DACFIFOENTRY(3,4095-i)))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
#else//-------------------------------------------------------------------
                        if(!me3000AOAddToDACFIFO(giBoardNumber,
                            MAKE_DACFIFOENTRY(giDACChannel,(int)(4095. / giDACSize *i))))
                        {
                            me3000ErrorMessage(szAppName);
                            return 0;
                        }
#endif//------------------------------------------------------------------


                    }
#endif

                    for (i=0;i<giDACCount;i++)
                    {
                        int    iVal;
                        double dVal;

                        dVal = M_2PI/giDACCount*(double)i * 1.0;
                        iVal = (int)(2048.0+2048.0*cos(dVal));
                        iVal = min(iVal,4095);

                        if(!me3000AOAddToDACFIFO(giBoardNumber,
                            MAKE_DACFIFOENTRY(giDACChannel,iVal)))
                        {
                            me3000ErrorMessage(szAppName);
                            return 0;
                        }
                    }

                    // Setup Mode
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber,giDACChannel,
                                        giDACRange,giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }

                    // Setup Timer
                    //----------------------------------------------------
                    {
                        int x = ((int) (ADC_BASE_FREQUENCY_1 / gdDACFrequency)) -1;
                        //me3000AOSetTimer(giBoardNumber,   2);
                        me3000AOSetTimer(giBoardNumber, x);
                    }
                    // Start automatic mode with wraparound
                    //----------------------------------------------------
                    giAOStop=0;

                    if(!me3000AOWrapAround(giBoardNumber))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    CheckMenuItem(GetMenu(hWnd), IDM_DAC_WRAPAROUND,
                                  MF_CHECKED);
                    break;



                case IDM_DAC_CONTINOUS_POLL:
                    // Calculate beautiful output values
                    //----------------------------------------------------
                    for (i=0;i<giDACCount;i++)
                    {
                        int    iVal;
                        double dVal;

                        dVal = M_2PI/giDACCount*(double)i *5.0;
                        iVal = (int)(2048.0+2048.0*cos(dVal));
                        iVal = min(iVal,4095);

                        gsDACBuffer[i] = (short) MAKE_DACFIFOENTRY(giDACChannel,iVal);
                    }
                    PrepareDACPlot(gsDACBuffer, giDACCount);

                    // Setup Mode
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber, giDACChannel,
                                        giDACRange, giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }

                    // Setup Timer
                    //----------------------------------------------------
                    me3000AOSetTimer(giBoardNumber,
                                     me3000FrequencyToCounter(gdDACFrequency));

                    if (!me3000AOContinuous(giBoardNumber,
                                           AO3000_POLLING,
                                           giDACCount,
                                           gsDACBuffer))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;



                case IDM_DAC_CONTINOUS_INT:
                    // Calculate beautiful output values
                    //----------------------------------------------------
                    for (i=0;i<giDACCount;i++)
                    {
                        int    iVal;
                        double dVal;

                        dVal = M_2PI/giDACCount*(double)i *5.0;
                        iVal = (int)(2048.0+2048.0*sin(dVal));
                        iVal = min(iVal,4095);

                        gsDACBuffer[i] = (short) MAKE_DACFIFOENTRY(giDACChannel,iVal);
                    }
                    PrepareDACPlot(gsDACBuffer, giDACCount);

                    // Setup Mode
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber, giDACChannel,
                                        giDACRange, giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    // Setup Timer
                    //----------------------------------------------------
                    me3000AOSetTimer(giBoardNumber,
                                     me3000FrequencyToCounter(gdDACFrequency));

                    if (!me3000AOContinuous(giBoardNumber,
                                           AO3000_INTERRUPT,
                                           giDACCount,
                                           gsDACBuffer))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;



                case IDM_DAC_CONTINOUS_POLL_EX:
                    // Calculate beautiful output values
                    //----------------------------------------------------
                    for (i=0;i<giDACCount;i++)
                    {
                        int    iVal;
                        double dVal;

                        dVal = M_2PI/giDACCount*(double)i *5.0;
                        iVal = (int)(2048.0+2048.0*cos(dVal));
                        iVal = min(iVal,4095);

                        gsDACBuffer[i] = (short) MAKE_DACFIFOENTRY(giDACChannel,iVal);
                    }
                    PrepareDACPlot(gsDACBuffer, giDACCount);

                    // Setup Mode
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber, giDACChannel,
                                        giDACRange, giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    // Setup Timer
                    //----------------------------------------------------
                    me3000AOSetTimer(giBoardNumber,
                                     me3000FrequencyToCounter(gdDACFrequency));


                    giAOStop=1;
                    if (!me3000AOContinuousEx(giBoardNumber,
                                             AO3000_POLLING,
                                             giDACCount,
                                             gsDACBuffer,
                                             giDACLoops,
                                             giDACDelay,
                                             AOContinuousHandler))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;



                case IDM_DAC_CONTINOUS_INT_EX:
                    // Calculate beautiful output values
                    //----------------------------------------------------
                    for (i=0;i<giDACCount;i++)
                    {
                        int    iVal;
                        double dVal;

                        dVal = M_2PI/giDACCount*(double)i *5.0;
                        iVal = (int)(2048.0+2048.0*cos(dVal));
                        iVal = min(iVal,4095);

                        gsDACBuffer[i] = (short) MAKE_DACFIFOENTRY(giDACChannel,iVal);
                    }
                    PrepareDACPlot(gsDACBuffer, giDACCount);

                    // Setup Mode
                    //----------------------------------------------------
                    if(!me3000AOSetMode(giBoardNumber, giDACChannel,
                                        giDACRange, giDACMode))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    // Setup Timer
                    //----------------------------------------------------
                    me3000AOSetTimer(giBoardNumber,
                                     me3000FrequencyToCounter(gdDACFrequency));


                    giAOStop=1;
                    if (!me3000AOContinuousEx(giBoardNumber,
                                             AO3000_INTERRUPT,
                                             giDACCount,
                                             gsDACBuffer,
                                             giDACLoops,
                                             giDACDelay,
                                             AOContinuousHandler))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_DAC_SETUP_FREQ:
                    giEditType = 21;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_DAC_SETUP_COUNT:
                    giEditType = 22;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_DAC_SETUP_DELAY:
                    giEditType = 23;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_DAC_SETUP_SIZE:
                    giEditType = 24;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_DAC_SETUP_LOOPS:
                    giEditType = 25;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;



                // PWM functions
                //--------------------------------------------------------
                case IDM_PWM_START:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                            if(!me3000PWMSetMode(giBoardNumber,
                                                 gdPWMFrequency,
                                                 giDutyCycle,
                                                 giInverted))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }

                            me3000PWMStart(giBoardNumber);

                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            me3000PWMStop(giBoardNumber);
                        }
                    }
                    break;

                case IDM_PWM_FREQ:
                    giEditType = 30;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_PWM_DUTY:
                    giEditType = 31;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_PWM_INVERTED:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);
                            giInverted = PWM3000_INVERTED;
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);
                            giInverted = PWM3000_NORMAL;
                        }
                    }
                    break;

                // External Interrupt functions
                //--------------------------------------------------------
                case IDM_EXT_INTERRUPT:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                            if (!me3000EnableExternalInt(giBoardNumber,
                                             ExternInterruptHandler))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);

                            if (!me3000DisableExternalInt(giBoardNumber))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                    }
                    break;


                // Counter functions
                //--------------------------------------------------------
                case IDM_CNT_READ_A:
                    if (!me3000CNTRead(giBoardNumber, COUNTER3000_A,
                                       &gsCounterValue))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    else
                    {
                        wsprintf(szText,"Counter A = %d = 0x%04x",
                                 gsCounterValue,gsCounterValue);
                        MessageBox(0,szText,szAppName,
                                   MB_OK | MB_ICONINFORMATION);
                    }
                    break;


                case IDM_CNT_START_A:
                    if (!me3000CNTStart(giBoardNumber, COUNTER3000_A))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_RESET_A:
                    if (!me3000CNTReset(giBoardNumber, COUNTER3000_A))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_LOAD_A:
                    if (!me3000CNTStart(giBoardNumber, COUNTER3000_A))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    if (!me3000CNTSetRange(giBoardNumber,
                                           COUNTER3000_A,
                                           giCNTEndVal_A,
                                           giCNTStartVal_A))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_ENABLE_INT_A:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                            if (!me3000CNTInterrupt(giBoardNumber,
                                                    COUNTER3000_A,
                                                    COUNTER3000_ENABLE,
                                                    CounterAInterruptHandler))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);

                            if (!me3000CNTInterrupt(giBoardNumber,
                                                    COUNTER3000_A,
                                                    COUNTER3000_DISABLE,
                                                    NULL))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                    }
                    break;


                case IDM_CNT_EDIT_ENDVAL_A:
                    giEditType = 32;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                case IDM_CNT_EDIT_STARTVAL_A:
                    giEditType = 33;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_CNT_READ_B:
                    if (!me3000CNTRead(giBoardNumber, COUNTER3000_B,
                                       &gsCounterValue))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    else
                    {
                        wsprintf(szText,"Counter B = %d = 0x%04x",
                                 gsCounterValue,gsCounterValue);
                        MessageBox(0,szText,szAppName,
                                   MB_OK | MB_ICONINFORMATION);
                    }
                    break;


                case IDM_CNT_START_B:
                    if (!me3000CNTStart(giBoardNumber, COUNTER3000_B))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_RESET_B:
                    if (!me3000CNTReset(giBoardNumber, COUNTER3000_B))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_LOAD_B:
                    if (!me3000CNTStart(giBoardNumber, COUNTER3000_B))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    if (!me3000CNTSetRange(giBoardNumber,
                                           COUNTER3000_B,
                                           giCNTEndVal_B,
                                           giCNTStartVal_B))
                    {
                        me3000ErrorMessage(szAppName);
                        return 0;
                    }
                    break;


                case IDM_CNT_ENABLE_INT_B:
                    {
                        static int iToggle = 0;

                        if (iToggle==0)
                        {
                            iToggle = 1;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_CHECKED);

                            if (!me3000CNTInterrupt(giBoardNumber,
                                                    COUNTER3000_B,
                                                    COUNTER3000_ENABLE,
                                                    CounterBInterruptHandler))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                        else
                        {
                            iToggle = 0;
                            CheckMenuItem(GetMenu(hWnd), wParam, MF_UNCHECKED);

                            if (!me3000CNTInterrupt(giBoardNumber,
                                                    COUNTER3000_B,
                                                    COUNTER3000_DISABLE,
                                                    NULL))
                            {
                                me3000ErrorMessage(szAppName);
                                return 0;
                            }
                        }
                    }
                    break;

                case IDM_CNT_EDIT_ENDVAL_B:
                    giEditType = 34;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_CNT_EDIT_STARTVAL_B:
                    giEditType = 35;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;


                // SIO functions
                //--------------------------------------------------------
                case IDM_SIO_REGISTERS:
                    {
                        ME3000_SIO_REGS SioRegs;

                        me3000SIOGetRegisters(giBoardNumber,&SioRegs);
                        wsprintf(szText,
                                "SIO Registers:\n\n"
                                "   SIO RHR:    0x%x\n"
                                "   SIO IER:    0x%x\n"
                                "   SIO FCR:    0x%x\n"
                                "   SIO LCR:    0x%x\n"
                                "   SIO MCR:    0x%x\n"
                                "   SIO LSR:    0x%x\n"
                                "   SIO MSR:    0x%x\n"
                                "   SIO SPR:    0x%x\n",
                                SioRegs.RHR & 0xFF,
                                SioRegs.IER & 0xFF,
                                SioRegs.FCR & 0xFF,
                                SioRegs.LCR & 0xFF,
                                SioRegs.MCR & 0xFF,
                                SioRegs.LSR & 0xFF,
                                SioRegs.MSR & 0xFF,
                                SioRegs.SPR & 0xFF);
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_SIO_READ:
                    giEditType = 1;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);

                    break;

                case IDM_SIO_WRITE:
                    giEditType = 2;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);

                    break;

                case IDM_SIO_LOOPBACK:
                    // Setup SIO Transfer Parameters
                    //----------------------------------------------------
                    me3000SIOSetup(giBoardNumber,19200,8,1,'N');

                    // Do a Loop-Back Test
                    //----------------------------------------------------
                    if (! me3000SIOLoopBackTest(giBoardNumber))
                    {
                        me3000ErrorMessage(szAppName);
                    }
                    else
                    {
                        wsprintf(szText,"ME3000 SIO loop-back test passed.");
                        MessageBox (GetFocus(), szText, szAppName, MB_OK);
                    }
                    break;

                case IDM_SIO_READ_POLL:
                    giEditType = 101;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_SIO_WRITE_POLL:
                    giEditType = 102;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_SIO_READ_INT:
                    giEditType = 103;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                case IDM_SIO_WRITE_INT:
                    giEditType = 104;
                    lpfnEDITDLGProc =
                        MakeProcInstance((FARPROC)EDITDLGProc, hInst);

                    hEDITDLG        = CreateDialog(hInst,
                                                   MAKEINTRESOURCE(EDITDLG),
                                                   NULL,
                                                   lpfnEDITDLGProc);
                    break;

                default:
                    return (DefWindowProc(hWnd, message, wParam, lParam));

             }
             break;

        case WM_NCRBUTTONUP: // RightClick on windows non-client area...
             if (IS_WIN95 && SendMessage(hWnd, WM_NCHITTEST, 0, lParam)
                 == HTSYSMENU)
             {
                // The user has clicked the right button on the applications
                // 'System Menu'. Here is where you would alter the default
                // system menu to reflect your application. Notice how the
                // explorer deals with this. For this app, we aren't doing
                // anything
                return (DefWindowProc(hWnd, message, wParam, lParam));
             } else
             {
                // Nothing we are interested in, allow default handling...
                return (DefWindowProc(hWnd, message, wParam, lParam));
             }
             break;

        case WM_RBUTTONDOWN: // RightClick in windows client area...
            pnt.x = LOWORD(lParam);
            pnt.y = HIWORD(lParam);
            ClientToScreen(hWnd, (LPPOINT) &pnt);

            // This is where you would determine the appropriate 'context'
            // menu to bring up. Since this app has no real functionality,
            // we will just bring up the 'Help' menu:
            hMenu = GetSubMenu (GetMenu (hWnd), 2);
            if (hMenu)
            {
                TrackPopupMenu (hMenu, 0, pnt.x, pnt.y, 0, hWnd, NULL);
            } else
            {
            // Couldn't find the menu...
                MessageBeep(0);
            }
            break;


        case WM_DISPLAYCHANGE: // Only comes through on plug'n'play systems
            {
                 SIZE  szScreen;
                 DWORD dwBitsPerPixel = (DWORD)wParam;

                 szScreen.cx = LOWORD(lParam);
                 szScreen.cy = HIWORD(lParam);

                 MessageBox (GetFocus(), GetStringRes(IDS_DISPLAYCHANGED),
                             szAppName, 0);
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint (hWnd, &ps);

            if (giPlotMode==PLOT_ADC)
            {
                PlotADCData(hWnd, &ps, hdc);
            }
            else
            {
                PlotDACData(hWnd, &ps, hdc);
            }
            EndPaint (hWnd, &ps);
            break;


        case WM_DESTROY:
            // Clean up what we may have started and don' exit if
            // one process is still active
            //------------------------------------------------------------
            if (meCleanUp()) return 0;

            // Tell WinHelp we don't need it any more...
            WinHelp (hWnd, APPNAME".HLP", HELP_QUIT,(DWORD)0);
            PostQuitMessage(0);
            break;


        case WM_CLOSE:
            // Clean up what we may have started and don't exit if
            // one process is still active
            //------------------------------------------------------------
            if (meCleanUp()) return 0;

        default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0;
}




//
//  FUNCTION: About(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for "About" dialog box
//       This version allows greater flexibility over the contents of the 'About' box,
//       by pulling out values from the 'Version' resource.
//
//  MESSAGES:
//
// WM_INITDIALOG - initialize dialog box
// WM_COMMAND    - Input received
//
//
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   static  HFONT hfontDlg;    // Font for dialog text
   static   HFONT hFinePrint; // Font for 'fine print' in dialog
   DWORD   dwVerInfoSize;     // Size of version information block
   LPSTR   lpVersion;         // String pointer to 'version' text
   DWORD   dwVerHnd=0;        // An 'ignored' parameter, always '0'
   UINT    uVersionLen;
   WORD    wRootLen;
   BOOL    bRetCode;
   int     i;
   char    szFullPath[256];
   char    szResult[256];
   char    szGetName[256];
   DWORD dwVersion;
   char  szVersion[40];
   DWORD dwResult;

   switch (message) {
        case WM_INITDIALOG:
         ShowWindow (hDlg, SW_HIDE);

         if (PRIMARYLANGID(GetUserDefaultLangID()) == LANG_JAPANESE)
         {
            hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, 0, 0, 0,
                                  VARIABLE_PITCH | FF_DONTCARE, "");
            hFinePrint = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, 0, 0, 0,
                                    VARIABLE_PITCH | FF_DONTCARE, "");
         }
         else
         {
            hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  VARIABLE_PITCH | FF_SWISS, "");
            hFinePrint = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    VARIABLE_PITCH | FF_SWISS, "");
         }

         CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
         GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));

         // Now lets dive in and pull out the version information:
         dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
         if (dwVerInfoSize) {
            LPSTR   lpstrVffInfo;
            HANDLE  hMem;
            hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
            lpstrVffInfo  = GlobalLock(hMem);
            GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
            // The below 'hex' value looks a little confusing, but
            // essentially what it is, is the hexidecimal representation
            // of a couple different values that represent the language
            // and character set that we are wanting string values for.
            // 040904E4 is a very common one, because it means:
            //   US English, Windows MultiLingual characterset
            // Or to pull it all apart:
            // 04------        = SUBLANG_ENGLISH_USA
            // --09----        = LANG_ENGLISH
            // --11----        = LANG_JAPANESE
            // ----04E4 = 1252 = Codepage for Windows:Multilingual

            lstrcpy(szGetName, GetStringRes(IDS_VER_INFO_LANG));

            wRootLen = lstrlen(szGetName); // Save this position

            // Set the title of the dialog:
            lstrcat (szGetName, "ProductName");
            bRetCode = VerQueryValue((LPVOID)lpstrVffInfo,
               (LPSTR)szGetName,
               (LPVOID)&lpVersion,
               (UINT *)&uVersionLen);

            // Notice order of version and string...
            if (PRIMARYLANGID(GetUserDefaultLangID()) == LANG_JAPANESE)
            {
               lstrcpy(szResult, lpVersion);
               lstrcat(szResult, " ‚Ìƒo[ƒWƒ‡ƒ“î•ñ");
            }
            else
            {
               lstrcpy(szResult, "About ");
               //lstrcat(szResult, lpVersion);
               lstrcat(szResult, "...");
            }

            // -----------------------------------------------------

            SetWindowText (hDlg, szResult);

            // Walk through the dialog items that we want to replace:
            for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++) {
               GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
               szGetName[wRootLen] = (char)0;
               lstrcat (szGetName, szResult);
               uVersionLen   = 0;
               lpVersion     = NULL;
               bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                  (LPSTR)szGetName,
                  (LPVOID)&lpVersion,
                  (UINT *)&uVersionLen);

               if ( bRetCode && uVersionLen && lpVersion) {
               // Replace dialog item text with version info
                  lstrcpy(szResult, lpVersion);
                  SetDlgItemText(hDlg, i, szResult);
               }
               else
               {
                  dwResult = GetLastError();

                  wsprintf(szResult, GetStringRes(IDS_VERSION_ERROR), dwResult);
                  SetDlgItemText (hDlg, i, szResult);
               }
               SendMessage (GetDlgItem (hDlg, i), WM_SETFONT,
                  (UINT)((i==DLG_VERLAST)?hFinePrint:hfontDlg),
                  TRUE);
            } // for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++)


            GlobalUnlock(hMem);
            GlobalFree(hMem);

         }
         else
         {
            // No version information available.
         } // if (dwVerInfoSize)

            SendMessage (GetDlgItem (hDlg, IDC_LABEL), WM_SETFONT,
            (WPARAM)hfontDlg,(LPARAM)TRUE);

         // We are  using GetVersion rather then GetVersionEx
         // because earlier versions of Windows NT and Win32s
         // didn't include GetVersionEx:
         dwVersion = GetVersion();

         if (dwVersion < 0x80000000)
         {
            // Windows NT
            wsprintf (  szVersion, "Microsoft Windows NT %u.%u (Build: %u)",
                        (DWORD)(LOBYTE(LOWORD(dwVersion))),
                        (DWORD)(HIBYTE(LOWORD(dwVersion))),
                        (DWORD)(HIWORD(dwVersion)));
         } else if (LOBYTE(LOWORD(dwVersion))<4)
         {
            // Win32s
            wsprintf (  szVersion, "Microsoft Win32s %u.%u (Build: %u)",
                        (DWORD)(LOBYTE(LOWORD(dwVersion))),
                        (DWORD)(HIBYTE(LOWORD(dwVersion))),
                        (DWORD)(HIWORD(dwVersion) & ~0x8000) );
         } else {
            // Windows 95
            wsprintf (  szVersion, "Microsoft Windows 95 %u.%u",
                        (DWORD)(LOBYTE(LOWORD(dwVersion))),
                        (DWORD)(HIBYTE(LOWORD(dwVersion))) );
         }

         SetWindowText (GetDlgItem(hDlg, IDC_OSVERSION), szVersion);
         ShowWindow (hDlg, SW_SHOW);
         return (TRUE);

      case WM_COMMAND:
         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, TRUE);
            DeleteObject (hfontDlg);
            DeleteObject (hFinePrint);
            return (TRUE);
         }
         break;
   }

    return FALSE;
}

//
//   FUNCTION: CenterWindow(HWND, HWND)
//
//   PURPOSE: Centers one window over another.
//
//   COMMENTS:
//
//   In this function, we save the instance handle in a global variable and
//   create and display the main program window.
//
//   This functionwill center one window over another ensuring that
//   the placement of the window is within the 'working area', meaning
//   that it is both within the display limits of the screen, and not
//   obscured by the tray or other framing elements of the desktop.
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
   RECT    rChild, rParent, rWorkArea;
   int     wChild, hChild, wParent, hParent;
   int     xNew, yNew;
   BOOL    bResult;

   // Get the Height and Width of the child window
   GetWindowRect (hwndChild, &rChild);
   wChild = rChild.right - rChild.left;
   hChild = rChild.bottom - rChild.top;

   // Get the Height and Width of the parent window
   GetWindowRect (hwndParent, &rParent);
   wParent = rParent.right - rParent.left;
   hParent = rParent.bottom - rParent.top;

   // Get the limits of the 'workarea'
   bResult = SystemParametersInfo(
      SPI_GETWORKAREA,  // system parameter to query or set
      sizeof(RECT),
      &rWorkArea,
      0);
   if (!bResult) {
      rWorkArea.left = rWorkArea.top = 0;
      rWorkArea.right = GetSystemMetrics(SM_CXSCREEN);
      rWorkArea.bottom = GetSystemMetrics(SM_CYSCREEN);
   }

   // Calculate new X position, then adjust for workarea
   xNew = rParent.left + ((wParent - wChild) /2);
   if (xNew < rWorkArea.left) {
      xNew = rWorkArea.left;
   } else if ((xNew+wChild) > rWorkArea.right) {
      xNew = rWorkArea.right - wChild;
   }

   // Calculate new Y position, then adjust for workarea
   yNew = rParent.top  + ((hParent - hChild) /2);
   if (yNew < rWorkArea.top) {
      yNew = rWorkArea.top;
   } else if ((yNew+hChild) > rWorkArea.bottom) {
      yNew = rWorkArea.bottom - hChild;
   }

   // Set it, and return
   return SetWindowPos (hwndChild, NULL, xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


//---------------------------------------------------------------------------
//
// FUNCTION:    GetStringRes (int id INPUT ONLY)
//
// COMMENTS:    Load the resource string with the ID given, and return a
//              pointer to it.  Notice that the buffer is common memory so
//              the string must be used before this call is made a second time.
//
//---------------------------------------------------------------------------

LPTSTR   GetStringRes (int id)
{
  static TCHAR buffer[MAX_PATH];

  buffer[0]=0;
  LoadString (GetModuleHandle (NULL), id, buffer, MAX_PATH);
  return buffer;
}



/*---------------------------------------------------------------

   ExternInterruptHandler

---------------------------------------------------------------*/
void _stdcall ExternInterruptHandler(void)
{
    glExtIrqCount++;
    MessageBeep(-1);
}



/*---------------------------------------------------------------

   CounterAInterruptHandler

---------------------------------------------------------------*/
void _stdcall CounterAInterruptHandler(void)
{
    glCounterAIrqCount++;
    MessageBeep(-1);
}



/*---------------------------------------------------------------

   CounterBInterruptHandler

---------------------------------------------------------------*/
void _stdcall CounterBInterruptHandler(void)
{
    glCounterBIrqCount++;
    MessageBeep(-1);
}

/*---------------------------------------------------------------

   AISingleHandler

---------------------------------------------------------------*/
void _stdcall AISingleHandler(short *psValue)
{
    sprintf(szText,"ADC channel %d = %d = 0x%x %6.3f [V]",
             giADCChannel,
             *psValue,
             *psValue,
             ADC_TO_VOLT(*psValue,gdHalfRange,gdADCOffset));
    SetWindowText(hWndMain,(LPSTR)szText);
}



/*---------------------------------------------------------------

   AIMultipleHandler

---------------------------------------------------------------*/
void _stdcall AIMultipleHandler(short *psBuffer, int iCount)
{
    PrepareNextPlot(psBuffer, iCount);
}



/*---------------------------------------------------------------

   AOContinuousHandler

---------------------------------------------------------------*/
void _stdcall AOContinuousHandler(void)
{
    MessageBox(0,"Finish!","AOContinuousEx", MB_OK | MB_ICONINFORMATION);
}


/*---------------------------------------------------------------

   EDITDLGProc

---------------------------------------------------------------*/
BOOL FAR PASCAL EDITDLGProc(HWND hWndDlg,
                            WORD Message,
                            WORD wParam,
                            LONG lParam)
{
    HDC             hDC;
    PAINTSTRUCT     ps;
    RECT            Rect;

    static  int     iLeft = 200;
    static  int     iTop  = 200;

    switch (Message)
    {
        case WM_ERASEBKGND:
        //---------------------------------------------------------------------------------------
            return FALSE;


        case WM_INITDIALOG:
        //---------------------------------------------------------------------------------------
            switch (giEditType)
            {

                // SIO setup
                //--------------------------------------------------------
                case 1:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"SIO Register");
                    break;

                case 2:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"SIO Register and Output Value");
                    break;

                case 101:
                    SetWindowText(hWndDlg, (LPSTR)"No. of bytes to read");
                    break;

                case 102:
                    SetWindowText(hWndDlg, (LPSTR)"SIO Output");
                    break;

                case 103:
                    SetWindowText(hWndDlg, (LPSTR)"No. of bytes to read");
                    break;

                case 104:
                    SetWindowText(hWndDlg, (LPSTR)"SIO Output");
                    break;


                // DIO setup
                //--------------------------------------------------------
                case 3:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port A Output Word (hex)");
                    break;

                case 4:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port B Output Word (hex)");
                    break;

                case 5:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port A Output Low Byte (hex)");
                    break;

                case 6:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port A Output High Byte (hex)");
                    break;

                case 7:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port B Output Low Byte (hex)");
                    break;

                case 8:
                    SetWindowText(hWndDlg,
                                  (LPSTR)"Port B Output High Byte (hex)");
                    break;


                // ADC setup
                //--------------------------------------------------------
                case 9:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Frequency [Hz] (integer)");
                    wsprintf(szText,"%d",(int)gdADCFrequency);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 10:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter (integer)");
                    wsprintf(szText,"%d",giADCCount);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 11:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Delay [ms] (integer)");
                    wsprintf(szText,"%d",giADCDelay);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 12:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Size of Channel List");
                    wsprintf(szText,"%d",giADCSize);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 13:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Loops of Background Process");
                    wsprintf(szText,"%d",giDACLoops);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                // DAC setup
                //--------------------------------------------------------
                case 20:
                    SetWindowText(hWndDlg,
                    (LPSTR)"DAC output value");
                    break;

                case 21:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Freqency [Hz] (integer)");
                    wsprintf(szText,"%d",(int)gdDACFrequency);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 22:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter (integer)");
                    wsprintf(szText,"%d",(int)giDACCount);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 23:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Delay [ms] (integer)");
                    wsprintf(szText,"%d",(int)giDACDelay);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 24:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Number of FIFO Entries");
                    wsprintf(szText,"%d",giDACSize);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 25:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Loops of Background Process");
                    wsprintf(szText,"%d",giDACLoops);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;


                // PWM setup
                //--------------------------------------------------------
                case 30:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Frequency [Hz] (integer)");
                    wsprintf(szText,"%d",(int)gdPWMFrequency);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 31:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Duty Cycle [%]");
                    wsprintf(szText,"%d",giDutyCycle);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;


                // Counter setup
                //--------------------------------------------------------
                case 32:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter A End Value (short)");
                    wsprintf(szText,"%d",giCNTEndVal_A);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 33:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter A Start Value (short)");
                    wsprintf(szText,"%d",giCNTStartVal_A);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 34:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter B End Value (short)");
                    wsprintf(szText,"%d",giCNTEndVal_B);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

                case 35:
                    SetWindowText(hWndDlg,
                    (LPSTR)"Counter B Start Value (short)");
                    wsprintf(szText,"%d",giCNTStartVal_B);
                    SetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText);
                    break;

            }


            SetWindowPos(hWndDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE + SWP_NOSIZE);

            // Set or Restore the old positon
            //--------------------------------------
            GetWindowRect(hWndDlg,(LPRECT)&Rect);
            MoveWindow(hWndDlg,iLeft,iTop,(Rect.right-Rect.left),(Rect.bottom-Rect.top),FALSE);
            break;


        case WM_COMMAND:
        //---------------------------------------------------------------------------------------
            switch(wParam)
            {
                case ID_DLG_OKAY:
                    GetDlgItemText(hWndDlg, ID_EDITBOX_TEXT1, (LPSTR) szText, 80);
                    // Store position
                    //-----------------------------------
                    GetWindowRect(hWndDlg,(LPRECT)&Rect);
                    iLeft = Rect.left;
                    iTop  = Rect.top;
                    EndDialog(hWndDlg, TRUE);

                    switch (giEditType)
                    {

                        // SIO setup
                        //------------------------------------------------
                        case 1:
                            ReadSIORegister(szText[0]);
                            break;

                        case 2:
                            WriteSIORegister(szText);
                            break;

                        case 101:
                            ReadSIO(0,szText);
                            break;

                        case 102:
                            WriteSIO(0,szText);
                            break;

                        case 103:
                            ReadSIO(1,szText);
                            break;

                        case 104:
                            WriteSIO(1,szText);
                            break;


                        case 3:
                            if (!WriteDIOWord(PORTA,szText))
                            {
                                me3000ErrorMessage(szAppName);
                            }
                            break;

                        case 4:
                            if (!WriteDIOWord(PORTB,szText))
                            {
                                me3000ErrorMessage(szAppName);
                            }
                            break;

                        case 5:
                            WriteDIOByte(PORTA, LOW_BYTE, szText);
                            break;

                        case 6:
                            WriteDIOByte(PORTA, HIGH_BYTE, szText);
                            break;

                        case 7:
                            WriteDIOByte(PORTB, LOW_BYTE, szText);
                            break;

                        case 8:
                            WriteDIOByte(PORTB, HIGH_BYTE, szText);
                            break;

                        // ADC setup
                        //------------------------------------------------
                        case 9:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                            GetADCSetup(giEditType-9,szText);
                            break;

                        // DAC setup
                        //------------------------------------------------
                        case 20:
                            SetDAC(szText);
                            break;

                        case 21:
                        case 22:
                        case 23:
                        case 24:
                        case 25:
                            GetDACSetup(giEditType-21,szText);
                            break;

                        // PWM setup
                        //------------------------------------------------
                        case 30:
                        case 31:
                            GetPWMSetup(giEditType-30,szText);
                            break;

                        // Counter setup
                        //------------------------------------------------
                        case 32:
                        case 33:
                        case 34:
                        case 35:
                            GetCNTSetup(giEditType-32,szText);
                            break;

                    }
                    return TRUE;

                case ID_DLG_CANCEL:
                    szText[0] = (char) 0;
                    // Store position
                    //-----------------------------------
                    GetWindowRect(hWndDlg,(LPRECT)&Rect);
                    iLeft = Rect.left;
                    iTop  = Rect.top;
                    EndDialog(hWndDlg, TRUE);
                    return TRUE;
            }
            break;



        case WM_PAINT: /* code for the window's client area */
        //---------------------------------------------------------------------------------------
            hDC = BeginPaint(hWndDlg, &ps);
            GetClientRect(hWndDlg,(LPRECT)&Rect);
            FillRect(hDC,&Rect,GetStockObject(LTGRAY_BRUSH));
            SetBkColor(hDC,RGB(192,192,192));
            ReleaseDC(hWndDlg, hDC);
            EndPaint(hWndDlg, &ps);
            break;       /*  End of WM_PAINT  */


        default:
            return FALSE;
    }
    return TRUE;


}


/*---------------------------------------------------------------

   ReadSIORegister

---------------------------------------------------------------*/
int ReadSIORegister(char ch)
{
    ch -= 0x30;     // Convert ACSII to char

    if ((ch < 0) || (ch > 7))
    {
        return FALSE;
    }

    wsprintf(szText, " SIO Register %d = 0x%x", ch,
             me3000SIOReadRegister(giBoardNumber,ch) & 0xFF);
    MessageBox (GetFocus(), szText, szAppName, MB_OK);

    return TRUE;
}


/*---------------------------------------------------------------

   WriteSIORegister

---------------------------------------------------------------*/
int WriteSIORegister(char* szString)
{
    char ch1;
    char ch2;
    int  iVal;

    sscanf(szString,"%c %x",&ch1, &iVal);
    ch1 -= 0x30;        // Convert ACSII to char

    if ((ch1 < 0) || (ch1 > 7))
    {
        return FALSE;
    }

    ch2 = (char) iVal & 0xFF;

    wsprintf(szText, " Writing 0x%x to SIO Register %d.", ch2 & 0xFF, ch1);
    MessageBox (GetFocus(), szText, szAppName, MB_OK);

    me3000SIOWriteRegister(giBoardNumber, ch1, ch2);
    return TRUE;
}



/*---------------------------------------------------------------

   ReadSIORegister

---------------------------------------------------------------*/
int ReadSIO(int iMode,  char* pcCount)
{
    int     iCount;
    char    SioBuffer[1024];

    iCount = atoi(pcCount);

    // Polling
    if (iMode ==0)
    {

        if (!me3000SIOOpen(giBoardNumber, SIO_POLLING,0,0))
        {
            me3000ErrorMessage(szAppName);
            return 0;
        }

        if (!me3000SIOSetup(giBoardNumber,19200,8,1,'N'))
        {
            me3000ErrorMessage(szAppName);
            return 0;
        }

        if (me3000SIOReceive(giBoardNumber, SIO_POLLING, iCount, SioBuffer) != -1)
        {
            SioBuffer[iCount] = (char)0;
            MessageBox(0, SioBuffer, szAppName,
                       MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
        }
        else
        {
            MessageBox(0,"SIO error",szAppName,MB_OK | MB_ICONINFORMATION);
        }
    }
    else
    {
    }
    return 0;
}



/*---------------------------------------------------------------

   WriteSIORegister

---------------------------------------------------------------*/
int WriteSIO(int iMode, char* pcBuffer)
{
    int iCount;

    // Polling
    if (iMode ==0)
    {
        if (!me3000SIOOpen(giBoardNumber, SIO_POLLING,0,0))
        {
            me3000ErrorMessage(szAppName);
            return 0;
        }

        if (!me3000SIOSetup(giBoardNumber,19200,8,1,'N'))
        {
            me3000ErrorMessage(szAppName);
            return 0;
        }

        iCount = strlen(pcBuffer);
        me3000SIOTransmit(giBoardNumber, SIO_POLLING, iCount, pcBuffer);
    }
    else
    {
    }
    return 0;
}


/*---------------------------------------------------------------

   WriteDIOWord

---------------------------------------------------------------*/
int WriteDIOWord(int iPort, char* szString)
{
    int iWord;

    sscanf(szString,"%x", &iWord);

    me3000DIOSetPortDirection(giBoardNumber, iPort, MEOUTPUT);

    return me3000DOSetWord(giBoardNumber, iPort, iWord);
}


int WriteDIOByte(int iPort, int iByte, char* szString)
{
    int iWord;

    sscanf(szString,"%x", &iWord);

    me3000DIOSetPortDirection(giBoardNumber, iPort, MEOUTPUT);

    return me3000DOSetByte(giBoardNumber, iPort, iByte, iWord);
}




/*---------------------------------------------------------------

   SetDAC

---------------------------------------------------------------*/
int SetDAC(char* szString)
{
    short sWord;

    sscanf(szString,"%d", &sWord);

    return me3000AOSingle(giBoardNumber, giDACChannel, sWord);

}


/*---------------------------------------------------------------

   GetADCSetup

---------------------------------------------------------------*/
void GetADCSetup(int iType, char* szString)
{
    int    iDummy;


    sscanf(szString,"%d", &iDummy);

    switch (iType)
    {
        case 0:
            wsprintf(szText,"Frequency = %d [Hz]\nIs this correct?",iDummy);
            break;

        case 1:
            wsprintf(szText,"Counter = %d\nIs this correct?",iDummy);
            break;

        case 2:
            wsprintf(szText,"Delay = %d [ms]\nIs this correct?",iDummy);
            break;

        case 3:
            wsprintf(szText,"Size of chan. list = %d\nIs this correct?",iDummy);
            break;

        case 4:
            wsprintf(szText,"No. of Loops = %d\nIs this correct?",iDummy);
            break;

        default:
            MessageBox(0,"Invalid ADC setup type!","",MB_OK | MB_ICONSTOP);
            return;
    }


    if (MessageBox(0,szText,szAppName, MB_YESNO) == IDYES)
    {
        switch (iType)
        {

            case 0:
                gdADCFrequency = (double )iDummy;
                break;

            case 1:
                giADCCount      = iDummy;
                giADCCount      = min(giADCCount,BUFFER_SIZE);
                break;

            case 2:
                giADCDelay      = iDummy;
                break;

            case 3:
                giADCSize       = iDummy;
                break;

            case 4:
                giADCLoops      = iDummy;
                break;
        }
    }
}


/*---------------------------------------------------------------

   GetDACSetup

---------------------------------------------------------------*/
void GetDACSetup(int iType, char* szString)
{
    int    iDummy;


    sscanf(szString,"%d", &iDummy);

    switch (iType)
    {
        case 0:
            wsprintf(szText,"Frequency = %d [Hz]\nIs this correct?",iDummy);
            break;

        case 1:
            wsprintf(szText,"Counter = %d\nIs this correct?",iDummy);
            break;

        case 2:
            wsprintf(szText,"Delay = %d [ms]\nIs this correct?",iDummy);
            break;

        case 3:
            wsprintf(szText,"No. of FIFO entries = %d\nIs this correct?",iDummy);
            break;

        case 4:
            wsprintf(szText,"No. of Loops = %d\nIs this correct?",iDummy);
            break;


        default:
            MessageBox(0,"Invalid DAC setup type!","",MB_OK | MB_ICONSTOP);
            return;
    }


    if (MessageBox(0,szText,szAppName, MB_YESNO) == IDYES)
    {
        switch (iType)
        {

            case 0:
                gdDACFrequency = (double )iDummy;
                break;

            case 1:
                giDACCount      = iDummy;
                giDACCount      = min(giDACCount,BUFFER_SIZE);
                break;

            case 2:
                giDACDelay      = iDummy;
                break;

            case 3:
                giDACSize       = iDummy;
                break;

            case 4:
                giDACLoops      = iDummy;
                break;
        }
    }
}



/*---------------------------------------------------------------

   GetPWMSetup

---------------------------------------------------------------*/
void GetPWMSetup(int iType, char* szString)
{
    int    iDummy;


    sscanf(szString,"%d", &iDummy);

    switch (iType)
    {
        case 0:
            wsprintf(szText,"Frequency = %d [Hz]\nIs this correct?",iDummy);
            break;

        case 1:
            wsprintf(szText,"Duty Cycle = %d\nIs this correct?",iDummy);
            break;

        default:
            MessageBox(0,"Invalid PWM setup type!","",MB_OK | MB_ICONSTOP);
            return;
    }


    if (MessageBox(0,szText,szAppName, MB_YESNO) == IDYES)
    {
        switch (iType)
        {

            case 0:
                gdPWMFrequency = (double )iDummy;
                break;

            case 1:
                giDutyCycle     = iDummy;
                break;
        }
    }
}



/*---------------------------------------------------------------

   GetCNTSetup

---------------------------------------------------------------*/
void GetCNTSetup(int iType, char* szString)
{
    int    iDummy;


    sscanf(szString,"%d", &iDummy);

    switch (iType)
    {
        case 0:
        case 2:
            wsprintf(szText,"End Value = %d\nIs this correct?",iDummy);
            break;

        case 1:
        case 3:
            wsprintf(szText,"Start Value = %d\nIs this correct?",iDummy);
            break;

        default:
            MessageBox(0,"Invalid Counter setup type!","",MB_OK | MB_ICONSTOP);
            return;
    }


    if (MessageBox(0,szText,szAppName, MB_YESNO) == IDYES)
    {
        switch (iType)
        {

            case 0:
                giCNTEndVal_A   = iDummy;
                break;

            case 1:
                giCNTStartVal_A = iDummy;
                break;

            case 2:
                giCNTEndVal_B   = iDummy;
                break;

            case 3:
                giCNTStartVal_B = iDummy;
                break;
        }
    }
}






/*---------------------------------------------------------------

   ShowBoardInfo

---------------------------------------------------------------*/
void ShowBoardInfo(int iBoard)
{
    ME3000_BOARD_INFO BoardInfo;


    if (me3000DLLBoardInfo(iBoard, &BoardInfo) == 1)
    {
        char szDummy[15];
        char szVersion[10];
        char szDate[10];

        wsprintf(szDummy,"%08X",BoardInfo.FileVersion);
        szVersion[0] = 'M';
        szVersion[1] = szDummy[0];
        szVersion[2] = szDummy[1];
        szVersion[3] = 'v';
        szVersion[4] = szDummy[2];
        szVersion[5] = szDummy[3];
        szVersion[6] = '.';
        szVersion[7] = szDummy[4];
        szVersion[8] = szDummy[5];
        szVersion[9] = (char) 0;

        wsprintf(szDummy,"%08X",BoardInfo.FileDate);
        szDate[0] = szDummy[4];
        szDate[1] = szDummy[5];
        szDate[2] = '.';
        szDate[3] = szDummy[2];
        szDate[4] = szDummy[3];
        szDate[5] = '.';
        szDate[6] = szDummy[6];
        szDate[7] = szDummy[7];
        szDate[8] = (char) 0;

        wsprintf(szBigText,"\n\tInformation of Board No. %d  (Device No. %d):\n\n"
              "\tPCI slot number:\t\t%d\n"
              "\tRT phys. address:\t\t0x%x\n"
              "\tXILINX phys. address:\t0x%x\n"
              "\tSIO phys. address:\t\t0x%x\n"
              "\tBoards found:\t\t%d\n"
              "\tDevice Number:\t\t%d\n"
              "\tFirmware File Status:\t\t%d\n"
              "\tFirmware File Length:\t\t%d\n"
              "\tFirmware Version:\t\t%s\n"
              "\tDate of Firmware:\t\t%s\n"
              "\tSize of ADC FIFO:\t\t%d\n"
              "\tSize of DAC FIFO:\t\t%d\n"
              "\tSize of Chan List FIFO:\t%d\n"
              "\tSerial Number:\t\t%d\n"
              "\tEEPROM Date:\t\t0x%x\n"
              "\tMEVEC Model:\t\t%d",
              iBoard,
              BoardInfo.DeviceNumber,
              BoardInfo.SlotNumber,
              BoardInfo.RTPhysAddr,
              BoardInfo.XilinxPhysAddr,
              BoardInfo.SioPhysAddr,
              BoardInfo.NoOfBoards,
              BoardInfo.DeviceNumber,
              BoardInfo.FileStatus,
              BoardInfo.FileLength,
              szVersion,
              szDate,
              BoardInfo.ADCFifo,
              BoardInfo.DACFifo,
              BoardInfo.ChanListFifo,
              BoardInfo.SerialNumber,
              BoardInfo.Date,
              BoardInfo.MEVECModel);
        MessageBox (GetFocus(), szBigText, szAppName, MB_OK);

    }
    else
    {
        me3000ErrorMessage(szAppName);
    }
}



/*-----------------------------------------------------------------------------

   meCleanUp

------------------------------------------------------------------------------*/
int meCleanUp(void)
{

    // This function prevents from exiting with an active interrupt
    // process.
    //
    // It has to be called from the different locations
    //      1. IDM_EXIT
    //      2. WM_DESTROY
    //      3. WM_CLOSE
    //--------------------------------------------------------------------
    if (giContinuous)
    {

        MessageBox(GetFocus(),
                   "Can't exit. Please stop running operation!", szAppName,
                   MB_OK | MB_ICONSTOP);
        return 1;
    }

    return 0;
}


/*---------------------------------------------------------------

   PlotADCData

---------------------------------------------------------------*/
int PlotADCData(HWND hWnd, LPPAINTSTRUCT lpPaint, HDC hDC)
{

    int i;

    int     iX0 = 50;
    int     iY0 = 50;
    int     iY1;

    double  dXScale;
    double  dYScale;

    RECT    Rect;
    HPEN    hPen;

    static  int bBusy = 0;

    if (bBusy) return 1;
    bBusy = 1;

    GetClientRect(hWnd,&Rect);


    dXScale = (double)(Rect.right  - Rect.left-2*iX0) / (giSizeOfPlotData-1);
    iY1     = (Rect.bottom - Rect.top) / 2;

    if ((giADCRange==AI3000_MINUS_10)||
        (giADCRange==AI3000_MINUS_5) ||
        (giADCRange==AI3000_MINUS_2) ||
        (giADCRange==AI3000_MINUS_1))
    {
        dYScale = (double)(Rect.bottom - Rect.top -2*iY0) / 2.0 / gdHalfRange;
    }
    else
    {
        dYScale = (double)(Rect.bottom - Rect.top -2*iY0) / 4.0 / gdHalfRange;
    }



    //Draw the plot window frame
    //--------------------------------------------------------------------
    pPoint[0].x = Rect.left+iX0;
    pPoint[0].y = Rect.top+iY0;

    pPoint[1].x = Rect.right-iX0;
    pPoint[1].y = Rect.top+iY0;

    pPoint[2].x = Rect.right-iX0;
    pPoint[2].y = Rect.bottom-iY0;

    pPoint[3].x = Rect.left+iX0;
    pPoint[3].y = Rect.bottom-iY0;

    pPoint[4].x = Rect.left+iX0;
    pPoint[4].y = Rect.top+iY0;

    Polyline(hDC, pPoint, 5);

    for (i=1;i<10;i++)
    {
        if (i==5)
        {
            pPoint[0].x = Rect.left+iX0/2 ;
            pPoint[0].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;

            pPoint[1].x = Rect.right-iX0/2;
            pPoint[1].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;
            Polyline(hDC, pPoint, 2);
        }
        else
        {
            pPoint[0].x = Rect.left+iX0 ;
            pPoint[0].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;

            pPoint[1].x = Rect.right-iX0;
            pPoint[1].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;
            Polyline(hDC, pPoint, 2);
        }
    }


    if (giPlotData)
    {
        int iCnt = 0;

        hPen = SelectObject(hDC,CreatePen(PS_SOLID,1,0xFF));

        for (i=0;i<giSizeOfPlotData;i++)
        {
            pPoint[iCnt].x = iX0 + (int) (i * dXScale);
            pPoint[iCnt].y = iY1 - (int) ((gdVoltData[i] * dYScale));

            if (iCnt == 1000)
            {
                Polyline(hDC, pPoint, iCnt);
                iCnt = -1;
            }
            iCnt++;

        }
        Polyline(hDC, pPoint, iCnt);
        DeleteObject(SelectObject(hDC,hPen));
    }

    giPlotData = 1;
    bBusy = 0;

    return 0;
}


/*---------------------------------------------------------------

   PlotDACData

---------------------------------------------------------------*/
int PlotDACData(HWND hWnd, LPPAINTSTRUCT lpPaint, HDC hDC)
{

    int i;

    int     iX0 = 50;
    int     iY0 = 50;
    int     iY1;

    double  dXScale;
    double  dYScale;

    RECT    Rect;
    HPEN    hPen;

    static  int bBusy = 0;

    if (bBusy) return 1;
    bBusy = 1;

    GetClientRect(hWnd,&Rect);


    dXScale = (double)(Rect.right  - Rect.left-2*iX0) / (giSizeOfPlotData-1);
    iY1     = (Rect.bottom - Rect.top-iY0);

    dYScale = (double)(Rect.bottom - Rect.top -2*iY0) / 4096.0;



    //Draw the plot window frame
    //--------------------------------------------------------------------
    pPoint[0].x = Rect.left+iX0;
    pPoint[0].y = Rect.top+iY0;

    pPoint[1].x = Rect.right-iX0;
    pPoint[1].y = Rect.top+iY0;

    pPoint[2].x = Rect.right-iX0;
    pPoint[2].y = Rect.bottom-iY0;

    pPoint[3].x = Rect.left+iX0;
    pPoint[3].y = Rect.bottom-iY0;

    pPoint[4].x = Rect.left+iX0;
    pPoint[4].y = Rect.top+iY0;

    Polyline(hDC, pPoint, 5);

    for (i=1;i<10;i++)
    {
        if (i==5)
        {
            pPoint[0].x = Rect.left+iX0/2 ;
            pPoint[0].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;

            pPoint[1].x = Rect.right-iX0/2;
            pPoint[1].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;
            Polyline(hDC, pPoint, 2);
        }
        else
        {
            pPoint[0].x = Rect.left+iX0 ;
            pPoint[0].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;

            pPoint[1].x = Rect.right-iX0;
            pPoint[1].y = Rect.top+iY0  + (Rect.bottom-Rect.top-2*iY0) / 10 * i;
            Polyline(hDC, pPoint, 2);
        }
    }


    if (giPlotData)
    {
        hPen = SelectObject(hDC,CreatePen(PS_SOLID,1,0xFF0000));
        for (i=0;i<giSizeOfPlotData;i++)
        {
            pPoint[i].x = iX0 + (int) (i * dXScale);
            pPoint[i].y = iY1 - (int) ((gdVoltData[i] * dYScale));
        }
        Polyline(hDC, pPoint, giSizeOfPlotData);
        DeleteObject(SelectObject(hDC,hPen));

    }

    giPlotData = 1;
    bBusy = 0;

    return 0;
}




/*---------------------------------------------------------------

   PrepareNextPlot

---------------------------------------------------------------*/
int PrepareNextPlot(short *psBuffer, int iCount)
{
    int i;

    giNewPlot        = 1;
    giSizeOfPlotData = iCount;

    giPlotMode = PLOT_ADC;

    for (i=0;i<iCount;i++)
    {
        gdVoltData[i] = ADC_TO_VOLT(psBuffer[i],gdHalfRange,gdADCOffset);

        if (i >= BUFFER_SIZE) break;
    }

    GetClientRect(hWndMain,&gClientRect);
    InvalidateRect(hWndMain,&gClientRect,TRUE);
    SendMessage(hWndMain,WM_PAINT,0,0);
    return 1;
}

/*---------------------------------------------------------------

   PrepareDACPlot

---------------------------------------------------------------*/
int PrepareDACPlot(short *psBuffer, int iCount)
{
    int i;

    giNewPlot        = 1;
    giSizeOfPlotData = iCount;

    giPlotMode = PLOT_DAC;

    for (i=0;i<iCount;i++)
    {
        gdVoltData[i] = (double) psBuffer[i];

        if (i >= BUFFER_SIZE) break;
    }

    GetClientRect(hWndMain,&gClientRect);
    InvalidateRect(hWndMain,&gClientRect,TRUE);
    SendMessage(hWndMain,WM_PAINT,0,0);
    return 1;
}

/*---------------------------------------------------------------

   SetChannelMenu

---------------------------------------------------------------*/
int SetChannelMenu(HMENU hMenu,int iType)
{

    int i;
    MENUITEMINFO mii;
    char acText[15];

    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask  = MIIM_TYPE;
    mii.fType  = MFT_STRING;

    // 09.06.098 mk: allocate a buffer to hold the string
    //---------------------------------------------------
    mii.dwTypeData =(LPSTR)acText;

    if (iType)
    {
        mii.wID    = IDM_ADC_0;
        mii.cch = 7;
        wsprintf(mii.dwTypeData," ADC 0 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_1;
        wsprintf(mii.dwTypeData," ADC 1 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_2;
        wsprintf(mii.dwTypeData," ADC 2 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_3;
        wsprintf(mii.dwTypeData," ADC 3 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_4;
        wsprintf(mii.dwTypeData," ADC 4 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_5;
        wsprintf(mii.dwTypeData," ADC 5 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_6;
        wsprintf(mii.dwTypeData," ADC 6 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_7;
        wsprintf(mii.dwTypeData," ADC 7 ");
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        EnableMenuItem(hMenu,IDM_ADC_8, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_9, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_A, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_B, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_C, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_D, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_E, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu,IDM_ADC_F, MF_BYCOMMAND | MF_ENABLED);
    }
    else
    {
        mii.wID    = IDM_ADC_0;
        //wsprintf(acText,"%s",(LPSTR)(" ADC 0 / ADC 8"));
        wsprintf((LPSTR)mii.dwTypeData,(LPSTR)"%s",(LPSTR)(" ADC 0 / ADC 8"));
        //mii.dwTypeData =(LPSTR)acText;
        mii.cch = 14;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_1;
        wsprintf(mii.dwTypeData," ADC 1 / ADC 9");
        mii.cch = 14;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_2;
        wsprintf(mii.dwTypeData," ADC 2 / ADC 10");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_3;
        wsprintf(mii.dwTypeData," ADC 3 / ADC 11");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_4;
        wsprintf(mii.dwTypeData," ADC 4 / ADC 12");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_5;
        wsprintf(mii.dwTypeData," ADC 5 / ADC 13");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_6;
        wsprintf(mii.dwTypeData," ADC 6 / ADC 14");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        mii.wID    = IDM_ADC_7;
        wsprintf(mii.dwTypeData," ADC 7 / ADC 15");
        mii.cch = 15;
        i=SetMenuItemInfo(hMenu, mii.wID, FALSE, &mii);

        EnableMenuItem(hMenu,IDM_ADC_8, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_9, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_A, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_B, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_C, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_D, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_E, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu,IDM_ADC_F, MF_BYCOMMAND | MF_GRAYED);
    }
    return i;
}