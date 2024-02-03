set(SENDER_LIB "sender")
add_library(${SENDER_LIB} Sender.cpp)
target_include_directories(${SENDER_LIB} PUBLIC ${CMAKE_TOP_DIR}/Buffer/ ${CMAKE_TOP_DIR}/Receiver/)
