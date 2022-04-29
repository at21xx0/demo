
import java.util.concurrent.FutureTask;
import java.util.concurrent.Callable;

class ThreadTest implements Runnable{
	private Thread t;
	private String threadName;
	public ThreadTest(String name)
	{
		this.threadName=name;
		System.out.println("create: "+this.threadName);
	}
	public void start()
	{
		System.out.println("start: "+threadName);
		if(t==null)
		{
			t=new Thread(this, threadName);
			t.start();
		}
		
	}
	public void run()
	{
		System.out.println("run: "+threadName);
		for(int i=0;i<10;i++)
		{
			try{
			Thread.sleep(1);
			}catch(Exception err){
				err.printStackTrace();
			}
			System.out.println(threadName);
		}
		System.out.println("exit: "+threadName);
	}
}
class ThreadTest2 extends Thread{
	private Thread t;
	private String threadName;
	public ThreadTest2(String name)
	{
		this.threadName=name;
		System.out.println("create: "+this.threadName);
	}
	public void start()
	{
		System.out.println("start: "+threadName);
		if(t==null)
		{
			t=new Thread(this, threadName);
			t.start();
		}
		
	}
	public void run()
	{
		System.out.println("run: "+threadName);
		for(int i=0;i<10;i++)
		{
			try{
			Thread.sleep(1);
			}catch(Exception err){
				err.printStackTrace();
			}
			System.out.println(threadName);
		}
		System.out.println("exit: "+threadName);
	}
}
class ThreadTest3 implements Callable<Integer>{
	public static void test(){
		ThreadTest3 t=new ThreadTest3();
		FutureTask<Integer> f=new FutureTask<>(t);
		try{
			new Thread(f,"call").start();
			//f.cencel(false);// 不中断线程
			//f.cencel(true);//中断线程
			System.out.println(f.get());
		}catch(Exception err){
			err.printStackTrace();
		}
	}
	//@override
	public Integer call() throws Exception{
		System.out.println(Thread.currentThread().getName());
		return 1;
	}
}



public class j8
{
	public static void main(String[] args)
	{
		System.out.println("hello, world!\n");
		ThreadTest p1=new ThreadTest("p1");
		ThreadTest p2=new ThreadTest("p2");
		p1.start();
		p2.start();
		ThreadTest2 p3=new ThreadTest2("p2");
		p3.setName("p3");
		p3.setPriority(5); // 优先级 1-10
		p3.setDaemon(true);// 守护线程或用户线程
		p3.start();
		new Thread(){
			@Override
			public void run()
			{
				System.out.println("run");
			}
		}.start();
		System.out.println(p3.isAlive());
		try{
			p3.join(1);//毫秒
		}catch(Exception err){
			err.printStackTrace();
		}
		p3.interrupt();
		Thread.yield();// 暂停
		try{
		Thread.sleep(500);
		}catch(Exception err){
			err.printStackTrace();
		}
		System.out.println(Thread.currentThread().isAlive());
		Thread.dumpStack();
		ThreadTest3.test();

	}
}
