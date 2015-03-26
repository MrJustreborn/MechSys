Purpose:
	This program reads the PCI settings and 
	serial number of all PCI Meilhaus boards

Using requirements:
	This utility runs only under DOS compatible
	operating systems (DOS, Windows 3.x, Windows 9x).
	For Windows NT you need a DOS boot disk !

Using hints:
	The process can take several minutes!
	All values are hexadecimal!
	If an address occurs with the last number 1,
	you must ignore the 1. It means that it is an 
	IO address (as opposed to a memory mapped address)
	Example:       B801 means B800 with IO port access

Results:
	See file Getmepci.txt for results!

Background:
	This program uses the PCI BIOS Int 1Ah interface
	with the appropriate subfunctions
	AH = 0xb1;
	AL = Subfunction 
	     (0x01, 0x02, 0x03, 0x06, 0x08, 0x09, 0x0a, 
	      0x0b, 0x0c, 0x0d)
	Please see PCI BIOS documentation for further 
	information.

The programs are shipped as is and Meilhaus 
Electronic offers no guarantees.