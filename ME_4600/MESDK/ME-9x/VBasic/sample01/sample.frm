VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows-Standard
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    'DEMO for ME 95
    'The file ME9x_32.LIB was included

    Dim retval As Long              'Return value of the function'
    Dim dll As Long                 'DLL version'
    Dim val_32 As Long              '32 bit input/output value'
    Dim dir As Long                 'direction value'
    Dim errtext As String * 255     'String for error'
    Dim board As Long               'Name/number of board'
    Dim version  As Long            'version of board'
    Dim bitn As Long                'number of bit'
    Dim port As Long                'port'
    
    'default settings'
    retval = 0
    dll = 0
    val_32 = 0
    errtext = ""
    board = 0
    version = 0
    bitn = 0
    port = 0
    
    'determine dll version
    dll = me9xGetDLLVersion()
    
    'determine board
    retval = me9xGetBoardVersion(board, version)
    
    'Write
    port = 0
    val_32 = &HAA
    retval = me96DOSetBit(board, bitn, 1)
    retval = me96DOSetByte(board, port, val_32)
End Sub



