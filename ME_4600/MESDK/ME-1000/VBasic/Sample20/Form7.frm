VERSION 5.00
Begin VB.Form Form7 
   Caption         =   "DOSetByte"
   ClientHeight    =   6150
   ClientLeft      =   3645
   ClientTop       =   3180
   ClientWidth     =   8580
   LinkTopic       =   "Form7"
   ScaleHeight     =   6150
   ScaleWidth      =   8580
   Begin VB.CommandButton Command6 
      Caption         =   "Reset"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   3720
      TabIndex        =   14
      Top             =   4920
      Width           =   1695
   End
   Begin VB.CommandButton Command5 
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
      Height          =   735
      Left            =   5880
      TabIndex        =   13
      Top             =   4920
      Width           =   1695
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Byte_3"
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
      Left            =   960
      TabIndex        =   12
      Top             =   4200
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Byte_2"
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
      Left            =   960
      TabIndex        =   11
      Top             =   3480
      Width           =   1335
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Byte_1"
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
      Left            =   960
      TabIndex        =   10
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Byte_0"
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
      Left            =   960
      TabIndex        =   9
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Frame Frame1 
      Caption         =   "Port select"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2535
      Left            =   5880
      TabIndex        =   4
      Top             =   2040
      Width           =   1695
      Begin VB.OptionButton Option4 
         Caption         =   "Port D"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   8
         Top             =   1920
         Width           =   1095
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Port C"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   7
         Top             =   1440
         Width           =   1095
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Port B"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   6
         Top             =   960
         Width           =   975
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Port A"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   5
         Top             =   480
         Value           =   -1  'True
         Width           =   1095
      End
   End
   Begin VB.TextBox Text4 
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
      Left            =   2760
      TabIndex        =   3
      Text            =   "0"
      Top             =   4200
      Width           =   615
   End
   Begin VB.TextBox Text3 
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
      Left            =   2760
      TabIndex        =   2
      Text            =   "0"
      Top             =   3480
      Width           =   615
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
      Left            =   2760
      TabIndex        =   1
      Text            =   "0"
      Top             =   2760
      Width           =   615
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
      Left            =   2760
      TabIndex        =   0
      Text            =   "0"
      Top             =   2040
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "0....FF"
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
      Left            =   2760
      TabIndex        =   15
      Top             =   1800
      Width           =   855
   End
End
Attribute VB_Name = "Form7"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
        
    tt = Text1.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetByte(Boardnumber, Port_X, 0, val_32)

If retval = 0 Then
         Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command2_Click()

  
    tt = Text2.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetByte(Boardnumber, Port_X, 1, val_32)

If retval = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command3_Click()
 
    tt = Text3.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetByte(Boardnumber, Port_X, 2, val_32)

If retval = 0 Then
         Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command4_Click()

    tt = Text4.Text
    a = "&H" & tt
    val_32 = CLng(a)
    retval = me1000DOSetByte(Boardnumber, Port_X, 3, val_32)

If retval = 0 Then
       Call me1000GetDrvErrMess(errtext, 128)
        MsgBox "ME1000 error: " + errtext, vbInformation
    Else
    End If
End Sub

Private Sub Command5_Click()
Form7.Hide
Unload Form7
End Sub

Private Sub Command6_Click()
    If Option1.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option2.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option3.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    ElseIf Option4.Value = True Then
        retval = me1000DOSetLong(Boardnumber, Port_X, 0)
    End If
End Sub

Private Sub Option1_Click()
If Option1.Value = True Then Port_X = PORTA
End Sub

Private Sub Option2_Click()
If Option2.Value = True Then Port_X = PORTB
End Sub

Private Sub Option3_Click()
If Option3.Value = True Then Port_X = PORTC
End Sub

Private Sub Option4_Click()
If Option4.Value = True Then Port_X = PORTD
End Sub

