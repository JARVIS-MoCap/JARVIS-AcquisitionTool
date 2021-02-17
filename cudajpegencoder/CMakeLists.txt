project (cudajpegencoder LANGUAGES CXX CUDA)
find_package(OpenCV REQUIRED)
find_package(CUDA)
add_compile_options("-O3")
 add_compile_options("-m64")


add_library(${PROJECT_NAME}
  exception.h
  helper_cuda.h
  helper_nvJPEG.hpp
  helper_string.h
  helper_timer.h
  cudajpegencoder.hpp
  cudajpegencoder.cu
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${CUDA_INCLUDE_DIRS}
    ../
)

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
  -lnvjpeg
  -lnppc
  -lnppicc
  -lnppig
)
