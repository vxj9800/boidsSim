import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import myPackages.boids 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("BoidsSim")

    Rectangle{
        id: mainWindow
        height: parent.height
        width: parent.width
        color: "black"

        Rectangle{
            id: sideBar
            anchors.right: mainWindow.right
            anchors.rightMargin: mainWindow.width/100
            anchors.top: mainWindow.top
            anchors.topMargin: mainWindow.height/100
            anchors.bottom: mainWindow.bottom
            anchors.bottomMargin: mainWindow.height/100
            width: mainWindow.width/5
            radius: Math.max(mainWindow.width/100,mainWindow.width/100)
            color: "gray"
            z: 1
            OpacityAnimator{
                target: sideBar
                to: 0.5
                duration: 5000
                running: hoverCheck.containsMouse | cfactor.hovered | afactor.hovered | sfactor.hovered | rstBtn.hovered
            }
            OpacityAnimator{
                target: sideBar
                to: 0.1
                duration: 5000
                running: !(hoverCheck.containsMouse)
            }
            MouseArea{
                id: hoverCheck
                anchors.fill: parent
                hoverEnabled: true
            }

            MySlider{
                id: cfactor
                anchors.top: parent.top
                from: 0.001
                to: 0.02
                value: 0.005
                hoverEnabled: true
                text: "Coherance Factor"
            }

            MySlider{
                id: afactor
                anchors.top: cfactor.bottom
                from: 1
                to: 10
                value: 2
                hoverEnabled: true
                text: "Alignment Factor"
            }

            MySlider{
                id: sfactor
                anchors.top: afactor.bottom
                from: 0.0005
                to: 0.01
                value: 0.005
                hoverEnabled: true
                text: "Separation Factor"
            }

            Button{
                id: rstBtn
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: sfactor.bottom
                text: qsTr("Reset")
                onPressed: birds.initBoids()
                hoverEnabled: true
            }
        }

        Boids{
            id: birds
            nBoids: 100
            cFactor: cfactor.value
            aFactor: afactor.value
            sFactor: sfactor.value
            onRotChanged: drawBoids.requestPaint()
        }

        Canvas{
            id: drawBoids
            height: mainWindow.height
            width: mainWindow.width
            renderStrategy: Canvas.Threaded
            onPaint: {
                var c = getContext("2d")
                c.clearRect(0,0,width,height);
                c.fillStyle = Qt.rgba(1,0,0,0);
                c.fillRect(0, 0, width, height);
                for (var i = 0; i < birds.nBoids; ++i){
                    c.fillStyle = Qt.rgba(1,0,0,1);
                    c.translate(birds.xPos[i]*width, birds.yPos[i]*height);
                    c.rotate(birds.rot[i]);
                    c.translate(-birds.xPos[i]*width, -birds.yPos[i]*height);
                    c.beginPath();
                    c.moveTo(birds.xPos[i]*width, birds.yPos[i]*height);
                    c.lineTo(birds.xPos[i]*width - 15, birds.yPos[i]*height + 5);
                    c.lineTo(birds.xPos[i]*width - 15, birds.yPos[i]*height - 5);
                    c.lineTo(birds.xPos[i]*width, birds.yPos[i]*height);
                    c.fill();
                    c.setTransform(1, 0, 0, 1, 0, 0);
                }
            }
        }
    }
}
