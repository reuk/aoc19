file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
add_executable(aoc2019 ${sources})
target_link_libraries(aoc2019 PUBLIC aoc Catch2::Catch2)
