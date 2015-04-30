VERSION 5.00
Begin VB.Form Single_Mux 
   Caption         =   "Single-Mux"
   ClientHeight    =   7545
   ClientLeft      =   2715
   ClientTop       =   1665
   ClientWidth     =   10845
   LinkTopic       =   "Form1"
   ScaleHeight     =   7545
   ScaleWidth      =   10845
   Begin VB.PictureBox Picture1 
      Height          =   6375
      Left            =   4680
      ScaleHeight     =   6315
      ScaleWidth      =   3555
      TabIndex        =   10
      Top             =   720
      Width           =   3615
   End
   Begin VB.Frame Frame1 
      Caption         =   "Auswahl Modul"
      Height          =   6495
      Left            =   960
      TabIndex        =   2
      Top             =   600
      Width           =   2775
      Begin VB.OptionButton Option16 
         Caption         =   "Slave_7_B"
         Height          =   375
         Left            =   120
         TabIndex        =   19
         Top             =   5760
         Width           =   1215
      End
      Begin VB.OptionButton Option15 
         Caption         =   "Slave_7_A"
         Height          =   375
         Left            =   120
         TabIndex        =   18
         Top             =   5400
         Width           =   1215
      End
      Begin VB.OptionButton Option14 
         Caption         =   "Slave_6_B"
         Height          =   375
         Left            =   120
         TabIndex        =   17
         Top             =   5040
         Width           =   1215
      End
      Begin VB.OptionButton Option13 
         Caption         =   "Slave_6_A"
         Height          =   375
         Left            =   120
         TabIndex        =   16
         Top             =   4680
         Width           =   1215
      End
      Begin VB.OptionButton Option12 
         Caption         =   "Slave_5_B"
         Height          =   375
         Left            =   120
         TabIndex        =   15
         Top             =   4320
         Width           =   1215
      End
      Begin VB.OptionButton Option11 
         Caption         =   "Slave_5_A"
         Height          =   375
         Left            =   120
         TabIndex        =   14
         Top             =   3960
         Width           =   1215
      End
      Begin VB.OptionButton Option10 
         Caption         =   "Slave_4_B"
         Height          =   375
         Left            =   120
         TabIndex        =   13
         Top             =   3600
         Width           =   1215
      End
      Begin VB.OptionButton Option9 
         Caption         =   "Slave_4_A"
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   3240
         Width           =   1215
      End
      Begin VB.OptionButton Option8 
         Caption         =   "Slave_3_B"
         Height          =   375
         Left            =   120
         TabIndex        =   11
         Top             =   2880
         Width           =   1215
      End
      Begin VB.OptionButton Option7 
         Caption         =   "Slave_3_A"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   2520
         Width           =   1215
      End
      Begin VB.OptionButton Option6 
         Caption         =   "Slave_2_B"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   2160
         Width           =   1215
      End
      Begin VB.OptionButton Option5 
         Caption         =   "Slave_2_A"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   1800
         Width           =   1215
      End
      Begin VB.OptionButton Option4 
         Caption         =   "Slave_1_B"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   1440
         Width           =   1215
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Slave_1_A"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   1080
         Width           =   1215
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Master_B"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   720
         Width           =   1215
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Master_A"
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Single"
      Height          =   495
      Left            =   8760
      TabIndex        =   1
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      Height          =   495
      Left            =   8760
      TabIndex        =   0
      Top             =   5640
      Width           =   1215
   End
End
Attribute VB_Name = "Single_Mux"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Mux_C As Integer
Dim Error As Integer
Dim v_Value As Single


Private Sub Command1_Click()
    If Option1.Value = True Then Mux_C = &HF
    If Option2.Value = True Then Mux_C = &H1F
    If Option3.Value = True Then Mux_C = &H2F
    If Option4.Value = True Then Mux_C = &H3F
    If Option5.Value = True Then Mux_C = &H4F
    If Option6.Value = True Then Mux_C = &H5F
    If Option7.Value = True Then Mux_C = &H6F
    If Option8.Value = True Then Mux_C = &H7F
    If Option9.Value = True Then Mux_C = &H8F
    If Option10.Value = True Then Mux_C = &H9F
    If Option11.Value = True Then Mux_C = &HAF
    If Option12.Value = True Then Mux_C = &HBF
    If Option13.Value = True Then Mux_C = &HCF
    If Option14.Value = True Then Mux_C = &HDF
    If Option15.Value = True Then Mux_C = &HEF
    If Option16.Value = True Then Mux_C = &HFF
   
    Picture1.Cls
    Error = me2600DIOSetPortDirection(0, PORTA, 1)
    Mux_C_0 = Mux_C - &HF
    For i = Mux_C_0 To Mux_C
        Out = &H900 + i
        Error = me2600DOSetWord(0, PORTA, Out)
        Error = me2600AISingle(0, 0, AI2600 - Minus_10, Value)
        v_Value = (Value * ((20 / 4096)) - 10)
        Picture1.Print "Value" & i & Chr(9) & Chr(9) & Value & Chr(9) & Chr(9) & v_Value & " Volt" & (Chr(13) & Chr(10))
    Next
End Sub

Private Sub Command2_Click()
    Single_Mux.Hide
    Unload Single_Mux
End Sub



Private Sub Text1_Change()
        Text1.Text = "Value" & i & Chr(9) & Chr(9) & Value & (Chr(13) & Chr(10))

End Sub


