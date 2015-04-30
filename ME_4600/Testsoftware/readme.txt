*************************************************************************
*                                                                       *
*          ME-4000 Driver System 4.03 for Windows 98/Me/NT4/2000/XP     *
*                                                                       *
*************************************************************************

In this README-file you find information
on the following topics:

    - Supported Boards
    - Supported Operating Systems
    - Driver Components
       * System Drivers:
       * High Level Language Support:
       * Graphical Programming Support:
    - Installation Process
    - New in this Version
    - Contact per Phone or fax

Supported Boards:
=================
- ME-4000 family
 (ME-6x00 family, not tested yet)

Supported Operating Systems:
============================
- Windows XP   -> WDM driver package, see directory .\winwdm
                  (tested with personal version only)
- Windows 2000 -> WDM driver package, see directory .\winwdm
                  (tested with professional version only)
- Windows Me   -> WDM driver package, see directory .\winwdm
- Windows 98   -> WDM driver package, see directory .\winwdm (all releases)
- Windows NT4  -> SYS driver package, see directory .\winnt (all service packs)
- DOS          -> ME-SDK package, programming samples in C,
                  see directory ..\me-sdk
                  samples "as is" Meilhaus Electronic offers no support
- Linux        -> LNX driver package, see directory .\linux

(*) If you use Windows 95, we recommend updating to a
newer Windows version and using the WDM driver.


Driver Components:
==================
* System Drivers:
  The Windows system driver consists of operating system specific low level
  driver, an user interface with the application programming interface (API)
  and a board specific test program.

  Kernel drivers for Linux: see appropriate readme file in the directory .\linux

* High Level Language Support:
  Use the Meilhaus Electronic Software Developer Kit (ME-SDK)
  (-> see the directory ..\me-sdk). Most of the following topics
  are supported:
    Bc       samples for Borland C
    BDelphi  samples for Borland Delphi
    DOS      samples for MS-DOS (16 bit)
    VBasic   samples for Microsoft Visual Basic
    VBA      samples for MS Office
    Vc       samples for Microsoft Visual C
    Test     test program

* Graphical Programming Support:
    Agilent VEE / HP VEE -> ME-VEE driver package see directory .\vee
    LabVIEW              -> LabVIEW driver see directory .\labview

Please read the additional readme.txt in the subdirectories.
If you don't find the sample what you need you have the
following possibilities:
    - ask our support division (email: support@meilhaus.com)
    - look for a similar sample included with the ME-SDK


Installation under Windows 98/Me/2000/XP:
=========================================
  Please proceed step by step as described below. This is important
  to guarantee a correct Plug&Play procedure as required under
  Windows 98/Me/2000 (see also the description in the manual).

- Please install the board first into your computer
  (see the manual of your board for hardware installation).

- After power up, the new board will be detected automatically by
  the Windows "Hardware Wizard" and the message "New Hardware Found"
  will be shown (The dialogs may differ slightly depending on your
  Windows release).

- Insert the ME-Power CD with the driver software.

- Select the option "Search for a suitable driver for my device
  (recommended)" and click "Next".

- Browse to the directory with the installation software. Mark the
  INF file for the board to be installed and confirm with "OK".

  -> System driver and API-DLL will be installed
  -> The device class "Meilhaus DAQ-boards" will be added in the
     device manager
  -> The currently installed board will be added to the device class
     "Meilhaus DAQ-boards"
  -> The resource settings will automatically be assigned

- Reboot your computer.

- For high level language support, demos and test programs
  please install the ME-Software-Developer-Kit (ME-SDK).

- Test the function of the board by the test program.


Installation under Windows NT 4.0
=================================
- If you install from CD-ROM double click the file "Start" in the
  root directory of the CD-ROM. Navigate to the driver installation
  and start the setup program. Alternativly choose "Run" from the
  Windows start menu and click "Browse". Enter the path for the
  SETUP.EXE file of the board installation.

  -> Kernel driver (*.SYS) and API-DLL will be installed.

- Reboot your computer.

- For high level language support, demos and test programs
  please install the ME-Software-Developer-Kit (ME-SDK).

- Test the function of the board by the test program.


ME-SDK (optional):
******************
For programming of ME PCI boards with all common high level languages
the Meilhaus Electronic Software Developer Kit (ME-SDK) is provided.
It includes samples, test programs and tools for all ME PCI boards.

- Start the installation by running the file "setup.exe" in the directory
  <CD>:\drivers\me-boards\me-sdk.

- Follow the instructions of the setup program

  -> Libraries, samples and test programs will be installed to the
     directory C:\Meilhaus\me-sdk (by default).


New in this Version
===================
0.09 -> 3.91:   first release
3.91 -> 3.92:   adaptions in me4000Ex.dll for Vee
3.92 -> 3.93:   DLL: Bug removed in ADGetNewValues, ADSingle, ADStart
                all: new firmware, TTL level inverted
3.93 -> 3.94:   All: DIOBP operations bit 15 sometimes inverted
                Ex:  (Vee) MultiSigAIConfig
                Ex:  (Vee) new function: MultiSigAIDigitToSizeArray
                Ex:  (Vee) new function: MultiSigAOVoltToDigitArray
                Ex:  (Vee) me4000VEE_DIOBPWraparound short* to long*
                DLL: timeoutcheck in Start routine
                All: new firmware
3.94 -> 3.95:   All: new firmware:
                        ANALOGE TRIGGER negation removed
                        SCAN and CHAN minimum scan time
                        DA  sysncrone trigger
                All: AISingle fixed
3.95 -> 3.96:   All: new firmware:
                     several improvments
3.96 -> 4.00:   All: new firmware
                     new AO functions
                     new Delphi Samples
4.00 -> 4.01:   All: support of ME-4610 (Jekyll)
                     increase precision of temperature acquisition
4.01 -> 4.02:   All: MultiSigThermo module support
		     support of new versions of ME-6x00
4.02 -> 4.03:   SYS: Bug removed. Frequency for the Analog output was 
                     incorrectly calculated.


Contact per Phone or Fax
========================
If you have sales questions, please contact
our sales department:

Phone: ++49 (0)89/890166-0
Fax: ++49 (0)89/808316
E-Mail: sales@meilhaus.de

If you have difficulties, caused by the driver,
please contact us by:

Fax-Hotline: ++49 (0)89/89016628
   or
E-Mail: support@meilhaus.de

For updates, see the support section under www.meilhaus.com

End of README file *****************************************************
