Imports System.IO

Public Class Save_read_settings
    Private Declare Ansi Function GetPrivateProfileString Lib "kernel32.dll" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As System.Text.StringBuilder, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Private Declare Ansi Function WriteSettings Lib "kernel32.dll" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Private Property Path As String
    Private Shared instance As Save_read_settings
    Private section As String = "[settings]"
    Private itm_settings As String() = {"x_motor", "y_motor", "tuning"}

    Private Sub New()
        _Path = Application.StartupPath
        _Path += "\settings.ini"

        createFile()
    End Sub

    Private Sub createFile()
        Dim fileStream As New IO.FileStream(_Path, IO.FileMode.OpenOrCreate, IO.FileAccess.ReadWrite, IO.FileShare.None)

        Dim myFileWriter As New IO.StreamWriter(fileStream)
        Dim item As String

        myFileWriter.WriteLine(section)

        For Each item In itm_settings
            myFileWriter.WriteLine(item & "= 0")
        Next item

        myFileWriter.Close()
        fileStream.Close()

    End Sub

    Public Shared ReadOnly Property getInstance() As Save_read_settings
        Get
            If IsNothing(instance) Then
                instance = New Save_read_settings()
            End If
            Return instance
        End Get
    End Property


    Public Function ReadValue(ByVal section As String, ByVal key As String) As String
        Dim sb As New System.Text.StringBuilder(255)
        Try
            If Not File.Exists(_Path) Then
                createFile()
            Else
                Dim i = GetPrivateProfileString(section, key, "", sb, 255, Path)
                Return sb.ToString
            End If
            Return ""
        Catch ex As Exception
            MsgBox("Fehler beim Lesen der Datei")
        End Try

        
    End Function

    Public Sub WriteValue(ByVal section As String, ByVal key As String, ByVal values As String)
        Try
            If File.Exists(_Path) Then
                WriteSettings(section, key, values, Path)
            Else
                createFile()
                WriteSettings(section, key, values, Path)
            End If


        Catch ex As Exception
            MsgBox("Fehler beim Schreiben in die Datei")
        End Try

    End Sub


End Class
