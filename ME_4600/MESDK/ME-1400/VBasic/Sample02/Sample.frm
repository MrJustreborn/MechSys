VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2445
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   ScaleHeight     =   2445
   ScaleWidth      =   3750
   StartUpPosition =   3  'Windows-Standard
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Dim retval As Long          'Returnwert der Funktionen'
    Dim val_32 As Long          '32 Bit Ein / Ausgabewert '
    Dim dir As Long             'Richtungsvariable'
    Dim port As Long            ''
    Dim bitn As Long            'Bitnummer'
    Dim board As Long           'Boardname / number'
    Dim dir1 As Long
    
    
    'Defaulteinstellungen'
    retval = 0
    dir = 0
    port = 0    'Port A'
    bitn = 0    'Bitnummer 0'
    val_32 = 0
    board = 0
    dir1 = 1
        
    '-----------------------------------------------------------------------
    ' General Functions
    '-----------------------------------------------------------------------
    
    'Port A als Ausgang definieren'
    retval = me1400DIOSetPortDirection(iBoard, port, dir1)
    
    'Bit 0 setzen'
    retval = me1400DOSetBit(board, port, bitn, 1)
  
    
    'Port A als Eingang definieren'
    retval = me1400DIOSetPortDirection(iBoard, port, dir)
      
    'Bit 0 lesen'
    retval = me1400DIGetBit(board, port, bitn, val_32)
    MsgBox "ME 1400, Port A,Bit 0 =   " + Hex(val_32), vbInformation
        
        
End Sub
