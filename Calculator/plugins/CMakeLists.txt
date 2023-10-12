set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(funcpow SHARED "Pow.cpp")
add_library(funcsin SHARED "Sin.cpp")
add_library(funccos SHARED "Cos.cpp")
add_library(funcmod SHARED "Mod.cpp")
add_library(funcfxyz SHARED "Fxyz.cpp")