Public Class DrawingView
    Private p_start As Point
    Private p_end As Point
    Private mouse As Boolean = False
    Private first_point_selected_line As Boolean = False
    Private first_point_selected_circle As Boolean = False
    Private btn_selected As Integer = -1
    Private con As Controller

    Private Sub Btn_cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_cancel.Click
        Me.con.delete_drawing_file()
        Me.Close()
    End Sub


    Private Sub Btn_back_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_back.Click
        Me.btn_selected = 1
        Me.Btn_back.Enabled() = False
        Me.Refresh()
        Me.con.back_drawing()
    End Sub


    Private Sub Btn_line_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_line.Click
        Me.Lbl_order.Text = "Markieren Sie den Startpunkt der Linie auf der Zeichenebene"
        Me.btn_selected = 2

    End Sub

    Private Sub Btn_circle_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_circle.Click
        Me.Lbl_order.Text = "Markieren Sie den Startpunkt des Kreises auf der Zeichenebene"
        Me.btn_selected = 3
    End Sub



    Public Sub draw_line(ByVal p_start As Point, ByVal p_end As Point)
        Console.WriteLine("Point" + p_start.X.ToString + " " + p_start.Y.ToString + " " + p_end.X.ToString + " " + p_end.Y.ToString)
        Me.Group_1.CreateGraphics.DrawLine(Pens.White, p_start.X, p_start.Y, p_end.X, p_end.Y)
    End Sub


    Private Sub Group_1_MouseClick(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseClick
        If (Me.btn_selected = 2) Then ' Line Button wurde zuvor aktiviert
            If (Me.first_point_selected_line) Then
                Me.Lbl_order.Text = "Klicken Sie zum Zeichnen auf die Linie bzw. den Viertelkreis"
                Me.draw_line(p_start, New Point(e.X, e.Y))
                Me.con.save_drawing_steps(p_start, New Point(e.X, e.Y))
                Me.Btn_back_Enabled()
                p_end.X = e.X
                p_end.Y = e.Y
                Me.first_point_selected_line = False
            Else
                Me.Lbl_order.Text = "Markieren Sie nun den Endpunkt der Linie auf der Zeichenebene"
                Me.first_point_selected_line = True
                Me.first_point_selected_circle = False
                p_start = New Point(e.X, e.Y)

            End If


        ElseIf (Me.btn_selected = 3) Then 'Circle Button wurde zuvor aktiviert 
            If (Me.first_point_selected_circle) Then
                Dim swapAngle As Integer = Me.show_MsgBox_for_swapAngle()
                Me.Lbl_order.Text = "Klicken Sie zum Zeichnen auf die Linie bzw. den Viertelkreis"
                Me.Btn_back_Enabled()
                Me.con.draw_circle_drawingView(New Point(e.X, e.Y), p_start, swapAngle)
                Me.first_point_selected_circle = False
            Else
                Me.Lbl_order.Text = "Markieren Sie nun den Mittelpunkt auf der Zeichenebene"
                Me.first_point_selected_circle = True
                Me.first_point_selected_line = False
                p_start = New Point(e.X, e.Y)

            End If
        End If
    End Sub


    Private Sub Group_1_MouseMove(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseMove
       
        Label1.Text = "X - Achse: " + e.X.ToString
        Label2.Text = "Y - Achse: " + e.Y.ToString
    End Sub

    Private Sub Zeichnung_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.con = Controller.getInstance
        Me.con.set_DrawingView(Me)
        Me.con.delete_drawing_file()
    End Sub

    

    Private Sub Btn_save_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_save.Click
        Dim filepath As String
        If (SaveFileDialog.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            filepath = SaveFileDialog.FileName
            Me.con.save_drawing_to_file(filepath)
            Me.con.refreshPreview()
            Me.con.showPreview(filepath)
            Me.Hide()
        End If

    End Sub

    Public Sub Btn_back_Enabled()
        If Not (Me.Btn_back.Enabled) Then
            Me.Btn_back.Enabled = Not (Me.Btn_back.Enabled)
        End If

    End Sub

    Public Sub draw_circle(ByVal rect As Rectangle, ByVal startAngle As Single, ByVal swapAngle As Single)
        Me.Group_1.CreateGraphics.DrawArc(Pens.White, rect, -1 * startAngle, swapAngle)
    End Sub

    Private Function show_MsgBox_for_swapAngle() As Integer
        Dim angle_string As String
        Dim angle As Integer
        angle_string = InputBox(Prompt:="Bitte Kreiswinkel eingeben!", Title:="Abfrage Kreiswinkel")

        If Not IsNumeric(angle_string) Then
            MsgBox("Fehler bei der Eingabe! Versuchen Sie es erneut")
            Me.show_MsgBox_for_swapAngle()
        Else
            angle = Val(angle_string)
            angle = angle * -1
        End If
        Return angle
    End Function

    Private Sub Btn_import_Click(sender As Object, e As EventArgs) Handles Btn_import.Click
        Me.con.start_printing_from_drawingView()
        Me.con.refreshPreview()
        Me.con.showPreview(Me.con.getPath())
        Me.Hide()
    End Sub


End Class