import QtQuick 2.3

CheckButtonBase
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
        source: !root_item.enabled ? disableIcon :
                           (isChecked ? pressedIcon : defaultIcon)


    }
}
