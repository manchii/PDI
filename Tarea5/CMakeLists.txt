cmake_minimum_required(VERSION 2.8)
project( tarea5-ocv )
find_package( OpenCV REQUIRED )
add_executable( tarea5-ocv tarea5-ocv.cpp )
set_property(TARGET tarea5-ocv PROPERTY CXX_STANDARD 11)
target_link_libraries( tarea5-ocv ${OpenCV_LIBS} )
