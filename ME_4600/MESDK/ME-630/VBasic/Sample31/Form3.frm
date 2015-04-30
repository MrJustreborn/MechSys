VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "SetGetWord"
   ClientHeight    =   3225
   ClientLeft      =   4650
   ClientTop       =   3975
   ClientWidth     =   5775
   LinkTopic       =   "Form3"
   ScaleHeight     =   3225
   ScaleWidth      =   5775
   Begin VB.CommandButton Command4 
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
      Left            =   4080
      TabIndex        =   6
      Top             =   2280
      Width           =   1215
   End
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
      Left            =   4080
      TabIndex        =   5
      Top             =   840
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Get-Word"
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
      Left            =   480
      TabIndex        =   3
      Top             =   2280
      Width           =   1215
   End
   Begin VB.TextBox Text2 
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
      TabIndex        =   2
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Set-Word"
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
      Left            =   480
      TabIndex        =   1
      Top             =   840
      Width           =   1215
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
      TabIndex        =   0
      Text            =   "0"
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "0.....FFFF"
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
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
 
    iWordValue = "&H" & Text1.Text
    iValue = CLng(iWordValue)
    retval = me630DOSetRelayWord(Boardnumber, iWordValue)

    If retval = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
        MsgBox "ME630 error: " + errtext, vbInformation
    
    Else
    End If
End Sub

Private Sub Command2_Click()
    retval = me630DIGetRelayWord(Boardnumber, iWordValue)
If retval = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
        MsgBox "ME630 error: " + errtext, vbInformation
    Else
     Text2 = Hex(iWordValue)
    End If
End Sub

Private Sub Command3_Click()
    retval = me630ResetRelays(Boardnumber)
End Sub

Private Sub Command4_Click()
    retval = me630ResetRelays(Boardnumber)
    Unload Form3
End Sub
