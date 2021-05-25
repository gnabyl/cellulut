QT += widgets

HEADERS += \
    components/automata_settings_window.h \
    components/cell_widget.h \
    components/control_panel.h \
    components/main_window.h \
    components/menubar.h \
    components/simulator_widget.h \
    constants.h \
    utils/simulator.h \
    utils/automata.h \
    utils/automata_manager.h \
    utils/cell.h \
    utils/cell_state.h \
    utils/grid.h \
    utils/neighborhood_strategy.h \
    utils/transition_strategy.h \

SOURCES += \
    components/cell_widget.cpp \
    components/control_panel.cpp \
    components/main_window.cpp \
    components/menubar.cpp \
    components/simulator_widget.cpp \
    main.cpp \
    utils/simulator.cpp \
    utils/automata.cpp \
    utils/automata_manager.cpp \
    utils/cell.cpp \
    utils/cell_state.cpp \
    utils/grid.cpp \
    utils/neighborhood_strategy.cpp \
    utils/transition_strategy.cpp \

RESOURCES += \
    images_resource.qrc
