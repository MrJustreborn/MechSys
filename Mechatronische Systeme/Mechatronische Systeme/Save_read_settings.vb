Imports System.IO
Public Class Save_read_settings
    Private Declare Ansi Function GetPrivateProfileString Lib "kernel32.dll" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As System.Text.StringBuilder, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Private Declare Ansi Function WriteSettings Lib "kernel32.dll" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Private Property Path As String

    Public Sub New()
        _Path = Application.StartupPath
        _Path += "\settings.ini"
    End Sub

    Public Function ReadValue(ByVal section As String, ByVal key As String) As String
        Dim sb As New System.Text.StringBuilder(255)
        If Not File.Exists(_Path) Then
            MsgBox("Keine Ini-Datei vorhanden")
        Else
            Dim i = GetPrivateProfileString(section, key, "", sb, 255, Path)
            Return sb.ToString
        End If
        Return ""
    End Function

    Public Sub WriteValue(ByVal section As String, ByVal key As String, ByVal values As String)
        WriteSettings(section, key, values, Path)
    End Sub
End Class
