VERSION 5.00
Begin VB.Form Identify 
   Caption         =   "Identify"
   ClientHeight    =   4695
   ClientLeft      =   5745
   ClientTop       =   2805
   ClientWidth     =   5115
   LinkTopic       =   "Form1"
   ScaleHeight     =   4695
   ScaleWidth      =   5115
   Begin VB.CommandButton Command3 
      Caption         =   "Exit"
      Height          =   495
      Left            =   2880
      TabIndex        =   11
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Reset all"
      Height          =   495
      Left            =   2880
      TabIndex        =   10
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Set"
      Height          =   495
      Left            =   2880
      TabIndex        =   9
      Top             =   480
      Width           =   1215
   End
   Begin VB.Frame Frame2 
      Caption         =   "Adress"
      Height          =   3375
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   1455
      Begin VB.OptionButton Option11 
         Caption         =   "Slave_7"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   2760
         Width           =   1215
      End
      Begin VB.OptionButton Option10 
         Caption         =   "Slave_6"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   2400
         Width           =   1215
      End
      Begin VB.OptionButton Option9 
         Caption         =   "Slave_5"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   2040
         Width           =   1215
      End
      Begin VB.OptionButton Option8 
         Caption         =   "Slave_4"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   1680
         Width           =   1215
      End
      Begin VB.OptionButton Option7 
         Caption         =   "Slave_3"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   1320
         Width           =   1215
      End
      Begin VB.OptionButton Option6 
         Caption         =   "Slave_2"
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   1215
      End
      Begin VB.OptionButton Option5 
         Caption         =   "Slave_1"
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   1215
      End
      Begin VB.OptionButton Option4 
         Caption         =   "Master"
         Height          =   375
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Value           =   -1  'True
         Width           =   1215
      End
   End
End
Attribute VB_Name = "Identify"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Adress As Integer
Dim V As Integer
Dim Grupp As Integer
Dim Value_0 As Integer
Dim Value_1 As Integer
Dim Value_2 As Integer
Dim Error As Integer

Private Sub Command1_Click()

    If Option4.Value = True Then Adress = &H0
    If Option5.Value = True Then Adress = &H2
    If Option6.Value = True Then Adress = &H4
    If Option7.Value = True Then Adress = &H6
    If Option8.Value = True Then Adress = &H8
    If Option9.Value = True Then Adress = &HA
    If Option10.Value = True Then Adress = &HC
    If Option11.Value = True Then Adress = &HE
  
    
    Value_0 = &HF00 + Adress + &H1
    Value_1 = &HE00 + Adress + &H1
    Value_2 = &HF00 + Adress
    Value_3 = &HE00 + Adress
    Error = me2600DIOSetPortDirection(0, PORTA, 1)
    Error = me2600DOSetWord(0, PORTA, Value_0)
    Error = me2600DOSetWord(0, PORTA, Value_1)
    Error = me2600DOSetWord(0, PORTA, Value_0)
    MsgBox "Konfiguration ok", vbOKCancel
    Error = me2600DOSetWord(0, PORTA, Value_2)
    Error = me2600DOSetWord(0, PORTA, Value_3)
    Error = me2600DOSetWord(0, PORTA, Value_2)

End Sub

Private Sub Command2_Click()
    Error = me2600DOSetWord(0, PORTA, 0)
End Sub

Private Sub Command3_Click()
    Identify.Hide
    Unload Identify
End Sub




