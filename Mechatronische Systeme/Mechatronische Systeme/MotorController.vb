Public Class MotorController
	Private datas As List(Of Integer())
	Private max_steps_x As Integer
	Private max_steps_y As Integer
	Private max_x As Integer 'die cm des blattes warscheinlich A4
	Private max_y As Integer

	'konstruktor als singelton

	Private Sub reset() 'reset Motoren, zähle die steps für einmal komplett ausfahren
	End Sub
	
	Public Sub setDatas(datas As List(Of Integer())) ' bekommt das Daten-Array mit den Linien und Stift zuständen
		'berechnet anhand der koordinaten des Arrays dir anzahl der Steps und konvertiert somit die cm in steps für die motorsteuerung
	End Sub

	Public function drawNext() As Boolean 'solange Bool=true, hat noch ein datensatz im Array und kann weiter zeichnen
	End function
	
	Private Sub move(ByVal x_steps As Integer, ByVal y_steps As Integer, ByVal status As Boolean)
		'bewegt den Stift in x,y richtig mit den angegebenen Steps so, dass die Motoren unterschiedlich schnell laufen damit die Endposition gleichzeitig erreicht wird
	End Sub
End Class
