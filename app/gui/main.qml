import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
	id: root
	visible: true
	width: 500
	height: 500
	
	StackView {
		id: menuStack
		anchors.fill: parent
	}
	Connections {
		target: FlowController
		function onPushRequest (page, args = {}) { menuStack.push(page, args) }
		function onSwitchRequest (arg) { menuStack.replace(arg) }
		function onPopRequest () { menuStack.pop() }
	}

	Component.onCompleted: FlowController.push("qrc:/boot/bootpage.qml")
} //root 