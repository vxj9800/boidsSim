import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    property alias text: textbox.text
    property alias from: slider.from
    property alias to: slider.to
    property alias value: slider.value
    property alias hoverEnabled: slider.hoverEnabled
    property alias hovered: slider.hovered

    width: parent.width
    height: 50
    Column{
        anchors.fill: parent
        Text{
            id: textbox
            text: qsTr(text)
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
        }
        Slider{
            id: slider
            from: from
            to: to
            value: value
            width: parent.width
            hoverEnabled: hoverEnabled
        }
    }
}
