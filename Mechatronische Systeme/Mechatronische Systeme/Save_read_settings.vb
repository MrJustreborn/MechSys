Imports System.IO

Public Class Save_read_settings
    Private Declare Ansi Function GetPrivateProfileString Lib "kernel32.dll" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As System.Text.StringBuilder, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Private Declare Ansi Function WriteSettings Lib "kernel32.dll" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Private Property Path As String
    Private Shared instance As Save_read_settings
    Private section As String = "[settings]"
    Private itm_settings As String() = {"x_motor", "y_motor", "tuning"}

    ' Da es sich bei dieser Klasse um ein Singleton - Pattern handelt, ist dier Konstruktur nicht global zugreifbar
    ' der Wert der Variablen "Path" - der Pfad zur Datei wird bei Aufruf des Konstrukturs gesetzt 
    Private Sub New()
        _Path = Application.StartupPath
        _Path += "\settings.ini"
    End Sub

    ' Diese Funktion erzeugt die Datei, in der die Einstellungen gespeichert sind; alle in der Datei vorhandenen Werte
    ' sind dann zunaechst "0" gesetzt 
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

    ' Da es sich bei dieser Klasse um ein Singleton Pattern handelt, ist eine entsprechende Funktion
    ' implementiert worden; diese Funktion ueberprueft zunaechst, ob bereits eine Instanz des Typs "Save_read_settings" 
    ' existiert; falls nicht wird eine entsprechende erzeugt und der Variablen "instance" zugewiesen
    ' zum Abschluss wird diese zurueckgegeben
    Public Shared ReadOnly Property getInstance() As Save_read_settings
        Get
            If IsNothing(instance) Then
                instance = New Save_read_settings()
            End If
            Return instance
        End Get
    End Property

    'Liest die Werte anhand der uebergebenen Parameter aus der Datei und gibt diese als String zurueck
    Private Function ReadValue(ByVal section As String, ByVal key As String) As String
        Dim sb As New System.Text.StringBuilder(255)
        Try
            If Not File.Exists(_Path) Then
                createFile()
            End If

            Dim i = GetPrivateProfileString(section, key, "", sb, 255, Path)
            Return sb.ToString


        Catch ex As Exception
            MsgBox("Fehler beim Lesen der Datei")
        End Try

        Return ""
    End Function

    'Funktion dient der Abspeicherung der uebergebenen Werte in die Datei; bei Auftreten eines Fehlers
    ' wird eine entsprechende Meldung ausgegeben
    Private Sub WriteValue(ByVal section As String, ByVal key As String, ByVal values As String)
        Try
            If Not File.Exists(_Path) Then
                createFile()
            End If

            WriteSettings(section, key, values, Path)

        Catch ex As Exception
            MsgBox("Fehler beim Schreiben in die Datei")
        End Try

    End Sub

    ' Gibt den Wert "x_motor" aus der Datei zurueck, dazu wird die Funktion "ReadValue" aufgerufen
    Public Function getX_motor() As String
        Return ReadValue("settings", "x_motor")
    End Function

    ' Gibt den Wert "y_motor" aus der Datei zurueck, dazu wird die Funktion "ReadValue" aufgerufen
    Public Function getY_motor() As String
        Return ReadValue("settings", "y_motor")
    End Function

    ' Gibt den Wert "tuning" aus der Datei zurueck, dazu wird die Funktion "ReadValue" aufgerufen
    Public Function get_tuning() As String
        Return ReadValue("settings", "tuning")
    End Function

    'Schreibt den uebergebenen String "x_motor" in die Datei; dazu wird die Funktion "WriteValue" aufgerufen 
    Public Sub writeX_motor(ByVal x_motor As String)
        WriteValue("settings", "x_motor", x_motor)
    End Sub

    'Schreibt den uebergebenen String "y_motor" in die Datei; dazu wird die Funktion "WriteValue" aufgerufen 
    Public Sub writeY_motor(ByVal y_motor As String)
        WriteValue("settings", "y_motor", y_motor)
    End Sub

    'Schreibt den uebergebenen String "tuning" in die Datei; dazu wird die Funktion "WriteValue" aufgerufen 
    Public Sub write_tuning(ByVal tuning As String)
        WriteValue("settings", "tuning", tuning)
    End Sub
End Class
