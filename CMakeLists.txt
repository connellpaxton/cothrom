cmake_minimum_required (VERSION 3.8)

if(WIN32)
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
endif()


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cothrom")


include_directories(cothrom include)
add_executable (cothrom cothrom.cpp thirdparty/glad.c)

find_package(glfw3 3.3 REQUIRED)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cothrom PROPERTY CXX_STANDARD 20)
endif()

if(UNIX)
	set(GLFW3_LIBRARY glfw)
endif()


include_directories(${CMAKE_CURRENT_LIST_DIR} thirdparty/include ${GLFW3_INCLUDE_DIR})

target_link_libraries(cothrom ${GLFW3_LIBRARY})

