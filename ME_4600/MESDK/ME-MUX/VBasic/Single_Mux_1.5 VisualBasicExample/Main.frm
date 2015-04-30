VERSION 5.00
Begin VB.Form Main 
   Caption         =   "Single-Mux with ME-2600/3000"
   ClientHeight    =   4650
   ClientLeft      =   2715
   ClientTop       =   2895
   ClientWidth     =   10440
   LinkTopic       =   "Form1"
   ScaleHeight     =   4650
   ScaleWidth      =   10440
   Begin VB.Menu Configuration 
      Caption         =   "Configuration"
   End
   Begin VB.Menu Identification 
      Caption         =   "Identify"
   End
   Begin VB.Menu SingleMux 
      Caption         =   "Single_Mux"
   End
   Begin VB.Menu Exit 
      Caption         =   "Exit"
   End
   Begin VB.Menu Form_About 
      Caption         =   "?"
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Configuration_Click()
    Load Mux_Config
    Mux_Config.Show
   
 End Sub

Private Sub Exit_Click()
    End
End Sub

Private Sub Form_About_Click()
    Load FormAbout
    FormAbout.Show
End Sub

Private Sub Identification_Click()
    Load Identify
    Identify.Show
End Sub

Private Sub SingleMux_Click()
    Load Single_Mux
    Single_Mux.Show
End Sub
