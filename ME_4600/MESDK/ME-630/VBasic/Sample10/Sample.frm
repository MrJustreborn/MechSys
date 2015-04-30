VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME-630 Visual Basic Test Program"
   ClientHeight    =   6360
   ClientLeft      =   14160
   ClientTop       =   7635
   ClientWidth     =   9360
   LinkTopic       =   "Form1"
   ScaleHeight     =   6360
   ScaleWidth      =   9360
   StartUpPosition =   1  'Fenstermitte
   Begin VB.CommandButton Command6 
      Caption         =   "Programm beenden"
      Height          =   495
      Left            =   360
      TabIndex        =   17
      Top             =   5400
      Width           =   1695
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   3960
      TabIndex        =   11
      Text            =   "0"
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Get Relay Word"
      Height          =   375
      Left            =   360
      TabIndex        =   10
      Top             =   3240
      Width           =   2055
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Get Relay Bit"
      Height          =   375
      Left            =   360
      TabIndex        =   9
      Top             =   1440
      Width           =   2055
   End
   Begin VB.TextBox Text3 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1031
         SubFormatType   =   1
      EndProperty
      Height          =   375
      Left            =   3960
      TabIndex        =   7
      Text            =   "0"
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Set Relay Word"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   6
      Top             =   2400
      Width           =   3015
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Reset Relays"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   5
      Top             =   4080
      Width           =   3015
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   5400
      TabIndex        =   2
      Text            =   "0"
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   3960
      TabIndex        =   1
      Text            =   "0"
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Set Relay Bit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   600
      Width           =   3015
   End
   Begin VB.Label Label8 
      Caption         =   "Word Value"
      Height          =   255
      Left            =   5400
      TabIndex        =   16
      Top             =   3000
      Width           =   855
   End
   Begin VB.Label Label7 
      Caption         =   "Bit Value"
      Height          =   255
      Left            =   5400
      TabIndex        =   15
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label6 
      Caption         =   "Bit No"
      Height          =   255
      Left            =   3960
      TabIndex        =   14
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label5 
      BackColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   5400
      TabIndex        =   13
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label Label4 
      BackColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   5400
      TabIndex        =   12
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "Word Value"
      Height          =   255
      Left            =   3960
      TabIndex        =   8
      Top             =   2160
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Value"
      Height          =   255
      Left            =   5400
      TabIndex        =   4
      Top             =   480
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Bit No"
      Height          =   255
      Left            =   3960
      TabIndex        =   3
      Top             =   480
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Val_Bit = Text2.Text
iBitNo = Text1.Text

retval = me630DOSetRelayBit(board, iBitNo, Val_Bit)
End Sub

Private Sub Command2_Click()

retval = me630ResetRelays(board)

End Sub

Private Sub Command3_Click()



val_32 = Text3.Text

retval = me630DOSetRelayWord(board, val_32)

End Sub

Private Sub Command4_Click()

iBitNo = Text4.Text

retval = me630DIGetRelayBit(board, iBitNo, iBitValue)

Label4.Caption = iBitValue
End Sub

Private Sub Command5_Click()

retval = me630DIGetRelayWord(board, iWordValue)
Label5.Caption = iWordValue

End Sub

Private Sub Command6_Click()

Unload Form1

End Sub

Private Sub Form_Load()
    'DEMO for ME-630
    'The file ME630DLL.LIB was included

    Dim board As Long               'number of board'
    Dim register_set As Long        'number of register set'
    Dim retval As Long              'Return value of the function'
    Dim dll As Long                 'DLL version'
    Dim val_32 As Long              '32 bit input/output value'
    Dim errtext As String * 255     'String for error'
    Dim iBitNo As Long                'number of bit'
    Dim Val_Bit As Long
    Dim iWordValue As Long
    Dim iBitValue As Long
    
    
    'default settings'
    board = 0
    register_set = REGISTER_SET_A
    retval = 0
    dll = 0
    errtext = ""
        
    
End Sub

