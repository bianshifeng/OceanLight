
.pragma library

var hostPort = "127.0.0.1:8080/algconfig"
var getAlgConfigUrl = hostPort + "/algconfig"


function _requestAlgConfig(){
    var reponseData;
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function(){
        if(xhr.readyState === xhr.DONE){
            console.log("--------------------------------------")
            console.log(xhr.responseText.toString())
            reponseData = JSON.parse(xhr.responseText.toString());
            WorkerScript.sendMessage(reponseData);
        }

    }
    var url ="http://127.0.0.1:8080/algconfig"
    xhr.open("GET",url);
    xhr.send();

}


WorkerScript.onMessage = function(message){
    WorkerScript.sendMessage(message);
}



