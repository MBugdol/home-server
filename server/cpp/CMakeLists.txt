message(NOTICE "Starting work on the C++ extension")

message(NOTICE "Looking for required packages...")
find_package(pybind11 REQUIRED)

pybind11_add_module(backend)

target_sources(backend
	PRIVATE	
	src/module.cpp
)

set_target_properties(backend
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin"
)

add_custom_command(TARGET backend POST_BUILD
	COMMAND "${Python3_EXECUTABLE}" -m pip install ${CMAKE_CURRENT_LIST_DIR})