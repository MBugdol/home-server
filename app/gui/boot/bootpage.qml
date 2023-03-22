import QtQuick
import QtQuick.Controls

Page {
	id: root
	background: Rectangle {color: "steelblue"}
	Label {
		anchors.centerIn: parent
		text: "I'm broot!"
	}
	Timer {
		id: tempTimer
		interval: 1000
		running: true
		repeat: false
		onTriggered: FlowController.switchTo("login/loginpage.qml")
	}
}