cmake_minimum_required(VERSION 3.10)
project(PlayingCard)

set(CMAKE_CXX_STANDARD 14)

# Основной проект - демонстрация игральной карты
add_executable(card_demo 
    main.cpp 
    location.cpp 
    point.cpp 
    card.cpp
)

# Проект с виртуальными методами
add_executable(card_demo_virt
    main_virt.cpp
    location.cpp
    point_virt.cpp
    card_virt.cpp
)

# Добавляем windows.h и другие необходимые библиотеки для компиляции в Windows
if(WIN32)
    target_link_libraries(card_demo gdi32)
    target_link_libraries(card_demo_virt gdi32)
endif()
