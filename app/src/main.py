import sys
from PySide6.QtCore import QDir
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtGui import QGuiApplication
from PySide6.QtQuickControls2 import QQuickStyle

import rc_style

if __name__ == '__main__':
	app = QGuiApplication(sys.argv)
	QQuickStyle.setStyle("Material")
	engine = QQmlApplicationEngine()

	main_qml = QDir(__file__)
	main_qml.cd('../../src-qml')
	print(main_qml.absoluteFilePath('main.qml'))
	engine.load(main_qml.absoluteFilePath('main.qml'))

	if not engine.rootObjects():
		sys.exit(-1)
	
	sys.exit(app.exec())
