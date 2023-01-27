# Find all cpp files
file(GLOB_RECURSE coreqml_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

# Find all qml files
# NOTE: GLOB_RECURSE should be avoided!
file(GLOB_RECURSE coreqml_SRC_QML CONFIGURE_DEPENDS "*.qml" "*.js")

# Find all resources files
file(GLOB_RECURSE coreqml_SRC_QRC CONFIGURE_DEPENDS "*.qrc")

# Group qml sources in IDE
source_group("QML" FILES ${coreqml_SRC_QML})

qt_add_resources(coreqml_RESOURCES ${coreqml_SRC_QRC})

add_library(coreqml SHARED
    ${coreqml_SRC}
    ${coreqml_SRC_QML}
    ${coreqml_RESOURCES}
)

target_link_libraries(coreqml Qt6::Core Qt6::Quick Qt6::Gui Qt6::Qml)
