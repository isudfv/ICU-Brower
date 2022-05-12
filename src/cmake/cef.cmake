# Determine the platform.
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MAC 1)
    set(OS_MACOSX 1)  # For backwards compatibility.
    set(OS_POSIX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    set(OS_POSIX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
endif ()

# Define some macros

# Copy a list of files from one directory to another. Relative files paths are maintained.
# The path component of the source |file_list| will be removed.
macro(COPY_FILES target file_list source_dir target_dir)
    foreach (FILENAME ${file_list})
        set(source_file ${source_dir}/${FILENAME})
        get_filename_component(target_name ${FILENAME} NAME)
        set(target_file ${target_dir}/${target_name})

        if (IS_DIRECTORY ${source_file})
            add_custom_command(
                    TARGET ${target}
                    PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_file}" "${target_file}"
                    VERBATIM
            )
        else ()
            add_custom_command(
                    TARGET ${target}
                    PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source_file}" "${target_file}"
                    VERBATIM
            )
        endif ()
    endforeach ()
endmacro()

if (OS_WINDOWS)
    # Add custom manifest files to an executable target.
    macro(ADD_WINDOWS_MANIFEST manifest_path target extension)
        add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND "mt.exe" -nologo
                -manifest \"${manifest_path}/app.${extension}.manifest\" \"${manifest_path}/compatibility.manifest\"
                -outputresource:"${CMAKE_CURRENT_BINARY_DIR}/${target}.${extension}"\;\#1
                COMMENT "Adding manifest..."
        )
    endmacro()
endif (OS_WINDOWS)


# CEF directory paths.
set(CEF_RESOURCE_DIR "${CMAKE_SOURCE_DIR}/Resources")
set(CEF_BINARY_DIR "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")

# List of CEF resource files.
set(CEF_RESOURCE_FILES
        ABPFilterParserData.dat
        chrome_100_percent.pak
        chrome_200_percent.pak
        resources.pak
        icudtl.dat
        locales
        )

if (OS_LINUX)
    # Standard libraries.
    set(CEF_LIBS
            libcef.so
            libcef_dll_wrapper.a)

    set(CEF_STANDARD_LIBS
            X11
            )

    # List of CEF binary files.
    set(CEF_BINARY_FILES
            libcef_dll_wrapper.a
            chrome-sandbox
            libcef.so
            libEGL.so
            libGLESv2.so
            libvk_swiftshader.so
            libvulkan.so.1
            snapshot_blob.bin
            v8_context_snapshot.bin
            vk_swiftshader_icd.json
            swiftshader
            )
endif ()

if (OS_WINDOWS)
    # Standard libraries.
    set(CEF_LIBS
            libcef.lib
            libcef_dll_wrapper.lib)

    set(CEF_STANDARD_LIBS
            comctl32.lib
            gdi32.lib
            rpcrt4.lib
            shlwapi.lib
            ws2_32.lib
            )

    # List of CEF binary files.
    set(CEF_BINARY_FILES
            chrome_elf.dll
            d3dcompiler_47.dll
            libcef.lib
            libcef_dll_wrapper.lib
            libcef.dll
            libEGL.dll
            libGLESv2.dll
            snapshot_blob.bin
            v8_context_snapshot.bin
            vk_swiftshader.dll
            vk_swiftshader_icd.json
            vulkan-1.dll
            swiftshader
            )
endif ()