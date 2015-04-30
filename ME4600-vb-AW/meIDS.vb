'==============================================================================
'Copyright(c), Meilhaus Electronic GmbH
'              http://www.meilhaus.de
'              support@meilhaus.de
'
'Source File : meIDS.vb
'Description : Constants, types and function prototypes of the ME-iDS API 
'              for accessing the API in Visual Basic .NET 
'              
'Important   : This file uses the CallingConvention.Cdecl of the ME-iDS API
'Note        : import library for ME-iDS API 32bit: meIDSmain.dll
'              import library for ME-iDS API 64bit: meIDSmain64.dll
'==============================================================================
Option Strict Off
Option Explicit On

Imports System.Runtime.InteropServices
Imports System.Text

Module Module1
    '---------------------------------------------------------------
    '                                                               
    ' me-iDS Constants                  
    '                                                               
    '---------------------------------------------------------------

    Public NotInheritable Class meIDS

#Region "Constants"
        '===============================================================
        '  General
        '===============================================================

        Public Const ME_VALUE_NOT_USED As Integer = &H0S

        Public Const ME_VALUE_DEFAULT As Integer = &H0S

        Public Const ME_NO_FLAGS As Integer = &H0S
        
        Public Const ME_VALUE_INVALID As Integer = -1

        '===============================================================
        '  Defines common to access functions
        '===============================================================

        Public Const ME_LOCK_RELEASE As Integer = &H10001
        Public Const ME_LOCK_SET As Integer = &H10002
        Public Const ME_LOCK_CHECK As Integer = &H10003

        '===============================================================
        '  Defines meOpen function
        '===============================================================

        Public Const ME_OPEN_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines meClose function
        '===============================================================

        Public Const ME_CLOSE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines meLockDriver function
        '===============================================================

        Public Const ME_LOCK_DRIVER_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines meLockDevice function
        '===============================================================

        Public Const ME_LOCK_DEVICE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines meLockSubdevice function
        '===============================================================

        Public Const ME_LOCK_SUBDEVICE_NO_FLAGS As Integer = &H0S


        '===============================================================
        '  Defines common to error functions
        '===============================================================

        Public Const ME_ERROR_MSG_MAX_COUNT As Integer = 256

        '===============================================================
        '  Defines for meErrorSetDefaultProc function
        '===============================================================

        Public Const ME_SWITCH_DISABLE As Integer = &H20001
        Public Const ME_SWITCH_ENABLE As Integer = &H20002

        '==================================================================
        '  Defines for meErrorGetLast function
        '==================================================================

        Public Const ME_ERROR_GET_LAST_NO_FLAGS As Integer = &H0
        Public Const ME_ERROR_GET_LAST_CLEAR As Integer = &H1

        '===============================================================
        '  Defines common to io functions
        '===============================================================

        Public Const ME_REF_NONE As Integer = &H0
        Public Const ME_REF_DIO_FIFO_LOW As Integer = &H30001
        Public Const ME_REF_DIO_FIFO_HIGH As Integer = &H30002

        Public Const ME_REF_CTR_PREVIOUS As Integer = &H40001
        Public Const ME_REF_CTR_INTERNAL_1MHZ As Integer = &H40002
        Public Const ME_REF_CTR_INTERNAL_10MHZ As Integer = &H40003
        Public Const ME_REF_CTR_EXTERNAL As Integer = &H40004

        Public Const ME_REF_AI_GROUND As Integer = &H50001
        Public Const ME_REF_AI_DIFFERENTIAL As Integer = &H50002

        Public Const ME_REF_AO_GROUND As Integer = &H60001
        Public Const ME_REF_AO_DIFFERENTIAL As Integer = &H60002

        Public Const ME_TRIG_CHAN_NONE As Integer = ME_VALUE_NOT_USED
        Public Const ME_TRIG_CHAN_DEFAULT As Integer = &H70001
        Public Const ME_TRIG_CHAN_SYNCHRONOUS As Integer = &H70002

        Public Const ME_TRIG_TYPE_NONE As Integer = ME_VALUE_NOT_USED
        Public Const ME_TRIG_TYPE_SW As Integer = &H80001
        Public Const ME_TRIG_TYPE_THRESHOLD As Integer = &H80002
        Public Const ME_TRIG_TYPE_WINDOW As Integer = &H80003
        Public Const ME_TRIG_TYPE_EDGE As Integer = &H80004
        Public Const ME_TRIG_TYPE_SLOPE As Integer = &H80005
        Public Const ME_TRIG_TYPE_EXT_DIGITAL As Integer = &H80006
        Public Const ME_TRIG_TYPE_EXT_ANALOG As Integer = &H80007
        Public Const ME_TRIG_TYPE_PATTERN As Integer = &H80008          ' These two defines are the same
        Public Const ME_TRIG_TYPE_PATTERN_MATCH As Integer = &H80008    ' to preserve compatibility
        Public Const ME_TRIG_TYPE_TIMER As Integer = &H80009
        Public Const ME_TRIG_TYPE_COUNT As Integer = &H8000A
        Public Const ME_TRIG_TYPE_FOLLOW As Integer = &H8000B
        Public Const ME_TRIG_TYPE_PATTERN_NO_MATCH As Integer = &H8000C
        Public Const ME_TRIG_TYPE_EXT_DIGITAL_OR_COUNT As Integer = &H8000D
        Public Const ME_TRIG_TYPE_PATTERN_MATCH_OR_COUNT As Integer = &H8000E
        Public Const ME_TRIG_TYPE_PATTERN_NO_MATCH_OR_COUNT As Integer = &H8000F

        Public Const ME_TRIG_EDGE_NONE As Integer = ME_VALUE_NOT_USED
        Public Const ME_TRIG_EDGE_ABOVE As Integer = &H90001
        Public Const ME_TRIG_EDGE_BELOW As Integer = &H90002
        Public Const ME_TRIG_EDGE_ENTRY As Integer = &H90003
        Public Const ME_TRIG_EDGE_EXIT As Integer = &H90004
        Public Const ME_TRIG_EDGE_RISING As Integer = &H90005
        Public Const ME_TRIG_EDGE_FALLING As Integer = &H90006
        Public Const ME_TRIG_EDGE_ANY As Integer = &H90007

        Public Const ME_TIMER_ACQ_START As Integer = &HA0001
        Public Const ME_TIMER_SCAN_START As Integer = &HA0002
        Public Const ME_TIMER_CONV_START As Integer = &HA0003
        Public Const ME_TIMER_FIO_TOTAL As Integer = &HA0004
        Public Const ME_TIMER_FIO_FIRST_PHASE As Integer = &HA0005

        '===============================================================
        '  Defines for meIOFrequencyToTicks function
        '===============================================================

        Public Const ME_IO_FREQUENCY_TO_TICKS_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_FREQUENCY_TO_TICKS_NO_FLAGS = ME_IO_FREQUENCY_TO_TICKS_NO_FLAGS
        Public Const ME_IO_FREQUENCY_TO_TICKS_MEPHISTO_SCOPE_OSCILLOSCOPE As Integer = &H1S

        '===============================================================
        '  Defines for meIOIrqStart function
        '===============================================================

        Public Const ME_IRQ_SOURCE_DIO_PATTERN As Integer = &HB0001
        Public Const ME_IRQ_SOURCE_DIO_MASK As Integer = &HB0002
        Public Const ME_IRQ_SOURCE_DIO_LINE As Integer = &HB0003
        Public Const ME_IRQ_SOURCE_DIO_OVER_TEMP As Integer = &HB0004
        Public Const ME_IRQ_SOURCE_DIO_NORMAL_TEMP As Integer = &HB0005
        Public Const ME_IRQ_SOURCE_DIO_CHANGE_TEMP As Integer = &HB0006

        Public Const ME_IRQ_EDGE_NOT_USED As Integer = ME_VALUE_NOT_USED
        Public Const ME_IRQ_EDGE_RISING As Integer = &HC0001
        Public Const ME_IRQ_EDGE_FALLING As Integer = &HC0002
        Public Const ME_IRQ_EDGE_ANY As Integer = &HC0003

        Public Const ME_IO_IRQ_START_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_IRQ_START_DIO_BIT As Integer = &H1S
        Public Const ME_IO_IRQ_START_DIO_BYTE As Integer = &H2S
        Public Const ME_IO_IRQ_START_DIO_WORD As Integer = &H4S
        Public Const ME_IO_IRQ_START_DIO_DWORD As Integer = &H8S
        Public Const ME_IO_IRQ_START_PATTERN_FILTERING As Integer = &H10S
        Public Const ME_IO_IRQ_START_EXTENDED_STATUS As Integer = &H20S
        Public Const ME_IO_IRQ_START_USE_PROPERTIES As Integer = &H40000000

        '===============================================================
        '  Defines for meIOIrqWait function
        '===============================================================

        Public Const ME_IO_IRQ_WAIT_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_IRQ_WAIT_NORMAL_STATUS As Integer = &H1S
        Public Const ME_IO_IRQ_WAIT_EXTENDED_STATUS As Integer = &H2S

        '===============================================================
        '  Defines for meIOIrqStop function
        '===============================================================

        Public Const ME_IO_IRQ_STOP_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOIrqSetCallback function
        '===============================================================

        Public Const ME_IO_IRQ_SET_CALLBACK_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOResetDevice function
        '===============================================================

        Public Const ME_IO_RESET_DEVICE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOResetSubdevice function
        '===============================================================

        Public Const ME_IO_RESET_SUBDEVICE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOSingleConfig function
        '===============================================================

        Public Const ME_SINGLE_CONFIG_DIO_INPUT As Integer = &HD0001
        Public Const ME_SINGLE_CONFIG_DIO_OUTPUT As Integer = &HD0002
        Public Const ME_SINGLE_CONFIG_DIO_HIGH_IMPEDANCE As Integer = &HD0003
        Public Const ME_SINGLE_CONFIG_DIO_SINK As Integer = &HD0004
        Public Const ME_SINGLE_CONFIG_DIO_SOURCE As Integer = &HD0005
        Public Const ME_SINGLE_CONFIG_DIO_MUX32M As Integer = &HD0006
        Public Const ME_SINGLE_CONFIG_DIO_DEMUX32 As Integer = &HD0007
        Public Const ME_SINGLE_CONFIG_DIO_BIT_PATTERN As Integer = &HD0008

        Public Const ME_SINGLE_CONFIG_FIO_INPUT As Integer = &H1E0001
        Public Const ME_SINGLE_CONFIG_FIO_OUTPUT As Integer = &H1E0002
        Public Const ME_SINGLE_CONFIG_FIO_HIGH_IMPEDANCE As Integer = &H1E0002
        Public Const ME_SINGLE_CONFIG_FIO_SINK As Integer = &H1E0003
        Public Const ME_SINGLE_CONFIG_FIO_SOURCE As Integer = &H1E0004

        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_0 As Integer = &HE0001
        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_1 As Integer = &HE0002
        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_2 As Integer = &HE0003
        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_3 As Integer = &HE0004
        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_4 As Integer = &HE0005
        Public Const ME_SINGLE_CONFIG_CTR_8254_MODE_5 As Integer = &HE0006

        Public Const ME_IO_SINGLE_CONFIG_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_SINGLE_CONFIG_DIO_BIT As Integer = &H1S
        Public Const ME_IO_SINGLE_CONFIG_DIO_BYTE As Integer = &H2S
        Public Const ME_IO_SINGLE_CONFIG_DIO_WORD As Integer = &H4S
        Public Const ME_IO_SINGLE_CONFIG_DIO_DWORD As Integer = &H8S
        Public Const ME_IO_SINGLE_CONFIG_MULTISIG_LED_ON As Integer = &H10S
        Public Const ME_IO_SINGLE_CONFIG_MULTISIG_LED_OFF As Integer = &H20S
        Public Const ME_IO_SINGLE_CONFIG_AI_RMS As Integer = &H40S

        '===============================================================
        '  Defines for meIOSingle function
        '===============================================================

        Public Const ME_IO_SINGLE_NO_FLAGS As Integer = &H0S

        Public Const ME_DIR_INPUT As Integer = &HF0001
        Public Const ME_DIR_OUTPUT As Integer = &HF0002
        Public Const ME_DIR_SET_OFFSET As Integer = &HF0003

        Public Const ME_IO_SINGLE_TYPE_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_SINGLE_TYPE_DIO_BIT As Integer = &H1S
        Public Const ME_IO_SINGLE_TYPE_DIO_BYTE As Integer = &H2S
        Public Const ME_IO_SINGLE_TYPE_DIO_WORD As Integer = &H4S
        Public Const ME_IO_SINGLE_TYPE_DIO_DWORD As Integer = &H8S
        Public Const ME_IO_SINGLE_TYPE_TRIG_SYNCHRONOUS As Integer = &H10S
        Public Const ME_IO_SINGLE_TYPE_NONBLOCKING As Integer = &H20
        Public Const ME_IO_SINGLE_TYPE_WRITE_NONBLOCKING As Integer = ME_IO_SINGLE_TYPE_NONBLOCKING
        Public Const ME_IO_SINGLE_TYPE_READ_NONBLOCKING As Integer = ME_IO_SINGLE_TYPE_NONBLOCKING

        Public Const ME_IO_SINGLE_TYPE_FIO_DIVIDER As Integer = &H40
        Public Const ME_IO_SINGLE_TYPE_FO_START_LOW As Integer = &H80
        Public Const ME_IO_SINGLE_TYPE_FO_START_SOFT As Integer = &H100
        Public Const ME_IO_SINGLE_TYPE_FI_LAST_VALUE As Integer = &H200
        Public Const ME_IO_SINGLE_TYPE_FO_UPDATE_ONLY As Integer = &H200
        Public Const ME_IO_SINGLE_TYPE_FIO_TICKS_TOTAL As Integer = &H400
        Public Const ME_IO_SINGLE_TYPE_FIO_TICKS_FIRST_PHASE As Integer = &H800
        Public Const ME_IO_SINGLE_TYPE_FO_USE_PROPERTIES As Integer = &H40000000

        '==================================================================
        '  Defines for meIOSingleTimeToTicks function
        '==================================================================

        Public Const ME_IO_SINGLE_TIME_TO_TICKS_NO_FLAGS As Integer = &H0S

        '==================================================================
        '  Defines for meIOSingleTicksToTime function
        '==================================================================

        Public Const ME_IO_SINGLE_TICKS_TO_TIME_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOSetChannelOffset function
        '===============================================================

        Public Const ME_IO_SET_CHANNEL_OFFSET_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamConfig function
        '===============================================================

        Public Const ME_IO_STREAM_CONFIG_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_CONFIG_BIT_PATTERN As Integer = &H1S
        Public Const ME_IO_STREAM_CONFIG_WRAPAROUND As Integer = &H2S
        Public Const ME_IO_STREAM_CONFIG_SAMPLE_AND_HOLD As Integer = &H4S

        Public Const ME_IO_STREAM_CONFIG_INTERNAL_COUNTER As Integer = &H80000000

        Public Const ME_IO_STREAM_CONFIG_TYPE_NO_FLAGS As Integer = &H0S

        Public Const ME_IO_STREAM_TRIGGER_TYPE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamRead function
        '===============================================================

        Public Const ME_READ_MODE_BLOCKING As Integer = &H100001
        Public Const ME_READ_MODE_NONBLOCKING As Integer = &H100002

        Public Const ME_IO_STREAM_READ_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_READ_FRAMES As Integer = &H1S

        '===============================================================
        '  Defines for meIOStreamWrite function
        '===============================================================

        Public Const ME_WRITE_MODE_BLOCKING As Integer = &H110001
        Public Const ME_WRITE_MODE_NONBLOCKING As Integer = &H110002
        Public Const ME_WRITE_MODE_PRELOAD As Integer = &H110003

        Public Const ME_IO_STREAM_WRITE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamStart function
        '===============================================================

        Public Const ME_IO_STREAM_START_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_START_NONBLOCKING As Integer = &H20S

        Public Const ME_START_MODE_BLOCKING As Integer = &H120001
        Public Const ME_START_MODE_NONBLOCKING As Integer = &H120002

        Public Const ME_IO_STREAM_START_TYPE_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_START_TYPE_TRIG_SYNCHRONOUS As Integer = &H1S

        '===============================================================
        '  Defines for meIOStreamStop function
        '===============================================================

        Public Const ME_IO_STREAM_STOP_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_STOP_NONBLOCKING As Integer = &H20S

        Public Const ME_STOP_MODE_IMMEDIATE As Integer = &H130001
        Public Const ME_STOP_MODE_LAST_VALUE As Integer = &H130002

        Public Const ME_IO_STREAM_STOP_TYPE_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamStatus function
        '===============================================================

        Public Const ME_WAIT_NONE As Integer = &H140001
        Public Const ME_WAIT_IDLE As Integer = &H140002
        Public Const ME_WAIT_BUSY As Integer = &H140003

        Public Const ME_STATUS_INVALID As Integer = &H0S
        Public Const ME_STATUS_IDLE As Integer = &H150001
        Public Const ME_STATUS_BUSY As Integer = &H150002
        Public Const ME_STATUS_ERROR As Integer = &H150003

        Public Const ME_IO_STREAM_STATUS_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamSetCallbacks function
        '===============================================================

        Public Const ME_IO_STREAM_SET_CALLBACKS_NO_FLAGS As Integer = &H0S

        '===============================================================
        '  Defines for meIOStreamTimeToTicks function
        '===============================================================

        Public Const ME_IO_TIME_TO_TICKS_NO_FLAGS As Integer = &H0S
        Public Const ME_IO_STREAM_TIME_TO_TICKS_NO_FLAGS = ME_IO_TIME_TO_TICKS_NO_FLAGS
        Public Const ME_IO_TIME_TO_TICKS_MEPHISTO_SCOPE_OSCILLOSCOPE As Integer = &H1S

        '===============================================================
        '  Defines for module types
        '===============================================================

        Public Const ME_MODULE_TYPE_MULTISIG_NONE As Integer = &H0S
        Public Const ME_MODULE_TYPE_MULTISIG_DIFF16_10V As Integer = &H160001
        Public Const ME_MODULE_TYPE_MULTISIG_DIFF16_20V As Integer = &H160002
        Public Const ME_MODULE_TYPE_MULTISIG_DIFF16_50V As Integer = &H160003
        Public Const ME_MODULE_TYPE_MULTISIG_CURRENT16_0_20MA As Integer = &H160004
        Public Const ME_MODULE_TYPE_MULTISIG_RTD8_PT100 As Integer = &H160005
        Public Const ME_MODULE_TYPE_MULTISIG_RTD8_PT500 As Integer = &H160006
        Public Const ME_MODULE_TYPE_MULTISIG_RTD8_PT1000 As Integer = &H160007
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_B As Integer = &H160008
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_E As Integer = &H160009
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_J As Integer = &H16000A
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_K As Integer = &H16000B
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_N As Integer = &H16000C
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_R As Integer = &H16000D
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_S As Integer = &H16000E
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TYPE_T As Integer = &H16000F
        Public Const ME_MODULE_TYPE_MULTISIG_TE8_TEMP_SENSOR As Integer = &H160010

        '===============================================================
        '  Defines for meQuerySubdeviceCaps function
        '===============================================================

        Public Const ME_CAPS_DIO_DIR_BIT As Integer = &H1S
        Public Const ME_CAPS_DIO_DIR_BYTE As Integer = &H2S
        Public Const ME_CAPS_DIO_DIR_WORD As Integer = &H4S
        Public Const ME_CAPS_DIO_DIR_DWORD As Integer = &H8S
        Public Const ME_CAPS_DIO_SINK_SOURCE As Integer = &H10S
        Public Const ME_CAPS_DIO_BIT_PATTERN_IRQ As Integer = &H20S
        Public Const ME_CAPS_DIO_BIT_MASK_IRQ_EDGE_RISING As Integer = &H40S
        Public Const ME_CAPS_DIO_BIT_MASK_IRQ_EDGE_FALLING As Integer = &H80S
        Public Const ME_CAPS_DIO_BIT_MASK_IRQ_EDGE_ANY As Integer = &H100S
        Public Const ME_CAPS_DIO_OVER_TEMP_IRQ As Integer = &H200S
        Public Const ME_CAPS_DIO_NORMAL_TEMP_IRQ As Integer = &H400S

        Public Const ME_CAPS_CTR_CLK_PREVIOUS As Integer = &H1S
        Public Const ME_CAPS_CTR_CLK_INTERNAL_1MHZ As Integer = &H2S
        Public Const ME_CAPS_CTR_CLK_INTERNAL_10MHZ As Integer = &H4S
        Public Const ME_CAPS_CTR_CLK_EXTERNAL As Integer = &H8S

        Public Const ME_CAPS_AI_TRIG_SIMULTANEOUS As Integer = &H1S
        Public Const ME_CAPS_AI_FIFO As Integer = &H2S
        Public Const ME_CAPS_AI_FIFO_THRESHOLD As Integer = &H4S
        Public Const ME_CAPS_AI_SAMPLE_HOLD As Integer = &H8S

        Public Const ME_CAPS_AO_TRIG_SIMULTANEOUS As Integer = &H1S
        Public Const ME_CAPS_AO_FIFO As Integer = &H2S
        Public Const ME_CAPS_AO_FIFO_THRESHOLD As Integer = &H4S

        Public Const ME_CAPS_FIO_SINK_SOURCE As Integer = &H10S

        Public Const ME_CAPS_EXT_IRQ_EDGE_RISING As Integer = &H1S
        Public Const ME_CAPS_EXT_IRQ_EDGE_FALLING As Integer = &H2S
        Public Const ME_CAPS_EXT_IRQ_EDGE_ANY As Integer = &H4S

        '===============================================================
        '  Defines for meQuerySubdeviceCapsArgs function
        '===============================================================

        Public Const ME_CAP_AI_FIFO_SIZE As Integer = &H1D0000
        Public Const ME_CAP_AI_BUFFER_SIZE As Integer = &H1D0001
        Public Const ME_CAP_AI_CHANNEL_LIST_SIZE As Integer = &H1D0002
        Public Const ME_CAP_AI_MAX_THRESHOLD_SIZE As Integer = &H1D0003

        Public Const ME_CAP_AO_FIFO_SIZE As Integer = &H1F0000
        Public Const ME_CAP_AO_BUFFER_SIZE As Integer = &H1F0001
        Public Const ME_CAP_AO_CHANNEL_LIST_SIZE As Integer = &H1F0002
        Public Const ME_CAP_AO_MAX_THRESHOLD_SIZE As Integer = &H1F0003

        Public Const ME_CAP_CTR_WIDTH As Integer = &H200000

        Public Const ME_CAP_FPGA_IN_FIFO_SIZE As Integer = &H300000
        Public Const ME_CAP_FPGA_IN_BUFFER_SIZE As Integer = &H300001
        Public Const ME_CAP_FPGA_OUT_FIFO_SIZE As Integer = &H300002
        Public Const ME_CAP_FPGA_OUT_BUFFER_SIZE As Integer = &H300003

        '===============================================================
        '  Defines common to query functions
        '===============================================================

        Public Const ME_UNIT_INVALID As Integer = &H0S
        Public Const ME_UNIT_VOLT As Integer = &H170001
        Public Const ME_UNIT_AMPERE As Integer = &H170002
        Public Const ME_UNIT_ANY As Integer = &H170003
        Public Const ME_UNIT_HZ As Integer = &H170004

        Public Const ME_TYPE_INVALID As Integer = &H0S
        Public Const ME_TYPE_AO As Integer = &H180001
        Public Const ME_TYPE_AI As Integer = &H180002
        Public Const ME_TYPE_DIO As Integer = &H180003
        Public Const ME_TYPE_DO As Integer = &H180004
        Public Const ME_TYPE_DI As Integer = &H180005
        Public Const ME_TYPE_CTR As Integer = &H180006
        Public Const ME_TYPE_EXT_IRQ As Integer = &H180007
        Public Const ME_TYPE_FIO As Integer = &H180008
        Public Const ME_TYPE_FO As Integer = &H180009
        Public Const ME_TYPE_FI As Integer = &H18000A
        Public Const ME_TYPE_FPGA As Integer = &H18000B

        Public Const ME_SUBTYPE_INVALID As Integer = &H0S
        Public Const ME_SUBTYPE_SINGLE As Integer = &H190001
        Public Const ME_SUBTYPE_STREAMING As Integer = &H190002
        Public Const ME_SUBTYPE_CTR_8254 As Integer = &H190003
        Public Const ME_SUBTYPE_ANY As Integer = &H190004
        Public Const ME_SUBTYPE_CTR As Integer = &H190006

        Public Const ME_DEVICE_DRIVER_NAME_MAX_COUNT As Integer = 64
        Public Const ME_DEVICE_NAME_MAX_COUNT As Integer = 64

        Public Const ME_DEVICE_DESCRIPTION_MAX_COUNT As Integer = 256

        Public Const ME_BUS_TYPE_INVALID As Integer = &H0S
        Public Const ME_BUS_TYPE_ANY As Integer = &H1A0000    'ME_BUS_TYPE_ANY only for checking bus
        Public Const ME_BUS_TYPE_PCI As Integer = &H1A0001
        Public Const ME_BUS_TYPE_USB As Integer = &H1A0002
        Public Const ME_BUS_TYPE_LAN_PCI As Integer = &H1A0101
        Public Const ME_BUS_TYPE_LAN_USB As Integer = &H1A0102

        Public Const ME_PLUGGED_INVALID As Integer = &H0S
        Public Const ME_PLUGGED_ANY As Integer = &H1B0000     'ME_PLUGGED_ANY only for checking status
        Public Const ME_PLUGGED_IN As Integer = &H1B0001
        Public Const ME_PLUGGED_OUT As Integer = &H1B0002

        Public Const ME_EXTENSION_TYPE_INVALID As Integer = &H0S
        Public Const ME_EXTENSION_TYPE_NONE As Integer = &H1C0001
        Public Const ME_EXTENSION_TYPE_MUX32M As Integer = &H1C0002
        Public Const ME_EXTENSION_TYPE_DEMUX32 As Integer = &H1C0003
        Public Const ME_EXTENSION_TYPE_MUX32S As Integer = &H1C0004
        Public Const ME_EXTENSION_TYPE_ME1001 As Integer = &H1C0005

        Public Const ME_ACCESS_TYPE_INVALID As Integer = &H0S
        Public Const ME_ACCESS_TYPE_ANY As Integer = &H1D0000
        Public Const ME_ACCESS_TYPE_LOCAL As Integer = &H1D0001
        Public Const ME_ACCESS_TYPE_REMOTE As Integer = &H1D0002

        '===============================================================
        '  Defines for ConfigLoad
        '===============================================================

        Public Const ME_CONF_LOAD_CUSTOM_DRIVER As Integer = &H1000

        '==================================================================
        '  Defines for FPGA device
        '==================================================================

        Public Const ME_FPGA_FIRMWARE As UInt32 = &HFF000001UI
        Public Const ME_FPGA_SUBDEVICE As UInt32 = &HFF000002UI

        '==================================================================
        '  Defines for meUtilityPWM
        '==================================================================

        Public Const ME_PWM_START_NO_FLAGS As Integer = &H0
        Public Const ME_PWM_START_CONNECT_INTERNAL As Integer = &H1

        '==================================================================
        '  Defines of flags for error handling
        '==================================================================

        Public Const ME_ERRNO_CLEAR_FLAGS As Integer = &H1

        '==================================================================
        '  Defines of flags for device settings, used with property functions
        '==================================================================
        
        Public Const ME_IO_PIN_VOLTAGE_LEVEL_5_VOLTS As Integer = &H0
        Public Const ME_IO_PIN_VOLTAGE_LEVEL_3_3_VOLTS As Integer = &H1

        '==================================================================
        '  Defines of flags for property functions
        '==================================================================

        Public Const ME_PROPERTY_TYPE_INVALID As Integer = &H0
        Public Const ME_PROPERTY_TYPE_CONTAINER As Integer = &H1
        Public Const ME_PROPERTY_TYPE_BOOL As Integer = &H2
        Public Const ME_PROPERTY_TYPE_INT As Integer = &H3
        Public Const ME_PROPERTY_TYPE_DOUBLE As Integer = &H4
        Public Const ME_PROPERTY_TYPE_STRING As Integer = &H5
        Public Const ME_PROPERTY_TYPE_DEFINE As Integer = &H6

        Public Const ME_PROPERTY_ACCESS_READ_ONLY As Integer = &H0
        Public Const ME_PROPERTY_ACCESS_READ_WRITE As Integer = &H1

        Public Const ME_PROPERTY_BOOLEAN_FALSE As Integer = &H0
        Public Const ME_PROPERTY_BOOLEAN_TRUE As Integer = &H1

        Public Const ME_CALIBRATION_TYPE_FACTORY As Integer = &H1E0000
        Public Const ME_CALIBRATION_TYPE_USER_1 As Integer = &H1E0001
        
        
#End Region


#Region "PropertyConstants"


        '-------------------------------------------------------------------
        '                                                                   
        '  me-iDS System properties
        '                                                                   
        '-------------------------------------------------------------------
        Public Const ME_CONTAINER_NAME_ROOT As String = "\\"  ' Root container (system container)

        Public Const ME_ATTRIBUTE_NAME_NUMBER_OF_ELEMENTS As String = "NumberOfElements"
        Public Const ME_ATTRIBUTE_NAME_PROPERTY_NAME As String = "PropertyName"
        Public Const ME_ATTRIBUTE_NAME_PROPERTY_TYPE As String = "PropertyType"
        Public Const ME_ATTRIBUTE_NAME_PROPERTY_ACCESS As String = "PropertyAccess"
        Public Const ME_ATTRIBUTE_NAME_PROPERTY_DESCRIPTION As String = "PropertyDescription"
        Public Const ME_ATTRIBUTE_NAME_MIN_VALUE As String = "MinValue"
        Public Const ME_ATTRIBUTE_NAME_MAX_VALUE As String = "MaxValue"
        Public Const ME_ATTRIBUTE_NAME_LENGTH As String = "Length"
        Public Const ME_ATTRIBUTE_NAME_MAX_LENGTH As String = "MaxLength"
        Public Const ME_ATTRIBUTE_NAME_NUMBER_OF_SELECTIONS As String = "NumberOfSelections"
        Public Const ME_ATTRIBUTE_NAME_PREFIX_SELECTION As String = "Selection"    ' The selection with index # is "Selection#"


        '==================================================================
        '  System properties and containers
        '==================================================================

        Public Const ME_PROPERTY_NAME_LIBRARY_VERSION As String = "LibraryVersion"
        Public Const ME_PROPERTY_NAME_MAIN_DRIVER_VERSION As String = "MainDriverVersion"
        Public Const ME_PROPERTY_NAME_NUMBER_OF_DEVICES As String = "NumberOfDevices"
        Public Const ME_CONTAINER_NAME_DEVICES As String = "Devices"

        '==================================================================
        '  General device properties and containers - not device specific
        '==================================================================

        Public Const ME_CONTAINER_NAME_PREFIX_DEVICE As String = "Device"    ' The container name for the device with index # is "Device#"
        Public Const ME_PROPERTY_NAME_NAME As String = "Name"
        Public Const ME_PROPERTY_NAME_DRIVER_NAME As String = "DriverName"
        Public Const ME_PROPERTY_NAME_DRIVER_VERSION As String = "DriverVersion"
        Public Const ME_PROPERTY_NAME_DESCRIPTION As String = "Description"
        Public Const ME_PROPERTY_NAME_SERIAL_NUMBER As String = "SerialNumber"
        Public Const ME_PROPERTY_NAME_BUS_TYPE As String = "BusType"
        Public Const ME_PROPERTY_NAME_ACCESS_TYPE As String = "AccessType"
        Public Const ME_PROPERTY_NAME_PLUGGED As String = "Plugged"
        Public Const ME_PROPERTY_NAME_FIRMWARE_SELECTABLE As String = "FirmwareSelectable"
        Public Const ME_PROPERTY_NAME_CURRENT_FIRMWARE_ID As String = "CurrentFirmwareID"
        Public Const ME_PROPERTY_NAME_NUMBER_OF_SUBDEVICES As String = "NumberOfSubdevices"
        Public Const ME_CONTAINER_NAME_SUBDEVICES As String = "Subdevices"


        '==================================================================
        ' Additional properties for PCI devices
        '==================================================================

        Public Const ME_PROPERTY_NAME_PCI_VENDOR_ID As String = "PCIVendorID"
        Public Const ME_PROPERTY_NAME_PCI_DEVICE_ID As String = "PCIDeviceID"
        Public Const ME_PROPERTY_NAME_PCI_BUS_NUMBER As String = "PCIBusNumber"
        Public Const ME_PROPERTY_NAME_PCI_SLOT_NUMBER As String = "PCISlotNumber"
        Public Const ME_PROPERTY_NAME_PCI_FUNCTION_NUMBER As String = "PCIFunctionNumber"


        '==================================================================
        ' General sub-device properties and containers - not sub-device specific
        '==================================================================

        Public Const ME_CONTAINER_NAME_PREFIX_SUBDEVICE As String = "Subdevice"    ' The container name for the sub-device with index # is "Subdevice#"
        Public Const ME_PROPERTY_NAME_TYPE As String = "Type"
        Public Const ME_PROPERTY_NAME_SUBTYPE As String = "Subtype"
        Public Const ME_PROPERTY_NAME_NUMBER_OF_CHANNELS As String = "NumberOfChannels"
        Public Const ME_PROPERTY_NAME_CONFIGURABLE As String = "Configurable"
        Public Const ME_PROPERTY_NAME_NUMBER_OF_CONFIGURATIONS As String = "NumberOfConfigurations"
        Public Const ME_PROPERTY_NAME_CURRENT_CONFIGURATION As String = "CurrentConfiguration"
        Public Const ME_CONTAINER_NAME_CHANNELS As String = "Channels"
        Public Const ME_CONTAINER_NAME_PREFIX_CHANNEL As String = "Channel" ' The container name for the channel with index # is "Channel#"
        Public Const ME_CONTAINER_NAME_CONFIGURATIONS As String = "Configurations"
        Public Const ME_CONTAINER_NAME_PREFIX_CONFIGURATION As String = "Configuration"    ' The container name for the configuration with index # is "Configuration#"

        '==================================================================
        ' Configuration properties
        '==================================================================

        Public Const ME_PROPERTY_NAME_SUBDEVICE_TYPE As String = "SubdeviceType"
        Public Const ME_PROPERTY_NAME_SUBDEVICE_SUBTYPE As String = "SubdeviceSubtype"
        Public Const ME_PROPERTY_NAME_SUBDEVICE_NUMBER_OF_CHANNELS As String = "SubdeviceNumberOfChannels"

        '==================================================================
        ' ME-5100 and ME-5001 - additional device properties
        '==================================================================

        Public Const ME_PROPERTY_NAME_IO_PIN_VOLTAGE_LEVEL As String = "IOPinVoltageLevel"
        Public Const ME_PROPERTY_NAME_SUBDEVICES_0_AND_1_TERMINATED As String = "Subdevice0And1Terminated"
        Public Const ME_PROPERTY_NAME_SUBDEVICES_2_AND_3_TERMINATED As String = "Subdevice2And3Terminated"

        '==================================================================
        ' Additional sub-device properties for various sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_TERMINATED As String = "Terminated"
        Public Const ME_PROPERTY_NAME_SYSTEM_CLOCK_FREQUENCY As String = "SystemClockFrequency"

        '==================================================================
        ' Additional sub-device properties and containers for DI and DO sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_TRIGGER_TYPE As String = "TriggerType"
        Public Const ME_PROPERTY_NAME_PREFIX_RISING_EDGE_BIT As String = "RisingEdgeBit"    ' The name for the trigger condition on bit # is "RisingEdgeBit#"
        Public Const ME_PROPERTY_NAME_PREFIX_FALLING_EDGE_BIT As String = "FallingEdgeBit"    ' The name for the trigger condition on bit # is "FallngEdgeBit#"
        Public Const ME_PROPERTY_NAME_INTERNAL_BUFFER_SIZE As String = "InternalBufferSize"
        Public Const ME_PROPERTY_NAME_SAMPLE_FREQUENCY As String = "SampleFrequency"
        Public Const ME_PROPERTY_NAME_SAMPLE_TIME As String = "SampleTime"
        Public Const ME_PROPERTY_NAME_START_TRIGGER_TYPE As String = "StartTriggerType"
        Public Const ME_PROPERTY_NAME_CONV_TRIGGER_TYPE As String = "ConvTriggerType"
        Public Const ME_PROPERTY_NAME_STOP_TRIGGER_TYPE As String = "StopTriggerType"
        Public Const ME_PROPERTY_NAME_START_STOP_PATTERN As String = "StartStopPattern"
        Public Const ME_PROPERTY_NAME_STOP_ON_COUNT As String = "StopOnCount"
        Public Const ME_PROPERTY_NAME_STOP_COUNT As String = "StopCount"
        Public Const ME_CONTAINER_NAME_INTERRUPT_CONDITION As String = "InterruptCondition"
        Public Const ME_CONTAINER_NAME_SINGLE_CONFIGURATION As String = "SingleConfiguration"
        Public Const ME_CONTAINER_NAME_EXT_DIGITAL_TRIGGER_CONDITION As String = "ExtDigitalTriggerCondition"
        Public Const ME_CONTAINER_NAME_STREAMING_CONFIGURATION As String = "StreamingConfiguration"
        Public Const ME_CONTAINER_NAME_START_AND_CONV_TRIGGER_CONDITION As String = "StartAndConvTriggerCondition"
        Public Const ME_CONTAINER_NAME_STOP_TRIGGER_CONDITION As String = "StopTriggerCondition"
        Public Const ME_CONTAINER_NAME_IRQ_CONFIGURATION As String = "IRQConfiguration"

        '==================================================================
        ' Additional sub-device properties for AI sub-device types
        '==================================================================
        
        Public Const ME_PROPERTY_NAME_CALIBRATION             As String = "Calibration"
        Public Const ME_PROPERTY_NAME_RISING_EDGE_TRIGGER_A1  As String = "RisingEdgeTriggerA1"
        Public Const ME_PROPERTY_NAME_FALLING_EDGE_TRIGGER_A1 As String = "FallingEdgeTriggerA1"
        Public Const ME_PROPERTY_NAME_RISING_EDGE_TRIGGER_A2  As String = "RisingEdgeTriggerA2"
        Public Const ME_PROPERTY_NAME_FALLING_EDGE_TRIGGER_A2 As String = "FallingEdgeTriggerA2"
        Public Const ME_PROPERTY_NAME_ACQUIRE_CHANNEL         As String = "AcquireChannel"

        '==================================================================
        ' Additional sub-device properties and containers for DI sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_RISING_EDGE_TRIGGER_A As String   = "RisingEdgeTriggerA"
        Public Const ME_PROPERTY_NAME_FALLING_EDGE_TRIGGER_A As String  = "FallingEdgeTriggerA"
        Public Const ME_PROPERTY_NAME_USE_INTERNAL_TEST_COUNTER As String = "UseInternalTestCounter"
        Public Const ME_PROPERTY_NAME_TRANSFER_SIZE As String = "TransferSize"
        Public Const ME_PROPERTY_NAME_IRQ_SOURCE As String = "IRQSource"
        Public Const ME_PROPERTY_NAME_BIT_PATTERN As String = "BitPattern"
        Public Const ME_PROPERTY_NAME_BIT_PATTERN_FILTERING As String = "BitPatternFiltering"
        Public Const ME_PROPERTY_CONTAINER_BIT_MASK As String = "BitMask"

        '==================================================================
        ' Additional sub-device properties and containers for DO sub-device types
        '==================================================================
        
        Public Const ME_PROPERTY_NAME_RISING_EDGE_TRIGGER_B As String  = "RisingEdgeTriggerB"
        Public Const ME_PROPERTY_NAME_FALLING_EDGE_TRIGGER_B As String = "FallingEdgeTriggerB"
        Public Const ME_PROPERTY_NAME_IRQ_ON_EXCESS_TEMPERATURE As String = "IRQOnExcessTemperature"
        Public Const ME_PROPERTY_NAME_IRQ_ON_NORMAL_TEMPERATURE As String = "IRQOnNormalTemperature"
        Public Const ME_PROPERTY_NAME_STOP_PATTERN As String = "StopPattern"
        Public Const ME_PROPERTY_NAME_WRAPAROUND As String = "Wraparound"
        Public Const ME_PROPERTY_NAME_WRAPAROUND_LOOPS As String = "WraparoundLoops"

        '==================================================================
        ' Additional sub-device properties and containers for DO and FO sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_OUTPUT_MODE As String = "OutputMode"

        '==================================================================
        ' Additional sub-device properties and containers for DIO sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_DIRECTION As String = "Direction"

        '==================================================================
        ' Additional sub-device properties FI sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_MIN_MEASURABLE_TOTAL_TICKS As String = "MinMeasurableTotalTicks"
        Public Const ME_PROPERTY_NAME_MAX_MEASURABLE_TOTAL_TICK As String = "MaxMeasurableTotalTicks"
        Public Const ME_PROPERTY_NAME_MIN_MEASURABLE_FIRST_PHASE_TICKS As String = "MinMeasurableFirstPhaseTicks"
        Public Const ME_PROPERTY_NAME_MAX_MEASURABLE_FIRST_PHASE_TICKS As String = "MaxMeasurableFirstPhaseTicks"
        Public Const ME_PROPERTY_NAME_MIN_MEASURABLE_TOTAL_TIME As String = "MinMeasurableTotalTime"
        Public Const ME_PROPERTY_NAME_MAX_MEASURABLE_TOTAL_TIME As String = "MaxMeasurableTotalTime"
        Public Const ME_PROPERTY_NAME_MIN_MEASURABLE_FIRST_PHASE_TIME As String = "MinMeasurableFirstPhaseTime"
        Public Const ME_PROPERTY_NAME_MAX_MEASURABLE_FIRST_PHASE_TIME As String = "MaxMeasurableFirstPhaseTime"

        '==================================================================
        ' Additional sub-device properties for FO sub-device types
        '==================================================================

        Public Const ME_PROPERTY_NAME_MIN_TOTAL_TICKS As String = "MinTotalTicks"
        Public Const ME_PROPERTY_NAME_MAX_TOTAL_TICK As String = "MaxTotalTicks"
        Public Const ME_PROPERTY_NAME_MIN_FIRST_PHASE_TICKS As String = "MinFirstPhaseTicks"
        Public Const ME_PROPERTY_NAME_MAX_FIRST_PHASE_TICKS As String = "MaxFirstPhaseTicks"
        Public Const ME_PROPERTY_NAME_MIN_TOTAL_TIME As String = "MinTotalTime"
        Public Const ME_PROPERTY_NAME_MAX_TOTAL_TIME As String = "MaxTotalTime"
        Public Const ME_PROPERTY_NAME_MIN_FIRST_PHASE_TIME As String = "MinFirstPhaseTime"
        Public Const ME_PROPERTY_NAME_MAX_FIRST_PHASE_TIME As String = "MaxFirstPhaseTime"

        '==================================================================
        ' FO sub-device channel properties
        '==================================================================

        Public Const ME_PROPERTY_NAME_INVERTED As String = "Inverted"
        Public Const ME_PROPERTY_NAME_SYNCHRONOUS_START As String = "SynchronousStart"
        Public Const ME_PROPERTY_NAME_SOFT_START As String = "SoftStart"

        '==================================================================
        ' Counter sub-devices - additional sub-device properties
        '==================================================================

        Public Const ME_PROPERTY_NAME_WIDTH_IN_BITS As String = "WidthInBits"
        Public Const ME_PROPERTY_NAME_CLOCK_SOURCE As String = "ClockSource"
        Public Const ME_PROPERTY_NAME_COUNTER_MODE As String = "CounterMode"

#End Region


#Region "ErrorCodes"
        Public Const ME_ERRNO_SUCCESS As Integer = 0
        Public Const ME_ERRNO_INVALID_DEVICE As Integer = 1
        Public Const ME_ERRNO_INVALID_SUBDEVICE As Integer = 2
        Public Const ME_ERRNO_INVALID_CHANNEL As Integer = 3
        Public Const ME_ERRNO_INVALID_SINGLE_CONFIG As Integer = 4
        Public Const ME_ERRNO_INVALID_REF As Integer = 5
        Public Const ME_ERRNO_INVALID_TRIG_CHAN As Integer = 6
        Public Const ME_ERRNO_INVALID_TRIG_TYPE As Integer = 7
        Public Const ME_ERRNO_INVALID_TRIG_EDGE As Integer = 8
        Public Const ME_ERRNO_INVALID_TIMEOUT As Integer = 9
        Public Const ME_ERRNO_INVALID_FLAGS As Integer = 10
        Public Const ME_ERRNO_OPEN As Integer = 11
        Public Const ME_ERRNO_CLOSE As Integer = 12
        Public Const ME_ERRNO_NOT_OPEN As Integer = 13
        Public Const ME_ERRNO_INVALID_DIR As Integer = 14
        Public Const ME_ERRNO_PREVIOUS_CONFIG As Integer = 15
        Public Const ME_ERRNO_NOT_SUPPORTED As Integer = 16
        Public Const ME_ERRNO_SUBDEVICE_TYPE As Integer = 17
        Public Const ME_ERRNO_USER_BUFFER_SIZE As Integer = 18
        Public Const ME_ERRNO_LOCKED As Integer = 19
        Public Const ME_ERRNO_NO_MORE_SUBDEVICE_TYPE As Integer = 20
        Public Const ME_ERRNO_TIMEOUT As Integer = 21
        Public Const ME_ERRNO_SIGNAL As Integer = 22
        Public Const ME_ERRNO_INVALID_IRQ_SOURCE As Integer = 23
        Public Const ME_ERRNO_THREAD_RUNNING As Integer = 24
        Public Const ME_ERRNO_START_THREAD As Integer = 25
        Public Const ME_ERRNO_CANCEL_THREAD As Integer = 26
        Public Const ME_ERRNO_NO_CALLBACK As Integer = 27
        Public Const ME_ERRNO_USED As Integer = 28
        Public Const ME_ERRNO_INVALID_UNIT As Integer = 29
        Public Const ME_ERRNO_INVALID_MIN_MAX As Integer = 30
        Public Const ME_ERRNO_NO_RANGE As Integer = 31
        Public Const ME_ERRNO_INVALID_RANGE As Integer = 32
        Public Const ME_ERRNO_SUBDEVICE_BUSY As Integer = 33
        Public Const ME_ERRNO_INVALID_LOCK As Integer = 34
        Public Const ME_ERRNO_INVALID_SWITCH As Integer = 35
        Public Const ME_ERRNO_INVALID_ERROR_MSG_COUNT As Integer = 36
        Public Const ME_ERRNO_INVALID_STREAM_CONFIG As Integer = 37
        Public Const ME_ERRNO_INVALID_CONFIG_LIST_COUNT As Integer = 38
        Public Const ME_ERRNO_INVALID_ACQ_START_TRIG_TYPE As Integer = 39
        Public Const ME_ERRNO_INVALID_ACQ_START_TRIG_EDGE As Integer = 40
        Public Const ME_ERRNO_INVALID_ACQ_START_TRIG_CHAN As Integer = 41
        Public Const ME_ERRNO_INVALID_ACQ_START_TIMEOUT As Integer = 42
        Public Const ME_ERRNO_INVALID_ACQ_START_ARG As Integer = 43
        Public Const ME_ERRNO_INVALID_SCAN_START_TRIG_TYPE As Integer = 44
        Public Const ME_ERRNO_INVALID_SCAN_START_ARG As Integer = 45
        Public Const ME_ERRNO_INVALID_CONV_START_TRIG_TYPE As Integer = 46
        Public Const ME_ERRNO_INVALID_CONV_START_ARG As Integer = 47
        Public Const ME_ERRNO_INVALID_SCAN_STOP_TRIG_TYPE As Integer = 48
        Public Const ME_ERRNO_INVALID_SCAN_STOP_ARG As Integer = 49
        Public Const ME_ERRNO_INVALID_ACQ_STOP_TRIG_TYPE As Integer = 50
        Public Const ME_ERRNO_INVALID_ACQ_STOP_ARG As Integer = 51
        Public Const ME_ERRNO_SUBDEVICE_NOT_RUNNING As Integer = 52
        Public Const ME_ERRNO_INVALID_READ_MODE As Integer = 53
        Public Const ME_ERRNO_INVALID_VALUE_COUNT As Integer = 54
        Public Const ME_ERRNO_INVALID_WRITE_MODE As Integer = 55
        Public Const ME_ERRNO_INVALID_TIMER As Integer = 56
        Public Const ME_ERRNO_DEVICE_UNPLUGGED As Integer = 57
        Public Const ME_ERRNO_USED_INTERNAL As Integer = 58
        Public Const ME_ERRNO_INVALID_DUTY_CYCLE As Integer = 59
        Public Const ME_ERRNO_INVALID_WAIT As Integer = 60
        Public Const ME_ERRNO_CONNECT_REMOTE As Integer = 61
        Public Const ME_ERRNO_COMMUNICATION As Integer = 62
        Public Const ME_ERRNO_INVALID_SINGLE_LIST As Integer = 63
        Public Const ME_ERRNO_INVALID_MODULE_TYPE As Integer = 64
        Public Const ME_ERRNO_INVALID_START_MODE As Integer = 65
        Public Const ME_ERRNO_INVALID_STOP_MODE As Integer = 66
        Public Const ME_ERRNO_INVALID_FIFO_IRQ_THRESHOLD As Integer = 67
        Public Const ME_ERRNO_INVALID_POINTER As Integer = 68
        Public Const ME_ERRNO_CREATE_EVENT As Integer = 69
        Public Const ME_ERRNO_LACK_OF_RESOURCES As Integer = 70
        Public Const ME_ERRNO_CANCELLED As Integer = 71
        Public Const ME_ERRNO_RING_BUFFER_OVERFLOW As Integer = 72
        Public Const ME_ERRNO_SOFTWARE_BUFFER_OVERFLOW As Integer = ME_ERRNO_RING_BUFFER_OVERFLOW
        Public Const ME_ERRNO_RING_BUFFER_UNDERFLOW As Integer = 73
        Public Const ME_ERRNO_SOFTWARE_BUFFER_UNDERFLOW As Integer = ME_ERRNO_RING_BUFFER_UNDERFLOW
        Public Const ME_ERRNO_INVALID_IRQ_EDGE As Integer = 74
        Public Const ME_ERRNO_INVALID_IRQ_ARG As Integer = 75
        Public Const ME_ERRNO_INVALID_CAP As Integer = 76
        Public Const ME_ERRNO_INVALID_CAP_ARG_COUNT As Integer = 77
        Public Const ME_ERRNO_INTERNAL As Integer = 78
        Public Const ME_ERRNO_VALUE_OUT_OF_RANGE As Integer = 79
        Public Const ME_ERRNO_HARDWARE_FIFO_OVERFLOW As Integer = 80
        Public Const ME_ERRNO_HARDWARE_BUFFER_OVERFLOW As Integer = ME_ERRNO_HARDWARE_FIFO_OVERFLOW
        Public Const ME_ERRNO_HARDWARE_FIFO_UNDERFLOW As Integer = 81
        Public Const ME_ERRNO_HARDWARE_BUFFER_UNDERFLOW As Integer = ME_ERRNO_HARDWARE_FIFO_UNDERFLOW
        Public Const ME_ERRNO_CONFIG_LOAD_FAILED As Integer = 82
        Public Const ME_ERRNO_PROPERTY_CONTAINER As Integer = 83
        Public Const ME_ERRNO_PROPERTY_NOT_A_CONTAINER As Integer = 84
        Public Const ME_ERRNO_PROPERTY_DATA_TYPE As Integer = 85
        Public Const ME_ERRNO_PROPERTY_PATH As Integer = 86
        Public Const ME_ERRNO_PROPERTY_INDEX As Integer = 87
        Public Const ME_ERRNO_PROPERTY_BUFFER_TOO_SMALL As Integer = 88
        Public Const ME_ERRNO_PROPERTY_UNKNOWN As Integer = 89
        Public Const ME_ERRNO_PROPERTY_ATTRIBUTE_UNKNOWN As Integer = 90
        Public Const ME_ERRNO_PROPERTY_ATTRIBUTE_UNSUPPORTED As Integer = 91
        Public Const ME_ERRNO_PROPERTY_SELECTION_INVALID As Integer = 92
        Public Const ME_ERRNO_PROPERTY_VALUE_INVALID As Integer = 93
        Public Const ME_ERRNO_PROPERTY_READ_ONLY As Integer = 94

        '==============================================================================
        '  ME_ERRNO_INVALID_ERROR_NUMBER is always the error constant
        '  with the greatest number when new error codes are added
        '==============================================================================
        Public Const ME_ERRNO_INVALID_ERROR_NUMBER As Integer = 95

#End Region


#Region "MEiDSTypes"
#Region "IOSingle"
        '-------------------------------------------------------------------
        '                                                                   
        '  me-iDS Types                                      
        '  Declares a managed structure for each unmanaged structure.                                                                 
        '-------------------------------------------------------------------
        ''' <summary>
        ''' Contains the parameters to read a single value from 
        ''' or to write a single value to a subdevice.
        ''' Used with function meIOSingle()
        ''' </summary>
        <StructLayout(LayoutKind.Sequential)> _
        Public Structure meIOSingle_t
            ''' <summary>
            '''    Index of the device to be accessed.
            ''' </summary>
            Public iDevice As Integer
            ''' <summary>
            '''    Index of the sub-device to be accessed.
            ''' </summary>
            Public iSubdevice As Integer
            ''' <summary>
            '''    Channel index resp. index of the group
            ''' </summary>
            Public iChannel As Integer
            ''' <summary>
            '''    Direction of the single operation
            ''' </summary>
            ''' <remarks>
            ''' ME_DIR_INPUT, ME_DIR_OUTPUT, ME_DIR_SET_OFFSET
            ''' </remarks>
            Public iDir As Integer
            ''' <summary>
            ''' Read resp. output a 32 bit digital value. ME_DIR_INPUT, ME_DIR_OUTPUT, ME_DIR_SET_OFFSET
            ''' </summary>
            Public iValue As Integer
            ''' <summary>
            ''' Time-out value in milliseconds. If no external trigger is being used or no time-out value is used, pass 0
            ''' </summary>
            Public iTimeOut As Integer
            ''' <summary>
            ''' Extended settings depending on the operation
            ''' </summary>
            Public iFlags As Integer
            ''' <summary>
            ''' Error code returned by the particular entry
            ''' </summary>
            Public iErrno As Integer
        End Structure
#End Region

#Region "IOStream"
        ''' <summary>
        ''' Channel-list for analog and digital (bit pattern output) streaming operations
        ''' </summary>
        <StructLayout(LayoutKind.Sequential)> _
        Public Structure meIOStreamConfig_t
            ''' <summary>
            ''' Channel index. Depending on sub-device this can be analog inputs or outputs as well as a group of digital I/Os
            ''' </summary>
            Public iChannel As Integer
            ''' <summary>
            ''' Index of analog input or analog output range
            ''' </summary>
            Public iStreamConfig As Integer
            ''' <summary>
            ''' Defines the ground reference for analog inputs and outputs, ME_REF_NONE, ME_REF_AI_GROUND, ME_REF_AI_DIFFERENTIAL, ME_REF_AO_GROUND, ME_REF_AO_DIFFERENTIAL
            ''' </summary>
            Public iRef As Integer
            ''' <summary>
            ''' Extended settings, if no extended options available, use ME_IO_STREAM_CONFIG_TYPE_NO_FLAGS
            ''' </summary>
            Public iFlags As Integer
        End Structure

        ''' <summary>
        ''' Defines parameters to start and stop streaming operations.
        ''' </summary>
        <StructLayout(LayoutKind.Sequential, Pack:=4)> _
        Public Structure meIOStreamTrigger_t
            ''' <summary>
            ''' defines the trigger type for start of the whole operation (ME_TRIG_TYPE_SW, ME_TRIG_TYPE_EXT_ANALOG, ME_TRIG_TYPE_THRESHOLD...)
            ''' </summary>
            Public iAcqStartTrigType As Integer
            ''' <summary>
            ''' defines the trigger edge for start of a single conversion (ME_TRIG_EDGE_NONE, ME_TRIG_EDGE_RISING, ME_TRIG_EDGE_FALLING...)
            ''' </summary>
            Public iAcqStartTrigEdge As Integer
            ''' <summary>
            ''' choose whether triggering should be done separatly for each channel (standard) or if a channel should be started synchronously with other channels
            ''' </summary>
            Public iAcqStartTrigChan As Integer
            ''' <summary>
            ''' Offset time in number of ticks between "start" of the measurement and the first conversion.
            ''' </summary>
            Public iAcqStartTicksLow As Integer
            ''' <summary>
            ''' Higher significant part of the offset time (bits 63...32)
            ''' </summary>
            Public iAcqStartTicksHigh As Integer
            ''' <summary>
            ''' List of Start Arguments (threshold value in [µV], slew rate in [µV/Sample], lower threshold value of the window in [µV])
            ''' </summary>
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=10)> Public iAcqStartArgs As Integer()
            ''' <summary>
            ''' defines the trigger type for start of a scan (ME_TRIG_TYPE_TIMER, ME_TRIG_TYPE_FOLLOW, ME_TRIG_TYPE_EXT_DIGITAL...)
            ''' </summary>
            Public iScanStartTrigType As Integer
            ''' <summary>
            ''' Time interval in ticks between the start of two consecutive scans
            ''' </summary>
            Public iScanStartTicksLow As Integer
            ''' <summary>
            ''' Higher significant part of the scan-time (bits 63...32)
            ''' </summary>
            Public iScanStartTicksHigh As Integer
            ''' <summary>
            ''' reserved
            ''' </summary>
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=10)> Public iScanStartArgs As Integer()
            ''' <summary>
            ''' defines the trigger type for start of a single conversion (ME_TRIG_TYPE_TIMER, ME_TRIG_TYPE_EXT_DIGITAL, ME_TRIG_TYPE_EXT_ANALOG)
            ''' </summary>
            Public iConvStartTrigType As Integer
            ''' <summary>
            ''' Chan interval in number of ticks between two conversions (Sample resp. output rate)
            ''' </summary>
            Public iConvStartTicksLow As Integer
            ''' <summary>
            ''' Higher significant part of the chan interval (bits 63...32)
            ''' </summary>
            Public iConvStartTicksHigh As Integer
            ''' <summary>
            ''' reserved
            ''' </summary>
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=10)> Public iConvStartArgs As Integer()
            ''' <summary>
            ''' defines the trigger type for ending the scan (ME_TRIG_TYPE_NONE, ME_TRIG_TYPE_COUNT)
            ''' </summary>
            Public iScanStopTrigType As Integer
            ''' <summary>
            ''' Total number of conversions after which the scans will be ended and at the same time the measurement as a whole.
            ''' </summary>
            Public iScanStopCount As Integer
            ''' <summary>
            ''' MEphisto Scope in oscilloscope mode: trigger point in percent between 0%...100%
            ''' </summary>
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=10)> Public iScanStopArgs As Integer()
            ''' <summary>
            ''' defines the trigger type for ending the whole operation (ME_TRIG_TYPE_NONE, ME_TRIG_TYPE_COUNT, ME_TRIG_TYPE_FOLLOW)
            ''' </summary>
            Public iAcqStopTrigType As Integer
            ''' <summary>
            ''' Number of scans (channel-list processings) after which the complete operation should be ended
            ''' </summary>
            Public iAcqStopCount As Integer
            ''' <summary>
            ''' reserved
            ''' </summary>
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=10)> Public iAcqStopArgs As Integer()
            ''' <summary>
            ''' ME_IO_STREAM_TRIGGER_TYPE_NO_FLAGS (default) (no flags available)
            ''' </summary>
            Public iFlags As Integer
        End Structure

        ''' <summary>
        ''' StartList, defines parameters for the start of streaming operations
        ''' </summary>
        <StructLayout(LayoutKind.Sequential)> _
        Public Structure meIOStreamStart_t
            ''' <summary>
            ''' Index of the device to be accessed
            ''' </summary>
            Public iDevice As Integer
            ''' <summary>
            ''' Index of the sub-device to be accessed
            ''' </summary>
            Public iSubdevice As Integer
            ''' <summary>
            ''' Blocking or Nonblocking start mode of the streaming operation
            ''' </summary>
            ''' <remarks>
            ''' ME_START_MODE_BLOCKING (waits until the proper trigger signal occurs), ME_START_MODE_NONBLOCKING (Function returns immediately)
            ''' </remarks>
            Public iStartMode As Integer
            ''' <summary>
            ''' Time interval in milliseconds within the first trigger pulse must occur
            ''' </summary>
            Public iTimeOut As Integer
            ''' <summary>
            ''' Extended settings, Start particular subdevice only or several subdevices synchronously
            ''' </summary>
            ''' <remarks>
            ''' ME_IO_STREAM_START_TYPE_NO_FLAGS default setting, ME_IO_STREAM_START_TYPE_TRIG_SYNCHRONOUS for Synchronous start
            ''' </remarks>
            Public iFlags As Integer
            ''' <summary>
            ''' If an error occurs, an error code will be set.
            ''' </summary>
            Public iErrno As Integer
        End Structure

        ''' <summary>
        ''' StopList, defines end of input/output streaming operations
        ''' </summary>
        <StructLayout(LayoutKind.Sequential)> _
        Public Structure meIOStreamStop_t
            ''' <summary>
            ''' Index of the device to be accessed.
            ''' </summary>
            Public iDevice As Integer
            ''' <summary>
            ''' Index of the sub-device to be accessed.
            ''' </summary>
            Public iSubdevice As Integer
            ''' <summary>
            ''' Stop mode of the streaming operation
            ''' </summary>
            ''' <remarks>
            ''' <see cref="ME_STOP_MODE_IMMEDIATE"/>: Streaming operation is stopped at once. 
            ''' In case of an analog output 0V is attached to the pin.
            ''' <see cref="ME_STOP_MODE_LAST_VALUE"/>: Output sub-device: operation is stopped on the last entry 
            ''' in the DA-FIFO which is a defined value.
            ''' Input sub-device: operation is stopped on the last entry from the channel-list.
            ''' </remarks>
            Public iStopMode As Integer
            ''' <summary>
            ''' <see cref="ME_IO_STREAM_STOP_TYPE_NO_FLAGS"/>: Default settings.
            ''' </summary>
            ''' <remarks>
            ''' Output sub-device: all buffers are cleared.
            ''' Input sub-device: Hardware buffer is cleared. No synchronization at all. 
            ''' In mode <see cref="ME_STOP_MODE_IMMEDIATE"/> some data can be lost.
            ''' </remarks>
            Public iFlags As Integer
            ''' <summary>
            ''' If an error occurs, an error code will be set.
            ''' </summary>
            Public iErrno As Integer
        End Structure
#End Region

#End Region '"MEiDSTypes"


#Region "Delegates"

        ''' <summary>
        ''' Delegate type to be used for <see cref="meErrorSetUserProc"/>.
        ''' </summary>
        ''' <param name="functionName">
        ''' String with the name of the faulty function where the error was detected.
        ''' </param>
        ''' <param name="errorCode">
        ''' The error code.
        ''' </param>
        ''' <returns>
        ''' No error possible. Return "0".
        ''' </returns>
        Public Delegate Function meErrorCB_t(ByVal functionName As String, ByVal errorCode As Integer) As Integer

        ''' <summary>
        ''' Delegate type to be used for <see cref="meIOStreamSetCallbacks"/>.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the interrupt sub-device.
        ''' </param>
        ''' <param name="count">
        ''' Input sub-device: number of values, which can be read
        ''' Output sub-device: Free memory in the output buffer.
        ''' </param>
        ''' <param name="context">
        ''' User-defined pointer.
        ''' </param>
        ''' <param name="errorCode">
        ''' If an error occurs an error code will be returned.
        ''' </param>
        ''' <returns>
        ''' Return the errorCode if the operation should stop when an error occured, otherwise return "0"
        ''' </returns>
        Public Delegate Function meIOStreamCB_t(ByVal device As Integer, ByVal subdevice As Integer, ByVal count As Integer, ByVal context As IntPtr, ByVal errorCode As Integer) As Integer


        ''' <summary>
        ''' Delegate type to be used for <see cref="meIOIrqSetCallback"/>.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the interrupt sub-device.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the interrupt channel within the sub-device
        ''' </param>
        ''' <param name="irqCount">
        ''' Number of interrupts from the specified channel since starting.
        ''' </param>
        ''' <param name="value">
        ''' Parameter returns the interrupt status.
        ''' </param>
        ''' <param name="context">
        ''' User-defined pointer.
        ''' </param>
        ''' <param name="errorCode">
        ''' Error code: see error reported by <see cref="meIOIrqWait"/>.
        ''' </param>
        ''' <returns>
        ''' Return the errorCode if the operation should stop when an error occured, otherwise return "0"
        ''' </returns>
        Public Delegate Function meIOIrqCB_t(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByVal irqCount As Integer, ByVal value As Integer, ByVal context As IntPtr, ByVal errorCode As Integer) As Integer

#End Region


#Region "MEiDSFunctions"
        '-------------------------------------------------------------------
        '                                                                   
        '  ME-iDS Functions                      
        '  Functions to access the driver system
        '  CallingConvention.Cdecl must be used since the stack is cleaned up by the caller. 
        '-------------------------------------------------------------------

#Region "meOpen"

        ''' <summary>
        ''' Initializes the function library.
        ''' </summary>
        ''' <param name="flags">Use <see cref="ME_OPEN_NO_FLAGS"/>.</param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_OPEN"/>: ME-iDS can not be properly opened. Usually driver is not loaded.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' Before the ME-iDS driver functions can be used this function must be called.
        ''' Otherwise the function calls will fail.
        ''' In case of an error <see cref="meClose"/> doesn't have to be called.
        ''' </remarks>
        ''' <seealso cref="meClose"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meOpen(ByVal flags As Integer) As Integer
        End Function
#End Region

#Region "meClose"

        ''' <summary>
        ''' This function closes the connection to the function library.
        ''' </summary>
        ''' <param name="flags">
        ''' Use <see cref="ME_CLOSE_NO_FLAGS"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_CLOSE"/>: ME-iDS can not be properly closed.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' Call this function to release resources and to disconnect from the ME-iDS driver.
        ''' </remarks>
        ''' <seealso cref="meOpen"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meClose(ByVal flags As Integer) As Integer
        End Function
#End Region

#Region "meLockDriver"
        ''' <summary>
        ''' Locks or unlocks the entire ME-iDS driver system.
        ''' </summary>
        ''' <param name="lockMode">
        ''' The possible values are <see cref="ME_LOCK_SET"/>, <see cref="ME_LOCK_RELEASE"/>, <see cref="ME_LOCK_CHECK"/>.
        ''' </param>
        ''' <param name="flags">
        ''' Use <see cref="ME_LOCK_DRIVER_NO_FLAGS"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_LOCKED"/>: resource is locked by other application/task.
        ''' <see cref="ME_ERRNO_USED"/>: resource is currently in use therefore lock can not be set.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' If another thread wants access to the driver system an error message is returned.
        ''' </remarks>
        ''' <seealso cref="meLockDevice"/>
        ''' <seealso cref="meLockSubdevice"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meLockDriver(ByVal lockMode As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region

#Region "meLockDevice"
        ''' <summary>
        ''' Locks or unlocks a ME-iDS device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="lockMode">
        ''' The possible values are <see cref="ME_LOCK_SET"/>, <see cref="ME_LOCK_RELEASE"/>, <see cref="ME_LOCK_CHECK"/>.
        ''' </param>
        ''' <param name="flags">
        ''' Use <see cref="ME_LOCK_DEVICE_NO_FLAGS"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_LOCKED"/>: resource is locked by other application/task.
        ''' <see cref="ME_ERRNO_USED"/>: resource is currently in use therefore lock can not be set.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' If another thread wants to access to a locked device an error message is returned.
        ''' </remarks>
        ''' <seealso cref="meLockDriver"/>
        ''' <seealso cref="meLockSubdevice"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meLockDevice(ByVal device As Integer, ByVal lockMode As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region

#Region "meLockDevice"
        ''' <summary>
        ''' Locks or unlocks a sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="lockMode">
        ''' The possible values are <see cref="ME_LOCK_SET"/>, <see cref="ME_LOCK_RELEASE"/>, <see cref="ME_LOCK_CHECK"/>.
        ''' </param>
        ''' <param name="flags">
        ''' Use <see cref="ME_LOCK_SUBDEVICE_NO_FLAGS"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_LOCKED"/>: resource is locked by other application/task.
        ''' <see cref="ME_ERRNO_USED"/>: resource is currently in use therefore lock can not be set.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' If another thread wants to access to a locked sub-device an error message is returned.
        ''' </remarks>
        ''' <seealso cref="meLockDevice"/>
        ''' <seealso cref="meLockDriver"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meLockSubdevice(ByVal device As Integer, ByVal subdevice As Integer, ByVal lockMode As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meErrorGetLast"
        ''' <summary>
        ''' Returns the last error code.
        ''' </summary>
        ''' <param name="errorCode">
        ''' Variable that receives the error code.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_NO_FLAGS"/>: Default setting.
        ''' <see cref="ME_ERRNO_CLEAR_FLAGS"/>: Do not report this error again.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <seealso cref="meErrorGetLastMessage"/>
        ''' <seealso cref="meErrorGetMessage"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meErrorGetLast(ByRef errorCode As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meErrorGetLastMessage"

        ''' <summary>
        ''' Returns the last error caused by an API function.
        ''' </summary>
        ''' <param name="buffer">
        ''' Buffer to hold the error description text.
        ''' </param>
        ''' <param name="count">
        ''' Buffer size in bytes for the error description text. Use the constant <see cref="ME_ERROR_MSG_MAX_COUNT"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_ERROR_MSG_COUNT"/>: reserved buffer is too small for description. 
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <seealso cref="meErrorGetMessage"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meErrorGetLastMessage(buffer As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meErrorGetMessage"
        ''' <summary>
        ''' Converts an error code returned from an API function to plain text.
        ''' </summary>
        ''' <param name="errorCode">
        ''' The error code from the API function.
        ''' </param>
        ''' <param name="msg">
        ''' Buffer to hold the error description text.
        ''' </param>
        ''' <param name="count">
        ''' Buffer size in bytes for the error description text. Use the constant ME_ERROR_MSG_MAX_COUNT.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_ERROR_NUMBER"/>: provided error code is not valid in ME-iDS.
        ''' <see cref="ME_ERRNO_INVALID_ERROR_MSG_COUNT"/>: reserved buffer is too small for description.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <seealso cref="meErrorGetLastMessage"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meErrorGetMessage(ByVal errorCode As Integer, msg As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meErrorSetDefaultProc"
        ''' <summary>
        ''' Installs a predefined global error logging routine for the entire ME-iDS.
        ''' </summary>
        ''' <param name="switch">
        ''' <see cref="ME_SWITCH_ENABLE"/>Installing the predefined error routine for global error logging.
        ''' <see cref="ME_SWITCH_DISABLE"/>Uninstall the predefined error routine.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_SWITCH"/>: passed action code is not supported.
        ''' </returns>
        ''' <remarks>
        ''' This global error routine is automatically called if any function call returns an error. 
        ''' Only one global error routine can be installed.
        ''' The following infos are returned:
        ''' -Name of the function causing the error
        ''' -Short error description
        ''' -Error code
        ''' </remarks>
        ''' <seealso cref="meErrorSetUserProc"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meErrorSetDefaultProc(ByVal switch As Integer) As Integer
        End Function
#End Region


#Region "meErrorSetUserProc"
        ''' <summary>
        ''' Installs a global user-defined error logging routine for the ME-iDS.
        ''' </summary>
        ''' <param name="errorProc">
        ''' Delegate to the user-defined error logging routine.
        ''' See <see cref="meErrorCB_t"/>
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' </returns>
        ''' <remarks>
        ''' This function is automatically called if any function call returns an error.
        ''' Passing a NULL will uninstall a previously installed error routine.
        ''' The following infos are returned:
        ''' -Name of the function causing the error
        ''' -Error code
        ''' </remarks>
        ''' <seealso cref="meErrorSetDefaultProc"/>
        ''' <seealso cref="meErrorGetMessage"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meErrorSetUserProc(errorProc As meErrorCB_t) As Integer
        End Function
#End Region


#Region "meIOIrqSetCallback"
        ''' <summary>
        ''' Installs a callback function which waits for an interrupt in the background.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="callback">
        ''' Delegate to the user-defined callback function.
        ''' See <see cref="meIOIrqCB_t"/>
        ''' </param>
        ''' <param name="callbackContext">
        ''' User-defined pointer passed to the callback function.
        ''' Can be used to pass a reference of the own instance through the callback routine
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_IRQ_SET_CALLBACK_NO_FLAGS"/>: No flags in use.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: sub-device is protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_START_THREAD"/>: creating callback thread failed. (Linux only)
        ''' <see cref="ME_ERRNO_THREAD_RUNNING"/>: callback thread is already running. (Windows only)
        ''' </returns>
        ''' <remarks>
        ''' To deinstall/cancel the callback function (all registered instances) 
        ''' for the selected sub-device call meIOIrqSetCallback() and pass null in 
        ''' <paramref name="callback"/>.
        ''' </remarks>
        ''' <example>
        ''' See also (<a href="http://msdn.microsoft.com/en-gb/magazine/cc301501.aspx">Call Unmanaged DLLs from C#, Killing Processes Cleanly</a>).
        ''' <code>
        ''' // the form contains a TextBox to display the values given by the callback function
        ''' public partial class Form1 : Form
        ''' {
        '''     meIDS.meIOIrqCB_t IrqCallback = new meIDS.meIOIrqCB_t(meIOIrqCB);   'create a delegate for Callback function
        '''     GCHandle objectHandle = new GCHandle();                             'global variable 
        '''    
        '''     private void MyStartIrqFunction(int deviceIndex, int subdeviceIndex)
        '''     {
        '''         objectHandle = GCHandle.Alloc(this);
        '''         
        '''         int meError = meIDS.meIOIrqSetCallback(deviceIndex,             'Device index
        '''                                                subdeviceIndex,          'Subdevice index
        '''                                                IrqCallback,             'Callback routine
        '''                                                (IntPtr)objectHandle,    'Callback context, GCHandle used to wrap instance of Form 
        '''                                                meIDS.ME_IO_IRQ_SET_CALLBACK_NO_FLAGS); 'No flags in use
        '''
        '''         if (meError == meIDS.ME_ERRNO_SUCCESS)
        '''         {
        '''             //callback function is armed, meIDS.meIOIrqStart() may be called
        '''             meError = meIDS.meIOIrqStart(deviceIndex,                   'Device index
        '''                                          subdeviceIndex,                'Subdevice index
        '''                                          ...
        '''                                         );
        '''             ...
        '''         }
        '''     }
        '''
        '''     private static int meIOIrqCB(int idxDevice, int idxSubdevice, int idxChannel,
        '''                                         int irqCount, int value, IntPtr pContext, int errorCode)
        '''     {
        '''         if (errorCode == meIDS.ME_ERRNO_SUCCESS)
        '''         {
        '''             GCHandle objectHandle = GCHandle.FromIntPtr(pContext);          'get objectHandle of our instance
        '''             Form1 frm = (Form1)objectHandle.Target;
        '''             frm.DisplayValues(idxDevice, idxSubdevice, idxChannel, irqCount, value, pContext, errorCode);  'display values in textBox1
        '''         }
        '''         return (0);
        '''     }
        '''     
        '''     // This delegate enables asynchronous calls for setting the text in a textBox1
        '''     private delegate void DisplayValuesDelegate(int idxDevice, int idxSubdevice, int idxChannel,
        '''                                    int irqCount, int value, IntPtr context, int errorCode);
        ''' 
        '''     // This method demonstrates a pattern for making thread-safe calls on a Windows Forms control.
        '''     private void DisplayValues(int idxDevice, int idxSubdevice, int idxChannel,
        '''                                    int irqCount, int value, IntPtr context, int errorCode)
        '''     {
        '''         // InvokeRequired compares the thread ID of the calling thread to the thread ID of the creating thread.
        '''         // If these threads are different, it returns true.
        '''         if (textBox1.InvokeRequired)
        '''         {
        '''             //The calling thread is different from the thread that created the TextBox.
        '''             //The method creates a SetTextCallback and calls itself asynchronously using the Invoke method.
        '''             DisplayValuesDelegate dispDelegate = new DisplayValuesDelegate(DisplayValues);
        '''             this.Invoke(dispDelegate, new object[] {idxDevice,  idxSubdevice, idxChannel, irqCount, value, context, errorCode});
        '''         }
        '''         else
        '''         {
        '''             //The calling thread is the same as the thread that created the TextBox
        '''             //The Text property is set directly.
        '''             textBox1.AppendText("Device index: " + idxDevice.ToString()
        '''                        + ",  Subdevice index: " + idxSubdevice.ToString()
        '''                        + String.Format(",  Value hex: 0x{0:X}", value)      'display value in hexadecimal
        '''                        + ",  dec: " + value.ToString()                      'display value in decimal
        '''                        + Environment.NewLine);
        '''         }
        '''     }
        '''     
        '''     private void MyStopIrqFunction(int deviceIndex, int subdeviceIndex)
        '''     {
        '''         //disable generating IRQs
        '''         meIDS.meIOIrqStop(deviceIndex, 
        '''                           subdevIndex, 
        '''                           0, 
        '''                           meIDS.ME_IO_IRQ_STOP_NO_FLAGS);
        '''                           
        '''         //Don't forget to call Free for objectHandle
        '''         if (objectHandle.IsAllocated)                   
        '''         {
        '''             objectHandle.Free();                        ' do this when callback cannot be called anymore
        '''         }
        '''     }
        ''' }
        ''' </code>
        ''' </example>
        ''' <seealso cref="meIOIrqWait"/>
        ''' <seealso cref="meIOIrqStart"/>
        ''' <seealso cref="meIOIrqStop"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOIrqSetCallback(ByVal device As Integer, ByVal subdevice As Integer, callback As meIOIrqCB_t, ByVal callbackContext As IntPtr, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOIrqStart"
        ''' <summary>
        ''' Starts the interrupt handler for the given interrupt sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the interrupt channel within the selected sub-device.
        ''' </param>
        ''' <param name="irqSource">
        ''' Selection of interrupt source
        ''' <see cref="ME_IRQ_SOURCE_DIO_LINE"/>: Interrupt source is a dedicated external interrupt input.
        ''' <see cref="ME_IRQ_SOURCE_DIO_PATTERN"/>: Operation mode "Bit Pattern Match". 
        ''' When the current bit pattern at the digital port matches the reference bit pattern to be passed in <paramref name="irqArg"/> an interrupt is triggered.
        ''' <see cref="ME_IRQ_SOURCE_DIO_MASK"/>: Operation mode "Bit Pattern Change". 
        ''' On change of at least one bit, masked as "sensitive" an interrupt is triggered.
        ''' <see cref="ME_IRQ_SOURCE_DIO_OVER_TEMP"/>: On overheating of the driver circuit an interrupt is triggered.
        ''' </param>
        ''' <param name="irqEdge">
        ''' Selection of the edge on which an interrupt should be triggered.
        ''' <see cref="ME_IRQ_EDGE_NOT_USED"/>: Choosing an edge is not supported
        ''' <see cref="ME_IRQ_EDGE_RISING"/>: Interrupt on rising edge
        ''' <see cref="ME_IRQ_EDGE_FALLING"/>: Interrupt on falling edge
        ''' <see cref="ME_IRQ_EDGE_ANY"/>: Interrupt on rising or falling edge
        ''' </param>
        ''' <param name="irqArg">
        ''' Argument to configure the modes "Bit Pattern Match" and "Bit Pattern Change"
        ''' In other cases pass the value "0" here.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_IRQ_START_NO_FLAGS"/>: No flags in use. Default settings will be used.
        ''' <see cref="ME_IO_IRQ_START_DIO_BIT"/>: The reference bit pattern is one bit wide.
        ''' <see cref="ME_IO_IRQ_START_DIO_BYTE"/>: The reference bit pattern is one byte wide (8 bit).
        ''' <see cref="ME_IO_IRQ_START_DIO_WORD"/>: The reference bit pattern is one word wide (16 bit).
        ''' <see cref="ME_IO_IRQ_START_DIO_DWORD"/>: The reference bit pattern is one double-word wide (32 bit).
        ''' <see cref="ME_IO_IRQ_START_PATTERN_FILTERING"/>: (for "Bit Pattern Match" only): Enables filtering of the result.
        ''' <see cref="ME_IO_IRQ_START_EXTENDED_STATUS"/>: (for "Bit Pattern Change" only): Set extended IRQ status format as default.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_INVALID_IRQ_SOURCE"/>: wrong mode or not supported by sub-device.
        ''' <see cref="ME_ERRNO_INVALID_IRQ_EDGE"/>: set edge not supported.
        ''' <see cref="ME_ERRNO_INVALID_IRQ_ARG"/>: wrong configuration argument / argument not supported.
        ''' <see cref="ME_ERRNO_LOCKED"/>: sub-device is protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_START_THREAD"/>: creating callback thread failed. (Linux only)
        ''' </returns>
        ''' <remarks>
        ''' On demand an user-defined callback function can be installed by the function <see cref="meIOIrqSetCallback"/>() which is then called on each interrupt.
        ''' </remarks>
        ''' <seealso cref="meIOIrqSetCallback"/>
        ''' <seealso cref="meIOIrqWait"/>
        ''' <seealso cref="meIOIrqStop"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOIrqStart(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByVal irqSource As Integer, ByVal irqEdge As Integer, ByVal irqArg As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOIrqStop"
        ''' <summary>
        ''' Stops a previously started interrupt handler
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the interrupt channel within the selected sub-device.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_IRQ_STOP_NO_FLAGS"/>: No flags in use. Default settings will be used.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: sub-device is protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' </returns>
        ''' <seealso cref="meIOIrqStart"/>
        ''' <seealso cref="meIOIrqSetCallback"/>
        ''' <seealso cref="meIOIrqWait"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOIrqStop(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOIrqWait"
        ''' <summary>
        ''' Waits as long as an interrupt occurs.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the interrupt channel within the selected sub-device.
        ''' </param>
        ''' <param name="irqCount">
        ''' Returns the number of interrupts from the specified channel since starting.
        ''' </param>
        ''' <param name="value">
        ''' Returns the interrupt status. "Simple format": One status bit per IRQ line. "Extended format": Two status bits per IRQ line.
        ''' </param>
        ''' <param name="timeout">
        ''' Time-out value in milliseconds. If 0 is passed the function will wait indefinitely.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_IRQ_WAIT_NO_FLAGS"/>: No flags in use. Default settings will be used.
        ''' <see cref="ME_IO_IRQ_WAIT_NORMAL_STATUS"/>: Use "simple format" for interrupt status, see <paramref name="value"/>.
        ''' <see cref="ME_IO_IRQ_WAIT_EXTENDED_STATUS"/>: Use "extended format" for interrupt status, see <paramref name="value"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: sub-device is protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_CANCELLED"/>: Sub-device was reset.
        ''' <see cref="ME_ERRNO_SIGNAL"/>: Driver was unloaded.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: Sub-device wrongly configured.
        ''' </returns>
        ''' <remarks>
        ''' This function is completely independent from <seealso cref="meIOIrqStart"/>. 
        ''' In multi-threading applications there is no need for synchronization. 
        ''' meIOIrqWait() can be called before or after <seealso cref="meIOIrqStart"/> and waits for the first interrupt event. 
        ''' If an interrupt occurs before meIOIrqWait() is called the function returns immediately and reports it.
        ''' You must decide whether you want to install a callback function by <seealso cref="meIOIrqSetCallback"/>. 
        ''' before calling the function <seealso cref="meIOIrqStart"/>.
        ''' </remarks>
        ''' <seealso cref="meIOIrqStart"/>
        ''' <seealso cref="meIOIrqSetCallback"/>
        ''' <seealso cref="meIOIrqStop"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOIrqWait(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByRef irqCount As Integer, ByRef value As Integer, ByVal timeOut As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOResetDevice"
        ''' <summary>
        ''' The device will be reset.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be reset.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_RESET_DEVICE_NO_FLAGS"/>: no flags available
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' All currently executed operations of the specific device are cancelled:
        ''' - All hardware actions are stopped
        ''' - Hardware is set to default (idle) state
        ''' - Internal states are cleared
        ''' - Buffers are flushed (emptied)
        ''' - Interrupt counters are set to zero
        ''' </remarks>
        ''' <seealso cref="meIOResetSubdevice"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOResetDevice(ByVal device As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOResetSubdevice"
        ''' <summary>
        ''' The sub-device will be reset.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be reset.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_RESET_SUBDEVICE_NO_FLAGS"/>: no flags available 
        ''' verfügbar.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' All currently executed operations of the specific sub-device are cancelled:
        ''' - All hardware actions are stopped
        ''' - Hardware is set to default (idle) state
        ''' - Internal states are cleared
        ''' - Buffers are flushed (emptied)
        ''' - Interrupt counters are set to zero
        ''' </remarks>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOResetSubdevice(ByVal device As Integer, ByVal subdevice As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOSingleConfig"
        ''' <summary>
        ''' Prepares a sub-device for a "single operation".
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the channel within the selected sub-device.
        ''' </param>
        ''' <param name="singleConfig">
        ''' Configuration of measurement ranges, digital ports and counters.
        ''' </param>
        ''' <param name="reference">
        ''' Depending on the subdevice type it can be a ground reference, 
        ''' the clock source of the counters or <see cref="ME_REF_NONE"/> 
        ''' for standard digital I/O and frequency I/O. 
        ''' </param>
        ''' <param name="trigChan">
        ''' Trigger channel, if supported by the sub-device.
        ''' </param>
        ''' <param name="trigType">
        ''' Trigger type for starting of input/output
        ''' </param>
        ''' <param name="trigEdge">
        ''' Choose the appropriate trigger edge
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_SINGLE_CONFIG_NO_FLAGS"/>: No flags used. Default settings.
        ''' <see cref="ME_IO_SINGLE_CONFIG_DIO_BIT"/>: Digital input/output operation by bit.
        ''' <see cref="ME_IO_SINGLE_CONFIG_DIO_BYTE"/>: Digital input/output operation by byte (8 bit).
        ''' <see cref="ME_IO_SINGLE_CONFIG_DIO_WORD"/>: Digital input/output operation by word (16 bit).
        ''' <see cref="ME_IO_SINGLE_CONFIG_DIO_DWORD"/>: Digital input/output operation by double-word (32 bit).
        ''' for the channel passed in parameter <paramref name="channel"/> and all channels beyond.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_REF"/>: parameter <paramref name="reference"/> is not correct.
        ''' <see cref="ME_ERRNO_INVALID_TRIG_CHAN"/>: parameter <paramref name="trigChan"/> is not correct.
        ''' <see cref="ME_ERRNO_INVALID_TRIG_TYPE"/>: parameter <paramref name="trigType"/> is not correct.
        ''' <see cref="ME_ERRNO_INVALID_TRIG_EDGE"/>: parameter <paramref name="trigEdge"/> is not correct.
        ''' <see cref="ME_ERRNO_INVALID_SINGLE_CONFIG"/>: parameter <paramref name="singleConfig"/> is not correct.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' Basically the operation starts after calling the function <seealso cref="meIOSingle"/> 
        ''' corresponding to the trigger conditions described here.
        ''' </remarks>
        ''' <seealso cref="meIOSingle"/>
        ''' <seealso cref="meIOStreamConfig"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOSingleConfig(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByVal singleConfig As Integer, ByVal reference As Integer, ByVal trigChan As Integer, ByVal trigType As Integer, ByVal trigEdge As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOSingle"
        ''' <summary>
        ''' Read/write operations can be processed.
        ''' </summary>
        ''' <param name="singleList">
        ''' Reference to a list of type <see cref="meIOSingle_t"/>.
        ''' </param>
        ''' <param name="count">
        ''' Number of entries in <paramref name="singleList"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_SINGLE_NO_FLAGS"/> No extended options. Default settings. 
        ''' Execution is stopped on first error.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_TIMEOUT"/>: timeout condition occurred.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: sub-device was not configured for required operation.
        ''' <see cref="ME_ERRNO_SUBDEVICE_BUSY"/>: sub-device is performing other operation.
        ''' </returns>
        ''' <remarks>
        ''' If for one or more list entries an external trigger source has been selected, 
        ''' the function waits until the appropriate trigger signal occurs. 
        ''' I. e. if operation 1 with external trigger is executed in blocking mode, 
        ''' operation 2 waits until the external trigger pulse of operation 1 occurs.
        ''' </remarks>
        ''' <seealso cref="meIOSingleConfig"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOSingle(ByRef singleList As meIOSingle_t, ByVal count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOSingleTicksToTime"
        ''' <summary>
        ''' Converts the number of ticks into the desired time, e. g. period [s] for e. g. frequency measurement.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="timer">
        ''' Ticks will be calculated in dependency of the sub-device type and the 
        ''' timer specified here.
        ''' <see cref="ME_TIMER_FIO_TOTAL"/>: The period is converted into seconds.
        ''' <see cref="ME_TIMER_FIO_FIRST_PHASE"/>: The duration of the first phase of the period is converted into seconds.
        ''' </param>
        ''' <param name="ticksLow">
        ''' The number of ticks (lower significant part, bits 31...0) from parameter 
        ''' value of the function <see cref="meIOSingle"/> are passed here.
        ''' </param>
        ''' <param name="ticksHigh">
        ''' The number of ticks (higher significant part, bits 63...32) from parameter 
        ''' value of the function <see cref="meIOSingle"/> are passed here. This 
        ''' parameter is resevered for future enhancements.
        ''' </param>
        ''' <param name="time">
        ''' Pointer to a double value, which returns the calculated time in seconds, e. g. period [s].
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_SINGLE_TICKS_TO_TIME_NO_FLAGS"/>: (default)
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_TIMER"/>: not supported timer ID.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported
        ''' </returns>
        ''' <remarks>
        ''' The conversion and the allowed value range depend on each sub-device and 
        ''' their properties. If hardware limits are exceeded, always the limit values are returned. 
        ''' If you need the dimensions frequency and duty-cycle you can calculate 
        ''' them easily by the return values from <paramref name="time"/>. It applies: 
        ''' Frequency [Hz] = 1/period [s] 
        ''' Duty-cycle [%] = ("Duration of the first phase of the period" [s] / period [s]) * 100
        ''' </remarks>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOSingleTicksToTime(ByVal device As Integer, ByVal subdevice As Integer, ByVal timer As Integer, ByVal ticksLow As Integer, ByVal ticksHigh As Integer, ByRef time As Double, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOSingleTimeToTicks"
        ''' <summary>
        ''' Converts a given time period [s] into the number of "ticks" to be passed to the 
        ''' timer in the function meIOSingleConfig.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="timer">
        ''' Ticks will be calculated in dependency of the sub-device type and the 
        ''' timer specified here. The values <paramref name="ticksLow"/> and <paramref name="ticksHigh"/> 
        ''' can be passed to the parameter value of the function <see cref="meIOSingle"/>.
        ''' <see cref="ME_TIMER_FIO_TOTAL"/>: The period is converted into ticks. 
        ''' <see cref="ME_TIMER_FIO_FIRST_PHASE"/>: The duration of the first phase of the period is converted into ticks.
        ''' </param>
        ''' <param name="time">
        ''' (in) Pointer to a double value, passing the asked time in seconds, e. g. the period [s] 
        ''' to be converted into ticks. If you pass invalid values a corresponding error code will be returned.
        ''' (out) If the asked time cannot be realized exactly by the hardware the 
        ''' value next lower to it will be returned here. The corresponding ticks are 
        ''' returned in the parameters <paramref name="ticksLow"/> and <paramref name="ticksHigh"/>.
        ''' </param>
        ''' <param name="ticksLow">
        ''' Pointer to an integer value, which contains the lower significant 32 bits 
        ''' (31...0) of the calculated ticks. To be passed to the parameter 
        ''' value of the function <see cref="meIOSingle"/>. 
        ''' </param>
        ''' <param name="ticksHigh">
        ''' Pointer to an integer value, which contains the higher significant 32 bits 
        ''' (63...32) of the calculated ticks. This parameter is resevered for future enhancements.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_SINGLE_TIME_TO_TICKS_NO_FLAGS"/>: (default)
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_TIMER"/>: not supported timer ID.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported
        ''' </returns>
        ''' <remarks>
        ''' The conversion and the allowed value range depend on each sub-device and 
        ''' their properties. If hardware limits are exceeded, an error message is returned.
        ''' </remarks>
        ''' <seealso cref="meIOSingle"/>
        ''' <seealso cref="meIOSingleTicksToTime"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOSingleTimeToTicks(ByVal device As Integer, ByVal subdevice As Integer, ByVal timer As Integer, ByRef time As Double, ByRef ticksLow As Integer, ByRef ticksHigh As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOSetChannelOffset"
        ''' <summary>
        ''' The anlog input ranges can be adjusted.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="channel">
        ''' Index of the channel whose offset should be adjusted.
        ''' </param>
        ''' <param name="range">
        ''' Index of the measurement range to be used for the measurement.
        ''' </param>
        ''' <param name="offset">
        ''' (in) Reference to a double value, passing the asked offset
        ''' (out) If the asked offset value cannot be realized exactly 
        ''' by the hardware the currently adjusted value will be returned.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_SET_CHANNEL_OFFSET_NO_FLAGS"/>: No flags used. Default settings.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' </returns>
        ''' <seealso cref="meQueryNumberRanges"/>
        ''' <seealso cref="meQueryRangeByMinMax"/>
        ''' <seealso cref="meQueryRangeInfo"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOSetChannelOffset(ByVal device As Integer, ByVal subdevice As Integer, ByVal channel As Integer, ByVal range As Integer, ByRef offset As Double, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamConfig"
        ''' <summary>
        ''' Configures the hardware for a timer-controlled streaming operation.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="configList">
        ''' Reference to a list of type <see cref="meIOStreamConfig_t"/>.
        ''' </param>
        ''' <param name="count">
        ''' Number of entries in <paramref name="configList"/>.
        ''' </param>
        ''' <param name="trigger">
        ''' Pointer to a structure of type <see cref="meIOStreamTrigger_t"/>. 
        ''' </param>
        ''' <param name="fifoIrqThreshold">
        ''' Number of values to be read or written (reloaded) in one package.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_CONFIG_NO_FLAGS"/>: Flag for continuous mode (default setting).
        ''' MEphisto Scope: analog acquisition
        ''' <see cref="ME_IO_STREAM_CONFIG_BIT_PATTERN"/>: Bit pattern output and FIFO redirection. 
        ''' MEphisto Scope: Digital acquisition.
        ''' <see cref="ME_IO_STREAM_CONFIG_WRAPAROUND"/>: Flag for wraparound mode (periodical output).
        ''' Disables software buffer. Used only in combination with ME_IO_STREAM_CONFIG_WRAPAROUND flag.
        ''' <see cref="ME_IO_STREAM_CONFIG_SAMPLE_AND_HOLD"/>: Enables "Sample Hold" feature.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CHANNEL"/>: no channel available on sub-device.
        ''' <see cref="ME_ERRNO_LOCKED"/>: device or some of sub-devices are protected.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_REF"/>: parameter <see cref="meIOStreamConfig_t"/>.iRef is not correct.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_START_TRIG_CHAN"/>: parameter <paramref name="meIOStreamConfig_t"/>.iAcqStartTrigChan is not correct.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_START_TRIG_EDGE"/>: parameter <paramref name="meIOStreamConfig_t"/>.iAcqStartTrigEdge is not correct.
        ''' <see cref="ME_ERRNO_INVALID_STREAM_CONFIG"/>: parameter <paramref name="meIOStreamConfig_t"/>.iStreamConfig is not correct.
        ''' <see cref="ME_ERRNO_TIMEOUT"/>: timeout condition occurred.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: sub-device was not configured for required operation.
        ''' <see cref="ME_ERRNO_SUBDEVICE_BUSY"/>: sub-device is performing other operation.
        ''' <see cref="ME_ERRNO_INVALID_FIFO_IRQ_THRESHOLD"/>: parameter <paramref name="iFifoIrqThreshold"/> is not valid (too big).
        ''' <see cref="ME_ERRNO_INVALID_CONFIG_LIST_COUNT"/>: Wrong iCount of configuration list.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_START_TRIG_TYPE"/>: parameter <paramref name="meIOStreamConfig_t"/>.iAcqStartTrigType is not correct.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_START_ARG"/>: interval <paramref name="meIOStreamConfig_t"/>.iAcqStartTicks is not correct.
        ''' <see cref="ME_ERRNO_INVALID_SCAN_START_ARG"/>: interval <paramref name="meIOStreamConfig_t"/>.iScanStartTicks is not correct.
        ''' <see cref="ME_ERRNO_INVALID_CONV_START_ARG"/>: interval <paramref name="meIOStreamConfig_t"/>.iConvStartTicks is not correct.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_STOP_TRIG_TYPE"/>: parameter <paramref name="meIOStreamConfig_t"/>.iConvStartTrigType is not correct.
        ''' <see cref="ME_ERRNO_INVALID_SCAN_STOP_TRIG_TYPE"/>: parameter <paramref name="meIOStreamConfig_t"/>.iConvStartTrigType is not correct.
        ''' <see cref="ME_ERRNO_INVALID_ACQ_STOP_ARG"/>: parameter <paramref name="meIOStreamConfig_t"/>.iAcqStopCount is not correct.
        ''' <see cref="ME_ERRNO_INVALID_SCAN_STOP_ARG"/>: parameter <paramref name="meIOStreamConfig_t"/>.iScanStopCount is not correct
        ''' </returns>
        ''' <remarks>
        ''' For periodic bit pattern output and for periodic DEMUX operation 
        ''' the constant ME_IO_STREAM_CONFIG_WRAPAROUND must be ORed 
        ''' with the constant ME_IO_STREAM_CONFIG_ BIT_PATTERN.
        ''' For analog and digital (bit pattern output) streaming operations 
        ''' a channel-list must be created, which contains an entry for 
        ''' each channel (channel index, measurement range...) of type meIOStreamConfig_t.
        ''' Additionally a trigger structure (meIOStreamTrigger_t) is required, 
        ''' which defines numerous settings like start/stop conditions, timer settings, 
        ''' trigger sources and trigger edges valid for the whole operation.
        ''' The operation is always started by the function meIOStreamStart() 
        ''' either at once (software start) or in accordance with the start 
        ''' conditions defined in the function meIOStreamConfig(). 
        ''' Stop the operation either according to the stop conditions 
        ''' defined in the trigger structure or by calling the function meIOStreamStop().
        ''' </remarks>
        ''' <seealso cref="meIOStreamFrequencyToTicks"/>
        ''' <seealso cref="meIOStreamFrequencyToTicks"/>
        ''' <seealso cref="meIOStreamStart"/>
        ''' <seealso cref="meIOStreamStop"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamConfig(ByVal device As Integer, ByVal subdevice As Integer, ByRef configList As meIOStreamConfig_t, ByVal count As Integer, ByRef trigger As meIOStreamTrigger_t, ByVal fifoIrqThreshold As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamRead"
        ''' <summary>
        ''' Reads values from the data buffer during a timer-controlled acquisition.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="readMode">
        ''' <see cref="ME_READ_MODE_BLOCKING"/>: (BLOCKING mode) The function waits until the number of 
        ''' measurement values specified in parameter <paramref name="count"/> has been acquired.
        ''' Important: Call can block for ever!
        ''' <see cref="ME_READ_MODE_NONBLOCKING"/>: (NONBLOCKING mode) The function returns immediately 
        ''' either with the number of measurement values available when calling 
        ''' the function or with the number specified in <paramref name="count"/>. 
        ''' Each time the lower value is valid.
        ''' </param>
        ''' <param name="values">
        ''' Reference to a data buffer to be filled up.
        ''' </param>
        ''' <param name="count">
        ''' (in) Size of the data buffer to be read in number of measurement values.
        ''' (out) The pointer returns the number of values actually read from the data buffer.
        ''' If in BLOCKING mode the acquisition has been cancelled, the return value can also be less than the value passed.
        ''' BLOCKING mode:
        ''' Number of values to be read – as a rule a multiple of the channel-list length, 
        ''' but this is not necessary (see also meUtilityExtractValues() on page 169).
        ''' NONBLOCKING mode:
        ''' Number of values to be read – if you want to read a multiple of channel-list 
        ''' length use the constant ME_IO_STREAM_ READ_FRAMES in the parameter <paramref name="flags"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_READ_NO_FLAGS"/>: Default settings.
        ''' <see cref="ME_IO_STREAM_READ_FRAMES"/>: Reading a multiple of channel-list length in NONBLOCKING mode.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_VALUE_COUNT"/>: <paramref name="count"/> is lower than zero.
        ''' <see cref="ME_ERRNO_INVALID_READ_MODE"/>: not supported read mode detected.
        ''' <see cref="ME_ERRNO_SUBDEVICE_NOT_RUNNING"/>: buffer is empty and sub-device is not running a streaming operation.
        ''' </returns>
        ''' <remarks>
        ''' The user has to allocate a data buffer, to which the measurement values are written to. 
        ''' Using the execution mode BLOCKING the function meIOStreamRead() returns when the last 
        ''' value has been read. In NONBLOCKING mode the function returns at once 
        ''' with the available measurement values. For reading the data a callback function can also be used.
        ''' </remarks>
        ''' <seealso cref="meIOStreamStatus"/>
        ''' <seealso cref="meIOStreamSetCallbacks"/>
        ''' <seealso cref="meUtilityDigitalToPhysical"/>
        ''' <seealso cref="meUtilityExtractValues"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamRead(ByVal device As Integer, ByVal subdevice As Integer, ByVal readMode As Integer, ByRef values As Integer, ByRef count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamWrite"
        ''' <summary>
        ''' Writes data to a buffer for timer-controlled analog resp. digital output.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="writeMode">
        ''' <see cref="ME_WRITE_MODE_BLOCKING"/>: The function waits until the number of values specified 
        ''' in parameter <paramref name="count"/> can be written to the internal buffer.
        ''' Important: Call can block for ever!
        ''' <see cref="ME_WRITE_MODE_NONBLOCKING"/>: With this option the function writes as many values 
        ''' to the internal buffer as there is space at the moment the function was called 
        ''' (max. number specified in <paramref name="count"/>).
        ''' <see cref="ME_WRITE_MODE_PRELOAD"/>: Pre-loading the data buffer for the first time. 
        ''' Data will be written directly to the hardware buffer. 
        ''' If there are more data as there is space in the FIFO the rest is stored in an internal buffer.
        ''' Note: This is non-blocking writing.
        ''' </param>
        ''' <param name="values">
        ''' Pointer to a data buffer (data stream) with the values resp. bit patterns to be output. 
        ''' Use the function <seealso cref="meUtilityPhysicalToDigital"/> for easy conversion of physical 
        ''' values (e. g. voltage) into digital values.
        ''' </param>
        ''' <param name="count">
        ''' (in): Number of values to be loaded into the data buffer.
        ''' (out): The pointer returns the number of values which could be written into the data buffer actually. 
        ''' The number will never be greater, but can also be less, 
        ''' if there is less memory for the number of values passed.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_WRITE_NO_FLAGS"/>: Default settings – no flags available
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_VALUE_COUNT"/>: <paramref name="count"/> is lower than zero.
        ''' Note: When <paramref name="count"/> is set to zero ME_ERRNO_SUCCESS is returned.
        ''' <see cref="ME_ERRNO_INVALID_WRITE_MODE"/>: not supported write mode detected.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: device is configured to work in single mode.
        ''' <see cref="ME_ERRNO_SUBDEVICE_NOT_RUNNING"/>: The internal hardware state machine is stopped but 
        ''' logical status show that should be working. No data in FIFO but software buffer is not empty
        ''' </returns>
        ''' <remarks>
        ''' For the values to be output allocate a data buffer of defined size for each sub-device to be used.
        ''' </remarks>
        ''' <seealso cref="meIOStreamRead"/>
        ''' <seealso cref="meUtilityPhysicalToDigital"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamWrite(ByVal device As Integer, ByVal subdevice As Integer, ByVal writeMode As Integer, ByRef values As Integer, ByRef count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamSetCallbacks"
        ''' <summary>
        ''' Installs different callback functions that wait for an event on a streaming sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="startCB">
        ''' Delegate to an user-defined function. This function is called when streaming operation starts. 
        ''' If the function exits with a return value different than <see cref="ME_ERRNO_SUCCESS"/> 
        ''' streaming is instantly stopped, <seealso cref="meIOStreamStop"/> is executed.
        ''' </param>
        ''' <param name="startCBContext">
        ''' User-defined pointer passed to start callback function. 
        ''' This parameter is optional. If you don't want to use this functionality pass NULL.
        '''  </param>
        ''' <param name="newValuesCB">
        ''' Pointer to an user-defined function. This function is called when the buffer status is changing. 
        ''' If the function exits with a return value different than <see cref="ME_ERRNO_SUCCESS"/> 
        ''' streaming is instantly stopped, <seealso cref="meIOStreamStop"/> is executed.
        ''' </param>
        ''' <param name="newValuesCBContext">
        ''' User-defined pointer passed to new values callback function. This parameter is optional. 
        ''' If you don't want to use this functionality pass NULL
        ''' </param>
        ''' <param name="endCB">
        ''' Pointer to an user-defined function. This function is called when streaming operation stops.
        ''' </param>
        ''' <param name="endCBContext">
        ''' User-defined pointer passed to stop callback function. This parameter is optional. 
        ''' If you don't want to use this functionality pass NULL.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_SET_CALLBACKS_NO_FLAGS"/>: (no flags available)
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' To deinstall/cancel all registered callback instances for the selected sub-device call 
        ''' meIOStreamSetCallbacks() with all callback pointers 
        ''' (<paramref name="startCB"/>, <paramref name="newValuesCB"/> and <paramref name="endCB"/>) set to NULL.
        ''' </remarks>
        ''' <seealso cref="meIOStreamStart"/>
        ''' <seealso cref="meIOStreamStop"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamSetCallbacks(ByVal device As Integer, ByVal subdevice As Integer, ByRef startCB As meIOStreamCB_t, ByVal startCBContext As IntPtr, ByVal newValuesCB As meIOStreamCB_t, ByVal newValuesCBContext As IntPtr, endCB As meIOStreamCB_t, ByVal endCBContext As IntPtr, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamStart"
        ''' <summary>
        ''' Starts streaming operations.
        ''' </summary>
        ''' <param name="startList">
        ''' Pointer to a list of type meIOStreamStart_t, by which one or more streaming operations can be started. 
        ''' The start is done immediately after calling the function corresponding to the start conditions. 
        ''' If for one or more list entries the <see cref="meIOStreamStart_t"/>.iStartMode
        ''' </param>
        ''' <param name="count">
        ''' Number of meIOStreamStart_t entries in <paramref name="startList"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_START_NO_FLAGS"/>: Default settings. Execute list up to the first error. 
        ''' Returned value corresponds with the first non-zero <see cref="meIOStreamStart_t"/>.iErrno field.
        ''' <see cref="ME_IO_STREAM_START_NONBLOCKING"/>: (Linux only) Execute whole start list. 
        ''' When this flag is set execution is processed although an error occured for some entries. 
        ''' The function returns ME_ERRNO_SUCCESS when no global error was detected. 
        ''' <see cref="meIOStreamStart_t"/>.iErrno fields have to be checked.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of the passed flags are not supported.
        ''' <see cref="ME_ERRNO_INVALID_TIMEOUT"/>: timeout lower than 0.
        ''' <see cref="ME_ERRNO_INVALID_START_MODE"/>: not supported start mode detected.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: sub-device is not configured correctly to proceed streaming operation.
        ''' <see cref="ME_STATUS_ERROR"/>: previous operation ended with an error. Reset has to be called to clear this state.
        ''' <see cref="ME_ERRNO_LACK_OF_RESOURCES"/>: (output only) operation can not be proceed. Buffers are empty. (Linux only)
        ''' <see cref="ME_ERRNO_TIMEOUT"/>: Operation didn't start on time.
        ''' <see cref="ME_ERRNO_START_THREAD"/>: creating callback thread failed. (Windows only)
        ''' </returns>
        ''' <remarks>
        ''' Returning of the function depends on the <see cref="meIOStreamStart_t"/>.iStartMode
        ''' (BLOCKING or NONBLOCKING) and trigger conditions defined in the function <see cref="meIOStreamConfig"/>.
        ''' </remarks>
        ''' <seealso cref="meIOStreamStart_t"/>
        ''' <seealso cref="meIOStreamConfig"/>
        ''' <seealso cref="meIOStreamStop"/>
        ''' <seealso cref="meIOResetDevice"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamStart(ByRef startList As meIOStreamStart_t, ByVal count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamStatus"
        ''' <summary>
        ''' Checks the status of streaming operation.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="wait">
        ''' Behaviour of return of this function:
        ''' <see cref="ME_WAIT_NONE"/>: Check current status. 
        ''' Function returns the current state of operation immediately in parameter <paramref name="status"/>.
        ''' <see cref="ME_WAIT_IDLE"/>: In case of an output operation the function waits until all values have been output. 
        ''' The function returns with <see cref="ME_STATUS_IDLE"/> in parameter <paramref name="status"/>.
        ''' Important: Call can block for ever!
        ''' <see cref="ME_WAIT_BUSY"/>: (Linux only)
        ''' The function blocks while the status is <see cref="ME_STATUS_BUSY"/>
        ''' Important: Call can block for ever!
        ''' </param>
        ''' <param name="status">
        ''' Pointer which returns the current state of operation of the specified sub-device.
        ''' <see cref="ME_STATUS_IDLE"/>: Streaming operation has finished.
        ''' <see cref="ME_STATUS_BUSY"/>: Streaming operation is still running.
        ''' <see cref="ME_STATUS_ERROR"/>: Error occured, e. g. data stream was interrupted.
        ''' </param>
        ''' <param name="count">
        ''' Input sub-device: Number of values which can be read
        ''' Output sub-device: Free memory in the output buffer (in number of values)
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_STATUS_NO_FLAGS"/>: Default settings – no flags available
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: unsupported flag detected.
        ''' <see cref="ME_ERRNO_INVALID_WAIT"/>: not supported wait mode detected.
        ''' </returns>
        ''' <remarks>
        ''' Depending on input or output operation this function is used to check whether 
        ''' all measurement values have been acquired or whether an output operation is still running.
        ''' With the parameter <paramref name="wait"/> you can control, whether the function 
        ''' should return the current state at once, or whether you want to wait 
        ''' until the input resp. output operation has been ended.
        ''' </remarks>
        ''' <seealso cref="meIOStreamRead"/>
        ''' <seealso cref="meIOStreamWrite"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamStatus(ByVal device As Integer, ByVal subdevice As Integer, ByVal wait As Integer, ByRef status As Integer, ByRef count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamStop"
        ''' <summary>
        ''' An "infinite" operation can be cancelled at once or stopped in a defined way.
        ''' </summary>
        ''' <param name="stopList">
        ''' Pointer to a list of type <see cref="meIOStreamStop_t"/> to end one or several input/output operations. 
        ''' Stopping is done in accordance to parameter <see cref="meIOStreamStop_t"/>.iStopMode.
        ''' </param>
        ''' <param name="count">
        ''' Number of <see cref="meIOStreamStop_t"/> entries in <paramref name="stopList"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_STREAM_STOP_NO_FLAGS"/>: Default settings. 
        ''' Execute list up to the first error. 
        ''' Returned value corresponds with the first non-zero <see cref="meIOStreamStop_t"/>.iErrno field.
        ''' <see cref="ME_IO_STREAM_STOP_NONBLOCKING"/>: (Linux only)
        ''' Execute whole stop list one by one. When this flag is set execution is processed 
        ''' although an error occured for some entries. The function returns ME_SUCCESS 
        ''' when no global error was detected. <see cref="meIOStreamStop_t"/>.iErrno fields have to be checked.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: unsupported flag detected.
        ''' <see cref="ME_ERRNO_INVALID_STOP_MODE"/>: not supported stop mode detected.
        ''' <see cref="ME_ERRNO_PREVIOUS_CONFIG"/>: sub-device is not configured correctly to proceed streaming operation.
        ''' <see cref="ME_STATUS_ERROR"/>: previous operation ended with an error. Reset has to be called to clear this state.
        ''' </returns>
        ''' <remarks>
        ''' With meIOStreamStop you have the possibility to stop an output operation by the last entry 
        ''' in the FIFO which is a known value.
        ''' If in the parameters iAcqStopCount resp. iScanStopCount of the function meIOStreamConfig() 
        ''' stop conditions have been defined, calling the function meIOStreamStop() is not necessary.
        ''' Configuration of the sub-device remains preserved (channel-list, timer...) 
        ''' so that a restart with the function <see cref="meIOStreamStart"/> is possible without new configuration.
        ''' In opposite to this using the function <see cref="meIOResetDevice"/> deletes the whole configuration of the device.
        ''' </remarks>
        ''' <seealso cref="meIOStreamStop_t"/>
        ''' <seealso cref="meIOResetDevice"/>
        ''' <seealso cref="meIOStreamStart"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamStop(ByRef stopList As meIOStreamStop_t, ByVal count As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamFrequencyToTicks"
        ''' <summary>
        ''' Converts a given frequency [Hz] into the number of "ticks"
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="timer">
        ''' Ticks will be calculated in dependency of the sub-device to which the specified timer belongs to. 
        ''' The values <paramref name="ticksLow"/> and <paramref name="ticksHigh"/> are passed 
        ''' in the trigger structure of the function <see cref="meIOStreamConfig"/> 
        ''' <see cref="ME_TIMER_ACQ_START"/>: <see cref="meIOStreamTrigger_t"/>.iAcqStartTicks 
        ''' should be calculated for passing to the parameter of the same name. 
        ''' <see cref="ME_TIMER_SCAN_START"/>: <see cref="meIOStreamTrigger_t"/>.iScanStartTicks 
        ''' should be calculated for passing to the parameter of the same name.  
        ''' <see cref="ME_TIMER_CONV_START"/>: <see cref="meIOStreamTrigger_t"/>.iConvStartTicks 
        ''' should be calculated for passing to the parameter of the same name. 
        ''' </param>
        ''' <param name="frequency">
        ''' Pointer to a double value, passing the asked frequency [Hz] to be converted into ticks.
        ''' If you pass „0“ the maximum frequency will be returned.
        ''' If the asked frequency cannot be realized exactly by the hardware the frequency next higher 
        ''' to it will be returned as an approximation. 
        ''' The corresponding ticks are returned in the parameters <paramref name="ticksLow"/> and <paramref name="ticksHigh"/>.
        ''' </param>
        ''' <param name="ticksLow">
        ''' Pointer to an integer value, which contains the lower significant 32 bits (31...0) of the calculated ticks. 
        ''' Will be passed to the appropriate parameter startTicksLow of the function <see cref="meIOStreamConfig"/>.
        ''' </param>
        ''' <param name="ticksHigh">
        ''' Pointer to an integer value, which contains the higher significant 32 bits (63...32) of the calculated ticks. 
        ''' Will be passed to the appropriate parameter startTicksHigh of the function <see cref="meIOStreamConfig"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_FREQUENCY_TO_TICKS_NO_FLAGS"/>: (default) MEphisto Scope: data-logging mode
        ''' <see cref="ME_IO_FREQUENCY_TO_TICKS_MEPHISTO_SCOPE_OSCILLOSCOPE"/>: MEphisto Scope: oscilloscope mode
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_TIMER"/>: not supported timer ID.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' The conversion and the allowed value range depend on each sub-device and their timers. 
        ''' If hardware limits are exceeded, always the limit values are returned.
        ''' Tip: Passing "0" in parameter <paramref name="frequency"/> of this function returns the maximum frequency allowed. 
        ''' In dependency of parameter <paramref name="timer"/> of this function the return values of 
        ''' <paramref name="ticksLow"/> and <paramref name="ticksHigh"/> can be passed to the corresponding parameters 
        ''' <see cref="meIOStreamTrigger_t"/>.iAcqStartTicks, <see cref="meIOStreamTrigger_t"/>.iConvStartTicks 
        ''' and <see cref="meIOStreamTrigger_t"/>.iScanStartTicks in the trigger structure of function <see cref="meIOStreamConfig"/>.
        ''' </remarks>
        ''' <seealso cref="meIOStreamTimeToTicks"/>
        ''' <seealso cref="meIOStreamConfig"/>
        ''' <seealso cref="meIOStreamTrigger_t"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamFrequencyToTicks(ByVal device As Integer, ByVal subdevice As Integer, ByVal timer As Integer, ByRef frequency As Double, ByRef ticksLow As Integer, ByRef ticksHigh As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meIOStreamTimeToTicks"
        ''' <summary>
        ''' Converts a given time period [s] into the number of "ticks".
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="timer">
        ''' Ticks will be calculated in dependency of the sub-device to which the specified timer belongs to. 
        ''' The values <paramref name="ticksLow"/> and <paramref name="ticksHigh"/> are passed 
        ''' in the trigger structure of the function <see cref="meIOStreamConfig"/> 
        ''' <see cref="ME_TIMER_ACQ_START"/>: <see cref="meIOStreamTrigger_t"/>.iAcqStartTicks 
        ''' should be calculated for passing to the parameter of the same name. 
        ''' <see cref="ME_TIMER_SCAN_START"/>: <see cref="meIOStreamTrigger_t"/>.iScanStartTicks 
        ''' should be calculated for passing to the parameter of the same name.  
        ''' <see cref="ME_TIMER_CONV_START"/>: <see cref="meIOStreamTrigger_t"/>.iConvStartTicks 
        ''' should be calculated for passing to the parameter of the same name. 
        ''' </param>
        ''' <param name="time">
        ''' (in): Pointer to a double value, passing the asked period [s] to be converted into ticks. 
        ''' If you pass "0" the minimum period will be returned.
        ''' (out): If the asked period cannot be realized exactly by the hardware the 
        ''' period next lower to it will be returned as an approximation. The corresponding ticks 
        ''' are returned in the parameters <paramref name="ticksLow"/> and <paramref name="ticksHigh"/>.
        ''' </param>
        ''' <param name="ticksLow">
        ''' Pointer to an integer value, which contains the lower significant 32 bits (31...0) of the calculated ticks. 
        ''' Will be passed to the appropriate parameter startTicksLow of the function <see cref="meIOStreamConfig"/>.
        ''' </param>
        ''' <param name="ticksHigh">
        ''' Pointer to an integer value, which contains the higher significant 32 bits (63...32) of the calculated ticks. 
        ''' Will be passed to the appropriate parameter startTicksHigh of the function <see cref="meIOStreamConfig"/>.
        ''' </param>
        ''' <param name="flags">
        ''' <see cref="ME_IO_TIME_TO_TICKS_NO_FLAGS"/>: (default) MEphisto Scope: data-logging mode
        ''' <see cref="ME_IO_TIME_TO_TICKS_MEPHISTO_SCOPE_OSCILLOSCOPE"/>: MEphisto Scope: oscilloscope mode
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_TIMER"/>: not supported timer ID.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: some of passed flags are not supported.
        ''' </returns>
        ''' <remarks>
        ''' The conversion and the allowed value range depend on each sub-device and their timers. 
        ''' If hardware limits are exceeded, always the limit values are returned. 
        ''' Tip: Passing "0" in parameter <paramref name="time"/> of this function returns the 
        ''' minimum frequency allowed. In dependency of parameter <paramref name="timer"/> of 
        ''' this function the return values of <paramref name="ticksLow"/> and <paramref name="ticksHigh"/> 
        ''' can be passed to the corresponding parameters <see cref="meIOStreamTrigger_t"/>.iAcqStartTicks, 
        ''' <see cref="meIOStreamTrigger_t"/>.iConvStartTicks and <see cref="meIOStreamTrigger_t"/>.iScanStartTicks 
        ''' in the trigger structure of function <see cref="meIOStreamConfig"/>.
        ''' </remarks>
        ''' <seealso cref="meIOStreamFrequencyToTicks"/>
        ''' <seealso cref="meIOStreamConfig"/>
        ''' <seealso cref="meIOStreamTrigger_t"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meIOStreamTimeToTicks(ByVal device As Integer, ByVal subdevice As Integer, ByVal timer As Integer, ByRef time As Double, ByRef ticksLow As Integer, ByRef ticksHigh As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meQueryDescriptionDevice"
        ''' <summary>
        ''' Determines the device description.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="description">
        ''' Buffer to hold the device description.
        ''' </param>
        ''' <param name="count">
        ''' Buffer size in bytes for device description. 
        ''' Recommended: <see cref="ME_DEVICE_DESCRIPTION_MAX_COUNT"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_USER_BUFFER_SIZE"/>: count smaller than 1.
        ''' </returns>
        ''' <seealso cref="meQueryInfoDevice"/>
        ''' <seealso cref="meQueryNameDevice"/>
        ''' <seealso cref="meQueryNumberDevices"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function meQueryDescriptionDevice(ByVal device As Integer, description As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meQueryInfoDevice"
        ''' <summary>
        ''' Determines detailed information of the device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="vendorId">
        ''' Pointer returns vendor ID of the device.
        ''' 0x1402 for Meilhaus PCI boards, 0x1B04 for USB devices like e. g. ME-1 (ME-Synapse USB).
        ''' </param>
        ''' <param name="deviceId">
        ''' Pointer returns the device ID.
        ''' </param>
        ''' <param name="serialNo">
        ''' Pointer returns the serial number of the device.
        ''' </param>
        ''' <param name="busType">
        ''' Pointer returns the bus type by which the device is connected with the PC (PCI/cPCI, USB).
        ''' </param>
        ''' <param name="busNo">
        ''' PCI only: Pointer returns the PCI bus number, if several PCI buses are available in your system (if one bus it is always "0")
        ''' </param>
        ''' <param name="slot">
        ''' PCI only: Slot number of the board to be accessed.
        ''' </param>
        ''' <param name="funcNo">
        ''' PCI: Function number.
        ''' </param>
        ''' <param name="plugged">
        ''' Pointer indicates whether a device is physically available.
        ''' <see cref="ME_PLUGGED_IN"/>: Device physically available.
        ''' <see cref="ME_PLUGGED_OUT"/>: Device registered with the ME-iDC (ME-Config-Tool) but not connected with the PC.
        ''' <see cref="ME_PLUGGED_INVALID"/>: invalid return value
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' </returns>
        ''' <remarks>
        ''' This is a PCI orientated function and some parameters have no meaning for 
        ''' ME-Synapse USB or ME-Synapse LAN.
        ''' </remarks>
        ''' <seealso cref="meQueryDescriptionDevice"/>
        ''' <seealso cref="meQueryNameDevice"/>
        ''' <seealso cref="meQueryNumberDevices"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryInfoDevice(ByVal device As Integer, ByRef vendorId As Integer, ByRef deviceId As Integer, ByRef serialNo As Integer, ByRef busType As Integer, ByRef busNo As Integer, ByRef slot As Integer, ByRef funcNo As Integer, ByRef plugged As Integer) As Integer
        End Function
#End Region


#Region "meQueryNameDevice"
        ''' <summary>
        ''' Determines the device name.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="name">
        ''' Buffer for the device name.
        ''' </param>
        ''' <param name="count">
        ''' Buffer size in bytes for device name. Recommended: <see cref="ME_DEVICE_NAME_MAX_COUNT"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_USER_BUFFER_SIZE"/>: count smaller than 1.
        ''' </returns>
        ''' <seealso cref="meQueryInfoDevice"/>
        ''' <seealso cref="meQueryDescriptionDevice"/>
        ''' <seealso cref="meQueryNumberDevices"/>
        ''' <seealso cref="meQueryNameDeviceDriver"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function meQueryNameDevice(ByVal device As Integer, name As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meQueryNameDeviceDriver"
        ''' <summary>
        ''' Determines the name of the device specific driver module.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="name">
        ''' Pointer to a buffer for the driver module.
        ''' </param>
        ''' <param name="count">
        ''' Buffer size in bytes for the driver module. 
        ''' Recommended: <see cref="ME_DEVICE_DRIVER_NAME_MAX_COUNT"/>.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_USER_BUFFER_SIZE"/>: count smaller than 1.
        ''' </returns>
        ''' <seealso cref="meQueryVersionDeviceDriver"/>
        ''' <seealso cref="meQueryVersionMainDriver"/>
        ''' <seealso cref="meQueryVersionLibrary"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function meQueryNameDeviceDriver(ByVal device As Integer, name As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meQueryNumberDevices"
        ''' <summary>
        ''' Determines the number of devices recognized by the ME-iDS.
        ''' </summary>
        ''' <param name="count">
        ''' Contains the number of recognized devices after the function returned.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <remarks>
        ''' Not all devices have to be physically present.
        ''' This can be tested with the function <see cref="meQueryInfoDevice"/>.
        ''' </remarks>
        ''' <seealso cref="meQueryInfoDevice"/>
        ''' <seealso cref="meQueryNumberSubdevices"/>
        ''' <seealso cref="meQueryNumberChannels"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryNumberDevices(ByRef count As Integer) As Integer
        End Function
#End Region


#Region "meQueryNumberSubdevices"
        ''' <summary>
        ''' Determines the number of sub-devices on a queried device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="count">
        ''' Number of sub-devices on the device.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' </returns>
        ''' <seealso cref="meQueryNumberDevices"/>
        ''' <seealso cref="meQueryNumberChannels"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryNumberSubdevices(ByVal device As Integer, ByRef count As Integer) As Integer
        End Function
#End Region


#Region "meQueryNumberChannels"
        ''' <summary>
        ''' Determines the number of channels of a sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="count">
        ''' Returns the number of channels of the specified sub-device.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' </returns>
        ''' <seealso cref="meQueryNumberDevices"/>
        ''' <seealso cref="meQueryNumberSubdevices"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryNumberChannels(ByVal device As Integer, ByVal subdevice As Integer, ByRef count As Integer) As Integer
        End Function
#End Region


#Region "meQueryNumberChannels"
        ''' <summary>
        ''' Determines the number of ranges which support the specified measurement range(s).
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="unit">
        ''' Restrict the query to the specified measurement range(s).
        ''' <see cref="ME_UNIT_ANY"/>: Query for all ranges
        ''' <see cref="ME_UNIT_VOLT"/>: Query only for voltage ranges
        ''' <see cref="ME_UNIT_AMPERE"/>: Query only for current ranges
        ''' </param>
        ''' <param name="count">
        ''' Returns the number of ranges which support the specified measurement range(s).
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_NOT_SUPPORTED"/>: function is not supported by sub-device.
        ''' </returns>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meQueryRangeByMinMax"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryNumberRanges(ByVal device As Integer, ByVal subdevice As Integer, ByVal unit As Integer, ByRef count As Integer) As Integer
        End Function
#End Region


#Region "meQueryRangeByMinMax"
        ''' <summary>
        ''' Determines the appropriate measurement range by given limits
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="unit">
        ''' Restrict the query to the specified measurement range(s).
        ''' <see cref="ME_UNIT_ANY"/>: Query for all ranges
        ''' <see cref="ME_UNIT_VOLT"/>: Query only for voltage ranges
        ''' <see cref="ME_UNIT_AMPERE"/>: Query only for current ranges
        ''' </param>
        ''' <param name="min">
        ''' (in) Passing the lower limit of the searched range.
        ''' (out) Returns the lower limit for the range determined.
        ''' </param>
        ''' <param name="max">
        ''' (in) Passing the upper limit of the searched range. 
        ''' (out) Returns the upper limit for the range determined.
        ''' </param>
        ''' <param name="maxData">
        ''' Returns the maximum resolution for the range determined (e. g. 65535 (0xFFFF) for 16 bit resolution).
        ''' </param>
        ''' <param name="rangeIndex">
        ''' The index of the best fitting measurement range is returned. 
        ''' Always the smallest range is chosen, which includes the range limits searched for.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_UNIT"/>: unit's type not supported on sub-device.
        ''' <see cref="ME_ERRNO_INVALID_MIN_MAX"/>: lower limit is higher than upper.
        ''' <see cref="ME_ERRNO_NO_RANGE"/>: fitted range not found.
        ''' </returns>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meQueryNumberRanges"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryRangeByMinMax(ByVal device As Integer, ByVal subdevice As Integer, ByVal unit As Integer, ByRef min As Double, ByRef max As Double, ByRef maxData As Integer, ByRef rangeIndex As Integer) As Integer
        End Function
#End Region


#Region "meQueryRangeInfo"
        ''' <summary>
        ''' Determines details of the specified measurement range.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device that is queried.
        ''' </param>
        ''' <param name="range">
        ''' Index of measurement range that is queried.
        ''' </param>
        ''' <param name="unit">
        ''' Pointer, which returns the physical unit of the specified measurement range.
        ''' <see cref="ME_UNIT_INVALID"/>: Invalid return value
        ''' <see cref="ME_UNIT_VOLT"/>: Voltage range
        ''' <see cref="ME_UNIT_AMPERE"/>: Current range
        ''' </param>
        ''' <param name="min">
        ''' Reference to the lower limit of the requested range. 
        ''' It applies to the physical unit specified in parameter <paramref name="unit"/>.
        ''' </param>
        ''' <param name="max">
        ''' Reference to the upper limit of the requested range.
        ''' It applies to the physical unit specified in parameter <paramref name="unit"/>.
        ''' </param>
        ''' <param name="maxData">
        ''' Returns the maximum resolution of the measurement range (e. g. for 16 bit resolution the value 65535 (0xFFFF) is returned).
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' </returns>
        ''' <seealso cref="meQueryNumberRanges"/>
        ''' <seealso cref="meQueryRangeByMinMax"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryRangeInfo(ByVal device As Integer, ByVal subdevice As Integer, ByVal range As Integer, ByRef unit As Integer, ByRef min As Double, ByRef max As Double, ByRef maxData As Integer) As Integer
        End Function
#End Region


#Region "meQuerySubdeviceByType"
        ''' <summary>
        ''' Determines the index of the first available sub-device which matches the features searching for.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="startSubdevice">
        ''' Index of the sub-device the query starts with.
        ''' </param>
        ''' <param name="type">
        ''' Type of the sub-device searched for:
        ''' <see cref="ME_TYPE_AI"/> Analog acquisition
        ''' <see cref="ME_TYPE_AO"/>: Analog output
        ''' <see cref="ME_TYPE_DIO"/>: Digital input/output (bi-directional)
        ''' <see cref="ME_TYPE_DO"/>: Digital output
        ''' <see cref="ME_TYPE_DI"/>: Digital input
        ''' <see cref="ME_TYPE_FIO"/>: Frequency input/output (bi-directional)
        ''' <see cref="ME_TYPE_FO"/>: Frequency output
        ''' <see cref="ME_TYPE_FI"/>: Frequency input
        ''' <see cref="ME_TYPE_CTR"/>: Counter
        ''' <see cref="ME_TYPE_EXT_IRQ"/>: External interrupt
        ''' </param>
        ''' <param name="subType">
        ''' The capabilities of the sub-device searched for can be specified more detailed if necessary:
        ''' <see cref="ME_SUBTYPE_ANY"/>: Sub-type doesn't matter.
        ''' <see cref="ME_SUBTYPE_SINGLE"/>: Acquisition resp. output of a single value.
        ''' <see cref="ME_SUBTYPE_STREAMING"/>: Continuous acquisition resp. output by using special hardware capabilities (e. g. FIFOs).
        ''' <see cref="ME_SUBTYPE_CTR_8254"/>: Sub-device with a counter of type 8254
        ''' </param>
        ''' <param name="subdevice">
        ''' Reference to the index of the first matching sub-device.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_NO_MORE_SUBDEVICE_TYPE"/>: Matching sub-device not found.
        ''' </returns>
        ''' <seealso cref="meQuerySubdeviceType"/>
        ''' <seealso cref="meQuerySubdeviceCaps"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQuerySubdeviceByType(ByVal device As Integer, ByVal startSubdevice As Integer, ByVal type As Integer, ByVal subtype As Integer, ByRef subdevice As Integer) As Integer
        End Function
#End Region


#Region "meQuerySubdeviceType"
        ''' <summary>
        ''' Determines the type and subtype of the specified sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device that is queried.
        ''' </param>
        ''' <param name="type">
        ''' Reference to the sub-device type:
        ''' <see cref="ME_TYPE_AO"/>: Analog output
        ''' <see cref="ME_TYPE_AI"/> Analog input
        ''' <see cref="ME_TYPE_DIO"/>: Digital input/output (bi-directional)
        ''' <see cref="ME_TYPE_DO"/>: Digital output
        ''' <see cref="ME_TYPE_DI"/>: Digital input
        ''' <see cref="ME_TYPE_FIO"/>: Frequency input/output (bi-directional)
        ''' <see cref="ME_TYPE_FO"/>: Frequency output
        ''' <see cref="ME_TYPE_FI"/>: Frequency input
        ''' <see cref="ME_TYPE_CTR"/>: Counter
        ''' <see cref="ME_TYPE_EXT_IRQ"/>: External interrupt
        ''' </param>
        ''' <param name="subType">
        ''' Returns the subtype of the sub-device:
        ''' <see cref="ME_SUBTYPE_SINGLE"/>: Sub-device is able to acquire resp. output single values.
        ''' <see cref="ME_SUBTYPE_STREAMING"/>: The sub-device can acquire values continuously resp. output a data stream.
        ''' <see cref="ME_SUBTYPE_CTR_8254"/>: Sub-device with a counter of type 8254
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' </returns>
        ''' <seealso cref="meQueryInfoDevice"/>
        ''' <seealso cref="meQuerySubdeviceByType"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQuerySubdeviceType(ByVal device As Integer, ByVal subdevice As Integer, ByRef type As Integer, ByRef subtype As Integer) As Integer
        End Function
#End Region


#Region "meQuerySubdeviceCaps"
        ''' <summary>
        ''' Determines the special capabilities of a sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device that is queried.
        ''' </param>
        ''' <param name="caps">
        ''' Reference to a bit-coded integer value which returns the special capabilities of the specified sub-device.
        ''' If several capabilities apply, the values are ORed bitwise.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' </returns>
        ''' <seealso cref="meQuerySubdeviceCapsArgs"/>
        ''' <seealso cref="meQuerySubdeviceType"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQuerySubdeviceCaps(ByVal device As Integer, ByVal subdevice As Integer, ByRef caps As Integer) As Integer
        End Function
#End Region


#Region "meQuerySubdeviceCapsArgs"
        ''' <summary>
        ''' Determines detailed information of a specific capability of a sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device that is queried.
        ''' </param>
        ''' <param name="cap">
        ''' The capability to be queried.
        ''' </param>
        ''' <param name="args">
        ''' Reference to an array of type integer, which returns the queried values.
        ''' </param>
        ''' <param name="count">
        ''' Number of values in parameter <paramref name="args"/>.  
        ''' As a rule "1", if the returned values fit into an integer.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_CAP"/>: Passed code is invalid or not supported on sub-device.
        ''' <see cref="ME_ERRNO_INVALID_CAP_ARG_COUNT"/>: Parameter <paramref name="count"/> doesn't fit for queried capability code.
        ''' </returns>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQuerySubdeviceCapsArgs(ByVal device As Integer, ByVal subdevice As Integer, ByVal cap As Integer, ByRef args As Integer, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "meQueryVersionLibrary"
        ''' <summary>
        ''' Determines the version number of the library.
        ''' </summary>
        ''' <param name="version">
        ''' Reference to the version number of the library.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <remarks>
        ''' Can be called before calling <see cref="meOpen"/>.
        ''' </remarks>
        ''' <seealso cref="meQueryVersionDeviceDriver"/>
        ''' <seealso cref="meQueryVersionMainDriver"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryVersionLibrary(ByRef version As Integer) As Integer
        End Function
#End Region


#Region "meQueryVersionMainDriver"
        ''' <summary>
        ''' Determines the version number of the main driver.
        ''' </summary>
        ''' <param name="version">
        ''' Reference to the version number of the main driver.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <remarks>
        ''' The two higher significant bytes (main version, sub version) must be the same one as the 
        ''' version number of the device specific driver module. <see cref="meQueryVersionDeviceDriver"/>
        ''' The lower significant bytes (build number) can differ.
        ''' </remarks>
        ''' <seealso cref="meQueryVersionDeviceDriver"/>
        ''' <seealso cref="meQueryVersionLibrary"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryVersionMainDriver(ByRef version As Integer) As Integer
        End Function
#End Region


#Region "meQueryVersionDeviceDriver"
        ''' <summary>
        ''' Determines the version number of the device specific driver module.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="version">
        ''' Reference to the version number of the main driver.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' </returns>
        ''' <remarks>
        ''' The version number must be the same one as the version number of the main driver. 
        '''  <see cref="meQueryVersionMainDriver"/>
        ''' </remarks>
        ''' <seealso cref="meQueryVersionLibrary"/>
        ''' <seealso cref="meQueryVersionMainDriver"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meQueryVersionDeviceDriver(ByVal device As Integer, ByRef version As Integer) As Integer
        End Function
#End Region


#Region "meUtilityExtractValues"
        ''' <summary>
        ''' Extracts the values of the specified channel from an array of values taking the channel-list into account.
        ''' </summary>
        ''' <param name="channel">
        ''' Channel index whose values should be extracted.
        ''' </param>
        ''' <param name="dataBuffer">
        ''' Reference to the data buffer allocated for the function <see cref="meIOStreamRead"/>.
        ''' </param>
        ''' <param name="dataCount">
        ''' Number of measurement values in data buffer <paramref name="dataBuffer"/>.
        ''' </param>
        ''' <param name="configList">
        ''' Pointer to the channel-list, which was passed to the function <see cref="meIOStreamConfig"/>.
        ''' </param>
        ''' <param name="configListCount">
        ''' Number of channel-list entries in <paramref name="configList"/>.
        ''' </param>
        ''' <param name="chanBuffer">
        ''' Pointer to an array with the extracted values of the specified channel.
        ''' </param>
        ''' <param name="chanBufferCount">
        ''' (in) Passing the size of the array <paramref name="chanBuffer"/> in number of values.
        ''' (out) The function returns the number values actually written to <paramref name="chanBuffer"/>.
        ''' Feld <paramref name="chanBuffer"/> channBuffer kopiert.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <remarks>
        ''' To extract the channels for several channels the function must be called separately. 
        ''' Note: If channel is not on list the function returns ME_ERRNO_SUCCESS 
        ''' and <paramref name="chanBufferCount"/> is set to "0".
        ''' </remarks>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityExtractValues(ByVal channel As Integer, ByRef dataBuffer As Integer, ByVal dataCount As Integer, ByRef configList As meIOStreamConfig_t, ByVal configListCount As Integer, ByRef chanBuffer As Integer, ByRef chanBufferCount As Integer) As Integer
        End Function
#End Region


#Region "meUtilityDigitalToPhysical"
        ''' <summary>
        ''' Conversion of the standardized digital values into the appropriate physical unit.
        ''' </summary>
        ''' <param name="min">
        ''' The lower limit of the range e. g. -10[V].
        ''' </param>
        ''' <param name="max">
        ''' The upper limit of the range e. g. +10[V].
        ''' </param>
        ''' <param name="maxData">
        ''' The maximum resolution of the range e. g. 65536 at 16 bit resolution.
        ''' </param>
        ''' <param name="data">
        ''' Digital value (0...65535) to be converted.
        ''' </param>
        ''' <param name="moduleType">
        ''' Support for ME-MultiSig module.
        ''' If for the current calculation no plug-on module must be taken into account,
        ''' pass the constant: <see cref="ME_MODULE_TYPE_MULTISIG_NONE"/>  
        ''' No plug-on module used (standard)
        ''' </param>
        ''' <param name="refValue">
        ''' For a RTD module or a thermo-couple module. Otherwise use: ME_VALUE_NOT_USED.
        ''' </param>
        ''' <param name="physical">
        ''' Result in the corresponding physical unit [V], [A], [°C].
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_VALUE_OUT_OF_RANGE"/>: passed value is lower than "0" or bigger than <paramref name="maxData"/>.
        ''' <see cref="ME_ERRNO_INVALID_MIN_MAX"/>: passed <paramref name="maxData"/> is not valid.
        ''' <see cref="ME_ERRNO_INVALID_MODULE_TYPE"/>: passed module type is not supported.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <remarks>
        ''' If you read data from an input sub-device in streaming mode, you should 
        ''' apply the function <see cref="meUtilityExtractValues"/> to the array of values before 
        ''' calling this function. Only by that way it is guarenteed, that different gain 
        ''' factors and the usage of different plug-on modules in combination with the 
        ''' ME-MultiSig system can be taken into account when calculating.
        ''' If you want to apply the function to a whole array of values we recommend 
        ''' the function <see cref="meUtilityDigitalToPhysicalV"/>.
        ''' The parameters <paramref name="min"/> and <paramref name="max"/> must correspond with the limits of 
        ''' the measurement range choosen in the functions <see cref="meIOSingleConfig"/> 
        ''' resp. <see cref="meIOStreamConfig"/>. 
        ''' The parameters <paramref name="min"/>, <paramref name="max"/> and <paramref name="physical"/> must be given 
        ''' always in the same decimal power of the respective base unit (e. g. either "mV" or "V"). 
        ''' The physical unit is not relevant for calculation.
        ''' </remarks>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meUtilityExtractValues"/>
        ''' <seealso cref="meUtilityDigitalToPhysicalV"/>
        ''' <seealso cref="meIOSingleConfig"/>
        ''' <seealso cref="meIOStreamConfig"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityDigitalToPhysical(ByVal min As Double, ByVal max As Double, ByVal maxData As Integer, ByVal data As Integer, ByVal moduleType As Integer, ByVal refValue As Double, ByRef physical As Double) As Integer
        End Function
#End Region


#Region "meUtilityDigitalToPhysicalV"
        ''' <summary>
        ''' Conversion of a whole array of standardized digital values into the appropriate physical unit.
        ''' </summary>
        ''' <param name="min">
        ''' The lower limit of the range.
        ''' </param>
        ''' <param name="max">
        ''' The upper limit of the range.
        ''' </param>
        ''' <param name="maxData">
        ''' The maximum resolution of the range.
        ''' </param>
        ''' <param name="dataBuffer">
        ''' Pointer to an array of digital values to be converted.
        ''' </param>
        ''' <param name="dataCount">
        ''' Number of values in the array.
        ''' </param>
        ''' <param name="moduleType">
        ''' Support for ME-MultiSig module.
        ''' If for the current calculation no plug-on module must be taken into account,
        ''' pass the constant: <see cref="ME_MODULE_TYPE_MULTISIG_NONE"/>  
        ''' No plug-on module used (standard)
        ''' </param>
        ''' <param name="refValue">
        ''' For a RTD module or a thermo-couple module. Otherwise use: ME_VALUE_NOT_USED.
        ''' </param>
        ''' <param name="physicalBuffer">
        ''' Pointer to an array for the results in the appropriate physical unit [V], 
        ''' [A], [°C]. Has to be able to store <paramref name="dataCount"/> values.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_VALUE_OUT_OF_RANGE"/>: passed value is lower than "0" or bigger than <paramref name="maxData"/>.
        ''' <see cref="ME_ERRNO_INVALID_MIN_MAX"/>: passed <paramref name="maxData"/> is not valid.
        ''' <see cref="ME_ERRNO_INVALID_MODULE_TYPE"/>: passed module type is not supported.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meUtilityDigitalToPhysical"/>
        ''' <seealso cref="meIOSingleConfig"/>
        ''' <seealso cref="meIOStreamConfig"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityDigitalToPhysicalV(ByVal min As Double, ByVal max As Double, ByVal maxData As Integer, ByRef dataBuffer As Integer, ByVal dataCount As Integer, ByVal moduleType As Integer, ByVal refValue As Double, ByRef physicalBuffer As Double) As Integer
        End Function
#End Region


#Region "meUtilityPhysicalToDigital"
        ''' <summary>
        ''' Conversion of values to be output in standardized digital values which are appropriate for the converter.
        ''' </summary>
        ''' <param name="min">
        ''' The lower limit of the range, e. g. -10[V].
        ''' </param>
        ''' <param name="max">
        ''' The upper limit of the range, e. g. +9.999695[V].
        ''' </param>
        ''' <param name="maxData">
        ''' The maximum resolution of the range, e. g. 65536 at 16 bit resolution.
        ''' </param>
        ''' <param name="physical">
        ''' Voltage or current value to be converted, e. g. +0.75[V].
        ''' </param>
        ''' <param name="data">
        ''' Result as a digital value to be output.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_VALUE_OUT_OF_RANGE"/>: passed value is lower than <paramref name="min"/> or bigger than <paramref name="max"/>.
        ''' <see cref="ME_ERRNO_INVALID_MIN_MAX"/>: passed <paramref name="maxData"/> is not valid.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointer is NULL.
        ''' </returns>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meUtilityPhysicalToDigitalV"/>
        ''' <seealso cref="meUtilityDigitalToPhysical"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityPhysicalToDigital(ByVal min As Double, ByVal max As Double, ByVal maxData As Integer, ByVal physical As Double, ByRef data As Integer) As Integer
        End Function
#End Region


#Region "meUtilityPhysicalToDigitalV"
        ''' <summary>
        ''' Conversion of a whole array of values to be output in standardized digital values.
        ''' </summary>
        ''' <param name="min">
        ''' The lower limit of the range, e. g. -10[V].
        ''' </param>
        ''' <param name="max">
        ''' The upper limit of the range, e. g. +9.999695[V].
        ''' </param>
        ''' <param name="maxData">
        ''' The maximum resolution of the range, e. g. 65536 at 16 bit resolution.
        ''' </param>
        ''' <param name="physicalBuffer">
        ''' Pointer to an array with the voltage or current values to be converted.
        ''' </param>
        ''' <param name="physicalCount">
        ''' Number of values in the array.
        ''' </param>
        ''' <param name="dataBuffer">
        ''' Pointer to an array with the digital values to be output. Has to be able to store <paramref name="physicalCount"/> values.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_VALUE_OUT_OF_RANGE"/>: passed value is lower than <paramref name="min"/> or bigger than <paramref name="max"/>.
        ''' <see cref="ME_ERRNO_INVALID_MIN_MAX"/>: passed <paramref name="maxData"/> is not valid.
        ''' <see cref="ME_ERRNO_INVALID_POINTER"/>: passed pointers are NULL.
        ''' </returns>
        ''' <seealso cref="meQueryRangeInfo"/>
        ''' <seealso cref="meUtilityPhysicalToDigital"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityPhysicalToDigitalV(ByVal min As Double, ByVal max As Double, ByVal maxData As Integer, ByRef physicalBuffer As Double, ByVal physicalCount As Integer, ByRef dataBuffer As Integer) As Integer
        End Function
#End Region


#Region "meUtilityPWMStart"
        ''' <summary>
        ''' configures the counter device 8254 for the operation mode "pulse width modulation" and starts the operation.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed.
        ''' </param>
        ''' <param name="subdevice1">
        ''' Index of the sub-device counter 0 (used as prescaler).
        ''' </param>
        ''' <param name="subdevice2">
        ''' Index of the sub-device counter 1.
        ''' </param>
        ''' <param name="subdevice3">
        ''' Index of the sub-device counter 2.
        ''' </param>
        ''' <param name="reference">
        ''' Defines the clock source for counter 0 (CLK_0)
        ''' <see cref="ME_REF_CTR_INTERNAL_1MHZ"/>: Clock source is the internal 1 MHz crystal oszillator.
        ''' <see cref="ME_REF_CTR_INTERNAL_10MHZ"/>: Clock source is the internal 10 MHz crystal oszillator.
        ''' <see cref="ME_REF_CTR_EXTERNAL"/>: Clock source is an external oszillator.
        ''' </param>
        ''' <param name="prescaler">
        ''' Value for the prescaler (counter 0) in the range 2...65535.
        ''' </param>
        ''' <param name="dutyCycle">
        ''' TDuty cycle of the output signal from 1% –99% adjustable in steps of 1%.
        ''' </param>
        ''' <param name="flags">
        ''' Flag for extended options:
        ''' <see cref="ME_PWM_START_NO_FLAGS"/>: default settings
        ''' <see cref="ME_PWM_START_CONNECT_INTERNAL"/>: If supported by hardware (e. g. ME-1400 series), 
        ''' connect OUT_1 with GATE_2 internally. This reduces the number of external connections.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_FLAGS"/>: not supported flag detected.
        ''' <see cref="ME_ERRNO_INVALID_REF"/>: used signal source not available.
        ''' <see cref="ME_ERRNO_INVALID_DUTY_CYCLE"/>: value outside of supported range.
        ''' <see cref="ME_ERRNO_NOT_SUPPORTED"/>: used sub-device is not a counter or internal connection can not be done
        ''' </returns>
        ''' <remarks>
        ''' A further usage of the counters 0...2 is not possible in this operation mode. 
        ''' The signal is available at OUT_2 of the specified counter device. 
        ''' Depending on device type the base clock (max. 10 MHz) must be provided externally 
        ''' or (if supported by the hardware) an on-board crystal oszillator can be used. 
        ''' Counter 0 is used as a prescaler. The frequency of the output signal is max. 50 kHz
        ''' and can be calculated as follows:
        ''' <code>fOut_2 = baseClock / prescaler * 100;  //with prescaler = 2Exp(16-1)</code>
        ''' The duty cycle can be set between 1...99% in steps of 1%
        ''' </remarks>
        ''' <seealso cref="meUtilityPWMStop"/>
        ''' <seealso cref="meUtilityPWMRestart"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityPWMStart(ByVal device As Integer, ByVal subdevice1 As Integer, ByVal subdevice2 As Integer, ByVal subdevice3 As Integer, ByVal reference As Integer, ByVal prescaler As Integer, ByVal dutyCycle As Integer, ByVal flags As Integer) As Integer
        End Function
#End Region


#Region "meUtilityPWMRestart"
        ''' <summary>
        ''' Restarts a PWM operation stopped by the function meUtilityPWMStop()
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed
        ''' </param>
        ''' <param name="subdevice1">
        ''' Index of the sub-device counter 0 used as prescaler
        ''' </param>
        ''' <param name="reference">
        ''' Defines the clock source for counter 0 (CLK_0)
        ''' <see cref="ME_REF_CTR_INTERNAL_1MHZ"/>: Clock source is the internal 1 MHz crystal oszillator.
        ''' <see cref="ME_REF_CTR_INTERNAL_10MHZ"/>: Clock source is the internal 10 MHz crystal oszillator.
        ''' <see cref="ME_REF_CTR_EXTERNAL"/>: Clock source is an external oszillator.
        ''' </param>
        ''' <param name="prescaler">
        ''' Value for the prescaler (counter 0) in the range 2...65535.
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_REF"/>: used signal source not available.
        ''' <see cref="ME_ERRNO_NOT_SUPPORTED"/>: used sub-device is no counter.
        ''' </returns>
        ''' <seealso cref="meUtilityPWMStop"/>
        ''' <seealso cref="meUtilityPWMStart"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityPWMRestart(ByVal device As Integer, ByVal subdevice1 As Integer, ByVal reference As Integer, ByVal prescaler As Integer) As Integer
        End Function
#End Region


#Region "meUtilityPWMStop"
        ''' <summary>
        ''' Stops a PWM operation started by the function <see cref="meUtilityPWMStart"/> 
        ''' </summary>
        ''' <param name="device">
        ''' Index of the device to be accessed
        ''' </param>
        ''' <param name="subdevice1">
        ''' Index of the sub-device counter 0 used as prescaler
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_NOT_OPEN"/>: ME-iDS is not properly open.
        ''' <see cref="ME_ERRNO_INVALID_DEVICE"/>: no device mapped to requested index.
        ''' <see cref="ME_ERRNO_INVALID_SUBDEVICE"/>: on requested device no sub-device mapped to requested index.
        ''' <see cref="ME_ERRNO_NOT_SUPPORTED"/>: used sub-device is no counter.
        ''' </returns>
        ''' <seealso cref="meUtilityPWMStart"/>
        ''' <seealso cref="meUtilityPWMRestart"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl)> _
        Overloads Shared Function meUtilityPWMStop(ByVal device As Integer, ByVal subdevice1 As Integer) As Integer
        End Function
#End Region


#Region "mePropertyGetIntA"
        ''' <summary>
        ''' Read an integer value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the integer value
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertyGetIntA is the ANSI character version of mePropertyGetIntW
        ''' </remarks>
        ''' <seealso cref="mePropertyGetIntW"/>
        ''' <seealso cref="mePropertySetIntA"/>
        ''' <seealso cref="mePropertySetIntW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertyGetIntA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, ByRef propertyValue As Integer) As Integer
        End Function
#End Region


#Region "mePropertyGetIntW"
        ''' <summary>
        ''' Read an integer value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the integer value
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertyGetIntW is the wide character version of mePropertyGetIntA
        ''' </remarks>
        ''' <seealso cref="mePropertyGetIntA"/>
        ''' <seealso cref="mePropertySetIntA"/>
        ''' <seealso cref="mePropertySetIntW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertyGetIntW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, ByRef propertyValue As Integer) As Integer
        End Function
#End Region


#Region "mePropertyGetDoubleA"
        ''' <summary>
        ''' Read a double value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the double value
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertyGetDoubleA is the ANSI character version of mePropertyGetDoubleW
        ''' </remarks>
        ''' <seealso cref="mePropertyGetDoubleW"/>
        ''' <seealso cref="mePropertySetDoubleA"/>
        ''' <seealso cref="mePropertySetDoubleW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertyGetDoubleA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, ByRef propertyValue As Double) As Integer
        End Function
#End Region


#Region "mePropertyGetDoubleW"
        ''' <summary>
        ''' Read a double value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the double value
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertyGetDoubleW is the wide character version of mePropertyGetDoubleA
        ''' </remarks>
        ''' <seealso cref="mePropertyGetDoubleA"/>
        ''' <seealso cref="mePropertySetDoubleA"/>
        ''' <seealso cref="mePropertySetDoubleW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertyGetDoubleW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, ByRef propertyValue As Double) As Integer
        End Function
#End Region


#Region "mePropertyGetStringA"
        ''' <summary>
        ''' Read a string value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the ANSI-string value
        ''' </param>
        ''' <param name="count">
        ''' Buffer length in characters including the terminating null character
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_PROPERTY_BUFFER_TOO_SMALL"/>: the buffer is not large enough to hold the string
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertyGetStringA is the ANSI character version of mePropertyGetStringW
        ''' The required buffer length can be determined with the property attribute "Length" 
        ''' </remarks>
        ''' <seealso cref="mePropertyGetStringW"/>
        ''' <seealso cref="mePropertySetStringA"/>
        ''' <seealso cref="mePropertySetStringW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertyGetStringA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, propertyValue As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "mePropertyGetStringW"
        ''' <summary>
        ''' Read a string value from the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' Variable that receives the UTF-16 Unicode-string value
        ''' </param>
        ''' <param name="count">
        ''' Buffer length in characters, not bytes, including the terminating null character
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' <see cref="ME_ERRNO_PROPERTY_BUFFER_TOO_SMALL"/>: the buffer is not large enough to hold the string
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' The required buffer length can be determined with the property attribute "Length" 
        ''' mePropertyGetStringW is the wide character version of mePropertyGetStringA
        ''' </remarks>
        ''' <seealso cref="mePropertyGetStringA"/>
        ''' <seealso cref="mePropertySetStringA"/>
        ''' <seealso cref="mePropertySetStringW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertyGetStringW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, propertyValue As StringBuilder, ByVal count As Integer) As Integer
        End Function
#End Region


#Region "mePropertySetIntA"
        ''' <summary>
        ''' Set an integer value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The integer value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetIntA is the ANSI character version of mePropertySetIntW
        ''' </remarks>
        ''' <seealso cref="mePropertySetIntW"/>
        ''' <seealso cref="mePropertyGetIntA"/>
        ''' <seealso cref="mePropertyGetIntW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertySetIntA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, propertyValue As Integer)
        End Function
#End Region


#Region "mePropertySetIntW"
        ''' <summary>
        ''' Set an integer value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The integer value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetIntW is the wide character version of mePropertySetIntA
        ''' </remarks>
        ''' <seealso cref="mePropertySetIntA"/>
        ''' <seealso cref="mePropertyGetIntA"/>
        ''' <seealso cref="mePropertyGetIntW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertySetIntW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, propertyValue As Integer) As Integer
        End Function
#End Region


#Region "mePropertySetDoubleA"
        ''' <summary>
        ''' Set a double value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The double value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetIntA is the ANSI character version of mePropertySetDoubleW
        ''' </remarks>
        ''' <seealso cref="mePropertySetDoubleW"/>
        ''' <seealso cref="mePropertyGetDoubleA"/>
        ''' <seealso cref="mePropertyGetDoubleW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertySetDoubleA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, propertyValue As Double) As Integer
        End Function
#End Region


#Region "mePropertySetDoubleW"
        ''' <summary>
        ''' Set a double value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The double value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetDoubleW is the wide character version of mePropertySetDoubleA
        ''' </remarks>
        ''' <seealso cref="mePropertySetDoubleA"/>
        ''' <seealso cref="mePropertyGetDoubleA"/>
        ''' <seealso cref="mePropertyGetDoubleW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertySetDoubleW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, propertyValue As Double) As Integer
        End Function
#End Region


#Region "mePropertySetStringA"
        ''' <summary>
        ''' Set a string value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as ANSI-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The ANSI-string value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetStringA is the ANSI character version of mePropertyGetStringW
        ''' </remarks>
        ''' <seealso cref="mePropertySetStringW"/>
        ''' <seealso cref="mePropertyGetStringA"/>
        ''' <seealso cref="mePropertyGetStringW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Ansi)> _
        Overloads Shared Function mePropertySetStringA(<MarshalAs(UnmanagedType.LPStr)> propertyPath As String, <MarshalAs(UnmanagedType.LPStr)> propertyValue As String) As Integer
        End Function
#End Region


#Region "mePropertySetStringW"
        ''' <summary>
        ''' Set a string value of the given property
        ''' </summary>
        ''' <param name="propertyPath">
        ''' Property path as UTF-16 Unicode-string
        ''' </param>
        ''' <param name="propertyValue">
        ''' The UTF-16 Unicode-string value to be set
        ''' </param>
        ''' <returns>
        ''' <see cref="ME_ERRNO_SUCCESS"/>: the function returned successfully.
        ''' The return value is an error code if there is a failure.
        ''' </returns>
        ''' <remarks>
        ''' mePropertySetStringW is the wide character version of mePropertySetStringA
        ''' </remarks>
        ''' <seealso cref="mePropertySetStringA"/>
        ''' <seealso cref="mePropertyGetStringA"/>
        ''' <seealso cref="mePropertyGetStringW"/>
        <DllImport("meIDSmain.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)> _
        Overloads Shared Function mePropertySetStringW(<MarshalAs(UnmanagedType.LPWStr)> propertyPath As String, <MarshalAs(UnmanagedType.LPWStr)> propertyValue As String) As Integer
        End Function
#End Region


#End Region

    End Class

End Module