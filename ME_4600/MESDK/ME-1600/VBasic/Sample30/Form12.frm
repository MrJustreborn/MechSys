VERSION 5.00
Begin VB.Form Form12 
   Caption         =   "AOUpdateAll"
   ClientHeight    =   2310
   ClientLeft      =   6840
   ClientTop       =   4185
   ClientWidth     =   2145
   LinkTopic       =   "Form12"
   ScaleHeight     =   2310
   ScaleWidth      =   2145
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
      Left            =   480
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "UpdateAll"
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
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
End
Attribute VB_Name = "Form12"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    retval = me1600AOUpdateAll(Boardnumber)
    
    If retval = 0 Then
         Call me1600GetDrvErrMess(errtext, 128)
        MsgBox "ME1600 error: " + errtext, vbInformation
    Else
    End If
    Unload Form12
End Sub

Private Sub Command2_Click()
    Unload Form12
End Sub
