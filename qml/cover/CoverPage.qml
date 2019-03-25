import Sailfish.Silica 1.0
import QtQuick 2.6
import QtQuick.Layouts 1.0

CoverBackground {
    id: cover

    Label {
        id: label
        anchors.centerIn: parent
        visible: !(page.visible && page.source != "")
        text: qsTr("PDF Viewer")
    }

    Image {
        id: page
        anchors {
            fill: parent
            centerIn: parent
        }
        fillMode: Image.PreserveAspectFit
        visible: (cover.status == Cover.Active) || (cover.status == Cover.Activating)
        source: visible ? pdfHandler.pageRequest(pdfHandler.currentPage) : ""
    }

    CoverActionList {

        CoverAction {
            iconSource: "image://theme/icon-cover-previous"
            onTriggered: { pdfHandler.previousPage(); }
        }
        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: { pdfHandler.nextPage(); }
        }
    }
}
