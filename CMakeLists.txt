cmake_minimum_required(VERSION 3.10)

# set the project name
set (CMAKE_CXX_STANDARD 17)
project(CmakeTest)
include(FindPkgConfig)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)


# include dirs
include_directories(
    include
    ${LIBMYSQLCLIENT_INCLUDE_DIRS}
    ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
    # ${GLPK_INCLUDE_DIRS}
    # /home/hems/glpk-4.65/src
)

link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})

# add the executable
# executable include 3 demand response by 5 household CEMS
add_executable(LHEMS src/LHEMS.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(LHEMS 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)
add_executable(GHEMS src/GHEMS.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(GHEMS 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)

add_executable(LHEMS_dr1 src/LHEMS_dr1.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(LHEMS_dr1 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)
add_executable(GHEMS_dr1 src/GHEMS_dr1.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(GHEMS_dr1 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)

add_executable(LHEMS_dr2 src/LHEMS_dr2.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(LHEMS_dr2 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)
add_executable(GHEMS_dr2 src/GHEMS_dr2.cpp src/new2D.cpp src/SQLFunction.cpp src/scheduling_parameter.cpp)
target_link_libraries(GHEMS_dr2 
${LIBMYSQLCLIENT_LIBRARIES} 
/usr/local/lib/libglpk.a
)