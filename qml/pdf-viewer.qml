import QtQuick 2.6
import Sailfish.Silica 1.0

ApplicationWindow {
    initialPage: Qt.resolvedUrl("pages/ViewerPage.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
