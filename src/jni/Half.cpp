#include "Half.hpp"

#include "../../include/yacx/Kernel.hpp"
#include "../../include/yacx/Program.hpp"
#include "../../include/yacx/Source.hpp"

#include <stdlib.h>

using yacx::Source, yacx::KernelArg, yacx::Kernel, yacx::Device, yacx::Options;

unsigned int maxGridSize = 0;
unsigned int maxBlockSize = 0;
yacx::Kernel* kernelFtoH = NULL;
yacx::Kernel* kernelHtoF = NULL;

void initKernel(){
    Device dev;

    dim3 grid;
    dev.max_grid_dim(&grid);
    maxGridSize = grid.x;
    dev.max_block_dim(&grid);
    maxBlockSize = grid.x;

    Source source{
            "#include <cuda_fp16.h>\n"
            "extern \"C\" __global__\n"
                "void floatToHalf(float* floats, half* out, unsigned int n) {\n"
                "  for (int i = threadIdx.x+blockIdx.x*blockDim.x; i < n; i += gridDim.x*blockDim.x){\n"
                "    out[i] = __float2half(floats[i]);\n"
                "  }\n"
                "}"};

    kernelFtoH = new Kernel{source.program("floatToHalf").compile()};

    Source source2{
        "#include <cuda_fp16.h>\n"
                "extern \"C\" __global__\n"
        		"void halfToFloat(half* halfs, float* out, unsigned int n) {\n"
        		"  for (unsigned int i = threadIdx.x+blockIdx.x*blockDim.x; i < n; i += gridDim.x*blockDim.x){\n"
        		"    out[i] = __half2float(halfs[i]);\n"
        		"  }\n"
        		"}"};

    kernelHtoF = new Kernel{source2.program("halfToFloat").compile()};
}

void yacx::convertFtoH(void* floats, void* halfs, unsigned int length){
    if (kernelFtoH == NULL){
        initKernel();
    }

    std::vector<KernelArg> args;
    args.emplace_back(KernelArg{floats, length*sizeof(float), false, true, true});
    args.emplace_back(KernelArg{halfs, length*sizeof(float)/2, true, false, true});
    args.emplace_back(KernelArg{const_cast<unsigned int*>(&length)});

    unsigned int grids = length/maxBlockSize+1;
    dim3 grid(grids < maxGridSize ? grids : maxGridSize);
    dim3 block(maxBlockSize);

    kernelFtoH->configure(grid, block).launch(args);
}

void yacx::convertHtoF(void* halfs, void* floats, unsigned int length){
    if (kernelHtoF == NULL){
        initKernel();
    }

    std::vector<KernelArg> args;
    args.emplace_back(KernelArg{halfs, length*sizeof(float)/2, false, true, true});
    args.emplace_back(KernelArg{floats, length*sizeof(float), true, false, true});
    args.emplace_back(KernelArg{const_cast<unsigned int*>(&length)});

    unsigned int grids = length/maxBlockSize+1;
    dim3 grid(grids < maxGridSize ? grids : maxGridSize);
    dim3 block(maxBlockSize);

    kernelHtoF->configure(grid, block).launch(args);
}
