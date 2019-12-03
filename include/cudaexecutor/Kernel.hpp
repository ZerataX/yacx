#pragma once

#include "Device.hpp"
#include "KernelArg.hpp"
#include "Logger.hpp"
#include "KernelTime.hpp"

#include <cuda.h>
#include <memory>
#include <nvrtc.h>
#include <vector>
#include <vector_types.h>

namespace cudaexecutor {
/*!
  \class Kernel Kernel.hpp
  \brief Class to help launch and configure a CUDA kernel
  \example docs/kernel_launch.cpp
  \example example_saxpy.cpp
*/
class Kernel {
 public:
  //! create a Kernel based on a templated kernel string
  //! \param ptx
  //! \param kernel_name
  //! \param demangled_name
  Kernel(std::shared_ptr<char[]> ptx, std::string demangled_name);
  //!
  //! \param grid vector of grid dimensions
  //! \param block vector of block dimensions
  //! \return this (for method chaining)
  Kernel &configure(dim3 grid, dim3 block);
  //!
  //! \param program_args
  //! \return KernelTime
  KernelTime &launch(std::vector<KernelArg> program_args, Device device = Device());

 private:
  std::shared_ptr<char[]> m_ptx;
  std::string m_demangled_name;

  dim3 m_grid, m_block;
  CUcontext m_context;
  CUmodule m_module;
  CUfunction m_kernel;
};

} // namespace cudaexecutor
