#pragma once

#include <cuda.h>
#include <string>
#include <vector_types.h>

namespace cudaexecutor {

class Device {
  /*!
    \class Device Device.hpp
    \brief Class to help get a CUDA-capable device
  */
 public:
  Device();
  explicit Device(std::string name);
  [[nodiscard]] int minor() const { return _minor; }
  [[nodiscard]] int major() const { return _major; }
  std::string name() const { return _name; }
  CUdevice get() { return _device; }
  size_t total_memory() { return _memory; }
  void max_block_dim(dim3 *block);
  void max_grid_dim(dim3 *grid);

 private:
  void set_device_properties(const CUdevice &device);

  int _minor, _major;
  std::string _name;
  CUdevice _device;
  size_t _memory;
};

} // namespace cudaexecutor
