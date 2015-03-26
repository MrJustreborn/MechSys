// generall example for using me4000AISingle
// normally you should handle errors (check the return values)

#include <stdio.h>
#include <conio.h>
#include "..\me4000dll.h"

void main(void)
{
    short s_digital_value;
    double d_volt;

	me4000AISingle(
        0,                              // ui_board_number
		0,                              // ui_channel_number
        ME4000_AI_RANGE_BIPOLAR_10,     // i_range
        ME4000_AI_INPUT_SINGLE_ENDED,   // i_sd_mode
		ME4000_AI_TRIGGER_SOFTWARE,     // i_trigger_mode
        ME4000_VALUE_NOT_USED,          // i_ext_trigger_edge
		ME4000_VALUE_NOT_USED,          // ul_time_out_seconds
        &s_digital_value);

	me4000AIDigitToVolt(
        s_digital_value, 
        ME4000_AI_RANGE_BIPOLAR_10, 
        &d_volt);

	printf("Digital value: %6d    Physical Value: %7.3f V\n", s_digital_value, d_volt);  

	printf("\nPress any key to terminate\n");
	_getch();
}
