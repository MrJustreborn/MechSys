VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME8100 Visual Basic Test Program"
   ClientHeight    =   3204
   ClientLeft      =   14160
   ClientTop       =   7632
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3204
   ScaleWidth      =   4680
   Begin VB.TextBox TextBox 
      Height          =   2895
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   120
      Width           =   4215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    'DEMO for ME 8100
    'The file ME8100DLL.LIB was included

    Dim board As Long               'number of board'
    Dim register_set As Long        'number of register set'
    Dim retval As Long              'Return value of the function'
    Dim dll As Long                 'DLL version'
    Dim val_32 As Long              '32 bit input/output value'
    Dim errtext As String * 255     'String for error'
    Dim bitn As Long                'number of bit'
    
    'default settings'
    board = 0
    register_set = REGISTER_SET_A
    retval = 0
    dll = 0
    val_32 = 0
    errtext = ""
    bitn = 0
    
    'String for TextBox
    Dim text_box_str As String
    
    'determine dll version
    dll = me8100GetDLLVersion()
    
    text_box_str = "DLL Version: "
    text_box_str = text_box_str & Hex(dll)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'determine board
    retval = me8100PROMVersion(board, version)

    text_box_str = text_box_str & "PROM Version: "
    text_box_str = text_box_str & Hex(retval)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'Set Tristate ON
    retval = me8100DIOSetTristateOFF(board, register_set)
    
    'Set SOURCE mode
    retval = me8100SetSinkSourceMode(board, register_set, SOURCE_MODE)
    
    'Write
    val_32 = &HABCD&
    retval = me8100DOSetWord(board, register_set, val_32)
 
    text_box_str = text_box_str & "Write word: "
    text_box_str = text_box_str & Hex(val_32)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
   'Read
    val_32 = &HFFFF&
    retval = me8100DIGetWord(board, register_set, val_32)
    
    text_box_str = text_box_str & "Read word: "
    text_box_str = text_box_str & Hex(val_32)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'Display string
    TextBox.Text = text_box_str

End Sub

