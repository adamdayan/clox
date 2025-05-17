add_library(clox_lib src/chunk.c src/memory.c src/debug.c src/value.c src/vm.c)
target_include_directories(clox_lib PUBLIC include)


