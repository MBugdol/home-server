import QtQuick
import QtQuick.Controls

Page {
	id: root
	background: Rectangle {color: "steelblue"}
	Label {
		anchors.centerIn: parent
		text: "HoSe"
		font.pixelSize: root.height * 0.4
		verticalAlignment: Text.AlignVCenter
	}
	Timer {
		id: tempTimer
		interval: 1000
		running: true
		repeat: false
		onTriggered: FlowController.switchTo("menu/menu_main.qml")
	}
}