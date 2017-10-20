//Toast窗体显示
var com = 0
function showToast(parent, text) {
    com = Qt.createComponent("Toast.qml")
    if(com.status === Component.Ready)
    {
        var toast = com.createObject(parent, {"anchors.horizontalCenter":parent.horizontalCenter, "anchors.bottomMargin": parent.height/5, "anchors.bottom": parent.bottom, "text": text})
    }
    else
    {
        console.log("创建Toast失败")
    }
}
