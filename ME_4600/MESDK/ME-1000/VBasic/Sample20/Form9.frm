VERSION 5.00
Begin VB.Form Form9 
   Caption         =   "DoSetLong"
   ClientHeight    =   6375
   ClientLeft      =   2850
   ClientTop       =   2190
   ClientWidth     =   9660
   LinkTopic       =   "Form9"
   ScaleHeight     =   6375
   ScaleWidth      =   9660
   Begin VB.TextBox Text1 
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
      Left            =   2880
      TabIndex        =   8
      Text            =   "0"
      Top             =   2640
      Width           =   1455
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   5640
      TabIndex        =   7
      Top             =   4920
      Width           =   1455
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Reset"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3240
      TabIndex        =   6
      Top             =   4920
      Width           =   1335
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
      Left            =   1080
      TabIndex        =   5
      Top             =   2640
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
      Height          =   2895
      Left            =   5760
      TabIndex        =   0
      Top             =   1200
      Width           =   1695
      Begin VB.OptionButton Option4 
         Caption         =   "Port D"
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
         Left            =   240
         TabIndex        =   4
         Top             =   2280
         Width           =   1095
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Port C"
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
         Left            =   240
         TabIndex        =   3
         Top             =   1680
         Width           =   1215
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Port B"
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
         Left            =   240
         TabIndex        =   2
         Top             =   1080
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A"
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
         Left            =   240
         TabIndex        =   1
         Top             =   480
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.Label Label1 
      Caption         =   "0.....FFFFFFFF"
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
      Left            =   2880
      TabIndex        =   9
      Top             =   2400
      Width           =   1455
   End
End
Attribute VB_Name = "Form9"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()

  
    tt = Text1.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetLong(Boardnumber, Port_X, val_32)

If retval = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command2_Click()
   If Option1.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option2.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option3.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option4.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    End If
End Sub

Private Sub Command3_Click()
Form9.Hide
Unload Form9
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

