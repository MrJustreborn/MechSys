VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "DOSetByte"
   ClientHeight    =   4605
   ClientLeft      =   2850
   ClientTop       =   1995
   ClientWidth     =   7545
   LinkTopic       =   "Form5"
   ScaleHeight     =   4605
   ScaleWidth      =   7545
   Begin VB.CommandButton Command3 
      Caption         =   "Reset"
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
      Left            =   360
      TabIndex        =   13
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
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
      Left            =   360
      TabIndex        =   11
      Top             =   3720
      Width           =   1215
   End
   Begin VB.OptionButton Option6 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   8
      Top             =   3480
      Width           =   975
   End
   Begin VB.OptionButton Option5 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   7
      Top             =   3120
      Width           =   975
   End
   Begin VB.OptionButton Option4 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   6
      Top             =   2760
      Width           =   975
   End
   Begin VB.OptionButton Option3 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   5
      Top             =   1560
      Width           =   975
   End
   Begin VB.OptionButton Option2 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   4
      Top             =   1200
      Width           =   975
   End
   Begin VB.OptionButton Option1 
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
      Height          =   375
      Left            =   4440
      TabIndex        =   3
      Top             =   840
      Value           =   -1  'True
      Width           =   975
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port Selection"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3735
      Left            =   4200
      TabIndex        =   2
      Top             =   480
      Width           =   3015
      Begin VB.Label Label2 
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
         Left            =   1320
         TabIndex        =   10
         Top             =   2640
         Width           =   1455
      End
      Begin VB.Label Label1 
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
         Height          =   255
         Left            =   1440
         TabIndex        =   9
         Top             =   840
         Width           =   1335
      End
   End
   Begin VB.TextBox Text1 
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
      Left            =   1920
      TabIndex        =   1
      Text            =   "0"
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "SetByte"
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
      Left            =   360
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "0....FF"
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
      Left            =   1920
      TabIndex        =   12
      Top             =   1080
      Width           =   1215
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()

    If Option1.Value = True Then Port_x = ME1400_PORTA
    If Option2.Value = True Then Port_x = ME1400_PORTB
    If Option3.Value = True Then Port_x = ME1400_PORTC
    If Option4.Value = True Then Port_x = ME1400_PORTD
    If Option5.Value = True Then Port_x = ME1400_PORTE
    If Option6.Value = True Then Port_x = ME1400_PORTF
    
    tt = Text1.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1400DOSetByte(Boardnumber, Port_x, val_32)

If retval = 0 Then
         Call me1400GetDrvErrMess(errtext)
        MsgBox "ME1400 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command2_Click()
    retval = me1400ResetBoard(Boardnumber)
    retval = me1400InitBoard(Boardnumber)
    Unload Form5
End Sub

Private Sub Command3_Click()
   If Option1.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTA, 0)
    ElseIf Option2.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTB, 0)
    ElseIf Option3.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTC, 0)
    ElseIf Option4.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTD, 0)
    ElseIf Option5.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTE, 0)
    ElseIf Option6.Value = True Then
        retval = me1400DOSetByte(Boardnumber, ME1400_PORTF, 0)
    End If
End Sub

