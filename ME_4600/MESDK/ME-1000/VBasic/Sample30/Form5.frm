VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "DIGetWord"
   ClientHeight    =   3390
   ClientLeft      =   3450
   ClientTop       =   3975
   ClientWidth     =   7995
   LinkTopic       =   "Form5"
   ScaleHeight     =   3390
   ScaleWidth      =   7995
   Begin VB.CommandButton Command3 
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
      TabIndex        =   9
      Top             =   2280
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port Select"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1935
      Left            =   4200
      TabIndex        =   4
      Top             =   840
      Width           =   1575
      Begin VB.OptionButton Option4 
         Caption         =   "Port D"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   1320
         Width           =   855
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Port C"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Port B"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   600
         Width           =   855
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Word_1"
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
      Left            =   600
      TabIndex        =   1
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Word_0"
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
      Left            =   600
      TabIndex        =   0
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label Label3 
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
      Left            =   1920
      TabIndex        =   10
      Top             =   480
      Width           =   1095
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
      Left            =   2040
      TabIndex        =   3
      Top             =   1920
      Width           =   1215
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
      Left            =   2040
      TabIndex        =   2
      Top             =   960
      Width           =   1215
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    If me1000DIGetWord(Boardnumber, Port_X, WORD_0, iValue_0) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label1.Caption = Hex(iValue_0)

End Sub

Private Sub Command2_Click()
    If me1000DIGetWord(Boardnumber, Port_X, WORD_1, iValue_1) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    Label2.Caption = Hex(iValue_1)

End Sub

Private Sub Command3_Click()
    Form5.Hide
    Unload Form5
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
