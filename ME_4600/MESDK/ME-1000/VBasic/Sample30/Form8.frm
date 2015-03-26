VERSION 5.00
Begin VB.Form Form8 
   Caption         =   "DOSetWord"
   ClientHeight    =   6075
   ClientLeft      =   2850
   ClientTop       =   3180
   ClientWidth     =   8880
   LinkTopic       =   "Form8"
   ScaleHeight     =   6075
   ScaleWidth      =   8880
   Begin VB.CommandButton Command4 
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
      Left            =   1320
      TabIndex        =   10
      Top             =   3600
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
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
      Left            =   1320
      TabIndex        =   9
      Top             =   2520
      Width           =   1335
   End
   Begin VB.TextBox Text2 
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
      Left            =   3000
      TabIndex        =   8
      Text            =   "0"
      Top             =   3600
      Width           =   975
   End
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
      Height          =   495
      Left            =   3000
      TabIndex        =   7
      Text            =   "0"
      Top             =   2520
      Width           =   975
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
      Height          =   735
      Left            =   4680
      TabIndex        =   6
      Top             =   4800
      Width           =   1695
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
      Height          =   2535
      Left            =   6720
      TabIndex        =   1
      Top             =   1560
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
         TabIndex        =   5
         Top             =   1800
         Width           =   1215
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
         TabIndex        =   4
         Top             =   1320
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
         TabIndex        =   3
         Top             =   840
         Width           =   1335
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
         TabIndex        =   2
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.CommandButton Command1 
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
      Height          =   735
      Left            =   6720
      TabIndex        =   0
      Top             =   4800
      Width           =   1695
   End
   Begin VB.Label Label2 
      Caption         =   "0.....FFFF"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3000
      TabIndex        =   12
      Top             =   3360
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "0.....FFFF"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3000
      TabIndex        =   11
      Top             =   2280
      Width           =   975
   End
End
Attribute VB_Name = "Form8"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Form8.Hide
Unload Form8
End Sub

Private Sub Command2_Click()
    If Option1.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option2.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option2.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option4.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    End If
End Sub

Private Sub Command3_Click()
  
    
    tt = Text1.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetWord(Boardnumber, Port_X, 0, val_32)

If retval = 0 Then
         Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command4_Click()
  
    tt = Text2.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetWord(Boardnumber, Port_X, 1, val_32)

If retval = 0 Then
         Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
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

