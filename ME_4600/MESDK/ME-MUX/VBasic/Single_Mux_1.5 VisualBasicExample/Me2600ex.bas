Attribute VB_Name = "Module1"
'-----------------------------------------------------------------------------
'       File: ME2600EX.BAS
'-----------------------------------------------------------------------------
'
'       Meilhaus Electronic GmbH
'
'       This module contains sample code for callback routines.
'
'
'
'       Version 1.000:          14.07.98        First version
'
'-----------------------------------------------------------------------------
'       Author: Andreas Bernau                                  (c) 1998   AB
'-----------------------------------------------------------------------------
'
'
' The functionality of a callback routine depends on the application,
' so it is up to you to define how your callbacks should work.
'
' The functions below are intended to demonstrate the parameters
' of callback routines used by the ME2600 API DLL.
'
'
' NOTE: The ...Ex routines and the according callback routines have to be in
'       the same source code module which MUST NOT be a Visual Basic form
'
'       It is a good idea to put all the routines dealing with callbacks
'       into a single module and call it me2600ex.bas
'
'       You can use a copy of this module for your own project.
'
'
' NOTE: Most probably, this module will not work immediately, because it is
'       using objects which may not exist in your project.
'
'
' NOTE: It is not possible to pass a pointer from the DLL to a callback
'       located in a Visual Basic module. So we have to work with global
'       variables. See AISingleHandler and AIMultipleHandler below.
'

Public Function AISingleEx(ByVal lBoardnumber As Long, ByVal lChannel As Long, ByVal lRange As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByRef piValue As Integer) As Long
    AISingleEx = me2600AISingleEx(lBoardnumber, lChannel, lRange, lLoops, lDelay, piValue, AddressOf AISingleHandler)
End Function

'Public Function AIQuickEx(ByVal lBoardnumber As Long, ByRef piBuffer() As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long) As Long
'    AIQuickEx = me2600AIQuickEx(lBoardnumber, piBuffer(0), lCount, lMode, lLoops, lDelay, AddressOf AIMultipleHandler)
'End Function

'Public Function AIMultipleEx(ByVal lBoardnumber As Long, ByRef piBuffer() As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long) As Long
'    AIMultipleEx = me2600AIMultipleEx(lBoardnumber, piBuffer(0), lCount, lMode, lLoops, lDelay, AddressOf AIMultipleHandler)
'End Function

'Public Function AIScanEx(ByVal lBoardnumber As Long, ByRef piBuffer() As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long) As Long
 '   AIScanEx = me2600AIScanEx(lBoardnumber, piBuffer(0), lSize, lCount, lMode, lLoops, lDelay, AddressOf AIMultipleHandler)
'End Function


' Passing a pointer is not working. So, we just pass a dummy to properly call
' the function. However, internally we use the global array "giADCBuffer"
' to access the data
'------------------------------------------------------------------------------
'Public Sub AIMultipleHandler(ByRef piBuffer() As Integer, ByVal lSize As Long)
   ' Dim i As Integer
    
   ' i = giADCBuffer(0)
'End Sub

' Passing a pointer is not working. So, we just pass a dummy to properly call
' the function. However, internally we use the global value "giSingleValue"
' to access the data
'------------------------------------------------------------------------------
Public Sub AISingleHandler(ByRef piValue As Integer)
    Dim dValue As Double
    
    dValue = giSingleValue * 0.00048828125 * gdHalfRange - gdADCOffset
    vbMain.SingleValueLabel.Caption = " ADC " + Str(glADCChannel) + ": " + Str(giSingleValue) + "  " + Str(dValue) + " [V]"

End Sub
Public Sub ExternalInterruptHandler()
    Beep
End Sub

Public Function EnableExternalInterrupt(ByVal lBoardnumber As Long) As Long
    EnableExternalInterrupt = me2600EnableExternalInt(glBoardNumber, AddressOf ExternalInterruptHandler)
End Function
Public Sub CounterInterruptHandler()
    Beep
End Sub

Public Function CounterInterrupt(ByVal lBoardnumber As Long, ByVal lCounter As Long, ByVal lFlag As Long) As Long
    CounterInterrupt = me2600CNTInterrupt(glBoardNumber, lCounter, lFlag, AddressOf CounterInterruptHandler)
End Function
Public Sub AOContinuousHandler()
    MsgBox "Finished!", vbOKOnly, "AOContinuous"
End Sub

Public Function AOContinuousEx(ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lSize As Long, ByRef piBuffer As Integer, ByVal lLoops As Long, ByVal lDelay As Long) As Long
    AOContinuousEx = me2600AOContinuousEx(lBoardnumber, lMode, lSize, piBuffer, lLoops, lDelay, AddressOf AOContinuousHandler)
End Function


