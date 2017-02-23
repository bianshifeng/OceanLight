import QtQuick 2.7
//messageObject
WorkerScript {
    id: id_root
    property string algId:""
    property string algName:""
    property string algParam:""
    property string algType:""
    property string algIpc:""
    property bool algActiveStatus:false
    property string actionType:"getAlg"
    source: "./WorkerScriptAlgDetail.js"

    onMessage: {
        console.log(messageObject)
    }


    function __requestAlgConfig(url){
        var reponseData;
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
            if(xhr.readyState === xhr.DONE){
                console.log("--------------------------------------")
                if(xhr.responseText.toString()){
                    reponseData = xhr.responseText.toString();
                    id_root.sendMessage(reponseData)
                }
            }
        }

        xhr.open("GET",url);
        xhr.send();

    }

    function getAlgConfig(){
        id_root.actionType = "getAlg"
        var url ="http://127.0.0.1:8080/algconfig?action="+id_root.actionType;

        id_root.__requestAlgConfig(url)
    }
    function setAlgConfig(){
        id_root.actionType = "setAlg"
        var url ="http://127.0.0.1:8080/algconfig?action="+id_root.actionType+"&algConfig="+"bianshifeng";
        id_root.__requestAlgConfig(url)
    }
    function startAlg(){
        id_root.actionType = "startAlg"
        var url ="http://127.0.0.1:8080/algconfig?action="+id_root.actionType;
        id_root.__requestAlgConfig(url)
    }
    function stopAlg(){
        id_root.actionType = "stopAlg"
        var url ="http://127.0.0.1:8080/algconfig?action="+id_root.actionType;
        id_root.__requestAlgConfig(url)
    }


    function initParams(){
     var xx= {
            "algParam":{
                "enSensity":1,  //1,2,3 精确度
                "stDirection":{  //目标走出去的方向
                    "startPoint":[23,23],
                    "endPoint":[15,20]
                },
                "stRoiRect":{ //监测区域
                    "leftTopPoint":[23,23],
                    "rightBottomPoint":[40,20]
                }
            },
            "algType":"cpc",

        }
    }
}
