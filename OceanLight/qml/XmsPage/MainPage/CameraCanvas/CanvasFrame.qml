import QtQuick 2.7
import QtCanvas3D 1.1
import "./jsCamera.js" as GLCode

Canvas3D {
    id: id_root
    focus: true
    onInitializeGL: {
        GLCode.initializeGL(id_root);
    }

    onPaintGL: {
        GLCode.paintGL(id_root);
    }

    onResizeGL: {
        GLCode.resizeGL(id_root);
    }
}
