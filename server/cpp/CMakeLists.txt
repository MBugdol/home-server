message(NOTICE "Starting work on the C++ extension")

set(CMAKE_CXX_STANDARD 20 REQUIRED)



#
# Create the base library
#

message(NOTICE "Creating the base library...")

set(HOSE_BACKEND_SOURCES
	"include/debug.h" 
	"include/file_access.h" "src/file_access.cpp" 
	"include/entry.h" "src/filesystem_structure/entry.cpp"
	"include/directory.h" "src/filesystem_structure/directory.cpp" 
	"include/file.h" "src/filesystem_structure/file.cpp"

	"include/database.h" "src/database/database.cpp"
	"include/queryiterator.h" "src/database/queryiterator.cpp"
	"include/query.h" "src/database/query.cpp"
	"include/userstable.h" "src/database/userstable.cpp" 
	"include/concepts.h"

	"include/accountmanager.h" "src/auth/accountmanager.cpp"
	
	"vendor/sqlite/sqlite3.h" "vendor/sqlite/sqlite3.c" 
	
 "include/user.h"    )

add_library(HoseBackendLib STATIC ${HOSE_BACKEND_SOURCES})
target_include_directories(HoseBackendLib 
	PUBLIC
		"include" 
		"vendor/sqlite"
	PRIVATE
		"src" 
		#"vendor/asio-1.24.0/include"
)
#target_link_libraries(HoseBackendLib cryptopp::cryptopp)

# target compile definitions

if(NOT ${HOSE_INSTALL_PATH} EQUAL "")
	target_compile_definitions(HoseBackendLib PUBLIC 
	HOSE_INSTALL_PATH="${HOSE_INSTALL_PATH}"
	)
endif()


#
# Set up the actual Python module
#

message(NOTICE "Creating the Python module...")
find_package(pybind11 REQUIRED)
pybind11_add_module(HoseBackendPythonModule)


target_sources(HoseBackendPythonModule PRIVATE module.cpp)
target_link_libraries(HoseBackendPythonModule PRIVATE HoseBackendLib)

set_target_properties(HoseBackendPythonModule PROPERTIES 
	OUTPUT_NAME "backend"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin"
)

add_custom_command(TARGET HoseBackendPythonModule POST_BUILD
	COMMAND "${Python3_EXECUTABLE}" -m pip install ${CMAKE_CURRENT_LIST_DIR})

#
# Set up the sandbox executable
#

message(NOTICE "Creating the sandbox executable...")

add_executable(HoseBackendSandbox sandbox.cpp)
target_link_libraries(HoseBackendSandbox PRIVATE HoseBackendLib)

#
# Add tests
#

#add_subdirectory(tests)