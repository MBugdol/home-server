import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
	id: root
	background: Rectangle {color: "green"}
	GridLayout {
		component SquareTitle: Rectangle {
			//Layout.minimumHeight
			//width = height = min(screenwidth, screenheight) / 6?
		}
	}
}