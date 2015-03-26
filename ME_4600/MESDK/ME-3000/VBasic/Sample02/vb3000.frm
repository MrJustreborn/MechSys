VERSION 5.00
Begin VB.Form vbMain 
   Caption         =   "ME3000 Test Application (VB 5.0)"
   ClientHeight    =   4590
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   8475
   LinkTopic       =   "Form1"
   ScaleHeight     =   4590
   ScaleWidth      =   8475
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox PlotArea 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H80000015&
      BorderStyle     =   0  'None
      Height          =   3132
      Left            =   360
      ScaleHeight     =   3135
      ScaleWidth      =   6735
      TabIndex        =   0
      Top             =   480
      Width           =   6732
   End
   Begin VB.Label SingleValueLabel 
      BorderStyle     =   1  'Fixed Single
      Height          =   252
      Left            =   360
      TabIndex        =   1
      Top             =   120
      Width           =   2412
   End
   Begin VB.Menu mnuBasics 
      Caption         =   "&Basics"
      Begin VB.Menu menClearPlotArea 
         Caption         =   "Clear Plot &Area"
      End
      Begin VB.Menu Separator1_00 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDLLVersion 
         Caption         =   "&DLL Version"
      End
      Begin VB.Menu mnuDriverVersion 
         Caption         =   "D&river Version"
      End
      Begin VB.Menu mnuDriverTimeStamp 
         Caption         =   "Driver &Time Stamp"
      End
      Begin VB.Menu Separator1_0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuBoardSelection 
         Caption         =   "&Board Selection"
         Begin VB.Menu mnuSelectBoard1 
            Caption         =   "Board &1"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuSelectBoard2 
            Caption         =   "Board &2"
         End
         Begin VB.Menu mnuSelectBoard3 
            Caption         =   "Board &3"
         End
         Begin VB.Menu mnuSelectBoard4 
            Caption         =   "Board &4"
         End
      End
      Begin VB.Menu Separator1_01 
         Caption         =   "-"
      End
      Begin VB.Menu mnuVECModel 
         Caption         =   "&VEC Model"
      End
      Begin VB.Menu Separator1_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPCIConfiguration 
         Caption         =   "&PCI Configuration"
      End
      Begin VB.Menu Separator1_2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSerialNumber 
         Caption         =   "&Serial Number"
      End
      Begin VB.Menu Separator1_29 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDriverStatus 
         Caption         =   "D&river Status"
      End
      Begin VB.Menu Separator1_30 
         Caption         =   "-"
      End
      Begin VB.Menu mnuInterruptCounter 
         Caption         =   "Interr&upt Counter"
      End
      Begin VB.Menu Separator1_3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuBoardInfo 
         Caption         =   "Board &Info"
      End
      Begin VB.Menu Separator1_4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuInitialize 
         Caption         =   "Initiali&ze ME3000"
      End
      Begin VB.Menu Separator1_5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuGeneralReset 
         Caption         =   "&General Reset"
      End
      Begin VB.Menu Separator1_6 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetPriority 
         Caption         =   "Background Pri&ority High"
      End
      Begin VB.Menu Separator1_7 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuADC 
      Caption         =   "&ADC"
      Begin VB.Menu mnuStopADC 
         Caption         =   "Sto&p"
      End
      Begin VB.Menu Separator2_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuADCSingle 
         Caption         =   "&Single"
         Begin VB.Menu mnuSingleSingle 
            Caption         =   "&One Shot"
         End
         Begin VB.Menu Separator2_13 
            Caption         =   "-"
         End
         Begin VB.Menu mnuSingleConti 
            Caption         =   "&Run Continuously"
         End
      End
      Begin VB.Menu mnuADCQuick 
         Caption         =   "&Quick"
         Begin VB.Menu mnuQuickPolling 
            Caption         =   "&Polling Mode"
         End
         Begin VB.Menu mnuQuickInterrupt 
            Caption         =   "&Interrupt Mode"
         End
         Begin VB.Menu Separator2_12 
            Caption         =   "-"
         End
         Begin VB.Menu mnuQuickContiPolling 
            Caption         =   "&Run continuously in polling mode"
         End
         Begin VB.Menu mnuQuickContiInt 
            Caption         =   "Run &continuously in interrupt mode"
         End
      End
      Begin VB.Menu mnuADCMultiple 
         Caption         =   "&Multiple"
         Begin VB.Menu mnuMultiplePolling 
            Caption         =   "&Polling Mode"
         End
         Begin VB.Menu mnuMultipleInterrupt 
            Caption         =   "&Interrupt Mode"
         End
         Begin VB.Menu Separator2_11 
            Caption         =   "-"
         End
         Begin VB.Menu mnuMultipleContiPolling 
            Caption         =   "&Run continuously in polling mode"
         End
         Begin VB.Menu mnuMultipleContiInterrupt 
            Caption         =   "Run &continuously in interrupt mode"
         End
      End
      Begin VB.Menu mnuADCScan 
         Caption         =   "Sc&an"
         Begin VB.Menu mnuScanPolling 
            Caption         =   "&Polling Mode"
         End
         Begin VB.Menu mnuScanInterrupt 
            Caption         =   "&Interrupt Mode"
         End
         Begin VB.Menu Separator2_24 
            Caption         =   "-"
         End
         Begin VB.Menu mnuScanContiPolling 
            Caption         =   "&Run continuously in polling mode"
         End
         Begin VB.Menu mnuScanContiInterrupt 
            Caption         =   "Run &continuously in interrupt mode"
         End
         Begin VB.Menu Separator2_25 
            Caption         =   "-"
         End
         Begin VB.Menu mnuScanToDisk 
            Caption         =   "&Scan to hard disk"
         End
         Begin VB.Menu mnuScanForEver 
            Caption         =   "Scan for &ever"
         End
      End
      Begin VB.Menu Separator2_2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSimultaneousSampling 
         Caption         =   "&Simultaneous sampling"
      End
      Begin VB.Menu Separator2_3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuADCChannel 
         Caption         =   "&Channel"
         Begin VB.Menu mnuADC0 
            Caption         =   "ADC &0"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuADC1 
            Caption         =   "ADC &1"
         End
         Begin VB.Menu mnuADC2 
            Caption         =   "ADC &2"
         End
         Begin VB.Menu mnuADC3 
            Caption         =   "ADC &3"
         End
         Begin VB.Menu mnuADC4 
            Caption         =   "ADC &4"
         End
         Begin VB.Menu mnuADC5 
            Caption         =   "ADC &5"
         End
         Begin VB.Menu mnuADC6 
            Caption         =   "ADC &6"
         End
         Begin VB.Menu mnuADC7 
            Caption         =   "ADC &7"
         End
         Begin VB.Menu mnuADC8 
            Caption         =   "ADC &8"
         End
         Begin VB.Menu mnuADC9 
            Caption         =   "ADC &9"
         End
         Begin VB.Menu mnuADCA 
            Caption         =   "ADC &A"
         End
         Begin VB.Menu mnuADCB 
            Caption         =   "ADC &B"
         End
         Begin VB.Menu mnuADCC 
            Caption         =   "ADC &C"
         End
         Begin VB.Menu mnuADCD 
            Caption         =   "ADC &D"
         End
         Begin VB.Menu mnuADCE 
            Caption         =   "ADC &E"
         End
         Begin VB.Menu mnuADCF 
            Caption         =   "ADC &F"
         End
      End
      Begin VB.Menu mnuADCRange 
         Caption         =   "&Range"
         Begin VB.Menu mnuRangeMinus10 
            Caption         =   "+/- 10 V"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuRangeMinus5 
            Caption         =   "+/- 5 V"
         End
         Begin VB.Menu mnuRangeMinus2 
            Caption         =   "+/- 2.5 V"
         End
         Begin VB.Menu mnuRangeMinus1 
            Caption         =   "+/- 1.25 V"
         End
         Begin VB.Menu mnuRangePlus10 
            Caption         =   "0..10 V"
         End
         Begin VB.Menu mnuRangePlus5 
            Caption         =   "0..5 V"
         End
         Begin VB.Menu mnuRangePlus2 
            Caption         =   "0..2.5 V"
         End
         Begin VB.Menu mnuRangePlus1 
            Caption         =   "0..1.25 V"
         End
      End
      Begin VB.Menu mnuADCTrigger 
         Caption         =   "&Trigger"
         Begin VB.Menu mnuADCTriggerTimer 
            Caption         =   "&Timer"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuADCTriggerHigh 
            Caption         =   "&High"
         End
         Begin VB.Menu mnuADCTriggerLow 
            Caption         =   "&Low"
         End
         Begin VB.Menu mnuADCTriggerConti 
            Caption         =   "&Run continuously"
         End
      End
      Begin VB.Menu mnuDifferentialMode 
         Caption         =   "D&ifferential Mode"
      End
      Begin VB.Menu Separator2_4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuADCSetup 
         Caption         =   "Set&up"
         Begin VB.Menu mnuADCSetupFrequency 
            Caption         =   "&Frequency"
         End
         Begin VB.Menu mnuADCSetupCounter 
            Caption         =   "&Counter"
         End
         Begin VB.Menu mnuADCSetupDelay 
            Caption         =   "&Delay"
         End
         Begin VB.Menu mnuADCSetupChanlist 
            Caption         =   "&Size of chan. list"
         End
         Begin VB.Menu mnuADCSetupLoops 
            Caption         =   "&Loops"
         End
         Begin VB.Menu mnuADCFileName 
            Caption         =   "File &Name"
         End
      End
      Begin VB.Menu Separator2_5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuShowDataFile 
         Caption         =   "Show &Data File"
      End
   End
   Begin VB.Menu mnuDIO 
      Caption         =   "DI&O"
   End
   Begin VB.Menu mnuDAC 
      Caption         =   "&DAC"
      Begin VB.Menu mnuDACStop 
         Caption         =   "Sto&p"
      End
      Begin VB.Menu Separator4_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDACSingle 
         Caption         =   "&Single"
      End
      Begin VB.Menu mnuDACWrapAround 
         Caption         =   "&WrapAround"
      End
      Begin VB.Menu mnuDACContinous 
         Caption         =   "&Continous"
         Begin VB.Menu mnuDACPolling 
            Caption         =   "&Polling Mode"
         End
         Begin VB.Menu mnuDACInterrupt 
            Caption         =   "&Interrupt Mode"
         End
         Begin VB.Menu Separator4_10 
            Caption         =   "-"
         End
         Begin VB.Menu mnuDACContiPolling 
            Caption         =   "&Run continuously in polling mode"
         End
         Begin VB.Menu mnuDACContiInt 
            Caption         =   "Run &continuously in interrupt mode"
         End
      End
      Begin VB.Menu Separator4_2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDACChannel 
         Caption         =   "&Channel"
         Begin VB.Menu mnuDAC0 
            Caption         =   "DAC &0"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuDAC1 
            Caption         =   "DAC &1"
         End
         Begin VB.Menu mnuDAC2 
            Caption         =   "DAC &2"
         End
         Begin VB.Menu mnuDAC3 
            Caption         =   "DAC &3"
         End
      End
      Begin VB.Menu mnuDACRange 
         Caption         =   "&Range"
         Begin VB.Menu mnuDACRangeMinus10 
            Caption         =   "+/- 10 V"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuDACRangeMinus5 
            Caption         =   "+/- 5 V"
         End
         Begin VB.Menu mnuDACRangePlus 
            Caption         =   "0..10 V"
         End
      End
      Begin VB.Menu mnuDACTrigger 
         Caption         =   "&Trigger"
         Begin VB.Menu mnuDACTriggerTimer 
            Caption         =   "&Timer"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuDACTriggerHigh 
            Caption         =   "&High"
         End
         Begin VB.Menu mnuDACTriggerLow 
            Caption         =   "&Low"
         End
      End
      Begin VB.Menu mnuDACMode 
         Caption         =   "&Mode"
         Begin VB.Menu mnuDACBuffered 
            Caption         =   "&Buffered"
         End
         Begin VB.Menu mnuDACTransparent 
            Caption         =   "&Transparent"
            Checked         =   -1  'True
         End
      End
      Begin VB.Menu Separator4_3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDACSetup 
         Caption         =   "Set&up"
         Begin VB.Menu mnuDACFreq 
            Caption         =   "&Frequency"
         End
         Begin VB.Menu mnuDACCounter 
            Caption         =   "&Counter"
         End
         Begin VB.Menu mnuDACDelay 
            Caption         =   "&Delay"
         End
         Begin VB.Menu mnuDACSize 
            Caption         =   "&No. of FIFO entries"
         End
         Begin VB.Menu mnuDACLoops 
            Caption         =   "&Loops"
         End
      End
      Begin VB.Menu Separator4_4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDACUpdate 
         Caption         =   "Upd&ate"
      End
      Begin VB.Menu Separator4_5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDACReset 
         Caption         =   "&Reset"
      End
   End
   Begin VB.Menu mnuPWM 
      Caption         =   "&PWM"
      Begin VB.Menu mnuPWMStart 
         Caption         =   "&Start"
      End
      Begin VB.Menu mnuPWMFrequency 
         Caption         =   "&Frequency"
      End
      Begin VB.Menu mnuPWMDutyCycle 
         Caption         =   "&Duty Cycle"
      End
      Begin VB.Menu mnuPWMInverted 
         Caption         =   "&Inverted"
      End
   End
   Begin VB.Menu mnuExtInterrupt 
      Caption         =   "E&xt. Interrupt"
      Begin VB.Menu mnuEnableExternInterrupt 
         Caption         =   "&Enable"
      End
   End
   Begin VB.Menu mnuCounterA 
      Caption         =   "Counter &A"
      Begin VB.Menu mnuCountARead 
         Caption         =   "Re&ad"
      End
      Begin VB.Menu mnuCountAStart 
         Caption         =   "S&tart"
      End
      Begin VB.Menu mnuCountAReset 
         Caption         =   "&Reset"
      End
      Begin VB.Menu mnuCountALoad 
         Caption         =   "&Load"
      End
      Begin VB.Menu mnuCountAEnableInt 
         Caption         =   "Enable &Interrupt"
      End
      Begin VB.Menu Separator5_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCountASetupEndValue 
         Caption         =   "Setup &End Value"
      End
      Begin VB.Menu mnuCountASetupStartValue 
         Caption         =   "Setup &Start Value"
      End
   End
   Begin VB.Menu mnuCountB 
      Caption         =   "Counter &B"
      Begin VB.Menu mnuCountBRead 
         Caption         =   "Re&ad"
      End
      Begin VB.Menu mnuCountBStart 
         Caption         =   "S&tart"
      End
      Begin VB.Menu mnuCountBReset 
         Caption         =   "&Reset"
      End
      Begin VB.Menu mnuCountBLoad 
         Caption         =   "&Load"
      End
      Begin VB.Menu mnuCountBEnableInt 
         Caption         =   "Enable &Interrupt"
      End
      Begin VB.Menu Separator6_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCountBSetupEndValue 
         Caption         =   "Setup &End Value"
      End
      Begin VB.Menu mnuCountBSetupStartValue 
         Caption         =   "Setup &Start Value"
      End
   End
   Begin VB.Menu mnuSIO 
      Caption         =   "&SIO"
      Begin VB.Menu mnuShowRegisters 
         Caption         =   "&Show Registers"
      End
      Begin VB.Menu mnuReadRegisters 
         Caption         =   "&Read Registers"
      End
      Begin VB.Menu mnuWriteRegisters 
         Caption         =   "&Write Registers"
      End
      Begin VB.Menu mnuLoopbackTest 
         Caption         =   "&Loopback Test"
      End
      Begin VB.Menu Separator7_1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSIOTransmitPoll 
         Caption         =   "&Transmit in polling mode"
      End
      Begin VB.Menu mnuSIOReceivePoll 
         Caption         =   "Re&ceive in polling mode"
      End
      Begin VB.Menu Separator7_2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuTransmitInt 
         Caption         =   "Trans&mit in interrupt mode"
      End
      Begin VB.Menu mnuSIOReceiveInt 
         Caption         =   "Recei&ve in interrupt mode"
      End
      Begin VB.Menu Separator7_3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSIORS422 
         Caption         =   "RS&485/RS422"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuSIORS485HALF 
         Caption         =   "RS485 &Half-Duplex"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About VB3000 Test"
      End
   End
End
Attribute VB_Name = "vbMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim gsBigText As String
Dim gsTextBuffer As String * 256
Dim gbAOStop As Integer

Dim gMessage, gTitle, gDefault, gInputValue

Private Sub Form_Load()
    AppName = "ME3000 Test (VB)"
    glBoardNumber = 0
    glADCChannel = 0
    glADCCount = 1024
    glADCLoops = -1
    glADCDelay = 100
    glADCSize = 256
    
    glDACChannel = 0
    glDACCount = 1024
    glDACLoops = -1
    glDACDelay = 100
    glDACSize = 4096
    
    glADCRange = AI3000_MINUS_10
    glADCMode = AI3000_SINGLE_ENDED
    glADCTrigger = AI3000_TRIGGER_TIMER
    glADCTriggerConti = 0
    
    glDACRange = AO3000_MINUS_10
    glDACTrigger = AO3000_TRIGGER_TIMER
    glDACMode = AO3000_TRANSPARENT
    
    glPWMDutyCycle = 50&
    glPWMInverted = PWM3000_NORMAL
    
    glCNTEndValueA = 10
    glCNTStartValueA = 1
    glCNTEndValueB = 10
    glCNTStartValueB = 1
        
    gdHalfRange = 10#
    gdADCOffset = 10#
    gdADCFrequency = 49000#
    gdDACFrequency = 100000#
    gdPWMFrequency = 10000#
    
    gsADCFile = "C:\ME3000_1.DAT"
    gbAOStop = False
    
    glScanToDisk = 0
    glScanForEver = 0
    
    glRS485Mode = 0
    
    Me.Width = 9000
    Me.Height = 6000
    PlotArea.Top = 100
    PlotArea.Left = 100
    
    Me.Caption = "ME3000 Test Application (VB 5.0) connected to board 0"
    
End Sub

Private Sub Form_Resize()
    If (Me.Width - 250) > 1000 Then
        PlotArea.Width = Me.Width - 250
    End If
    If (Me.Height - 1000) > 1000 Then
        PlotArea.Height = Me.Height - 700 - SingleValueLabel.Height - 100
    End If
    SingleValueLabel.Width = PlotArea.Width
    SingleValueLabel.Left = PlotArea.Left
    SingleValueLabel.Top = PlotArea.Top + PlotArea.Height + 20

    End Sub

Private Sub menClearPlotArea_Click()
    PlotArea.Cls
End Sub

Private Sub mnuAbout_Click()
    frmAboutBox.Show
End Sub

Private Sub mnuADC0_Click()
    mnuADC0.Checked = True
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 0
End Sub

Private Sub mnuADC1_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = True
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 1
End Sub

Private Sub mnuADC2_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = True
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 2
End Sub

Private Sub mnuADC3_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = True
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 3
End Sub

Private Sub mnuADC4_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = True
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 4
End Sub

Private Sub mnuADC5_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = True
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 5
End Sub

Private Sub mnuADC6_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = True
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 6
End Sub

Private Sub mnuADC7_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = True
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 7
End Sub

Private Sub mnuADC8_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = True
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 8
End Sub

Private Sub mnuADC9_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = True
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 9
End Sub

Private Sub mnuADCA_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = True
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 10
End Sub

Private Sub mnuADCB_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = True
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 11
End Sub

Private Sub mnuADCC_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = True
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 12
End Sub

Private Sub mnuADCD_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = True
    mnuADCE.Checked = False
    mnuADCF.Checked = False
    glADCChannel = 13
End Sub

Private Sub mnuADCE_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = True
    mnuADCF.Checked = False
    glADCChannel = 14
End Sub

Private Sub mnuADCF_Click()
    mnuADC0.Checked = False
    mnuADC1.Checked = False
    mnuADC2.Checked = False
    mnuADC3.Checked = False
    mnuADC4.Checked = False
    mnuADC5.Checked = False
    mnuADC6.Checked = False
    mnuADC7.Checked = False
    mnuADC8.Checked = False
    mnuADC9.Checked = False
    mnuADCA.Checked = False
    mnuADCB.Checked = False
    mnuADCC.Checked = False
    mnuADCD.Checked = False
    mnuADCE.Checked = False
    mnuADCF.Checked = True
    glADCChannel = 15
End Sub

Private Sub mnuADCFileName_Click()
    gMessage = "Enter file name"   ' Set prompt.
    gTitle = "ADC File Name"
    gDefault = gsADCFile
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        gsADCFile = gInputValue
        Call me3000FileName(glBoardNumber, 0, gsADCFile)
    End If
End Sub

Private Sub mnuADCSetupChanlist_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "ADC Size Of ChannelList"
    gDefault = Trim(Str(glADCSize))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glADCSize = CLng(gInputValue)
    End If
End Sub

Private Sub mnuADCSetupCounter_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "ADC Counter"
    gDefault = Trim(Str(glADCCount))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glADCCount = CLng(gInputValue)
    End If
End Sub

Private Sub mnuADCSetupDelay_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "ADC Delay"
    gDefault = Trim(Str(glADCDelay))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glADCDelay = CLng(gInputValue)
    End If
End Sub

Private Sub mnuADCSetupFrequency_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "Frequency"
    gDefault = Trim(Str(CLng(gdADCFrequency)))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        gdADCFrequency = CDbl(gInputValue)
    End If
End Sub

Private Sub mnuADCSetupLoops_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "Loops Of Background Process"
    gDefault = Trim(Str(glADCLoops))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glADCLoops = CLng(gInputValue)
    End If
End Sub

Private Sub mnuADCTriggerConti_Click()
    If glADCTriggerConti = 0 Then
        glADCTriggerConti = AI3000_TRIGGER_CONTI
        mnuADCTriggerConti.Checked = True
    Else
        glADCTriggerConti = 0
        mnuADCTriggerConti.Checked = False
    End If
End Sub

Private Sub mnuADCTriggerHigh_Click()
    mnuADCTriggerTimer.Checked = False
    mnuADCTriggerHigh.Checked = True
    mnuADCTriggerLow.Checked = False
    glADCTrigger = AI3000_TRIGGER_EXT_HIGH
End Sub

Private Sub mnuADCTriggerLow_Click()
    mnuADCTriggerTimer.Checked = False
    mnuADCTriggerHigh.Checked = False
    mnuADCTriggerLow.Checked = True
    glADCTrigger = AI3000_TRIGGER_EXT_LOW
End Sub

Private Sub mnuADCTriggerTimer_Click()
    mnuADCTriggerTimer.Checked = True
    mnuADCTriggerHigh.Checked = False
    mnuADCTriggerLow.Checked = False
    glADCTrigger = AI3000_TRIGGER_TIMER
End Sub

Private Sub mnuBoardInfo_Click()
    If me3000DLLBoardInfo(glBoardNumber, gBoardInfo) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        gsBigText = Chr(9) + "Information of Board: " + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.DeviceNumber)) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "PCI slot number:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.SlotNumber)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "RT phys. address:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardInfo.RTPhysAddr) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "XILINX phys. address:" + Chr(9) + "0x" + Hex(gBoardInfo.XilinxPhysAddr) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "SIO phys. address:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardInfo.SioPhysAddr) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Boards found:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.NoOfBoards)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "General Debug Word:" + Chr(9) + "0x" + Hex(gBoardInfo.Word) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Firmware File Status:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.FileStatus)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Firmware File Length:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.FileLength)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Firmware Version:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardInfo.FileVersion) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Firmware Date:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardInfo.FileDate) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Size of ADC FIFO:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.AdcFifo)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Size of DAC FIFO:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.DacFifo)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Size of Chan. List FIFO:" + Chr(9) + Trim(Str(gBoardInfo.ChanListFifo)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Serial Number:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.SerialNumber)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "EEPROM date:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardInfo.Date) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "MEVEC Model:" + Chr(9) + Chr(9) + Trim(Str(gBoardInfo.MEVECModel)) + Chr(10) + Chr(13)
        MsgBox gsBigText, vbOKOnly
    End If
End Sub

Private Sub mnuCountAEnableInt_Click()
    If mnuCountAEnableInt.Checked Then
        If me3000CNTInterrupt(glBoardNumber, COUNTER3000_A, COUNTER3000_DISABLE, AddressOf CounterAInterruptHandler) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuCountAEnableInt.Checked = False
    Else
        If me3000CNTInterrupt(glBoardNumber, COUNTER3000_A, COUNTER3000_ENABLE, AddressOf CounterAInterruptHandler) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuCountAEnableInt.Checked = True
    End If
End Sub

Private Sub mnuCountALoad_Click()
    If me3000CNTSetRange(glBoardNumber, COUNTER3000_A, glCNTEndValueA, glCNTStartValueA) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuCountARead_Click()
    If me3000CNTRead(glBoardNumber, COUNTER3000_A, giCounterValue) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    Else
        SingleValueLabel.Caption = "Counter A = " + Str(giCounterValue)
    End If
End Sub

Private Sub mnuCountAReset_Click()
    If me3000CNTReset(glBoardNumber, COUNTER3000_A) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuCountASetupEndValue_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "End Value"
    gDefault = Trim(Str(glCNTEndValueA))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glCNTEndValueA = CLng(gInputValue)
    End If
End Sub

Private Sub mnuCountASetupStartValue_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "End Value"
    gDefault = Trim(Str(glCNTStartValueA))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glCNTStartValueA = CLng(gInputValue)
    End If
End Sub

Private Sub mnuCountAStart_Click()
    If me3000CNTStart(glBoardNumber, COUNTER3000_A) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuCountBEnableInt_Click()
    If mnuCountBEnableInt.Checked Then
        If me3000CNTInterrupt(glBoardNumber, COUNTER3000_B, COUNTER3000_DISABLE, AddressOf CounterBInterruptHandler) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuCountBEnableInt.Checked = False
    Else
        If me3000CNTInterrupt(glBoardNumber, COUNTER3000_B, COUNTER3000_ENABLE, AddressOf CounterBInterruptHandler) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuCountBEnableInt.Checked = True
    End If
End Sub

Private Sub mnuCountBLoad_Click()
    If me3000CNTSetRange(glBoardNumber, COUNTER3000_B, glCNTEndValueB, glCNTStartValueB) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuCountBRead_Click()
    If me3000CNTRead(glBoardNumber, COUNTER3000_B, giCounterValue) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    Else
        SingleValueLabel.Caption = "Counter B = " + Str(giCounterValue)
    End If
End Sub

Private Sub mnuCountBReset_Click()
    If me3000CNTReset(glBoardNumber, COUNTER3000_B) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuCountBSetupEndValue_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "End Value"
    gDefault = Trim(Str(glCNTEndValueB))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glCNTEndValueB = CLng(gInputValue)
    End If
End Sub

Private Sub mnuCountBSetupStartValue_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "End Value"
    gDefault = Trim(Str(glCNTStartValueB))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glCNTStartValueB = CLng(gInputValue)
    End If
End Sub

Private Sub mnuCountBStart_Click()
    If me3000CNTStart(glBoardNumber, COUNTER3000_B) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDAC0_Click()
    mnuDAC0.Checked = True
    mnuDAC1.Checked = False
    mnuDAC2.Checked = False
    mnuDAC3.Checked = False
    glDACChannel = 0
End Sub

Private Sub mnuDAC1_Click()
    mnuDAC0.Checked = False
    mnuDAC1.Checked = True
    mnuDAC2.Checked = False
    mnuDAC3.Checked = False
    glDACChannel = 1
End Sub

Private Sub mnuDAC2_Click()
    mnuDAC0.Checked = False
    mnuDAC1.Checked = False
    mnuDAC2.Checked = True
    mnuDAC3.Checked = False
    glDACChannel = 2
End Sub

Private Sub mnuDAC3_Click()
    mnuDAC0.Checked = False
    mnuDAC1.Checked = False
    mnuDAC2.Checked = False
    mnuDAC3.Checked = True
    glDACChannel = 3
End Sub

Private Sub mnuDACBuffered_Click()
    mnuDACBuffered.Checked = True
    mnuDACTransparent.Checked = False
    glDACMode = AO3000_BUFFERED
End Sub

Private Sub mnuDACContiInt_Click()
    Dim i As Integer
    Dim iVal As Integer
    Dim dVal As Double
    ReDim DummyX(0 To 5) As Integer
        
    ' Calculate beautiful output values
    '----------------------------------------------------
    For i = 0 To glDACCount - 1
        dVal = 6.28318530718 / glDACCount * CDbl(i) * 5#
        iVal = CInt(2048# + 2048# * Cos(dVal))
        If iVal >= 4095 Then iVal = 4095

        piDACBuffer(i) = MAKE_DACFIFOENTRY(glDACChannel, iVal)
    Next i
    
    Call PlotDACData(DummyX, glDACCount)

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(gdDACFrequency))

    gbAOStop = True
    
    If meContinuousEx(glBoardNumber, AO3000_INTERRUPT, glDACCount, piDACBuffer(0), glDACLoops, glDACDelay, AddressOf AOContinuousHandler) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACContiPolling_Click()
    Dim i As Integer
    Dim iVal As Integer
    Dim dVal As Double
    ReDim DummyX(0 To 5) As Integer
        
    ' Calculate beautiful output values
    '----------------------------------------------------
    For i = 0 To glDACCount - 1
        dVal = 6.28318530718 / glDACCount * CDbl(i) * 5#
        iVal = CInt(2048# + 2048# * Sin(dVal))
        If iVal >= 4095 Then iVal = 4095

        piDACBuffer(i) = MAKE_DACFIFOENTRY(glDACChannel, iVal)
    Next i
    
    Call PlotDACData(DummyX, glDACCount)

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(gdDACFrequency))

    gbAOStop = True
    
    If me3000ContinuousEx(glBoardNumber, AO3000_POLLING, glDACCount, piDACBuffer(0), glDACLoops, glDACDelay, AddressOf AOContinuousHandler) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACCounter_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "DAC Counter"
    gDefault = Trim(Str(glDACCount))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glDACCount = CLng(gInputValue)
    End If
End Sub

Private Sub mnuDACDelay_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "DAC Delay"
    gDefault = Trim(Str(glDACDelay))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glDACDelay = CLng(gInputValue)
    End If
End Sub

Private Sub mnuDACFreq_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "Frequency"
    gDefault = Trim(Str(CLng(gdDACFrequency)))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        gdDACFrequency = CDbl(gInputValue)
    End If
End Sub

Private Sub mnuDACInterrupt_Click()
    Dim i As Integer
    Dim iVal As Integer
    Dim dVal As Double
    ReDim DummyX(0 To 5) As Integer
        
    ' Calculate beautiful output values
    '----------------------------------------------------
    For i = 0 To glDACCount
        dVal = 6.28318530718 / glDACCount * CDbl(i) * 5#
        iVal = CInt(2048# + 2048# * Sin(dVal))
        If iVal >= 4095 Then iVal = 4095

        piDACBuffer(i) = MAKE_DACFIFOENTRY(0, iVal)
    Next i
    
    Call PlotDACData(DummyX, glDACCount)

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(gdDACFrequency))

    gbAOStop = False
    
    If me3000AOContinuous(glBoardNumber, AO3000_INTERRUPT, glDACCount, piDACBuffer(0)) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACLoops_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "Loops Of Background Process"
    gDefault = Trim(Str(glDACLoops))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glDACLoops = CLng(gInputValue)
    End If
End Sub

Private Sub mnuDACPolling_Click()
    Dim i As Integer
    Dim iVal As Integer
    Dim dVal As Double
    ReDim DummyX(0 To 5) As Integer
        
    ' Calculate beautiful output values
    '----------------------------------------------------
    For i = 0 To glDACCount - 1
        dVal = 6.28318530718 / glDACCount * CDbl(i) * 5#
        iVal = CInt(2048# + 2048# * Sin(dVal))
        If iVal >= 4095 Then iVal = 4095

        piDACBuffer(i) = MAKE_DACFIFOENTRY(glDACChannel, iVal)
    Next i
    
    Call PlotDACData(DummyX, glDACCount)

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(gdDACFrequency))

    gbAOStop = False
    
    If me3000AOContinuous(glBoardNumber, AO3000_POLLING, glDACCount, piDACBuffer(0)) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACRangeMinus10_Click()
    mnuDACRangeMinus10.Checked = True
    mnuDACRangeMinus5.Checked = False
    mnuDACRangePlus.Checked = False
    glDACRange = AO3000_MINUS_10
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACRangeMinus5_Click()
    mnuDACRangeMinus10.Checked = False
    mnuDACRangeMinus5.Checked = True
    mnuDACRangePlus.Checked = False
    glDACRange = AO3000_MINUS_5
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACRangePlus_Click()
    mnuDACRangeMinus10.Checked = False
    mnuDACRangeMinus5.Checked = False
    mnuDACRangePlus.Checked = True
    glDACRange = AO3000_PLUS_10
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACReset_Click()
    If me3000AOReset(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuDACSingle_Click()
    Dim iValue As Integer
    
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "DAC output value"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        iValue = CInt(gInputValue)
        If me3000AOSingle(glBoardNumber, glDACChannel, iValue) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuDACSize_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "DAC FIFO Size"
    gDefault = Trim(Str(glDACSize))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glDACSize = CLng(gInputValue)
    End If
End Sub

Private Sub mnuDACStop_Click()
    If gbAOStop Then
        Call me3000AOStopEx(glBoardNumber)
    Else
        Call me3000AOStop(glBoardNumber)
        mnuDACWrapAround.Checked = False
    End If
End Sub

Private Sub mnuDACTransparent_Click()
    mnuDACBuffered.Checked = False
    mnuDACTransparent.Checked = True
    glDACMode = AO3000_TRANSPARENT
End Sub

Private Sub mnuDACTriggerHigh_Click()
    mnuDACTriggerTimer.Checked = False
    mnuDACTriggerHigh.Checked = True
    mnuDACTriggerLow.Checked = False
    glDACTrigger = AO3000_TRIGGER_EXT_HIGH
End Sub

Private Sub mnuDACTriggerLow_Click()
    mnuDACTriggerTimer.Checked = False
    mnuDACTriggerHigh.Checked = False
    mnuDACTriggerLow.Checked = True
    glDACTrigger = AO3000_TRIGGER_EXT_LOW
End Sub

Private Sub mnuDACTriggerTimer_Click()
    mnuDACTriggerTimer.Checked = True
    mnuDACTriggerHigh.Checked = False
    mnuDACTriggerLow.Checked = False
    glDACTrigger = AO3000_TRIGGER_TIMER
End Sub

Private Sub mnuDACUpdate_Click()
    If me3000AOUpdate(glBoardNumber) = 0 Then
        me3000ErrorMessage (AppName)
    End If
End Sub

Private Sub mnuDACWrapAround_Click()
    Dim i As Integer
    Dim lEntry As Long
    
    ' Clear the DAC FIFO
    '----------------------------------------------------
    If me3000AOClearDACFIFO(glBoardNumber) = 0 Then
        me3000ErrorMessage (AppName)
    End If
    
    ' Create the new DAC FIFO contents
    '----------------------------------------------------
    For i = 0 To glDACSize - 1
        lEntry = MAKE_DACFIFOENTRY(glDACChannel, CLng(4095# / glDACSize * i))
        If me3000AOAddToDACFIFO(glBoardNumber, lEntry) = 0 Then
            me3000ErrorMessage (AppName)
            Exit Sub
        End If
    Next i

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(glBoardNumber, glDACChannel, glDACRange, glDACMode) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(gdDACFrequency))

    ' Start automatic mode with wraparound
    '----------------------------------------------------
    gbAOStop = False

    If me3000AOWrapAround(glBoardNumber) = 0 Then
        me3000ErrorMessage (AppName)
    End If
    
    mnuDACWrapAround.Checked = True
End Sub

Private Sub mnuDifferentialMode_Click()
    If mnuDifferentialMode.Checked Then
        mnuDifferentialMode.Checked = False
        glADCMode = AI3000_SINGLE_ENDED
    Else
        mnuDifferentialMode.Checked = True
        glADCMode = AI3000_DIFFERENTIAL
    End If
End Sub

Private Sub mnuDIO_Click()
    frmDIO.Show
End Sub
Private Sub mnuDLLVersion_Click()
    MsgBox "ME3000 DLL Version: " + Hex(me3000GetDLLVersion()), vbInformation
End Sub

Private Sub mnuDriverStatus_Click()
     If me3000GetDriverStatus(glBoardNumber, gDriverStatus) = 0 Then
        Call me3000ErrorMessage(AppName)
     Else
        gsBigText = Chr(9) + "Driver status of board: " + Str(glBoardNumber) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Control1:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.Control1) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Control2:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.Control2) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Control3:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.Control3) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "IRQMask:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.IRQMask) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "ISRMask:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.ISRMask) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Status:" + Chr(9) + Chr(9) + "0x" + Hex(gDriverStatus.Status) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "DACStatus:" + Chr(9) + "0x" + Hex(gDriverStatus.DACStatus) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "DebugWord:" + Chr(9) + "0x" + Hex(gDriverStatus.DebugWord) + Chr(10) + Chr(13)
        MsgBox gsBigText, vbOKOnly
     End If
End Sub

Private Sub mnuDriverTimeStamp_Click()
    Call me3000GetDriverTimeStamp(gsTextBuffer)
    MsgBox "ME3000 Driver Time Stamp: " + gsTextBuffer, vbInformation
End Sub
Private Sub mnuDriverVersion_Click()
    Call me3000GetDriverVersion(gsTextBuffer)
    MsgBox "ME3000 Driver Version: " + gsTextBuffer, vbInformation
End Sub

Private Sub mnuEnableExternInterrupt_Click()
    If mnuEnableExternInterrupt.Checked Then
        If me3000DisableExternalInt(glBoardNumber) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        mnuEnableExternInterrupt.Checked = False
    Else
        If me3000EnableExternalInt(glBoardNumber, AddressOf ExternalInterruptHandler) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        mnuEnableExternInterrupt.Checked = True
    End If
End Sub

Private Sub mnuExit_Click()
    End
End Sub
Private Sub mnuGeneralReset_Click()
    If me3000GeneralReset(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuInitialize_Click()
    If me3000Initialize(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuInterruptCounter_Click()
    If me3000GetInterrupts(glBoardNumber, gInterrupts) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        gsBigText = Chr(9) + "Interrupt counter of board: " + Str(glBoardNumber) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "ISR:" + Chr(9) + Chr(9) + Str(gInterrupts.ISR) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "ADC FIFO half full:" + Chr(9) + Str(gInterrupts.AdcFifo) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Channel List:" + Chr(9) + Str(gInterrupts.ChanList) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Extern:" + Chr(9) + Chr(9) + Str(gInterrupts.Extern) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Counter A:" + Chr(9) + Chr(9) + Str(gInterrupts.CountA) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Counter B:" + Chr(9) + Chr(9) + Str(gInterrupts.CountB) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "UART:" + Chr(9) + Chr(9) + Str(gInterrupts.UART) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "DAC FIFO half full:" + Chr(9) + Str(gInterrupts.DacFifo) + Chr(10) + Chr(13)
        MsgBox gsBigText, vbOKOnly
    End If
End Sub

Private Sub mnuLoopbackTest_Click()
    Call me3000SIOSetup(glBoardNumber, 19200, 8, 1, AscB("N"))

    If me3000SIOLoopBackTest(glBoardNumber) = 0 Then
        MsgBox "SIO Loopback Test failed!"
    Else
        MsgBox "SIO Loopback Test passed!"
    End If
End Sub

Private Sub mnuMultipleContiInterrupt_Click()
    If MakeChannelList(glBoardNumber, 1) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIMultipleEx(glBoardNumber, piADCBuffer(0), glADCCount, AI3000_POLLING, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuMultipleContiPolling_Click()
    If MakeChannelList(glBoardNumber, 1) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIMultipleEx(glBoardNumber, piADCBuffer(0), glADCCount, AI3000_POLLING, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuMultipleInterrupt_Click()
    If MakeChannelList(glBoardNumber, 1) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIMultiple(glBoardNumber, piADCBuffer(0), glADCCount, AI3000_INTERRUPT) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCCount)
        End If
    End If
End Sub

Private Sub mnuMultiplePolling_Click()
    If MakeChannelList(glBoardNumber, 1) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIMultiple(glBoardNumber, piADCBuffer(0), glADCCount, AI3000_POLLING) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCCount)
        End If
    End If
End Sub

Private Sub mnuPCIConfiguration_Click()
    If me3000GetPCIConfiguration(glBoardNumber, gBoardData) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        gsBigText = Chr(9) + "PCI Configuration Data of Board: " + Str(glBoardNumber) + Chr(9) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Vendor ID:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.VendorID) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Device ID:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.DeviceID) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Command:" + Chr(9) + "0x" + Hex(gBoardData.Command) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Status:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Status) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Revision:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Revision) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Class:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Class(0)) + " " + Hex(gBoardData.Class(1)) + " " + Hex(gBoardData.Class(2)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "CacheSize:" + Chr(9) + "0x" + Hex(gBoardData.CacheSize) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Latency:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Latency) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "HeaderType:" + Chr(9) + "0x" + Hex(gBoardData.HeaderType) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Bist:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Bist) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "RT Regs (memory):" + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(0)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "RT Regs (port):" + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(1)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "XILINX:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(2)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "SIO:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(3)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "BaseAddr 4:" + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(4)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "BaseAddr 5:" + Chr(9) + "0x" + Hex(gBoardData.BaseAddr(5)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "CIS:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.Cis) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Sub Vendor ID:" + Chr(9) + "0x" + Hex(gBoardData.SubVendor) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Sub Device ID:" + Chr(9) + "0x" + Hex(gBoardData.SubSystem) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "ROMAddr:" + Chr(9) + Chr(9) + "0x" + Hex(gBoardData.ROMAddr) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Reserved 0:" + Chr(9) + "0x" + Hex(gBoardData.Reserved(0)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "Reserved 1:" + Chr(9) + "0x" + Hex(gBoardData.Reserved(1)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "INT:" + Chr(9) + Chr(9) + Trim(Str(gBoardData.IRQ)) + Chr(10) + Chr(13)
        gsBigText = gsBigText + Chr(9) + "IPin:" + Chr(9) + Chr(9) + Trim(Str(gBoardData.IPin)) + Chr(10) + Chr(13)
        MsgBox gsBigText, vbOKOnly
    End If

End Sub

Private Sub mnuPWMDutyCycle_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "PWM Duty Cycle"
    gDefault = Trim(Str(glPWMDutyCycle))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        glPWMDutyCycle = CLng(gInputValue)
    End If
End Sub

Private Sub mnuPWMFrequency_Click()
    gMessage = "Enter a integer value"   ' Set prompt.
    gTitle = "PWM Frequency"
    gDefault = Trim(Str(CLng(gdPWMFrequency)))
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        gdPWMFrequency = CDbl(gInputValue)
    End If
End Sub

Private Sub mnuPWMInverted_Click()
    If mnuPWMInverted.Checked Then
        mnuPWMInverted.Checked = False
        glPWMInverted = PWM3000_NORMAL
    Else
        mnuPWMInverted.Checked = True
        glPWMInverted = PWM3000_INVERTED
    End If
End Sub

Private Sub mnuPWMStart_Click()
    If mnuPWMStart.Checked Then
        mnuPWMStart.Checked = False
        me3000PWMStop (glBoardNumber)
    Else
        If me3000PWMSetMode(glBoardNumber, gdPWMFrequency, glPWMDutyCycle, glPWMInverted) = 0 Then
            me3000ErrorMessage (AppName)
            Exit Sub
        End If
        me3000PWMStart (glBoardNumber)
        mnuPWMStart.Checked = True
    End If
End Sub

Private Sub mnuQuickContiInt_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIQuickEx(glBoardNumber, piADCBuffer(0), glADCSize, AI3000_INTERRUPT, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuQuickContiPolling_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIQuickEx(glBoardNumber, piADCBuffer(0), glADCSize, AI3000_POLLING, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuQuickInterrupt_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIQuick(glBoardNumber, piADCBuffer(0), glADCSize, AI3000_INTERRUPT) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCSize)
        End If
    End If
End Sub

Private Sub mnuQuickPolling_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIQuick(glBoardNumber, piADCBuffer(0), glADCSize, AI3000_POLLING) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCSize)
        End If
    End If
End Sub

Private Sub mnuRangeMinus1_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = True
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_MINUS_1
End Sub

Private Sub mnuRangeMinus10_Click()
    mnuRangeMinus10.Checked = True
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_MINUS_10
End Sub

Private Sub mnuRangeMinus2_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = True
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_MINUS_2
End Sub

Private Sub mnuRangeMinus5_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = True
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_MINUS_5
End Sub

Private Sub mnuRangePlus1_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = True
    glADCRange = AI3000_PLUS_1
End Sub

Private Sub mnuRangePlus10_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = True
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_PLUS_10
End Sub

Private Sub mnuRangePlus2_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = False
    mnuRangePlus2.Checked = True
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_PLUS_2
End Sub

Private Sub mnuRangePlus5_Click()
    mnuRangeMinus10.Checked = False
    mnuRangeMinus5.Checked = False
    mnuRangeMinus2.Checked = False
    mnuRangeMinus1.Checked = False
    mnuRangePlus10.Checked = False
    mnuRangePlus5.Checked = True
    mnuRangePlus2.Checked = False
    mnuRangePlus1.Checked = False
    glADCRange = AI3000_PLUS_5
End Sub


Private Sub mnuReadRegisters_Click()
    gMessage = "Enter register 0 - 7"
    gTitle = "SIO Read Register"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        MsgBox "Reg " + Hex(CLng(gInputValue)) + " =  0x" + Hex(me3000SIOReadRegister(glBoardNumber, CLng(gInputValue)))
    End If
End Sub


Private Sub mnuScanContiInterrupt_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIScanEx(glBoardNumber, piADCBuffer(0), glADCSize, glADCCount, AI3000_INTERRUPT Or glScanToDisk Or glScanForEver, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuScanContiPolling_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        
        If me3000AIScanEx(glBoardNumber, piADCBuffer(0), glADCSize, glADCCount, AI3000_POLLING Or glScanToDisk, glADCLoops, glADCDelay, AddressOf PlotADCData) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
    End If
End Sub

Private Sub mnuScanForEver_Click()
    If mnuScanForEver.Checked Then
        mnuScanForEver.Checked = False
        glScanForEver = 0
    Else
        mnuScanForEver.Checked = True
        glScanForEver = AI3000_SCAN_INFINITE
    End If
End Sub

Private Sub mnuScanInterrupt_Click()
    If glScanForEver = AI3000_SCAN_INFINITE Then
        MsgBox "SCAN_INFINITE is not allowed!", vbCritical
        Exit Sub
    End If

    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIScan(glBoardNumber, piADCBuffer(0), glADCSize, glADCCount, AI3000_INTERRUPT Or glScanToDisk) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCCount * glADCSize)
        End If
    End If
End Sub

Private Sub mnuScanPolling_Click()
    If MakeChannelList(glBoardNumber, glADCSize) = 1 Then
        If me3000AISetTimer(glBoardNumber, 0, me3000FrequencyToCounter(gdADCFrequency)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(glBoardNumber, glADCTrigger Or glADCTriggerConti) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If BUFFER_SIZE < (glADCCount * glADCSize) Then
            MsgBox "Count * Size exceeds buffer size!", vbOKOnly
            Exit Sub
        End If
        If me3000AIScan(glBoardNumber, piADCBuffer(0), glADCSize, glADCCount, AI3000_POLLING Or glScanToDisk) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            Call PlotADCData(piADCBuffer, glADCCount * glADCSize)
        End If
    End If
End Sub

Private Sub mnuScanToDisk_Click()
    If mnuScanToDisk.Checked Then
        mnuScanToDisk.Checked = False
        glScanToDisk = 0
    Else
        mnuScanToDisk.Checked = True
        glScanToDisk = AI3000_SCAN_TO_DISK
    End If
End Sub

Private Sub mnuSelectBoard1_Click()
    mnuSelectBoard1.Checked = True
    mnuSelectBoard2.Checked = False
    mnuSelectBoard3.Checked = False
    mnuSelectBoard4.Checked = False
    glBoardNumber = 0
    Me.Caption = "ME3000 Test Application (VB 5.0) conneceted to board 0"
End Sub

Private Sub mnuSelectBoard2_Click()
    mnuSelectBoard1.Checked = False
    mnuSelectBoard2.Checked = True
    mnuSelectBoard3.Checked = False
    mnuSelectBoard4.Checked = False
    glBoardNumber = 1
    Me.Caption = "ME3000 Test Application (VB 5.0) conneceted to board 1"
End Sub

Private Sub mnuSelectBoard3_Click()
    mnuSelectBoard1.Checked = False
    mnuSelectBoard2.Checked = False
    mnuSelectBoard3.Checked = True
    mnuSelectBoard4.Checked = False
    glBoardNumber = 2
    Me.Caption = "ME3000 Test Application (VB 5.0) conneceted to board 2"
End Sub

Private Sub mnuSelectBoard4_Click()
    mnuSelectBoard1.Checked = False
    mnuSelectBoard2.Checked = False
    mnuSelectBoard3.Checked = False
    mnuSelectBoard4.Checked = True
    glBoardNumber = 3
    Me.Caption = "ME3000 Test Application (VB 5.0) conneceted to board 3"
End Sub

Private Sub mnuSerialNumber_Click()
    Dim lSerialNumber As Long
    
    If me3000GetSerialNumber(glBoardNumber, lSerialNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        MsgBox "Serial Number: " + Str(lSerialNumber), vbInformation
    End If
End Sub

Private Sub mnuSetPriority_Click()
    If mnuSetPriority.Checked Then
        If me3000SetPriority(glBoardNumber, PRIORITY_LOW) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuSetPriority.Checked = False
    Else
        If me3000SetPriority(glBoardNumber, PRIORITY_HIGH) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuSetPriority.Checked = True
    End If
End Sub

Private Sub mnuShowDataFile_Click()
    Dim l As Long
    Dim lPos As Long
    Dim iData As Integer
    
    SingleValueLabel.Caption = "Busy..."
    DoEvents
    
    If Dir(gsADCFile) = Empty Then
        MsgBox "ADC data file " + gsADCFile + " not found!", vbCritical
        SingleValueLabel.Caption = Empty
    Else
        Open gsADCFile For Binary Access Read As #1
    
        l = 0
        lPos = 1
        Do While Not EOF(1)
            Get #1, lPos, iData
            piADCBuffer(l) = iData Xor &H800
            l = l + 1
            lPos = lPos + 2
        Loop
        Close (1)
            
        Call PlotADCData(piADCBuffer, l - 1)
        SingleValueLabel.Caption = Str(l - 1)
    End If
End Sub

Private Sub mnuShowRegisters_Click()
    Dim s As String
    Dim Regs As ME3000_SIO_REGS
    
    If me3000SIOGetRegisters(glBoardNumber, Regs) = 0 Then
        me3000ErrorMessage ("VB3000")
    Else
        s = "SIO Registers of board " + Trim(Str(glBoardNumber)) + ":" + Chr(13) + Chr(10) + Chr(13) + Chr(10)
        s = s + "RHR:" + Chr(9) + " 0x" + Hex(Regs.RHR) + Chr(13) + Chr(10)
        s = s + "ICR:" + Chr(9) + " 0x" + Hex(Regs.IER) + Chr(13) + Chr(10)
        s = s + "FCR:" + Chr(9) + " 0x" + Hex(Regs.FCR) + Chr(13) + Chr(10)
        s = s + "LCR:" + Chr(9) + " 0x" + Hex(Regs.LCR) + Chr(13) + Chr(10)
        s = s + "MCR:" + Chr(9) + " 0x" + Hex(Regs.MCR) + Chr(13) + Chr(10)
        s = s + "LSR:" + Chr(9) + " 0x" + Hex(Regs.LSR) + Chr(13) + Chr(10)
        s = s + "MSR:" + Chr(9) + " 0x" + Hex(Regs.MSR) + Chr(13) + Chr(10)
        s = s + "SPR:" + Chr(9) + " 0x" + Hex(Regs.SPR) + Chr(13) + Chr(10)
        MsgBox s
    End If
End Sub

Private Sub mnuSimultaneousSampling_Click()
    If mnuSimultaneousSampling.Checked Then
        If me3000AISetSimultaneous(glBoardNumber, AI3000_DISABLE) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuSimultaneousSampling.Checked = False
    Else
        If me3000AISetSimultaneous(glBoardNumber, AI3000_ENABLE) = 0 Then
            Call me3000ErrorMessage(AppName)
            Exit Sub
        End If
        mnuSimultaneousSampling.Checked = True
    End If
End Sub

Private Sub mnuSingleConti_Click()
    If me3000AISingleEx(glBoardNumber, glADCChannel, glADCRange, glADCLoops, glADCDelay, giSingleValue, AddressOf AISingleHandler) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuSingleSingle_Click()
    Dim dValue As Double
    If me3000AISingle(glBoardNumber, glADCChannel, glADCRange, giSingleValue) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        dValue = giSingleValue * 0.00048828125 * gdHalfRange - gdADCOffset
        SingleValueLabel.Caption = "ADC " + Trim(Str(glADCChannel)) + ": " + Str(giSingleValue) + "  " + Str(dValue) + " [V]"
    End If
End Sub

Private Sub mnuSIOReceiveInt_Click()
    Dim Buffer As String * 256 ' size needed by SIOReceive!!!
    Dim Sio As ME3000_SIO
    Dim s As String

    gMessage = "Enter the number of characters to receive"
    gTitle = "SIO Receive (Interrupt)"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        If me3000SIOOpen(glBoardNumber, SIO_INTERRUPT Or SIO_RS485_HALF_DUPLEX, 1024&, 512&) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        Call me3000SIOSetup(glBoardNumber, 19200, 8, 1, AscB("N"))
        
        MsgBox "Now, we read " + gInputValue + " characters"
        
        If me3000SIOReceive(glBoardNumber, SIO_INTERRUPT, CLng(gInputValue), Buffer) = 0 Then
            me3000ErrorMessage ("VB3000")
        Else
            MsgBox Buffer
        End If
        
        If me3000SIOClose(glBoardNumber) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        
    End If
End Sub

Private Sub mnuSIOReceivePoll_Click()
    Dim Buffer As String * 256 ' size needed by SIOReceive!!!

    gMessage = "Enter the number of characters to receive"
    gTitle = "SIO Receive (Polling)"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        If me3000SIOOpen(glBoardNumber, SIO_POLLING Or SIO_RS485_HALF_DUPLEX, 0, 0) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        Call me3000SIOSetup(glBoardNumber, 19200, 8, 1, AscB("N"))
        If me3000SIOReceive(glBoardNumber, SIO_POLLING, CLng(gInputValue), Buffer) = 0 Then
            me3000ErrorMessage ("VB3000")
        Else
            MsgBox Buffer
        End If
    End If
End Sub

Private Sub mnuSIORS422_Click()
    mnuSIORS422.Checked = True
    mnuSIORS485HALF.Checked = False
    glRS485Mode = 0
End Sub

Private Sub mnuSIORS485HALF_Click()
    mnuSIORS422.Checked = False
    mnuSIORS485HALF.Checked = True
    glRS485Mode = SIO_RS485_HALF_DUPLEX
End Sub

Private Sub mnuSIOTransmitPoll_Click()
    Dim Buffer As String
    Dim l As Long
    
    gMessage = "Enter the outout string"
    gTitle = "SIO Transmit (Polling)"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        Buffer = gInputValue
        l = Len(Buffer)
        
        If me3000SIOOpen(glBoardNumber, SIO_POLLING Or SIO_RS485_HALF_DUPLEX, 0, 0) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        
        Call me3000SIOSetup(glBoardNumber, 19200, 8, 1, AscB("N"))
        
        If me3000SIOTransmit(glBoardNumber, SIO_POLLING, l, Buffer) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
    End If
End Sub

Private Sub mnuStopADC_Click()
    If me3000AIStop(glBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End Sub

Private Sub mnuTransmitInt_Click()
    Dim Buffer As String
    Dim Sio As ME3000_SIO
    Dim s As String
    Dim l As Long
    

    gMessage = "Enter the outout string"
    gTitle = "SIO Transmit (Interrupt)"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        Buffer = gInputValue
        l = Len(Buffer)
        If me3000SIOOpen(glBoardNumber, SIO_INTERRUPT Or SIO_RS485_HALF_DUPLEX, 1024&, 512&) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        Call me3000SIOSetup(glBoardNumber, 19200, 8, 1, AscB("N"))
        If me3000SIOTransmit(glBoardNumber, SIO_INTERRUPT, l, Buffer) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
        
        If me3000SIOCheckBuffer(glBoardNumber, Sio) = 0 Then
            me3000ErrorMessage ("VB3000")
        Else
            While (Sio.OutBufferCount > 0)
                Call me3000SIOCheckBuffer(glBoardNumber, Sio)
            Wend
            s = "SIO Buffer of Board " + Trim(Str(glBoardNumber)) + ":" + Chr(13) + Chr(10) + Chr(13) + Chr(10)
            s = s + "InBufferSize:" + Chr(9) + Str(Sio.InBufferSize) + Chr(13) + Chr(10)
            s = s + "InBufferCount:" + Chr(9) + Str(Sio.InBufferCount) + Chr(13) + Chr(10)
            s = s + "InBufferReadPointer" + Chr(9) + Str(Sio.InBufferReadPointer) + Chr(13) + Chr(10)
            s = s + "InBufferWritePointer:" + Chr(9) + Str(Sio.InBufferWritePointer) + Chr(13) + Chr(10)
            s = s + "InBufferOverwrite:" + Chr(9) + Str(Sio.InBufferOverwrite) + Chr(13) + Chr(10)
            s = s + "InStop:" + Chr(9) + Chr(9) + Str(Sio.InStop) + Chr(13) + Chr(10)
            s = s + "InError:" + Chr(9) + Chr(9) + Str(Sio.InError) + Chr(13) + Chr(10)
            s = s + "OutBufferSize:" + Chr(9) + Str(Sio.OutBufferSize) + Chr(13) + Chr(10)
            s = s + "OutBufferCount:" + Chr(9) + Str(Sio.OutBufferCount) + Chr(13) + Chr(10)
            s = s + "OutBufferEndPointer:" + Chr(9) + Str(Sio.OutBufferEndPointer) + Chr(13) + Chr(10)
            s = s + "OutError:" + Chr(9) + Chr(9) + Str(Sio.OutError) + Chr(13) + Chr(10)
            MsgBox s
        End If
        If me3000SIOClose(glBoardNumber) = 0 Then
            me3000ErrorMessage ("VB3000")
        End If
    End If

End Sub

Private Sub mnuVECModel_Click()
    Dim lMEVECModel As Long
    
    If me3000GetVECModel(glBoardNumber, lMEVECModel) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        MsgBox "MEVEC Model: " + Str(lMEVECModel), vbInformation
    End If
End Sub
Function MakeChannelList(ByVal lNo As Long, ByVal lCount As Long) As Long
    Dim i As Integer
    Dim lEntry As Long
            
    ' Clear the current channel list
    '----------------------------------------------------
    Call me3000AIClearChannelList(lNo)

    ' Write n channel list entries to the board
    '----------------------------------------------------
    For i = 0 To lCount - 1
    
        If me3000AIMakeChannelListEntry(glADCChannel, glADCRange, glADCMode, lEntry) = 0 Then
            Call me3000ErrorMessage(AppName)
            MakeChannelList = 0
        End If
    
        If me3000AIAddToChannelList(lNo, lEntry) = 0 Then
            me3000ErrorMessage (AppName)
            MakeChannelList = 0
        End If
        
    Next i
    MakeChannelList = 1
End Function

Private Sub mnuWriteRegisters_Click()
    Dim cReg As Byte
    Dim cVal As Byte
    Dim l As Long
    
    gMessage = "Enter register (0 - 7) and value"
    gTitle = "SIO Write Register"
    gDefault = ""
    ' Display message, title, and default value.
    gInputValue = InputBox(gMessage, gTitle, gDefault)
    If gInputValue <> "" Then
        l = InStr(gInputValue, " ")
        cReg = CByte(Val(Mid$(gInputValue, 1, l)))
        l = InStr(gInputValue, " ")
        cVal = CByte(Val("&h" + Mid$(gInputValue, l + 1)))
        MsgBox "Reg " + Hex(cReg) + " =  0x" + Hex(me3000SIOWriteRegister(glBoardNumber, cReg, cVal))
    End If
    
End Sub

Private Sub PlotArea_Click()

End Sub
