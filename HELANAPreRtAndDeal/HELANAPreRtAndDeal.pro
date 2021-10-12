QT += core sql
QT -= gui

CONFIG += c++11

TARGET = HELANAPreRtAndDeal
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    AlarmLog.cpp \
    AlarmSetDeal.cpp \
    BasicMgr.cpp \
    buff_points.cpp \
    Count_service.cpp \
    LoadConfg.cpp \
    PointPreCal.cpp \
    PPubPointValue.cpp \
    PreRtProduce.cpp \
    pub_index_data.cpp \
    RDbOperationComplex.cpp \
    RDbOperationSimple.cpp \
    RecursiveCalculateIndex.cpp \
    RsdbAdapter.cpp \
    ServiceEIDSPreConfig.cpp \
    StartupServer.cpp \
    TbDfhCfg.cpp \
    TbPubModeMethodAvg.cpp \
    TbPubSetToPoint.cpp \
    Util.cpp \
    ../funlib/AlgoFunc.cpp \
    ../funlib/GmmEmFunc.cpp \
    ../funlib/Kmeanfun.cpp \
    ../funlib/Matrix.cpp \
    ../funlib/PublicMatrix.cpp \
    ../funlib/SimFunc.cpp

DISTFILES += \
    HELANAPreRtAndDeal.pro.user \
    eids_service_preValue_config.cfg

HEADERS += \
    AlarmLog.h \
    AlarmSetDeal.h \
    AlarmSetInfo.h \
    BasicMgr.h \
    buff_points.h \
    Count_service.h \
    DataValueInfo.h \
    ErrorDef.h \
    IndexConfigInfo.h \
    LoadConfg.h \
    ModeMethodAvgConfig.h \
    PointPreCal.h \
    PPubPointValue.h \
    PreRtProduce.h \
    pub_index_data.h \
    RDbHead.h \
    RDbOperationComplex.h \
    RDbOperationSimple.h \
    RecursiveCalculateIndex.h \
    RsdbAdapter.h \
    ServiceEIDSPreConfig.h \
    StartupServer.h \
    TbDfhCfg.h \
    TbPubModeMethodAvg.h \
    TbPubSetToPoint.h \
    TypeDef.h \
    Util.h \
    ../funlib/AlgoFunc.h \
    ../funlib/AlgoVarDef.h \
    ../funlib/FunPublic.h \
    ../funlib/GmmEmFunc.h \
    ../funlib/Kmeanfun.h \
    ../funlib/Matrix.h \
    ../funlib/PublicMatrix.h \
    ../funlib/SimFunc.h


LIBS += -ldl -lpthread


unix:!macx: LIBS += -L/usr/local/boost_1_71_0/lib -lboost_thread -lboost_filesystem

unix:!macx: LIBS += -L$$PWD/../compiler/lib -lcompiler

INCLUDEPATH += $$PWD/../compiler/inc
DEPENDPATH += $$PWD/../compiler/inc

unix:!macx: LIBS += -L$$PWD/../common/lib -lcommon

INCLUDEPATH += $$PWD/../common/inc
DEPENDPATH += $$PWD/../common/inc

unix:!macx: LIBS += -L$$PWD/../data_parser/lib -ldataparser

INCLUDEPATH += $$PWD/../data_parser/inc
DEPENDPATH += $$PWD/../data_parser/inc

unix:!macx: LIBS += -L$$PWD/../waspcn/lib/ -lwaspcn

INCLUDEPATH += $$PWD/../waspcn/inc
DEPENDPATH += $$PWD/../waspcn/inc


