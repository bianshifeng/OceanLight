import QtQuick 2.2
import XmsManagerEnginio_src 1.0
import "../Dialog"
import "../Components/Constants/UIConstants.js" as UI

Service_DeviceDetail{
    id: id_root
    property int monitorId: -1
    property int algType:-1

    onEmitSelectedDeviceOK: {
        id_service.itemId = data.itemId
        id_service.loadData()
    }

    function reset(){
        id_root.algListModel.clear()
        id_root.itemId = -1
        id_root.recordStatus = -1
        id_root.deviceUrl = ""
    }


    function getAlgsRunStatus(){
    }

    function startRecording(){
        id_root.recordStatus = true

    }
    function stopRecording(){
        id_root.recordStatus = false
    }



    //Dialogs

    function showMonitorDetailDialog(){
        id_root.showDetailDialog()
    }
    function showMonitorAlgManagerDialog(){
        id_root.dialog.__showDeviceAlgManagerDialog(id_root.itemId)
    }
    function showMonitorFullScreenDialog(){
        id_root.dialog.__showCommonPlayerDialog(id_root.deviceUrl)
    }

    function showMonitorAlarmsDialog(){
        id_root.dialog.__showAlarmManagerDialog(id_root.deviceId,id_root.algType)
        if(id_root.algType === -1){
            console.log("show all alarm Type")
        }
        if(id_root.algType === 1){
            console.log("show alg alarm")
        }
        if(id_root.algType === 0){
            console.log("show device alarm")
        }
    }
    function showMonitorReviewDialog(){
        id_root.dialog.__showRecordManagerDialog(id_root.itemId)
    }

    function showMonitorSettingDialog(){}
    function showSnapImageDialog(imgPath){
        id_root.dialog.__showCommonSnapDialog(imgPath)

    }


    Connections{
        id: id_liveEvent_monitor_cnt
        target: id_appWindow_liveEvent
        onEmitDeviceLiveingStatusChanged:{
            console.log("id_appWindow_liveEvent: the emitDeviceLiveingStatusChanged signal ------ get")
            //(int deviceId, bool status)
        }
        ignoreUnknownSignals: true
    }


}
