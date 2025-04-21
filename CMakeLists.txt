cmake_minimum_required(VERSION 3.16)

project(QtVoiceoverEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 modules
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    WebEngineWidgets
)

# libsndfile
find_package(PkgConfig REQUIRED)
pkg_check_modules(SNDFILE REQUIRED sndfile)

# Jeśli pkg-config nie działa:
set(SNDFILE_INCLUDE_DIRS "/opt/homebrew/Cellar/libsndfile/1.2.2_1/include")
set(SNDFILE_LIBRARIES "/opt/homebrew/Cellar/libsndfile/1.2.2_1/lib/libsndfile.dylib")



# Źródła
set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    waveformview.cpp
)

set(HEADERS
    mainwindow.h
    waveformview.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Automatyczne generowanie kodu z .ui i .qrc
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

#libsndfile
target_include_directories(${PROJECT_NAME} PRIVATE ${SNDFILE_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${SNDFILE_LIBRARIES})


# Linkowanie bibliotek
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebEngineWidgets
    ${SNDFILE_LIBRARIES}
)
