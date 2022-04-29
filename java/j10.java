
/*
* doc
* @author u0_a479
* @version 1.0
* @docRoot /
*/

import java.util.ArrayList;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Optional;

import java.time.LocalDate;
import java.time.LocalTime;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.ZonedDateTime;
import java.time.ZoneId;

import java.util.Base64;
import java.util.UUID;
import java.io.UnsupportedEncodingException;



interface Test{
	Integer test(Integer a,Integer b);
}
class T2{
	public T2(Integer a)
	{
		System.out.println(a);
	}
}
interface T3
{
	public void print(Object o);
	default void p2(Object o){//默认实现
		System.out.println(o);
	}
	static void p3(Object o){
		System.out.println(o);
	}
}
class T4 implements T3{
	public void print(Object o){
		System.out.println(o);
	}
}
class T5 implements T3{
	public void print(Object o){
		System.out.println(o);
	}
	public void p2(Object o){
		System.out.println("??? "+o);
	}
}

public class j10
{
	public static void test(Integer a,Integer b,Test t)
	{
		System.out.println(t.test(a,b));
	}
	public static Integer compareTo(Integer a,Integer b)
	{
		return a.compareTo(b);
	}
	public static void main(String[] args)
	{
		Integer a=5,b=10;
		Integer c=47;
		Test t=(i,u)->i.compareTo(u);
		System.out.println(a.compareTo(b));
		System.out.println(t.test(a,b));
		t=(i,u)->{return i.compareTo(u);};
		System.out.println(t.test(a,b));
		j10.test(a,b,(i,u)->i+u);
		j10.test(a,b,(i,u)->i+u+c);
		// x-> x*2
		// ()->5
		ArrayList<String> a1=new ArrayList<String>();
		a1.add("aaa");
		a1.add("bbb");
		a1.add("ccc");
		a1.forEach(System.out::println);
		j10.test(a,b,j10::compareTo);
		Function<Integer,T2> f1=T2::new;
		Function<Integer,Integer> f2=(i)->i+2;
		Function<Integer,Integer> f3=(i)->i*2;
		f1=(Integer i)->new T2(i);
		T2 tt=f1.apply(a);
		System.out.println(f2.compose(f3).apply(a));
		System.out.println(f2.andThen(f3).apply(a));
		System.out.println(f2.andThen(Function.identity()).apply(a));
		// Function.identify() t->t;

		Predicate<Integer> f5=(n)->n>5;
		System.out.println(f5.test(6));

		new T4().print("hhh");
		new T4().p2("hhh");
		new T5().p2("x");
		T3.p3("xx");
		Random r = new Random();
		r.ints().limit(10).forEach(System.out::println);
		a1.forEach(System.out::println);
		a1.add("xxx");
		a1.add("000");
		a1.add("kkk");
		a1.add("uuu");
		a1.add("u");
		a1.stream().limit(10).filter(s->s.length()==3).sorted().forEach(System.out::println);
		List<String> l1=a1.parallelStream().sorted().collect(Collectors.toList());
		Integer n1=null;
		Integer n2=5;
		Optional<Integer> o1=Optional.ofNullable(n1);
		//Optional.empty()
		// of Exception
		Optional<Integer> o2=Optional.ofNullable(n2);
		System.out.println(o1.isPresent());
		System.out.println(o2.isPresent());
		System.out.println(o1.orElse(new Integer(7)));

		LocalDateTime currentTime=LocalDateTime.now();
		System.out.println("current: "+currentTime);
		LocalDate date1=currentTime.toLocalDate();
		System.out.println("date1: "+date1);
		Month month=currentTime.getMonth();
		int day=currentTime.getDayOfMonth();
		int sec=currentTime.getSecond();
		System.out.println("mouth: "+month+"\nday: "+day+"\nsecond: "+sec);
		LocalDateTime date2 = currentTime.withDayOfMonth(10).withYear(2012);
		LocalDate date3 = LocalDate.of(2014, Month.DECEMBER, 12);
		System.out.println("date3: " + date3);
		// 22 小时 15 分钟
		LocalTime date4 = LocalTime.of(22, 15);
		System.out.println("date4: " + date4);
		// 解析字符串
		LocalTime date5 = LocalTime.parse("20:15:30");
		System.out.println("date5: " + date5);
		ZonedDateTime d1 = ZonedDateTime.parse("2015-12-03T10:15:30+05:30[Asia/Shanghai]");
		System.out.println("d1: " + d1);
		ZoneId id = ZoneId.of("Europe/Paris");
		System.out.println("ZoneId: " + id);
		ZoneId currentZone = ZoneId.systemDefault();
		System.out.println("当期时区: " + currentZone);

		//B
		try{
			String b1=Base64.getEncoder().encodeToString("test".getBytes("utf-8"));
			System.out.println(b1);
			byte[] b2=Base64.getDecoder().decode(b1);
			System.out.println(new String(b2));
			//getUrlEncoder
			System.out.println(UUID.randomUUID().toString());
			//getMimeEncoder
			//getMimeDecoder
		}catch(UnsupportedEncodingException err){
			err.printStackTrace();
		}





		


	}
}
