VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "DOSetBit"
   ClientHeight    =   5010
   ClientLeft      =   3450
   ClientTop       =   2595
   ClientWidth     =   9135
   LinkTopic       =   "Form4"
   ScaleHeight     =   5010
   ScaleWidth      =   9135
   Begin VB.CommandButton Command1 
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
      Left            =   7560
      TabIndex        =   56
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CheckBox Check48 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   6240
      TabIndex        =   47
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check47 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   6240
      TabIndex        =   46
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check46 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   6240
      TabIndex        =   45
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check45 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   6240
      TabIndex        =   44
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check44 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   6240
      TabIndex        =   43
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check43 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   6240
      TabIndex        =   42
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check42 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   6240
      TabIndex        =   41
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check41 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   6240
      TabIndex        =   40
      Top             =   840
      Width           =   1215
   End
   Begin VB.CheckBox Check40 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   5280
      TabIndex        =   39
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check39 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   5280
      TabIndex        =   38
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check38 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   5280
      TabIndex        =   37
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check37 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   5280
      TabIndex        =   36
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check36 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   5280
      TabIndex        =   35
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check35 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   5280
      TabIndex        =   34
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check34 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   5280
      TabIndex        =   33
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check33 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   5280
      TabIndex        =   32
      Top             =   840
      Width           =   1215
   End
   Begin VB.CheckBox Check32 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   4320
      TabIndex        =   31
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check31 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   4320
      TabIndex        =   30
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check30 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   4320
      TabIndex        =   29
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check29 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   4320
      TabIndex        =   28
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check28 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   4320
      TabIndex        =   27
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check27 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   4320
      TabIndex        =   26
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check26 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   4320
      TabIndex        =   25
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check25 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   4320
      TabIndex        =   24
      Top             =   840
      Width           =   1215
   End
   Begin VB.CheckBox Check24 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   2160
      TabIndex        =   23
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check23 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   2160
      TabIndex        =   22
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check22 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   2160
      TabIndex        =   21
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check21 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   2160
      TabIndex        =   20
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check20 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   2160
      TabIndex        =   19
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check19 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   2160
      TabIndex        =   18
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check18 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   2160
      TabIndex        =   17
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check17 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   2160
      TabIndex        =   16
      Top             =   840
      Width           =   1215
   End
   Begin VB.CheckBox Check16 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   1200
      TabIndex        =   15
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check15 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   1200
      TabIndex        =   14
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check14 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   1200
      TabIndex        =   13
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check13 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   1200
      TabIndex        =   12
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check12 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   1200
      TabIndex        =   11
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check11 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   1200
      TabIndex        =   10
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check10 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   1200
      TabIndex        =   9
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check9 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   1200
      TabIndex        =   8
      Top             =   840
      Width           =   1215
   End
   Begin VB.CheckBox Check8 
      Caption         =   "Bit 7"
      Height          =   495
      Left            =   240
      TabIndex        =   7
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CheckBox Check7 
      Caption         =   "Bit 6"
      Height          =   495
      Left            =   240
      TabIndex        =   6
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CheckBox Check6 
      Caption         =   "Bit 5"
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CheckBox Check5 
      Caption         =   "Bit 4"
      Height          =   495
      Left            =   240
      TabIndex        =   4
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox Check4 
      Caption         =   "Bit 3"
      Height          =   495
      Left            =   240
      TabIndex        =   3
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CheckBox Check3 
      Caption         =   "Bit 2"
      Height          =   495
      Left            =   240
      TabIndex        =   2
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CheckBox Check2 
      Caption         =   "Bit 1"
      Height          =   495
      Left            =   240
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Bit 0"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label Label8 
      Caption         =   "only ME 1400 B"
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
      Left            =   5040
      TabIndex        =   55
      Top             =   120
      Width           =   1695
   End
   Begin VB.Label Label7 
      Caption         =   "ME 1400 A/B"
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
      Left            =   960
      TabIndex        =   54
      Top             =   120
      Width           =   1575
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
      Left            =   6240
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
      Left            =   5280
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
      TabIndex        =   51
      Top             =   600
      Width           =   735
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
      Left            =   2160
      TabIndex        =   50
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
      Left            =   1200
      TabIndex        =   49
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
      Left            =   240
      TabIndex        =   48
      Top             =   600
      Width           =   735
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Check1_Click()
    If Check1.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_0, 0)
    End If
End Sub

Private Sub Check10_Click()
    If Check10.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_1, 0)
    End If
End Sub

Private Sub Check11_Click()
    If Check11.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_2, 0)
    End If
End Sub

Private Sub Check12_Click()
 If Check12.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_3, 0)
    End If
End Sub

Private Sub Check13_Click()
    If Check13.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_4, 0)
    End If
End Sub

Private Sub Check14_Click()
    If Check14.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_5, 0)
    End If
End Sub

Private Sub Check15_Click()
    If Check15.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_6, 0)
    End If
End Sub

Private Sub Check16_Click()
    If Check16.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_7, 0)
    End If
End Sub

Private Sub Check17_Click()
    If Check17.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_0, 0)
    End If
End Sub

Private Sub Check18_Click()
    If Check18.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_1, 0)
    End If
End Sub

Private Sub Check19_Click()
    If Check19.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_2, 0)
    End If
End Sub

Private Sub Check2_Click()
    If Check2.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_1, 0)
    End If
End Sub

Private Sub Check20_Click()
    If Check20.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_3, 0)
    End If
End Sub

Private Sub Check21_Click()
    If Check21.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_4, 0)
    End If
End Sub

Private Sub Check22_Click()
    If Check22.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_5, 0)
    End If
End Sub

Private Sub Check23_Click()
    If Check23.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_6, 0)
    End If
End Sub

Private Sub Check24_Click()
    If Check24.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTC, BIT_7, 0)
    End If
End Sub

Private Sub Check25_Click()
    If Check25.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_0, 0)
    End If
End Sub

Private Sub Check26_Click()
    If Check26.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_1, 0)
    End If
End Sub

Private Sub Check27_Click()
    If Check27.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_2, 0)
    End If
End Sub

Private Sub Check28_Click()
    If Check28.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_3, 0)
    End If
End Sub

Private Sub Check29_Click()
    If Check29.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_4, 0)
    End If
End Sub

Private Sub Check3_Click()
    If Check3.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_2, 0)
    End If
End Sub

Private Sub Check30_Click()
    If Check30.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_5, 0)
    End If
End Sub

Private Sub Check31_Click()
     If Check31.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_6, 0)
    End If
End Sub

Private Sub Check32_Click()
     If Check32.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTD, BIT_7, 0)
    End If
End Sub

Private Sub Check33_Click()
    If Check33.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_0, 0)
    End If
End Sub

Private Sub Check34_Click()
    If Check34.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_1, 0)
    End If
End Sub

Private Sub Check35_Click()
    If Check35.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_2, 0)
    End If
End Sub

Private Sub Check36_Click()
    If Check36.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_3, 0)
    End If
End Sub

Private Sub Check37_Click()
    If Check37.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_4, 0)
    End If
End Sub

Private Sub Check38_Click()
    If Check38.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_5, 0)
    End If
End Sub

Private Sub Check39_Click()
    If Check39.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_6, 0)
    End If
End Sub

Private Sub Check4_Click()
    If Check4.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_3, 0)
    End If
End Sub

Private Sub Check40_Click()
    If Check40.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTE, BIT_7, 0)
    End If
End Sub

Private Sub Check41_Click()
    If Check41.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_0, 0)
    End If
End Sub

Private Sub Check42_Click()
    If Check42.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_1, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_1, 0)
    End If
End Sub

Private Sub Check43_Click()
    If Check43.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_2, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_2, 0)
    End If
End Sub

Private Sub Check44_Click()
    If Check44.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_3, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_3, 0)
    End If
End Sub

Private Sub Check45_Click()
    If Check45.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_4, 0)
    End If
End Sub

Private Sub Check46_Click()
    If Check46.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_5, 0)
    End If
End Sub

Private Sub Check47_Click()
    If Check47.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_6, 0)
    End If
End Sub

Private Sub Check48_Click()
    If Check48.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTF, BIT_7, 0)
    End If
End Sub

Private Sub Check5_Click()
    If Check5.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_4, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_4, 0)
    End If
End Sub

Private Sub Check6_Click()
    If Check6.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_5, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_5, 0)
    End If
End Sub

Private Sub Check7_Click()
    If Check7.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_6, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_6, 0)
    End If
End Sub

Private Sub Check8_Click()
    If Check8.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_7, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTA, BIT_7, 0)
    End If
End Sub

Private Sub Check9_Click()
    If Check9.Value = 1 Then
        retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_0, 1)
    Else: retval = me1400DOSetBit(Boardnumber, ME1400_PORTB, BIT_0, 0)
    End If
End Sub

Private Sub Command1_Click()
    retval = me1400ResetBoard(Boardnumber)
    retval = me1400InitBoard(Boardnumber)
    Unload Form4
End Sub
