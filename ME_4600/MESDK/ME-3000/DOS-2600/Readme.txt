The following DOS samples are available:

	sample01	GeneralSample	sequential processing of all basic functions:
			a.) test if PLX addresses are valid
			b.) set user specified resources (address, interrupt)
			c.) determine the PCI resources
			d.) Digital Input
			e.) Digital Output
			f.) external Interrupt
			g.) Analog Input Single
			h.) Analog Output Single
			i.) Analog Input Scan (using the interrupt)

	sample02	scope		with graphical output

	sample03	ScanToDisk	demonstration using EMS memory

	All three of these examples contain a number of clearly marked defines and 
	variable definitions at the start of the source code which can be changed 
	to alter the behaviour of the resulting application. Having made the required
	changes it is only necessary to recompile with the help of the batch file
	provided.
		

You have to change the IO access mode
depending on the application mode.

in the default case the board is in memory mapped mode
	then you can use the board with the 32 bit driver
	under Windows NT or Windows 9x

in the other case the board is in IO mapped mode
	you need this for the DOS samples

You can switch from one mode to the other with a special tool
in the directory SetAcc [SetAccessMode]. This tool runs only under windows 95/98
Or you can let Meilhaus Electronic make the changes for you.

To run sample03 you need an EMS manager.

In the directory SmplCfg [SammpleConfiguration] you can find an image of 
a successfully tested configuration on floppy disk [Windows 95 SE files].
Some files have the file length zero. This is due to copyright laws.

The example programs are shipped as is and Meilhaus 
Electronic offers no guarantees.

Please use our web page for updates:
www.meilhaus.de
