VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "AIContinuous"
   ClientHeight    =   5820
   ClientLeft      =   5700
   ClientTop       =   5145
   ClientWidth     =   9225
   LinkTopic       =   "Form1"
   ScaleHeight     =   5820
   ScaleWidth      =   9225
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox PlotArea 
      BackColor       =   &H00000000&
      Height          =   2156
      Left            =   240
      ScaleHeight     =   2100
      ScaleWidth      =   1725
      TabIndex        =   3
      Top             =   240
      Width           =   1778
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "EXIT"
      Height          =   392
      Left            =   3528
      TabIndex        =   2
      Top             =   5040
      Width           =   1400
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "STOP"
      Height          =   392
      Left            =   1890
      TabIndex        =   1
      Top             =   5040
      Width           =   1400
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "START"
      Height          =   392
      Left            =   252
      TabIndex        =   0
      Top             =   5040
      Width           =   1400
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdExit_Click()
    
    If me3000AIStop(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    
    Unload Me
End Sub

Private Sub cmdStart_Click()
    
    Dim l_entry As Long

        cmdStart.Enabled = False
        cmdStop.Enabled = True
             
        ' Clear the current channel list
        '----------------------------------------------------
        If me3000AIClearChannelList(glBoardNumber) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
            
        ' Set timer
        '----------------------------------------------------
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency * 4)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        ' Write n channel list entries to the board
        '----------------------------------------------------
        '********** Channel 0 **********
        If me3000AIMakeChannelListEntry(0, AI3000_MINUS_10, AI3000_SINGLE_ENDED, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIAddToChannelList(glBoardNumber, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
              
        '********** Channel 1 **********
        If me3000AIMakeChannelListEntry(1, AI3000_MINUS_10, AI3000_SINGLE_ENDED, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIAddToChannelList(glBoardNumber, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
              
        '********** Channel 2 **********
        If me3000AIMakeChannelListEntry(2, AI3000_MINUS_10, AI3000_SINGLE_ENDED, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIAddToChannelList(glBoardNumber, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
              
        '********** Channel 3 **********
        If me3000AIMakeChannelListEntry(3, AI3000_MINUS_10, AI3000_SINGLE_ENDED, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIAddToChannelList(glBoardNumber, l_entry) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
              
        ' Set trigger
        '----------------------------------------------------
        If me3000AISetTrigger(glBoardNumber, AI3000_TRIGGER_TIMER) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
            
        If me3000AIContinuous(glBoardNumber, 4, &H10000, AddressOf PlotData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        gbDrawPlot = True
        
End Sub

Private Sub cmdStop_Click()
    
    gbDrawPlot = False

    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
    If me3000AIStop(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    
End Sub

Private Sub Form_Load()

Dim l_error As Long

    AppName = "ME3000i"
    
    glBoardNumber = 0           ' Number of used board.

    gdADCFrequency = 1000#
    
    gdWindowWidth = 4#
    
    glPlotColor(0) = RGB(255, 0, 0)
    glPlotColor(1) = RGB(0, 255, 0)
    glPlotColor(2) = RGB(0, 0, 255)
    glPlotColor(3) = RGB(255, 255, 255)
    
    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
    gbDrawPlot = False
    
End Sub


Private Sub Form_Resize()
    
    gbDrawPlot = False
    
    PlotArea.Cls
    
    PlotArea.ScaleMode = vbTwips

    If (Me.Width - 250) > 1000 Then
        PlotArea.Width = Me.Width - 500
    End If
    If (Me.Height - 1000) > 1000 Then
        PlotArea.Height = Me.Height - 2000
    End If
    
    cmdStart.Top = PlotArea.Height + 500
    cmdStop.Top = PlotArea.Height + 500
    cmdExit.Top = PlotArea.Height + 500
    
    PlotArea.ScaleMode = vbPixels

    gdCurrentXPix = 0#
    
    gdXPixIncrement = CDbl(PlotArea.ScaleWidth + 1) / gdWindowWidth / gdADCFrequency
    
    gdYPixelFactor = CDbl(PlotArea.ScaleHeight + 1 - 20) / 4095#
    
    glLastXPixel = -1
    
    glLastYPixel(0) = -1
    glLastYPixel(1) = -1
    glLastYPixel(2) = -1
    glLastYPixel(3) = -1
    
    gbDrawPlot = True
    
End Sub
