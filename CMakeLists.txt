cmake_minimum_required (VERSION 3.11)
project (VisualEditor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -EHsc)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Src
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "Source/*.cpp")
include_directories(Include)

# Vendor
include_directories("Vendor/sdl/vc/include/")
link_directories("Vendor/sdl/vc/lib/x64/")

set(imguisources
        "Vendor/imgui/imgui.cpp"
        "Vendor/imgui/imgui_draw.cpp"
        "Vendor/imgui/imgui_tables.cpp"
        "Vendor/imgui/imgui_widgets.cpp"
        "Vendor/imgui/backends/imgui_impl_sdl.cpp"
        "Vendor/imgui/backends/imgui_impl_opengl3.cpp")
include_directories("Vendor/imgui/")
include_directories("Vendor/imgui/backends/")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include(FetchContent)
message(cmake-build-debug/_deps/json-src/include)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(VisualEditor ${sources} ${imguisources})

target_link_libraries(VisualEditor SDL2main SDL2 ${OPENGL_LIBRARIES} nlohmann_json::nlohmann_json)