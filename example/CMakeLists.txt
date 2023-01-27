# Find all cpp files
file(GLOB coreqml_ex_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

# Find all qml files
# NOTE: GLOB_RECURSE should be avoided!
file(GLOB_RECURSE coreqml_ex_SRC_QML CONFIGURE_DEPENDS "*.qml")

# Find all resources files
file(GLOB_RECURSE coreqml_ex_SRC_QRC CONFIGURE_DEPENDS "*.qrc")

# Group qml sources in IDE
source_group("QML" FILES ${coreqml_ex_SRC_QML})

qt_add_resources(RESOURCES ${coreqml_ex_SRC_QRC})

qt_add_executable(example
    ${coreqml_ex_SRC}
    ${coreqml_ex_SRC_QML}
    ${RESOURCES}
)

target_link_libraries(example PRIVATE coreqml)
