Public Class Settings
    Private con As Controller

    Private Sub Btn_cancel_Click(sender As System.Object, e As System.EventArgs) Handles Btn_cancel.Click
        Me.Close()
    End Sub

   
    Private Sub Btn_save_Click(sender As System.Object, e As System.EventArgs) Handles Btn_save.Click
        If save() Then
            Me.Close()
        End If

    End Sub

    Private Sub Settings_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        con = Controller.getInstance
        con.load_settings(Me)
    End Sub

    Public Sub setTxt_1(txt As String)
            Me.TxtBox_1.Text = txt
    End Sub

    Public Sub setTxt_2(txt As String)
        Me.TxtBox_2.Text = txt
    End Sub

    Public Sub setScrollBar(txt As String)
        Me.Lbl_4.Text = "Wert: " + txt
        Me.Scroll_1.Value = CInt(txt)
    End Sub

    Private Function save() As Boolean
        If IsNumeric(Me.TxtBox_1.Text) And IsNumeric(Me.TxtBox_2.Text) Then
            con.save_settings(Me.TxtBox_1.Text, Me.TxtBox_2.Text, Me.Scroll_1.Value)
            Return True
        Else
            MsgBox("Einer Ihrer Eingaben ist keine Zahl")
        End If
        Return False
    End Function

    Private Sub Scroll_1_Scroll(sender As System.Object, e As System.Windows.Forms.ScrollEventArgs) Handles Scroll_1.Scroll
        Me.Lbl_4.Text = "Wert: " + Me.Scroll_1.Value.ToString
    End Sub

    Private Sub Lbl_1_Click(sender As Object, e As EventArgs) Handles Lbl_1.Click

    End Sub
End Class