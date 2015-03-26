VERSION 5.00
Begin VB.Form frmDIO 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Digital I/O"
   ClientHeight    =   3990
   ClientLeft      =   2565
   ClientTop       =   1500
   ClientWidth     =   5445
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3990
   ScaleWidth      =   5445
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox Value1 
      Alignment       =   2  'Center
      Height          =   372
      Left            =   2160
      TabIndex        =   51
      Top             =   960
      Width           =   1100
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "&Update"
      Default         =   -1  'True
      Height          =   372
      Left            =   120
      TabIndex        =   46
      Top             =   3480
      Width           =   3612
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port A Is Input"
      Height          =   1548
      Left            =   120
      TabIndex        =   27
      Top             =   120
      Width           =   5172
      Begin VB.OptionButton Option1 
         Caption         =   "LByte"
         Height          =   300
         Index           =   2
         Left            =   4200
         TabIndex        =   54
         Top             =   1200
         Width           =   700
      End
      Begin VB.OptionButton Option1 
         Caption         =   "HByte"
         Height          =   300
         Index           =   1
         Left            =   3120
         TabIndex        =   53
         Top             =   1200
         Width           =   700
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Word"
         Height          =   300
         Index           =   0
         Left            =   2040
         TabIndex        =   52
         Top             =   1200
         Value           =   -1  'True
         Width           =   700
      End
      Begin VB.CheckBox CheckPortAOutput 
         Caption         =   "Port A is Output"
         Height          =   252
         Left            =   360
         TabIndex        =   48
         Top             =   1200
         Width           =   1332
      End
      Begin VB.CheckBox CheckPortAInput 
         Caption         =   "Port A is Input"
         Height          =   252
         Left            =   360
         TabIndex        =   47
         Top             =   960
         Value           =   1  'Checked
         Width           =   1332
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   0
         Left            =   4680
         TabIndex        =   43
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   1
         Left            =   4440
         TabIndex        =   42
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   2
         Left            =   4200
         TabIndex        =   41
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   3
         Left            =   3960
         TabIndex        =   40
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   4
         Left            =   3480
         TabIndex        =   39
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   5
         Left            =   3240
         TabIndex        =   38
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   6
         Left            =   3000
         TabIndex        =   37
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   7
         Left            =   2760
         TabIndex        =   36
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   8
         Left            =   2280
         TabIndex        =   35
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   9
         Left            =   2040
         TabIndex        =   34
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   10
         Left            =   1800
         TabIndex        =   33
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   11
         Left            =   1560
         TabIndex        =   32
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   12
         Left            =   1080
         TabIndex        =   31
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   13
         Left            =   840
         TabIndex        =   30
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   14
         Left            =   600
         TabIndex        =   29
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   15
         Left            =   360
         TabIndex        =   28
         Top             =   480
         Width           =   175
      End
      Begin VB.Label Label1 
         Caption         =   "0"
         Height          =   252
         Index           =   0
         Left            =   4800
         TabIndex        =   45
         Top             =   300
         Width           =   132
      End
      Begin VB.Label Label1 
         Caption         =   "15"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   44
         Top             =   300
         Width           =   252
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Port B Is Output"
      Height          =   1548
      Left            =   120
      TabIndex        =   7
      Top             =   1800
      Width           =   5172
      Begin VB.OptionButton Option2 
         Caption         =   "HByte"
         Height          =   300
         Index           =   1
         Left            =   3120
         TabIndex        =   57
         Top             =   1200
         Width           =   700
      End
      Begin VB.OptionButton Option2 
         Caption         =   "LByte"
         Height          =   300
         Index           =   2
         Left            =   4200
         TabIndex        =   56
         Top             =   1200
         Width           =   700
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Word"
         Height          =   300
         Index           =   0
         Left            =   2040
         TabIndex        =   55
         Top             =   1200
         Value           =   -1  'True
         Width           =   700
      End
      Begin VB.CheckBox CheckPortBOutput 
         Caption         =   "Port B is Output"
         Height          =   252
         Left            =   360
         TabIndex        =   50
         Top             =   1200
         Width           =   1332
      End
      Begin VB.CheckBox CheckPortBInput 
         Caption         =   "Port B is Input"
         Height          =   252
         Left            =   360
         TabIndex        =   49
         Top             =   960
         Value           =   1  'Checked
         Width           =   1332
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   16
         Left            =   4680
         TabIndex        =   24
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   17
         Left            =   4440
         TabIndex        =   23
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   18
         Left            =   4200
         TabIndex        =   22
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   19
         Left            =   3960
         TabIndex        =   21
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   20
         Left            =   3480
         TabIndex        =   20
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   21
         Left            =   3240
         TabIndex        =   19
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   22
         Left            =   3000
         TabIndex        =   18
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   23
         Left            =   2760
         TabIndex        =   17
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   24
         Left            =   2280
         TabIndex        =   16
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   25
         Left            =   2040
         TabIndex        =   15
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   26
         Left            =   1800
         TabIndex        =   14
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   27
         Left            =   1560
         TabIndex        =   13
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   28
         Left            =   1080
         TabIndex        =   12
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   29
         Left            =   840
         TabIndex        =   11
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   30
         Left            =   600
         TabIndex        =   10
         Top             =   480
         Width           =   175
      End
      Begin VB.CheckBox Check1 
         Height          =   250
         Index           =   31
         Left            =   360
         TabIndex        =   9
         Top             =   480
         Width           =   175
      End
      Begin VB.TextBox Value2 
         Alignment       =   2  'Center
         Height          =   372
         Left            =   2040
         TabIndex        =   8
         Top             =   840
         Width           =   1100
      End
      Begin VB.Label Label1 
         Caption         =   "15"
         Height          =   252
         Index           =   2
         Left            =   240
         TabIndex        =   26
         Top             =   300
         Width           =   252
      End
      Begin VB.Label Label1 
         Caption         =   "0"
         Height          =   252
         Index           =   3
         Left            =   4800
         TabIndex        =   25
         Top             =   300
         Width           =   132
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   3
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   480
      Width           =   5685
      Begin VB.Frame fraBoard4 
         Caption         =   "Board 4"
         Height          =   1785
         Left            =   2100
         TabIndex        =   6
         Top             =   840
         Width           =   2055
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   2
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   480
      Width           =   5685
      Begin VB.Frame fraBoard3 
         Caption         =   "Board 3"
         Height          =   1785
         Left            =   1545
         TabIndex        =   5
         Top             =   675
         Width           =   2055
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   1
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   480
      Width           =   5685
      Begin VB.Frame fraBoard2 
         Caption         =   "Board 2"
         Height          =   1785
         Left            =   645
         TabIndex        =   4
         Top             =   300
         Width           =   2055
      End
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Close"
      Height          =   375
      Left            =   4200
      TabIndex        =   0
      Top             =   3480
      Width           =   1095
   End
End
Attribute VB_Name = "frmDIO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim giPortAIsOutput As Integer
Dim giPortBIsOutput As Integer



Private Sub Check1_Click(Index As Integer)
    Dim l As Long
    If Index <= 15 Then
        If giPortAIsOutput Then
            l = CLng(Index)
            If Check1(Index).Value = 1 Then
                If me3000DOSetBit(glBoardNumber, PORTA, l, 1&) = 0 Then
                    me3000ErrorMessage (AppName)
                    Exit Sub
                End If
            Else
                If me3000DOSetBit(glBoardNumber, PORTA, l, 0&) = 0 Then
                    me3000ErrorMessage (AppName)
                    Exit Sub
                End If
            End If
        End If
    Else
        If giPortBIsOutput Then
            l = CLng(Index - 16)
            If Check1(Index).Value = 1 Then
                If me3000DOSetBit(glBoardNumber, PORTB, l, 1&) = 0 Then
                    me3000ErrorMessage (AppName)
                    Exit Sub
                End If
            Else
                If me3000DOSetBit(glBoardNumber, PORTB, l, 0&) = 0 Then
                    me3000ErrorMessage (AppName)
                    Exit Sub
                End If
            End If
        End If
    End If
End Sub

Private Sub CheckPortAInput_Click()
    Dim l As Long
    
    If CheckPortAInput.Value = 1 Then
        CheckPortAOutput.Value = 0
        Frame1.Caption = "Port A is Input"
        
        giPortAIsOutput = False
        
        ' Set Port Direction to input
        '----------------------------------------------------
        If me3000DIOSetPortDirection(glBoardNumber, PORTA, MEINPUT) = 0 Then
            me3000ErrorMessage (AppName)
        End If
        
        For l = 0& To 15&
            Check1(l).Value = 0
            Check1(l).Enabled = False
        Next l
        
    End If
End Sub

Private Sub CheckPortAOutput_Click()
    Dim l As Long
    
    If CheckPortAOutput.Value = 1 Then
        CheckPortAInput.Value = 0
        Frame1.Caption = "Port A is Output"
        
        giPortAIsOutput = True
        
        ' Set Port Direction to output
        '----------------------------------------------------
        If me3000DIOSetPortDirection(glBoardNumber, PORTA, MEOUTPUT) = 0 Then
            me3000ErrorMessage (AppName)
        End If
        
        For l = 0& To 15&
            Check1(l).Value = 0
            Check1(l).Enabled = True
        Next l
        
    End If
End Sub

Private Sub CheckPortBInput_Click()
    Dim l As Long
    
    If CheckPortBInput.Value = 1 Then
        CheckPortBOutput.Value = 0
        Frame2.Caption = "Port B is Input"
        
        giPortBIsOutput = False
        
        ' Set Port Direction to output
        '----------------------------------------------------
        If me3000DIOSetPortDirection(glBoardNumber, PORTB, MEINPUT) = 0 Then
            me3000ErrorMessage (AppName)
        End If
        
        For l = 0& To 15&
            Check1(16 + l).Value = 0
            Check1(16 + l).Enabled = False
        Next l
        
    End If
End Sub

Private Sub CheckPortBOutput_Click()
    Dim l As Long
    
    If CheckPortBOutput.Value = 1 Then
        CheckPortBInput.Value = 0
        Frame2.Caption = "Port B is Output"
        
        giPortBIsOutput = True
        ' Set Port Direction to output
        '----------------------------------------------------
        If me3000DIOSetPortDirection(glBoardNumber, PORTB, MEOUTPUT) = 0 Then
            me3000ErrorMessage (AppName)
        End If
        For l = 0& To 15&
            Check1(16 + l).Value = 0
            Check1(16 + l).Enabled = True
        Next l
    End If
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub


Private Sub cmdUpdate_Click()
    Dim lValueA As Long
    Dim lValueB As Long
    Dim l As Long
        
    If Not giPortAIsOutput Then
        If Option1(0).Value Then
            If me3000DIGetWord(glBoardNumber, PORTA, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        ElseIf Option1(1).Value Then
            If me3000DIGetByte(glBoardNumber, PORTA, HIGH_BYTE, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        Else
            If me3000DIGetByte(glBoardNumber, PORTA, LOW_BYTE, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        End If
        Value1.Text = Hex(lValueA)
        
        For l = 0& To 15&
            If me3000DIGetBit(glBoardNumber, PORTA, l, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
            
            If lValueA = 1 Then
                Check1(l).Value = 1
            Else
                Check1(l).Value = 0
            End If
        Next l
    Else
        lValueA = Val("&h" + Trim(Value1.Text))
        If Option1(0).Value Then
            If me3000DOSetWord(glBoardNumber, PORTA, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        ElseIf Option1(1).Value Then
            If me3000DOSetByte(glBoardNumber, PORTA, HIGH_BYTE, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        Else
            If me3000DOSetByte(glBoardNumber, PORTA, LOW_BYTE, lValueA) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        End If
    End If
    

    If Not giPortBIsOutput Then
        If Option2(0).Value Then
            If me3000DIGetWord(glBoardNumber, PORTB, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        ElseIf Option2(1).Value Then
            If me3000DIGetByte(glBoardNumber, PORTB, HIGH_BYTE, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        Else
            If me3000DIGetByte(glBoardNumber, PORTB, LOW_BYTE, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        End If
        Value2.Text = Hex(lValueB)
        
        For l = 0& To 15&
            If me3000DIGetBit(glBoardNumber, PORTB, l, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
            
            If lValueB = 1 Then
                Check1(16 + l).Value = 1
            Else
                Check1(16 + l).Value = 0
            End If
        Next l
    Else
        lValueB = Val("&h" + Trim(Value2.Text))
        If Option2(0).Value Then
            If me3000DOSetWord(glBoardNumber, PORTB, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        ElseIf Option2(1).Value Then
            If me3000DOSetByte(glBoardNumber, PORTB, HIGH_BYTE, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        Else
            If me3000DOSetByte(glBoardNumber, PORTB, LOW_BYTE, lValueB) = 0 Then
                me3000ErrorMessage (AppName)
                Exit Sub
            End If
        End If
    End If

End Sub

Private Sub Form_Load()
    Dim i As Integer
    
    'center the form
    Me.Move (Screen.Width - Me.Width) / 2, (Screen.Height - Me.Height) / 2
    
    giPortAIsOutput = False
    giPortBIsOutput = False
    For i = 0 To 31
        Check1(i).Enabled = False
    Next i

End Sub

Private Sub Frame2_DragDrop(Source As Control, X As Single, Y As Single)

End Sub
