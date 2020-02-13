#include "Half.hpp"

using yacx::Source, yacx::KernelArg, yacx::Kernel, yacx::Device, yacx::Options;

unsigned int maxGridSize = 0;
yacx::Kernel* kernelFtoH = NULL;
yacx::Kernel* kernelHtoF = NULL;

void convertFtoH(void* floats, void* halfs, unsigned int length){
    if (kernelFtoH == NULL){
        initKernel();
    }

    std::vector<KernelArg> args;
    args.emplace_back(KernelArg{floats, length*sizeof(float), false, true, true});
    args.emplace_back(KernelArg{halfs, length*sizeof(float)/2, true, false, true});
    args.emplace_back(KernelArg{const_cast<unsigned int*>(&length)});

    dim3 grid(length < maxGridSize ? length : maxGridSize);
    dim3 block(1);

    kernelFtoH->configure(grid, block).launch(args);
}

void convertHtoF(void* halfs, void* floats, unsigned int length){
    if (kernelHtoF == NULL){
        initKernel();
    }

    std::vector<KernelArg> args;
    args.emplace_back(KernelArg{halfs, length*sizeof(float)/2, false, true, true});
    args.emplace_back(KernelArg{floats, length*sizeof(float), true, false, true});
    args.emplace_back(KernelArg{const_cast<unsigned int*>(&length)});

    dim3 grid(length < maxGridSize ? length : maxGridSize);
    dim3 block(1);

    kernelHtoF->configure(grid, block).launch(args);
}

void initKernel(){
    Device dev;

    dim3 grid;
    dev.max_grid_dim(&grid);
    maxGridSize = grid.x;

    Options options;
    options.insert("--gpu-architecture=compute_60");

    Source source{
            "#include <cuda_fp16.h>\n"
                "extern \"C\" __global__\n"
        		"void floatToHalf(float* floats, half* out, unsigned int n) {\n"
        		"  for (unsigned int i = threadIdx.x; i < n; i += blockDim.x){\n"
        		"    out[i] = __float2half(floats[i]);\n"
        		"  }\n"
        		"}"};

    kernelFtoH = new Kernel{source.program("floatToHalf").compile(options)};

    Source source2{
        "#include <cuda_fp16.h>\n"
                "extern \"C\" __global__\n"
        		"void halfToFloat(half* halfs, float* out, unsigned int n) {\n"
        		"  for (unsigned int i = threadIdx.x; i < n; i += blockDim.x){\n"
        		"    out[i] = __half2float(halfs[i]);\n"
        		"  }\n"
        		"}"};

    kernelHtoF = new Kernel{source2.program("halfToFloat").compile(options)};
}