import QtQuick 2.3
Rectangle{
    id: root_item
    property var buttons: []

    color: "transparent"

    Component{
        id: component
        Connections{
            id: conn
            onIsCheckedChanged:{
                if (conn.target.isChecked)
                {
                    for (var i = 0; i < buttons.length; i++)
                    {
                        if (conn.target !== buttons[i])
                        {
                            buttons[i].isChecked = false
                        }
                    }
                }

            }
        }
    }

    onButtonsChanged: {
        //console.log(buttons.size, buttons.count, buttons.length)
        for (var i = 0; i < buttons.length; i++)
        {
            buttons[i].canUncheckByManual = false
            buttons[i].isChecked = (0===i)
            component.createObject(root_item, {"target": buttons[i]})
        }
    }

}
