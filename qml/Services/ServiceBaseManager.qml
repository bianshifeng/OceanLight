import QtQuick 2.2

ServiceBase{
    id: id_serviceManager

    property string beginTime:"0"
    property string endTime:"0"
    property int orderType: 0

    // pageturn params -----start

    property int totalNum:0
    property int totalPages:1
    property int currentPageIndex:1
    property int currentPageNum:((totalNum - beginIndex) < onePageNum) ? (totalNum - beginIndex): onePageNum
    property int onePageNum:100
    property int beginIndex:0

    property bool toPageHead: currentPageIndex === 1 ? false : true
    property bool toPageEnd: currentPageIndex === totalPages ? false : true

    signal emitItemDeleted(int deleteItemId)

    onEmitLoadDataed: __dataLoading()

    onTotalNumChanged: {
        __refreshPageNumInfo()
    }

    onOnePageNumChanged: {
        __refreshPageNumInfo()
    }

    onCurrentPageIndexChanged: {
        __refreshPageNumInfo()

    }

    function __refreshPageNumInfo(){
        // 1. math totalPage
        if(totalNum > 0){
            totalPages = Math.ceil(totalNum/onePageNum)
        }else{
            totalPages = 1
        }
        // 2. protect currentPageIndex in range
        if(currentPageIndex < 1) currentPageIndex =1
        if(currentPageIndex > totalPages)currentPageIndex = totalPages

        // 3. math beginIndex
        beginIndex = (currentPageIndex - 1) * onePageNum


    }

    function deleteItem(nId){
        emitItemDeleted(nId)
    }


    Connections{
        id: id_listRefrsh_cnt
        target: id_appWindow_liveEvent
        onEmitItemManagerRefreshed:{

        }
        ignoreUnknownSignals: true

    }

}
