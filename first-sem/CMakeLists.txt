set(CMAKE_CXX_STANDARD 17)

#include(FetchContent)

#FetchContent_Declare(libfort
#  GIT_REPOSITORY    https://github.com/seleznevae/libfort
#  GIT_TAG           41237162a9bd34a30a88069ee4e230584ae8d674
#)
#set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")
#FetchContent_MakeAvailable(libfort)

add_executable(LW1 LW1.cpp)
add_executable(LW2 LW2.cpp)
add_executable(LW3 LW3.cpp)

#add_executable(LW2a LW2_alt.cpp)
#target_link_libraries(LW2a PRIVATE libfort::fort)
