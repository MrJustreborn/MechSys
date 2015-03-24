Public Class Parser
    'nur zu Testzwecken --- wird neu überarbeitet 
    Dim fileString As String
    Dim index = 0, txtLength As Integer
    Dim cmd As New List(Of Integer())


    Public Sub New(ByVal filepath As String)
        fileString = My.Computer.FileSystem.ReadAllText(filepath)
        txtLength = fileString.Length
    End Sub

    Public Sub parseFile()
        While (index < txtLength - 2)
            read()
            index += 1
        End While
    End Sub

    Private Sub read()
        Dim result(3) As Integer
        Select Case (fileString.Substring(index, 2))
            Case "PA"
                result = pa_parse()
            Case "CS"
                result = cs_parse()
            Case "PU"
                result = pu_parse()
            Case Else
                Console.WriteLine("Falsch")
        End Select
        cmd.Add(result)

        For Each element As Integer In result
            Console.Write(element)
        Next
    End Sub

    Private Function pa_parse() As Integer()
        Dim result(3) As Integer

        If (index < txtLength - 4) Then
            result(0) = 1
            result(1) = CInt(fileString.Substring(index + 3, 1))
            result(2) = CInt(fileString.Substring(index + 5, 1))
            index += 6
            Console.Write("PA")
        Else
            result(0) = 1
            result(1) = 0
            result(2) = 0
            index += 2
            Console.Write("PA")
        End If

        Return result
    End Function

    Private Function cs_parse() As Integer()
        Dim result(3) As Integer

        If (index < txtLength - 7) Then
            result(0) = 1
            result(1) = CInt(fileString.Substring(index + 3, 1))
            result(2) = CInt(fileString.Substring(index + 5, 1))
            index += 8
            Console.Write("CS")
        End If
        Return result

    End Function

    Private Function pu_parse() As Integer()
        Dim result(3) As Integer


        result(0) = 0
        result(1) = 0
        result(2) = 0

        index += 2
        Console.Write("PU")
        Return result

    End Function

End Class
