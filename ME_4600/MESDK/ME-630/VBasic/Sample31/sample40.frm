VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "Form1"
   ClientHeight    =   6930
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10935
   LinkTopic       =   "Form1"
   ScaleHeight     =   6930
   ScaleWidth      =   10935
   StartUpPosition =   3  'Windows-Standard
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   2400
      TabIndex        =   35
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CommandButton cmdExit 
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
      Height          =   1095
      Left            =   8160
      TabIndex        =   34
      Top             =   4320
      Width           =   1935
   End
   Begin VB.CommandButton cmdResetallRelays 
      Caption         =   "Reset all Relays"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   8160
      TabIndex        =   33
      Top             =   2880
      Width           =   1935
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   8160
      TabIndex        =   32
      Top             =   1440
      Width           =   1935
   End
   Begin VB.TextBox Text16 
      Height          =   495
      Left            =   5520
      TabIndex        =   31
      Top             =   6240
      Width           =   1215
   End
   Begin VB.TextBox Text15 
      Height          =   495
      Left            =   5520
      TabIndex        =   30
      Top             =   5520
      Width           =   1215
   End
   Begin VB.TextBox Text14 
      Height          =   495
      Left            =   5520
      TabIndex        =   29
      Top             =   4800
      Width           =   1215
   End
   Begin VB.TextBox Text13 
      Height          =   495
      Left            =   5520
      TabIndex        =   28
      Top             =   4080
      Width           =   1215
   End
   Begin VB.TextBox Text12 
      Height          =   495
      Left            =   5520
      TabIndex        =   27
      Top             =   3360
      Width           =   1215
   End
   Begin VB.TextBox Text11 
      Height          =   495
      Left            =   5520
      TabIndex        =   26
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox Text10 
      Height          =   495
      Left            =   5520
      TabIndex        =   25
      Top             =   1920
      Width           =   1215
   End
   Begin VB.TextBox Text9 
      Height          =   495
      Left            =   5520
      TabIndex        =   24
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CheckBox Check16 
      Caption         =   "Relay-Bit 15"
      Height          =   495
      Left            =   4200
      TabIndex        =   23
      Top             =   6240
      Width           =   1215
   End
   Begin VB.CheckBox Check15 
      Caption         =   "Relay-Bit 14"
      Height          =   495
      Left            =   4200
      TabIndex        =   22
      Top             =   5520
      Width           =   1215
   End
   Begin VB.CheckBox Check14 
      Caption         =   "Relay-Bit 13"
      Height          =   495
      Left            =   4200
      TabIndex        =   21
      Top             =   4800
      Width           =   1215
   End
   Begin VB.CheckBox Check13 
      Caption         =   "Relay-Bit 12"
      Height          =   495
      Left            =   4200
      TabIndex        =   20
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CheckBox Check12 
      Caption         =   "Relay-Bit 11"
      Height          =   495
      Left            =   4200
      TabIndex        =   19
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CheckBox Check11 
      Caption         =   "Relay-Bit 10"
      Height          =   495
      Left            =   4200
      TabIndex        =   18
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CheckBox Check10 
      Caption         =   "Relay-Bit 9"
      Height          =   495
      Left            =   4200
      TabIndex        =   17
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CheckBox Check9 
      Caption         =   "Relay-Bit 8"
      Height          =   495
      Left            =   4200
      TabIndex        =   16
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox Text8 
      Height          =   495
      Left            =   2400
      TabIndex        =   15
      Top             =   6240
      Width           =   1215
   End
   Begin VB.TextBox Text7 
      Height          =   495
      Left            =   2400
      TabIndex        =   14
      Top             =   5520
      Width           =   1215
   End
   Begin VB.TextBox Text6 
      Height          =   495
      Left            =   2400
      TabIndex        =   13
      Top             =   4800
      Width           =   1215
   End
   Begin VB.TextBox Text5 
      Height          =   495
      Left            =   2400
      TabIndex        =   12
      Top             =   4080
      Width           =   1215
   End
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   2400
      TabIndex        =   11
      Top             =   3360
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   2400
      TabIndex        =   10
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2400
      TabIndex        =   9
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CheckBox Check8 
      Caption         =   "Relay-Bit 7"
      Height          =   495
      Left            =   1080
      TabIndex        =   8
      Top             =   6240
      Width           =   1215
   End
   Begin VB.CheckBox Check7 
      Caption         =   "Relay-Bit 6"
      Height          =   495
      Left            =   1080
      TabIndex        =   7
      Top             =   5520
      Width           =   1215
   End
   Begin VB.CheckBox Check6 
      Caption         =   "Relay-Bit 5"
      Height          =   495
      Left            =   1080
      TabIndex        =   6
      Top             =   4800
      Width           =   1215
   End
   Begin VB.CheckBox Check5 
      Caption         =   "Relay-Bit 4"
      Height          =   495
      Left            =   1080
      TabIndex        =   5
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CheckBox Check4 
      Caption         =   "Relay-Bit 3"
      Height          =   495
      Left            =   1080
      TabIndex        =   4
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CheckBox Check3 
      Caption         =   "Relay-Bit 2"
      Height          =   495
      Left            =   1080
      TabIndex        =   3
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CheckBox Check2 
      Caption         =   "Relay-Bit 1"
      Height          =   495
      Left            =   1080
      TabIndex        =   2
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Relay-Bit 0"
      Height          =   495
      Left            =   1080
      TabIndex        =   1
      Top             =   1200
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "ME-630  Set-Get Relay Bit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1080
      TabIndex        =   0
      Top             =   240
      Width           =   8655
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Boardnumber As Long
Dim retval As Long

Dim Value_0 As Long
Dim Value_1 As Long
Dim Value_2 As Long
Dim Value_3 As Long
Dim Value_4 As Long
Dim Value_5 As Long
Dim Value_6 As Long
Dim Value_7 As Long
Dim Value_8 As Long
Dim Value_9 As Long
Dim Value_10 As Long
Dim Value_11 As Long
Dim Value_12 As Long
Dim Value_13 As Long
Dim Value_14 As Long
Dim Value_15 As Long



Private Sub Check1_Click()
    If Check1.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_0, 1)
    Text1.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_0, 0)
    Text1.Text = Visible
    End If
End Sub

Private Sub Check10_Click()
    If Check10.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_9, 1)
    Text10.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_9, 0)
    Text10.Text = Visible
    End If
End Sub

Private Sub Check11_Click()
    If Check11.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_10, 1)
    Text11.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_10, 0)
    Text11.Text = Visible
    End If
End Sub

Private Sub Check12_Click()
    If Check12.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_11, 1)
    Text12.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_11, 0)
    Text12.Text = Visible
    End If
End Sub

Private Sub Check13_Click()
    If Check13.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_12, 1)
    Text13.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_12, 0)
    Text13.Text = Visible
    End If
End Sub

Private Sub Check14_Click()
    If Check14.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_13, 1)
    Text14.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_13, 0)
    Text14.Text = Visible
    End If
End Sub

Private Sub Check15_Click()
    If Check15.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_14, 1)
    Text15.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_14, 0)
    Text15.Text = Visible
    End If
End Sub

Private Sub Check16_Click()
    If Check16.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_15, 1)
    Text16.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_15, 0)
    Text16.Text = Visible
    End If
End Sub

Private Sub Check2_Click()
    If Check2.Value = 1 Then
        retval = me630DOSetRelayBit(Boardnumber, BIT_1, 1)
        Text2.Text = Visible
        Else
        retval = me630DOSetRelayBit(Boardnumber, BIT_1, 0)
        Text2.Text = Visible
        End If
End Sub

Private Sub Check3_Click()
    If Check3.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_2, 1)
    Text3.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_2, 0)
    Text3.Text = Visible
    End If
End Sub

Private Sub Check4_Click()
    If Check4.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_3, 1)
    Text4.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_3, 0)
    Text4.Text = Visible
    End If
End Sub

Private Sub Check5_Click()
    If Check5.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_4, 1)
    Text5.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_4, 0)
    Text5.Text = Visible
    End If
End Sub

Private Sub Check6_Click()
    If Check6.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_5, 1)
    Text6.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_5, 0)
    Text6.Text = Visible
    End If
End Sub

Private Sub Check7_Click()
    If Check7.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_6, 1)
    Text7.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_6, 0)
    Text7.Text = Visible
    End If
End Sub

Private Sub Check8_Click()
    If Check8.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_7, 1)
    Text8.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_7, 0)
    Text8.Text = Visible
    End If
End Sub

Private Sub Check9_Click()
    If Check9.Value = 1 Then
    retval = me630DOSetRelayBit(Boardnumber, BIT_8, 1)
    Text9.Text = Visible
    Else
    retval = me630DOSetRelayBit(Boardnumber, BIT_8, 0)
    Text9.Text = Visible
    End If
End Sub

Private Sub cmdExit_Click()
    retval = me630ResetRelays(Boardnumber)
    End
End Sub

Private Sub cmdResetallRelays_Click()
    Boardnumber = 0
    retval = me630ResetRelays(Boardnumber)
    Text1.Text = Visible
    Text2.Text = Visible
    Text3.Text = Visible
    Text4.Text = Visible
    Text5.Text = Visible
    Text6.Text = Visible
    Text7.Text = Visible
    Text8.Text = Visible
    Text9.Text = Visible
    Text10.Text = Visible
    Text11.Text = Visible
    Text12.Text = Visible
    Text13.Text = Visible
    Text14.Text = Visible
    Text15.Text = Visible
    Text16.Text = Visible
    Check1.Value = 0
    Check2.Value = 0
    Check3.Value = 0
    Check4.Value = 0
    Check5.Value = 0
    Check6.Value = 0
    Check7.Value = 0
    Check8.Value = 0
    Check9.Value = 0
    Check10.Value = 0
    Check11.Value = 0
    Check12.Value = 0
    Check13.Value = 0
    Check14.Value = 0
    Check15.Value = 0
    Check16.Value = 0
    
End Sub


Private Sub cmdStart_Click()
    Text1.Text = Visible
    Text2.Text = Visible
    Text3.Text = Visible
    Text4.Text = Visible
    Text5.Text = Visible
    Text6.Text = Visible
    Text7.Text = Visible
    Text8.Text = Visible
    Text9.Text = Visible
    Text10.Text = Visible
    Text11.Text = Visible
    Text12.Text = Visible
    Text13.Text = Visible
    Text14.Text = Visible
    Text15.Text = Visible
    Text16.Text = Visible
End Sub

Private Sub Text1_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_0, Value_0)
    Text1.Text = "Value  :    " & Value_0
End Sub

Private Sub Text10_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_9, Value_9)
    Text10.Text = "Value  :    " & Value_9
End Sub

Private Sub Text11_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_10, Value_10)
    Text11.Text = "Value  :    " & Value_10
End Sub

Private Sub Text12_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_11, Value_11)
    Text12.Text = "Value  :    " & Value_11
End Sub

Private Sub Text13_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_12, Value_12)
    Text13.Text = "Value  :    " & Value_12
End Sub

Private Sub Text14_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_13, Value_13)
    Text14.Text = "Value  :    " & Value_13
End Sub

Private Sub Text15_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_14, Value_14)
    Text15.Text = "Value  :    " & Value_14
End Sub

Private Sub Text16_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_15, Value_15)
    Text16.Text = "Value  :    " & Value_15
End Sub

Private Sub Text2_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_1, Value_1)
    Text2.Text = "Value  :    " & Value_1
End Sub

Private Sub Text3_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_2, Value_2)
    Text3.Text = "Value  :    " & Value_2
End Sub

Private Sub Text4_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_3, Value_3)
    Text4.Text = "Value  :    " & Value_3
End Sub

Private Sub Text5_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_4, Value_4)
    Text5.Text = "Value  :    " & Value_4
End Sub

Private Sub Text6_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_5, Value_5)
    Text6.Text = "Value  :    " & Value_5
End Sub

Private Sub Text7_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_6, Value_6)
    Text7.Text = "Value  :    " & Value_6
End Sub

Private Sub Text8_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_7, Value_7)
    Text8.Text = "Value  :    " & Value_7
End Sub

Private Sub Text9_Change()
    retval = me630DIGetRelayBit(Boardnumber, BIT_8, Value_8)
    Text9.Text = "Value  :    " & Value_8
End Sub
