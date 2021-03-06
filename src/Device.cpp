#include "yacx/Devices.hpp"
#include "yacx/Exception.hpp"
#include "yacx/Logger.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

using yacx::Device, yacx::CUresultException, yacx::loglevel;

Device::Device(int ordinal) {
  CUdevice device;
  CUDA_SAFE_CALL(cuDeviceGet(&device, ordinal));
  this->set_device_properties(device);
}

void Device::set_device_properties(const CUdevice &device) {
  m_device = device;
  char cname[50];
  CUDA_SAFE_CALL(cuDeviceGetName(cname, 50, m_device));
  m_name = cname;

  m_major = attribute(CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR);
  m_minor = attribute(CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR);
  m_max_shared_memory_per_block =
      attribute(CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK);
  m_max_shared_memory_per_multiprocessor =
      attribute(CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR);
  m_multiprocessor_count = attribute(CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT);
  m_clock_rate = attribute(CU_DEVICE_ATTRIBUTE_CLOCK_RATE);
  m_memory_clock_rate = attribute(CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE);
  m_bus_width = attribute(CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH);

  CUDA_SAFE_CALL(cuDeviceTotalMem(&m_memory, m_device));

#if CUDA_VERSION >= 9020
  CUuuid uuid;
  CUDA_SAFE_CALL(cuDeviceGetUuid(&uuid, m_device));
  m_uuidHex = uuidToHex(uuid);
#else
  m_uuidHex = "";
#endif
}

Device::Context::Context(CUdevice device) {
  this->device = device;

  CUDA_SAFE_CALL(cuDevicePrimaryCtxRetain(&primaryContext, device));

  CUDA_SAFE_CALL(cuCtxSetCurrent(primaryContext));
  CUDA_SAFE_CALL(cuStreamCreate(&upload, CU_STREAM_NON_BLOCKING));
  CUDA_SAFE_CALL(cuStreamCreate(&launch, CU_STREAM_NON_BLOCKING));
  CUDA_SAFE_CALL(cuStreamCreate(&download, CU_STREAM_NON_BLOCKING));
}

Device::Context::~Context() {
  CUDA_SAFE_CALL(cuCtxSetCurrent(primaryContext));
  CUDA_SAFE_CALL(cuStreamDestroy(upload));
  CUDA_SAFE_CALL(cuStreamDestroy(launch));
  CUDA_SAFE_CALL(cuStreamDestroy(download));

  CUDA_SAFE_CALL(cuDevicePrimaryCtxRelease(device));
}

CUcontext Device::getPrimaryContext() {
  if (!m_context) {
    m_context = std::make_shared<struct Context>(m_device);
  }

  return m_context.get()->primaryContext;
}

CUstream Device::getUploadStream() {
  if (!m_context) {
    m_context = std::make_shared<struct Context>(m_device);
  }

  return m_context.get()->upload;
}

CUstream Device::getLaunchStream() {
  if (!m_context) {
    m_context = std::make_shared<struct Context>(m_device);
  }

  return m_context.get()->launch;
}

CUstream Device::getDownloadStream() {
  if (!m_context) {
    m_context = std::make_shared<struct Context>(m_device);
  }

  return m_context.get()->download;
}

std::string Device::uuidToHex(CUuuid &uuid) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < 16; i++) {
    ss << std::hex << std::setw(2)
       << (int)static_cast<unsigned char>(uuid.bytes[i]);
    if (i == 3 || i == 5 || i == 7 || i == 9) {
      ss << "-";
    }
  }
  return ss.str();
}

dim3 Device::max_block_dim() {
  dim3 block;
  block.x = attribute(CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X);
  Logger(loglevel::DEBUG1) << "block.x = " << block.x;

  block.y = attribute(CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y);
  Logger(loglevel::DEBUG1) << "block.y = " << block.y;

  block.z = attribute(CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z);
  Logger(loglevel::DEBUG1) << "block.z = " << block.z;

  return block;
}

dim3 Device::max_grid_dim() {
  dim3 grid;
  grid.x = attribute(CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X);
  Logger(loglevel::DEBUG1) << "grid.x = " << grid.x;

  grid.y = attribute(CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y);
  Logger(loglevel::DEBUG1) << "grid.y = " << grid.y;

  grid.z = attribute(CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z);
  Logger(loglevel::DEBUG1) << "grid.z = " << grid.z;

  return grid;
}

int Device::attribute(CUdevice_attribute attrib) const {
  int pi{0};
  CUDA_SAFE_CALL(cuDeviceGetAttribute(&pi, attrib, m_device));
  return pi;
}