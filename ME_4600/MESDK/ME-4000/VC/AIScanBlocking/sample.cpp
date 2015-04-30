// generall example for using me4000AIScan in blocking mode
// (blocking = AIScan returns after all data collected)
// 3 channels in channel list
// process channel list 8 times
// normally you should handle errors (check the return values)

#include <stdio.h>
#include <conio.h>

#include "..\me4000dll.h"


void main(void)
{    
    unsigned int uiNoOfEntries = 3;         // number of channel list entries
    unsigned char chanList[3];              // channel list with uiNoOfEntries elements
    unsigned int ui_count = 8;              // how much time process channel list
    short sDataBuffer[3*8];                 // to store measured data, size: ui_count * uiNoOfEntries

    /* prepare chanel list */
	me4000AIMakeChannelListEntry( 
        0,                                  // ui_channel_number
        ME4000_AI_RANGE_BIPOLAR_10,         // i_range
        &chanList[0]);

    me4000AIMakeChannelListEntry( 
        1,                                  // ui_channel_number
        ME4000_AI_RANGE_BIPOLAR_10,         // i_range
        &chanList[1]);

	me4000AIMakeChannelListEntry( 
        2,                                  // ui_channel_number
        ME4000_AI_RANGE_BIPOLAR_10,         // i_range
        &chanList[2]);

    /* configure scan mode */
	me4000AIConfig(
        0,                                  // ui_board_number
        chanList,                           // in this case: [0, 1, 2]
        uiNoOfEntries,                      // uiNoOfEntries,
        ME4000_AI_INPUT_SINGLE_ENDED,       // i_sd_mode
        ME4000_AI_SIMULTANEOUS_DISABLE,     // i_simultaneous
        ME4000_VALUE_NOT_USED,              // reserved
        100,                                // ul_chan_ticks
        0,                                  // ul_scan_ticks_low
        0,                                  // ul_scan_ticks_high
        ME4000_AI_ACQ_MODE_SOFTWARE,        // i_acq_mode
        ME4000_VALUE_NOT_USED,              // i_ext_trigger_mode
        ME4000_VALUE_NOT_USED);             // i_ext_trigger_edge

    /* configure scan mode */
	me4000AIScan(
        0,                                  // ui_board_number
        ui_count, 												
        sDataBuffer, 
        ui_count * uiNoOfEntries,
        ME4000_AI_SCAN_BLOCKING,            // i_exec_mode
        ME4000_POINTER_NOT_USED,            // p_callback
        ME4000_POINTER_NOT_USED,            // callback context
        ME4000_VALUE_NOT_USED,              // ui_callback_count
        ME4000_POINTER_NOT_USED,            // p_terminate,
        ME4000_POINTER_NOT_USED,            // terminate context
        ME4000_VALUE_NOT_USED);             // ul_timeout_seconds


    /* start scanning */
	me4000AIStart(
        0);                                 // ui_board_number

    /* print values */
    printf("%12s%12s%12s\n", "Channel 0", "Channel 1", "Channel 2");
    printf("%12s%12s%12s", "---------", "---------", "---------");
    for(unsigned int i=0; i< (ui_count * uiNoOfEntries); i++)
    {
        if ((i%uiNoOfEntries)==0)   printf("\n");
        printf("%12d",sDataBuffer[i]);
    }
    printf("\n%12s%12s%12s\n", "---------", "---------", "---------");
    getch();
}
