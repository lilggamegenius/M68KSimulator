add_library(Simulator SHARED Simulator.cpp Exceptions.cpp Helpers.cpp Opcodes/Opcode.cpp)

install(TARGETS Simulator
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)