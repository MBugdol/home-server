import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import "../utils"

Page {
	id: root
	background: Rectangle {color: Material.backgroundColor}
	header: ToolBar {
		Row {
			anchors.fill: parent
			ToolButton {
				text: "Test1"
			}
			ToolButton {
				text: "Test2"
			}
			Switch {

			}
		}
	
	}
	ScrollView {
		id: mainMenuScroll
		anchors.fill: parent
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
				//todo: create a nice model
				// qjsonobject
				// with name and type
				model: Backend.getCurrentChildren()
				GridTile {
					onClicked: {
						if(modelData.type !== "directory") return
						Backend.cd(modelData.name)

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
					foldersRepeater.model = Backend.getCurrentChildren()
				}
			}
		}
	} // mainMenuScroll
}