Public Class Controller
    Private main_form As MainView
    Private drawing_form As Zeichnung
    Private settings As Save_read_settings
    Private Shared instance As Controller
    Private parser As Parser
    Private drawing_file As Drawing_to_file
    Private list As List(Of Integer())

    Private Sub New()
        Me.settings = Save_read_settings.getInstance
        Me.parser = parser.getInstance()
        Me.drawing_file = Drawing_to_file.getInstance

    End Sub

    Public Shared ReadOnly Property getInstance() As Controller
        Get
            If IsNothing(Instance) Then
                instance = New Controller()
            End If
            Return Instance
        End Get
    End Property

    Private Sub parse(ByVal filepath As String)
        Me.list = Me.parser.parseFile(filepath)
    End Sub


    Public Sub load_settings(ByVal form As Settings)
        Dim x_motor, y_motor, tuning As String
        x_motor = Me.settings.getX_motor()
        y_motor = Me.settings.getY_motor()
        tuning = Me.settings.get_tuning()
        form.setTxt_1(x_motor)
        form.setTxt_2(y_motor)
        form.setScrollBar(tuning)
    End Sub

    Public Sub save_settings(ByVal x_motor As String, ByVal y_motor As String, ByVal tuning As Integer)
        Me.settings.writeX_motor(x_motor)
        Me.settings.writeY_motor(y_motor)
        Me.settings.write_tuning(tuning)
    End Sub

    Public Sub set_MainView(ByRef form As Form)
        Me.main_form = form
    End Sub

    Public Sub set_DrawingView(ByRef form As Form)
        Me.drawing_form = form
    End Sub

    Private Sub line_preview(ByVal x_old As Integer, ByVal y_old As Integer, ByVal x_new As Integer, ByVal y_new As Integer)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_preview(x_old, y_old, x_new, y_new)
        End If
    End Sub

    Private Sub line_drawing(ByVal x_old As Integer, ByVal y_old As Integer, ByVal x_new As Integer, ByVal y_new As Integer)
        If Not IsNothing(Me.drawing_form) Then
            Me.drawing_form.draw_line(x_old, y_old, x_new, y_new)
        End If
    End Sub

    Public Sub line_live_print(ByVal x_old As Integer, ByVal y_old As Integer, ByVal x_new As Integer, ByVal y_new As Integer)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_live_print(x_old, y_old, x_new, y_new)
        End If
    End Sub

    Public Sub progress(ByVal x As Integer)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.Progress(x)
        End If
    End Sub

    Public Sub print()
        If Not Me.list Is Nothing Then

        End If
    End Sub

    Public Sub showPreview(ByVal filepath As String)
        Dim factor = 10
        Dim x_last As Integer
        Dim y_last As Integer
        Dim x_start As Integer = 0
        Dim y_start As Integer = 0

        Me.parse(filepath)

        For Each item In Me.list
            x_last = x_start + item(1)
            y_last = y_start + item(2)

            If (item(0) = 0) Then
                Me.line_preview(x_start / factor, y_start / factor, x_last / factor, y_last / factor)
            End If
            x_start = x_last
            y_start = y_last
        Next
    End Sub

    Public Sub delete_drawing_file()
        Me.drawing_file.delete_file()
    End Sub

    Public Sub save_drawing_to_file(ByVal filename As String)
        Me.drawing_file.save_file_to_path(filename)
    End Sub

    Public Sub save_drawing_steps(ByVal x_start As Integer, ByVal y_start As Integer, ByVal x_end As Integer, ByVal y_end As Integer)
        Me.drawing_file.save_drawing_steps(x_start, y_start, x_end, y_end)
    End Sub

    Private Sub showDrawing(ByVal filepath As String)
        Dim factor = 10
        Dim x_last As Integer
        Dim y_last As Integer
        Dim x_start As Integer = 0
        Dim y_start As Integer = 0

        Me.parse(filepath)

        For Each item In Me.list
            x_last = x_start + item(1)
            y_last = y_start + item(2)

            If (item(0) = 0) Then
                Me.line_drawing(x_start / factor, y_start / factor, x_last / factor, y_last / factor)
            End If
            x_start = x_last
            y_start = y_last
        Next
    End Sub
    Public Sub back_drawing()
        Me.drawing_file.back()
        Me.showDrawing(Me.drawing_file.getPath())
    End Sub
End Class
