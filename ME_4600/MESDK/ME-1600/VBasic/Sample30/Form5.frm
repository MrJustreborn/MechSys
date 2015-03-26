VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "AOSetRange"
   ClientHeight    =   1920
   ClientLeft      =   5250
   ClientTop       =   4500
   ClientWidth     =   4305
   LinkTopic       =   "Form5"
   ScaleHeight     =   1920
   ScaleWidth      =   4305
   Begin VB.Menu mnuChannelSettings 
      Caption         =   "Channel Settings"
      Begin VB.Menu mnu 
         Caption         =   "Current only 0....7"
      End
      Begin VB.Menu Trennlinie 
         Caption         =   "-"
      End
      Begin VB.Menu mnuChannel_0 
         Caption         =   "Channel_0"
      End
      Begin VB.Menu mnuChannel_1 
         Caption         =   "Channel_1"
      End
      Begin VB.Menu mnuChannel_2 
         Caption         =   "Channel_2"
      End
      Begin VB.Menu mnuChannel_3 
         Caption         =   "Channel_3"
      End
      Begin VB.Menu mnuChannel_4 
         Caption         =   "Channel_4"
      End
      Begin VB.Menu mnuChannel_5 
         Caption         =   "Channel_5"
      End
      Begin VB.Menu mnuChannel_6 
         Caption         =   "Channel_6"
      End
      Begin VB.Menu mnuChannel_7 
         Caption         =   "Channel_7"
      End
      Begin VB.Menu mnuChannel_8 
         Caption         =   "Channel_8"
      End
      Begin VB.Menu mnuChannel_9 
         Caption         =   "Channel_9"
      End
      Begin VB.Menu mnuChannel_10 
         Caption         =   "Channel_10"
      End
      Begin VB.Menu mnuChannel_11 
         Caption         =   "Channel_11"
      End
      Begin VB.Menu mnuChannel_12 
         Caption         =   "Channel_12"
      End
      Begin VB.Menu mnuChannel_13 
         Caption         =   "Channel_13"
      End
      Begin VB.Menu mnuChannel_14 
         Caption         =   "Channel_14"
      End
      Begin VB.Menu mnuChannel_15 
         Caption         =   "Channel_15"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub mnuChannel_0_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH00
End Sub

Private Sub mnuChannel_1_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH01
End Sub

Private Sub mnuChannel_10_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH10
End Sub

Private Sub mnuChannel_11_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH11
End Sub

Private Sub mnuChannel_12_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH12
End Sub

Private Sub mnuChannel_13_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH13
End Sub

Private Sub mnuChannel_14_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH14
End Sub

Private Sub mnuChannel_15_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH15
End Sub

Private Sub mnuChannel_2_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH02
End Sub

Private Sub mnuChannel_3_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH03
End Sub

Private Sub mnuChannel_4_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH04
End Sub

Private Sub mnuChannel_5_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH05
End Sub

Private Sub mnuChannel_6_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH06
End Sub

Private Sub mnuChannel_7_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH07
End Sub

Private Sub mnuChannel_8_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH08
End Sub

Private Sub mnuChannel_9_Click()
    Load Form6
    Form6.Show
    iChannelNumber = AO1600_CH09
End Sub

Private Sub mnuExit_Click()
    Unload Form5
End Sub
