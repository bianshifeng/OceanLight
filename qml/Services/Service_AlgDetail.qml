import QtQuick 2.2
import XmsManagerEnginio_src 1.0
import "../Controls/UIConstants.js" as UI

ServiceBaseDetail{
    id: id_root
    //base info
    property int algType:-1
    property bool algStatus:false
    property string algName:__parserAlgName(algType)
    property string algIcon:__parserAlgIcon(algType)
    property string algIconUrl:__parserAlgIconUrl(algType)
    property string algInfo:__parserAlgInfo(algType)


    function showDetailDialog(){
        id_root.dialog.__showAlgDetailDialog(id_root.itemId,id_root.deviceId)

    }
    function showAlarmDialog(){}

    //for device alg info
    property int deviceId:-1
    property bool isAlgRunning: true
    property int deviceAlgAlarmNum: 10
    property int templateId:-1

    signal emitAlgParameterLoaded(var strData)

    Item{
        id: id_algManager //AlgorithmManager
        property int deviceId: id_root.deviceId
        property int algType: id_root.algType
        property int videoWidth: 100
        property int videoHeight:100

        onGetAlgTemplated: {
            if(errorCode === 0){
                id_root.templateId = nTemplateID
            }else{
                console.log("AlgorithmManager: Get pea alg error "+ errorCode);
            }
        }
        onSetAlgTemplated: {
            if(errorCode === 0){
                id_root.templateId = nTemplateID
            }else{
                console.log("AlgorithmManager: Get pea alg error "+ errorCode);
            }

        }

        onSetPEAParametered: {
//                Signal {
//                    name: "setPEAParametered"
//                    Parameter { name: "nDeviceID"; type: "int" }
//                    Parameter { name: "nWidth"; type: "int" }
//                    Parameter { name: "nHeight"; type: "int" }
//                    Parameter { name: "strParam"; type: "string" }
//                    Parameter { name: "strData"; type: "string" }
//                    Parameter { name: "errorcode"; type: "int" }
//                    Parameter { name: "errorstr"; type: "string" }
//                }
            if(errorCode === 0){
                console.debug("~~~~~ manager save ok pea parameter ")
                console.debug("DeviceId: "+nDeviceID);
                console.debug("strParam: " + strParam);
                console.debug("strData: " + strData);
            }else{
                console.log("AlgorithmManager: Get pea alg error "+ errorCode);
            }

        }
        onGetPEAParametered: {
            console.debug("AlgorithmManager: load data ......")
            if(errorCode==0){
                console.debug("AlgorithmManager: load data ok :" + strData);
                var data =JSON.parse(strData);
                if(data.algParam){
                    id_manager.__initAlgParamData(data.algParam);
                    id_alg_com.mediaSource = id_base.mediaUrl;
                    id_alg_com.mediaDefaultImage = ""
                }




            }else{
                console.log("AlgorithmManager: Get pea alg error "+ errorCode);


            }

        }

        onSetCPCParametered: {

        }
        onGetCPCParametered: {
            emitAlgParameterLoaded(strData)

        }

        function __getAlgParamter(){
            switch(algType){
                case UI.alg_pea_type:
                    id_algManager.getPEAParameter(deviceId,videoWidth,videoHeight);
                    break;
                case UI.alg_cpc_type:
                    id_algManager.getCPCParameter(deviceId)
                    break;
            }
        }

        function __setAlgParamter(data){
            switch(algType){
                case UI.alg_pea_type:
                    id_algManager.setPEAParameter(deviceId,videoWidth,videoHeight,data);
                    break;
                case UI.alg_cpc_type:
                    id_algManager.setCPCParameter(deviceId,data)
                    break;
            }


        }

        function __getAlgTemplate(){
            id_algManager.getAlgTemplate(deviceId,algType)
        }


        function __initAlgParamData(algParam){
            var data ={
                "algParamPerimeters":[
                    {"algParamPerimeter":[{"algPointX":9.955555555555556,"algPointY":8.711111111111112},{"algPointX":5.688888888888889,"algPointY":711.2888888888889},{"algPointX":580.2666666666667,"algPointY":493.6888888888889}]
                    }
                ],
                "algParamTripwires":[
                    {"algParamTripwire":[{"algPointX":581.6888888888889,"algPointY":495.11111111111114},{"algPointX":1271.4666666666667,"algPointY":11.555555555555555}]},
                    {"algParamTripwire":null}
                ],"ratio":10000}
            id_alg_com.algData=algParam;
        }


    }


    function modifyAlgParamter(algData){
        id_deviceManager.getList()

    }
    function showAlarmDialogByDeviceId(){
        id_root.dialog.__showAlarmManagerDialog(id_root.deviceId,id_root.algType)

    }


    function  __parserAlgName(algType){
        var t_algName =""
        switch(algType){
        case UI.alg_pea_type:
            t_algName =UI.alg_pea_name
            break
        case UI.alg_cpc_type:
            t_algName =UI.alg_cpc_name
            break
        case UI.alg_dvc_type:
            t_algName= UI.alg_dvc_name
            break
        default:
            t_algName= UI.alg_unkown_name

        }
        return t_algName
    }
    function  __parserAlgIconUrl(algType){
        var t_algIconUrl =""
        switch(algType){
        case UI.alg_pea_type:
            t_algIconUrl= UI.alg_pea_iconurl
            break
        case UI.alg_cpc_type:
            t_algIconUrl= UI.alg_cpc_iconurl
            break
        case UI.alg_dvc_type:
            t_algIconUrl= UI.alg_dvc_iconurl
            break
        default:
            t_algIconUrl= UI.alg_unkown_iconurl
       }
       return t_algIconUrl

   }
    function  __parserAlgInfo(algType){
       var t_algInfo =""
       switch(algType){
       case UI.alg_pea_type:
           t_algInfo= UI.alg_pea_info
           break
       case UI.alg_cpc_type:
           t_algInfo= UI.alg_cpc_info
           break
       case UI.alg_dvc_type:
           t_algInfo= UI.alg_dvc_info
           break
       default:
           t_algInfo= UI.alg_unkown_info
       }
       return t_algInfo
    }
    function  __parserAlgIcon(algType){
       var t_algIcon = ""
       switch(algType){
       case UI.alg_pea_type:
           t_algIcon= UI.alg_pea_icon
           break
       case UI.alg_cpc_type:
           t_algIcon= UI.alg_cpc_icon
           break
       case UI.alg_dvc_type:
           t_algIcon= UI.alg_dvc_icon
           break
       default:
           t_algIcon= UI.alg_unkown_icon
       }
       return t_algIcon
   }


    onEmitLoadDataed: {
        id_algManager.__getAlgTemplate()
        id_algManager.__getAlgParamter()
    }
}
