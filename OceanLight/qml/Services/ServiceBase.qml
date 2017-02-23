import QtQuick 2.2
import "../Dialog"

Item{
    id: id_root
    property int authorId: backendContext.userId
    property int loginId:backendContext.userId
    property string serverIp:backendContext.serverIP
    property int serverPort: backendContext.serverPort

    property ListModel listModel: ListModel{}  //for list
    property int itemId: -1             //for item

    property alias dialog: id_dialog
    property alias dlgLoader:id_dialog.dialogLoader
    property Item infoLoader:null



    signal emitMessageBoxOK(int messageId)
    signal emitMessageBoxCancel(int messageId)


    signal emitItemLoading(int loadStatus)
    signal emitLoadDataed
    function loadData(){
        //Load data step1 : emit loading data status
        __dataLoading()
        emitLoadDataed()
    }
    function refreshData(){
        loadData()
    }

    // pageturn params -----end

    function __dataLoading(){
        emitItemLoading(0)
    }
    function __dataLoadSuccess(){
        emitItemLoading(1)
    }
    function __dataLoadFailture(){
        emitItemLoading(-1)
    }

    DialogsObject{
        id: id_dialog
    }


    signal emitSelectedAlgOK(var data)
    signal emitSelectedTemplateOK(var data)
    signal emitSelectedDeviceOK(var data)
    //----------------deviceSelectDialog------------
    Connections{
        id: id_cnt_deviceSelect
        target: null
        onEmitSelectedOK:{
            var t_algType;
            // add alg to algListModel

            console.log("showCommonDialog_SelectDevice is selected " + selectedItemId)
            var t_data ={}
            t_data.itemId = selectedItemId
            t_data.itemList = selectedItemList
            emitSelectedDeviceOK(t_data)
            id_cnt_deviceSelect.target = null
        }
        onEmitSelectedCancel:{
            id_cnt_deviceSelect.target = null
            console.log("showCommonDialog_SelectDevice is cancel")
        }
        ignoreUnknownSignals: true

    }

    function _showCommonDialog_SelectDevice(deviceId,deviceList){
        id_dialog.__showCommonSelectDeviceDialog(id_dialog.loginId,deviceId,deviceList)
        id_cnt_deviceSelect.target = id_root.dlgLoader.item
    }
    //------------------------------------------------------

    //----------------algSelectDialog---------------------
    Connections{
        id: id_cnt_algSelectDialog
        target: null
        onEmitSelectedOK:{
            var t_algType;
            // add alg to algListModel
            id_cnt_algSelectDialog.target = null
            var t_data ={}
            t_data.itemId = selectedItemId
            t_data.itemList = selectedItemList
            emitSelectedAlgOK(t_data)
            console.log("showCommonDialog_SelectAlg is selected: selectedItemId " + selectedItemId   + "selectedItemList " + selectedItemList )
        }
        onEmitSelectedCancel:{
            id_cnt_algSelectDialog.target = null
            console.log("showCommonDialog_SelectAlg is cancel")
        }
        ignoreUnknownSignals: true
    }

    function _showCommonDialog_SelectAlg(algId,algList){
        id_dialog.__showCommonSelectAlgDialog(id_dialog.loginId,algId,algList)
        id_cnt_algSelectDialog.target = id_root.dlgLoader.item
    }


    //------------------------------------------------------

    //----------------templateSelectDialog------------
    Connections{
        id: id_cnt_templateSelect
        target: null
        onEmitSelectedOK:{
            var t_algType;
            // add alg to algListModel
            id_cnt_templateSelect.target = null
            console.log("showCommonDialog_SelectTemplate is selected")
            var t_data ={}
            t_data.itemId = selectedItemId
            t_data.itemList = selectedItemList
            emitSelectedTemplateOK(t_data)
        }
        onEmitSelectedCancel:{
            id_cnt_templateSelect.target = null
        }
        ignoreUnknownSignals: true

    }

    function _showCommonDialog_SelectTemplate(tempalteId,tempalteList){
        id_dialog.__showCommonSelectTemplateDialog(id_dialog.loginId,tempalteId,tempalteList)
        id_cnt_templateSelect.target = id_root.dlgLoader.item
    }
    //------------------------------------------------------



    //----------------MessageBoxDialog------------
    Connections{
        id: id_messgeBox_cnt
        target:null
        onEmitMessageBoxOK:{
            console.debug(" the message box is ok")
            emitMessageBoxOK(messageId)
            id_messgeBox_cnt.target = null
        }
        onEmitMessageBoxCancel:{
            console.debug("the message box is cancel")
            emitMessageBoxCancel(messageId)
            id_messgeBox_cnt.target = null
        }
    }

    function showMessageBoxDialog(t_id,t_title,t_msg){
        id_root.dialog.__showCommonMessageDialog(t_id,t_title,t_msg)
        id_messgeBox_cnt.target = id_root.dlgLoader.item
    }
    //------------------------------------------------------

}
