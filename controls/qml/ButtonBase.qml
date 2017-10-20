import QtQuick 2.0

Rectangle{
    id: root_item

    property alias mouseArea: mouse_area
    signal clicked()

    property string defaultColor: "#ECECEC"
    property string hoverColor: "#ECECEC"
    property string pressedColor: "#ECECEC"
    property string disabledColor: "#F3F3F3"

    property string defaultBorderColor: "transparent"
    property string hoverBorderColor: "transparent"
    property string pressedBorderColor: "transparent"
    property string disabledBorderColor: "transparent"

    color: !enabled ? disabledColor :
                      (mouseArea.pressed ? pressedColor :
                                            (mouseArea.containsMouse ? hoverColor : defaultColor))

    border.color: !enabled ? disabledBorderColor :
                             (mouseArea.pressed ? pressedBorderColor :
                                                   (mouseArea.containsMouse ? hoverBorderColor : defaultBorderColor))


    MouseArea{
        id: mouse_area
        z: 99999
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {emit: root_item.clicked()}
    }
}
