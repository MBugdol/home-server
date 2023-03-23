import QtQuick
import QtQuick.Controls

Page {
	id: root
	background: Rectangle {color: "green"}
	Column {
		height: childrenRect.height
		width: parent.width
		anchors.centerIn: parent
		TextArea {
			id: dirinput
			width: 0.8 * parent.width
			anchors.horizontalCenter: parent.horizontalCenter
		}
		Button {
			anchors.horizontalCenter: parent.horizontalCenter
			text: "Create folder!"
			onClicked: {
				var success = APICaller.createFolder(dirinput.text)
				if(success) {
					resText.text = "Successfully created directory " + dirinput.text
					resText.color = "green"
				}
				else {
					resText.text = "Specified directory is not a valid directory!"
					resText.color = "red"
				}
			}
		}
		Label {
			id: resText
			background: Pane {}
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}