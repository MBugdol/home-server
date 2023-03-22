import QtQuick
import QtQuick.Controls

Page {
	id: root
	background: Rectangle{color: "red"}
	Label {
		anchors.centerIn: parent
		text: "It's-a me, login!"
	}
	Timer {
		id: tempTimer
		interval: 1000
		running: true
		repeat: false
		onTriggered: FlowController.switchTo("menu/menu_main.qml")
	}
}