set(RECEIVER_LIB "receiver")
add_library(${RECEIVER_LIB} Receiver.cpp)
target_include_directories(${RECEIVER_LIB} PUBLIC ${CMAKE_TOP_DIR}/Buffer/)
