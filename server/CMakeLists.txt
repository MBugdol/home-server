#
#	Set project prerequisites
#
cmake_minimum_required(VERSION 3.18)
project(Server)

#
#	Prepare the CMake options
#	To modify these options use your editor's project options
#	For Visual Studio: go to Project -> CMake settings for project X -> Cache and CMake variables
#
message(NOTICE "=== Setting CMake variables ===")

set(PYTHON_VENV_PATH
	"${CMAKE_CURRENT_LIST_DIR}/venv" CACHE PATH 
	"Path to the python virtual environment")
message(TRACE "PYTHON_VENV_PATH: ${PYTHON_VENV_PATH}")

#
#	Python initialization
#
message(NOTICE "=== Initializing Python virtual environment ===")
message("Looking for Python...")
find_package(Python3 COMPONENTS Interpreter REQUIRED)

#	initializing python venv
IF(NOT EXISTS "${PYTHON_VENV_PATH}")
	message(WARNING "Python virtual environment not found - creating one...")
	execute_process(COMMAND "${Python3_EXECUTABLE}" -m venv "${PYTHON_VENV_PATH}")
ELSE()
	message("Python virtual environment found!")
ENDIF()

#	switch to virtual env
message(NOTICE "Switching to Python virtual environment...")

set (ENV{VIRTUAL_ENV} "${PYTHON_VENV_PATH}")
set (Python3_FIND_VIRTUALENV FIRST)
unset(Python3_EXECUTABLE)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

message(NOTICE "Python virtual environment launched!")
message(NOTICE "Installing python requirements...")
execute_process(COMMAND "${Python3_EXECUTABLE}" -m pip install -r "${CMAKE_CURRENT_LIST_DIR}/requirements.txt")
message(NOTICE "Python prerequisites installed!")

#
#	Preparing the C++ module
#
message("Setting prerequisites for the C++ module...")

set(PYBIND11_PATH "${PYTHON_VENV_PATH}/Lib/site-packages/pybind11/share/cmake/pybind11")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PYBIND11_PATH})

add_subdirectory(cpp)
