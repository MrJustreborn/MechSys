Imports System.IO

Public Class Drawing_to_file
    Private x_end As Integer = 0
    Private y_end As Integer = 0
    Private write As Boolean = False
    Private fileWriter As IO.StreamWriter
    Private _path As String = Application.StartupPath + "\temp.txt"
    Private Shared instance As Drawing_to_file
   

    Private Sub New()
        Me.createFile()
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

    Public Sub save_drawing_steps(ByVal x_start As Integer, ByVal y_start As Integer, ByVal x_end As Integer, ByVal y_end As Integer)
        If (Me.write) Then

            Me.write_drawed_line(Me.x_end, Me.y_end)
        Else
            Me.write = True
        End If

        Me.x_end = x_start
        Me.y_end = y_start
    End Sub

    Private Sub write_drawed_line(ByVal x As Integer, ByVal y As Integer)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "PA " + (x * 10).ToString + ", " + (y * 10).ToString
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
    End Sub

    Private Sub write_no_drawed_line(ByVal x As Integer, ByVal y As Integer)
        Dim txt As String
        Me.fileWriter = My.Computer.FileSystem.OpenTextFileWriter(Me._path, True)
        txt = "PU"
        Me.fileWriter.WriteLine(txt)
        Me.write_drawed_line(x, y)
        txt = "PD"
        Me.fileWriter.WriteLine(txt)
        Me.fileWriter.Close()
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
End Class
