cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/Private/EntityManager.cpp" "src/Public/Components/BaseComponent.h" "src/Public/EntityManager.h" "src/Public/System/BaseSystem.h" "src/Public/Components/SpriteComponent.h"  "src/Public/Entity/BaseEntity.h" "src/Public/System/RenderSystem.h" "src/Private/System/RenderSystem.cpp" "src/Public/Entity/Player.h" "src/Public/Components/SpriteSheetComponent.h" "src/Public/Components/TransformComponent.h" "src/Public/System/PlayerSystem.h" "src/Private/System/PlayerSystem.cpp" "src/Public/Entity/Coin.h" "src/Public/Components/BoxCollisionComponent.h" "src/Public/System/CoinSystem.h" "src/Private/System/CoinSystem.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Public
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/img"
    "$<TARGET_FILE_DIR:main>/img"
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
