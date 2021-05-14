QT += widgets

HEADERS += \
    components/cell_widget.h \
    components/control_panel.h \
    components/main_window.h \
    components/menubar.h \
    components/simulator_widget.h \
    utils/*.h

SOURCES += \
    components/cell_widget.cpp \
    components/control_panel.cpp \
    components/main_window.cpp \
    components/menubar.cpp \
    components/simulator_widget.cpp \
    main.cpp \
    utils/*.cpp

RESOURCES += ../assets/
