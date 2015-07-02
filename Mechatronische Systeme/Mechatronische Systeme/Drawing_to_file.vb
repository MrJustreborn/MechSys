Imports System.IO

Public Class Drawing_to_file
    Private p_end As Point
    Private line_insert As Integer = 0
    Private last_drawing_steps As Integer = 0
    Private write As Boolean = False
    Private fileWriter As IO.StreamWriter
    Private _path As String = Application.StartupPath + "\temp.txt"
    Private Shared instance As Drawing_to_file


    'In diesem privaten Konstruktur wird durch Aufruf der Funktion "createFile" eine
    'Datei angelegt
    Private Sub New()
        Me.createFile()
    End Sub

    ' Da es sich hier bei dieser Klasse um ein "Singleton - Pattern" handelt, besitzt diese auch keinen
    ' öffentlich zugänglichen Konstruktur; stattdessen wird durch Aufruf dieser Funktion eine Instanz 
    ' zurueckgegeben; hierbei wird zunaechst ueberprueft, ob diese bereits existiert; falls nicht wird 
    ' eine entsprechende angelegt
    Public Shared ReadOnly Property getInstance() As Drawing_to_file
        Get
            If IsNothing(instance) Then
                instance = New Drawing_to_file()
            End If
            Return instance
        End Get
    End Property

    'Bei Aufruf dieser Funktion wird eine leere,temporaere Datei angelegt
    Private Sub createFile()
        Dim fileStream As New IO.FileStream(Me._path, IO.FileMode.OpenOrCreate, IO.FileAccess.Write, IO.FileShare.None)

        fileStream.Close()

    End Sub

    'Diese Funktion sorgt dafuer, die erforderlichen Funktionen aufzurufen, die noetig sind, um die Daten fuer
    'eine Linie in der temporaeren Datei abzuspeichern; die dafuer einzutragenden Zeilen werden in der Variablen
    '"line_insert" abgelegt
    Public Sub save_drawing_steps(ByVal p_start As Point, ByVal p_end As Point)
        Me.last_drawing_steps = Me.line_insert
        Me.line_insert = 0
        Me.write_no_drawed_line(p_start)
        Me.write_drawed_line(p_end)
        Me.line_insert += 1
        Me.p_end = p_end
        
    End Sub

    'Diese Funktion sorgt dafuer, die erforderlichen Funktionen aufzurufen, die noetig sind, um die Daten fuer
    'einen Kreis in der temporaeren Datei abzuspeichern; die dafuer einzutragenden Zeilen werden in der Variablen
    '"line_insert" abgelegt
    Public Sub save_drawing_steps(ByVal middle As Point, ByVal point As Point, ByVal swapAngle As Integer)
        Me.last_drawing_steps = Me.line_insert
        Me.line_insert = 0
        Me.write_no_drawed_line(point)
        Me.write_drawed_circle(middle, swapAngle)
        Me.line_insert += 1
        Me.p_end = point
        
    End Sub

    'Bei Aufruf dieser Funktion wird in der temporaeren Datei, die erforderlichen Zeilen hinzugefuegt,
    ' die noetig sind, um einen Kreis, die der Drucker mit abgesetzten Stift, entlangfahren muss
    Private Sub write_drawed_circle(ByVal middle As Point, ByVal swapAngle As Integer)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "CS " + (middle.X * 10).ToString + ", " + (middle.Y * 10).ToString + ", " + (swapAngle * 10).ToString
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
    End Sub

    'Bei Aufruf dieser Funktion wird in der temporaeren Datei, die erforderlichen Zeilen hinzugefuegt,
    ' die noetig sind, um eine Linie, die der Drucker mit abgesetzten Stift, entlangfahren muss
    Private Sub write_drawed_line(ByVal point As Point)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "PA " + (point.X * 10).ToString + ", " + (point.Y * 10).ToString
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
    End Sub

    'Bei Aufruf dieser Funktion wird in der temporaeren Datei, die erforderlichen Zeilen hinzugefuegt,
    ' die noetig sind, um eine Linie, die der Drucker mit angehobenen Stift, entlangfahren muss
    Private Sub write_no_drawed_line(ByVal point As Point)
        Dim txt As String

        If Me.p_end.X <> point.X Or Me.p_end.Y <> point.Y Then
            Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
            txt = "PU"
            Me.fileWriter.WriteLine(txt)
            txt = "PA " + (point.X * 10).ToString + ", " + (point.Y * 10).ToString
            Me.fileWriter.WriteLine(txt)
            txt = "PD"
            Me.fileWriter.WriteLine(txt)
            Me.fileWriter.Close()
            Me.p_end = point
            Me.line_insert += 3

        End If

    End Sub

    'Bei Aufruf dieser Funktion wird die Datei, falls vorhanden, im angegebenen Pfad (_path) geloescht
    Public Sub delete_file()
        If File.Exists(Me._path) Then
            My.Computer.FileSystem.DeleteFile(Me._path)
        End If
    End Sub

    'Bei Aufruf dieser Funktion wird eine Kopie der temporaeren Datei "temp" erstellt und die Kopie im
    'uebergebenen Pfad abgelegt; die temporaere Datei wird zum Abschluß geloescht
    Public Sub save_file_to_path(ByVal filename As String)
        If File.Exists(Me._path) Then
            File.Copy(Me._path, filename, True)
            Me.delete_file()
        End If
    End Sub

    'Bei Betaetigung des Buttons "back" in der Form "DrawingView" wird diese Funktion aufgerufen;
    'hierbei wird die temporaer abgespeicherte Datei "temp" eingelesen, der Inhalt in dieser Datei
    'anschließend geloescht und die eingelesenen Daten bis auf die letzte Zeile/n wieder eingetragen
    'bei einem Fehler wird eine entsprechende Meldung ausgegeben
    Public Sub back()
        Dim insert_lines() As String  'speichert die eingefügten Zeilen aus der temp - Datei
        Dim list As New List(Of String)
        Dim writer As StreamWriter

        Me.last_drawing_steps = Me.line_insert

        Try
            insert_lines = IO.File.ReadAllLines(Me._path)
            list = insert_lines.ToList()
            If (Me.last_drawing_steps > 0 And Me.last_drawing_steps <= list.Count) Then
                Me.delete_file()
                Me.createFile()
                writer = New StreamWriter(Me._path)
                For I As Integer = 0 To list.Count - (Me.last_drawing_steps + 1)
                    writer.WriteLine(list(I))
                Next
                Me.last_drawing_steps = 0
                writer.Close()
            End If
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try



    End Sub

    'Diese Funktion gibt den Pfad zurueck, in der die Druckdatei, welche gezeichnet worden ist
    'abgelegt wird
    Public Function getPath() As String
        Return Me._path
    End Function

End Class
