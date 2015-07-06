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

    'Privater Konstruktur, der bei dessen Aufruf die einzelnen Variablen initialisiert 
    Private Sub New()
        Me.settings = Save_read_settings.getInstance
        Me.parser = parser.getInstance()
        Me.drawing_file = Drawing_to_file.getInstance
        '  Me.moCon = MotorController.getInstance
        Me.calc = Calculator.getInstance
    End Sub

    ' Da es sich hier bei dieser Klasse um ein "Singleton - Pattern" handelt, besitzt diese auch keinen
    ' öffentlich zugänglichen Konstruktur; stattdessen wird durch Aufruf dieser Funktion eine Instanz 
    ' zurueckgegeben; hierbei wird zunaechst ueberprueft, ob diese bereits existiert; falls nicht wird 
    ' eine entsprechende angelegt
    Public Shared ReadOnly Property getInstance() As Controller
        Get
            If IsNothing(Instance) Then
                instance = New Controller()
            End If
            Return Instance
        End Get
    End Property

    'Diese Funktion fuehrt dazu die in dem Parameter "filepath" uebergebene Datei zu parsen und das Ergebnis (Array) 
    'der Variablen "list" zuzuweisen
    Private Sub parse(ByVal filepath As String)
        Me.list = Me.parser.parseFile(filepath)
    End Sub

    'Diese Funktion dient dem Loeschen der "preview" in der Form "MainView"
    Public Sub refreshPreview()
        Me.main_form.Refresh()
    End Sub

    'Diese Funktion ermoeglicht den Druckvorgang aus der Form "Zeichnung" heraus zu starten; hierfuer muss jedoch 
    'die temporaere Datei geparst werden, um fuer den Drucker verstaendliche Druckbefehle zu generieren; bei einem
    'Fehler wird eine entsprechende Meldung ausgegeben
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

    'Diese Funktion dient dem Laden der Einstellungen, die in der Form "Settings" angezeigt werden;
    'dazu werden die entsprechenden Funktionen "getX_motor","getY_motor","get_tuning" im Objekt "settings" aufgerufen
    'die Werte den Variablen "x_motor","y_motor","tuning" zwischengespeichert und zum Abschluß in der 
    'uebergebenen Form "form" gesetzt
    Public Sub load_settings(ByVal form As Settings)
        Dim x_motor, y_motor, tuning As String
       
        tuning = Me.settings.get_tuning()
       
        form.setScrollBar(tuning)
    End Sub

    'Diese Funktion dient dem Abspeichern der Einstellungen, die in der Form "Settings" getaetigt wurden; hierzu werden
    'die entsprechenden Funktionen "writeX_motor","writeY_motor","write_tuning" im Objekt "settings" aufgerufen
    Public Sub save_settings(ByVal tuning As Integer)
        Me.settings.write_tuning(tuning)
    End Sub

    'Diese Funktion setzt die Variable "main_form" mittels des uebergebenen Parameters; durch diese Variable wird es ermoeglicht
    'auf die Form "MainView" zuzugreifen
    Public Sub set_MainView(ByRef form As Form)
        Me.main_form = form
    End Sub

    'Diese Funktion setzt die Variable "drawing_form" mittels des uebergebenen Parameters; durch diese Variable wird es ermoeglicht
    'auf die Form "Zeichnung" zuzugreifen
    Public Sub set_DrawingView(ByRef form As Form)
        Me.drawing_form = form
    End Sub

    'Diese Funktion, dient dem Einzeichnen von Linien in der Zeichenbene "preview" der Form "MainView"
    Private Sub line_preview(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_preview(p_old, p_new)
        End If
    End Sub

    'Diese Funktion, dient dem Einzeichnen von Linien in der Zeichenbene  der Form "Zeichnung"
    Private Sub line_drawing(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.drawing_form) Then
            Me.drawing_form.draw_line(p_old, p_new)
        End If
    End Sub

    'Diese Funktion, dient dem Einzeichnen der Linien in der Zeichenbene "live_print" der Form "MainView" waehrend des Druckvorgangs
    Public Sub line_live_print(ByVal p_old As Point, ByVal p_new As Point)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.draw_live_print(p_old, p_new)
        End If
    End Sub

    'Funktion die der Wertzuweisung der Progressbar "Progress" dient;
    Public Sub progress(ByVal x As Integer)
        If Not IsNothing(Me.main_form) Then
            Me.main_form.Progress(x)
        End If
    End Sub


    'Diese Funktion ermoeglicht es, die Druckdatei zu parsen ("parse"),sowie in die Form "MainView" zu laden;
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

    'Funktion, zum Loeschen der temporaeren Datei, welche in der Form "Zeichnung" fuer die Sicherung der zeichnerisch 
    'getaetigten Schritte dient;
    Public Sub delete_drawing_file()
        Me.drawing_file.delete_file()
    End Sub

    'Funktion, die zur Speicherung der temporaeren Datei in ein von dem Benutzer angegebenes Verzeichnis dient
    Public Sub save_drawing_to_file(ByVal filename As String)
        Me.drawing_file.save_file_to_path(filename)
    End Sub

    'Speichert den Schritt ab, der als Letztes in die Zeichenebene in der Form "Zeichnung" zeichnerisch getaetigt wurde 
    Public Sub save_drawing_steps(ByVal p_start As Point, ByVal p_end As Point)
        Me.drawing_file.save_drawing_steps(p_start, p_end)
    End Sub

    'Diese Funktion ermoeglicht es, die Druckdatei zu parsen ("parse"),sowie in die Form "Zeichnung" zu laden;
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

    'Diese Funktion wird fuer die Zureckfunktion in der Form "Zeichnung" verwendet; sie fuehrt dazu die Daten fuer die Zeichnung
    'in der Datei anzupassen, sowie in der Form die Zeichnung neu zuladen 
    Public Sub back_drawing()
        Me.drawing_file.back()
        Me.showDrawing(Me.drawing_file.getPath())
    End Sub

    'Gibt den aktuellen Pfad zurueck, unter dem die Zeichnung in der Form "Zeichnung" abgelegt ist
    Public Function getPath() As String
        Return Me.drawing_file.getPath()
    End Function

    'Um einen Kreis in der DrawingView zu zeichnen, wird diese Funktion benoetigt; diese dient dazu die erforderlichen Parameter 
    'wie Startwinkel ("calc_StartAngle") und Kreiswinkel zu ermitteln, die Daten in der temporaeren Datei abzuspeichern, sowie in der Form
    '"Zeichnung" den Kreis in der Zeichenebene ("draw_Circle_drawingView") einzuzeichnen 
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

    'Bricht den Druckvorgang durch Aufruf der Funktion "break" im Motorcontroller "moCon" ab
    Public Sub stop_plotter()
        Me.moCon.break()
    End Sub

    'Pausiert den Druckvorgang durch Aufruf der Funktion "pause" im Motorcontroller "moCon"
    Public Sub pause_plotter()
        Me.moCon.pause()
    End Sub

    'Setzt den Druckvorgang nach einer Pausierung durch Aufruf der Funktion "unpause" im Motorcontroller "moCon" fort 
    Public Sub unpause_plotter()
        Me.moCon.unpause()
    End Sub

    'Startet den Druckvorgang; dazu werden die Daten "list" dem MotorController "moCon" uebergeben ("setDatas")
    'und der Druckvorgang durch Aufruf der Funktion "start" im MotorController "moCon" gestartet
    Public Sub start_plotter()
        Me.moCon.setDatas(Me.list)
        Me.moCon.start()
    End Sub
End Class


