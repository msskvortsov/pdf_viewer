import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentWidth: page.width
        contentHeight: page.height

        Image {
            id: pdfAsImage
            anchors {
                fill: parent
                centerIn: parent
            }
            fillMode: Image.PreserveAspectFit
            source: pdfHandler.pageRequest(pdfHandler.currentPage)

            Slider {
                id: pageSlider
                visible: !pdfHandler.empty && (pdfHandler.pageCount > 1)
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                value: 1
                minimumValue: 1
                maximumValue: visible ? pdfHandler.pageCount : 2
                stepSize: 1
                valueText: qsTr("Page %1/%2").arg(value).arg(maximumValue)
                onValueChanged: { pdfHandler.currentPage = value - 1; }

                // This connection is necessary because there user can change page number
                // not only using this control. Also it can be changed by CoverActions.
                // So it is necessary to synchronise pdfHandler.currentPage and pageSlider.value
                Connections {
                    target: pdfHandler
                    onCurrentPageChanged: {
                        if (pageSlider.value - 1 !== pdfHandler.currentPage)
                            pageSlider.value = pdfHandler.currentPage + 1;
                    }
                }
            }
        }

        PushUpMenu {
            quickSelect: true

            MenuItem {
                text: qsTr("Open document")
                onClicked: {
                    var filePickerPage = pageStack.push("Sailfish.Pickers.FilePickerPage", { nameFilters: [ '*.pdf' ] });
                    filePickerPage.selectedContentPropertiesChanged.connect(function() {
                        pdfHandler.source = filePickerPage.selectedContentProperties.url;
                    });
                }
            }
        }
    }
}
