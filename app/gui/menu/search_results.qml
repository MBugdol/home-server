import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page {
	id: root
	required property string phrase
	required property var matches

	header: ToolBar {
		RowLayout {
			id: pageHeader
			anchors.fill: parent
			Label {
				id: searchInfoLabel
				Layout.preferredHeight: parent.height
				Layout.fillWidth: true
				text: qsTr("Search results for '") + root.phrase + "':"
				horizontalAlignment: Text.AlignLeft
				verticalAlignment: Text.AlignVCenter
				font.pixelSize: parent.height / 2
			}
		}
	}

	ListView {
		id: matchesList
		function getModelWithCdup() {
			let cdup_model = [
				{
					'name':'<-',
					'type':'back',
					'path':''
				}
			]
			return cdup_model.concat(root.matches)
		}
		anchors.fill: parent
		model: getModelWithCdup()
		delegate: Item {
			id: matchesDelegate
			width: matchesList.width
			height: matchesDelegateContent.height + 10
			Rectangle {
				id: matchesDelegateBackground
				anchors.fill: parent
				color: matchesDelegate.ListView.isCurrentItem ? Material.accent : Material.buttonColor
				border.color: Material.primaryTextColor
				border.width: 1
			}
			RowLayout {
				id: matchesDelegateContent
				width: parent.width
				height: matchesDelegateInfo.height 
				anchors.verticalCenter: parent.verticalCenter
				Image {
					id: matchesDelegateIcon
					Layout.preferredWidth: parent.height
					Layout.preferredHeight: parent.height
					sourceSize.width: width
					sourceSize.height: height
					source: modelData.type === "directory" ? "qrc:/img/folder-icon.svg" : "qrc:/img/file-icon.svg"
					fillMode: Image.PreserveAspectFit
				}
				Column {
					id: matchesDelegateInfo
					Layout.preferredHeight: childrenRect.height
					Layout.fillWidth: true

					Label {
						id: matchesDelegateName
						width: parent.width
						text: modelData.name
						horizontalAlignment: Text.alignLeft
					}
					Label {
						id: matchesDelegatePath
						width: parent.width
						text: modelData.path
						color: Material.hintTextColor
						elide: Text.ElideMiddle
						horizontalAlignment: Text.alignLeft
					}
				}
			}
			MouseArea {
				anchors.fill: parent
				onClicked: {
					matchesList.currentIndex = index
				}
				onDoubleClicked: {
					FlowController.pop()
					if(modelData.type !== 'back')
						Backend.setCwd(modelData.path, modelData.type)
				}
			}
		}
	}
}