cmake_minimum_required(VERSION 3.27)

project(main)

set(MY_BOOL TRUE)
if(my_bool)
    message(STATUS "Condation was met...")
else()
    message(STATUS "Condational failed...")
endif()

set(MY_STRING "This is a string")
if(MY_STRING MATCHES "string$")
    message(STATUS "Variable ends with word 'string'...")
endif()

set(MY_VALUE 5)
while(MY_VALUE LESS 10)
    message(STATUS "Value is ${MY_VALUE}")        
    math(EXPR MY_VALUE "${MY_VALUE}+1")
endwhile()

foreach(item IN ITEMS foo bar baz qux)
    message(STATUS "Item is ${item}")
endforeach()

foreach(idex RANGE 0 100 5)
    message(STATUS "Value is ${idex}")
endforeach()

set(MY_LIST 1 2 3)
set_property(GLOBAL PROPERTY FOO ${MY_LIST})
get_cmake_property(foo_value FOO)
message(STATUS "value of FOO is ${foo_value}")

function(do_cmake_good arg1)
    message(STATUS "You called the function wiht argument: ${arg1}")
endfunction(do_cmake_good arg1)
do_cmake_good(1)
do_cmake_good(2)
do_cmake_good(3)

function(do_cmake_good arg1 arg2)
    foreach(arg IN LISTS ARGN)
        message(STATUS "Got ARGN argument: ${arg}")
    endforeach()    
    foreach(arg IN LISTS ARGV)
        message(STATUS "Got ARGV argument: ${arg}")
    endforeach()
    
endfunction(do_cmake_good arg1 arg2)
do_cmake_good(1 2 3 4 5 6)

function(test_parse)
    set(options op1 op2 op3)
    set(oneValueArgs v1 v2 v3)
    set(multiValueArgs m1 m2)
    message(STATUS "options = ${options}")
    message(STATUS "oneValueArgs = ${oneValueArgs}")
    message(STATUS "multiValueArgs = ${multiValueArgs}")
    cmake_parse_arguments(MYPRE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    message("op1  = ${MYPRE_op1}")
    message("op2  = ${MYPRE_op2}")
    message("op3  = ${MYPRE_op3}")

    message("v1  = ${MYPRE_v1}")
    message("v2  = ${MYPRE_v2}")
    message("v3  = ${MYPRE_v3}")

    message("m1  = ${MYPRE_m1}")
    message("m2  = ${MYPRE_m2}")
endfunction()

message( STATUS "\n" )
test_parse( op1 op2 op3 v1 aaa v2 111 v3 bbb m1 1 2 3 4 5 m2 a b c )

message( STATUS "\n" )
test_parse(op1 op3 v1 aaa v2 111 v3 bbb m1 1 2 3 4 5 m2 a b c )

message( STATUS "\n" )
test_parse(op1 op3 v1 aaa v2 v3 bbb m1 1 2 3 4 5  )

message( STATUS "\n" )
test_parse( op1  v1 aaa v2 op2 111 v3 bbb m1 1 2 3 4 5 m2 a b c op3 )