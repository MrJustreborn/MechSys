Imports System.IO

Public Class Drawing_to_file
    Private p_end As Point
    Private line_insert As Integer = 0
    Private insert_steps_list As List(Of Integer)
    Private write As Boolean = False
    Private fileWriter As IO.StreamWriter
    Private _path As String = Application.StartupPath + "\temp.txt"
    Private Shared instance As Drawing_to_file



    Private Sub New()
        Me.createFile()
        Me.insert_steps_list = New List(Of Integer)
    End Sub

    Public Shared ReadOnly Property getInstance() As Drawing_to_file
        Get
            If IsNothing(instance) Then
                instance = New Drawing_to_file()
            End If
            Return instance
        End Get
    End Property

    Private Sub createFile()
        Dim fileStream As New IO.FileStream(Me._path, IO.FileMode.OpenOrCreate, IO.FileAccess.Write, IO.FileShare.None)

        fileStream.Close()

    End Sub

    Public Sub save_drawing_steps(ByVal p_start As Point, ByVal p_end As Point)

        Me.write_no_drawed_line(p_start)
        Me.write_drawed_line(p_end)
        Me.line_insert += 1
        Me.insert_steps_list.Add(Me.line_insert)
        Me.line_insert = 0
        Me.p_end = p_end
        
    End Sub

    Public Sub save_drawing_steps(ByVal middle As Point, ByVal point As Point, ByVal swapAngle As Integer)

        Me.write_no_drawed_line(point)
        Me.write_drawed_circle(middle, swapAngle)
        Me.line_insert += 1
        Me.insert_steps_list.Add(Me.line_insert)
        Me.line_insert = 0
        Me.p_end = point
        
    End Sub

    Private Sub write_drawed_circle(ByVal middle As Point, ByVal swapAngle As Integer)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "CS " + (middle.X * 10).ToString + ", " + (middle.Y * 10).ToString + ", " + swapAngle.ToString
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
    End Sub

    Private Sub write_drawed_line(ByVal point As Point)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "PA " + (point.X * 10).ToString + ", " + (point.Y * 10).ToString
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
    End Sub

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

    Public Sub delete_file()
        If File.Exists(Me._path) Then
            My.Computer.FileSystem.DeleteFile(Me._path)
        End If
    End Sub

    Public Sub save_file_to_path(ByVal filename As String)
        If File.Exists(Me._path) Then
            File.Copy(Me._path, filename, True)
            Me.delete_file()
        End If
    End Sub

    Public Sub back()
        Dim tmp As Integer 'letzter Wert im insert_steps_array
        Dim insert_lines() As String  'speichert die eingefügten Zeilen aus der temp - Datei
        Dim list As New List(Of String)
        Dim writer As StreamWriter



        If Me.insert_steps_list.Count > 0 Then
            Try
                tmp = Me.insert_steps_list.Last
                insert_lines = IO.File.ReadAllLines(Me._path)
                list = insert_lines.ToList()

                For index As Integer = 1 To tmp
                    list.RemoveAt(list.Count - 1)
                Next

                Me.delete_file()
                Me.createFile()
                writer = New StreamWriter(Me._path)

                For Each item In list
                    writer.WriteLine(item)
                Next
                writer.Flush()
                writer.Close()
                Me.insert_steps_list.RemoveAt(insert_steps_list.Count - 1)
            Catch ex As Exception
                MsgBox(ex.ToString)
            End Try
        End If


    End Sub

    Public Function getPath() As String
        Return Me._path
    End Function

End Class
