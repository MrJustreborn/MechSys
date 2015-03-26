VERSION 5.00
Begin VB.Form Form7 
   Caption         =   "AOSetMode"
   ClientHeight    =   3135
   ClientLeft      =   5040
   ClientTop       =   3705
   ClientWidth     =   4680
   LinkTopic       =   "Form7"
   ScaleHeight     =   3135
   ScaleWidth      =   4680
   Begin VB.Menu mnuChannelGroupSettings 
      Caption         =   "Channel Group Settings"
      Begin VB.Menu mnuChannelGroup_A 
         Caption         =   "ChannelGroup_A"
      End
      Begin VB.Menu mnuChannelGroup_B 
         Caption         =   "ChannelGroup_B"
      End
      Begin VB.Menu mnuChannelGroup_C 
         Caption         =   "ChannelGroup_C"
      End
      Begin VB.Menu mnuChannelGroup_D 
         Caption         =   "ChannelGroup_D"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
End
Attribute VB_Name = "Form7"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub mnuChannelGroup_A_Click()
    Load Form8
    Form8.Show
    iChannelGroup = AO1600_GROUP_A
End Sub

Private Sub mnuChannelGroup_B_Click()
    Load Form8
    Form8.Show
    iChannelGroup = AO1600_GROUP_B
End Sub

Private Sub mnuChannelGroup_C_Click()
    Load Form8
    Form8.Show
    iChannelGroup = AO1600_GROUP_C
End Sub

Private Sub mnuChannelGroup_D_Click()
    Load Form8
    Form8.Show
    iChannelGroup = AO1600_GROUP_D
End Sub

Private Sub mnuExit_Click()
    Unload Form7
End Sub
