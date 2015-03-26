Purpose:
	These are utilities for using programs written
	for the older cards ME-14 with the new PCI cards
	ME-1400

General hints :
	For backwards compatibility, there are several 
	different cases:

	1. Only the ME1400 is being used and a new 
	   application is being written or the example 
	   program included are being used
	   =>No restrictions apply

	2. An ME-14 ISA board is currently installed and 
	   the ME-14 driver system is being used (including 
	   any old applications).
	   A new ME-1400 is installed along with the 
	   ME-1400 driver system.
	   =>No restrictions apply

	3. The existing ME-14 ISA is to be replaced with 
	   an ME-1400 PCI board.  The existing application 
	   for the ME-14 ISA will still be used for the 
	   ME-1400 board.
	   =>Follow instructions below

	4. An existing application for the ME-14 ISA board 
	   is to be used for the ISA board and the new PCI 
	   ME-1400 boards.  
	   This is not possible due to logical differences 
	   in the way the boards are controlled. With a few 
	   minor changes, the application for the ME-14 ISA 
	   board can be modified to suit the PCI ME-1400.

	5. Software which has been programmed on the register 
	   level with fixed hardware addresses can not be 
	   used for the PCI boards without being modified.  
	   This is because the PCI Bios automatically assigns 
	   the addresses.


Using requirements:
	This runs only with programs using the 32 bit
	driver system.
	DOS programs need a special modification.
	Not every DOS program can be adapted to the newer
	boards ME-1400, because the new boards use 
	other IO ports.
	The new boards don't have any jumpers for 
	initializing the counters. The 32 bit driver 
	system API offers two new function to do that.
	You can also use the Init16 program to set up 
	the counters for MS-DOS.

Limitations:
	If you use ME-14 ISA cards and ME-1400 PCI cards
	at the same time in one system you can not use the 
	upward compatibility feature for the ME-1400.
	Then you have to use the standard driver for both
	card types.
	The ME-1400 standard version (in contrast to the
	ME-1400 A and B version) has no counters. If you 
	replace an ME-14 A or B with a ME-1400 standard,
	it can not be fully compatible.
	

Instructions:
	1.) copy the file me14_32.dll into the system directory
		Windows 9x: C:\WINDOWS\SYSTEM
		Windows NT: C:\WINNT\system32
	2.) Use the Init program to set the timer conditions
	    (for the former jumpers)
	3.) Now you can use the old program for ME-14 with
	    the ME-1400

Composition of the control word:

	Bit 4 to 7 are for timer A
	Bit 0 to 3 are for timer B

Timer A:
Bit  B7     B6                    B5	       	B4
0    1MHz   Clock signal on Clk0  Out0 to Clk1  Out1 to Clk2
1    10MHz  SubD for Clk0         SubD to Clk1  SubD to Clk2

Timer B:
Bit  B3     B2			  B1            B0
0    1MHz   Clock signal on Clk0  Out0 to Clk1  Out1 to Clk2
1    10MHz  SubD for Clk0         SubD to Clk1  SubD to Clk2

Example:
	If you want the following settings for timer A:
		Clock 10 MHz			=> B7=1
		Clock is source for timer 1	=> B6=0
		Timer 1 is source for timer 2	=> B5=0
		Timer 2 is source for timer 3	=> B4=0
	
	If you want the following settings for timer B:
		Clock 1 MHz 			=> B7=0
		SubD is source for timer 1	=> B6=1
		Timer 1 is source for timer 2	=> B5=0
		Timer 2 is source for timer 3	=> B4=0

	The binary value is:
		Bit number:	7 6 5 4 3 2 1 0
		Value:		1 0 0 0 0 1 0 0

	The hexadecimal value is:	0x84
	This is the value you have to use for the control 
	value with the init.exe program.

Multifunction pin:
	value of 0 if you use it as an interrupt input
	value of 1 if you use it as a clock output

The programs are shipped as is and Meilhaus 
Electronic offers no guarantees.



