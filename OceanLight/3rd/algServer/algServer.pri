INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/ipd_processor

LIBS += -LF:/OceanLightProject/ThirdProject/XmsAlg/lib -lIPD
LIBS += -LF:/OceanLightProject/ThirdProject/XmsAlg/lib -lVFD

#LIBS += -LI:/XMS/OceanLight/ThirdProject/XmsAlg/lib -lIPD
#LIBS += -LI:/XMS/OceanLight/ThirdProject/XmsAlg/lib -lVFD

HEADERS += \
    $$PWD/alg_server.h \
    $$PWD/camera_filter.h \
    $$PWD/common/imp_algo_type.h \
    $$PWD/common/IMP_Frame.h \
    $$PWD/common/IMP_FrameQueue.h \
    $$PWD/common/IMP_Lock.h\
    $$PWD/ipd_processor/ipd_processor.h \
    $$PWD/ipd_processor/imp_ipd_adv_para.h \
    $$PWD/ipd_processor/imp_ipd_api.h \
    $$PWD/ipd_processor/imp_ipd_para.h \
    $$PWD/vfd_processor/imp_vfd_api.h \
    $$PWD/vfd_processor/imp_vfd_para.h \
    $$PWD/vfd_processor/vfd_processor.h \
    $$PWD/vfd_processor/imp_align.h \
    $$PWD/vfd_processor/model_all2_int.h \
    $$PWD/alg_processor/alg_processor.h \
    $$PWD/pfr_processor/pfr_processor.h \
    $$PWD/pfr_processor/IMP_pfr_path.h \
    $$PWD/pfr_processor/IMP_StringQueue.h \
    $$PWD/vfd_processor/imp_align_tab_5.h \
    $$PWD/vfd_processor/imp_faceQA.h


SOURCES += \
    $$PWD/alg_server.cpp \
    $$PWD/camera_filter.cpp \
    $$PWD/common/IMP_FrameQueue.cpp \
    $$PWD/common/IMP_Lock.cpp \
    $$PWD/ipd_processor/ipd_processor.cpp \
    $$PWD/vfd_processor/vfd_processor.cpp \
    $$PWD/alg_processor/alg_processor.cpp \
    $$PWD/pfr_processor/pfr_processor.cpp \
    $$PWD/pfr_processor/IMP_StringQueue.cpp
