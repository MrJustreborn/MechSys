#ifndef SWEEP_H
#define SWEEP_H

#define SIGNAL_RECTANGLE								0x00
#define SIGNAL_TRIANGLE									0x01
#define SIGNAL_SINUS									0x02
#define SIGNAL_POS_RAMP									0x03
#define SIGNAL_NEG_RAMP									0x04

void WinSweepBuffer(int signal_type, double from_freq, double to_freq, 
						double from_amp, double to_amp, double base_freq, 
							unsigned long no_of_points, short* buffer, int buffer_increment);

void WinSweepDisplay(int signal_type, double from_freq, double to_freq, 
						double from_amp, double to_amp, double base_freq, unsigned long no_of_points,
							CDC* p_dc, CRect rect_disp, double d_x_const, double d_x_factor, double d_y_const, double d_y_factor);

#endif