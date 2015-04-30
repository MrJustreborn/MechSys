Attribute VB_Name = "vbEx"
Option Explicit
Global AppName As String * 20

Global piADCBuffer(0 To 262144) As Integer
Global piDACBuffer(0 To 262144) As Integer
Global Const BUFFER_SIZE = 262144
Global giSingleValue As Integer
Global giCounterValue As Integer
Global glBoardNumber As Long
Global glADCChannel As Long
Global glADCCount As Long
Global glADCLoops As Long
Global glADCDelay As Long
Global glADCSize As Long
Global glADCTrigger As Long
Global glADCTriggerConti As Long
Global glADCRange As Long
Global glADCMode As Long
Global glDACChannel As Long
Global glDACCount As Long
Global glDACLoops As Long
Global glDACDelay As Long
Global glDACSize As Long
Global glDACTrigger As Long
Global glDACRange As Long
Global glDACMode As Long
Global glPWMDutyCycle As Long
Global glPWMInverted As Long

Global glScanToDisk As Long
Global glScanForEver As Long

Global glCNTEndValueA As Long
Global glCNTStartValueA As Long
Global glCNTEndValueB As Long
Global glCNTStartValueB As Long

Global gsADCFile As String

Global gdHalfRange As Double
Global gdADCOffset As Double
Global gdADCFrequency As Double
Global gdDACFrequency As Double
Global gdPWMFrequency As Double

Global gInterrupts As ME3000_ISR
Global gBoardInfo As ME3000_BOARD_INFO
Global gBoardData As ME_PLX9050_INFO
Global gDriverStatus As ME3000_DRIVER_STATUS



Global glRS485Mode As Long


Public Sub PlotADCData(ByRef piBuffer() As Integer, ByVal lSize As Long)
    Dim i As Integer
    Dim l As Long
    Dim XScale As Single
    Dim YScale As Single
    Dim x As Single
    Dim Y As Single
    Dim Y1 As Single
    
    vbMain.PlotArea.Cls
    ' Top line
    vbMain.PlotArea.Line (0, 0)-(vbMain.PlotArea.Width, 0), RGB(0, 256, 0)
    ' Right line
    vbMain.PlotArea.Line (0, 0)-(0, vbMain.PlotArea.Height), RGB(0, 256, 0)
    ' Left line
    vbMain.PlotArea.Line (vbMain.PlotArea.Width - 20, 0)-(vbMain.PlotArea.Width - 10, vbMain.PlotArea.Height - 20), RGB(0, 256, 0)
    ' Bottom line
    vbMain.PlotArea.Line (0, vbMain.PlotArea.Height - 20)-(vbMain.PlotArea.Width, vbMain.PlotArea.Height - 20), RGB(0, 256, 0)
    
    For i = 0 To 9
        vbMain.PlotArea.Line (0, vbMain.PlotArea.Height / 10 * i - 20)-(vbMain.PlotArea.Width, vbMain.PlotArea.Height / 10 * i - 20), RGB(0, 256, 0)
        vbMain.PlotArea.Line (vbMain.PlotArea.Width / 10 * i, 0)-(vbMain.PlotArea.Width / 10 * i, vbMain.PlotArea.Height), RGB(0, 256, 0)
    Next i
    
    XScale = CDbl(vbMain.PlotArea.Width) / CDbl(lSize)

    If glADCRange = AI3000_MINUS_10 Or glADCRange = AI3000_MINUS_5 Or glADCRange = AI3000_MINUS_2 Or glADCRange = AI3000_MINUS_1 Then
        YScale = CSng(vbMain.PlotArea.Height) / 2# / gdHalfRange
    Else
        YScale = CSng(vbMain.PlotArea.Height) / 4# / gdHalfRange
    End If
                                                    
    Y1 = vbMain.PlotArea.Height / 2#
    ' Get starting point
    '-------------------------------------------------------------
    Y = piBuffer(0) * 0.00048828125 * gdHalfRange - gdADCOffset
    Y = CSng(Y * YScale)
    vbMain.PlotArea.PSet (0, Y1 - Y)
    For l = 0 To lSize - 1
        x = CSng(l * XScale)
        Y = piBuffer(l) * 0.00048828125 * gdHalfRange - gdADCOffset
        Y = CSng(Y * YScale)
        'vbMain.PlotArea.PSet (X, Y1 - Y), RGB(256, 0, 0)
        vbMain.PlotArea.Line -(x, Y1 - Y), RGB(256, 0, 0)
    Next l
End Sub
Public Sub PlotDACData(ByRef piBuffer() As Integer, ByVal lSize As Long)
    Dim i As Integer
    Dim l As Long
    Dim XScale As Single
    Dim YScale As Single
    Dim x As Single
    Dim Y As Single
    Dim Y1 As Single
    
    ' Accessing piBuffer() is not yet working. So we use a
    ' global variable
    '--------------------------------------------------------
    
    vbMain.PlotArea.Cls
    ' Top line
    vbMain.PlotArea.Line (0, 0)-(vbMain.PlotArea.Width, 0), RGB(0, 256, 0)
    ' Right line
    vbMain.PlotArea.Line (0, 0)-(0, vbMain.PlotArea.Height), RGB(0, 256, 0)
    ' Left line
    vbMain.PlotArea.Line (vbMain.PlotArea.Width - 20, 0)-(vbMain.PlotArea.Width - 10, vbMain.PlotArea.Height - 20), RGB(0, 256, 0)
    ' Bottom line
    vbMain.PlotArea.Line (0, vbMain.PlotArea.Height - 20)-(vbMain.PlotArea.Width, vbMain.PlotArea.Height - 20), RGB(0, 256, 0)
    
    For i = 0 To 9
        vbMain.PlotArea.Line (0, vbMain.PlotArea.Height / 10 * i - 20)-(vbMain.PlotArea.Width, vbMain.PlotArea.Height / 10 * i - 20), RGB(0, 256, 0)
        vbMain.PlotArea.Line (vbMain.PlotArea.Width / 10 * i, 0)-(vbMain.PlotArea.Width / 10 * i, vbMain.PlotArea.Height), RGB(0, 256, 0)
    Next i
    
    XScale = CDbl(vbMain.PlotArea.Width) / CDbl(lSize)

    If glADCRange = AI3000_MINUS_10 Or glADCRange = AI3000_MINUS_5 Or glADCRange = AI3000_MINUS_2 Or glADCRange = AI3000_MINUS_1 Then
        YScale = CSng(vbMain.PlotArea.Height) / 2# / gdHalfRange
    Else
        YScale = CSng(vbMain.PlotArea.Height) / 4# / gdHalfRange
    End If
                                                    
    Y1 = vbMain.PlotArea.Height / 2#
    ' Get starting point
    '-------------------------------------------------------------
    Y = piDACBuffer(0) * 0.00048828125 * gdHalfRange - gdADCOffset
    Y = CSng(Y * YScale)
    vbMain.PlotArea.PSet (0, Y1 - Y)
    For l = 0 To lSize
        x = CSng(l * XScale)
        Y = piDACBuffer(l) * 0.00048828125 * gdHalfRange - gdADCOffset
        Y = CSng(Y * YScale)
        'vbMain.PlotArea.PSet (X, Y1 - Y), RGB(256, 0, 0)
        vbMain.PlotArea.Line -(x, Y1 - Y), RGB(256, 0, 0)
    Next l
End Sub

Public Sub AISingleHandler(ByRef piValue As Integer)
    Dim dValue As Double
    
    dValue = giSingleValue * 0.00048828125 * gdHalfRange - gdADCOffset
    vbMain.SingleValueLabel.Caption = " ADC " + Str(glADCChannel) + ": " + Str(giSingleValue) + "  " + Str(dValue) + " [V]"

End Sub
Public Sub ExternalInterruptHandler()
    Beep
End Sub
Public Sub CounterAInterruptHandler()
    Beep
End Sub
Public Sub CounterBInterruptHandler()
    Beep
End Sub

Public Sub AOContinuousHandler()
    MsgBox "Finished!", vbOKOnly, "AOContinuous"
End Sub

