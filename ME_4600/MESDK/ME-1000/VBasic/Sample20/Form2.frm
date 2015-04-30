VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "Set Port Direction"
   ClientHeight    =   2190
   ClientLeft      =   3255
   ClientTop       =   4380
   ClientWidth     =   6645
   LinkTopic       =   "Form2"
   ScaleHeight     =   2190
   ScaleWidth      =   6645
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   5400
      TabIndex        =   12
      Top             =   360
      Width           =   1215
   End
   Begin VB.Frame Frame4 
      Caption         =   "Port D"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   4080
      TabIndex        =   3
      Top             =   240
      Width           =   1095
      Begin VB.OptionButton Option8 
         Caption         =   "Output"
         Height          =   375
         Left            =   120
         TabIndex        =   11
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton Option7 
         Caption         =   "Input"
         Height          =   375
         Left            =   120
         TabIndex        =   10
         Top             =   480
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Port C"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   2760
      TabIndex        =   2
      Top             =   240
      Width           =   1095
      Begin VB.OptionButton Option6 
         Caption         =   "Output"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton Option5 
         Caption         =   "Input"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   480
         Value           =   -1  'True
         Width           =   735
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Port B"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   1440
      TabIndex        =   1
      Top             =   240
      Width           =   1095
      Begin VB.OptionButton Option4 
         Caption         =   "Output"
         Height          =   315
         Left            =   120
         TabIndex        =   7
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Input"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   480
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port A"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1095
      Begin VB.OptionButton Option2 
         Caption         =   "Output"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Input"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   480
         Value           =   -1  'True
         Width           =   735
      End
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    Public Boardnumber As Integer
    Public iDir_A As Long
    Public iDir_B As Long
    Public iDir_C As Long
    Public iDir_D As Long
    Public errtext As String





Private Sub Command1_Click()
    If Option1.Value = True Then
        iDir_A = MEINPUT
    Else
        iDir_A = MEOUTPUT
    End If
    If me1000DIOSetPortDirection(Boardnumber, PORTA, iDir_A) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If Option3.Value = True Then
        iDir_B = MEINPUT
    Else
        iDir_B = MEOUTPUT
    End If
    If me1000DIOSetPortDirection(Boardnumber, PORTB, iDir_B) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If Option5.Value = True Then
        iDir_C = MEINPUT
    Else
        iDir_C = MEOUTPUT
    End If
    If me1000DIOSetPortDirection(Boardnumber, PORTC, iDir_C) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If Option7.Value = True Then
        iDir_D = MEINPUT
    Else
        iDir_D = MEOUTPUT
    End If
    If me1000DIOSetPortDirection(Boardnumber, PORTD, iDir_D) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Form2.Hide
    Unload Form2
End Sub


Private Sub Form_Load()
    
Boardnumber = 0
End Sub




