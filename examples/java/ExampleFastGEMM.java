import java.io.IOException;

import yacx.Device;
import yacx.Devices;
import yacx.Executor;
import yacx.FloatArg;
import yacx.HalfArg;
import yacx.IntArg;
import yacx.KernelArg;
import yacx.KernelTime;
import yacx.Options;
import yacx.PaddingArg;
import yacx.Utils;

public class ExampleFastGEMM {

	public static void main(String[] args) throws IOException {
		// Constants for shared memory calculation
		final int M = 16;
		final int N = 16;
		final int K = 16;
		// If you change this, don't forget to adjust the SHARED_MEMORY_LIMIT_64K in the
		// kernel, too.
		final boolean SHARED_MEMORY_LIMIT_64K = false;
		final int BLOCK_ROW_WARPS = 2;
		final int BLOCK_COL_WARPS = 4;
		final int WARP_ROW_TILES = 4;
		final int WARP_COL_TILES = 2;
		final int BLOCK_COL_TILES = WARP_COL_TILES * BLOCK_COL_WARPS;
		final int CHUNK_K = SHARED_MEMORY_LIMIT_64K ? 4 : 8;
		final int SKEW_HALF = 8;

		// Load Library
		Executor.loadLibrary();

		// Testdata
		int x = 4;
		int y = 3;
		int z = 2;
		float alpha = 1f;
		float beta = 1f;
		float[] aMatrix = new float[x * y];
		float[] bMatrix = new float[y * z];
		float[] cMatrix = new float[x * z];
		for (int i = 0; i < aMatrix.length; i++) {
			aMatrix[i] = i + 1;
		}
		for (int i = 0; i < bMatrix.length; i++) {
			bMatrix[i] = x * y + i + 1;
		}
		for (int i = 0; i < cMatrix.length; i++) {
			cMatrix[i] = 2 * (i + 1);
		}

		// Get the next biggest multiple of 128 for each dimension
		int m = (x % 128 == 0) ? x : (x / 128 + 1) * 128;
		int k = (y % 128 == 0) ? y : (y / 128 + 1) * 128;
		int n = (z % 128 == 0) ? z : (z / 128 + 1) * 128;

		// Get Device
		Device device = Devices.findDevice();

		// 8 Warps = 256 Threads per Block are required for the kernel to work
		int threads = 32 * 8;
		// The amount of blocks can be freely chosen but is optimal when it's equal to
		// the streaming multiprocessor count of the device
		int blocks = device.getMultiprocessorCount();

		// Compute the right amount of shared memory to request.
		// We need shared memory to hold per-CTA C and D matrix tiles, and to cache
		// per-CTA chunks of the A and B matrices.
		// Therefore, the right amount to request is the maximum of those two numbers.
		long SHMEM_SZ = Math.max(HalfArg.SIZE_BYTES * (BLOCK_COL_TILES * M) * (CHUNK_K * K + SKEW_HALF) * 2,
				M * (BLOCK_ROW_WARPS * WARP_ROW_TILES) * N * (BLOCK_COL_WARPS * WARP_COL_TILES) * FloatArg.SIZE_BYTES);

		// Calculate and print out the required and available shared memory size
		long required = SHMEM_SZ / 1024;
		long available = device.getSharedMemPerMultiprocessor() / 1024;
		System.out.println("Required shared memory size per multiprocessor: " + required + " KB");
		System.out.println("Available shared memory size per multiprocessor: " + available + " KB");

		// Check if there's enough shared memory per block available on the device for
		// this kernel
		if (required > available) {
			System.out.println("Not enough shared memory per block available on the device for this kernel! Abort!");
			System.out.println(
					"Please use the simple GEMM kernel instead or increase the amount of shared memory per block if possible!");
			System.exit(1);
		}

		// Create Arguments
		HalfArg aMatrixArg = HalfArg.create(aMatrix);
		// Kernel expects a transposed B matrix so this has to be done here
		HalfArg bMatrixArg = HalfArg.createTransposed(bMatrix, y, z);
		FloatArg cMatrixArg = FloatArg.create(cMatrix);
		FloatArg dMatrixArg = FloatArg.createOutput(x * z);
		KernelArg mArg = IntArg.createValue(m);
		KernelArg nArg = IntArg.createValue(n);
		KernelArg kArg = IntArg.createValue(k);
		KernelArg alphaArg = FloatArg.createValue(alpha);
		KernelArg betaArg = FloatArg.createValue(beta);

		// Do the padding for each input matrix if necessary
		KernelArg aMatrixArgPadding = (x == m && y == k) ? aMatrixArg
				: PaddingArg.createMatrixPadding(aMatrixArg, x, y, m, k, 0);
		KernelArg bMatrixArgPadding = (z == n && y == k) ? bMatrixArg
				: PaddingArg.createMatrixPadding(bMatrixArg, z, y, n, k, 0);
		KernelArg cMatrixArgPadding = (x == m && z == n) ? cMatrixArg
				: PaddingArg.createMatrixPadding(cMatrixArg, x, z, m, n, 0);
		KernelArg dMatrixArgPadding = (x == m && z == n) ? dMatrixArg
				: PaddingArg.createMatrixPadding(dMatrixArg, x, z, m, n, 0);

		// Load Kernel as string
		String kernelString = Utils.loadFile("kernels/fast_wmma_gemm.cu");

		// Compiler options
		Options options = Options.createOptions("--gpu-architecture=compute_70");

		// Compile and launch Kernel
		KernelTime time = Executor.launch(kernelString, "fast_wmma_gemm", options, blocks, 1, 1, threads, 1, 1,
				SHMEM_SZ, aMatrixArgPadding, bMatrixArgPadding, cMatrixArgPadding, dMatrixArgPadding, mArg, nArg, kArg,
				alphaArg, betaArg);

		// Print Result
		System.out.println("Kernel fast_wmma_gemm launched " + time.toString());
		System.out.println();
		System.out.println("aMatrix:");
		MatrixUtils.printlnMatrix(aMatrix, y);
		System.out.println("bMatrix:");
		MatrixUtils.printlnMatrix(bMatrix, z);
		System.out.println("cMatrix:");
		MatrixUtils.printlnMatrix(cMatrix, z);
		System.out.println("resultmatrix:");
		MatrixUtils.printlnMatrix(dMatrixArg.asFloatArray(), z);
	}
}