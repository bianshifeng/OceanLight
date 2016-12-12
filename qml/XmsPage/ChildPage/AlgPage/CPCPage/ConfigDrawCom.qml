import QtQuick 2.4
import QtCanvas3D 1.1
import "../../../../Utils/glcode.js" as GLCode

Canvas3D {
    id: canvas3d
    focus: true

    onInitializeGL: {
        GLCode.initializeGL(canvas3d);
    }

    onPaintGL: {
        GLCode.paintGL(canvas3d);
    }

    onResizeGL: {
        GLCode.resizeGL(canvas3d);
    }
}
