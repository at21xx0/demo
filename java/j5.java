
import java.util.Vector;
import java.util.Enumeration;
import java.util.BitSet;
import java.util.*;
import java.io.*;


import java.net.URL;
import java.net.URLConnection;
import java.net.HttpURLConnection;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.InetAddress;



public class j5
{
	public static void main(String[] args)
	{
		System.out.println("hello, world!");
		try{
			URL url=new URL("http://www.baidu.com/s?page=1#home");
			//URL url=new URL("http","www.baidu.com",80,"/s");
			//URL url=new URL("http","www.baidu.com","/s");
			//new URL(URL context,String url)
			System.out.println(url.toString());
			System.out.println(url.getProtocol());
			System.out.println(url.getHost());
			System.out.println(url.getPort());
			System.out.println(url.getDefaultPort());
			System.out.println(url.getPath());
			System.out.println(url.getQuery());
			System.out.println(url.getRef());
			System.out.println(url.getFile());
			System.out.println();

			/*
			URLConnection u=url.openConnection();
			HttpURLConnection h=null;
			if(u instanceof HttpURLConnection)
				h=(HttpURLConnection)u;
			else
				return;
			BufferedReader r1=new BufferedReader(new InputStreamReader(h.getInputStream()));
			String s1="";
			while((s1=r1.readLine())!=null)
			{
				System.out.print(s1);
			}
			System.out.println();
			*/

		
		}catch(Exception err){
			err.printStackTrace();
		}
		try{
		char c=(char)System.in.read();
		
		if(c=='1'){
			InetAddress i1=InetAddress.getByName("www.baidu.com");
			//InetAddress i1=InetAddress.getByAddress(Byte [] b);
			System.out.println(i1.toString());
			System.out.println(i1.getHostAddress());
			System.out.println(i1.getHostName());
			System.out.println(i1.getCanonicalHostName());
			//i1=InetAddress.getByAddress("127.0.0.1");
			i1=InetAddress.getLocalHost();
			// static InetAddress [] getAHByName(String Host);
			System.out.println(i1.getHostAddress());
		}else if(c=='2'){
				ServerSocket s1=new ServerSocket(8084);
				//ServerSocket s1=new ServerSocket(8084,50);//最大连接数
				//ServerSocket s1=new ServerSocket();
				//ServerSocket s1=new ServerSocket();
				//ServerSocket(8084,50,addr);
				System.out.println(s1.getLocalPort());
				Socket s2=s1.accept();
				System.out.println(s2.getPort());
				System.out.println(s2.getLocalPort());
				System.out.println(s2.getInetAddress());
			
				//connect(SocketAddress host,int timout);
			
				System.out.println("link: "+s2.getRemoteSocketAddress());
				DataInputStream r2=new DataInputStream(s2.getInputStream());
				DataOutputStream w2=new DataOutputStream(s2.getOutputStream());
				w2.writeUTF("test\n");
				System.out.println("read: "+r2.readUTF());
				w2.close();
				r2.close();
				s2.close();
				s1.close();
			}
			else if(c=='3')
			{
				//Socket s4=new Socket()
				//s4.connect(InetAddress.getLocalHost(),500)
				Socket s4=new Socket("127.0.0.1",8084);
				//Socket s4=new Socket(InetAddress.getLocalHost(),8084);
				//public Socket(String host, int port, InetAddress localAddress, int localPort) throws IOException.
				//public Socket(InetAddress host, int port, InetAddress localAddress, int localPort) throws IOException.
				OutputStream w3=s4.getOutputStream();
				DataOutputStream w4=new DataOutputStream(w3);
				w4.writeUTF("test\n");
				w4.close();
				w3.close();
				s4.close();

			}

			//
			
			//s1.setSoTimeout(500);//毫秒
			//s1.bind(8084
		}catch(Exception err){
			err.printStackTrace();
		}
	}
	
}
