message(NOTICE "Starting work on the C++ extension")

set(CMAKE_CXX_STANDARD 20 REQUIRED)



#
# Create the base library
#

message(NOTICE "Creating the base library...")

set(HOSE_BACKEND_SOURCES
	"include/debug.h" 
	"include/entry.h" "src/filesystem_structure/entry.cpp"
	"include/folder.h" "src/filesystem_structure/folder.cpp" 
	"include/file.h" "src/filesystem_structure/file.cpp"

	"include/database.h" "src/database/database.cpp"
	"include/queryiterator.h" "src/database/queryiterator.cpp"
	"include/query.h" "src/database/query.cpp"

	"include/uploadmanager.h" "src/transfer/uploadmanager.cpp" 
	"include/uploadtable.h" "src/database/uploadtable.cpp"

	  
	"include/concepts.h"
	
	"vendor/sqlite/sqlite3.h" "vendor/sqlite/sqlite3.c" 
	
    "include/crypto_utils.h" "src/auth/crypto_utils.cpp"  
 "src/filesystem_structure/filemetadata.cpp")

add_library(HoseBackendLib STATIC ${HOSE_BACKEND_SOURCES})
target_link_libraries(HoseBackendLib cryptopp::cryptopp nlohmann_json::nlohmann_json)
target_include_directories(HoseBackendLib 
	PUBLIC
		"include" 
		"vendor/sqlite"
		"vendor/cryptopp"
	PRIVATE
		"src" 
		#"vendor/asio-1.24.0/include"
)

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


target_sources(HoseBackendPythonModule PRIVATE 
"python_module/file_transfer.h" "python_module/file_transfer.cpp"
"python_module/file_navigation.h" "python_module/file_navigation.cpp"
"module.cpp" )
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

add_subdirectory(tests)