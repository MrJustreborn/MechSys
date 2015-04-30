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
    
    Dim lError As Long
    Dim lStatus As Long
    
    lError = me4000AIGetStatus(glBoardNumber, ME4000_AI_WAIT_NONE, lStatus)
    
    If lStatus = ME4000_AI_STATUS_BUSY Then
        lError = me4000AIStop(glBoardNumber, 0)
    End If
    
    Unload Me
End Sub

Private Sub cmdStart_Click()
    
    Dim l_error As Long
    
    Dim l_channel_index As Long
    
    Dim b_channel(0 To 3) As Byte
    
    Dim l_scan_ticks_low As Long

    Dim l_scan_ticks_high As Long

        cmdStart.Enabled = False
        cmdStop.Enabled = True
             
        ' Create channel list
        '----------------------------------------------------
        For l_channel_index = 0 To 3
        
            l_error = me4000AIMakeChannelListEntry(l_channel_index, ME4000_AI_RANGE_BIPOLAR_10, b_channel(l_channel_index))
        
        Next l_channel_index
        
        l_error = me4000FrequencyToTicks(gdADCFrequency, l_scan_ticks_low, l_scan_ticks_high, ME4000_POINTER_NOT_USED)
        
        l_error = me4000AIConfig(glBoardNumber, b_channel(0), 4, ME4000_AI_INPUT_SINGLE_ENDED, ME4000_AI_SIMULTANEOUS_DISABLE, ME4000_VALUE_NOT_USED, 0, l_scan_ticks_low, l_scan_ticks_high, ME4000_AI_ACQ_MODE_SOFTWARE, ME4000_VALUE_NOT_USED, ME4000_VALUE_NOT_USED)
        
        l_error = me4000AIContinuous(glBoardNumber, AddressOf PlotData, 0, gdADCFrequency / 10, ME4000_VALUE_NOT_USED)
        
        l_error = me4000AIStart(glBoardNumber)
        
        gbDrawPlot = True
        
End Sub

Private Sub cmdStop_Click()
    
    gbDrawPlot = False

    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
    lError = me4000AIStop(glBoardNumber, 0)
    
End Sub

Private Sub Form_Load()

Dim l_error As Long

    glBoardNumber = 0           ' Number of used board.

    gdADCFrequency = 100#
    
    gdWindowWidth = 4#
    
    glPlotColor(0) = RGB(255, 0, 0)
    glPlotColor(1) = RGB(0, 255, 0)
    glPlotColor(2) = RGB(0, 0, 255)
    glPlotColor(3) = RGB(255, 255, 255)
    
    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
    gbDrawPlot = False
    
    l_error = me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE)
    
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
    
    gdYPixelFactor = CDbl(PlotArea.ScaleHeight + 1 - 20) / 65536#
    
    glLastXPixel = -1
    
    glLastYPixel(0) = -1
    glLastYPixel(1) = -1
    glLastYPixel(2) = -1
    glLastYPixel(3) = -1
    
    gbDrawPlot = True
    
End Sub

Private Sub PlotArea_Click()

End Sub
