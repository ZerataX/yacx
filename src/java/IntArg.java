public class IntArg extends KernelArg {
	public static IntArg create(int ...ints) {
		return createInternal(ints, false);
	}
	
	public static IntArg create(int[] ints, boolean download) {
		assert(ints != null && ints.length > 0);
		
		return createInternal(ints, download);
	}
	
	private static native IntArg createInternal(int[] ints, boolean download);
	
	
	public static IntArg createOutput(int size) {
		assert(size > 0);
		
		return createOutputInternal(size);
	}
	
	private static native IntArg createOutputInternal(int size);
	
	IntArg(long handle) {
		super(handle);
	}
	
	public native int[] asIntArray();
	
	@Override
    public String toString(){
        return "IntArg " + super.toString();
    }
}
