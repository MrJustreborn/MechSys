Public Class Controller
    Private main_form As MainView
    Private drawing_form As DrawingView
    Private settings As Save_read_settings
    Private Shared instance As Controller
    Private parser As Parser
    Private drawing_file As Drawing_to_file
    Private calc As Calculator
    Private moCon As MotorController
    Private list As List(Of Integer())

    Private Sub New()
        Me.settings = Save_read_settings.getInstance
        Me.parser = parser.getInstance()
        Me.drawing_file = Drawing_to_file.getInstance
        Me.moCon = MotorController.getInstance
        Me.calc = Calculator.getInstance
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
    Public Sub refreshPreview()
        Me.main_form.Refresh()
    End Sub
    Public Sub start_printing_from_drawingView()
        Dim path As String
        path = Me.getPath()
        Me.parse(path)
        If (Me.list.Count > 0) Then
            Me.start_plotter()
        Else
            MsgBox("Der Printvorgang kann nicht gestartet werden, da Sie nichts gezeichnet haben")
        End If

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

    Private Sub line_preview(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_preview(p_old, p_new)
        End If
    End Sub

    Private Sub line_drawing(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.drawing_form) Then
            Me.drawing_form.draw_line(p_old, p_new)
        End If
    End Sub

    Public Sub line_live_print(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_live_print(p_old, p_new)
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
        Dim p_last As Point
        Dim p_start As New Point(0, 0)
        

        Me.parse(filepath)
       
        For Each item In Me.list
            p_last.X = p_start.X + item(1)
            p_last.Y = p_start.Y + item(2)

            If (item(0) = 0) Then
                Dim p_temp_st As Point = p_start
                Dim p_temp_last As Point = p_last

                p_temp_st.X /= factor
                p_temp_st.Y /= factor
                p_temp_last.X /= factor
                p_temp_last.Y /= factor
                Me.line_preview(p_temp_st, p_temp_last)
            End If
            p_start = p_last
        Next
    End Sub

    Public Sub delete_drawing_file()
        Me.drawing_file.delete_file()
    End Sub

    Public Sub save_drawing_to_file(ByVal filename As String)
        Me.drawing_file.save_file_to_path(filename)
    End Sub

    Public Sub save_drawing_steps(ByVal p_start As Point, ByVal p_end As Point)
        Me.drawing_file.save_drawing_steps(p_start, p_end)
    End Sub

    Private Sub showDrawing(ByVal filepath As String)
        Dim factor = 10
        Dim p_last As Point
        
        Dim p_start As New Point(0, 0)

        Me.parse(filepath)
        If Not (Me.list Is Nothing) Then
            For Each item In Me.list
                p_last.X = p_start.X + item(1)
                p_last.Y = p_start.Y + item(2)

                If (item(0) = 0) Then
                    Dim p_temp_st As Point = p_start
                    Dim p_temp_last As Point = p_last

                    p_temp_st.X /= factor
                    p_temp_st.Y /= factor
                    p_temp_last.X /= factor
                    p_temp_last.Y /= factor
                    Me.line_drawing(p_temp_st, p_temp_last)
                End If
                p_start = p_last
            Next
        Else
            Me.drawing_form.Btn_back_Enabled()
        End If
        
    End Sub

    
    Public Sub back_drawing()
        Me.drawing_file.back()
        Me.showDrawing(Me.drawing_file.getPath())
    End Sub

    Public Function getPath() As String
        Return Me.drawing_file.getPath()
    End Function


    Public Sub draw_circle_drawingView(ByVal middle As Point, ByVal point As Point, ByVal swapAngle As Integer)
        Dim rect As Rectangle
        Dim startAngle As Single

        rect = Me.calc.calcRectangle(middle, point)
        startAngle = Me.calc.calc_startAngle(middle.X, point.X)
        If (middle.Y < point.Y) Then
            startAngle += 180
        End If
        Me.drawing_file.save_drawing_steps(middle, point, swapAngle)
        Me.drawCircle_drawingView(rect, startAngle, swapAngle)

    End Sub

    ' Zeichnet einen Kreis in der DrawingView 
    Private Sub drawCircle_drawingView(ByVal rect As Rectangle, ByVal startAngle As Single, ByVal swapAngle As Single)
        Me.drawing_form.draw_circle(rect, startAngle, swapAngle)
    End Sub

    Public Sub stop_plotter()
        Me.moCon.break()
    End Sub

    Public Sub pause_plotter()
        Me.moCon.pause()
    End Sub

    Public Sub unpause_plotter()
        Me.moCon.unpause()
    End Sub

    Public Sub start_plotter()
        Me.moCon.setDatas(Me.list)
        Me.moCon.start()
    End Sub
End Class


