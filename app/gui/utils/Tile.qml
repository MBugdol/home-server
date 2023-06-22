import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
	id: root
	default property alias children: contentItem.children
	property color color: Material.backgroundDimColor
	property color hoverColor: Material.primaryColor
	property int sideLength: 0

	signal clicked(mouse_event: QtObject)

	width: sideLength
	height: sideLength
	Rectangle {
		id: visual
		color: control.containsMouse ? root.hoverColor : root.color
		anchors.fill: parent
		Item {
			id: contentItem
			anchors.centerIn: parent
			height: parent.height * 0.9
			width: parent.width * 0.9
		}
		Behavior on color {ColorAnimation {duration: 100}}
	} // visual

	MouseArea {
		id: control
		anchors.fill: parent
		hoverEnabled: true
		acceptedButtons: Qt.AllButtons
		onClicked: (mouse_event) => root.clicked(mouse_event)
	} // control
	
} // root