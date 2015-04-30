VERSION 5.00
Begin VB.Form Form6 
   Caption         =   "DOSetBit"
   ClientHeight    =   7410
   ClientLeft      =   3855
   ClientTop       =   1590
   ClientWidth     =   8505
   LinkTopic       =   "Form6"
   ScaleHeight     =   7410
   ScaleWidth      =   8505
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
      Height          =   615
      Left            =   6360
      TabIndex        =   67
      Top             =   5400
      Width           =   1335
   End
   Begin VB.CheckBox Check64 
      Caption         =   "Bit 31"
      Height          =   255
      Left            =   4560
      TabIndex        =   66
      Top             =   6840
      Width           =   855
   End
   Begin VB.CheckBox Check63 
      Caption         =   "Bit 30"
      Height          =   255
      Left            =   4560
      TabIndex        =   65
      Top             =   6480
      Width           =   855
   End
   Begin VB.CheckBox Check62 
      Caption         =   "Bit 29"
      Height          =   255
      Left            =   4560
      TabIndex        =   64
      Top             =   6120
      Width           =   855
   End
   Begin VB.CheckBox Check61 
      Caption         =   "Bit 28"
      Height          =   255
      Left            =   4560
      TabIndex        =   63
      Top             =   5760
      Width           =   855
   End
   Begin VB.CheckBox Check60 
      Caption         =   "Bit 27"
      Height          =   255
      Left            =   4560
      TabIndex        =   62
      Top             =   5400
      Width           =   855
   End
   Begin VB.CheckBox Check59 
      Caption         =   "Bit 26"
      Height          =   255
      Left            =   4560
      TabIndex        =   61
      Top             =   5040
      Width           =   855
   End
   Begin VB.CheckBox Check58 
      Caption         =   "Bit 25"
      Height          =   255
      Left            =   4560
      TabIndex        =   60
      Top             =   4680
      Width           =   855
   End
   Begin VB.CheckBox Check57 
      Caption         =   "Bit 24"
      Height          =   255
      Left            =   4560
      TabIndex        =   59
      Top             =   4320
      Width           =   855
   End
   Begin VB.CheckBox Check56 
      Caption         =   "Bit 23"
      Height          =   255
      Left            =   4560
      TabIndex        =   58
      Top             =   3960
      Width           =   855
   End
   Begin VB.CheckBox Check55 
      Caption         =   "Bit 22"
      Height          =   255
      Left            =   4560
      TabIndex        =   57
      Top             =   3600
      Width           =   855
   End
   Begin VB.CheckBox Check54 
      Caption         =   "Bit 21"
      Height          =   255
      Left            =   4560
      TabIndex        =   56
      Top             =   3240
      Width           =   855
   End
   Begin VB.CheckBox Check53 
      Caption         =   "Bit 20"
      Height          =   255
      Left            =   4560
      TabIndex        =   55
      Top             =   2880
      Width           =   855
   End
   Begin VB.CheckBox Check52 
      Caption         =   "Bit 19"
      Height          =   255
      Left            =   4560
      TabIndex        =   54
      Top             =   2520
      Width           =   855
   End
   Begin VB.CheckBox Check51 
      Caption         =   "Bit 18"
      Height          =   255
      Left            =   4560
      TabIndex        =   53
      Top             =   2160
      Width           =   855
   End
   Begin VB.CheckBox Check50 
      Caption         =   "Bit 17"
      Height          =   255
      Left            =   4560
      TabIndex        =   52
      Top             =   1800
      Width           =   855
   End
   Begin VB.CheckBox Check49 
      Caption         =   "Bit 16"
      Height          =   255
      Left            =   4560
      TabIndex        =   51
      Top             =   1440
      Width           =   855
   End
   Begin VB.CheckBox Check48 
      Caption         =   "Bit 15"
      Height          =   255
      Left            =   3480
      TabIndex        =   50
      Top             =   6840
      Width           =   855
   End
   Begin VB.CheckBox Check47 
      Caption         =   "Bit 14"
      Height          =   255
      Left            =   3480
      TabIndex        =   49
      Top             =   6480
      Width           =   855
   End
   Begin VB.CheckBox Check46 
      Caption         =   "Bit 13"
      Height          =   255
      Left            =   3480
      TabIndex        =   48
      Top             =   6120
      Width           =   855
   End
   Begin VB.CheckBox Check45 
      Caption         =   "Bit 12"
      Height          =   255
      Left            =   3480
      TabIndex        =   47
      Top             =   5760
      Width           =   855
   End
   Begin VB.CheckBox Check44 
      Caption         =   "Bit 11"
      Height          =   255
      Left            =   3480
      TabIndex        =   46
      Top             =   5400
      Width           =   855
   End
   Begin VB.CheckBox Check43 
      Caption         =   "Bit 10"
      Height          =   255
      Left            =   3480
      TabIndex        =   45
      Top             =   5040
      Width           =   855
   End
   Begin VB.CheckBox Check42 
      Caption         =   "Bit 9"
      Height          =   255
      Left            =   3480
      TabIndex        =   44
      Top             =   4680
      Width           =   855
   End
   Begin VB.CheckBox Check41 
      Caption         =   "Bit 8"
      Height          =   255
      Left            =   3480
      TabIndex        =   43
      Top             =   4320
      Width           =   855
   End
   Begin VB.CheckBox Check40 
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   3480
      TabIndex        =   42
      Top             =   3960
      Width           =   855
   End
   Begin VB.CheckBox Check39 
      Caption         =   "Bit 6"
      Height          =   255
      Left            =   3480
      TabIndex        =   41
      Top             =   3600
      Width           =   855
   End
   Begin VB.CheckBox Check38 
      Caption         =   "Bit 5"
      Height          =   255
      Left            =   3480
      TabIndex        =   40
      Top             =   3240
      Width           =   855
   End
   Begin VB.CheckBox Check37 
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   3480
      TabIndex        =   39
      Top             =   2880
      Width           =   855
   End
   Begin VB.CheckBox Check36 
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   3480
      TabIndex        =   38
      Top             =   2520
      Width           =   855
   End
   Begin VB.CheckBox Check35 
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   3480
      TabIndex        =   37
      Top             =   2160
      Width           =   855
   End
   Begin VB.CheckBox Check34 
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   3480
      TabIndex        =   36
      Top             =   1800
      Width           =   855
   End
   Begin VB.CheckBox Check33 
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   3480
      TabIndex        =   35
      Top             =   1440
      Width           =   855
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
      Height          =   1575
      Left            =   6120
      TabIndex        =   32
      Top             =   1320
      Width           =   1695
      Begin VB.OptionButton Option2 
         Caption         =   "Port C-D"
         Height          =   375
         Left            =   240
         TabIndex        =   34
         Top             =   840
         Width           =   1215
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A-B"
         Height          =   375
         Left            =   240
         TabIndex        =   33
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.CheckBox Check32 
      Caption         =   "Bit 31"
      Height          =   255
      Left            =   1200
      TabIndex        =   31
      Top             =   6840
      Width           =   855
   End
   Begin VB.CheckBox Check31 
      Caption         =   "Bit 30"
      Height          =   255
      Left            =   1200
      TabIndex        =   30
      Top             =   6480
      Width           =   855
   End
   Begin VB.CheckBox Check30 
      Caption         =   "Bit 29"
      Height          =   255
      Left            =   1200
      TabIndex        =   29
      Top             =   6120
      Width           =   855
   End
   Begin VB.CheckBox Check29 
      Caption         =   "Bit 28"
      Height          =   255
      Left            =   1200
      TabIndex        =   28
      Top             =   5760
      Width           =   855
   End
   Begin VB.CheckBox Check28 
      Caption         =   "Bit 27"
      Height          =   255
      Left            =   1200
      TabIndex        =   27
      Top             =   5400
      Width           =   855
   End
   Begin VB.CheckBox Check27 
      Caption         =   "Bit 26"
      Height          =   255
      Left            =   1200
      TabIndex        =   26
      Top             =   5040
      Width           =   855
   End
   Begin VB.CheckBox Check26 
      Caption         =   "Bit 25"
      Height          =   255
      Left            =   1200
      TabIndex        =   25
      Top             =   4680
      Width           =   855
   End
   Begin VB.CheckBox Check25 
      Caption         =   "Bit 24"
      Height          =   255
      Left            =   1200
      TabIndex        =   24
      Top             =   4320
      Width           =   855
   End
   Begin VB.CheckBox Check24 
      Caption         =   "Bit 23"
      Height          =   255
      Left            =   1200
      TabIndex        =   23
      Top             =   3960
      Width           =   855
   End
   Begin VB.CheckBox Check23 
      Caption         =   "Bit 22"
      Height          =   255
      Left            =   1200
      TabIndex        =   22
      Top             =   3600
      Width           =   855
   End
   Begin VB.CheckBox Check22 
      Caption         =   "Bit 21"
      Height          =   255
      Left            =   1200
      TabIndex        =   21
      Top             =   3240
      Width           =   855
   End
   Begin VB.CheckBox Check21 
      Caption         =   "Bit 20"
      Height          =   255
      Left            =   1200
      TabIndex        =   20
      Top             =   2880
      Width           =   855
   End
   Begin VB.CheckBox Check20 
      Caption         =   "Bit 19"
      Height          =   255
      Left            =   1200
      TabIndex        =   19
      Top             =   2520
      Width           =   855
   End
   Begin VB.CheckBox Check19 
      Caption         =   "Bit 18"
      Height          =   255
      Left            =   1200
      TabIndex        =   18
      Top             =   2160
      Width           =   855
   End
   Begin VB.CheckBox Check18 
      Caption         =   "Bit 17"
      Height          =   255
      Left            =   1200
      TabIndex        =   17
      Top             =   1800
      Width           =   855
   End
   Begin VB.CheckBox Check17 
      Caption         =   "Bit 16"
      Height          =   255
      Left            =   1200
      TabIndex        =   16
      Top             =   1440
      Width           =   855
   End
   Begin VB.CheckBox Check16 
      Caption         =   "Bit 15"
      Height          =   315
      Left            =   240
      TabIndex        =   15
      Top             =   6840
      Width           =   735
   End
   Begin VB.CheckBox Check15 
      Caption         =   "Bit 14"
      Height          =   375
      Left            =   240
      TabIndex        =   14
      Top             =   6480
      Width           =   735
   End
   Begin VB.CheckBox Check14 
      Caption         =   "Bit 13"
      Height          =   315
      Left            =   240
      TabIndex        =   13
      Top             =   6120
      Width           =   735
   End
   Begin VB.CheckBox Check13 
      Caption         =   "Bit 12"
      Height          =   375
      Left            =   240
      TabIndex        =   12
      Top             =   5760
      Width           =   735
   End
   Begin VB.CheckBox Check12 
      Caption         =   "Bit 11"
      Height          =   315
      Left            =   240
      TabIndex        =   11
      Top             =   5400
      Width           =   735
   End
   Begin VB.CheckBox Check11 
      Caption         =   "Bit 10"
      Height          =   315
      Left            =   240
      TabIndex        =   10
      Top             =   5040
      Width           =   735
   End
   Begin VB.CheckBox Check10 
      Caption         =   "Bit 9"
      Height          =   315
      Left            =   240
      TabIndex        =   9
      Top             =   4680
      Width           =   735
   End
   Begin VB.CheckBox Check9 
      Caption         =   "Bit 8"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   4320
      Width           =   735
   End
   Begin VB.CheckBox Check8 
      Caption         =   "Bit 7"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   3960
      Width           =   735
   End
   Begin VB.CheckBox Check7 
      Caption         =   "Bit 6"
      Height          =   315
      Left            =   240
      TabIndex        =   6
      Top             =   3600
      Width           =   735
   End
   Begin VB.CheckBox Check6 
      Caption         =   "Bit 5"
      Height          =   315
      Left            =   240
      TabIndex        =   5
      Top             =   3240
      Width           =   735
   End
   Begin VB.CheckBox Check5 
      Caption         =   "Bit 4"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   2880
      Width           =   735
   End
   Begin VB.CheckBox Check4 
      Caption         =   "Bit 3"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   2520
      Width           =   735
   End
   Begin VB.CheckBox Check3 
      Caption         =   "Bit 2"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2160
      Width           =   735
   End
   Begin VB.CheckBox Check2 
      Caption         =   "Bit 1"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   1800
      Width           =   735
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Bit 0"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   1440
      Width           =   735
   End
   Begin VB.Label Label2 
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
      Height          =   255
      Left            =   3720
      TabIndex        =   69
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label Label1 
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
      Height          =   255
      Left            =   480
      TabIndex        =   68
      Top             =   840
      Width           =   975
   End
End
Attribute VB_Name = "Form6"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Check1_Click()
If Check1.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_0, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_0, 0)
End If

End Sub

Private Sub Check10_Click()
If Check10.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_9, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_9, 0)
End If
End Sub

Private Sub Check11_Click()
If Check11.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_10, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_10, 0)
End If
End Sub

Private Sub Check12_Click()
If Check12.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_11, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_11, 0)
End If
End Sub

Private Sub Check13_Click()
If Check13.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_12, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_12, 0)
End If
End Sub

Private Sub Check14_Click()
If Check14.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_13, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_13, 0)
End If
End Sub

Private Sub Check15_Click()
If Check15.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_14, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_14, 0)
End If
End Sub

Private Sub Check16_Click()
If Check16.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_15, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_15, 0)
End If
End Sub

Private Sub Check17_Click()
If Check17.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_16, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_16, 0)
End If
End Sub

Private Sub Check18_Click()
If Check18.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_17, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_17, 0)
End If
End Sub

Private Sub Check19_Click()
If Check19.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_18, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_18, 0)
End If
End Sub

Private Sub Check2_Click()
If Check2.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_1, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_1, 0)
End If
End Sub

Private Sub Check20_Click()
If Check20.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_19, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_19, 0)
End If
End Sub

Private Sub Check21_Click()
If Check21.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_20, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_20, 0)
End If
End Sub

Private Sub Check22_Click()
If Check22.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_21, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_21, 0)
End If
End Sub

Private Sub Check23_Click()
If Check23.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_22, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_22, 0)
End If
End Sub


Private Sub Check24_Click()
If Check24.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_23, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_23, 0)
End If
End Sub

Private Sub Check25_Click()
If Check25.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_24, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_24, 0)
End If
End Sub

Private Sub Check26_Click()
If Check26.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_25, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_25, 0)
End If
End Sub

Private Sub Check27_Click()
If Check27.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_26, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_26, 0)
End If
End Sub

Private Sub Check28_Click()
If Check28.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_27, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_27, 0)
End If
End Sub

Private Sub Check29_Click()
If Check29.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_28, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_28, 0)
End If
End Sub

Private Sub Check3_Click()
If Check3.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_2, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_2, 0)
End If
End Sub

Private Sub Check30_Click()
If Check30.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_29, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_29, 0)
End If
End Sub

Private Sub Check31_Click()
If Check31.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_30, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_30, 0)
End If
End Sub

Private Sub Check32_Click()
If Check32.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_31, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_31, 0)
End If
End Sub

Private Sub Check33_Click()
If Check33.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_0, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_0, 0)
End If
End Sub

Private Sub Check34_Click()
If Check34.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_1, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_1, 0)
End If
End Sub

Private Sub Check35_Click()
If Check35.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_2, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_2, 0)
End If
End Sub

Private Sub Check36_Click()
If Check36.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_3, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_3, 0)
End If
End Sub

Private Sub Check37_Click()
If Check37.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_4, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_4, 0)
End If
End Sub

Private Sub Check38_Click()
If Check38.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_5, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_5, 0)
End If
End Sub

Private Sub Check39_Click()
If Check39.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_6, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_6, 0)
End If
End Sub

Private Sub Check4_Click()
If Check4.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_3, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_3, 0)
End If
End Sub

Private Sub Check40_Click()
If Check40.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_7, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_7, 0)
End If
End Sub

Private Sub Check41_Click()
If Check41.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_8, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_8, 0)
End If
End Sub

Private Sub Check42_Click()
If Check42.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_9, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_9, 0)
End If
End Sub

Private Sub Check43_Click()
If Check43.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_10, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_10, 0)
End If
End Sub

Private Sub Check44_Click()
If Check44.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_11, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_11, 0)
End If
End Sub

Private Sub Check45_Click()
If Check45.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_12, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_12, 0)
End If
End Sub

Private Sub Check46_Click()
If Check46.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_13, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_13, 0)
End If
End Sub

Private Sub Check47_Click()
If Check47.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_14, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_14, 0)
End If
End Sub

Private Sub Check48_Click()
If Check48.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_15, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_15, 0)
End If
End Sub

Private Sub Check49_Click()
If Check49.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_16, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_16, 0)
End If
End Sub

Private Sub Check5_Click()
If Check5.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_4, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_4, 0)
End If
End Sub

Private Sub Check50_Click()
If Check50.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_17, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_17, 0)
End If
End Sub

Private Sub Check51_Click()
If Check51.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_18, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_18, 0)
End If
End Sub

Private Sub Check52_Click()
If Check52.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_19, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_19, 0)
End If
End Sub

Private Sub Check53_Click()
If Check53.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_20, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_20, 0)
End If
End Sub

Private Sub Check54_Click()
If Check54.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_21, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_21, 0)
End If
End Sub

Private Sub Check55_Click()
If Check55.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_22, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_22, 0)
End If
End Sub

Private Sub Check56_Click()
If Check56.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_23, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_23, 0)
End If
End Sub

Private Sub Check57_Click()
If Check57.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_24, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_24, 0)
End If
End Sub

Private Sub Check58_Click()
If Check58.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_25, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_25, 0)
End If
End Sub

Private Sub Check59_Click()
If Check59.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_26, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_26, 0)
End If
End Sub

Private Sub Check6_Click()
If Check6.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_5, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_5, 0)
End If
End Sub

Private Sub Check60_Click()
If Check60.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_27, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_27, 0)
End If
End Sub

Private Sub Check61_Click()
If Check61.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_28, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_28, 0)
End If
End Sub

Private Sub Check62_Click()
If Check62.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_29, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_29, 0)
End If
End Sub

Private Sub Check63_Click()
If Check63.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_30, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_30, 0)
End If
End Sub

Private Sub Check64_Click()
If Check64.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_31, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_Y, BIT_31, 0)
End If
End Sub

Private Sub Check7_Click()
If Check7.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_6, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_6, 0)
End If
End Sub

Private Sub Check8_Click()
If Check8.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_7, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_7, 0)
End If
End Sub

Private Sub Check9_Click()
If Check9.Value = 1 Then
    retval = me1000DOSetBit(Boardnumber, Port_X, BIT_8, 1)
    Else: retval = me1000DOSetBit(Boardnumber, Port_X, BIT_8, 0)
End If
End Sub

Private Sub Command1_Click()
Form6.Hide
Unload Form6
End Sub

Private Sub Option1_Click()
    Port_X = PORTA
    Port_Y = PORTB
End Sub

Private Sub Option2_Click()
    Port_X = PORTC
    Port_Y = PORTD
End Sub
