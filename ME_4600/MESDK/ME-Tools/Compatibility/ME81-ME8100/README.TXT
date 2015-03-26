Purpose:
	These are utilities for using programs written
	for the older cards ME-81 with the new PCI cards
	ME-8100

General hints :
	For backwards compatibility, there are several 
	different cases:

	1. Only the ME8100 is being used and a new 
	   application is being written or the example 
	   program included are being used
	   =>No restrictions apply

	2. An ME-81 ISA board is currently installed and 
	   the ME-81 driver system is being used (including 
	   any old applications).
	   A new ME-8100 is installed along with the 
	   ME-8100 driver system.
	   =>No restrictions apply

	3. The existing ME-81 ISA is to be replaced with 
	   an ME-8100 PCI board.  The existing application 
	   for the ME-81 ISA will still be used for the 
	   ME-8100 board.
	   =>Follow instructions below

	4. An existing application for the ME-81 ISA board 
	   is to be used for the ISA board and the new PCI 
	   ME-8100 boards.  
	   This is not possible due to logical differences 
	   in the way the boards are controlled. With a few 
	   minor changes, the application for the ME-81 ISA 
	   board can be modified to suit the PCI ME-8100.

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
	boards ME-8100, because the new boards use 
	other IO ports.

Limitations:
	If you use ME-81 ISA cards and ME-8100 PCI cards
	at the same time in one system you can not use the 
	upward compatibility feature for the ME-8100.
	Then you have to use the standard driver for both
	card types.

Instructions:
	1.) copy the file me81_32.dll into the system directory
		Windows 9x: C:\WINDOWS\SYSTEM
		Windows NT: C:\WINNT\system32
	2.) Now you can use the old program for ME-81 with
	    the ME-8100

The programs are shipped as is and Meilhaus 
Electronic offers no guarantees.



