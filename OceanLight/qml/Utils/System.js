.pragma library

function func() {

}

// 判断是否是移动平台
function isMobileDevice(){
    return  Qt.platform.os === "android"
            ||Qt.platform.os === "blackberry"
            ||Qt.platform.os === "ios"
            ||Qt.platform.os === "winphone";
}
