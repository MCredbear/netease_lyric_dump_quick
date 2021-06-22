import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ApplicationWindow {
    id: window
    width: 500// @disable-check M16
    height: 700// @disable-check M16
    visible: true// @disable-check M16
    title: qsTr("Netdifficult lyric Dump")// @disable-check M16

    Material.theme: Material.Dark
    //color: Material.background// @disable-check M16

    Popup {
        id: about
        x: (window.width-width)/2
        y: (window.height+height)/8
        width: window.width/2
        height: window.height/2
        Text {
            id: name
            x: about.width*0.05
            y: about.width*0.05
            width: about.width*0.9
            height: about.height*0.9
            text: qsTr("作者：MCredbear\n源码：github.com/MCredbear/netease_lyric_dump_quick")
            elide: Text.ElideNone
            wrapMode: Text.WordWrap
            font.pointSize: 13
        }



    }
    ListView {
        id: listView
        x: window.width/20
        y: window.height/8
        width: window.width/3
        height: window.height*0.85-window.height/8+window.height/20
        spacing: 0
        model: getlist.filelist
        clip: true

        delegate: Button {
            id: eachbutton
            width: ListView.view.width
            height: 40
            //property color darkness: "#303030"
            //Material.accent: darkness
            Text {
            anchors.centerIn: parent
            font.pixelSize: 15
            text: modelData
            font.family: "UKIJ Qolyazma"
        }
            onClicked: {
                 listView.currentItem.highlighted = null
                 listView.currentIndex = index
                    readlyric.setlyric(index)
                 listView.currentItem.highlighted = eachbutton

            }

        }
    }
        Rectangle {
        id: rectangle
        x: window.width/18+listView.x+listView.width
        y: window.height/20
        width: window.width-listView.x-x; height: window.height*0.85;
        color: "#00000000"
        border.color: "#801e1e1e"

        Flickable {
             id: flick
             width: rectangle.width; height: rectangle.height
             contentWidth: edit.paintedWidth
             contentHeight: edit.paintedHeight
             clip: true

             function ensureVisible(r)
             {
                 if (contentX >= r.x)
                     contentX = r.x;
                 else if (contentX+width <= r.x+r.width)
                     contentX = r.x+r.width-width;
                 if (contentY >= r.y)
                     contentY = r.y;
                 else if (contentY+height <= r.y+r.height)
                     contentY = r.y+r.height-height;
             }

             TextEdit {
                 id: edit
                 width: flick.width
                 height: contentHeight
                 focus: true
                 font.family: "UKIJ Qolyazma"
                 font.pixelSize: 16
                 selectByMouse: false
                 text: readlyric.lyric
                 onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                 mouseSelectionMode: TextInput.SelectCharacters
             }
        }
    }

    Switch {
        id: switch1
        x: listView.x
        y: 35
        width: 200
        height: listView.height/15
        //Material.accent: darkness
        text: checked? "Download文件夹" : "Cache文件夹"
        checkable: true
        antialiasing: true
        onReleased: {
            getlist.setfilelist(checked)
        }
    }




      header: ToolBar {
        id: toolbar
        width: window.width

        Label {
            text: "Neteasy lyric Dump"
            anchors.centerIn: parent
        }


        ToolButton {
            id: toolbutton

            text: "\u2630"
            onPressed: {
                if (drawer.closed) {
                    open_drawer.start()
                    drawer.closed=false
                    listView.interactive=false
                    switch1.checkable=false
                }
                else {
                    close_drawer.start()
                    drawer.closed=true
                }

            }
            Connections {
                target: open_drawer
                onStopped: drawer.x=0
            }
            Connections {
                target: close_drawer
                onStopped: {
                    listView.interactive=true
                    switch1.checkable=true
                    drawer.x=-window.width*2
                }
            }
        }
     }
      MouseArea {
          id: close_drawer_area
          x: drawer.closed? -window.width:drawer.x+drawer.width
          y: drawer.y
          width: window.width
          height: window.height
          propagateComposedEvents: false

          onPressed: {
              close_drawer.start()
              drawer.closed=true
          }
      }

      Rectangle {
          id: drawer
          x: -window.width/2.5
          property bool closed: true
          width: window.width/2.5
          height: window.height
          color: Material.toolBarColor
          Column {
                  anchors.fill: parent
                  ItemDelegate {
                      text: "关于"
                      width: parent.width
                      onPressed: {
                          close_drawer.start()
                          drawer.closed=true
                          about.open()
                      }
                  }

          }
    }
    ParallelAnimation {
        id: open_drawer
        NumberAnimation{
                    target: drawer
                    properties: "x"
                    from: -window.width/2.5
                    to: 0
                    duration: 200
                    easing.type: Easing.OutQuad
                }

    }
    ParallelAnimation {
        id: close_drawer
        NumberAnimation{
                    target: drawer
                    properties: "x"
                    from: 0
                    to: -window.width/2.5
                    duration: 200
                    easing.type: Easing.OutQuad
                }

    }
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
