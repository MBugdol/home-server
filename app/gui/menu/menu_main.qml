import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import "../utils"

Page {
	id: root
	background: Rectangle {color: Material.backgroundColor}
	header: ToolBar {
		RowLayout {
			anchors.fill: parent
			spacing: 5
			Label {
				id: cwdLabel
				Layout.maximumWidth: 0.4 * parent.width
				text: Backend.getCwd()
				elide: Text.ElideRight
				Connections {
					target: Backend
					function onCwdChanged() {cwdLabel.text = Backend.getCwd()}
				}
			}
			TextField {
				Layout.minimumWidth: 0.2 * parent.width
				Layout.fillWidth: true
				placeholderText: "Search in this folder..."
				clip: true
				onAccepted: Backend.searchFor(text)
			}
		}
	}

	FileDialog {
		id: fileUploadDialog
		acceptLabel: "Upload"
		rejectLabel: "Cancel"
		options: FileDialog.ReadOnly | FileDialog.DontConfirmOverwrite
		onAccepted: Backend.uploadFile(selectedFile)
	}

	ScrollView {
		id: mainMenuScroll
		anchors.fill: parent
		MouseArea {
			id: backgroundMouseArea
			anchors.fill: parent
			acceptedButtons: Qt.RightButton
			onClicked: function (mouse) {
				if(mouse.button === Qt.RightButton)
					backgroundContextMenu.popup()
			}

			Menu {
				id: backgroundContextMenu
				MenuItem {
					text: "New folder"
					onClicked: Backend.createNewFolder()
				}
				MenuItem {
					text: "Upload a file"
					onClicked: fileUploadDialog.open()
				}
			}
		} // backgroundMouseArea

		GridLayout {
			id: tileGrid
			readonly property int minColSpacing: 5
			readonly property int tileSide: 100
			// some lovely gui math
			columns: (mainMenuScroll.width + minColSpacing) / (tileSide + minColSpacing)
			columnSpacing: (mainMenuScroll.width - columns * tileSide) / (columns-1)
			component GridTile: Tile {
				Layout.preferredWidth: tileGrid.tileSide
				Layout.preferredHeight: tileGrid.tileSide
				color: "transparent"
				property alias text: containedText.text
				Label {
					id: containedText
					anchors.centerIn: parent
				}
				
			}
			Repeater {
				id: foldersRepeater
				function setModel(new_model)
				{
					let model_begin = [
						{
							"name": "..",
							"type": "cdup"
						}
					]
					foldersRepeater.model = model_begin.concat(new_model)
				}
				Component.onCompleted: {setModel(Backend.getCurrentChildren())}
				GridTile {
					onClicked: {
						if(modelData.type == "directory")
							Backend.cd(modelData.name)
						else if(modelData.type == "cdup")
							Backend.cdUp()

					}
					text: modelData.name
					Image {
						anchors.centerIn: parent
						width: 0.8 * parent.width
						height: 0.8 * parent.width
						sourceSize.width: width
						sourceSize.height: height
						source: modelData.type === "directory" ? "../res/img/folder-icon.svg" : "../res/img/file-icon.svg" // add main.qml to qrc?
						fillMode: Image.PreserveAspectFit
					}
				}
			}
			Connections {
				target: Backend
				function onCwdChanged() {
					foldersRepeater.setModel(Backend.getCurrentChildren())
				}
			}
		}
	} // mainMenuScroll
}