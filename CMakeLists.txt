set(COMPONENT_SRCDIRS
    "src/components"
)

set(COMPONENT_ADD_INCLUDEDIRS
    "src" "src/components"
)

set(COMPONENT_REQUIRES
    "ArduinoJson"
)

register_component()

target_compile_options(${COMPONENT_TARGET} PRIVATE -fno-rtti)
