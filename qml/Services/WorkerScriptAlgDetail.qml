import QtQuick 2.7
//messageObject
WorkerScript {
    id: id_root
    property string algId:""
    property string algName:""
    property string algParams:""
    property string algType:""
    property string algIpc:""
    property bool algActiveStatus:false
    source: "./WorkerScriptAlgDetail.js"
    function requestAlgConfig(){
        var reponseData;
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
            if(xhr.readyState === xhr.DONE){
                console.log("--------------------------------------")
                console.log(xhr.responseText.toString())
                if(xhr.responseText.toString()){
                    reponseData = JSON.parse(xhr.responseText.toString());
                    id_root.sendMessage(reponseData)
                }


            }

        }
        var url ="http://127.0.0.1:8080/algconfig"
        xhr.open("GET",url);
        xhr.send();

    }

    onMessage: {
        console.log(JSON.stringify(messageObject))
        id_root.algId = messageObject.algId
        id_root.algName = messageObject.algName
        id_root.algParams = messageObject.algParams
        id_root.algType = messageObject.algType
        id_root.algIpc = messageObject.algIpc
        id_root.algActiveStatus = messageObject.algActiveStatus

    }

    Component.onCompleted: requestAlgConfig()
}
