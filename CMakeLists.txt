if (NOT TARGET mcu-util)

    add_library(mcu-util STATIC
        src/util/StringLite.cpp
        src/util/FilesystemTree.cpp
        src/util/TimeHandler.cpp
        src/util/Chars.c
        src/util/SPIDevice.cpp
    )

    target_include_directories(mcu-util PUBLIC
        include
        src # for tpp files
    )

    add_subdirectory(lib/mcu-platform)
    
    target_link_libraries(mcu-util
        mcu-platform-interface
    )

endif()