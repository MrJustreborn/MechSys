VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "DIGetBit"
   ClientHeight    =   6720
   ClientLeft      =   3855
   ClientTop       =   1800
   ClientWidth     =   6075
   FillColor       =   &H0000FFFF&
   LinkTopic       =   "Form3"
   ScaleHeight     =   6720
   ScaleWidth      =   6075
   Begin VB.CommandButton Command65 
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
      Left            =   4320
      TabIndex        =   69
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port Change"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1335
      Left            =   4200
      TabIndex        =   66
      Top             =   960
      Width           =   1575
      Begin VB.OptionButton Option2 
         Caption         =   "Port C-D"
         Height          =   255
         Left            =   240
         TabIndex        =   68
         Top             =   840
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A-B"
         Height          =   255
         Left            =   240
         TabIndex        =   67
         Top             =   360
         Value           =   -1  'True
         Width           =   1095
      End
   End
   Begin VB.CommandButton Command64 
      Caption         =   "Bit 31"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   65
      Top             =   6360
      Width           =   615
   End
   Begin VB.CommandButton Command63 
      Caption         =   "Bit 30"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   64
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Command62 
      Caption         =   "Bit 29"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   63
      Top             =   5640
      Width           =   615
   End
   Begin VB.CommandButton Command61 
      Caption         =   "Bit 28"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   62
      Top             =   5280
      Width           =   615
   End
   Begin VB.CommandButton Command60 
      Caption         =   "Bit 27"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   61
      Top             =   4920
      Width           =   615
   End
   Begin VB.CommandButton Command59 
      Caption         =   "Bit 26"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   60
      Top             =   4560
      Width           =   615
   End
   Begin VB.CommandButton Command58 
      Caption         =   "Bit 25"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   59
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command57 
      Caption         =   "Bit 24"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   58
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command56 
      Caption         =   "Bit 23"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   57
      Top             =   3480
      Width           =   615
   End
   Begin VB.CommandButton Command55 
      Caption         =   "Bit 22"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   56
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Command54 
      Caption         =   "Bit 21"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   55
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command53 
      Caption         =   "Bit 20"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   54
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Command52 
      Caption         =   "Bit 19"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   53
      Top             =   2040
      Width           =   615
   End
   Begin VB.CommandButton Command51 
      Caption         =   "Bit 18"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   52
      Top             =   1680
      Width           =   615
   End
   Begin VB.CommandButton Command50 
      Caption         =   "Bit 17"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   51
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command49 
      Caption         =   "Bit 16"
      Height          =   255
      Left            =   3120
      Style           =   1  'Grafisch
      TabIndex        =   50
      Top             =   960
      Width           =   615
   End
   Begin VB.CommandButton Command48 
      Caption         =   "Bit 15"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   49
      Top             =   6360
      Width           =   615
   End
   Begin VB.CommandButton Command47 
      Caption         =   "Bit 14"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   48
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Command46 
      Caption         =   "Bit 13"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   47
      Top             =   5640
      Width           =   615
   End
   Begin VB.CommandButton Command45 
      Caption         =   "Bit 12"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   46
      Top             =   5280
      Width           =   615
   End
   Begin VB.CommandButton Command44 
      Caption         =   "Bit 11"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   45
      Top             =   4920
      Width           =   615
   End
   Begin VB.CommandButton Command43 
      Caption         =   "Bit 10"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   44
      Top             =   4560
      Width           =   615
   End
   Begin VB.CommandButton Command42 
      Caption         =   "Bit 9"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   43
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command41 
      Caption         =   "Bit 8"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   42
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command40 
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   41
      Top             =   3480
      Width           =   615
   End
   Begin VB.CommandButton Command39 
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   40
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Command38 
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   39
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command37 
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   38
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Command36 
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   37
      Top             =   2040
      Width           =   615
   End
   Begin VB.CommandButton Command35 
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   36
      Top             =   1680
      Width           =   615
   End
   Begin VB.CommandButton Command34 
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   35
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command33 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   2280
      Style           =   1  'Grafisch
      TabIndex        =   34
      Top             =   960
      Width           =   615
   End
   Begin VB.CommandButton Command32 
      Caption         =   "Bit 31"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   33
      Top             =   6360
      Width           =   615
   End
   Begin VB.CommandButton Command31 
      Caption         =   "Bit 30"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   32
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Command30 
      Caption         =   "Bit 29"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   31
      Top             =   5640
      Width           =   615
   End
   Begin VB.CommandButton Command29 
      Caption         =   "Bit 28"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   30
      Top             =   5280
      Width           =   615
   End
   Begin VB.CommandButton Command28 
      Caption         =   "Bit 27"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   29
      Top             =   4920
      Width           =   615
   End
   Begin VB.CommandButton Command27 
      Caption         =   "Bit 26"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   28
      Top             =   4560
      Width           =   615
   End
   Begin VB.CommandButton Command26 
      Caption         =   "Bit 25"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   27
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command25 
      Caption         =   "Bit 24"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   26
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command24 
      Caption         =   "Bit 23"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   25
      Top             =   3480
      Width           =   615
   End
   Begin VB.CommandButton Command23 
      Caption         =   "Bit 22"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   24
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Command22 
      Caption         =   "Bit 21"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   23
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command21 
      Caption         =   "Bit 20"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   22
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Command20 
      Caption         =   "Bit 19"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   21
      Top             =   2040
      Width           =   615
   End
   Begin VB.CommandButton Command19 
      Caption         =   "Bit 18"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   20
      Top             =   1680
      Width           =   615
   End
   Begin VB.CommandButton Command18 
      Caption         =   "Bit 17"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   19
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command17 
      Caption         =   "Bit 16"
      Height          =   255
      Left            =   840
      Style           =   1  'Grafisch
      TabIndex        =   18
      Top             =   960
      Width           =   615
   End
   Begin VB.CommandButton Command16 
      Caption         =   "Bit 15"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   17
      Top             =   6360
      Width           =   615
   End
   Begin VB.CommandButton Command15 
      Caption         =   "Bit 14"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   16
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Command14 
      Caption         =   "Bit 13"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   15
      Top             =   5640
      Width           =   615
   End
   Begin VB.CommandButton Command13 
      Caption         =   "Bit 12"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   14
      Top             =   5280
      Width           =   615
   End
   Begin VB.CommandButton Command12 
      Caption         =   "Bit 11"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   13
      Top             =   4920
      Width           =   615
   End
   Begin VB.CommandButton Command11 
      Caption         =   "Bit 10"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   12
      Top             =   4560
      Width           =   615
   End
   Begin VB.CommandButton Command10 
      Caption         =   "Bit 9"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   11
      Top             =   4200
      Width           =   615
   End
   Begin VB.CommandButton Command9 
      Caption         =   "Bit 8"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   10
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command8 
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   9
      Top             =   3480
      Width           =   615
   End
   Begin VB.CommandButton Command7 
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   8
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   7
      Top             =   2760
      Width           =   615
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   6
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   5
      Top             =   2040
      Width           =   615
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   4
      Top             =   1680
      Width           =   615
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   3
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   2
      Top             =   960
      Width           =   615
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Zentriert
      Caption         =   "Port B/D"
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
      Left            =   2400
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "Port A/C"
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
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit




Private Sub Command1_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_0, iValueX_0) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_0 = 1 Then
    Command1.BackColor = vbGreen
    Else
    Command1.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command10_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_9, iValueX_9) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_9 = 1 Then
    Command10.BackColor = vbGreen
    Else
    Command10.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command11_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_10, iValueX_10) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_10 = 1 Then
    Command11.BackColor = vbGreen
    Else
    Command11.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command12_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_11, iValueX_11) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_11 = 1 Then
    Command12.BackColor = vbGreen
    Else
    Command12.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command13_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_12, iValueX_12) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_12 = 1 Then
    Command13.BackColor = vbGreen
    Else
    Command13.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command14_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_13, iValueX_13) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_13 = 1 Then
    Command14.BackColor = vbGreen
    Else
    Command14.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command15_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_14, iValueX_14) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_14 = 1 Then
    Command15.BackColor = vbGreen
    Else
    Command15.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command16_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_15, iValueX_15) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_15 = 1 Then
    Command16.BackColor = vbGreen
    Else
    Command16.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command17_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_16, iValueX_16) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_16 = 1 Then
    Command17.BackColor = vbGreen
    Else
    Command17.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command18_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_17, iValueX_17) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_17 = 1 Then
    Command18.BackColor = vbGreen
    Else
    Command18.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command19_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_18, iValueX_18) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_18 = 1 Then
    Command19.BackColor = vbGreen
    Else
    Command19.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command2_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_1, iValueX_1) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_1 = 1 Then
    Command2.BackColor = vbGreen
    Else
    Command2.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command20_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_19, iValueX_19) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_19 = 1 Then
    Command20.BackColor = vbGreen
    Else
    Command20.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command21_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_20, iValueX_20) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_20 = 1 Then
    Command21.BackColor = vbGreen
    Else
    Command21.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command22_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_21, iValueX_21) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_21 = 1 Then
    Command22.BackColor = vbGreen
    Else
    Command22.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command23_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_22, iValueX_22) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_22 = 1 Then
    Command23.BackColor = vbGreen
    Else
    Command23.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command24_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_23, iValueX_23) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_23 = 1 Then
    Command24.BackColor = vbGreen
    Else
    Command24.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command25_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_24, iValueX_24) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_24 = 1 Then
    Command25.BackColor = vbGreen
    Else
    Command25.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command26_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_25, iValueX_25) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_25 = 1 Then
    Command26.BackColor = vbGreen
    Else
    Command26.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command27_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_26, iValueX_26) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_26 = 1 Then
    Command27.BackColor = vbGreen
    Else
    Command27.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command28_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_27, iValueX_27) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_27 = 1 Then
    Command28.BackColor = vbGreen
    Else
    Command28.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command29_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_28, iValueX_28) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_28 = 1 Then
    Command29.BackColor = vbGreen
    Else
    Command29.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command3_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_2, iValueX_2) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_2 = 1 Then
    Command3.BackColor = vbGreen
    Else
    Command3.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command30_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_29, iValueX_29) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_29 = 1 Then
    Command30.BackColor = vbGreen
    Else
    Command30.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command31_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_30, iValueX_30) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_30 = 1 Then
    Command31.BackColor = vbGreen
    Else
    Command31.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command32_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_31, iValueX_31) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_31 = 1 Then
    Command32.BackColor = vbGreen
    Else
    Command32.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command33_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_0, iValueY_0) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_0 = 1 Then
    Command33.BackColor = vbGreen
    Else
    Command33.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command34_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_1, iValueY_1) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_1 = 1 Then
    Command34.BackColor = vbGreen
    Else
    Command34.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command35_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_2, iValueY_2) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_2 = 1 Then
    Command35.BackColor = vbGreen
    Else
    Command35.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command36_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_3, iValueY_3) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_3 = 1 Then
    Command36.BackColor = vbGreen
    Else
    Command36.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command37_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_4, iValueY_4) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_4 = 1 Then
    Command37.BackColor = vbGreen
    Else
    Command37.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command38_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_5, iValueY_5) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_5 = 1 Then
    Command38.BackColor = vbGreen
    Else
    Command38.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command39_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_6, iValueY_6) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_6 = 1 Then
    Command39.BackColor = vbGreen
    Else
    Command39.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command4_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_3, iValueX_3) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_3 = 1 Then
    Command4.BackColor = vbGreen
    Else
    Command4.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command40_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_7, iValueY_7) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_7 = 1 Then
    Command40.BackColor = vbGreen
    Else
    Command40.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command41_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_8, iValueY_8) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_8 = 1 Then
    Command41.BackColor = vbGreen
    Else
    Command41.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command42_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_9, iValueY_9) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_9 = 1 Then
    Command42.BackColor = vbGreen
    Else
    Command42.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command43_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_10, iValueY_10) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_10 = 1 Then
    Command43.BackColor = vbGreen
    Else
    Command43.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command44_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_11, iValueY_11) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_11 = 1 Then
    Command44.BackColor = vbGreen
    Else
    Command44.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command45_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_12, iValueY_12) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_12 = 1 Then
    Command45.BackColor = vbGreen
    Else
    Command45.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command46_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_13, iValueY_13) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_13 = 1 Then
    Command46.BackColor = vbGreen
    Else
    Command46.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command47_Click()
If me1000DIGetBit(Boardnumber, Port_Y, BIT_14, iValueY_14) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_14 = 1 Then
    Command47.BackColor = vbGreen
    Else
    Command47.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command48_Click()
If me1000DIGetBit(Boardnumber, Port_Y, BIT_15, iValueY_15) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_15 = 1 Then
    Command48.BackColor = vbGreen
    Else
    Command48.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command49_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_16, iValueY_16) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_16 = 1 Then
    Command49.BackColor = vbGreen
    Else
    Command49.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command5_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_4, iValueX_4) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_4 = 1 Then
    Command5.BackColor = vbGreen
    Else
    Command5.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command50_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_17, iValueY_17) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_17 = 1 Then
    Command50.BackColor = vbGreen
    Else
    Command50.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command51_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_18, iValueY_18) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_18 = 1 Then
    Command51.BackColor = vbGreen
    Else
    Command51.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command52_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_19, iValueY_19) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_19 = 1 Then
    Command52.BackColor = vbGreen
    Else
    Command52.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command53_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_20, iValueY_20) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_20 = 1 Then
    Command53.BackColor = vbGreen
    Else
    Command53.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command54_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_21, iValueY_21) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_21 = 1 Then
    Command54.BackColor = vbGreen
    Else
    Command54.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command55_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_22, iValueY_22) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_22 = 1 Then
    Command55.BackColor = vbGreen
    Else
    Command55.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command56_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_23, iValueY_23) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_23 = 1 Then
    Command56.BackColor = vbGreen
    Else
    Command56.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command57_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_24, iValueY_24) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_24 = 1 Then
    Command57.BackColor = vbGreen
    Else
    Command57.BackColor = &HC0C0C0
    End If

End Sub

Private Sub Command58_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_25, iValueY_25) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_25 = 1 Then
    Command58.BackColor = vbGreen
    Else
    Command58.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command59_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_26, iValueY_26) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_26 = 1 Then
    Command59.BackColor = vbGreen
    Else
    Command59.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command6_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_5, iValueX_5) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_5 = 1 Then
    Command6.BackColor = vbGreen
    Else
    Command6.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command60_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_27, iValueY_27) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_27 = 1 Then
    Command60.BackColor = vbGreen
    Else
    Command60.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command61_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_28, iValueY_28) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_28 = 1 Then
    Command61.BackColor = vbGreen
    Else
    Command61.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command62_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_29, iValueY_29) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_29 = 1 Then
    Command62.BackColor = vbGreen
    Else
    Command62.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command63_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_30, iValueY_30) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_30 = 1 Then
    Command63.BackColor = vbGreen
    Else
    Command63.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command64_Click()
    If me1000DIGetBit(Boardnumber, Port_Y, BIT_31, iValueY_31) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueY_31 = 1 Then
    Command64.BackColor = vbGreen
    Else
    Command64.BackColor = &HC0C0C0
End If
End Sub

Private Sub Command65_Click()
    Form3.Hide
    Unload Form3
End Sub



Private Sub Command7_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_6, iValueX_6) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_6 = 1 Then
    Command7.BackColor = vbGreen
    Else
    Command7.BackColor = &HC0C0C0
    End If
End Sub


Private Sub Command8_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_7, iValueX_7) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_7 = 1 Then
    Command8.BackColor = vbGreen
    Else
    Command8.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Command9_Click()
    If me1000DIGetBit(Boardnumber, Port_X, BIT_8, iValueX_8) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If iValueX_8 = 1 Then
    Command9.BackColor = vbGreen
    Else
    Command9.BackColor = &HC0C0C0
    End If
End Sub

Private Sub Form_Load()
    Boardnumber = 0
End Sub



Private Sub Option1_Click()
If Option1.Value = True Then
    Port_X = PORTA
    Port_Y = PORTB
    End If
End Sub

Private Sub Option2_Click()
If Option2.Value = True Then
   Port_X = PORTC
   Port_Y = PORTD
   End If
End Sub
