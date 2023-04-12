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
		function onPushRequest (arg) { menuStack.push(arg) }
		function onSwitchRequest (arg) { menuStack.replace(arg) }
		function onPopRequest () { menuStack.pop() }
	}

	Component.onCompleted: FlowController.push("boot/bootpage.qml")
} //root 