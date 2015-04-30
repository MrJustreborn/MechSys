VERSION 5.00
Begin VB.Form Form10 
   Caption         =   "Value"
   ClientHeight    =   2040
   ClientLeft      =   6045
   ClientTop       =   4380
   ClientWidth     =   4080
   LinkTopic       =   "Form10"
   ScaleHeight     =   2040
   ScaleWidth      =   4080
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
      Left            =   2520
      TabIndex        =   4
      Top             =   360
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
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
      Left            =   2520
      TabIndex        =   3
      Top             =   1080
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
      Left            =   720
      TabIndex        =   0
      Text            =   "0"
      Top             =   1080
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "000.....FFF Hex."
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
      Left            =   720
      TabIndex        =   2
      Top             =   840
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Value "
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
      Left            =   720
      TabIndex        =   1
      Top             =   600
      Width           =   495
   End
End
Attribute VB_Name = "Form10"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  
    sValue = "&H" & Text1.Text
    iValue = CLng(sValue)
    retval = me1600AOSingle(Boardnumber, iChannelNumber, iValue)

If retval = 0 Then
         Call me1600GetDrvErrMess(errtext, 128)
        MsgBox "ME1600 error: " + errtext, vbInformation
    
    Else
    End If
    Unload Form10
    Unload Form9
End Sub

Private Sub Command2_Click()
    Unload Form10
End Sub

