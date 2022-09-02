#!usr/bin/python
# -*- coding: UTF-8 -*-
import time
import math
def p( *a ):
    "弹出"
    for x in a:
      print( x );

print ("Hello, world");
if True:
    print ('ok');
else:
    print ('yeah');


# 我的注释
m = 'var_m'
print (m)
q= 3
if q==3:
    print ("yeah");
    k=q=2

if q==2:
    print('ok');

num = 1
numm = 2.2
n = "me"
num,numm,n = 4,5.3,'he'
print (num,numm,n)
num = 6 #Numbers 数字 支持 int 有符号整型 long 长整型（也可八进制十六进制） float 浮点数 complex 复数
#num = 44j ; num = 0122L ;
n = "Ohhhh" #String 字符串
st = 'Hello World!' 
print (st) # 输出完整字符串 
print (st[0]) # 输出字符串中的第一个字符 
print (st[2:5]) # 输出字符串中第三个至第六个之间的字符串 
print (st[2:]) # 输出从第三个字符开始的字符串 
print (st * 2) # 输出字符串两次 
print (st + "TEST") # 输出连接的字符串
# 注意本应该无括号
print (st[num])
list = ["yi","then","then"] #List
print (list[0:-1])
llll = ("hhhh","Ohhh") # Python 元组 (Tuple)只读列表 不允许更新
dic = {"name":"da","kana":"uu"} #dictionary
dic["code"] = 4
print (dic["name"],dic.keys(),dic.values())
print(int(num)) #int(number,base) 变为整数 或 进制转换 long(number,base)转为长整数 py3无
#float(number)创建一个浮点数
#complex(real[,imag]) real int long float或字符串 imag real int long complex("1+2j") complex(1,2)>>>1+2j
#str(object) 转为字符串 repr(object) 转为字符串表达式
#tuple( iterable ) iterable -- 要转换为元组的可迭代序列
#list(tup) tup -- 要转换为列表的元组
#set(s) 转换为一个集合 x&y 交集 x|y并集 x-y差集
#dict(d) 创建一个字典，d必须是(key,value)元祖
#frozenset(s) 转换为不可变集合
#chr(i)将一个整数转换为一个字符
#unichr(x) 将一个字符转换为 Unicode字符
#ord(x) 将一个字符转换为整数值
#hex(x)将一个字符串转换为十六进制字符串
#cot(x)将一个字符串转换为八进制字符串
#a=10;b=20;print((a+b),(a-b),(a*b),(a/b),(a%b),(a**b),(a//b),(a==b),(a!=b),(a>b),(a<b),(a>=b),(a<=b),(a and b),(a or b),(not(a and b)),"加 减 乘 除 除法取余数 次方 除法取商 是否相等 是否不相等 是否大于 是否小于 是否大于等于 是否小于等于")
#a=b 赋值预算  a+=b a=a+b  a-=b a=a-b a*=b a=a*b  a/=b a=a/b a%=b a=a%b  a**=b a=a**b  a//=b a=a//b
#& 按位与运算符：参与运算的两个值,如果两个相应位都为1,则该位的结果为1,否则为0  | 按位或运算符：只要对应的二个二进位有一个为1时，结果位就为1。 ^ 按位异或运算符：当两对应的二进位相异时，结果为1  ~ 按位取反运算符：对数据的每个二进制位取反,即把1变为0,把0变为1 。~x 类似于 -x-1 (~a )  <<  左移动运算符：运算数的各二进位全部左移若干位，由 << 右边的数字指定了移动的位数，高位丢弃，低位补0。  >>  右移动运算符：把">>"左边的运算数的各二进位全部右移若干位，>> 右边的数字指定了移动的位数
#a=2;b=[3,3,4,2];print ((a in b),(a not in b),(a is b),(a is not b),"前者是否在后者 反 两者是否应用同一对象 反")
#**指数 (最高优先级)~ + -按位翻转, 一元加号和减号 (最后两个的方法名为 +@ 和 -@)* / % //乘，除，取模和取整除+ -加法减法>> <<右移，左移运算符&位 'AND'^ |位运算符<= < > >=比较运算符<> == !=等于运算符= %= /= //= -= += *= **=赋值运算符is is not身份运算符in not in成员运算符not and or逻辑运算符
if True:
    print("c1")
    print("c2")
    if True:print("c3")
else:
    print("c4")
print("end")
i=20
i=0;
while i<10:
    i+=1
    if i == 3 :print("skip");continue
    if i == 5 :print("break");break
    if i == 2 :
        pass # pass 不起作用，防止报错
    print(i)
else: print("else")
print('Oh')
print("\n")
#r"\n" R"\n" 原始字符串
for el in list :print(el)
for el in m  :print(el)
for el in range(len(m)) :print(m[el]) #break else
del m , q #删除对象
#math import math  abs(x)返回数字的绝对值，如abs(-10) 返回 10  ceil(x)返回数字的上入整数，如math.ceil(4.1) 返回 5  cmp(x,y)如果 x < y 返回 -1, 如果 x == y 返回 0, 如果 x > y 返回 1  exp(x) 返回e的x次幂(ex),如math.exp(1) 返回2.718281828459045  fabs(x)返回数字的绝对值，如math.fabs(-10) 返回10.0  floor(x)返回数字的下舍整数，如math.floor(4.9)返回 4  log(x) 如math.log(math.e)返回1.0,math.log(100,10)返回2.0 log10(x)返回以10为基数的x的对数，如math.log10(100)返回 2.0  max(x1,x2,x3)返回给定参数的最大值，参数可以为序列。min(x1,x2,x3)返回给定参数的最小值，参数可以为序列。  modf(x) 返回x的整数部分与小数部分，两部分的数值符号与x相同，整数部分以浮点型表示。  pow(x,y) x**y 运算后的值。  round(x[,n]) 返回浮点数x的四舍五入值，如给出n值，则代表舍入到小数点后的位数。sqrt(x)返回数字x的平方根
# choice(seq) 从序列的元素中随机挑选一个元素，比如random.choice(range(10))，从0到9中随机挑选一个整数。  randrange ([start,] stop [,step]) 从指定范围内，按指定基数递增的集合中获取一个随机数，基数默认值为 1  random() 随机生成下一个实数，它在[0,1)范围内。  seed([x]) 改变随机数生成器的种子seed。如果你不了解其原理，你不必特别去设定seed，Python会帮你选择seed。  shuffle(lst) 将序列的所有元素随机排序  uniform(x, y) 随机生成下一个实数，它在[x,y]范围内。
# acos(x)  返回x的反余弦弧度值。  asin(x)  返回x的反正弦弧度值。  atan(x) 返回x的反正切弧度值。  atan2(y, x)  返回给定的 X 及 Y 坐标值的反正切值。  cos(x)  返回x的弧度的余弦值。  hypot(x, y)  返回欧几里德范数 sqrt(x*x + y*y)。  sin(x) 返回的x弧度的正弦值。  tan(x) 返回x弧度的正切值。  degrees(x) 将弧度转换为角度,如degrees(math.pi/2) ， 返回90.0  radians(x) 将角度转换为弧度
# pi e
#\(在行尾时) 续行符  \\ 反斜杠符号  \' 单引号  \" 双引号  \a 响铃  \b 退格(Backspace)  \e 转义  \000 空  \n 换行  \v 纵向制表符  \t 横向制表符  \r 回车  \f 换页  \oyy 八进制数，yy代表的字符，例如：\o12代表换行  \xyy 十六进制数，yy代表的字符，例如：\x0a代表换行  \other 其它的字符以普通格式输出
#%c  格式化字符及其ASCII码  %s  格式化字符串  %d  格式化整数  %u  格式化无符号整型  %o  格式化无符号八进制数  %x  格式化无符号十六进制数  %X  格式化无符号十六进制数（大写）  %f  格式化浮点数字，可指定小数点后的精度  %e  用科学计数法格式化浮点数  %E  作用同%e，用科学计数法格式化浮点数  %g  %f和%e的简写  %G  %F 和 %E 的简写  %p  用十六进制数格式化变量的地址     辅助指令 * 定义宽度或者小数点精度  - 用做左对齐  + 在正数前面显示加号( + )  <sp> 在正数前面显示空格  # 在八进制数前面显示零('0')，在十六进制前面显示'0x'或者'0X'(取决于用的是'x'还是'X')  0 显示的数字前面填充'0'而不是默认的空格  % '%%'输出一个单一的'%'  (var) 映射变量(字典参数)  m.n. m 是显示的最小总宽度,n 是小数点后的位数(如果可用的话)
#三引号允许跨行
print(u'me')
#string.capitalize() 把字符串的第一个字符大写
#string.center(width) 返回一个原字符串居中,并使用空格填充至长度 width 的新字符串
#string.count(str, beg=0, end=len(string)) 返回 str 在 string 里面出现的次数，如果 beg 或者 end 指定则返回指定范围内 str 出现的次数
#string.decode(encoding='UTF-8', errors='strict') 以 encoding 指定的编码格式解码 string，如果出错默认报一个 ValueError 的 异 常 ， 除非 errors 指 定 的 是 'ignore' 或 者'replace'
#string.encode(encoding='UTF-8', errors='strict') 以 encoding 指定的编码格式编码 string，如果出错默认报一个ValueError 的异常，除非 errors 指定的是'ignore'或者'replace'
#string.endswith(obj, beg=0, end=len(string)) 检查字符串是否以 obj 结束，如果beg 或者 end 指定则检查指定的范围内是否以 obj 结束，如果是，返回 True,否则返回 False.
#string.expandtabs(tabsize=8) 把字符串 string 中的 tab 符号转为空格，tab 符号默认的空格数是 8。
#string.find(str, beg=0, end=len(string)) 检测 str 是否包含在 string 中，如果 beg 和 end 指定范围，则检查是否包含在指定范围内，如果是返回开始的索引值，否则返回-1
#string.format() 格式化字符串
#string.index(str, beg=0, end=len(string)) 跟find()方法一样，只不过如果str不在 string中会报一个异常.
#string.isalnum() 如果 string 至少有一个字符并且所有字符都是字母或数字则返回 True,否则返回 False
#string.isalpha() 如果 string 至少有一个字符并且所有字符都是字母则返回 True,否则返回 False
#string.isdecimal()如果 string 只包含十进制数字则返回 True 否则返回 False.
#string.isdigit() 如果 string 只包含数字则返回 True 否则返回 False.
#string.islower() 如果 string 中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是小写，则返回 True，否则返回 False
#string.isnumeric() 如果 string 中只包含数字字符，则返回 True，否则返回 False
#string.isspace() 如果 string 中只包含空格，则返回 True，否则返回 False.
#string.istitle() 如果 string 是标题化的(见 title())则返回 True，否则返回 False
#string.isupper() 如果 string 中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是大写，则返回 True，否则返回 False
#string.join(seq) 以 string 作为分隔符，将 seq 中所有的元素(的字符串表示)合并为一个新的字符串
#string.ljust(width)返回一个原字符串左对齐,并使用空格填充至长度 width 的新字符串
#string.lower() 转换 string 中所有大写字符为小写.
#string.lstrip() 截掉 string 左边的空格
#string.maketrans(intab, outtab]) maketrans() 方法用于创建字符映射的转换表，对于接受两个参数的最简单的调用方式，第一个参数是字符串，表示需要转换的字符，第二个参数也是字符串表示转换的目标。
#max(str) 返回字符串 str 中最大的字母。
#min(str)返回字符串 str 中最小的字母。
#string.partition(str) 有点像 find()和 split()的结合体,从 str 出现的第一个位置起,把 字 符 串 string 分 成 一 个 3 元 素 的 元 组 (string_pre_str,str,string_post_str),如果 string 中不包含str 则 string_pre_str == string.
#string.replace(str1, str2,  num=string.count(str1)) 把 string 中的 str1 替换成 str2,如果 num 指定，则替换不超过 num 次.
#string.rfind(str, beg=0,end=len(string) ) 类似于 find()函数，不过是从右边开始查找.
#string.rindex( str, beg=0,end=len(string))类似于 index()，不过是从右边开始.
#string.rjust(width) 返回一个原字符串右对齐,并使用空格填充至长度 width 的新字符串
#string.rpartition(str) 类似于 partition()函数,不过是从右边开始查找
#string.rstrip() 删除 string 字符串末尾的空格.
#string.split(str="", num=string.count(str)) 以 str 为分隔符切片 string，如果 num 有指定值，则仅分隔 num+ 个子字符串
#string.splitlines([keepends]) 按照行('\r', '\r\n', \n')分隔，返回一个包含各行作为元素的列表，如果参数 keepends 为 False，不包含换行符，如果为 True，则保留换行符。
#string.startswith(obj, beg=0,end=len(string)) 检查字符串是否是以 obj 开头，是则返回 True，否则返回 False。如果beg 和 end 指定值，则在指定范围内检查.
#string.strip([obj])在 string 上执行 lstrip()和 rstrip()
#string.swapcase()翻转 string 中的大小写
#string.title() 返回"标题化"的 string,就是说所有单词都是以大写开始，其余字母均为小写(见 istitle())
#string.translate(str, del="")根据 str 给出的表(包含 256 个字符)转换 string 的字符,要过滤掉的字符放到 del 参数中
#string.upper() 转换 string 中的小写字母为大写
#string.zfill(width)  返回长度为 width 的字符串，原字符串 string 右对齐，前面填充0
#列表
#list.append(obj) 在列表末尾添加新的对象
#list.count(obj) 统计某个元素在列表中出现的次数
#list.extend(seq) 在列表末尾一次性追加另一个序列中的多个值（用新列表扩展原来的列表）
#list.index(obj) 从列表中找出某个值第一个匹配项的索引位置
#list.insert(index, obj) 将对象插入列表
#list.pop([index=-1]) 移除列表中的一个元素（默认最后一个元素），并且返回该元素的值
#list.remove(obj) 移除列表中某个值的第一个匹配项
#list.reverse() 反向列表中元素
#list.sort(cmp=None, key=None, reverse=False) 对原列表进行排序
#字典
#dict.clear() 删除字典内所有元素
#dict.copy() 返回一个字典的浅复制
#dict.fromkeys(seq[, val])创建一个新字典，以序列 seq 中元素做字典的键，val 为字典所有键对应的初始值
#dict.get(key, default=None)返回指定键的值，如果值不在字典中返回default值
#dict.has_key(key) 如果键在字典dict里返回true，否则返回false
#dict.items() 以列表返回可遍历的(键, 值) 元组数组
#dict.keys() 以列表返回一个字典所有的键
#dict.setdefault(key, default=None) 和get()类似, 但如果键不存在于字典中，将会添加键并将值设为default
#dict.update(dict2) 把字典dict2的键/值对更新到dict里
#dict.values()以列表返回字典中的所有值
#pop(key[,default]) 删除字典给定键 key 所对应的值，返回值为被删除的值。key值必须给出。 否则，返回default值。
#popitem() 返回并删除字典中的最后一对键和值
nowtime=time.time();print(nowtime);print(time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()))
print(time.strftime("%y年 %Y年 %m月 %d日 %H时 %I时 %M分 %S秒 %a星期 %A星期 %b月 %B月 %j日期和时间表示 %pAM.PM.  %W星期 %w星期 %W星期 %x日期 %X时间 %Z时区 %%", time.localtime()))
def ccc(a):
    i=0
    while(i<a):
        print('Ohhhh')
        i+=1

def text_e(a):
  "None"
  a.append(['33',4,55,45]);
  p(a)
p(list)
text_e(list)
p(list)
del text_e
def print_x ( arg1, *vartuple ):
  p(arg1)
  for x in vartuple :
    print ( x )
print_x(6797587,797978,646464,646464)
func = lambda a,b,c:a+b+c
fu = lambda a,d,f:a+d*f
p(fu(13,4,6))
p(func(1,2,2))
print("\n")
# import h # ./h.py
#import module1[, module2[,... moduleN]]
#from  import * 导入所有
p(dir(math));
def ke ():
   "ke"
   p(globals(),locals())  
ke()
#reload(h)
import os
src=os.path.dirname(os.path.realpath(__file__))
os.chdir(src);#设置当前目录 例如os.chdir('myfiles');
p(os.getcwd());#当前工作目录
#写
st = input("请输入：") 
st = "你输入的内容是: "+ st
p(st)
fo=open('foo.txt','w+');
fo.write(st);
print(fo.name)#文件名
fo.close();

del fo;
#读
fo=open('foo.txt','r+',encoding='utf-8',errors='ignore');
p(fo.read(7));
w=fo.tell()#获取位置
w=(fo.seek(7,0));#seek(offset [,from])from 0当前 1开始 2结尾
p(fo.read());
fo.close();
del fo
fo =open('fo.txt','w+');
fo.write('这是要被删除的文件');
fo.close();
del fo
os.rename('foo.txt','f.txt');#os.rename(current_file_name, new_file_name)
os.remove("fo.txt");#删除
os.mkdir('newfiles');#新建空目录
os.rmdir('newfiles');#删除新目录
try:
  fh = open("testfile", "w")
  fh.write("这是一个测试文件，用于测试异常!!")
except IOError:
  print ("Error: 没有找到文件或读取文件失败")
else:
  print ("内容写入文件成功")
  fh.close()
print(os.access('f.txt',os.F_OK),os.access('f.txt',os.R_OK),os.access('f.txt',os.W_OK),os.access('f.txt',os.X_OK),'存在 读 写 执行')#os.access(path, mode);参数path -- 要用来检测是否有访问权限的路径。mode -- mode为F_OK，测试存在的路径，或者它可以是包含R_OK, W_OK和X_OK或者R_OK, W_OK和X_OK其中之一或者更多。os.F_OK: 作为access()的mode参数，测试path是否存在。os.R_OK: 包含在access()的mode参数中 ， 测试path是否可读。os.W_OK 包含在access()的mode参数中 ， 测试path是否可写。os.X_OK 包含在access()的mode参数中 ，测试path是否可执行。
#os.chroot("tmp")设置根目录
#file=os.open('f.txt',os.O_RDWR|os.O_CREAT);os.wirte(file,'me');os.close(file)
p(os.listdir())
#import shutil
#未完成 shutil.copyfile(os.getcwd(),'f.txt');#复制文件
class ClassName:
    "hint"
    __c='yeah'
    d=666
    m=0
    def pp(self):
      print(self,self.__class__,self.d)# self 不是Python关键词 self代表实例 而非类
    def po(self,a):
      eval(a);
    def ad(self,*a):
      print(self.d)
      if a :print(a);
    def __init__(self,*a):
      self.d=a
      self.m+=1
      print("("+str(self.m)+")类的初始化方法","顺便:",a)
    def __del__(self):
      del self.d
      print('销毁:',self.__class__.__name__)
del numm
numm = ClassName()
numm.pp();
print(numm._ClassName__c)
ob1=ClassName('w','emmmmm')
ob2=ClassName('z','meeeee')
ob1.ad()
ob2.ad()
print(hasattr(ob2, 'd'),getattr(ob2,'d'))
del ob1,ob2
print(ClassName.__dict__,ClassName.__doc__,ClassName.__name__,ClassName.__module__,ClassName.__bases__,'类的属性 文档字符串 类名 类定义所在的模块 类的所有构成元素')
numm.ad('hiahiahia')
del numm
#父类
class Parent:
    def __init__(self):
        print('调用:',self.__class__.__name__)
    def p(self,*a):
        n=self.__class__.__name__
        for x in a:
            print('p:',n,x)
        del n
    def __del__(self):
        print('销毁:',self.__class__.__name__)
class per:
    def m(self,*a):
        print('m:',a)
#子类)
class Child(Parent,per):
    def d(self,*a):
        print('d: ',self.__class__.__name__,a)
ob1 = Parent()
ob2 = Child()
ob1.p('xxx','xx')
ob2.m('xx','xd')
ob2.d(1)
ob2.p('e','e','i')
del ob1,ob2
#__双下划线表示私用，即仅在类内访问
#_单下划线只允许本身和子类访问
import re
print(re.match('[A-Za-z0-9]+',n,flags=0),re.match('.*',n).span(),'不匹配起始位置 匹配起始位置')
#match从起始位置匹配，没有结果，None
n='Hello, world!'
ob1=re.match('([\S]+)(\,)',n)
print(ob1.group(0),ob1.group(1),ob1.groups())
ob2=re.search('wo[\S]+',n,flags=0)#可使用group groups
print(ob2.group())
pattern = re.compile('[A-Za-z0-9]+',flags=0)
# flages 参数#re.I 忽略大小写  re.L 表示特殊字符集 \w, \W, \b, \B, \s, \S 依赖于当前环境  re.M 多行模式  re.S 即为 . 并且包括换行符在内的任意字符（. 不包括换行符）  re.U 表示特殊字符集 \w, \W, \b, \B, \d, \D, \s, \S 依赖于 Unicode 字符属性数据库  re.X 为了增加可读性，忽略空格和 # 后面的注释
repl = 'yeah'
string=n
#repl可以为函数
#count表示个数，默认为0，表示所以
def ll(a):
  return (str(a.group())+'_')
ob3=re.sub(pattern, repl, string, count=0, flags=0)
ob4=re.sub(pattern,ll,string)
ob5=re.search(pattern,string)
print(ob5.group(),ob5.start(),ob5.end(),ob5.span(),'字符串 匹配的开始位置 结束位置 开始和结束位置')
print(ob3)
print(ob4)
del ob1,ob2,ob3
ob1=pattern.findall(string,1,10)#findall(string[, pos[, endpos]]) 开始位置结束位置
ob2=re.finditer(pattern, string, flags=0)
ob3=re.split('\W+', string)#re.split(pattern, string[, maxsplit=0, flags=0]) maxsplit为分割次数
print(ob1)
for x in ob2:
    print(x.group())
print(ob3)
del ob1,ob2,ob3,ob4,ob5,pattern,repl,string,ll
import queue
import _thread
import threading
def fun(name,a,t):
    i=0
    while i<a:
        time.sleep(t)
        print(name,i)
        i+=1
#_thread.start_new_thread(fun,('name1',100,1))
#_thread.start_new_thread(fun,('name2',100,0.5))
class line(threading.Thread):
    i=0
    def __init__(self,a,b,c):
      threading.Thread.__init__(self)
      self.a=a;self.b=b;self.c=c;
    def run(self):
      #lock=threading.Lock()
      #lock.acquire()
      #threadLock.acquire() #阻塞，直至获得锁，返回True，超时返回False
      while self.i<self.b:
        time.sleep(self.c)
        print (self.a,self.b,self.c)
        self.i+=1
      #lock.release()
      #threadLock.release()
threadLock=threading.Lock()
line1=line('line1',50,0.1)
line2=line('line2',25,0.2)
line1.start()
#line1.join(3) sleep
#line1.run() 活动
print(line1.isAlive(),line1.getName(),line1.setName('line555'),line1.getName()) #是否活动
line2.start()
p('sleep')
threads=[]
threads.append(line1)
threads.append(line2)
time.sleep(1)
print('run',threading.enumerate())
#for x in threads:
#    x.join() #等待线程完成
line3=line('line3',100,0.1)
lines=queue.Queue(3)
print(lines.qsize()) #队列大小
#Queue.put_nowait(item) 相当Queue.put(item, False)
#Queue.task_done() 在完成一项工作之后，Queue.task_done()函数向任务已经完成的队列发送一个信号
for x in threads:
  lines.put(x)
print('等待时间: ',lines.get())
lines.queue.clear() #怪异的清空
while not lines.empty():
  time.sleep(1)
  print(lines.empty())
  pass #等待队列清空
for x in threads:
    x.join()
print('end')
from xml.dom.minidom import parse
import xml.dom.minidom
 
# 使用minidom解析器打开 XML 文档
DOMTree = xml.dom.minidom.parse("this.xml")
collection = DOMTree.documentElement
if collection.hasAttribute("title"):
   print ("Root element : %s" % collection.getAttribute("title"))
elements = collection.getElementsByTagName("line")
for e in elements:
   print ("*****Movie*****")
   if e.hasAttribute("title"):
      print ("Title: %s" % e.getAttribute("title"))
 
   name = e.getElementsByTagName('name')[0]
   print ("name: %s" % name.childNodes[0].data)
   level = e.getElementsByTagName('level')[0]
   print ("level: %s" % level.childNodes[0].data)
#插曲
"""
import xlrd
def read_excel():
    # 打开文件
    workbook = xlrd.open_workbook('x.xlsx')
    # 获取所有sheet
    print(workbook.sheet_names())  # [u'sheet1', u'sheet2']
 
    # 根据sheet索引或者名称获取sheet内容
    sheet1 = workbook.sheet_by_index(0)  # sheet索引从0开始
 
    # sheet的名称，行数，列数
    print(sheet1.name, sheet1.nrows, sheet1.ncols)
 
    # 获取整行和整列的值（数组）
    rows = sheet1.row_values(3)  # 获取第四行内容
    cols = sheet1.col_values(2)  # 获取第三列内容
    print(rows)
    print(cols)
 
    # 获取单元格内容
    print(sheet1.cell(1, 0).value.encode('utf-8'))
    print(sheet1.cell_value(1, 0).encode('utf-8'))
    print(sheet1.row(1)[0].value.encode('utf-8'))
 
    # 获取单元格内容的数据类型
    print(sheet1.cell(1, 0).ctype)

if __name__ == '__main__':
    pass
    read_excel()
"""
import json
print('**json**')
del n
f=open('data.json','r+')
n=f.read()
f.close()
print('json:',n)
dic=json.loads(n)#json.loads(s[, encoding[, cls[, object_hook[, parse_float[, parse_int[, parse_constant[, object_pairs_hook[, **kw]]]]]]]])
print('dic:',dic)
print(json.dumps(dic))#json.dumps(obj, skipkeys=False, ensure_ascii=True, check_circular=True, allow_nan=True, cls=None, indent=None, separators=None, encoding="utf-8", default=None, sort_keys=False, **kw)
print ('no sleep')

# print(time.clock())


"""
#raw_input("按下 enter 键退出，其他任意键显示...\n")
"""
