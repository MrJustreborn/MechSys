Imports System
Imports System.IO


Public Class Parser

    Private fileReader As StreamReader
    Private calc As Calculator
    Private pen_status As Boolean = False
    Private Shared instance As Parser
   



    Private Sub New()
        calc = Calculator.getInstance()
    End Sub

    Public Shared ReadOnly Property getInstance() As Parser
        Get
            If IsNothing(instance) Then
                instance = New Parser()
            End If
            Return instance
        End Get
    End Property


    Public Function parseFile(ByVal filepath As String) As List(Of Integer())
        Try
            fileReader = New StreamReader(filepath)

            Do While fileReader.Peek() >= 0
                read()
            Loop
            fileReader.Close()
        Catch ex As Exception

        End Try

        Return Me.calc.getDatas()
    End Function

    Private Sub read()
        Try
            Dim txt_line As String = fileReader.ReadLine()
            Select Case (txt_line.Substring(0, 2))
                Case "PA"
                    pa_parse(txt_line)
                Case "CS"
                    cs_parse(txt_line)
                Case "PU"
                    pu_parse()
                Case "PD"
                    pd_parse()
                Case Else
                    MsgBox("Ihre Datei entspricht nicht den gewünschten Format")

            End Select
        Catch ex As Exception

        End Try
       

    End Sub

    Private Sub pa_parse(ByVal txt_line As String)
        txt_line = txt_line.Replace("PA ", "")
        txt_line = txt_line.Replace(" ", "")
        Dim tst As String() = Split(txt_line, ",")
        Dim intList As Integer() = Array.ConvertAll(tst, Function(str) Int32.Parse(str))
        
        Me.calc.addPA(intList(0), intList(1), Me.pen_status)
    End Sub

    Private Sub cs_parse(ByVal txt_line As String)
        txt_line.Replace("CS ", "")
        Dim tst As String() = Split(txt_line, ",")
        Dim intList As Integer() = Array.ConvertAll(tst, Function(str) Int32.Parse(str))
        Me.calc.addCS(intList(0), intList(1), intList(2),Me.pen_status)

    End Sub

    Private Sub pu_parse()
        Me.pen_status = True
    End Sub

    Private Sub pd_parse()
        Me.pen_status = False
    End Sub

End Class
