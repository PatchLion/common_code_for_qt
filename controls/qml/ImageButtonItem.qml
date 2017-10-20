import QtQuick 2.3

ButtonBase
{
    id: root_item

    property string defaultIcon: ""
    property string pressedIcon: ""
    property string hoverIcon: ""
    property string disableIcon: ""

    Image
    {
        z: 0
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: !enabled ? disableIcon :
                           (root_item.mouseArea.pressed ? pressedIcon :
                                                 (root_item.mouseArea.containsMouse ? hoverIcon : defaultIcon))

    }
}
