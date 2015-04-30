Attribute VB_Name = "Callback"
Option Explicit

Global AppName As String * 20

Global glBoardNumber As Long

Global gdADCFrequency As Double

Global gdWindowWidth As Double

Global gdCurrentXPix As Double

Global gdXPixIncrement As Double

Global gdYPixelFactor As Double

Global glLastXPixel As Long

Global glLastYPixel(0 To 3) As Long

Global glPlotColor(0 To 3) As Long

Global gbDrawPlot As Boolean





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
            
            l_Y_pix = CLng(gdYPixelFactor * piData(l_channel + l_frame * 4)) + 10
            
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




