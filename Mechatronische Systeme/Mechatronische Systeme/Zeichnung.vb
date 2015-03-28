Public Class Zeichnung
   
    Private x_start As Integer = 0
    Private y_start As Integer = 0
    Private x_end As Integer
    Private y_end As Integer
    Private first_point_selected As Boolean = False
    Private btn_selected As Integer = -1
    Private con As Controller

    Private Sub Btn_cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_cancel.Click
        Me.con.delete_drawing_file()
        Me.Close()
    End Sub


    Private Sub Btn_back_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_back.Click
        Me.btn_selected = 1

    End Sub


    Private Sub Btn_line_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_line.Click
        Me.btn_selected = 2

    End Sub

    Private Sub Btn_circle_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_circle.Click
        Me.btn_selected = 3
    End Sub



    Public Sub draw_line(ByVal x_start As Integer, ByVal y_start As Integer, ByVal x_end As Integer, ByVal y_end As Integer)
        Me.Group_1.CreateGraphics.DrawLine(Pens.White, x_start, y_start, x_end, y_end)
        Me.con.save_drawing_steps(x_start, y_start, x_end, y_end)
    End Sub


    Private Sub Group_1_MouseClick(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseClick
        If (Me.btn_selected = 1) Then 'Zurück Button wurde zuvor aktiviert
          
        ElseIf (Me.btn_selected = 2) Then ' Line Button wurde zuvor aktiviert
            If Me.first_point_selected Then
                Me.draw_line(x_start, y_start, e.X, e.Y)
                x_end = e.X
                y_end = e.Y
                Me.first_point_selected = False
            Else
                Me.first_point_selected = True
                x_start = e.X
                y_start = e.Y

               

            End If
        ElseIf (Me.btn_selected = 3) Then 'Circle Button wurde zuvor aktiviert 

        End If
    End Sub

    Private Sub Group_1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Group_1.Enter

    End Sub

    Private Sub Group_1_MouseMove(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseMove
        Label1.Text = e.X
        Label2.Text = e.Y
    End Sub

    Private Sub Zeichnung_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.con = Controller.getInstance
    End Sub

    Private Sub Btn_save_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_save.Click
        Dim filepath As String
        If (SaveFileDialog.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            filepath = SaveFileDialog.FileName
            Me.con.save_drawing_to_file(filepath)
            Me.con.showPreview(filepath)
            Me.Hide()
        End If
        
    End Sub

    Private Sub SaveFileDialog1_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles SaveFileDialog.FileOk

    End Sub
End Class