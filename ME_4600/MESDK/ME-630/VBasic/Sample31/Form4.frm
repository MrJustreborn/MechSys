VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "DIGetTTLBit"
   ClientHeight    =   4575
   ClientLeft      =   6045
   ClientTop       =   3975
   ClientWidth     =   3345
   ControlBox      =   0   'False
   LinkTopic       =   "Form4"
   ScaleHeight     =   4575
   ScaleWidth      =   3345
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
      Left            =   1680
      TabIndex        =   8
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CommandButton Command8 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   7
      Top             =   3960
      Width           =   615
   End
   Begin VB.CommandButton Command7 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   6
      Top             =   3480
      Width           =   615
   End
   Begin VB.CommandButton Command6 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   5
      Top             =   3000
      Width           =   615
   End
   Begin VB.CommandButton Command5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   4
      Top             =   2520
      Width           =   615
   End
   Begin VB.CommandButton Command4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   3
      Top             =   2040
      Width           =   615
   End
   Begin VB.CommandButton Command3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   2
      Top             =   1560
      Width           =   615
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   1
      Top             =   1080
      Width           =   615
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   480
      Style           =   1  'Grafisch
      TabIndex        =   0
      Top             =   600
      Width           =   615
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
 If me630DIGetTTLBit(Boardnumber, BIT_0, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command1.BackColor = vbGreen
    Else
    Command1.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command2_Click()
If me630DIGetTTLBit(Boardnumber, BIT_1, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command2.BackColor = vbGreen
    Else
    Command2.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command3_Click()
If me630DIGetTTLBit(Boardnumber, BIT_2, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command3.BackColor = vbGreen
    Else
    Command3.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command4_Click()
If me630DIGetTTLBit(Boardnumber, BIT_3, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command4.BackColor = vbGreen
    Else
    Command4.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command5_Click()
If me630DIGetTTLBit(Boardnumber, BIT_4, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command5.BackColor = vbGreen
    Else
    Command5.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command6_Click()
If me630DIGetTTLBit(Boardnumber, BIT_5, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command6.BackColor = vbGreen
    Else
    Command6.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command7_Click()
If me630DIGetTTLBit(Boardnumber, BIT_6, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command7.BackColor = vbGreen
    Else
    Command7.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command8_Click()
If me630DIGetTTLBit(Boardnumber, BIT_7, iValue) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    End If
    If iValue = 1 Then
    Command8.BackColor = vbGreen
    Else
    Command8.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command9_Click()
    Form4.Hide
    Unload Form4
End Sub
