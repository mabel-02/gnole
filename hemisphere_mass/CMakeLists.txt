add_library(hemisphere_mass STATIC
    hemisphere.cc
    ${PROJECT_SOURCE_DIR}/include/Observables.hh)

target_include_directories(hemisphere_mass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})