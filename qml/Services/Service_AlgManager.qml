import QtQuick 2.2
import XmsManagerEnginio_src 1.0
import "../Models"
ServiceBaseManager {
    id: id_root
    listModel: id_listModel
    Model_AlgList{
        id: id_listModel
        onEmitDataChanged: id_root.__dataLoadSuccess()
    }

    Component.onCompleted: {
        var t_alg ={};
        var algList =[];

        for(var i= 1; i< 12; i++){
            t_alg = {deviceAlgType:i,deviceAlgStatus:1};
            algList.push(t_alg);
        }
        id_listModel.__showData(algList,id_listModel.paserItemFun)
    }

}

