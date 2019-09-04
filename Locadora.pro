#-------------------------------------------------
#
# Project created by QtCreator 2019-06-06T07:37:10
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Locadora
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    cliente.cpp \
    locacao.cpp \
    veiculo.cpp \
    marca.cpp \
    modelo.cpp \
    telefone.cpp \
    clientepersistencia.cpp \
    telagerenciarclientes.cpp \
    telacadastrarcliente.cpp \
    telaalterarcliente.cpp \
    telagerenciarveiculo.cpp \
    id.cpp \
    veiculopersistencia.cpp \
    marcapersistencia.cpp \
    modelopersistencia.cpp \
    telacadastrarveiculo.cpp \
    telaAlterarVeiculo.cpp \
    telacadastrarmarca.cpp \
    telagerenciarmarca.cpp \
    telaalterarmarca.cpp \
    telagerenciarmodelo.cpp \
    telacadastrarmodelo.cpp \
    telaalterarmodelo.cpp \
    data.cpp \
    locacaoPersistencia.cpp \
    telaLocacao.cpp \
    telaDevolucao.cpp \
    TelaHistoricooLocacoes.cpp

HEADERS += \
        mainwindow.h \
    cliente.h \
    locacao.h \
    veiculo.h \
    marca.h \
    modelo.h \
    itransformardados.h \
    telefone.h \
    clientepersistencia.h \
    crudgeral.h \
    telagerenciarclientes.h \
    telacadastrarcliente.h \
    telaalterarcliente.h \
    telagerenciarveiculo.h \
    id.h \
    veiculopersistencia.h \
    marcapersistencia.h \
    modelopersistencia.h \
    telacadastrarveiculo.h \
    telaAlterarVeiculo.h \
    telacadastrarmarca.h \
    telagerenciarmarca.h \
    telaalterarmarca.h \
    telagerenciarmodelo.h \
    telacadastrarmodelo.h \
    telaalterarmodelo.h \
    data.h \
    locacaoPersistencia.h \
    telaLocacao.h \
    tiporelacionamento.h \
    telaDevolucao.h \
    TelaHistoricooLocacoes.h

FORMS += \
        mainwindow.ui \
    telagerenciarclientes.ui \
    telacadastrarcliente.ui \
    telaalterarcliente.ui \
    telagerenciarveiculo.ui \
    telacadastrarveiculo.ui \
    telaAlterarVeiculo.ui \
    telacadastrarmarca.ui \
    telagerenciarmarca.ui \
    telaalterarmarca.ui \
    telagerenciarmodelo.ui \
    telacadastrarmodelo.ui \
    telaalterarmodelo.ui \
    telaLocacao.ui \
    telaDevolucao.ui \
    TelaHistoricooLocacoes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
