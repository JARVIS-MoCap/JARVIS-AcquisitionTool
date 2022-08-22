set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

find_package(CUDA REQUIRED)

if (UNIX)
  add_compile_options("-O3")
  add_compile_options("-m64")
else()
  add_compile_options("-O2")
  
endif()

if (MSVC OR WIN32 OR MSYS)
    MESSAGE( STATUS "CMAKE_CUDA_COMPILER: " ${CMAKE_CUDA_COMPILER} )
    set(CUDA_LIBRARY_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.7/lib/x64")
    set(CUDART_LIBRARY ${CUDA_LIBRARY_PATH}/cudart.lib)
    set(NVJPEG_LIBRARY ${CUDA_LIBRARY_PATH}/nvjpeg.lib)
    set(NPPIG_LIBRARY ${CUDA_LIBRARY_PATH}/nppig.lib)
    set(NPPC_LIBRARY ${CUDA_LIBRARY_PATH}/nppc.lib)
    set(NPPICC_LIBRARY ${CUDA_LIBRARY_PATH}/nppicc.lib)

endif()


add_library(cudajpegencoder
  cuda_exception.h
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

if (MSVC OR WIN32 OR MSYS)
  target_link_libraries(cudajpegencoder
    ${CUDART_LIBRARY}
    ${NVJPEG_LIBRARY}
    ${NPPIG_LIBRARY}
    ${NPPC_LIBRARY}
    ${NPPICC_LIBRARY}
  )
else()
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
endif()
