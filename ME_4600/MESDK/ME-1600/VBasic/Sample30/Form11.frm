VERSION 5.00
Begin VB.Form Form11 
   Caption         =   "AOUpdate"
   ClientHeight    =   3135
   ClientLeft      =   5640
   ClientTop       =   3975
   ClientWidth     =   4680
   LinkTopic       =   "Form11"
   ScaleHeight     =   3135
   ScaleWidth      =   4680
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
      Left            =   3000
      TabIndex        =   6
      Top             =   960
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
      Left            =   3000
      TabIndex        =   5
      Top             =   1920
      Width           =   1215
   End
   Begin VB.OptionButton Option4 
      Caption         =   "ChannelGroup D"
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
      TabIndex        =   4
      Top             =   2280
      Width           =   1815
   End
   Begin VB.OptionButton Option3 
      Caption         =   "ChannelGroup C"
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
      TabIndex        =   3
      Top             =   1800
      Width           =   1815
   End
   Begin VB.OptionButton Option2 
      Caption         =   "ChannelGroup B"
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
      Top             =   1320
      Width           =   1815
   End
   Begin VB.Frame Frame1 
      Caption         =   "Setting"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2415
      Left            =   600
      TabIndex        =   0
      Top             =   480
      Width           =   2175
      Begin VB.OptionButton Option1 
         Caption         =   "ChannelGroup A"
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
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   1815
      End
   End
End
Attribute VB_Name = "Form11"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  retval = me1600AOUpdate(Boardnumber, iChannelGroup)

If retval = 0 Then
         Call me1600GetDrvErrMess(errtext, 128)
        MsgBox "ME1600 error: " + errtext, vbInformation
    Else
    End If
    Unload Form11
End Sub

Private Sub Command2_Click()
    Unload Form11
End Sub

Private Sub Option1_Click()
    If Option1.Value = True Then iChannelGroup = AO1600_GROUP_A
End Sub

Private Sub Option2_Click()
    If Option1.Value = True Then iChannelGroup = AO1600_GROUP_B
End Sub

Private Sub Option3_Click()
    If Option1.Value = True Then iChannelGroup = AO1600_GROUP_C
End Sub

Private Sub Option4_Click()
    If Option1.Value = True Then iChannelGroup = AO1600_GROUP_D
End Sub
