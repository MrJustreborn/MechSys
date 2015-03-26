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
Option Explicit

Dim glBoardNumber As Long

Dim gdADCFrequency As Double

Dim gdWindowWidth As Double

Dim gdCurrentXPix As Double

Dim gdXPixIncrement As Double

Dim gdYPixelFactor As Double

Dim glLastXPixel As Long

Dim glLastYPixel(0 To 3) As Long

Dim glPlotColor(0 To 3) As Long

Dim gbDrawPlot As Boolean

Dim glBuffer(0 To 999) As Integer





Public Sub PlotData(ByRef piData() As Integer, ByVal lNumberOfData As Long)

    Dim l_no_frames As Long
   
    Dim d_current_pix As Double
   
    Dim l_old_x_pix As Single
    
    Dim l_channel As Long
    
    Dim l_frame As Long
    
    Dim l_X_pix As Long
    
    Dim l_Y_pix As Long
    
    Dim l_erase_from_pixel As Long
    
    Dim l_erase_to_pixel As Long
   
    If Not gbDrawPlot Then
        Exit Sub
    End If
    
    l_no_frames = lNumberOfData / 4
    
    If l_no_frames < 1 Then
        Exit Sub
    End If
   
    l_erase_from_pixel = glLastXPixel + 1
    
    l_erase_to_pixel = CLng(gdCurrentXPix + CDbl(l_no_frames) * gdXPixIncrement)
    
    If l_erase_to_pixel > l_erase_from_pixel Then
        If l_erase_to_pixel > CLng(frmMain.PlotArea.ScaleWidth) Then
            
            ' Erase right hand side of plot
            frmMain.PlotArea.Line (CSng(l_erase_from_pixel), 0)-(CSng(frmMain.PlotArea.ScaleWidth), CSng(frmMain.PlotArea.ScaleHeight)), frmMain.PlotArea.BackColor, BF
        
            l_erase_from_pixel = 0
            l_erase_to_pixel = l_erase_to_pixel - CLng(frmMain.PlotArea.ScaleWidth)
        End If
        
        frmMain.PlotArea.Line (CSng(l_erase_from_pixel), 0)-(CSng(l_erase_to_pixel + 1), CSng(frmMain.PlotArea.ScaleHeight)), frmMain.PlotArea.BackColor, BF
    
    End If
    
    For l_channel = 0 To 3
        
        l_old_x_pix = glLastXPixel
        
        d_current_pix = gdCurrentXPix
        
        For l_frame = 0 To l_no_frames - 1
        
            l_X_pix = CLng(d_current_pix)
            
            l_Y_pix = CLng(gdYPixelFactor * (CLng(piData(l_channel + l_frame * 4)) + 32768)) + 10
            
            If Not gbDrawPlot Then
                Exit Sub
            End If
    
            ' To save time we only draw a line if the position has changed
            
            If l_old_x_pix <> l_X_pix Or glLastYPixel(l_channel) <> l_Y_pix Then
                If l_old_x_pix <> -1 Then
                    frmMain.PlotArea.Line (CSng(l_old_x_pix), CSng(glLastYPixel(l_channel)))-(CSng(l_X_pix), CSng(l_Y_pix)), glPlotColor(l_channel)
                End If
                
                glLastYPixel(l_channel) = l_Y_pix
                
                l_old_x_pix = l_X_pix
            End If
            
            d_current_pix = d_current_pix + gdXPixIncrement
            
            If CLng(d_current_pix) > CLng(frmMain.PlotArea.ScaleWidth) Then
                d_current_pix = d_current_pix - CDbl(frmMain.PlotArea.ScaleWidth)
                
                l_old_x_pix = l_old_x_pix - CLng(frmMain.PlotArea.ScaleWidth)
            End If
        
        Next l_frame
    
    Next l_channel

    gdCurrentXPix = d_current_pix
    
    glLastXPixel = l_old_x_pix

    frmMain.PlotArea.Line (CSng(glLastXPixel + 1), 0)-(CSng(glLastXPixel + 1), CSng(frmMain.PlotArea.ScaleHeight)), RGB(&HFF, &HFF, &HFF)
    
End Sub

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
    
    Dim l_acq_error As Long
    
    Dim l_channel_index As Long
    
    Dim b_channel(0 To 3) As Byte
    
    Dim l_scan_ticks_low As Long

    Dim l_scan_ticks_high As Long
    
    Dim l_no_of_values As Long
    
    Dim l_loop As Long

        cmdStart.Enabled = False
        cmdStop.Enabled = True
             
        ' Create channel list
        '----------------------------------------------------
        For l_channel_index = 0 To 3
        
            l_error = me4000AIMakeChannelListEntry(l_channel_index, ME4000_AI_RANGE_BIPOLAR_10, b_channel(l_channel_index))
        
        Next l_channel_index
        
        l_error = me4000FrequencyToTicks(gdADCFrequency, l_scan_ticks_low, l_scan_ticks_high, ME4000_POINTER_NOT_USED)
        
        l_error = me4000AIConfig(glBoardNumber, b_channel(0), 4, ME4000_AI_INPUT_SINGLE_ENDED, ME4000_AI_SIMULTANEOUS_DISABLE, ME4000_VALUE_NOT_USED, 0, l_scan_ticks_low, l_scan_ticks_high, ME4000_AI_ACQ_MODE_SOFTWARE, ME4000_VALUE_NOT_USED, ME4000_VALUE_NOT_USED)
        
        l_error = me4000AIContinuous(glBoardNumber, ME4000_POINTER_NOT_USED, ME4000_VALUE_NOT_USED, gdADCFrequency / 10, ME4000_VALUE_NOT_USED)
        
        l_error = me4000AIStart(glBoardNumber)
        
        For l_loop = 0 To 10
        
            l_error = me4000AIGetNewValues(glBoardNumber, glBuffer(0), 1000, ME4000_AI_GET_NEW_VALUES_BLOCKING, l_no_of_values, l_error)
            
            Call PlotData(glBuffer, l_no_of_values)
            
        Next l_loop
        
        gbDrawPlot = True
        
End Sub

Private Sub cmdStop_Click()
    
    Dim l_error As Long
        
    gbDrawPlot = False

    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
    l_error = me4000AIStop(glBoardNumber, 0)
    
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

