#include <windows.h>

#include <stdio.h>
#include <conio.h>
#include <time.h>

#define TEST_TEXT_1 "abcdef ghijkl mnopqr stuvwxyz ABCDEF GHIJKL MNOPQR STUVWXYZ 1234567890"
#define TEST_TEXT_2 "abcdef"
#define TEST_TEXT   TEST_TEXT_2

struct SME9x00Port
{
    BOOL m_bPortActive;
    char m_szPortName[16];
    BOOL m_bRS485;
};

#define MAX_PORTS_PER_BOARD 32

struct SME9x00Board
{
    char            m_szBoardID[256];   // Hardware string (from registry) uniquely identifying
                                        // the board - for all systems except Windows NT
    int             m_iBoardNumber;     // Number uniquely identifying the board - only for
                                        // windows NT
    unsigned short  m_usDeviceId;       // 9108, 9158, 9074 usw.
    unsigned long   m_ulSerialNumber;
    SME9x00Port     m_arrPorts[MAX_PORTS_PER_BOARD];
};

#define MAX_BOARDS  32

SME9x00Board    arrBoards[MAX_BOARDS];

int no_boards;

int baud_rates[] = {110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};

#define NO_BAUD_RATES   ( sizeof(baud_rates) / sizeof(int) )

struct sCOMMTest
{
    int     m_iFirstPortNo;
    int     m_iFirstBoardPortNo;
    int     m_iSecondPortNo;
    int     m_iSecondBoardPortNo;
    BOOL    m_bTestFailed;
    BOOL    m_bTestAborted;
    BOOL    m_bOpenFirstPortFailed;
    BOOL    m_bOpenSecondPortFailed;
    BOOL    m_bRejectOpenTwiceFailed;
    BOOL    m_bOpenStdPortFailed;
    BOOL    m_bSendFailed[NO_BAUD_RATES][2];
    BOOL    m_bRTS_CTSFailed[2];
    BOOL    m_bDTR_DSRFailed[2];
    BOOL    m_bRS485;
};

#define MAX_TESTS   20

sCOMMTest arrTests[MAX_TESTS];

char sz_rx_text[256];

HANDLE hCommPort1;
HANDLE hCommPort2;

#define WINDOWS_NT      0
#define WINDOWS_2000    1
#define WINDOWS_XP      2
#define WINDOWS_95      3
#define WINDOWS_98      4
#define WINDOWS_ME      5

BOOL GetSystemVersion(int& platform_version);
void BuildBoardList(int platform_version);
DWORD WINAPI SendText(PVOID lpParameter);
DWORD WINAPI ReceiveText(PVOID lpParameter);
int TransmitText(HANDLE h_tx, HANDLE h_rx);

void main(int argc, char* argv[])
{
    printf("\n\n");
    printf(" ME-9000 / ME-9100 / ME-9200 / ME-9300 Test Program\n");
    printf("====================================================\n");
    printf("\n");

    // Zero out the entire array 'arrTests'. In particular this sets all BOOL's
    // to 'FALSE'. We assume all tests will succeed

    memset( &arrTests[0], 0, sizeof(arrTests) );

    int platform_version;

    GetSystemVersion(platform_version);

    BuildBoardList(platform_version);

    if(no_boards == 0)
    {
        printf("No ME9x00 board found - Press any key to terminate\n\n");

        getch();

        return;
    }

    int no_ports = 0;
    char buffer[128];

    int board_index = 0;

    if(no_boards > 1)
    {
        printf("The following ME-9000 / 9100 / 9200 / 9300 RS232 COM Ports were found:\n\n");

        for(int index = 0; index < no_boards; index++)
        {
            printf("%2d      Device ID: 0x%4X      Serial Number: 0x%8X\n\n",
                      index + 1, arrBoards[index].m_usDeviceId, arrBoards[index].m_ulSerialNumber);
        }

        printf("Number of board to test (RETURN to terminate): ");

        while(TRUE)
        {
            gets(&buffer[0]);

            printf("/n/n");

            if(buffer[0] == 0)
            {
                return;
            }

            if( sscanf(&buffer[0], "%d", &board_index) != 1 )
            {
                continue;
            }

            if( (1 <= board_index)&&(board_index <= no_boards) )
            {
                --board_index;

                break;
            }
        }
    }

    printf("Testing board - Device ID: 0x%4X      Serial Number: 0x%8X\n\n",
                            arrBoards[board_index].m_usDeviceId, arrBoards[board_index].m_ulSerialNumber);

    SME9x00Port* p_first_port = NULL;

    int no_first_port = 0;

    // Test RS232 port connections

    for(int port_index = 0; port_index < MAX_PORTS_PER_BOARD; port_index++)
    {
        SME9x00Port* p_port = &arrBoards[board_index].m_arrPorts[port_index];

        if( (p_port->m_bPortActive)&&(!p_port->m_bRS485) )
        {
            if(p_first_port != NULL)
            {
                sscanf(&p_first_port->m_szPortName[0], "COM%d", &arrTests[no_ports].m_iFirstPortNo);

                arrTests[no_ports].m_iFirstBoardPortNo = no_first_port;

                sscanf(&p_port->m_szPortName[0], "COM%d", &arrTests[no_ports].m_iSecondPortNo);

                arrTests[no_ports].m_iSecondBoardPortNo = port_index + 1;

                arrTests[no_ports].m_bRS485 = FALSE;

                if(++no_ports >= MAX_TESTS)
                {
                    break;
                }

                p_first_port = NULL;
            }
            else
            {
                p_first_port = p_port;

                no_first_port = port_index + 1;
            }
        }
    }

    p_first_port = NULL;

    no_first_port = 0;

    // Test RS485 port connections

    for(port_index = 0; port_index < MAX_PORTS_PER_BOARD; port_index++)
    {
        SME9x00Port* p_port = &arrBoards[board_index].m_arrPorts[port_index];

        if( (p_port->m_bPortActive)&&(p_port->m_bRS485) )
        {
            if(p_first_port != NULL)
            {
                sscanf(&p_first_port->m_szPortName[0], "COM%d", &arrTests[no_ports].m_iFirstPortNo);

                arrTests[no_ports].m_iFirstBoardPortNo = no_first_port;

                sscanf(&p_port->m_szPortName[0], "COM%d", &arrTests[no_ports].m_iSecondPortNo);

                arrTests[no_ports].m_iSecondBoardPortNo = port_index + 1;

                arrTests[no_ports].m_bRS485 = TRUE;

                if(++no_ports >= MAX_TESTS)
                {
                    break;
                }

                p_first_port = NULL;
            }
            else
            {
                p_first_port = p_port;

                no_first_port = port_index + 1;
            }
        }
    }

    if(no_ports == 0)
    {
        printf("No connections to test. Press any key to terminate\n");

        getch();

        return;
    }

    char file_name[32];

    if(arrBoards[board_index].m_usDeviceId < 0x9100)
    {
        strcpy(&file_name[0], "chk9000.txt");
    }
    else if(arrBoards[board_index].m_usDeviceId < 0x9200)
    {
        strcpy(&file_name[0], "chk9100.txt");
    }
    else if(arrBoards[board_index].m_usDeviceId < 0x9300)
    {
        strcpy(&file_name[0], "chk9200.txt");
    }
    else // if(arrBoards[board_index].m_usDeviceId < 0x9400)
    {
        strcpy(&file_name[0], "chk9300.txt");
    }

    printf("Writing results to file %s\n\n", &file_name[0]);

    FILE* p_file = fopen(&file_name[0], "wt");

    if(p_file == NULL)
    {
        printf("File %s cannot be created - Press any key to terminate\n\n", file_name);

        getch();

        return;
    }

    time_t ltime;

    time(&ltime);

    localtime(&ltime);

    struct tm *today = localtime( &ltime );

    // Allocate an array with a BOOL for each test up to a maximum of 'MAX_TESTS' tests,
    // for each baud rate and for each of the two possible directions
    // (port 1 -> port 2, port 2 -> port 1).

    BOOL* p_b_results = new BOOL[MAX_TESTS * ( sizeof(baud_rates) / sizeof(int) ) * 2];

    // Initialise all slots with TRUE -> we assume all tests will be successful!!!

    for(int test = 0; test < MAX_TESTS; test++)
    {
        for(int baud_rate = 0; baud_rate < sizeof(baud_rates) / sizeof(int); baud_rate++)
        {
            for(int direction = 0; direction < 2; direction++)
            {
                p_b_results[test * baud_rate * direction] = TRUE;
            }
        }
    }

    char ch;

    for(int index_port = 0; index_port < no_ports; index_port++)
    {
        printf("\n\n");

        printf("Testing communication between ports COM%d and COM%d\n\n", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo);

        char win32_port_name[80];

        // Build the WIN32 device name of the first port

        sprintf(win32_port_name, "\\\\.\\COM%d", arrTests[index_port].m_iFirstPortNo);

        // Try to open the first port.

        hCommPort1 = CreateFile(win32_port_name,
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                0,
                                OPEN_EXISTING,
                                0,
                                0                   );

        if(hCommPort1 == INVALID_HANDLE_VALUE)
        {
            arrTests[index_port].m_bTestFailed = TRUE;

            arrTests[index_port].m_bOpenFirstPortFailed = TRUE;

            printf("COM%d could not be opened\n", arrTests[index_port].m_iFirstPortNo);

            continue;
        }

        // Build the WIN32 device name of the second port

        sprintf(win32_port_name, "\\\\.\\COM%d", arrTests[index_port].m_iSecondPortNo);

        // Try to open the second port.

        hCommPort2 = CreateFile(win32_port_name,
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                0,
                                OPEN_EXISTING,
                                0,
                                0                   );

        if(hCommPort2 == INVALID_HANDLE_VALUE)
        {
            arrTests[index_port].m_bTestFailed = TRUE;

            arrTests[index_port].m_bOpenSecondPortFailed = TRUE;

            printf("COM%d could not be opened\n", arrTests[index_port].m_iSecondPortNo);

            CloseHandle(hCommPort1);

            continue;
        }


        // Set timeouts for the ports

        COMMTIMEOUTS timeouts;

        timeouts.ReadIntervalTimeout            = 20;
        timeouts.ReadTotalTimeoutMultiplier     = 10;
        timeouts.ReadTotalTimeoutConstant       = 100;
        timeouts.WriteTotalTimeoutMultiplier    = 10;
        timeouts.WriteTotalTimeoutConstant      = 100;

/*
        timeouts.ReadIntervalTimeout            = 200;
        timeouts.ReadTotalTimeoutMultiplier     = 100;
        timeouts.ReadTotalTimeoutConstant       = 1000;
        timeouts.WriteTotalTimeoutMultiplier    = 100;
        timeouts.WriteTotalTimeoutConstant      = 1000;
*/

        // Timeouts for first port

        SetCommTimeouts(hCommPort1, &timeouts);

        // Timeouts for second port

        SetCommTimeouts(hCommPort2, &timeouts);

        /*--- communication test with all BAUD rates ------------------------*/
        for(int index_baud = 0; index_baud < NO_BAUD_RATES; index_baud++)
        {
            if(index_baud == 9)
            {
                // Set baud rate, parity etc. for the ports

                DCB dcb;

                FillMemory(&dcb, sizeof(dcb), 0);

                dcb.DCBlength = sizeof(dcb);

                // Copy the string "baud=xxxx parity=N data=8 stop=1" to a local buffer
                // due to WIN32 API error under WIN95 - see Microsoft Knowledge Base

                char sz_comm_settings[64];

                sprintf( &sz_comm_settings[0], "baud=%d parity=N data=8 stop=1", baud_rates[index_baud] );

                BuildCommDCB(&sz_comm_settings[0], &dcb);

                // Setting for first port

                SetCommState(hCommPort1, &dcb);

                // Setting for second port

                SetCommState(hCommPort2, &dcb);

                if( kbhit() )
                {
                    ch = getch();

                    if(ch == 27)
                    {
                        arrTests[index_port].m_bTestAborted = TRUE;

                        CloseHandle(hCommPort2);

                        CloseHandle(hCommPort1);

                        break;
                    }
                }

                // Transmit from first port to second port

                printf( "Send with %6d Baud: COM%d->COM%d: ",
                    baud_rates[index_baud],
                    arrTests[index_port].m_iFirstPortNo,
                    arrTests[index_port].m_iSecondPortNo);


                if(TransmitText(hCommPort1, hCommPort2) == 0)
                {
                    printf("ok");
                }
                else
                {
                    arrTests[index_port].m_bTestFailed = TRUE;

                    arrTests[index_port].m_bSendFailed[index_baud][0] = TRUE;

                    printf("--");
                }

                if( kbhit() )
                {
                    ch = getch();

                    if(ch == 27)
                    {
                        arrTests[index_port].m_bTestAborted = TRUE;

                        CloseHandle(hCommPort2);

                        CloseHandle(hCommPort1);

                        break;
                    }
                }

                // Transmit from second port to first port

                printf( "   COM%d->COM%d: ",
                    //baud_rates[index_baud],
                    arrTests[index_port].m_iSecondPortNo,
                    arrTests[index_port].m_iFirstPortNo);


                if(TransmitText(hCommPort2, hCommPort1) == 0)
                {
                    printf("ok");
                }
                else
                {
                    arrTests[index_port].m_bTestFailed = TRUE;

                    arrTests[index_port].m_bSendFailed[index_baud][1] = TRUE;

                    printf("--");
                }

                if( arrTests[index_port].m_bSendFailed[index_baud][1] |
                    arrTests[index_port].m_bSendFailed[index_baud][0])
                {
                    printf("\tError\n");
                }
                else
                {
                    printf("\tSuccess\n");
                }
            }
        }

        if( arrTests[index_port].m_bTestAborted )
        {
            continue;
        }

        printf("\n");



        if( !arrTests[index_port].m_bRS485 )
        {
            /*--- test the control lines ----------------------------------------*/

            //printf("Test COM%d, RTS <--> COM%d, CTS ...    ", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo);
            printf("Test RTS(COM%d)-CTS(COM%d): ",
                arrTests[index_port].m_iFirstPortNo,
                arrTests[index_port].m_iSecondPortNo);

            EscapeCommFunction(hCommPort1, CLRRTS);

            DWORD dw_status;

            GetCommModemStatus(hCommPort2, &dw_status);

            if(dw_status & MS_CTS_ON)
            {
                arrTests[index_port].m_bRTS_CTSFailed[0] = TRUE;
            }

            EscapeCommFunction(hCommPort1, SETRTS);

            GetCommModemStatus(hCommPort2, &dw_status);

            if( !(dw_status & MS_CTS_ON) )
            {
                arrTests[index_port].m_bRTS_CTSFailed[0] = TRUE;
            }

            EscapeCommFunction(hCommPort1, CLRRTS);

            GetCommModemStatus(hCommPort2, &dw_status);

            if(dw_status & MS_CTS_ON)
            {
                arrTests[index_port].m_bRTS_CTSFailed[0] = TRUE;
            }

            if( !arrTests[index_port].m_bRTS_CTSFailed[0] )
            {
                printf("ok");
            }
            else
            {
                arrTests[index_port].m_bTestFailed = TRUE;

                printf("--");
            }

            printf("   RTS(COM%d)-CTS(COM%d): ",
                arrTests[index_port].m_iSecondPortNo,
                arrTests[index_port].m_iFirstPortNo );

            EscapeCommFunction(hCommPort2, CLRRTS);

            GetCommModemStatus(hCommPort1, &dw_status);

            if(dw_status & MS_CTS_ON)
            {
                arrTests[index_port].m_bRTS_CTSFailed[1] = TRUE;
            }

            EscapeCommFunction(hCommPort2, SETRTS);

            GetCommModemStatus(hCommPort1, &dw_status);

            if( !(dw_status & MS_CTS_ON) )
            {
                arrTests[index_port].m_bRTS_CTSFailed[1] = TRUE;
            }

            EscapeCommFunction(hCommPort2, CLRRTS);

            GetCommModemStatus(hCommPort1, &dw_status);

            if(dw_status & MS_CTS_ON)
            {
                arrTests[index_port].m_bRTS_CTSFailed[1] = TRUE;
            }

            if( !arrTests[index_port].m_bRTS_CTSFailed[1] )
            {
                printf("ok");
            }
            else
            {
                arrTests[index_port].m_bTestFailed = TRUE,

                printf("--");
            }

            if( arrTests[index_port].m_bRTS_CTSFailed[1] |
                arrTests[index_port].m_bRTS_CTSFailed[0])
            {
                printf("\tError\n");
            }
            else
            {
                printf("\tSuccess\n");
            }


            printf("Test DTR(COM%d)-DSR(COM%d): ",
                arrTests[index_port].m_iFirstPortNo,
                arrTests[index_port].m_iSecondPortNo);

            EscapeCommFunction(hCommPort1, CLRDTR);

            GetCommModemStatus(hCommPort2, &dw_status);

            if(dw_status & MS_DSR_ON)
            {
                arrTests[index_port].m_bDTR_DSRFailed[0] = TRUE;
            }

            EscapeCommFunction(hCommPort1, SETDTR);

            GetCommModemStatus(hCommPort2, &dw_status);

            if( !(dw_status & MS_DSR_ON) )
            {
                arrTests[index_port].m_bDTR_DSRFailed[0] = TRUE;
            }

            EscapeCommFunction(hCommPort1, CLRDTR);

            GetCommModemStatus(hCommPort2, &dw_status);

            if(dw_status & MS_DSR_ON)
            {
                arrTests[index_port].m_bDTR_DSRFailed[0] = TRUE;
            }

            if( !arrTests[index_port].m_bDTR_DSRFailed[0] )
            {
                printf("ok");
            }
            else
            {
                arrTests[index_port].m_bTestFailed = TRUE;

                printf("--");
            }

            printf("   DTR(COM%d)-DSR(COM%d): ",
                arrTests[index_port].m_iSecondPortNo,
                arrTests[index_port].m_iFirstPortNo );

            EscapeCommFunction(hCommPort2, CLRDTR);

            GetCommModemStatus(hCommPort1, &dw_status);

            if(dw_status & MS_DSR_ON)
            {
                arrTests[index_port].m_bDTR_DSRFailed[1] = TRUE;
            }

            EscapeCommFunction(hCommPort2, SETDTR);

            GetCommModemStatus(hCommPort1, &dw_status);

            if( !(dw_status & MS_DSR_ON) )
            {
                arrTests[index_port].m_bDTR_DSRFailed[1] = TRUE;
            }

            EscapeCommFunction(hCommPort2, CLRDTR);

            GetCommModemStatus(hCommPort1, &dw_status);

            if(dw_status & MS_DSR_ON)
            {
                arrTests[index_port].m_bDTR_DSRFailed[1] = TRUE;
            }

            if( !arrTests[index_port].m_bDTR_DSRFailed[1] )
            {
                printf("ok");
            }
            else
            {
                arrTests[index_port].m_bTestFailed = TRUE;

                printf("--");
            }

            if( arrTests[index_port].m_bDTR_DSRFailed[0] |
                arrTests[index_port].m_bDTR_DSRFailed[1])
            {
                printf("\tError\n");
            }
            else
            {
                printf("\tSuccess\n");
            }
        }

        // Close both ports.

        CloseHandle(hCommPort2);

        CloseHandle(hCommPort1);
    }

    printf("\n");
    printf("Tests completed");

    printf("\n");

    int no_successful = 0;

    for(index_port = 0; index_port < no_ports; index_port++)
    {
        if( ( !arrTests[index_port].m_bTestFailed )&&( !arrTests[index_port].m_bTestAborted ) )
        {
            ++no_successful;
        }
    }

    if(no_successful > 0)
    {
        printf("The following connections were tested successfully to completion:\n");

        for(int index_port = 0; index_port < no_ports; index_port++)
        {
            if( ( !arrTests[index_port].m_bTestFailed )&&( !arrTests[index_port].m_bTestAborted ) )
            {
                printf("Connection COM%d <--> COM%d\n", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo);
            }
        }

        printf("\n\n");
    }

    int no_aborted = 0;

    for(index_port = 0; index_port < no_ports; index_port++)
    {
        if( ( !arrTests[index_port].m_bTestFailed )&&( arrTests[index_port].m_bTestAborted ) )
        {
            ++no_aborted;
        }
    }

    if(no_aborted > 0)
    {
        printf("The following tests were aborted without errors:\n");

        for(int index_port = 0; index_port < no_ports; index_port++)
        {
            if( ( !arrTests[index_port].m_bTestFailed )&&( arrTests[index_port].m_bTestAborted ) )
            {
                printf("Connection COM%d <--> COM%d\n", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo);
            }
        }

        printf("\n\n");
    }

    int no_failed = 0;

    for(index_port = 0; index_port < no_ports; index_port++)
    {
        if(arrTests[index_port].m_bTestFailed)
        {
            ++no_failed;
        }
    }

    if(no_failed > 0)
    {
        for(int index_port = 0; index_port < no_ports; index_port++)
        {
            if(arrTests[index_port].m_bTestFailed)
            {
                printf("The following test failed:\n\n");

                printf("Connection COM%d <--> COM%d\n\n", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo);

                if(arrTests[index_port].m_bOpenFirstPortFailed)
                {
                    printf("Could not open COM%d\n", arrTests[index_port].m_iFirstPortNo);
                }

                if(arrTests[index_port].m_bOpenSecondPortFailed)
                {
                    printf("Could not open COM%d\n", arrTests[index_port].m_iSecondPortNo);
                }

                for(int index_baud = 0; index_baud < NO_BAUD_RATES; index_baud++)
                {
                    if(arrTests[index_port].m_bSendFailed[index_baud][0])
                    {
                        printf("Send COM%d -> COM%d - Baud Rate: %6d   FAILED\n", arrTests[index_port].m_iFirstPortNo, arrTests[index_port].m_iSecondPortNo, baud_rates[index_baud]);
                    }

                    if(arrTests[index_port].m_bSendFailed[index_baud][1])
                    {
                        printf("Send COM%d -> COM%d - Baud Rate: %6d   FAILED\n", arrTests[index_port].m_iSecondPortNo, arrTests[index_port].m_iFirstPortNo, baud_rates[index_baud]);
                    }
                }

                if(arrTests[index_port].m_bRTS_CTSFailed[0])
                {
                    printf("Test COM%d, RTS <--> COM%d, CTS   FAILED\n", arrTests[index_port].m_iFirstPortNo , arrTests[index_port].m_iSecondPortNo);
                }

                if(arrTests[index_port].m_bRTS_CTSFailed[1])
                {
                    printf("Test COM%d, RTS <--> COM%d, CTS   FAILED\n", arrTests[index_port].m_iSecondPortNo , arrTests[index_port].m_iFirstPortNo);
                }

                if(arrTests[index_port].m_bDTR_DSRFailed[0])
                {
                    printf("Test COM%d, DTR <--> COM%d, DTS   FAILED\n", arrTests[index_port].m_iFirstPortNo , arrTests[index_port].m_iSecondPortNo);
                }

                if(arrTests[index_port].m_bDTR_DSRFailed[1])
                {
                    printf("Test COM%d, DTR <--> COM%d, DTS   FAILED\n", arrTests[index_port].m_iSecondPortNo , arrTests[index_port].m_iFirstPortNo);
                }

                if(arrTests[index_port].m_bTestAborted)
                {
                    printf("\n             Test aborted\n");
                }
            }


        }

        printf("\n\n");
    }

    fprintf(p_file,
        "=======================================\n"
        "ME-9x00 test report sheet\n"
        "=======================================\n");

    fprintf(p_file,
        "%d\toverall test result\n"
        "=======================================\n",
        (no_failed == 0) ? 1 : 0);

    for(index_port = 0; index_port < no_ports; index_port++)
    {
        if( !arrTests[index_port].m_bTestFailed )
        {
            fprintf(p_file, "1\t(Port%02d <--> Port%02d)\n", arrTests[index_port].m_iFirstBoardPortNo, arrTests[index_port].m_iSecondBoardPortNo);
        }
        else
        {
            fprintf(p_file, "0\t(Port%02d <--> Port%02d)\n", arrTests[index_port].m_iFirstBoardPortNo, arrTests[index_port].m_iSecondBoardPortNo);
        }
    }


    fprintf(p_file,
        "\n"
        "Boundary conditions\n"
        "=======================================\n");

    fprintf(p_file,
        "time stamp:\n"
        "\tDate:\t%02d.%02d.%04d\n"
        "\tTime:\t%02d:%02d:%02d\n",
        today->tm_mday,today->tm_mon + 1,today->tm_year + 1900,
        today->tm_hour, today->tm_min, today->tm_sec);

    fprintf(p_file,
        "Tested board:\n"
        "\tDevice ID:\t%4X\n"
        "\tSerial No:\t%8X\n",
        arrBoards[board_index].m_usDeviceId,
        arrBoards[board_index].m_ulSerialNumber);

    fprintf(p_file,
        "\n\n"
        "Detailed error report\n"
        "=======================================\n");

    for(index_port = 0; index_port < no_ports; index_port++)
    {
        fprintf(p_file, "\n");

        if(arrTests[index_port].m_bTestFailed)
        {
            if(arrTests[index_port].m_bOpenFirstPortFailed)
            {
                fprintf(p_file, "Could not open Port%02d\n", arrTests[index_port].m_iFirstBoardPortNo);
            }

            if(arrTests[index_port].m_bOpenSecondPortFailed)
            {
                fprintf(p_file, "Could not open Port%02d\n", arrTests[index_port].m_iSecondBoardPortNo);
            }

            for(int index_baud = 0; index_baud < NO_BAUD_RATES; index_baud++)
            {
                if(arrTests[index_port].m_bSendFailed[index_baud][0])
                {
                    fprintf(p_file, "Send Port%02d -> Port%02d - Baud Rate: %6d   0\n", arrTests[index_port].m_iFirstBoardPortNo, arrTests[index_port].m_iSecondBoardPortNo, baud_rates[index_baud]);
                }

                if(arrTests[index_port].m_bSendFailed[index_baud][1])
                {
                    fprintf(p_file, "Send Port%02d -> Port%2d - Baud Rate: %6d   0\n", arrTests[index_port].m_iSecondBoardPortNo, arrTests[index_port].m_iFirstBoardPortNo, baud_rates[index_baud]);
                }
            }

            if(arrTests[index_port].m_bRTS_CTSFailed[0])
            {
                fprintf(p_file, "Test Port%02d, RTS <--> Port%02d, CTS   0\n", arrTests[index_port].m_iFirstBoardPortNo , arrTests[index_port].m_iSecondBoardPortNo);
            }

            if(arrTests[index_port].m_bRTS_CTSFailed[1])
            {
                fprintf(p_file, "Test Port%02d, RTS <--> Port%02d, CTS   0\n", arrTests[index_port].m_iSecondBoardPortNo , arrTests[index_port].m_iFirstBoardPortNo);
            }

            if(arrTests[index_port].m_bDTR_DSRFailed[0])
            {
                fprintf(p_file, "Test Port%02d, DTR <--> Port%02d, DTS   0\n", arrTests[index_port].m_iFirstBoardPortNo , arrTests[index_port].m_iSecondBoardPortNo);
            }

            if(arrTests[index_port].m_bDTR_DSRFailed[1])
            {
                fprintf(p_file, "Test Port%02d, DTR <--> Port%02d, DTS   0\n", arrTests[index_port].m_iSecondBoardPortNo , arrTests[index_port].m_iFirstBoardPortNo);
            }
        }
    }

    fprintf(p_file,
        "=======================================\n"
        "End of test sheet\n"
        "=======================================\n");

    fclose(p_file);


    Sleep(800);

//  printf("Press any key to terminate\n");
//  getch();
}

BOOL GetSystemVersion(int& platform_version)
{
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;

    // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
    //
    // If that fails, try using the OSVERSIONINFO structure.

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
    {
        // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

        osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
        if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) )
            return FALSE;
    }

    switch (osvi.dwPlatformId)
    {
    case VER_PLATFORM_WIN32_NT:

      // Test for the product.

         if ( osvi.dwMajorVersion <= 4 )
         {
            platform_version = WINDOWS_NT;

            return TRUE;
         }
         else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
         {
            platform_version = WINDOWS_2000;

            return TRUE;
         }
         else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
         {
            platform_version = WINDOWS_NT;

            return TRUE;
         }
         else
         {
             return FALSE;
         }

         break;

    case VER_PLATFORM_WIN32_WINDOWS:

        if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
        {
            platform_version = WINDOWS_95;

            return TRUE;
        }
        else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
        {
            platform_version = WINDOWS_98;

            return TRUE;
        }
        else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
        {
            platform_version = WINDOWS_ME;

            return TRUE;
        }
        else
        {
            return FALSE;
        }

        break;

    default:

        return FALSE;

        break;
    }
}


void BuildBoardList(int platform_version)
{
    FillMemory(&arrBoards[0], MAX_BOARDS * sizeof(SME9x00Board), 0);

    no_boards = 0;

    switch(platform_version)
    {
    case WINDOWS_2000:
    case WINDOWS_XP:

        HKEY h_me9100_enum;

        // Open the registry key

        long l_error;

        l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                "SYSTEM\\CurrentControlSet\\Services\\me9100\\Enum",
                                0,
                                KEY_ALL_ACCESS,
                                &h_me9100_enum                                          );

        if(l_error != ERROR_SUCCESS)
        {
            return;
        }

        DWORD dw_index;
        dw_index = 0;

        // Investigate entries 0, 1, 2  etc under
        // HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\me9100\Enum"

        while(TRUE)
        {
            char sz_key_name[8];

            sprintf(&sz_key_name[0], "%d", dw_index);

            ++dw_index;

            DWORD dw_type;

            char sz_val[256];
            DWORD dw_val_length = 256;

            l_error = RegQueryValueEx(  h_me9100_enum,                      // handle to key
                                        &sz_key_name[0],                    // value name
                                        NULL,                               // reserved
                                        &dw_type,                           // type buffer
                                        (unsigned char *)&sz_val[0],        // data buffer
                                        &dw_val_length                  );  // size of data buffer

            if(l_error != ERROR_SUCCESS)
            {
                // No more registry entries -> end iteration

                break;
            }

            if(dw_type == REG_SZ)
            {
                // Value is a character string as required

                // Is value of the form MF\PCI#VEN_1402&DEV_9§§§&SUBSYS_§§§§§§§§&REV_§§\§&§§§§§§§§&§&§§#Child§§§§
                // where the § are numerals 0 .. 9

                if( strnicmp( &sz_val[0], "MF\\PCI#VEN_1402&DEV_9", strlen("MF\\PCI#VEN_1402&DEV_9") ) == 0 )
                {
                    // Device ID should be 90xx or 91xx or 92xx 0r 93xx

                    if( ( '0' <= sz_val[21] )&&( sz_val[21] <= '3' ) )
                    {
                        // Extract the board indentifier, this is the entire string up to the last '\'

                        char sz_board_id[256];

                        strcpy(&sz_board_id[0], &sz_val[0]);

                        char* p_char = strrchr(&sz_board_id[0], '\\');

                        if(p_char != NULL)
                        {
                            *p_char = 0;
                        }

                        // Using the identifier, look to see if we have already found ports
                        // for this same board

                        int index_board = -1;

                        for(int index = 0; index < no_boards; index++)
                        {
                            if( stricmp( &sz_board_id[0], &arrBoards[index].m_szBoardID[0] ) == 0 )
                            {
                                index_board = index;

                                break;
                            }
                        }

                        // This board is not yet in the list

                        if(index_board == -1)
                        {
                            // New board, add it to the list

                            index_board = no_boards;

                            strcpy( &arrBoards[index_board].m_szBoardID[0], &sz_board_id[0] );

                            int hex_int;

                            sscanf(&sz_val[20], "%x", &hex_int);

                            arrBoards[index_board].m_usDeviceId = (unsigned short)hex_int;

                            sscanf(&sz_val[32], "%x", &hex_int);

                            arrBoards[index_board].m_ulSerialNumber = (unsigned long)hex_int;

                            ++no_boards;
                        }

                        // Bulid the entire registry path to the port information

                        char sz_hardware_path[256];

                        strcpy(&sz_hardware_path[0], "SYSTEM\\CurrentControlSet\\Enum\\");

                        strcat( &sz_hardware_path[0], &sz_val[0] );

                        strcat(&sz_hardware_path[0], "\\Device Parameters");

                        HKEY h_me9100_device_param;

                        // Open the registry key

                        l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                                &sz_hardware_path[0],
                                                0,
                                                KEY_ALL_ACCESS,
                                                &h_me9100_device_param      );

                        if(l_error != ERROR_SUCCESS)
                        {
printf("Error opening %s\n", &sz_hardware_path[0]);

                            continue;
                        }

                        DWORD dw_value = 0xffffffff;

                        dw_val_length = sizeof(DWORD);

                        l_error = RegQueryValueEx(  h_me9100_device_param,              // handle to key
                                                    "PortIndex",                        // value name
                                                    NULL,                               // reserved
                                                    &dw_type,                           // type buffer
                                                    (unsigned char*)&dw_value,          // data buffer
                                                    &dw_val_length              );      // size of data buffer

                        if( (l_error != ERROR_SUCCESS)||(dw_value < 0)||(MAX_PORTS_PER_BOARD <= dw_value) )
                        {
                            RegCloseKey(h_me9100_device_param);

printf("Error reading PortIndex\n");

                            continue;
                        }

                        SME9x00Port* p_port = &arrBoards[index_board].m_arrPorts[dw_value];

                        dw_val_length = 16;

                        l_error = RegQueryValueEx(  h_me9100_device_param,                          // handle to key
                                                    "PortName",                                     // value name
                                                    NULL,                                           // reserved
                                                    &dw_type,                                       // type buffer
                                                    (unsigned char*)&p_port->m_szPortName[0],       // data buffer
                                                    &dw_val_length                              );  // size of data buffer


                        if(l_error != ERROR_SUCCESS)
                        {
                            RegCloseKey(h_me9100_device_param);

printf("Error reading PortName\n");

                            continue;
                        }

                        p_port->m_bPortActive = TRUE;

                        dw_val_length = sizeof(DWORD);

                        dw_value = 0;

                        l_error = RegQueryValueEx(  h_me9100_device_param,          // handle to key
                                                    "RS485",                        // value name
                                                    NULL,                           // reserved
                                                    &dw_type,                       // type buffer
                                                    (unsigned char *)&dw_value,     // data buffer
                                                    &dw_val_length              );  // size of data buffer

                        if(l_error == ERROR_SUCCESS)
                        {
                            if(dw_value == 1)
                            {
                                p_port->m_bRS485 = TRUE;
                            }
                        }

                        RegCloseKey(h_me9100_device_param);
                    }
                }
            }
        }

        RegCloseKey(h_me9100_enum);

        break;

    case WINDOWS_95:
    case WINDOWS_98:
    case WINDOWS_ME:

        HKEY h_enum_dev;

        // The sub-keys of HKEY_DYN_DATA\\Config Manager\\Enum identify the active devices
        // und have names which are simply hex addresses

        l_error = RegOpenKeyEx( HKEY_DYN_DATA,
                                "Config Manager\\Enum",
                                0,
                                KEY_ALL_ACCESS,
                                &h_enum_dev                 );

        if(l_error != ERROR_SUCCESS)
        {
            return;
        }

        dw_index = 0;

        while(TRUE)
        {
            // Look at the sub-keys one after another

            char sz_sub_key_name[16];

            DWORD dw_name_length = 16;

            l_error = RegEnumKeyEx( h_enum_dev,             // handle to key to enumerate
                                    dw_index,               // subkey index
                                    &sz_sub_key_name[0],    // subkey name
                                    &dw_name_length,        // size of subkey buffer
                                    NULL,                   // reserved
                                    NULL,                   // class string buffer
                                    NULL,                   // size of class string buffer
                                    NULL                );  // last write time

            ++dw_index;

            if(l_error != ERROR_SUCCESS)
            {
                // no more sub keys -> end iteration

                break;
            }

            // Build a string to open the sub-key

            char sz_sub_key_path[64];

            strcpy(&sz_sub_key_path[0], "Config Manager\\Enum\\");

            strcat( &sz_sub_key_path[0], &sz_sub_key_name[0] );

            HKEY h_dev;

            l_error = RegOpenKeyEx( HKEY_DYN_DATA,
                                    &sz_sub_key_path[0],
                                    0,
                                    KEY_ALL_ACCESS,
                                    &h_dev                  );

            if(l_error != ERROR_SUCCESS)
            {
                // Shouldn't really happen - we know the key exists

                continue;
            }

            // Now read the registry path to the hardware key under 'HardWareKey'

            char sz_val[256];
            DWORD dw_val_length = 256;

            DWORD dw_type;

            l_error = RegQueryValueEx(  h_dev,                              // handle to key
                                        "HardWareKey",                      // value name
                                        NULL,                               // reserved
                                        &dw_type,                           // type buffer
                                        (unsigned char *)&sz_val[0],        // data buffer
                                        &dw_val_length                  );  // size of data buffer

            if(l_error != ERROR_SUCCESS)
            {
                // Key doesn't contain a value 'HardWareKey' -> shouldn't happen

                continue;
            }

            if(dw_type == REG_SZ)
            {
                // Value is a character string as required

                // Is value of the form MF\CHILD§§§§\PCI&VEN_1402&DEV_9§§§&SUBSYS_§§§§§§§§&REV_§§..............
                // where the § are numerals 0 .. 9

                if( ( strnicmp( &sz_val[0], "MF\\CHILD", strlen("MF\\CHILD") ) == 0 )&&
                                    ( strnicmp( &sz_val[12], "\\PCI&VEN_1402&DEV_9", strlen("\\PCI&VEN_1402&DEV_9") ) == 0 ) )
                {
                    // Device ID should be 90xx or 91xx or 92xx 0r 93xx

                    if( ( '0' <= sz_val[31] )&&( sz_val[31] <= '3' ) )
                    {
                        // Extract the board indentifier, this is the entire string from 'PCI#VEN_....

                        char sz_board_id[256];

                        strcpy(&sz_board_id[0], &sz_val[13]);

                        // Using the identifier, look to see if we have already found ports
                        // for this same board

                        int index_board = -1;

                        for(int index = 0; index < no_boards; index++)
                        {
                            if( stricmp( &sz_board_id[0], &arrBoards[index].m_szBoardID[0] ) == 0 )
                            {
                                index_board = index;

                                break;
                            }
                        }

                        // This board is not yet in the list

                        if(index_board == -1)
                        {
                            // New board, add it to the list

                            index_board = no_boards;

                            strcpy( &arrBoards[index_board].m_szBoardID[0], &sz_board_id[0] );

                            int hex_int;

                            sscanf(&sz_val[30], "%x", &hex_int);

                            arrBoards[index_board].m_usDeviceId = (unsigned short)hex_int;

                            sscanf(&sz_val[42], "%x", &hex_int);

                            arrBoards[index_board].m_ulSerialNumber = (unsigned long)hex_int;

                            ++no_boards;
                        }

                        // Bulid the entire registry path to the port information

                        char sz_hardware_path[256];

                        strcpy(&sz_hardware_path[0], "Enum\\");

                        strcat( &sz_hardware_path[0], &sz_val[0] );

                        HKEY h_me9100_param;

                        // Open the registry key

                        l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                                &sz_hardware_path[0],
                                                0,
                                                KEY_ALL_ACCESS,
                                                &h_me9100_param         );

                        if(l_error != ERROR_SUCCESS)
                        {
printf("Error opening %s\n", &sz_hardware_path[0]);

                            continue;
                        }

                        // Value DeviceDesc has the form ME-9§§§/PCI Port $$ - RS§§§(COM§§) or possibly
                        // for older installations ME9§§§/PCI Port $$ - RS§§§(COM§§)

                        char sz_device_desc[64];

                        dw_val_length = 64;

                        l_error = RegQueryValueEx(  h_me9100_param,                             // handle to key
                                                    "DeviceDesc",                               // value name
                                                    NULL,                                       // reserved
                                                    &dw_type,                                   // type buffer
                                                    (unsigned char*)&sz_device_desc[0],         // data buffer
                                                    &dw_val_length                          );  // size of data buffer


                        if(l_error != ERROR_SUCCESS)
                        {
                            RegCloseKey(h_me9100_param);

printf("Error reading DeviceDesc\n");

                            continue;
                        }

                        int port_index;

                        if( sscanf(&sz_device_desc[16], "%d", &port_index) != 1 )
                        {
                            RegCloseKey(h_me9100_param);

printf("Port index not found\n");

                            continue;
                        }

                        // The index is one less than the port number contained in DeviceDesc

                        --port_index;


                        if( (port_index < 0)||(MAX_PORTS_PER_BOARD <= port_index) )
                        {
                            RegCloseKey(h_me9100_param);

printf("Port index out of bounds\n");

                            continue;
                        }

                        SME9x00Port* p_port = &arrBoards[index_board].m_arrPorts[port_index];

                        dw_val_length = 16;

                        l_error = RegQueryValueEx(  h_me9100_param,                                 // handle to key
                                                    "PortName",                                     // value name
                                                    NULL,                                           // reserved
                                                    &dw_type,                                       // type buffer
                                                    (unsigned char*)&p_port->m_szPortName[0],       // data buffer
                                                    &dw_val_length                              );  // size of data buffer


                        if(l_error != ERROR_SUCCESS)
                        {
                            RegCloseKey(h_me9100_param);

printf("Error reading PortName\n");

                            continue;
                        }

                        p_port->m_bPortActive = TRUE;

                        p_port->m_bRS485 = FALSE;

                        if( (strnicmp( &sz_device_desc[21], "RS485", strlen("RS485") ) == 0)||
                                        ( strnicmp(&sz_device_desc[22], "RS485", strlen("RS485") ) == 0) )
                        {
                            p_port->m_bRS485 = TRUE;
                        }

                        RegCloseKey(h_me9100_param);
                    }
                }
            }

            RegCloseKey(h_dev);
        }

        RegCloseKey(h_enum_dev);

        break;

    case WINDOWS_NT:

        // Search all the values under the registry key HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
        // looking for those COM ports managed by ME9100 boards

        HKEY h_serial_comm;

        // Open the registry key

        l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                "HARDWARE\\DEVICEMAP\\SERIALCOMM",
                                0,
                                KEY_ALL_ACCESS,
                                &h_serial_comm);

        if(l_error != ERROR_SUCCESS)
        {
            return;
        }

        dw_index = 0;

        // Iterate over all entries under HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM

        while(TRUE)
        {
            char sz_dev_name[24];
            DWORD dw_dev_length = 24;

            DWORD dw_type;

            char sz_port_name[24];
            DWORD dw_port_length = 24;

            l_error = RegEnumValue( h_serial_comm,                          // handle to key to query
                                    dw_index,                               // index of value to query
                                    &sz_dev_name[0],                        // value buffer
                                    &dw_dev_length,                         // size of value buffer
                                    NULL,                                   // reserved
                                    &dw_type,                               // type buffer
                                    (unsigned char*)&sz_port_name[0],       // data buffer
                                    &dw_port_length                     );  // size of data buffer

            if(l_error != ERROR_SUCCESS)
            {
                // No more registry entries -> end iteration

                break;
            }

            ++dw_index;

            if(dw_type == REG_SZ)
            {
                // Value is a character string as required

                // Parse the value name - Is it of the form B9100_<board number>_<port number>?

                int i_board_no;
                int i_port_no;

                int no_vars = sscanf(&sz_dev_name[0], "B9100_%d_%d", &i_board_no, &i_port_no);

                if( (no_vars == 2)&&(1 <= i_board_no)&&(i_board_no <= 32)&&(1 <= i_port_no)&&(i_port_no <= 32) )
                {
                    // Value name is of the correct form
                    // Parse the value string - Is it of the form COM<com number>?

                    int i_com_no;

                    no_vars = sscanf(&sz_port_name[0], "COM%d", &i_com_no);

                    if(no_vars = 1)
                    {
                        // Value string is of the correct form -> we have found another ME9100 port.

                        int index_board = -1;

                        for(int index = 0; index < no_boards; index++)
                        {
                            if(i_board_no ==  arrBoards[index].m_iBoardNumber)
                            {
                                index_board = index;

                                break;
                            }
                        }

                        // This board is not yet in the list

                        if(index_board == -1)
                        {
                            // Build the registry path for the board information

                            char sz_board_path[256];

                            strcpy(&sz_board_path[0], "SYSTEM\\CurrentControlSet\\Services\\ME9100\\");

                            char sz_board_name[8];

                            sprintf(&sz_board_name[0], "B%d", i_board_no);

                            strcat( &sz_board_path[0], &sz_board_name[0] );

                            HKEY h_board;

                            l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                                    &sz_board_path[0],
                                                    0,
                                                    KEY_ALL_ACCESS,
                                                    &h_board                    );

                            if(l_error != ERROR_SUCCESS)
                            {
                                // Shouldn't happen

printf("Error opening board key: %s\n", &sz_board_path[0]);

                                continue;
                            }

                            index_board = no_boards;

                            ++no_boards;

                            arrBoards[index_board].m_iBoardNumber = i_board_no;

                            DWORD dw_val_length = sizeof(DWORD);

                            DWORD dw_value = 0;

                            l_error = RegQueryValueEx(  h_board,                        // handle to key
                                                        "SerialNo",                     // value name
                                                        NULL,                           // reserved
                                                        &dw_type,                       // type buffer
                                                        (unsigned char *)&dw_value,     // data buffer
                                                        &dw_val_length              );  // size of data buffer

                            if(l_error == ERROR_SUCCESS)
                            {
                                arrBoards[index_board].m_ulSerialNumber = dw_value;
                            }

                            RegCloseKey(h_board);
                        }

                        SME9x00Port* p_port = &arrBoards[index_board].m_arrPorts[i_port_no - 1];

                        strcpy(&p_port->m_szPortName[0], sz_port_name);

                        p_port->m_bRS485 = FALSE;

                        // Build the registry path for the port information

                        char sz_port_path[256];

                        strcpy(&sz_port_path[0], "SYSTEM\\CurrentControlSet\\Services\\ME9100\\");

                        char sz_board_name[8];

                        sprintf(&sz_board_name[0], "B%d\\", i_board_no);

                        strcat( &sz_port_path[0], &sz_board_name[0] );

                        char sz_port_number[16];

                        sprintf(&sz_port_number[0], "Port%d", i_port_no);

                        strcat( &sz_port_path[0], &sz_port_number[0] );

                        HKEY h_port;

                        l_error = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                                &sz_port_path[0],
                                                0,
                                                KEY_ALL_ACCESS,
                                                &h_port                 );

                        if(l_error != ERROR_SUCCESS)
                        {
                            // Shouldn't happen

printf("Error opening port key: %s\n", &sz_port_path[0]);

                            continue;
                        }

                        p_port->m_bPortActive = TRUE;

                        DWORD dw_val_length = sizeof(DWORD);

                        DWORD dw_value = 0;

                        l_error = RegQueryValueEx(  h_port,                         // handle to key
                                                    "RS485",                        // value name
                                                    NULL,                           // reserved
                                                    &dw_type,                       // type buffer
                                                    (unsigned char *)&dw_value,     // data buffer
                                                    &dw_val_length              );  // size of data buffer

                        if(l_error == ERROR_SUCCESS)
                        {
                            if(dw_value == 1)
                            {
                                p_port->m_bRS485 = TRUE;
                            }
                        }

                        RegCloseKey(h_port);
                    }
                }
            }
        }


        RegCloseKey(h_serial_comm);

    }
}


DWORD WINAPI SendText(PVOID lpParameter)
{
    HANDLE h_comm = (HANDLE)lpParameter;

    DWORD dw_bytes_written;

    FlushFileBuffers(h_comm);

    WriteFile(h_comm, (void*)TEST_TEXT, strlen(TEST_TEXT) + 1, &dw_bytes_written, NULL);

    return(0);
}


DWORD WINAPI ReceiveText(PVOID lpParameter)
{
    HANDLE h_comm = (HANDLE)lpParameter;

    FlushFileBuffers(h_comm);

    DWORD dw_bytes_written;

    ReadFile(h_comm, (void*)&sz_rx_text[0], 256, &dw_bytes_written, NULL);

    return(0);
}


int TransmitText(HANDLE h_tx, HANDLE h_rx)
{
    FillMemory(&sz_rx_text[0], 256, 0);

    DWORD dw_thread_id;

    HANDLE h_receive_text = CreateThread(   NULL,               // thread attributes
                                            0x2000,             // initial stack size
                                            ReceiveText,        // thread function
                                            (void *)h_rx,       // thread argument
                                            0,                  // creation option
                                            &dw_thread_id   );  // thread identifier

    HANDLE h_send_text = CreateThread(  NULL,               // thread attributes
                                        0x2000,             // initial stack size
                                        SendText,           // thread function
                                        (void *)h_tx,       // thread argument
                                        0,                  // creation option
                                        &dw_thread_id   );  // thread identifier

    HANDLE arr_handles[2] = { h_send_text, h_receive_text };

    WaitForMultipleObjects( 2,                  // number of handles in array
                            &arr_handles[0],    // handle array
                            TRUE,               // wait for BOTH threads to finish
                            INFINITE        );  // NO time out




    if( strcmp(TEST_TEXT, &sz_rx_text[0] ) )
    {
        // Bernau
        //printf("<%s>\n", &sz_rx_text[0]);

        return(-1);
    }

    return(0);
}



