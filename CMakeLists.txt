cmake_minimum_required(VERSION 2.8.9)
project(ngl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) 

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
	${PROJECT_SOURCE_DIR}/src/CmdLine.cc
	${PROJECT_SOURCE_DIR}/src/Event.cc
	${PROJECT_SOURCE_DIR}/src/Momentum.cc
	${PROJECT_SOURCE_DIR}/src/Parameters.cc
	${PROJECT_SOURCE_DIR}/src/Shower.cc
	${PROJECT_SOURCE_DIR}/src/helpers.cc)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

find_package(GSL REQUIRED)

add_library(gnole_core STATIC ${SOURCES})

target_include_directories(gnole_core PUBLIC 
						${PROJECT_SOURCE_DIR}/include
)	

target_link_libraries(gnole_core PUBLIC GSL::gsl GSL::gslcblas)

add_executable(gnole
        ${PROJECT_SOURCE_DIR}/src/gnole.cc)
#target_link_libraries(gnole PRIVATE gnole_core)


add_executable(gnole_hemisphere
		${PROJECT_SOURCE_DIR}/hemisphere_mass/gnole_hemisphere.cc
		)
#target_link_libraries(gnole_hemisphere PRIVATE gnole_core hemisphere_mass)


# just for example add some compiler flags
add_definitions(-Wall -g -O2)

# added my own subdirectory for experiments
add_subdirectory(hemisphere_mass)


option(NNET "Use neural network implementation" OFF)
if(NNET)
find_package(Torch REQUIRED)
target_link_libraries(gnole ${TORCH_LIBRARIES} gnole_core)
target_link_libraries(gnole_hemisphere ${TORCH_LIBRARIES} gnole_core})
add_definitions(-DNNET)
else()
target_link_libraries(gnole PRIVATE gnole_core)
target_link_libraries(gnole_hemisphere PRIVATE gnole_core)
endif(NNET)
unset(NNET)
 
