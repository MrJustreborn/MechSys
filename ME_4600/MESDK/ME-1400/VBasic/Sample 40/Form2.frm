VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "DIGetBit"
   ClientHeight    =   4830
   ClientLeft      =   3045
   ClientTop       =   2985
   ClientWidth     =   9720
   LinkTopic       =   "Form2"
   ScaleHeight     =   4830
   ScaleWidth      =   9720
   Begin VB.CommandButton Command49 
      Caption         =   "Exit"
      Default         =   -1  'True
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
      Left            =   8160
      TabIndex        =   54
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton Command48 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   51
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command47 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   50
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command46 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   49
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command45 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   48
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command44 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   47
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command43 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   46
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command42 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   45
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command41 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   6480
      Style           =   1  'Grafisch
      TabIndex        =   44
      Top             =   840
      Width           =   615
   End
   Begin VB.CommandButton Command40 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   43
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command39 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   42
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command38 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   41
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command37 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   40
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command36 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   39
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command35 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   38
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command34 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   37
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command33 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   5400
      Style           =   1  'Grafisch
      TabIndex        =   36
      Top             =   840
      Width           =   615
   End
   Begin VB.CommandButton Command32 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   34
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command31 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   33
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command30 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   32
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command29 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   31
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command28 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   30
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command27 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   29
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command26 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   28
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command25 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   4320
      Style           =   1  'Grafisch
      TabIndex        =   27
      Top             =   840
      Width           =   615
   End
   Begin VB.CommandButton Command24 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   23
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command23 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   22
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command22 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   21
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command21 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   20
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command20 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   19
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command19 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   18
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command18 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   17
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command17 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   2520
      Style           =   1  'Grafisch
      TabIndex        =   16
      Top             =   840
      Width           =   615
   End
   Begin VB.CommandButton Command16 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   15
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command15 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   14
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command14 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   13
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command13 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   12
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command12 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   11
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command11 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   10
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command10 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   9
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command9 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   1440
      Style           =   1  'Grafisch
      TabIndex        =   8
      Top             =   840
      Width           =   615
   End
   Begin VB.CommandButton Command8 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   7
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command7 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   6
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command6 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   5
      Top             =   3240
      Width           =   615
   End
   Begin VB.CommandButton Command5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   4
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   3
      Top             =   2280
      Width           =   615
   End
   Begin VB.CommandButton Command3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   2
      Top             =   1800
      Width           =   615
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   1
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   360
      Style           =   1  'Grafisch
      TabIndex        =   0
      Top             =   840
      Width           =   615
   End
   Begin VB.Label Label8 
      Caption         =   "only 1400 B"
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
      Left            =   5280
      TabIndex        =   56
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label7 
      Caption         =   "1400 A/B"
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
      Left            =   1560
      TabIndex        =   55
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label6 
      Caption         =   "Port F"
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
      Left            =   6480
      TabIndex        =   53
      Top             =   600
      Width           =   855
   End
   Begin VB.Label Label5 
      Caption         =   "Port E"
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
      Left            =   5400
      TabIndex        =   52
      Top             =   600
      Width           =   735
   End
   Begin VB.Label Label4 
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
      Height          =   255
      Left            =   4320
      TabIndex        =   35
      Top             =   600
      Width           =   615
   End
   Begin VB.Label Label3 
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
      Height          =   255
      Left            =   2520
      TabIndex        =   26
      Top             =   600
      Width           =   735
   End
   Begin VB.Label Label2 
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
      Height          =   255
      Left            =   1440
      TabIndex        =   25
      Top             =   600
      Width           =   735
   End
   Begin VB.Label Label1 
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
      Height          =   255
      Left            =   360
      TabIndex        =   24
      Top             =   600
      Width           =   735
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
 If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command1.BackColor = vbGreen
    Else
    Command1.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command10_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command10.BackColor = vbGreen
    Else
    Command10.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command11_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command11.BackColor = vbGreen
    Else
    Command11.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command12_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command12.BackColor = vbGreen
    Else
    Command12.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command13_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command13.BackColor = vbGreen
    Else
    Command13.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command14_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command14.BackColor = vbGreen
    Else
    Command14.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command15_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command15.BackColor = vbGreen
    Else
    Command15.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command16_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command16.BackColor = vbGreen
    Else
    Command16.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command17_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command17.BackColor = vbGreen
    Else
    Command17.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command18_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command18.BackColor = vbGreen
    Else
    Command18.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command19_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command19.BackColor = vbGreen
    Else
    Command19.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command2_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command2.BackColor = vbGreen
    Else
    Command2.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command20_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command20.BackColor = vbGreen
    Else
    Command20.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command21_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command21.BackColor = vbGreen
    Else
    Command21.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command22_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command22.BackColor = vbGreen
    Else
    Command22.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command23_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command23.BackColor = vbGreen
    Else
    Command23.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command24_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTC, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command24.BackColor = vbGreen
    Else
    Command24.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command25_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command25.BackColor = vbGreen
    Else
    Command25.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command26_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command26.BackColor = vbGreen
    Else
    Command26.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command27_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command27.BackColor = vbGreen
    Else
    Command27.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command28_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command28.BackColor = vbGreen
    Else
    Command28.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command29_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command29.BackColor = vbGreen
    Else
    Command29.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command3_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command3.BackColor = vbGreen
    Else
    Command3.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command30_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command30.BackColor = vbGreen
    Else
    Command30.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command31_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command31.BackColor = vbGreen
    Else
    Command31.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command32_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTD, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command32.BackColor = vbGreen
    Else
    Command32.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command33_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command33.BackColor = vbGreen
    Else
    Command33.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command34_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command34.BackColor = vbGreen
    Else
    Command34.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command35_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command35.BackColor = vbGreen
    Else
    Command35.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command36_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command36.BackColor = vbGreen
    Else
    Command36.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command37_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command37.BackColor = vbGreen
    Else
    Command37.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command38_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command38.BackColor = vbGreen
    Else
    Command38.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command39_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command39.BackColor = vbGreen
    Else
    Command39.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command4_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command4.BackColor = vbGreen
    Else
    Command4.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command40_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTE, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command40.BackColor = vbGreen
    Else
    Command40.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command41_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command41.BackColor = vbGreen
    Else
    Command41.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command42_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_1, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command42.BackColor = vbGreen
    Else
    Command42.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command43_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_2, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command43.BackColor = vbGreen
    Else
    Command43.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command44_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_3, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command44.BackColor = vbGreen
    Else
    Command44.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command45_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command45.BackColor = vbGreen
    Else
    Command45.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command46_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command46.BackColor = vbGreen
    Else
    Command46.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command47_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command47.BackColor = vbGreen
    Else
    Command47.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command48_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTF, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command48.BackColor = vbGreen
    Else
    Command48.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command49_Click()
    Unload Form2
End Sub

Private Sub Command5_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_4, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command5.BackColor = vbGreen
    Else
    Command5.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command6_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_5, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command6.BackColor = vbGreen
    Else
    Command6.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command7_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_6, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command7.BackColor = vbGreen
    Else
    Command7.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command8_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTA, BIT_7, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command8.BackColor = vbGreen
    Else
    Command8.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command9_Click()
If me1400DIGetBit(Boardnumber, ME1400_PORTB, BIT_0, iValueX_0) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If iValueX_0 = 1 Then
    Command9.BackColor = vbGreen
    Else
    Command9.BackColor = &HC0C0C0
    End If
End Sub
