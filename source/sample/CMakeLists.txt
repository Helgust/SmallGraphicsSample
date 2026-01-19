project(GraphicsSample)

add_executable(GraphicsSample
    graphics/command_buffer.cpp
    graphics/command_buffer.hpp
    graphics/gpu_device.cpp
    graphics/gpu_device.hpp
    graphics/gpu_enum.hpp
    graphics/gpu_profiler.cpp
    graphics/gpu_profiler.hpp
    graphics/gpu_resources.cpp
    graphics/gpu_resources.hpp
    graphics/renderer.cpp
    graphics/renderer.hpp

    graphics/raptor_imgui.cpp
    graphics/raptor_imgui.hpp

    main.cpp
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(TARGET GraphicsSample PROPERTY CXX_STANDARD 17)

if (WIN32)
    target_compile_definitions(GraphicsSample PRIVATE
        _CRT_SECURE_NO_WARNINGS
        WIN32_LEAN_AND_MEAN
        NOMINMAX)
endif()

target_compile_definitions(GraphicsSample PRIVATE
    TRACY_ENABLE
    TRACY_ON_DEMAND
    TRACY_NO_SYSTEM_TRACING
)

target_include_directories(GraphicsSample PRIVATE
    .
    ..
    ../raptor
    ${Vulkan_INCLUDE_DIRS}
)

if (WIN32)
    target_include_directories(GraphicsSample PRIVATE
        ../../binaries/SDL2-2.0.18/include)

    target_link_directories(GraphicsSample PRIVATE
        ../../binaries/SDL2-2.0.18/lib/x64
    )
else()
    target_include_directories(GraphicsSample PRIVATE
        ${SDL2_INCLUDE_DIRS})

endif()

target_link_libraries(GraphicsSample PRIVATE
    RaptorFoundation
    RaptorExternal
    RaptorApp
    ${Vulkan_LIBRARIES}
)

if (WIN32)
    target_link_libraries(GraphicsSample PRIVATE
        SDL2)
else()
    target_link_libraries(GraphicsSample PRIVATE
        dl
        pthread
        SDL2::SDL2)
endif()

if (WIN32)
    set(DLLS_TO_COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/../../binaries/SDL2-2.0.18/lib/x64/SDL2.dll
    )

    foreach(DLL ${DLLS_TO_COPY})
        add_custom_command(TARGET GraphicsSample POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL}
                $<TARGET_FILE_DIR:GraphicsSample>
            COMMENT "Copying SDL2.dll to output directory"
            VERBATIM
            )
    endforeach()
endif()
