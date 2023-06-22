import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
	id: root
	default property alias children: contentItem.children
	property color color 
	property int sideLength: 0

	signal clicked(mouse_event: QtObject)

	width: sideLength
	height: sideLength
	Rectangle {
		id: visual
		color: root.color
		anchors.fill: parent
		Item {
			id: contentItem
			anchors.centerIn: parent
			height: parent.height * 0.9
			width: parent.width * 0.9
		}
		Behavior on color {ColorAnimation {duration: 100}}
	} // visual

	
	
} // root