import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import "../utils"

Page {
	id: root
	property string moveOrigin: Backend.getMoveOrigin()
	property string cwd: Backend.getCwd()
	Connections {
		target: Backend
		function onCwdChanged() {root.cwd = Backend.getCwd()}
	}

	background: Rectangle {color: Material.backgroundColor}
	header: ToolBar {
		RowLayout {
			height: parent.height
			width: 0.9 * parent.width
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: 5
			Button {
				id: cdRootButton
				Layout.preferredWidth: implicitHeight
				text: "~"
				onClicked: Backend.setCwd('', 'directory')
			}
			Label {
				id: cwdLabel
				Layout.maximumWidth: 0.4 * parent.width
				text: root.cwd
				elide: Text.ElideLeft
				clip: true
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
		options: FileDialog.DontConfirmOverwrite | FileDialog.ReadOnly
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

	Popup {
		id: entryRenameDialog
		property string entry
		parent: Overlay.overlay
		anchors.centerIn: parent
		width: 0.5 * parent.width
		Column {
			anchors.fill: parent
			Label {
				text: "Enter the new name:"
				anchors.horizontalCenter: parent.horizontalCenter
			}
			TextField {
				id: entryRenameInput
				text: entryRenameDialog.entry
				horizontalAlignment: Text.AlignHCenter
				anchors.horizontalCenter: parent.horizontalCenter
				clip: true
			}
			Button {
				id: entryRenameSubmit
				anchors.horizontalCenter: parent.horizontalCenter
				text: "Submit"
				onClicked: {
					Backend.rename(entryRenameDialog.entry, entryRenameInput.text)
					entryRenameDialog.close()
				}
			}
		}
		function pop(entry_)
		{
			entryRenameDialog.entry = entry_
			open()
		}
	}

	Popup {
		id: errorPopup
		property string text
		
		parent: Overlay.overlay
		anchors.centerIn: parent
		width: 1.5 * errorColumn.childrenRect.width
		height: 1.5 * errorColumn.childrenRect.height
		modal: true
		closePolicy: Popup.NoAutoClose
		Column {
			id: errorColumn
			anchors.centerIn: parent
			width: childrenRect.width
			height: errorLabel.height + errorOkButton.height
			Label {
				anchors.horizontalCenter: parent.horizontalCenter
				text: "An error occured!"
				font.bold: true
				font.pointSize: 25
			}
			Label {
				id: errorLabel
				anchors.horizontalCenter: parent.horizontalCenter
				text: errorPopup.text
			}
			Button {
				id: errorOkButton
				anchors.horizontalCenter: parent.horizontalCenter
				width: errorLabel.width
				text: "OK"
				onClicked: errorPopup.close()
			}
		}
		Connections {
			target: Backend
			function onErrorOccured (text) {
				errorPopup.pop(text)
			}
		}
		function pop(text) {
			errorPopup.text = text
			errorPopup.open()
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
				MenuItem {
					text: "Paste"
					enabled: root.moveOrigin !== ''
					onClicked: Backend.paste()
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
					color: {
						if(foldersRepeater.currentIndex === index)
						 	return Material.primaryColor 
						else if(root.moveOrigin == modelData.path)
							return Material.accentColor
						return "transparent"
					}
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
							id: entryContextMenu
							MenuItem {
								text: "Rename"
								onClicked: entryRenameDialog.pop(modelData.name)
							}
							MenuItem {
								text: "Cut"
								onClicked: {
									Backend.move(modelData.name)
									root.moveOrigin = Backend.getMoveOrigin()
								}
							}

							MenuItem {
								text: "Delete " + modelData.name
								onClicked: Backend.delete(modelData.name)
							}
							MenuItem {
								text: "Download"
								enabled: modelData.type === "file"
								onClicked: fileDownloadDialog.openWithName(modelData.name)
							}
						}
						onClicked: function(mouse) {
							foldersRepeater.currentIndex = index
							if(mouse.button === Qt.RightButton)
								entryContextMenu.popup()
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