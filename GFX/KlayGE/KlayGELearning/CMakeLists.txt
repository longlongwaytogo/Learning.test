project(KlayGELearning)

cmake_minimum_required(VERSION 3.20)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

 
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0074 NEW)
set(KLAYGE_ROOT CACHE PATH "")

#message(STATUS "modulePath:${CMAKE_MODULE_PATH}")

#EXECUTABLE_OUTPUT_PATH
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#LIBRARY_OUTPUT_PATH
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

 set(KLAYGE_BIN  ${KLAYGE_ROOT}/KlayGE/bin/win_x64)
 set(MY_CUSTOM_PATH ${KLAYGE_BIN})
 set(MY_PATH "PATH=${MY_CUSTOM_PATH};%PATH%")
 include_directories(
${KLAYGE_ROOT}/KlayGE/Core/Include/KlayGE
${KLAYGE_ROOT}/KlayGE/Core/Include
${KLAYGE_ROOT}/KlayGE/Plugins/Include/KlayGE
${KLAYGE_ROOT}/KlayGE/Plugins/Include
${KLAYGE_ROOT}/KFL/include
${KLAYGE_ROOT}/KFL/include/KFL
${KLAYGE_ROOT}/KlayGE/External
${KLAYGE_ROOT}/External/boost/assert/include
${KLAYGE_ROOT}/External/boost/static_assert/include
${KLAYGE_ROOT}/External/boost/utility/include
${KLAYGE_ROOT}/External/boost/core/include
${KLAYGE_ROOT}/External/boost/config/include
${KLAYGE_ROOT}/External/boost/container_hash/include
${KLAYGE_ROOT}/External/boost/describe/include
${KLAYGE_ROOT}/External/boost/detail/include
${KLAYGE_ROOT}/External/boost/integer/include
${KLAYGE_ROOT}/External/boost/type_index/include
${KLAYGE_ROOT}/External/boost/type_traits/include
${KLAYGE_ROOT}/External/boost/throw_exception/include
${KLAYGE_ROOT}/External/boost/preprocessor/include
${KLAYGE_ROOT}/External/boost/mp11/include
${KLAYGE_ROOT}/External/scope-lite/include
${KLAYGE_ROOT}/External/GSL/include
 )

 link_libraries(${KLAYGE_ROOT}/KlayGE/lib/win_x64/KlayGE_Core_vc142_d.lib
 ${KLAYGE_ROOT}/KFL/lib/win_x64/KFL_vc142_d.lib
 )

add_definitions(-DKLAYGE_ROOT="${KLAYGE_ROOT}")
add_definitions(-DKLAYGE_BINARY_ROOT="${KLAYGE_ROOT}/KlayGE/bin/win_x64")

add_subdirectory(examples/Tutor1)
add_subdirectory(examples/Tutor2)
add_subdirectory(examples/DrawAxis)