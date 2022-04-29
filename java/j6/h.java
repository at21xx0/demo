
import java.io.*;


public class h
{
	public native void test();
	static{
		//System.setProperty("java.library.path",System.getProperty("user.dir"));
		System.loadLibrary("test");
	}
	public static void main(String[] args)
	{
		new h().test();
	
	}
	
}
