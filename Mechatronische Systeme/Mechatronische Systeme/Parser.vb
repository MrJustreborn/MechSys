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

    ' Da es sich hier bei dieser Klasse um ein "Singleton - Pattern" handelt, besitzt diese auch keinen
    ' öffentlich zugänglichen Konstruktur; stattdessen wird durch Aufruf dieser Funktion eine Instanz 
    ' zurueckgegeben; hierbei wird zunaechst ueberprueft, ob diese bereits existiert; falls nicht wird 
    ' eine entsprechende angelegt
    Public Shared ReadOnly Property getInstance() As Parser
        Get
            If IsNothing(instance) Then
                instance = New Parser()
            End If
            Return instance
        End Get
    End Property

    ' In dieser Funktion wird anhand des uebergebenen Pfades (filepath) die entsprechende Datei geparst
    ' dies geschieht unter Mithilfe der Funktion "read"; eine ArrayList, welche die geparsten Daten enthaelt
    ' wird zum Abschluss zurueckgegeben
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

    'Bei Aufruf dieser Funktion wird zunaechst eine Zeile aus der Datei gelesen; im Anschluss erfolgt 
    ' eine Analyse der ersten 2 Buchstaben; dies dient dazu die entsprechende Funktion fuer das Parsen 
    ' aufzurufen; bei einen Fehler wird eine entsprechende Meldung ausgegeben
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

    ' Diese Funktion dient den Parsen einer Linie; hierzu wird zunaechst der uebergebene String formatiert 
    ' und die danach noch vorhandenen Werte in Integer - Werte umgewandelt; zum Abschluss wird die Funktion
    ' "addPA", die sich im "Calculator" befindet aufgerufen 
    Private Sub pa_parse(ByVal txt_line As String)
        txt_line = txt_line.Replace("PA ", "")
        txt_line = txt_line.Replace(" ", "")
        Dim tst As String() = Split(txt_line, ",")
        Dim intList As Integer() = Array.ConvertAll(tst, Function(str) Int32.Parse(str))
        
        Me.calc.addPA(intList(0), intList(1), Me.pen_status)
    End Sub

    ' Diese Funktion dient dem Parsen eines Kreises; hierzu wird zunaechst der uebergebene String formatiert 
    ' und die danach noch vorhandenen Werte in Integer - Werte umgewandelt; zum Abschluss wird die Funktion
    ' "addCS", die sich im "Calculator" befindet aufgerufen 
    Private Sub cs_parse(ByVal txt_line As String)
        txt_line = txt_line.Replace("CS ", "")
        txt_line = txt_line.Replace(" ", "")
        Dim tst As String() = Split(txt_line, ",")
        Dim intList As Integer() = Array.ConvertAll(tst, Function(str) Int32.Parse(str))

        Me.calc.addCS(intList(0), intList(1), intList(2),Me.pen_status)

    End Sub

    'Diese Funktion dient dazu die Boolean Variable "pen_status" auf "True" zusetzen- dies dient dazu, dem Drucker 
    ' beim Druckvorgang mitzuteilen, den Stift abzusetzen
    Private Sub pu_parse()
        Me.pen_status = True
    End Sub

    'Diese Funktion dient dazu die Boolean Variable "pen_status" auf "False" zusetzen- dies dient dazu, dem Drucker 
    ' beim Druckvorgang mitzuteilen, den Stift abzuheben
    Private Sub pd_parse()
        Me.pen_status = False
    End Sub

End Class
