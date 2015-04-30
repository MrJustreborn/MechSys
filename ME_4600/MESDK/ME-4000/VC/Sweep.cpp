#include "stdafx.h"

#include <math.h>

#include "sweep.h"

void Sweep(int signal_type, double from_freq, double to_freq, 
					double from_amp, double to_amp, double base_freq, 
								unsigned long no_of_points, short* buffer, int buffer_increment)
{
	double d_total_time = no_of_points / base_freq;
	
	for(unsigned long index = 0; index < no_of_points; index++)
	{
		double d_time = (double)index / base_freq;

		double d_arg = 	(0.5 * d_time * d_time * (to_freq - from_freq) + d_time * from_freq * d_total_time) / d_total_time;

		d_arg-= floor(d_arg);
		
		double d_amplitude = from_amp + (double)index * (to_amp - from_amp) / (double)no_of_points;

		double d_signal;
		
		switch(signal_type)
		{
		case SIGNAL_RECTANGLE:

			d_signal = (d_arg < 0.5) ? +1.0 : -1.0;
				
			break;

		case SIGNAL_TRIANGLE:

			d_signal = (d_arg < 0.5) ? (-1.0 + 4 * d_arg) : (+1.0 - 4 * (d_arg - 0.5) );
				
			break;

		case SIGNAL_SINUS:

			d_signal = sin(2 * 3.14153 * d_arg);
				
			break;

		case SIGNAL_POS_RAMP:

			d_signal = 2 * (d_arg - 0.5);
				
			break;

		case SIGNAL_NEG_RAMP:

			d_signal = -2 * (d_arg - 0.5);
				
			break;
		}

		d_signal*= d_amplitude;

		buffer[index * buffer_increment] = (short)( d_signal * (double)0x7FFF / 10.0 );
	}
}

