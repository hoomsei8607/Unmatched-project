cmake_minimum_required(VERSION 3.10)
project(UNMATCHED_BOARD_GAME)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git GIT_TAG v6.1.9)
FetchContent_MakeAvailable(ftxui)
add_executable(app src/main.cpp)
set(CMAKE_BUILD_TYPE Debug)
add_library(My_Written_Code 
                src/Ui_Menu_Screen.cpp
                src/Ui_GameLoop_Screen.cpp
                src/Ui.cpp
                src/get_user_input.cpp
                src/controller.cpp
                src/user.cpp
                src/fighter_abstract.cpp
                src/fighter_sub_classes.cpp
                src/main_game_loop_sideckick_placement_manager.cpp
                src/game_flow_ui_to_controller_interface.cpp
                src/graph.cpp
                src/space.cpp
                src/cards.cpp
                src/card_abstract.cpp
                src/Fighting_Screen_Manager_Class.cpp
                src/after_combat_sub_screen_manager.cpp
                )
target_link_directories(My_Written_Code PUBLIC headers)

target_link_libraries(My_Written_Code PUBLIC ftxui::screen ftxui::dom ftxui::component)
target_link_libraries(app PRIVATE My_Written_Code)