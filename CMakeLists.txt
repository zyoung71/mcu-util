if (NOT TARGET pico-util)

    add_library(pico-util STATIC
        src/util/StringLite.cpp
        src/util/FilesystemTree.cpp
        src/util/TimeHandler.cpp
        src/util/Chars.c
        src/util/SPIDevice.cpp
    )

    target_include_directories(pico-util PUBLIC
        include
        src # for tpp files
    )

    target_link_libraries(pico-util
        hardware_rtc
        hardware_spi
    )

    target_compile_definitions(pico-util PUBLIC
        $<$<CONFIG:Debug>:DEBUG>
    )

endif()