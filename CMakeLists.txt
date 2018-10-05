project(fuz_cy_logic)

include_directories(HPPCODE)
file(GLOB implementation_code "./CPPCODE/*.CPP")

add_library(fuz_cy_lib ${implementation_code})