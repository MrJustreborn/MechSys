VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "DIGetByte"
   ClientHeight    =   4035
   ClientLeft      =   3450
   ClientTop       =   3780
   ClientWidth     =   8115
   LinkTopic       =   "Form4"
   ScaleHeight     =   4035
   ScaleWidth      =   8115
   Begin VB.CommandButton Command5 
      Caption         =   "Exit"
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
      Left            =   6480
      TabIndex        =   13
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Byte_3"
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
      Left            =   120
      TabIndex        =   8
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Byte_2"
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
      Left            =   120
      TabIndex        =   7
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Byte_1"
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
      Left            =   120
      TabIndex        =   6
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Byte_0"
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
      Left            =   120
      TabIndex        =   5
      Top             =   720
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port select"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   4440
      TabIndex        =   0
      Top             =   840
      Width           =   1455
      Begin VB.OptionButton Option4 
         Caption         =   "Port D"
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   1440
         Width           =   855
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Port C"
         Height          =   375
         Left            =   240
         TabIndex        =   3
         Top             =   1080
         Width           =   855
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Port B"
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   855
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A"
         Height          =   375
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   855
      End
   End
   Begin VB.Label Label5 
      Caption         =   "Hex."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   14
      Top             =   240
      Width           =   975
   End
   Begin VB.Label Label4 
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
      Left            =   1680
      TabIndex        =   12
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Label Label3 
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
      Left            =   1680
      TabIndex        =   11
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label Label2 
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
      Left            =   1680
      TabIndex        =   10
      Top             =   1440
      Width           =   1575
   End
   Begin VB.Label Label1 
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
      Left            =   1680
      TabIndex        =   9
      Top             =   720
      Width           =   1575
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub Command1_Click()
    If me1000DIGetByte(Boardnumber, Port_X, BYTE_0, iValue_0) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label1.Caption = Hex(iValue_0)
    
End Sub

Private Sub Command2_Click()
    If me1000DIGetByte(Boardnumber, Port_X, BYTE_1, iValue_1) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label2.Caption = Hex(iValue_1)
End Sub

Private Sub Command3_Click()
    If me1000DIGetByte(Boardnumber, Port_X, BYTE_2, iValue_2) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label3.Caption = Hex(iValue_2)
End Sub

Private Sub Command4_Click()
    If me1000DIGetByte(Boardnumber, Port_X, BYTE_3, iValue_3) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label4.Caption = Hex(iValue_3)
End Sub

Private Sub Command5_Click()
    Form4.Hide
    Unload Form4
End Sub

Private Sub Option1_Click()
   If Option1.Value = True Then Port_X = PORTA
   
   
End Sub

Private Sub Option2_Click()
    If Option2.Value = True Then Port_X = PORTB
End Sub

Private Sub Option3_Click()
    If Option3.Value = True Then Port_X = PORTC
End Sub

Private Sub Option4_Click()
    If Option4.Value = True Then Port_X = PORTD
End Sub
