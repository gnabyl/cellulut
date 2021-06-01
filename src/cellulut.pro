QT += widgets \
    sql \

HEADERS += \
    components/automata_settings_windows.h \
    components/bslider.h \
    components/cell_widget.h \
    components/control_panel.h \
    components/main_window.h \
    components/menubar.h \
    components/simulator_widget.h \
    components/subwindows/automatas_browser.h \
    components/subwindows/neighbors_browser.h \
    components/subwindows/transitions_browser.h \
    constants.h \
    utils/database.h \
    utils/grid_factory.h \
    utils/simulator.h \
    utils/automata.h \
    utils/automata_manager.h \
    utils/cell.h \
    utils/cell_state.h \
    utils/grid.h \
    utils/neighborhood_strategy.h \
    utils/transition_strategy.h \

SOURCES += \
    components/automata_settings_windows.cpp \
    components/bslider.cpp \
    components/cell_widget.cpp \
    components/control_panel.cpp \
    components/main_window.cpp \
    components/menubar.cpp \
    components/simulator_widget.cpp \
    components/subwindows/automatas_browser.cpp \
    components/subwindows/neighbors_browser.cpp \
    components/subwindows/transitions_browser.cpp \
    main.cpp \
    utils/database.cpp \
    utils/grid_factory.cpp \
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
