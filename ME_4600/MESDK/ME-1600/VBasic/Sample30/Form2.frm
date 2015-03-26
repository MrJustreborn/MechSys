VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "AOSetCurrent"
   ClientHeight    =   2490
   ClientLeft      =   5040
   ClientTop       =   4500
   ClientWidth     =   5310
   LinkTopic       =   "Form2"
   ScaleHeight     =   2490
   ScaleWidth      =   5310
   Begin VB.Menu ChannelSettings 
      Caption         =   "Channel Settings"
      Begin VB.Menu mnuChannel0 
         Caption         =   "Channel_0"
      End
      Begin VB.Menu mnuChannel1 
         Caption         =   "Channel_1"
      End
      Begin VB.Menu mnuChannel2 
         Caption         =   "Channel_2"
      End
      Begin VB.Menu mnuChannel3 
         Caption         =   "Channel_3"
      End
      Begin VB.Menu mnuChannel4 
         Caption         =   "Channel_4"
      End
      Begin VB.Menu mnuChannel5 
         Caption         =   "Channel_5"
      End
      Begin VB.Menu mnuChannel6 
         Caption         =   "Channel_6"
      End
      Begin VB.Menu mnuChannel7 
         Caption         =   "Channel_7"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub mnuChannel0_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH00
End Sub

Private Sub mnuChannel1_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH01
End Sub

Private Sub mnuChannel2_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH02
End Sub

Private Sub mnuChannel3_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH03
End Sub

Private Sub mnuChannel4_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH04
End Sub

Private Sub mnuChannel5_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH05
End Sub

Private Sub mnuChannel6_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH06
End Sub

Private Sub mnuChannel7_Click()
    Load Form3
    Form3.Show
    iChannelNumber = AO1600_CH07
End Sub

Private Sub mnuExit_Click()
    Unload Form2
End Sub
