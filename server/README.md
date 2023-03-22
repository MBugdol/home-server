# About

The **Home Server** project is aimed to provide a storage server with a clean and easy API. Its abilities will include sending and receiving data, live video and music transfer and more.

## Prerequisites
The server project has the following prerequisites:
- CMake - see [this page](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html) for a brief tutorial,
- Python3 and pip - you can download them from [here](https://www.python.org/downloads/).

Step-by-step tutorial for launching this project:
1. Use CMake to launch the top-level CMakeLists.txt. You can do this by using the `cmake --build <output_dir>` command,
2. Wait for the CMake process to finish - it creates a virtual Python environment, compiles the C++ library into a dynamic library and initializes the whole dependency chain for you,
3. Run main.py - that's all!

You can also launch the server from the Python terminal using `uvicorn main:app` command. This is a basic server launch command - see [uvicorn.org](https://www.uvicorn.org/#command-line-options) for all of the possible options.