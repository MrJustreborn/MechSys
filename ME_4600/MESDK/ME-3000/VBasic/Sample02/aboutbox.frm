VERSION 5.00
Begin VB.Form frmAboutBox 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About ..."
   ClientHeight    =   2280
   ClientLeft      =   1740
   ClientTop       =   2400
   ClientWidth     =   5055
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2280
   ScaleWidth      =   5055
   ShowInTaskbar   =   0   'False
   Begin VB.PictureBox picIcon 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      Height          =   495
      Index           =   1
      Left            =   480
      ScaleHeight     =   495
      ScaleWidth      =   480
      TabIndex        =   6
      Top             =   480
      Width           =   480
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   1800
      Width           =   975
   End
   Begin VB.PictureBox picIcon 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      Height          =   495
      Index           =   0
      Left            =   480
      ScaleHeight     =   495
      ScaleWidth      =   480
      TabIndex        =   0
      Top             =   480
      Width           =   480
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "(c) 1998 by Max Kormaier"
      Height          =   372
      Index           =   3
      Left            =   1320
      TabIndex        =   5
      Top             =   1296
      Width           =   2532
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Version 1.001"
      Height          =   216
      Index           =   2
      Left            =   1320
      TabIndex        =   4
      Top             =   816
      Width           =   2532
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "ME3000 Visual Basic Sample Application"
      Height          =   216
      Index           =   1
      Left            =   1200
      TabIndex        =   3
      Top             =   576
      Width           =   2892
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Meilhaus Electronic GmbH"
      Height          =   276
      Index           =   0
      Left            =   1320
      TabIndex        =   2
      Top             =   240
      Width           =   2532
   End
End
Attribute VB_Name = "frmAboutBox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Sub CenterMe(rfrm As Object)
  
    ' See an other CenterMe routine in the VisData example
    
    ' center it on the screen
    rfrm.Top = (Screen.Height - rfrm.Height) \ 2
    rfrm.Left = (Screen.Width - rfrm.Width) \ 2
  
End Sub

Private Sub Form_Load()
  picIcon(1).Visible = False
  CenterMe Me
End Sub

Private Sub cmdOK_Click()
  Dim l As Long
  
  picIcon(0).Visible = False
  picIcon(1).Visible = True

  Sleep (1000)
  Unload Me
End Sub

Private Sub cmdOK_KeyPress(KeyAscii As Integer)
  Unload Me
End Sub

