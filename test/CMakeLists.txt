find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIR})

add_executable(check_parse_app check_parse.c)
add_test(check_parse_suite check_parse_app)
target_link_libraries(check_parse_app romcalc ${CHECK_LIBRARIES})

add_executable(check_unparse_app check_unparse.c)
add_test(check_parse_suit check_unparse_app)
target_link_libraries(check_unparse_app romcalc ${CHECK_LIBRARIES})

add_executable(check_calculator_app check_calculator.c)
add_test(check_calculator_suite check_calculator_app)
target_link_libraries(check_calculator_app romcalc ${CHECK_LIBRARIES})