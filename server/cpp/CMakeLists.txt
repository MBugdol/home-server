message(NOTICE "Starting work on the C++ extension")

message(NOTICE "Looking for required packages...")
find_package(pybind11 REQUIRED)

pybind11_add_module(backend)

target_sources(backend
	PRIVATE	
	src/module.cpp
 "src/file_access.cpp" "src/file_access.h")

target_include_directories(backend PRIVATE vendor/asio-1.24.0/include)
if(NOT ${HOSE_INSTALL_PATH} EQUAL "")
	target_compile_definitions(backend PUBLIC 
	HOSE_INSTALL_PATH="${HOSE_INSTALL_PATH}"
	)
endif()


set_target_properties(backend
	PROPERTIES
	LANGUAGE CXX
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin"
)

add_custom_command(TARGET backend POST_BUILD
	COMMAND "${Python3_EXECUTABLE}" -m pip install ${CMAKE_CURRENT_LIST_DIR})