#include "yacx_Kernel.h"
#include "Handle.h"
#include "KernelArgJNI.hpp"
#include "KernelUtils.h"
#include "../../include/yacx/Kernel.hpp"
#include "../../include/yacx/KernelArgs.hpp"
#include "../../include/yacx/Devices.hpp"
#include "../../include/yacx/KernelTime.hpp"

#include <string>
#include <limits.h>

using yacx::Kernel, yacx::KernelArg, yacx::KernelArgs, yacx::KernelTime, yacx::Device, yacx::Devices,
      jni::KernelArgJNI;

void Java_yacx_Kernel_configureInternal(JNIEnv *env, jobject obj, jint jgrid0, jint jgrid1, jint jgrid2, jint jblock0, jint jblock1, jint jblock2, jlong jshared)
{
    BEGIN_TRY
        CHECK_BIGGER(jgrid0, 0, "illegal size for grid0", )
        CHECK_BIGGER(jgrid1, 0, "illegal size for grid1", )
        CHECK_BIGGER(jgrid2, 0, "illegal size for grid2", )
        CHECK_BIGGER(jblock0, 0, "illegal size for block0", )
        CHECK_BIGGER(jblock1, 0, "illegal size for block1", )
        CHECK_BIGGER(jblock2, 0, "illegal size for block2", )
        CHECK_BIGGER(jshared, -1, "illegal size for shared memory", )
        CHECK_BIGGER(UINT_MAX, jshared - 1, "illegal size for shared memory", )

        auto kernelPtr = getHandle<Kernel>(env, obj);
    	CHECK_NULL(kernelPtr, )

        dim3 grid{static_cast<unsigned int> (jgrid0), static_cast<unsigned int> (jgrid1), static_cast<unsigned int> (jgrid2)};
        dim3 block{static_cast<unsigned int> (jblock0), static_cast<unsigned int> (jblock1), static_cast<unsigned int> (jblock2)};
        unsigned int shared = static_cast<unsigned int> (jshared);

        kernelPtr->configure(grid, block, shared);
    END_TRY("configuring Kernel")
}

jobject Java_yacx_Kernel_launchInternal___3Lyacx_KernelArg_2(JNIEnv *env, jobject obj, jobjectArray jArgs)
{
    BEGIN_TRY
        CHECK_NULL(jArgs, NULL);

        auto kernelPtr = getHandle<Kernel>(env, obj);
        CHECK_NULL(kernelPtr, NULL)

        auto args = getArguments(env, jArgs);
        if (args.empty()) return NULL;

        auto kernelTimePtr = kernelPtr->launch(KernelArgs{args});

        return createJavaKernelTime(env, &kernelTimePtr);
    END_TRY_R("launching Kernel", NULL)
}

jobject Java_yacx_Kernel_launchInternal__Lyacx_Device_2_3Lyacx_KernelArg_2(JNIEnv *env, jobject obj, jobject jdevice, jobjectArray jArgs)
{
    BEGIN_TRY
        CHECK_NULL(jArgs, NULL);
        CHECK_NULL(jdevice, NULL);

        auto kernelPtr = getHandle<Kernel>(env, obj);
        CHECK_NULL(kernelPtr, NULL);
        auto devicePtr = getHandle<Device>(env, jdevice);
        CHECK_NULL(devicePtr, NULL);

        auto args = getArguments(env, jArgs);
        if (args.empty()) return NULL;

        return launchInternal(env, kernelPtr, *devicePtr, args);
    END_TRY_R("launching Kernel on specific device", NULL)
}
