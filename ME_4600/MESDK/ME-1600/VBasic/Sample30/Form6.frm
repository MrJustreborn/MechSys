VERSION 5.00
Begin VB.Form Form6 
   Caption         =   "Range"
   ClientHeight    =   2895
   ClientLeft      =   5040
   ClientTop       =   3585
   ClientWidth     =   4710
   LinkTopic       =   "Form6"
   ScaleHeight     =   2895
   ScaleWidth      =   4710
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
      TabIndex        =   4
      Top             =   720
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
      TabIndex        =   3
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Range Setting"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   600
      TabIndex        =   0
      Top             =   240
      Width           =   1815
      Begin VB.OptionButton Option2 
         Caption         =   "Bipolar +/-10V"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   240
         TabIndex        =   2
         Top             =   1200
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Unipolar   0-10V"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   240
         TabIndex        =   1
         Top             =   480
         Width           =   1095
      End
   End
End
Attribute VB_Name = "Form6"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    If Option1.Value = True Then
        iRange = AO1600_UNIPOLAR
    End If
    If Option2.Value = True Then
        iRange = AO1600_BIPOLAR
    End If
    
        retval = me1600AOSetRange(Boardnumber, iChannelNumber, iRange)

    If retval = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
        MsgBox "ME1600 error: " + errtext, vbInformation
    Else
    End If
      Unload Form6
      Unload Form5
End Sub

Private Sub Command2_Click()
    Unload Form6
End Sub

