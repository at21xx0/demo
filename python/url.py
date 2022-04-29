#!usr/bin/python3
# -*- coding: UTF-8 -*-
print('urllib test')
import urllib
import urllib.request
import http.cookiejar
#m=urllib.request.urlopen('http://cn.bing.com/')
#print(m.read())
# 从 https://blog.csdn.net/jiduochou963/article/details/87564467 https://blog.csdn.net/duxu24/article/details/77414298
#urllib.request.urlretrieve('http://www.python.org', '/storage/emulated/0/qpython/my/python_webpage.html')
#urllib.request.urlretrieve('https://mzh.moegirl.org/File:A54e55fb635ced29024f565b.jpg')#urllib.request.urlretrieve(url,filename,reporthook,data) 
#Get
#req=urllib.request.Request('',header=headers)

def g():
  req = urllib.request.Request('https://www.baidu.com')
  #class urllib.request.Request(url, data=None, headers={},origin_req_host=None,unverifiable=False, method=None)
  req.add_header('User-Agent', "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163")
  url = 'https://www.baidu.com'
  #data=urllib.urlencode({'name':'xxxx','friend':'xxxx'})
  # 创建一个cookiejar对象
  cookie=http.cookiejar.CookieJar()
  # 使用HTTPCookieProcessor创建cookie处理器
  cookies = urllib.request.HTTPCookieProcessor(cookie)
  # 并以它为参数创建Opener对象
  opener = urllib.request.build_opener(cookies)
  # 使用这个opener来发起请求
  #resp = opener.open(url)
  #或者也可以把这个生成的opener使用install_opener方法来设置为全局的，之后使用urlopen方法发起请求时，都会带上这个cookie：
  # 将这个opener设置为全局的opener
  urllib.request.install_opener(opener)
  #resp = request.urlopen(url)
  with urllib.request.urlopen(req) as f:
    # 有data 在默认发出post请求
    data=f.read()
    print(data.decode())
    print(type(f))
    return ('o')
    print('Status:', f.status, f.reason)
    print('Data: ',data.decode('utf-8'))
    for k, v in f.getheaders():
        print('%s: %s' % (k, v))
    for i in cookie:
      print(i)
        #print('Data:', data.decode('utf-8'))
g()
def p():
  print('p')

#urllib.parse.quote_plus(string[, safe])
#urllib.parse.unquote_plus(string)




