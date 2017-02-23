INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/aidevicebase.h \
    $$PWD/aideviceglobal.h


SOURCES += \
    $$PWD/aidevicebase.cpp


#---------------------add alg cpc-------------------------#
PATH_XMSALG = $$PWD/../../../ThirdProject/XmsAlg

LIBS += -L$$PWD\alg\cpc\lib -Lauth
INCLUDEPATH += $$PATH_XMSALG/cpc/include
HEADERS += \
    $$PATH_XMSALG/cpc/include/imp_algo_type.h \
    $$PATH_XMSALG/cpc/include/imp_cpc_api.h \
    $$PATH_XMSALG/cpc/include/imp_cpc_para.h \


