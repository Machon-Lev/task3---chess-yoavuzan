﻿cmake_minimum_required (VERSION 3.15)

project (Task3_Yoav_Uzan)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Task3_Yoav_Uzan  "include/Chess.h" "include/Board.h" "include/Rook.h" "include/Knight.h" "include/Pawn.h"
"include/Peice.h"  "include/King.h" "include/Loction.h" "include/Color.h" "include/Bishop.h" 
 "src/Peice.cpp" "src/Board.cpp"  "src/Rook.cpp" "src/King.cpp" "src/main.cpp" "src/Chess.cpp"
 "src/Bishop.cpp" "include/Queen.h" "src/Queen.cpp" "src/Pawn.cpp" "src/Knight.cpp")


add_subdirectory (include)
add_subdirectory (src)



