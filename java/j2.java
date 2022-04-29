


class ClassA{
	public int count;
	public ClassA()
	{
		count=0;
	}
	public ClassA(int i)
	{
		// 不同参数，构造函数的重载
		count=i;
	}
	public void printCount()
	{
		System.out.println(count);
	}
	public final void show(ClassA a)
	{
		// 多态
		System.out.print("showClass");
		if( a instanceof ClassB)
			System.out.println("B");
		else if( a instanceof ClassC)
			System.out.println("C");
		else if( a instanceof ClassA)
			System.out.println("A");
	}
}
class ClassB extends ClassA
{
	public final int getCount()//final 不可修改
	{
		return count;
	}
}
class ClassC extends ClassA
{
	public ClassC()
	{
		super();// 指向父 构造器
	}
	public ClassC(int i)
	{
		super(i);
	}
	public void printCount()
	{
		// 重写
		System.out.print("Count: ");
		super.printCount();
	}
	public void plus()
	{
		this.count++;// 指向本身
	}
}
/*
class ClassD implements ClassA,ClassB
{
	// 类似多继承
}
*/
abstract class A1
{
	int i;
	public abstract int getI();
}
class A2 extends A1
{
	public int getI()
	{
		return i;
	}
}

class ClassP
{
	private static int count;//设置 private
	private synchronized static void plus()
	{
		count++;
	}
	public ClassP()
	{
		plus();
	}
	public final static int getCount()
	{
		return count; // 设置函数
	}
}
interface I1//extends I // implements
{
	public final static int i=5;
	public void g();
}
class I2 implements I1
{
	public void g()
	{
		System.out.println(i);
	}
}
enum Color
{
	RED,GREEN,BLUE
}







public class j2{
	public static void main(String[] args)
	{
		System.out.println("hello, world!");
		ClassA a1=new ClassA();
		a1.printCount();
		//继承
		ClassB b1=new ClassB();
		b1.printCount();
		//ClassB b2=new ClassB(5); //error
		//重载
		ClassC c3=new ClassC(5);
		//重写
		c3.printCount();
		//多态
		a1.show(new ClassA());
		a1.show(new ClassB());
		a1.show(new ClassC());
		//抽象
		//A1 aa=new A1(); //error
		A2 aa=new A2();
		System.out.println(aa.getI());
		// 封装
		ClassP p1=new ClassP();
		p1=new ClassP();
		System.out.println(p1.getCount());
		// 接口
		I2 i=new I2();
		i.g();
		Color c1=Color.RED;
		System.out.println(c1);
		for(Color c2:Color.values())
			System.out.println(c2+": "+c2.ordinal());
		switch(c1)
		{
			case RED:
			case GREEN:
			case BLUE:
				System.out.println(c1);
				break;
			default:
				System.out.println("UNKONWN");
		}
		System.out.println(Color.valueOf("RED"));
		// 包
		
	}
}
