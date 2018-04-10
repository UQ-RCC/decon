cmake_minimum_required (VERSION 3.8)

project ("decon-test" VERSION 0.1 LANGUAGES CXX)

add_executable(decon-test decon.cpp Licensing.h DeconvolutionLauncher.h Callbacks.h)
target_link_libraries(decon-test ${CMAKE_CURRENT_SOURCE_DIR}/libMicrovolution.so)
#target_link_libraries(decon-test /opt/ohpc/pub/apps/fiji/Fiji.app/lib/libMicrovolution.so)

