'==============================================================================
'Copyright(c), Meilhaus Electronic GmbH
'              http://www.meilhaus.de
'              support@meilhaus.de
'
'Source File : meIDSToolsDLL.vb
'              contains a collection of routines to carry out common tasks using the ME-iDS system
'              The library is located in the folder:
'              %ProgramFiles%\Meilhaus Electronic\ME-iDS\[me-ids-version]\System\ME-iDS (Driver)
'              replace [me-ids-version] with the installed version
'              of the ME-iDS, e.g.: 02.00.03.000
'              See ME-iDS help file for more information
'Note        : import library for 32bit: meIDSTools.dll
'              import library for 64bit: meIDSTools64.dll
'              
'==============================================================================
Option Explicit On

Imports System.Runtime.InteropServices

Module meIDSTools_VB

    ''' <summary>
    ''' Defines all constants and methods to use the meIDSTools library
    ''' </summary>
    Public NotInheritable Class meIDSTools

#Region "Constants"

        '==============================================================================
        '  Error codes
        '==============================================================================

        Public Const MEIDS_TOOLS_ERRNO_SUCCESS As Integer = 0
        Public Const MEIDS_TOOLS_ERRNO_WAVEGEN_SIGNAL_OUT_OF_RANGE As Integer = 10001
        Public Const MEIDS_TOOLS_ERRNO_WAVEGEN_FREQUENCY_OUT_OF_RANGE As Integer = 10002

        '==============================================================================
        ' Signal forms for the function meIDSToolsWaveGen - Parameter iShape
        '==============================================================================

        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_RECTANGLE As Integer = &H10010001
        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_TRIANGLE As Integer = &H10010002
        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_SINUS As Integer = &H10010003
        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_COSINUS As Integer = &H10010004
        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_POS_RAMP As Integer = &H10010005
        Public Const MEIDS_TOOLS_WAVEGEN_SHAPE_NEG_RAMP As Integer = &H10010006

#End Region

#Region "meIDSToolsFunctions"
        ''' <summary>
        ''' Description of the library functions
        ''' </summary>

#Region "meIDSToolsWaveGen"

        ''' <summary>
        ''' Creates the waveform using a number of data points less than the size of the internal FIFO on the sub-device.
        ''' </summary>
        ''' <param name="device">
        ''' Index of the AO streaming device which will be used to output the waveform.
        ''' </param>
        ''' <param name="subdevice">
        ''' Index of the sub-device to be accessed.
        ''' </param>
        ''' <param name="unit">
        ''' Type of signal which will be output.
        ''' Use one of the constants ME_UNIT_VOLT, ME_UNIT_AMPERE, ME_UNIT_HZ from meIDS.vb
        ''' </param>
        ''' <param name="shape">
        ''' Shape of the waveform to be output
        ''' </param>
        ''' <param name="amplitude">
        ''' The amplitude in the units of the parameter 'unit' of the signal produced
        ''' </param>
        ''' <param name="offset">
        ''' The offset in the units of the parameter 'unit' of the signal produced
        ''' </param>
        ''' <param name="frequency">
        ''' Contains the frequency in Hz of the signal produced.
        ''' </param>
        ''' <returns>
        ''' Returns one of the standard ME-iDS error codes or one of the error codes defined in this module
        ''' </returns>
        ''' <remarks>
        ''' The routine uses as much of the internal FIFO as possible in order to produce a signal as smooth as possible.
        ''' </remarks>
        <DllImport("meIDSTools.dll", CallingConvention:=CallingConvention.Cdecl)>
        Overloads Shared Function meIDSToolsWaveGen(device As Integer, subdevice As Integer, unit As Integer, shape As Integer, amplitude As Double, offset As Double, ByRef frequency As Double) As Integer
        End Function

#End Region

#End Region

    End Class

End Module

