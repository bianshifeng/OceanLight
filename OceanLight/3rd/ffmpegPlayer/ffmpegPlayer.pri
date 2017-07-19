

include(./core/ffmpeg_core.pri)

HEADERS += \
    $$PWD/ffmpeg_logger.h \
    $$PWD/ffmpeg_player.h \
    $$PWD/ffmpeg_worker.h

SOURCES += \
    $$PWD/ffmpeg_logger.cpp \
    $$PWD/ffmpeg_player.cpp \
    $$PWD/ffmpeg_worker.cpp

DISTFILES += \
    $$PWD/readme.md



