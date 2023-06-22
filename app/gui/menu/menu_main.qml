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
		acceptLabel: qsTr("Upload")
		fileMode: FileDialog.SaveFile
		onAccepted: Backend.uploadFile(selectedFile)
	}

	FileDialog {
		id: fileDownloadDialog
		property string serverFilename
		fileMode: FileDialog.SaveFile
		onAccepted: Backend.downloadFile(serverFilename, selectedFile)

		function openWithName(filename)
		{
			fileDownloadDialog.selectedFile = fileDownloadDialog.currentFolder + "/" + filename
			serverFilename = filename
			fileDownloadDialog.open()
		}
	}

	ScrollView {
		id: mainMenuScroll
		anchors.fill: parent
		MouseArea {
			id: backgroundMouseArea
			anchors.fill: parent
			acceptedButtons: Qt.AllButtons
			onClicked: function (mouse) {
				if(mouse.button === Qt.RightButton)
					backgroundContextMenu.popup()
				else if(mouse.button === Qt.LeftButton)
					foldersRepeater.currentIndex = -1
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
				property int currentIndex: -1
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
					id: delegateTile
					text: modelData.name
					color: foldersRepeater.currentIndex === index ? Material.primaryColor : "transparent"
					Image {
						anchors.centerIn: parent
						width: 0.8 * parent.width
						height: 0.8 * parent.width
						sourceSize.width: width
						sourceSize.height: height
						source: modelData.type === "directory" ? "../res/img/folder-icon.svg" : "../res/img/file-icon.svg" // add main.qml to qrc?
						fillMode: Image.PreserveAspectFit
					}
					MouseArea {
						id: tileMouseArea
						anchors.fill: parent
						hoverEnabled: true
						acceptedButtons: Qt.AllButtons

						Menu {
							id: fileContextMenu
							MenuItem {
								text: "Download"
								onClicked: fileDownloadDialog.openWithName(modelData.name)
								
							}
						}
						onClicked: function(mouse) {
							if(mouse.button === Qt.LeftButton) {
								foldersRepeater.currentIndex = index
							}
							else if(mouse.button === Qt.RightButton) {
								if(modelData.type == "file")
									fileContextMenu.popup()
							}
						}
						onDoubleClicked: function(mouse) {
							if(mouse.button === Qt.LeftButton) {
								if(modelData.type == "directory")
									Backend.cd(modelData.name)
								else if(modelData.type == "cdup")
									Backend.cdUp()
							}
						}
						
					} // tileMouseArea
				}
			}
			Connections {
				target: Backend
				function onCwdChanged() {
					foldersRepeater.setModel(Backend.getCurrentChildren())
					foldersRepeater.currentIndex = -1
				}
			}
		}
	} // mainMenuScroll
}