VERSION 5.00
Begin VB.Form Mux_Config 
   Caption         =   "Mux-Config"
   ClientHeight    =   4695
   ClientLeft      =   4605
   ClientTop       =   2805
   ClientWidth     =   7665
   LinkTopic       =   "Form1"
   ScaleHeight     =   4695
   ScaleWidth      =   7665
   Begin VB.CommandButton Command3 
      Caption         =   "Exit"
      Height          =   495
      Left            =   5880
      TabIndex        =   18
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Reset all"
      Height          =   495
      Left            =   5880
      TabIndex        =   17
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Set"
      Height          =   495
      Left            =   5880
      TabIndex        =   16
      Top             =   600
      Width           =   1215
   End
   Begin VB.Frame Frame3 
      Caption         =   "KanalGruppe"
      Height          =   1695
      Left            =   240
      TabIndex        =   13
      Top             =   480
      Width           =   1455
      Begin VB.OptionButton Option13 
         Caption         =   "B"
         Height          =   375
         Left            =   240
         TabIndex        =   15
         Top             =   840
         Width           =   855
      End
      Begin VB.OptionButton Option12 
         Caption         =   "A"
         Height          =   375
         Left            =   240
         TabIndex        =   14
         Top             =   360
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Adress"
      Height          =   3975
      Left            =   2040
      TabIndex        =   1
      Top             =   480
      Width           =   1455
      Begin VB.OptionButton Option11 
         Caption         =   "Slave_7"
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   2760
         Width           =   1215
      End
      Begin VB.OptionButton Option10 
         Caption         =   "Slave_6"
         Height          =   375
         Left            =   120
         TabIndex        =   11
         Top             =   2400
         Width           =   1215
      End
      Begin VB.OptionButton Option9 
         Caption         =   "Slave_5"
         Height          =   375
         Left            =   120
         TabIndex        =   10
         Top             =   2040
         Width           =   1215
      End
      Begin VB.OptionButton Option8 
         Caption         =   "Slave_4"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   1680
         Width           =   1215
      End
      Begin VB.OptionButton Option7 
         Caption         =   "Slave_3"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   1320
         Width           =   1215
      End
      Begin VB.OptionButton Option6 
         Caption         =   "Slave_2"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   960
         Width           =   1215
      End
      Begin VB.OptionButton Option5 
         Caption         =   "Slave_1"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   600
         Width           =   1215
      End
      Begin VB.OptionButton Option4 
         Caption         =   "Master"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Verstärkung"
      Height          =   2295
      Left            =   3840
      TabIndex        =   0
      Top             =   480
      Width           =   1455
      Begin VB.OptionButton Option3 
         Caption         =   "V=100"
         Height          =   495
         Left            =   120
         TabIndex        =   4
         Top             =   1560
         Width           =   1215
      End
      Begin VB.OptionButton Option2 
         Caption         =   "V=10"
         Height          =   495
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   1215
      End
      Begin VB.OptionButton Option1 
         Caption         =   "V=1"
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
End
Attribute VB_Name = "Mux_Config"
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
    If Option1.Value = True Then V = &H0
    If Option2.Value = True Then V = &H200
    If Option3.Value = True Then V = &H400
    If Option4.Value = True Then Adress = &H0
    If Option5.Value = True Then Adress = &H2
    If Option6.Value = True Then Adress = &H4
    If Option7.Value = True Then Adress = &H6
    If Option8.Value = True Then Adress = &H8
    If Option9.Value = True Then Adress = &HA
    If Option10.Value = True Then Adress = &HC
    If Option11.Value = True Then Adress = &HE
    If Option12.Value = True Then Grupp = 1
    If Option13.Value = True Then Grupp = 0
    
    Value_0 = V + Adress + Grupp + &H800 + &H100
    Value_1 = Value_0 - &H100
    Value_2 = &H800 + Grupp + Adress + &H100
    Error = me2600DIOSetPortDirection(0, PORTA, 1)
    Error = me2600DOSetWord(0, PORTA, Value_0)
    Error = me2600DOSetWord(0, PORTA, Value_1)
    MsgBox "Konfiguration ok", vbOKCancel
    Error = me2600DOSetWord(0, PORTA, Value_2)

End Sub

Private Sub Command2_Click()
    Error = me2600DIOSetPortDirection(0, PORTA, 1)
    Error = me2600DOSetWord(0, PORTA, 0)
End Sub

Private Sub Command3_Click()
    Mux_Config.Hide
    Unload Mux_Config
End Sub


