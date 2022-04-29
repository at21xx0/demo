/* 
 * 我是跨行注释
 *
 */
// 我是注释
import java.io.*;
import java.util.*;
import java.text.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class MyClass
{
	public int num;
	protected static int i=0; // 默认 0
	public String name;
	public static final String S1="hey"; // 常量
	private transient String passwd;
	private volatile boolean lock;// 从共享内存
	public MyClass(String n){
		// 构造函数
		name=n;
		i++;
		System.out.println(n+" ("+i+")");
	}
	public void Test(){
		System.out.println("Test: "+name);
	}
	public int getI()
	{
		return i;
	}
	public int getNum()
	{
		return num;
	}
	public void setNum(int i)
	{
		num=i;
	}
	public final void finalTest()
	{
		//可以被继承，不能被改写
		// public final class MyClass  {}  不可继承
	}
	public synchronized void sync()
	{
		// 同一时间只能被一个线程访问
	}
	public void print(int i)
	{
		System.out.println(i);
	}
	public void print(String s)
	{
		System.out.println(s);
	}
	public int max(int... a)
	{
		int i=a[0];
		int k;
		for(k=1;k<a.length;k++)
			if(i<a[k])
				i=a[k];
		return i;
	}
	public void errTest(int i) throws ErrTestException
	{
		if(i==0)
		{
			throw new ErrTestException();
		}
	}
	protected void finalize() throws java.lang.Throwable
	{
		super.finalize();
		System.out.println("close");
	}
}
class MyEnum
{
    enum AlphaBet{A,B,C,D,E,F};
    AlphaBet al;
}
class ErrTestException extends Exception
{
	public ErrTestException()
	{
		super();
	}
	public ErrTestException(String s)
	{
		super(s);
	}
}
class MyTest
{
	public static void Test()
	{
		System.out.println("test");
		MyEnum e=new MyEnum();
		e.al=MyEnum.AlphaBet.A;
		MyClass c1=new MyClass("c1");
		c1.num=5;
		c1.Test();
		c1.setNum(6);
		System.out.println(c1.getNum());
		// 数据类型
		boolean bool;
		byte b;
		short s;
		int i,k=6;
		long l;
		float f;
		double d=6.5;
		char c;
		String str;
		bool=true;
		System.out.println("boolean: "+bool);
		// 强制类型转换
		c=15;
		s=(short)c;
		System.out.println("short: "+s);
		// 未定义的 i
		//System.out.println("int: "+i);
		MyClass c2=new MyClass("c2");
		// 访问修饰符
		// dafault private public protected
		// 访问权限
		// public protected default private
		// 其他包 子孙类(不同包) 子孙类(同包) 同包 同类
		
		// 继承
		// public > public
		// protected > public / protected
		// private

		// 非访问修饰符
		// static
		//   静态变量  不能是局部变量
		//   静态方法  不能使用类的非静态变量
		// final
		// 被赋值后不能重新赋值
		// 常量，如 MyClass.S1
		
		// 运算符
		// 算数 + - * / % ++ --
		// 关系 == != > < >= <=
		// 位运算 | & ^ ~ << >>  
		// >>>  右位移补零
		// 逻辑 && || !
		// 赋值 += -= *= /= (%)= <<= >>= &= ^= |=
		// 条件运算符 i=(i=5)?6:5;
		// instanceof
		System.out.println(c1 instanceof MyClass);
		// 优先级
		// 循环
		i=0;
		while(i<5)
		{
			System.out.println("i: "+i);
			i++;
		}
		i=0;
		do
		{
			System.out.println("i: "+i);
			i++;
		}
		while(i<5);
		for(i=0;i<5;i++)
		{
			System.out.println("i: "+i);
		}
		int [] arr={1,5,3,6,7};
		for(int y : arr)
		{
				System.out.println(k);
		}
		System.out.println("***");
		for(k=0,i=0;i<5;i++)
		{
			if(i==2)continue;
			k++;
			if(i==3)break;
		}
		System.out.println(k);
		if(true)
			System.out.println(true);
		if(false)
			System.out.println(false);
		else if(0==1)
			System.out.println(0);
		else
		{
			System.out.println("else");
			if(1==1)
				System.out.println("next");
		}
		// switch
		i=1;
		switch(i)
		{
			case 0:
				System.out.println(i);
				break; // 可选
			case 1:
				System.out.println(i);
			case 2:
				System.out.println(i);
				break;
			default:// 默认的
				System.out.println(i);
		}
		System.out.println("Math");
		// Boolean Byte Short Integer Long Character Float Double
		Integer n1=4;
		Short n2=5;
		n1++;
		System.out.println(n1);
		System.out.println(n1.doubleValue());
		// byteValue() doubleValue() floatValue() intValue() longValue() shortValue()
		if(n1.compareTo(8)<0)
			System.out.println("<");
		if(n1.compareTo(5)==0)
			System.out.println("=");
		if(n1.compareTo(3)>0)
			System.out.println(">");
		if(n1.equals(n2))
			System.out.println("equal");
		n1=Integer.valueOf(5);
		n1=Integer.valueOf("5");
		System.out.println(n1.toString());
		System.out.println(Integer.parseInt("44",16));
		System.out.println(Math.abs(-7));
		System.out.println(Math.ceil(4.3));
		System.out.println(Math.floor(4.3));
		System.out.println(Math.rint(4.3));
		System.out.println(Math.round(4.3));
		// Math.min() Math.max() Math.pow()
		// Math.exp() Math.log() Math.sqrt() Math.sin() Math.cos() Math.tan() Math.asin() Math.acos() Math.atan() Math.atan2() Math.toDegrees() Math.toRadians() Math.random()
		
		// Character
		Character ch=new Character('a');
		// \t \b \n \r \f \' \" \\
		System.out.println(Character.isLetter('a'));
		// Character.isDigit(5) Character.isWhitespace(\t) Character.isUpperCase('a') Character.isLowerCase('a') toUpperCase toLowerCase toString
		//java.lang.Character API
		
		// String
		String s1="String1";
		String s2=new String("String2");
		String s3=s1;
		char [] s_4={'S','t','r','i','n','g','4'};
		String s4=new String(s_4);
		System.out.println(s1);
		System.out.println(s1.length());
		System.out.println(s1.concat(s2));
		System.out.println(s1+s2);
		//格式化显示
		System.out.printf("%d\n",i);
		s4=String.format("String%d",4);
		System.out.println(s1.charAt(0));
		System.out.println(s1.compareTo(s2));
		// compareToIgnoreCase() 忽略大小写
		// concat() 
		System.out.println(s1.contentEquals("String1"));
		System.out.println(s1.copyValueOf(s_4));
		System.out.println(s1.copyValueOf(s_4,1,2));
		System.out.println(s1.endsWith("ing1"));
		System.out.println(s1.equals(s3));
		// == 比较地址
			byte [] s_1;
		try{
		s_1=s1.getBytes("UTF-8");
		}catch(UnsupportedEncodingException err)
		{
			System.out.println("UnsupportedEncodingException");
		}
		char [] s_2=new char[10];
		try{
			s1.getChars(0,3,s_2,0);
		}catch(Exception err)
		{
			System.out.println("error");
		}
		System.out.println(s1.hashCode());
		System.out.println(s1.indexOf("in",1));// ("in") ('i',1) ('i')
		System.out.println(s1.intern());// 规范化表达
		// lastIndexOf()  从后面开始
		// length()
		System.out.println(s1.matches("String\\d"));// Pattern.matches(regex, str)
		System.out.println(s1.regionMatches(0,s2,0,2));// (忽略大小写) 起始偏移 字符串 偏移 length
		System.out.println(s1.replace("Str","str"));
		System.out.println(s1.replaceAll("[a-z]","X"));
		System.out.println(s1.replaceFirst("[a-z]","X"));
		for(String tmp : s1.split("r|i")) // split(reg,limit);
		{
			System.out.println(tmp);
		}
		System.out.println(s1.startsWith("t",1));
		System.out.println(s1.startsWith("t"));
		System.out.println(s1.subSequence(1,2));// 子字符串
		System.out.println(s1.substring(1,2));
		System.out.println(s1.substring(1));
		for(char tmp : s1.toCharArray())
			System.out.println(tmp);
		// toLowerCase
		// toString()
		// toUpperCase
		// s1.trim() 返回副本，忽略大小写
		System.out.println(s1.valueOf(1));
		System.out.println(s1.contains("in"));
		System.out.println(s1.isEmpty());
		StringBuilder s5=new StringBuilder(20);
		s5.append("str");
		s5.insert(2," yooo");
		s5.delete(2,3);
		System.out.println(s5);
		
		StringBuffer s6=new StringBuffer("hhhhh");// 线程安全
		s6.append("y");
		System.out.println(s6.reverse());
		//delete(int start,int end)
		//insert(int offset,int i)
		//insert(int offset,String str)
		//replace(int start,int end,String str)
		// capacity() charAt(int index) ensureCapacity(int minimumCapacity) getChars(int srcBegin,int srcEnd,char[] dst,int dstBegin) int indexOf(String str) indexOf(String str,int fromIndex) lastindexOf(String str) lastIndexOf(String str,int fromIndex) length() setCharAt(int index, char ch) setLength(int newLength) subSequence(int start, int end) substring(int start) 	String substring(int start, int end) toString()
		// 数组
		int [] intArr=new int[16];
		System.out.println("array");
		// date
		//import  java.util.*;import java.text.*;
		Date date1=new Date();
		System.out.println(date1.toString());
		Date date2=new Date();
		System.out.println(date1.after(date2));
		System.out.println(date1.before(date2));
		System.out.println(date1.clone().toString());
		System.out.println(date1.compareTo(date2));
		System.out.println(date1.equals(date2));
		System.out.println(date1.getTime());
		System.out.println(date1.hashCode());
		//setTime(long time)
		SimpleDateFormat format1=new SimpleDateFormat("yyyy-MM-dd,hh-mm-ss");
		System.out.println(format1.format(date1));
		System.out.printf("%tc %tF%n %<tD %1$tr %1$tT %1$tR",date1,date1);
		try{
			date1=format1.parse(format1.format(date2));
		}catch(ParseException err){
			System.out.println("error!");
		}
		// sleep
		//Calendar c1 = Calendar.getInstance();
		//c1.set(2009, 6 - 1, 12);
		//System.out.println(c1.YEAR()+" "+c1.MONTH());
		System.out.println(format1.format(date1));
		// import java.util.regex.Matcher; import java.util.regex.Pattern;
		Pattern r1=Pattern.compile("String\\d");
		Pattern r2=Pattern.compile("ng\\d");
		Matcher m1=r1.matcher(s1);
		Matcher m2=r2.matcher(s1);
		if(m1.find())
		{
			System.out.println(m1.group(0));
		}
		System.out.println(m1.start(0));
		System.out.println(m1.start());
		System.out.println(m1.end());
		System.out.println(m1.end(0));
		System.out.println(m1.lookingAt());
		System.out.println(m2.find());
		System.out.println(m2.matches());
		System.out.println(m2.lookingAt());// 从第一个字符匹配，不是全部
		System.out.println(m1.replaceAll(s2));
		// replaceFirst
		m1=r1.matcher(s1);
		while(m1.find())
			m1.appendReplacement(s6,s2);
		m1.appendTail(s6);
		System.out.println(s6.toString());
		// Java 方法
		c1.print(1);
		c1.print("1");
		//for(String tmp : arg)
		//	System.out.println("arg: "+tmp);
		System.out.println(c1.max(1,6,5,4,2));
		//System.in.
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		System.out.println("press c");
		try{
			c=(char)br.read();
			if(c=='c')
			{
				System.out.println("continue");
				//c=(char)System.in.read();
				//System.out.println(c);
				/*
				while(true)
				{
					c=(char)System.in.read();
					if(c==-1||c=='\n')
						break;
					System.out.write(c);
				}
				*/
				//s3=br.readLine();
				Console cons=System.console();
				s3=cons.readLine("Enter...");
				if(s3!=null)
				{
					System.out.println(s3);
					System.out.println(s3.length());
				}
				//java.util.Scanner
				Scanner scan=new Scanner(System.in);
				if(scan.hasNext())
				{
				 // hello world
				 // hello
					System.out.println(scan.next());
				}
				if(scan.hasNextLine())
				{
					System.out.println(scan.nextLine());
				}
				scan.close();
			}
			//File f0=new File("a.txt");
			OutputStream f1=new FileOutputStream("a.txt");//FileOutStream(f0);
			//f1.write('a');
			f1.write(s1.getBytes());
			f1.close();
			//f1.finalize();
			InputStream f2=new FileInputStream("a.txt");
			byte [] b1=new byte[64];
			byte [] b2=new byte[64*2];
			//if(f2.read(b1)==-1)// 结束
			System.out.println(f2.read(b1));
			System.out.println(new String(b1));
			if(f2.read(b1)==-1)//结束
				System.out.println(f2.available());//不收阻塞读字节数
			f2.close();
			ByteArrayInputStream f3=new ByteArrayInputStream(b1);//(b2,int off,int len);
			System.out.println((char)f3.read());
			f3.close();
			// read(byte [] r,int off,int len); available() mark(int read) skip(long n)
			OutputStream f4=new ByteArrayOutputStream(32);//32字节缓冲区(默认)
			f4.write(s1.getBytes(),0,3);
			//f4.reset();//清零
			System.out.println(f4.toString());
			//toByteArray()
			//f4.writeTo(OutputStream f1);
			//DataInputStream f5=new DataInputStream(new FileInputStream());
			//read(byte [] r,int off,int len); read(byte []) readBoolean() readByte() readShort() readInt() readLine
			//DataOutputStream f6=new DataOutputStream(new FileOutputStream("a.txt"));
			File f8=new File("");
			String pwd=f8.getCanonicalPath();// 路径
			System.out.println(f8.getAbsolutePath());// 绝对路径
			File f7=new File("folder");
			f7.mkdir();
			f7.mkdirs();// 新建
			System.out.println(f7.getName());
			System.out.println(f7.getParent());
			System.out.println(f7.getPath());
			System.out.println(f7.isAbsolute());
			System.out.println(f7.isDirectory());
			System.out.println(f7.lastModified());// 最后修改时间
			// createNewFile() 不存在时创建
			// deleteOnExit() 退出时删除
			// list() 返回文件名，文件夹名字符串数组
			// setLastModified(long tm);
			// setReadOnly();
			// public static File createTempFile(String prefix, String suffix, File directory) throws IOException
			// public static File createTempFile(String prefix, String suffix) throws IOException
			// 	public int compareTo(File pathname)
			// 	public int compareTo(object o)
			// equals(Object obj) toString()
			f7.delete();
			System.out.println(f7.exists());
			//f7=f8.getParentFile();
			f8=new File("a.txt");
			f8.renameTo(new File("a"));
			f7=new File(".");
			for(File temp:f7.listFiles())
			{
				System.out.print(temp.getName());
				System.out.write(' ');
				if(temp.isFile())
					System.out.print(temp.length()+" ");
				if(temp.canRead())
					System.out.write('r');
				if(temp.canWrite())
					System.out.write('w');
				System.out.write('\n');
			}
			f8.delete();
			//System.out.println(System.getProperty("user.dir"));
			
		}catch(IOException err){
			System.out.println("err");
		}catch(Exception err){
			System.out.println("err");
		}
		try{
			c1.errTest(0);
		}catch(ErrTestException err){
			//System.out.println(err.getMessage());
			//System.out.println(err.getCause());
			System.out.println(err.toString());
			err.printStackTrace();
			//public StackTraceElement [] getStackTrace()
			//public Throwable fillInStackTrace()
		}finally{
			System.out.println("next");
		}

		
	}
}
abstract class Ab // 必须 abstract
{
	public abstract int AA(int a); // 由子类提供
}

public class j1
{
	public static void main(String[] args)
	{
		System.out.println("h");
        MyTest.Test();
	}
}

