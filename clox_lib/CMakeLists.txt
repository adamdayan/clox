add_library(clox_lib src/chunk.c src/memory.c src/debug.c src/value.c src/vm.c src/compiler.c src/scanner.c)
target_include_directories(clox_lib PUBLIC include)




