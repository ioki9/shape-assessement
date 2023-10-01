
set(PROJECT_SOURCES
        main.cpp
        ${PROJECT_SOURCE_DIR}/icons/icons.qrc
        mainwindow.h mainwindow.cpp

        shapes/ishape.h shapes/ishape.cpp
        shapecanvas.h shapecanvas.cpp
        shapes/srectangle.h shapes/srectangle.cpp
        shapes/sline.h shapes/sline.cpp
        shapes/striangle.h shapes/striangle.cpp
        shapes/sellipse.h shapes/sellipse.cpp
        shapes/ishapevisitor.h
        shapes/shapetypededucer.h shapes/shapetypededucer.cpp
        connectionmanager.cpp connectionmanager.h
        settings.cpp settings.h
        shapes/Shapes.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(shape-assessment
        ${PROJECT_SOURCES}
    )
endif()
target_link_libraries(shape-assessment PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(shape-assessment PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS shape-assessment
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

