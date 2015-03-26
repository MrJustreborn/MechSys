// DEMO für ME 81
// In das Project wurde die me8x_32.lib eingebunden.

#include <stdio.h>
#include <windows.h>

// Einbindung der Meilhaus Defenitionsdatei
// und des ME 8x Headers

#include ".\..\medefs.h"
#define MICROSOFT_C
#include ".\..\me8x.h"

int count = 0;   // IRQ-Zähler

// Einfache Interruptfunktion erhöht count um eins wenn Interrupt
void _stdcall IRQFKT (void)

{
    printf("*");
	count++;
	if (count==65000) 
		count = 0;
}

// Die Beschreibung der Funktionen entnehmen Sie bitte dem Handbuch
void main (void)
{

	int retval = 0;        // Returnvalue der Funktionen
	int Board = 0;		   // Boardname
	int value = 0xff;	   // Rückgabe- / Eingabewert
	int Boardversion = 0;  
	int dllver = 0;		   // DLLVersionsnummer
	int bitnumber = 0;	   
	int Mode = 0;		   // verschiedene Modi
	int RegMode = 0;	   // versch. Registermodi
	int Port = 0;			

	// Boardversion ermitteln
	retval = _me8xPROMVersion (Board,&Boardversion);
    printf(
        "iBoardVersion: Major: 0x%04x Minor: 0x%04x\n",
        (Boardversion>>16)& 0xFFFF,
        (Boardversion)    & 0xFFFF);


	// Aktuelle DLLVersion ermitteln
	dllver = _me8xGetDLLVersion ();
    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (dllver>>16)& 0xFFFF,
        (dllver)    & 0xFFFF);


	// Aus / Eingänge freischalten
	retval = _me8xDIOSetTristateOFF (Board);


	//  Bitnummer 0 wird ausgelesen. Wert in value
	bitnumber =  0;       // Bitwert 0	
	retval = _me8xDIGetBit (Board,bitnumber,&value);
    
	//  16 Bit Port wird ausgelesen. Wert in value
	Port = 0;
	retval = _me8xDIGetWord (Board,Port,&value);
	

	bitnumber = 0 ; // Bit 0
	value = 0x01;	// Ausgabewert 1

	// Bitnummer 0 Ausgabewert 1
	retval = _me8xDOSetBit (Board,bitnumber,value);    
	// Port A 
	value = 0xAAAA;	//  Ausgabewert AAAA
	retval = _me8xDOSetWord (Board,Port,value);

	// IRQ-Maske (AAAA) setzen
	retval = _me81DIOSetMask (Board,value);

	// Pattern Leitung 0
	Port = 0;
	retval = _me8xDIOSetPattern (Board,Port);

	// Interruptkanal 1 setzen
	retval = _me8xEnableInt (Board,IRQFKT);
	// wait a moment ...
	Sleep(1000);

	// Interruptkanal 1 löschen
	retval = _me8xDisableInt (Board);
}
