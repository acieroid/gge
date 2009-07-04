project(GuileGameEngine)
add_executable(gge main.cpp System.cpp ScriptManager.cpp LogManager.cpp)
target_link_libraries(gge boost_program_options  -pthread  -lguile -lltdl -lgmp -lcrypt -lm -lltdl)
