import QtQuick 2.0
import "../publics"

//数据结构 {"name": "xxxxx", "type": var} var类型可变

Rectangle
{
    id: root_item

    width: 300
    height: 40 + isExpended ? list_content_item.height : 0
    property var selectedType: items_model.count > 0 ? null : items_view.currentItem.itype
    property int maxShowItemSize: 10

    property var typeItems
    property bool isExpended: false

    onTypeItemsChanged: {
        items_model.clear()
        items_model.append(typeItems)
    }

    Text
    {
        id: text_item

        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 39
        verticalAlignment: Qt.AlignVCenter
        font.pointSize: 15
        color: "#18b5be"
    }

    ListModel{
        id: items_model
    }

    Rectangle
    {
        id: list_content_item
        MouseArea{
            anchors.fill: parent
        }
        color: "#0d5087"

        visible: root_item.isExpended
        width: parent.width
        height: (items_model.count > root_item.maxShowItemSize) ? root_item.maxShowItemSize * itemHeight : items_model.count * itemHeight + (items_model.count-1)*itemSpacing
        anchors.top: text_item.bottom
        anchors.topMargin: 1
        anchors.horizontalCenter: parent.horizontalCenter
        property int itemHeight: 30
        property int itemSpacing: 5
        ListView
        {
            id: items_view
            anchors.fill: parent

            onCurrentIndexChanged: {
                if (currentIndex >= 0)
                {
                    text_item.text = items_view.currentItem.iname
                }
            }
            model: items_model
            spacing: list_content_item.itemSpacing
            delegate:
                Rectangle
                {
                    id: item_content
                    property var itype: type
                    property string iname: name
                    width: items_view.width
                    height: list_content_item.itemHeight

                    property bool isCurrent: items_view.currentIndex === index
                    color: mouse_area.containsMouse ? "lightgray" : (isCurrent ? "#1ab4be" : "transparent")

                    Text
                    {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 39
                        verticalAlignment: Qt.AlignVCenter
                        font.pointSize: 15
                        color: item_content.isCurrent ? "#ffffff" : "#18b5be"
                        text: parent.iname
                    }

                    MouseArea
                    {
                        id: mouse_area
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            items_view.currentIndex = index
                            root_item.isExpended = false
                        }
                    }
                }
        }
    }



    ImageCheckButtonItem {
        id: image
        width: 17
        height: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 15
        normalIcon: "qrc:/images/deployment_control/scroll_bar_bottom.png"
        pressedIcon: "qrc:/images/deployment_control/scroll_bar_top.png"
    }

    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            root_item.isExpended = !root_item.isExpended
        }
    }
}
