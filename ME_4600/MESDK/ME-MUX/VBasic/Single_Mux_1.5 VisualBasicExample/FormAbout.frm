VERSION 5.00
Begin VB.Form FormAbout 
   Caption         =   "About This Program"
   ClientHeight    =   2970
   ClientLeft      =   6240
   ClientTop       =   4185
   ClientWidth     =   3900
   LinkTopic       =   "Form2"
   ScaleHeight     =   2970
   ScaleWidth      =   3900
   Begin VB.CommandButton AboutWindowOK 
      Caption         =   "OK"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   372
      Left            =   1164
      TabIndex        =   3
      Top             =   2400
      Width           =   1572
   End
   Begin VB.Label Label4 
      Caption         =   "Developed with Visual Basic 6.0"
      Height          =   252
      Left            =   600
      TabIndex        =   4
      Top             =   1080
      Width           =   2772
   End
   Begin VB.Label Label3 
      Caption         =   "ME-Mux Test Application Version 1.0"
      Height          =   492
      Left            =   600
      TabIndex        =   2
      Top             =   240
      Width           =   2892
   End
   Begin VB.Label Label2 
      Caption         =   "Copyright (C)  Dezember 2002"
      Height          =   252
      Left            =   600
      TabIndex        =   1
      Top             =   720
      Width           =   2412
   End
   Begin VB.Label Label1 
      Caption         =   "Meilhaus Electronic GmbH Fischerstraﬂe 4            82178 Puchheim"
      Height          =   612
      Left            =   600
      TabIndex        =   0
      Top             =   1560
      Width           =   1932
   End
End
Attribute VB_Name = "FormAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub AboutWindowOK_Click()
    FormAbout.Hide
    Unload FormAbout
End Sub
