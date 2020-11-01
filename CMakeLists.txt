cmake_minimum_required(VERSION 3.18)
project(MayaPluginAdapter)

function(download_file url archive_dir hash_type hash)

    if(NOT EXISTS ${archive_dir})
        message(STATUS "Downloading")
        file(DOWNLOAD ${url} ${archive_dir}
           EXPECTED_HASH ${hash_type}=${hash}
           TLS_VERIFY ON
           SHOW_PROGRESS
        )
        message(STATUS "Download complete")
    else()
        message(STATUS "File found, will not be downloaded")
    endif()

endfunction(download_file)

function(extract_file archive_dir dest_dir)

    if(NOT EXISTS ${dest_dir})
        message(STATUS "Extracting")
        file(ARCHIVE_EXTRACT INPUT ${archive_dir} DESTINATION ${dest_dir})
        message(STATUS "Extraction complete")
    else()
        message(STATUS "Destination exists, will not extract")
    endif()

endfunction(extract_file)

function(extract_file_dmg archive_dir archive_name dest_dir)

    if(NOT EXISTS ${dest_dir})
        message(STATUS "Opening dmg")
        execute_process(
            COMMAND hdiutil attach "${archive_dir}"
            COMMAND_ECHO STDOUT
        )
        execute_process(
            COMMAND mkdir -p "${dest_dir}/${archive_name}"
            COMMAND_ECHO STDOUT
        )
        execute_process(
            COMMAND cp -rf "/Volumes/${archive_name}" "${dest_dir}"
            COMMAND_ECHO STDOUT
        )
        execute_process(
            COMMAND hdiutil detach  "/Volumes/${archive_name}"
            COMMAND_ECHO STDOUT
        )
        message(STATUS "Extraction complete")
    else()
        message(STATUS "Destination exists, will not extract")
    endif()

endfunction(extract_file_dmg)

set(MAYA_DEVKIT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Maya2020.3_Devkit")

if (WIN32)
    set(MAYA_DEVKIT_ROOT "${MAYA_DEVKIT_ROOT}/win")
    set(MAYA_DEVKIT_LOCATION "${MAYA_DEVKIT_ROOT}/devkit/devkitBase")
    download_file(
        https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2020/Autodesk_Maya_2020_3_Update_DEVKIT_Windows.zip
        "${MAYA_DEVKIT_ROOT}/devkit.zip"
        SHA1 3EECB64E61309D9DD93F12736525702053A139F6
    )
    extract_file(
        "${MAYA_DEVKIT_ROOT}/devkit.zip"
        "${MAYA_DEVKIT_ROOT}/devkit"
    )
elseif (APPLE)
    set(MAYA_DEVKIT_ROOT "${MAYA_DEVKIT_ROOT}/macOS")
    set(MAYA_DEVKIT_LOCATION "${MAYA_DEVKIT_ROOT}/devkit/devkitBase")
    download_file(
        https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2020/Autodesk_Maya_2020_3_Update_DEVKIT_Mac.dmg
        "${MAYA_DEVKIT_ROOT}/devkit.dmg"
        SHA1 52E5E62773CD2B6155E1F85D34B983F316667792
    )
    extract_file_dmg(
        "${MAYA_DEVKIT_ROOT}/devkit.dmg"
        "devkitBase"
        "${MAYA_DEVKIT_ROOT}/devkit"
    )
else ()
    set(MAYA_DEVKIT_ROOT "${MAYA_DEVKIT_ROOT}/linux")
    set(MAYA_DEVKIT_LOCATION "${MAYA_DEVKIT_ROOT}/devkit/devkitBase")
    download_file(
        https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2020/Autodesk_Maya_2020_3_Update_DEVKIT_Linux.tgz
        "${MAYA_DEVKIT_ROOT}/devkit.tgz"
        SHA1 211ED0A662B999BDEEFFBA2B2629DA241AE971DB
    )
    extract_file(
        "${MAYA_DEVKIT_ROOT}/devkit.tgz"
        "${MAYA_DEVKIT_ROOT}/devkit"
    )
endif()

set(ENV{DEVKIT_LOCATION} ${MAYA_DEVKIT_LOCATION})
set(LIBRARIES
    OpenMaya
    OpenMayaAnim
    OpenMayaFX
    OpenMayaRender
    OpenMayaUI
    Foundation
)

# Maya Dev Kit - Include the project setting file / include path
include(${MAYA_DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

set(SOURCE_FILES
    src/MayaPluginAdapter.h
    src/MayaPluginAdapter.cpp
)

# Maya Dev Kit - add the plugin building function name
build_plugin()