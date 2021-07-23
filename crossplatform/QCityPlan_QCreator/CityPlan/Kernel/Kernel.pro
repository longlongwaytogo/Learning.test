TEMPLATE = subdirs

SUBDIRS += \
    KernelCommonUse
    CONFIG(debug, debug|release){
        DESTDIR =$$PWD/../../build/bin/debug
    }else{
        DESTDIR = build/release
    }
