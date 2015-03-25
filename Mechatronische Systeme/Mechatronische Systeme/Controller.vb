Public Class Controller
    Private form As MainView
    Private settings As Save_read_settings
    Private Shared instance As Controller

    Private Sub New()
        settings = Save_read_settings.getInstance
    End Sub

    Public Shared ReadOnly Property getInstance() As Controller
        Get
            If IsNothing(Instance) Then
                instance = New Controller()
            End If
            Return Instance
        End Get
    End Property

    Public Sub parse(filepath As String)
        '  parser = New Parser(filepath)
        ' parser.parseFile()
    End Sub


    Public Sub load_settings(form As Settings)
        Dim x_motor, y_motor, tuning As String
        x_motor = Me.settings.ReadValue("settings", "x_motor")
        y_motor = Me.settings.ReadValue("settings", "y_motor")
        tuning = Me.settings.ReadValue("settings", "tuning")
        form.setTxt_1(x_motor)
        form.setTxt_2(y_motor)
        form.setScrollBar(tuning)
    End Sub

    Public Sub save_settings(x_motor As String, y_motor As String, tuning As Integer)
        settings.WriteValue("settings", "x_motor", x_motor)
        settings.WriteValue("settings", "y_motor", y_motor)
        settings.WriteValue("settings", "tuning", tuning)
    End Sub

    Public Sub set_MainView(form As Form)
        Me.form = form
    End Sub


    Private Sub line_preview(x_old As Integer, y_old As Integer, x_new As Integer, y_new As Integer)
        If Not IsNothing(Me.form) Then
            Me.form.draw_preview(x_old, y_old, x_new, y_new)
        End If
    End Sub

    Public Sub line_live_print(x_old As Integer, y_old As Integer, x_new As Integer, y_new As Integer)
        If Not IsNothing(Me.form) Then
            Me.form.draw_live_print(x_old, y_old, x_new, y_new)
        End If
    End Sub

    Public Sub progress(ByVal x As Integer)
        If Not IsNothing(Me.form) Then
            Me.form.Progress(x)
        End If
    End Sub

End Class
