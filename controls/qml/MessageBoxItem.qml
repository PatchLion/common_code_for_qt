import QtQuick 2.4

Rectangle
{
    id: root_item
    property alias message: text_item.text
    signal confirmClicked()

    MouseArea
    {
        anchors.fill: parent
    }

    color: Qt.rgba(0, 0, 0, 0.1)

    Rectangle{
        id: messagebox
        color: "#11213a"
        height: text_item.height + 60 + buttons_content.height
        radius: 5
        width: 420

        anchors.centerIn: parent


        Text
        {
            id: text_item
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -20
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            font.pointSize: 16
            wrapMode: Text.Wrap
            color: "#1ab4be"
        }

        Item
        {
            id: buttons_content
            width: parent.width
            height: 80
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            TextButtonItem{
                width: 50
                height: 25
                text: "确定"
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: - width/2 - 30
                onClicked: {
                    emit: root_item.confirmClicked()
                }
            }

            TextButtonItem{
                width: 50
                height: 25
                text: "取消"
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: width/2 + 30
                onClicked: {
                    root_item.visible = false
                }
            }
        }
    }
}
