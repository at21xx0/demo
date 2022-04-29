
//java 9
/*
* module
* jshell
* javadoc
* 
*/
import java.util.HashSet;
import java.util.Set;
import java.util.Collection;
import java.util.Collections;

import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.time.ZoneId;
import java.io.IOException;
import java.util.stream.IntStream;

import java.io.BufferedReader;
import java.io.StringReader;
import java.io.Reader;

import java.util.Optional;
import java.util.function.Supplier;




//interface test{
	//
	//常量 抽象方法 默认方法 静态方法 私有方法 私有静态方法
//}

public class h
{
	public static String readLine1(String fn){
		/* 
		* @since 弃用版本
		* @Deprecated 不在使用方法
		* @forRemoval 迁移
		*/
		Reader r1=new StringReader(fn);
		BufferedReader r2=new BufferedReader(r1);
		try(BufferedReader r3=r2)
		{
			return r3.readLine();
		//try(r2){return r2.readLine();//java9
		}catch(IOException err){
			err.printStackTrace();
		}
		return "";
	}
	public static void main(String[] args)
	{
		Set<String> s1=new HashSet<String>();
		s1.add("aaa");
		s1.add("aa");
		s1.add("bbb");
		s1=Collections.unmodifiableSet(s1);
		System.out.println(s1);
		Set<String> s2=Set.of("hhhh","mmm","kkk");
		try{
			ProcessBuilder pb=new ProcessBuilder("/root/j11/program");
			Process p=pb.start();
			ProcessHandle.Info info=p.info();
			System.out.println("pid: "+p.pid());
			System.out.printf("Command line : %s%n", info.commandLine().orElse("null"));
			System.out.printf("Start time: %s%n",info.startInstant().map(i -> i.atZone(ZoneId.systemDefault()).toLocalDateTime().toString()).orElse("null"));
			System.out.printf("Arguments : %s%n",info.arguments().map(a -> Stream.of(a).collect(Collectors.joining(" "))).orElse("null"));
			System.out.printf("User : %s%n", info.user().orElse("null"));
		}catch(IOException err){
			err.printStackTrace();
		}
		Stream.of("aa","bb","cc","kkk","").takeWhile(u->!u.isEmpty()).dropWhile(u->u.length()==3).forEach(System.out::println);
		//ofNullable
		IntStream.iterate(3, x -> x < 10, x -> x+ 3).forEach(System.out::println);
		System.out.println(readLine1("test\nhello\nworld"));
		
		Optional o1=Optional.ofNullable(null);
		Optional o2=Optional.ofNullable(5);
		Optional o3=Optional.ofNullable(s2);
		o3.stream().forEach(System.out::println);
		o3.ifPresentOrElse(x->System.out.println(x),()->System.out.println("null"));
		Supplier<Optional<Integer>> n2 = () -> Optional.of(0);
		System.out.println(o1.or(n2));
		System.out.println(o2.or(n2));




		


	}
}
