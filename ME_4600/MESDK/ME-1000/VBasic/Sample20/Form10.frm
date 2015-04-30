VERSION 5.00
Begin VB.Form Form10 
   Caption         =   "DOGetLong"
   ClientHeight    =   5400
   ClientLeft      =   2655
   ClientTop       =   2595
   ClientWidth     =   7920
   LinkTopic       =   "Form10"
   ScaleHeight     =   5400
   ScaleWidth      =   7920
   Begin VB.CommandButton Command2 
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
      Height          =   615
      Left            =   5640
      TabIndex        =   7
      Top             =   4440
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Long"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   1320
      TabIndex        =   6
      Top             =   2880
      Width           =   1455
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
      Height          =   2655
      Left            =   5640
      TabIndex        =   0
      Top             =   1320
      Width           =   1575
      Begin VB.OptionButton Option4 
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
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   1920
         Width           =   1095
      End
      Begin VB.OptionButton Option3 
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
         Height          =   375
         Left            =   240
         TabIndex        =   3
         Top             =   1440
         Width           =   1095
      End
      Begin VB.OptionButton Option2 
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
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   960
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
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
         Height          =   375
         Left            =   240
         TabIndex        =   1
         Top             =   480
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.Label Label2 
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
      Left            =   3120
      TabIndex        =   8
      Top             =   2520
      Width           =   1695
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
      Height          =   615
      Left            =   3120
      TabIndex        =   5
      Top             =   3000
      Width           =   2175
   End
End
Attribute VB_Name = "Form10"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
 If me1000DIGetLong(Boardnumber, Port_X, iValue_0) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
        Label1.Caption = Hex(iValue_0)
End Sub

Private Sub Command2_Click()
    Form10.Hide
    Unload Form10
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
