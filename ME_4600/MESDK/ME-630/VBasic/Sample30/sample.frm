VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6930
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10935
   LinkTopic       =   "Form1"
   ScaleHeight     =   6930
   ScaleWidth      =   10935
   StartUpPosition =   3  'Windows-Standard
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   6000
      TabIndex        =   10
      Top             =   2760
      Width           =   1455
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   4200
      TabIndex        =   9
      Text            =   "0"
      Top             =   2760
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2520
      TabIndex        =   8
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   600
      TabIndex        =   7
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Get Relay Word"
      Height          =   495
      Left            =   6000
      TabIndex        =   6
      Top             =   1680
      Width           =   1455
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Set Relay-Word"
      Height          =   495
      Left            =   4200
      TabIndex        =   5
      Top             =   1680
      Width           =   1455
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Get Opto-Byte"
      Height          =   495
      Left            =   2520
      TabIndex        =   4
      Top             =   1680
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Get TTL-Byte"
      Height          =   495
      Left            =   600
      TabIndex        =   3
      Top             =   1680
      Width           =   1215
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   8160
      TabIndex        =   2
      Top             =   5760
      Width           =   1815
   End
   Begin VB.CommandButton cmdReset 
      Caption         =   "Reset Relays"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   8160
      TabIndex        =   1
      Top             =   1680
      Width           =   1815
   End
   Begin VB.Label Label2 
      Caption         =   "Output Value"
      Height          =   255
      Left            =   4200
      TabIndex        =   11
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "ME-630  Set-Get Relay Bit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1080
      TabIndex        =   0
      Top             =   240
      Width           =   8655
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Boardnumber As Long
Dim retval As Long

Dim Set_Relay_Value As Integer
Dim TTL_Value As Integer
Dim Opto_Value As Integer
Dim Relay_Value As Integer

Private Sub cmdExit_Click()
    retval = me630ResetRelays(Boardnumber)
    End
End Sub

Private Sub cmdReset_Click()
        retval = me630ResetRelays(Boardnumber)
End Sub

Private Sub Command1_Click()
    retval = me630DIGetTTLByte(Boardnumber, TTL_Value)
    Text1.Text = "Value  :    " & TTL_Value
End Sub

Private Sub Command2_Click()
    retval = me630DIGetOptoByte(Boardnumber, Opto_Value)
    Text2.Text = "Value  :    " & Opto_Value
End Sub

Private Sub Command3_Click()
    Set_Relay_Value = Text3.Text
    retval = me630DOSetRelayWord(Boardnumber, Set_Relay_Value)
End Sub

Private Sub Command4_Click()
    retval = me630DIGetRelayWord(Boardnumber, Relay_Value)
    Text4.Text = "Value  :    " & Relay_Value
End Sub

