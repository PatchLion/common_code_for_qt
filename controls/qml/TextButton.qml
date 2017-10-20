import QtQuick 2.0
import "../datas/AppConfigs.js" as Configs

ButtonBase{
    property alias text: text_item.text

    property string textDefaultColor: "#ffffff"
    property string textPressedColor: "#ffffff"
    property string textHoverColor: "#ffffff"
    property string textDisabledColor: "#ffffff"

    property alias textFontFamliy: text_item.font.family
    property alias textPointSize: text_item.font.pointSize


    Text
    {
        id: text_item
        anchors.centerIn: parent
        font.family: Configs.DefaultFontFamily
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
        color: !enabled ? textDisabledColor :
                          (mouseArea.pressed ? textPressedColor :
                                                (mouseArea.containsMouse ? textHoverColor : textDefaultColor))

        font.pointSize: 12
    }
}
