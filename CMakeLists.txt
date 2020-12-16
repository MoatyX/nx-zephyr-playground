
# Point to LBP root directory.
set(NX_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "NX root directory")

zephyr_include_directories("include")
message("sexxxxxxxxxy boy")

add_subdirectory("subsys")
