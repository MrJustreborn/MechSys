VERSION 5.00
Begin VB.Form Form6 
   Caption         =   "CntInitSrc"
   ClientHeight    =   3705
   ClientLeft      =   4455
   ClientTop       =   3180
   ClientWidth     =   5400
   LinkTopic       =   "Form6"
   ScaleHeight     =   3705
   ScaleWidth      =   5400
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
      Left            =   1320
      TabIndex        =   9
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
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
      Left            =   1320
      TabIndex        =   8
      Top             =   1800
      Width           =   1215
   End
   Begin VB.OptionButton Option4 
      Caption         =   "PREV"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3240
      TabIndex        =   5
      Top             =   2640
      Width           =   1215
   End
   Begin VB.OptionButton Option3 
      Caption         =   "10 MHZ"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3240
      TabIndex        =   4
      Top             =   2160
      Width           =   1215
   End
   Begin VB.OptionButton Option2 
      Caption         =   "1 MHZ"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3240
      TabIndex        =   3
      Top             =   1680
      Width           =   1215
   End
   Begin VB.OptionButton Option1 
      Caption         =   "SUBD"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3240
      TabIndex        =   2
      Top             =   1200
      Value           =   -1  'True
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "CounterSource"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2535
      Left            =   3120
      TabIndex        =   1
      Top             =   840
      Width           =   1935
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
      Left            =   1320
      TabIndex        =   0
      Text            =   "0"
      Top             =   1080
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Counter ?"
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
      Left            =   360
      TabIndex        =   7
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "0....29"
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
      TabIndex        =   6
      Top             =   840
      Width           =   975
   End
End
Attribute VB_Name = "Form6"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    
    If Option1.Value = True Then CounterSource = COUNTER_SOURCE_SUBD
    If Option2.Value = True Then CounterSource = COUNTER_SOURCE_1MHZ
    If Option3.Value = True Then CounterSource = COUNTER_SOURCE_10MHZ
    If Option4.Value = True Then CounterSource = COUNTER_SOURCE_PREV
    
    Counter = Text1
    
    If me1400CntInitSrc(Boardnumber, Counter, CounterSource) = 0 Then
    Call me1400GetDrvErrMess(errortext)
    MsgBox ("Error" & errortext)
    End If
    Unload Form6
End Sub

Private Sub Command2_Click()
    Unload Form6
End Sub


