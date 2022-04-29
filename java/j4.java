
import java.util.Vector;
import java.util.Enumeration;
import java.util.BitSet;
import java.util.*;
import java.io.*;


class C3<T>
{
	public C3(T t)
	{
		System.out.println(t);
	}
}
class TestB implements java.io.Serializable
{
	public int i;
}
public class j4
{
	public static void enumPrint(Enumeration e)
	{
		while(e.hasMoreElements())
			System.out.println(e.nextElement());
	}
	public static <E> void f1(E [] arr)
	{
		System.out.println("f1");
		for(E e:arr)
			System.out.println(e);

	}
	public static void f2(ArrayList<?> arr)
	{//List<String>  List<Integer>
		System.out.println("f2");
		System.out.println(arr.size());

	}
	public static void main(String[] args)
	{
			System.out.println("hello, world!\n");
      Enumeration<String> days;
      Vector<String> dayNames = new Vector<String>();
      dayNames.add("Sunday");
      dayNames.add("Monday");
      dayNames.add("Tuesday");
      dayNames.add("Wednesday");
      dayNames.add("Thursday");
      dayNames.add("Friday");
      dayNames.add("Saturday");
      days = dayNames.elements();
      while (days.hasMoreElements()){
         System.out.println(days.nextElement()); 
      }
		
		BitSet b1=new BitSet(16);//
		BitSet b2=new BitSet(16);
		System.out.println(b1.isEmpty());
		b1.set(0,true);//b1.set(0);
		b2.set(0,16,true);
		b1.and(b2);// &
		b1.or(b2);// |
		//b1.
		b1.xor(b2);// 
		System.out.println(b1.nextSetBit(0));// 返回 off 后为true 索引
		System.out.println(b1.nextClearBit(0));
		System.out.println(b1.intersects(b2));// b1 后为 true

		System.out.println(b1.length());
		System.out.println(b1.size());
		System.out.println(b1.toString());
		System.out.println(b1.hashCode());
		System.out.println(b1.get(0));
		b1=b2.get(0,4);
		//b1.clone();
		System.out.println(b1.equals(b2));
		b1.clear();//所有位 false
		b1.clear(5);
		b1.clear(5,6);
		System.out.println(b1.cardinality());//true 位数
		// flip andNot


		//Vector 向量
		Vector<String> v1=new Vector<String>();
		v1.add("xxx");
		v1.add(1,"xx");
		//v1.addAll(int index,Collection c);
		v1.addElement("x");
		System.out.println(v1.capacity());
		Vector<String> v2=(Vector)v1.clone();
		v1.clear();//删除所有
		System.out.println(v2.contains("xxx"));
		v1.add("xx");
		System.out.println(v2.containsAll(v1));
		String [] a3=new String[16];
		v2.copyInto(a3);
		System.out.println(v2.elementAt(0));
		// v2.elements() 返回枚举
		v2.ensureCapacity(32);//增大容量
		System.out.println(v1.equals(v2));
		System.out.println(v1.firstElement());
		System.out.println(v1.get(0));
		System.out.println(v1.hashCode());
		System.out.println(v1.indexOf("xx"));//返回索引
		System.out.println(v1.indexOf("xx",0));//开始
		System.out.println(v1.get(0));
		v1.insertElementAt("xxx",0);
		System.out.println(v1.lastElement());
		System.out.println(v1.isEmpty());
		//System.out.println(v1.lastIndexOf("xx"));//lastIndexOf(Object o,int index);
		v1.remove(1);
		v2.removeAll(v1);
		//v1.removeAllElements();//移除全部组件，大小0
		v1.removeElementAt(0);
		//v2.removeRange(int from,int to);
		//v1.retainAll(v2);// 保留
		v2.set(0,"xxxx");// 替换
		v2.setElementAt("xxxxx",0);
		//v2.setSize(128);
		System.out.println(v2.size());
		System.out.println(v2.subList(0,v2.size()));
		v2.add("aa");
		for(Object s:v2.toArray())
			System.out.println(s);
		Object [] o1=new Object[10];
		o1=v2.toArray(o1);
		System.out.println(v2.toString());
		//v2.trimToSize(86);//微调

		Stack<String> s1=new Stack<String>();
		System.out.println(s1.empty());
		//s1.add("v1"); // 包含Vector
		s1.push("v1");
		s1.push("v2");
		s1.push("v3");
		s1.push("v4");
		System.out.println(s1.peek());//查看顶部
		System.out.println(s1.peek());//查看顶部
		
		System.out.println(s1.pop());//查看最后一个，并删除
		System.out.println(s1.search("v3"));
		
		//Dictionary d1=new Dictionary();
		//System.out.println(d1.isEmpty());
		//Enumeration elements( )
		//Object get(Object key)
		//boolean isEmpty( )
		//Enumeration keys( )
		//Object put(Object key, Object value)
		//Object remove(Object key)
		//int size( )
		
		//Map m1=new HashMap();
		Map<String,Integer> m1=new HashMap<String,Integer>();
		m1.put("v1",1);
		m1.put("v2",2);
		m1.put("v3",3);
		System.out.println(m1);
		m1.clear();
		System.out.println(m1.isEmpty());
		m1.put("v4",4);
		m1.put("v6",6);
		m1.put("v5",5);
		System.out.println(m1.containsKey("v4"));
		//Set entrySet()
		for(String key : m1.keySet())
		{
			System.out.println(key);
		}
		System.out.println(m1.get("v4"));
		System.out.println(m1.hashCode());
		Map m2=new HashMap();
		m1.putAll(m1);
		System.out.println(m1.equals(m2));
		m1.remove("v4");
		System.out.println(m1.size());
		System.out.println(m1.values());
		System.out.println(m1.entrySet());
		
		Hashtable h1=new Hashtable();//(int size) (int size,float fillRatio) (map m)
		//clear() clone() isEmpty()
		h1.put("hhh",9);
		h1.put("v9",9);
		System.out.println(h1.contains(9));
		System.out.println(h1.containsKey("v9"));
		System.out.println(h1.containsValue(9));
		enumPrint(h1.elements());
		enumPrint(h1.keys());
		//h1.rehash();
		//remove(Object key) toString() size()
		
		//Properties	
		Properties p1=new Properties();
		p1.setProperty("PATH","/bin");
		p1.setProperty("PWD","/root/j4");
		//Set s1=
		enumPrint(p1.propertyNames());
		System.out.println(p1.getProperty("PWD"));
		try{
			p1.store(new FileOutputStream("a.properties"),"a");
			//p1.load(new FileInputStream("a.properties"));
			p1.list(System.out);
		}catch(Exception err){
			System.out.println("error");
		}
		
		ArrayList<String> a1=new ArrayList<String>();
		a1.add("v1");
		a1.add("v2");
		a1.add("v3");
		a1.add("v4");
		a1.add("v5");
		System.out.println(a1.get(1));
		a1.remove(3);
		a1.remove(0);
		System.out.println(a1.size());
		for(String s:a1)
			System.out.println(s);
		a1.add("v4");
		Collections.sort(a1);
		// add() addAll() clear() clone() contains() get() indexOf() removeAll() size() isEmpty() subList() set() sort() toArray() toString() ensureCapacity() lastIndexOf() retainAll() containsAll() trimToSize() removeAll() replaceAll() removeIf() forEach()
		//
		



		Iterator<String> i1=a1.iterator();
		while(i1.hasNext())
		{
			System.out.println(i1.next());
			i1.remove();
		}
		for(String s:a1)
			System.out.println(s);
		String [] a2=new String[5];
		a1.toArray(a2);
		
		//Iterator<Map.Entry<String, String>> i2 = m1.entrySet().iterator();
		for(Map.Entry<String,Integer> entry:m1.entrySet())
			System.out.println(entry.getKey()+": "+entry.getValue());
		//for(Integar i : m1.values())
		
		// 链表
		LinkedList<String> l1=new  LinkedList<String>();
		l1.add("v7");
		l1.add("v6");
		l1.add(1,"v10");
		System.out.println(l1.addAll(a1));
		//System.out.println(l1.addAll(1,a1));
		for(String s:l1)
			System.out.println(s);
		l1.addFirst("v0");
		l1.addLast("v9");
		System.out.println(l1.offer("v11"));
		l1.remove("v0");
		l1.remove("v9");
		l1.removeFirst();
		l1.removeLast();
		l1.add("x1");
		l1.add("x2");
		l1.add("x3");
		l1.add("x4");
		l1.add("x5");
		System.out.println(l1.remove());
		System.out.println(l1.poll());
		System.out.println(l1.contains("x4"));
		System.out.println(l1.get(1));
		//getFirst() getFast()
		//indexOf(Object o) lastIndexOf(Object o)
		//peek() peekFirst() element() peekLast() 
		//set(int index,E element)
		// descendingIterator()
		//public ListIterator listIterator(int index)
		//public Object[] toArray()
		//public T[] toArray(T[] a)
		l1.clear();

		HashSet<String> s3=new HashSet<String>();
		s3.add("v1");
		s3.add("v2");
		s3.add("v3");
		System.out.println(s3.add("v3"));
		System.out.println(s3.contains("v3"));
		s3.remove("v3");
		System.out.println(s3.size());
		//for(String s:s3)
		//	System.out.println(s);
		//

		//Object()
		//clone() equals() finalize() getClass() hashCode() 
		//notify() 唤醒该对象上等待的线程
		//notifyAll()
		//toString()
		//wait() 等notify() 等方法调用
		//wait(long tm)
		//wait(long tm,int nanos)  加上纳秒
		
		/*泛型
		* E Element 集合
		* T Type
		* K Key	
		* V Value
		* N Number
		* ?
		*/
		f1(a1.toArray());
		f2(a1);
		C3 c3=new C3("next");
		
		// 序列化
		TestB o5=new TestB();
		o5.i=5;
		try{
			FileOutputStream o3=new FileOutputStream("a.ser");
			ObjectOutputStream o4=new ObjectOutputStream(o3);
			o4.writeObject(o5);
			o4.close();
			o3.close();
			o5=null;
			FileInputStream i3=new FileInputStream("a.ser");
			ObjectInputStream i4=new ObjectInputStream(i3);
			o5=(TestB)i4.readObject();
			i4.close();
			i3.close();
			System.out.println(o5.i);
		}catch(Exception e){
			e.printStackTrace();
		}

		
		
		
		
	}
}
