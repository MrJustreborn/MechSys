VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "Range"
   ClientHeight    =   2490
   ClientLeft      =   5640
   ClientTop       =   4185
   ClientWidth     =   3420
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form3"
   ScaleHeight     =   2490
   ScaleWidth      =   3420
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      Height          =   495
      Left            =   2040
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   495
      Left            =   2040
      TabIndex        =   3
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Range"
      Height          =   1695
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   1455
      Begin VB.OptionButton Option2 
         Caption         =   "4....20mA"
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
         Left            =   120
         TabIndex        =   2
         Top             =   960
         Width           =   1215
      End
      Begin VB.OptionButton Option1 
         Caption         =   "0....20mA"
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
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Load Form4
    Form4.Show
End Sub

Private Sub Command2_Click()
    Unload Form3
End Sub

Private Sub Option1_Click()
    If Option1.Value = True Then
       iRange = &H0
    Else
    End If
End Sub

Private Sub Option2_Click()
    If Option2.Value = True Then
        iRange = &H1
    Else
    End If
End Sub
