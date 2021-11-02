find_package(CUDA REQUIRED)

add_compile_options("-O3")
add_compile_options("-m64")

add_library(cudajpegencoder
  exception.h
  helper_cuda.h
  helper_nvJPEG.hpp
  helper_string.h
  helper_timer.h
  cudajpegencoder.hpp
  cudajpegencoder.cu
)


target_include_directories(cudajpegencoder
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${CUDA_INCLUDE_DIRS}
    .
)

target_link_libraries(cudajpegencoder
  ${CUDNN_LIBRARY}
  ${CULIBOS_LIBRARY}
  ${CUDA_LIBRARIES}
  -lnvjpeg
  -lnppc
  -lnppicc
  -lnppig
  -lculibos
)
