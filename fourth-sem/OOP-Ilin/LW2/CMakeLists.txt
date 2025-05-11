cmake_minimum_required(VERSION 3.10)

# Создание исполняемого файла с уникальным именем
add_executable(card_demo_lw2
    main_virt.cpp
    card_virt.cpp
    location.cpp
    point_virt.cpp
)

# Подключение библиотек Windows
target_link_libraries(card_demo_lw2
    gdi32
    user32
)
