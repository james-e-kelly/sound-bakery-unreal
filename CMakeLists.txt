cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. You should create a separate directory for build files.")
endif()

project(sound_bakery_unreal)

include(FetchContent)

FetchContent_Declare(
  sound_bakery
  GIT_REPOSITORY https://github.com/james-e-kelly/sound-bakery
  GIT_TAG        dev
  GIT_SHALLOW    TRUE
  GIT_PROGRESS TRUE
  OVERRIDE_FIND_PACKAGE 
)

FetchContent_MakeAvailable(sound_bakery)

if (WIN32)
    set(SBK_UE5_PLATFORM_FOLDER "x64")
elseif(UNIX)
    if (APPLE)
        set(SBK_UE5_PLATFORM_FOLDER "Mac")
    else()
        set(SBK_UE5_PLATFORM_FOLDER "Linux")
    endif()
endif()

install(TARGETS sound_chef_shared DESTINATION "${PROJECT_SOURCE_DIR}/Source/ThirdParty/SoundBakeryLibrary/${SBK_UE5_PLATFORM_FOLDER}/$<CONFIG>")
install(TARGETS sound_bakery_shared DESTINATION "${PROJECT_SOURCE_DIR}/Source/ThirdParty/SoundBakeryLibrary/${SBK_UE5_PLATFORM_FOLDER}/$<CONFIG>")
install(DIRECTORY ${sound_bakery_SOURCE_DIR}/dist/inc/sound_bakery DESTINATION "${PROJECT_SOURCE_DIR}/Source/ThirdParty/SoundBakeryLibrary/Public/SoundBakeryLibrary")
install(DIRECTORY ${sound_bakery_SOURCE_DIR}/dist/inc/sound_chef DESTINATION "${PROJECT_SOURCE_DIR}/Source/ThirdParty/SoundBakeryLibrary/Public/SoundBakeryLibrary")