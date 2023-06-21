import sys
from PySide6.QtCore import QDir
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtGui import QGuiApplication
from PySide6.QtQuickControls2 import QQuickStyle

import app.logic as logic

def exec():
	app = QGuiApplication(sys.argv)
	QQuickStyle.setStyle("Material")
	engine = QQmlApplicationEngine()


	backend = logic.Backend()
	
	engine.rootContext().setContextProperty("Backend", backend)
	engine.rootContext().setContextProperty("FlowController", backend.FlowController)

	

	main_qml = QDir(__file__)
	main_qml.cd('../../gui')
	print(main_qml.absoluteFilePath('main.qml'))
	engine.load(main_qml.absoluteFilePath('main.qml'))

	if not engine.rootObjects():
		sys.exit(-1)
	
	sys.exit(app.exec())
