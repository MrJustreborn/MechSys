VERSION 5.00
Begin VB.Form Form6 
   Caption         =   "Form6"
   ClientHeight    =   4395
   ClientLeft      =   6240
   ClientTop       =   4185
   ClientWidth     =   3705
   LinkTopic       =   "Form6"
   ScaleHeight     =   4395
   ScaleWidth      =   3705
   Begin VB.CommandButton Command9 
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
      Left            =   2040
      TabIndex        =   8
      Top             =   3600
      Width           =   1215
   End
   Begin VB.CommandButton Command8 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 7"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   7
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton Command7 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 6"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   6
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton Command6 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 5"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   5
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton Command5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 4"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   4
      Top             =   2400
      Width           =   855
   End
   Begin VB.CommandButton Command4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 3"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   3
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton Command3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 2"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   2
      Top             =   1440
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 1"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   1
      Top             =   960
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OptoBit 0"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   0
      Top             =   480
      Width           =   855
   End
End
Attribute VB_Name = "Form6"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
If me630DIGetOptoBit(Boardnumber, BIT_0, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command1.BackColor = vbGreen
    Else
    Command1.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command2_Click()
If me630DIGetOptoBit(Boardnumber, BIT_1, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command2.BackColor = vbGreen
    Else
    Command2.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command3_Click()
If me630DIGetOptoBit(Boardnumber, BIT_2, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command3.BackColor = vbGreen
    Else
    Command3.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command4_Click()
If me630DIGetOptoBit(Boardnumber, BIT_3, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command4.BackColor = vbGreen
    Else
    Command4.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command5_Click()
If me630DIGetOptoBit(Boardnumber, BIT_4, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command5.BackColor = vbGreen
    Else
    Command5.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command6_Click()
If me630DIGetOptoBit(Boardnumber, BIT_5, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command6.BackColor = vbGreen
    Else
    Command6.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command7_Click()
If me630DIGetOptoBit(Boardnumber, BIT_6, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command7.BackColor = vbGreen
    Else
    Command7.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command8_Click()
If me630DIGetOptoBit(Boardnumber, BIT_7, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command8.BackColor = vbGreen
    Else
    Command8.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command9_Click()
    Form6.Hide
    Unload Form6
End Sub
