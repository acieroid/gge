project(GuileGameEngine)
add_executable(gge main.cpp ScriptManager.cpp System.cpp LogManager.cpp Display.cpp)
target_link_libraries(gge boost_program_options  -pthread  -lguile -lltdl -lgmp -lcrypt -lm -lltdl -lSDL)
