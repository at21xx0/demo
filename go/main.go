// main - godoc
package main
// import "fmt"
import (
	"fmt"
	"unsafe"
	"math"
	"strings"
	"bytes"
	"sync"
	"container/list"
	"errors"
	"time"
	"strconv"
	"crypto/md5"
	"crypto/sha1"
	"runtime"
	"bufio"
	"sort"
	"net/url"
	"net/http"
	"math/big"
	"regexp"
	"os"
	"os/exec"
	"os/signal"
	"flag"
	"context"
	"sync/atomic"
	"net"
	"log"
	"reflect"
	"encoding/xml"
	"encoding/json"
	"encoding/gob"
	"encoding/base64"
	"encoding/binary"
	"encoding/hex"
	"io"
	// "mime/multipart"
	"io/ioutil"
	"path/filepath"
	"archive/zip"
	"crypto/tls"
	"crypto/x509"
)
// import . fmt // fmt.Println -> Println
// import "test1" // $GOPATH/test1/test1.go

type point struct {
	x, y int
}

type u8 = uint8
type point2 = point
type u16 = uint16
type u32 = uint32
type u64 = uint64
type u8_ uint8
// non-local type error


func max_1(num1, num2 int) int {
	if num1 > num2{
		return num1
	}
	return num2
}

func add_1(x, y int) (z int) { z = x + y; return}

func add_2(nums ... int) int {
	var ret int = 0
	for _, i := range nums {
		ret += i
	}
	return ret
}

func ret_1(x, y int) (int, int) {
	return x, y
}
func swap_1(x, y *int) {
	var t int
	t = *x
	*x = *y
	*y = t
}


func escape_x(i int) *int {
	var x int = 5
	return &x
}

func getIPP(i int) func() int {
	return func() int {
		i++
		return i
	}
}

func (p point) getM() float64 {
	return math.Sqrt(float64(0.0 + p.x * p.x + p.y + p.y))
}

func print_1(ifs ... interface{}) {
	var s string
	for _, v := range ifs {
		// switch v.(type) { case int:}
		s += fmt.Sprintf("%T ", v)
		s += fmt.Sprint(v, "\t")
	}
	fmt.Println(s)
}

type PPSTRT func(string) string

func PPSTR() PPSTRT {
	var str string = ""
	return func(s string) string {
		str += s
		return str
	}
}

func defer_test(pp PPSTRT) {
	pp("[")
	defer pp("]")
	defer pp("r")
	pp("s")
	pp("t")
}

func panic_test() {
	err := errors.New("FATAL_ERROR: nullptr")
	defer func() {
		fmt.Println("before crash")
		err := recover()
		fmt.Println("err:", err)
	}()
	if err != nil {
		fmt.Println(err)
		panic("crash")
	}
}

var var_g int = 0
func getG() int {
	return var_g
}

func sum10(a [10]int) int {
	var i, ret int
	for i = 0;i != 10;i++ {
		ret += a[i]
	}
	return ret
}
func sum_2_2(a [2][2]int) int {
	var ret int
	ret = a[0][0] + a[0][1]
	ret += a[1][0] + a[1][1]
	return ret
}

func factorial(n uint64) uint64 {
	if(n > 0) {
		return n * factorial(n - 1)
	}
	return 1
}


type point3 struct {
	x, y, z int
}

type interface_f2 func(interface{}) int

type interface_1 interface {
	// method_name [return_type]
	method_1(i int) int
	method_2(interface{}) int
}

/*
type interface_3 interface {
	interface_1
	interface_2
}
*/



func (p point) method_1(i int) int {
	return p.x + p.y + i
}
func (p *point3) method_1(i int) int {
	return p.x + p.y + p.z + i
}


func (p point) method_2(if1 interface{}) int {
	if i, bool1 := if1.(int);bool1 {
		return p.method_1(i)
	}
	return p.method_1(0)
}
func (p *point3) method_2(if1 interface{}) int {
	return p.method_1(if1.(int))
}




func (f interface_f2) method_2(i interface{}) int {
	return f(i)
}
func (f interface_f2) method_1(i int) int {
	return f(i)
}

func pointNIL() *point {
	var pp *point = nil
	// return pp // error
	if pp == nil {
		return nil
	}
	return pp
}

type SORTPOINT []point

func (p SORTPOINT) Len() int {
	return len(p)
}

func (p SORTPOINT) Less(i, j int) bool {
	return p[i].x * p[i].x + p[i].y + p[i].y < p[j].x * p[j].x + p[j].y + p[j].y
}

func (p SORTPOINT) Swap(i, j int) {
	p[i].x, p[j].x = p[j].x, p[i].x
	p[i].y, p[j].y = p[j].y, p[i].y
}


type pErr struct {
	x, y int
}

// interface

func (e *pErr) Error() string {
	return fmt.Sprintf("err: %d %d", e.x, e.y)
}

type OddStruct struct {
	x, y, z int
	int // anonymous
	point3 // anonymous
}


func goroutine_1(n int, chan1 chan int) {
	var i int
	for i = 0;i != 10;i++ {
		time.Sleep(10 * time.Millisecond)
	}
	chan1 <- i
}

type EventEmitter map[string][]func(interface{})
// make(EventEmitter)

func (ee EventEmitter) on(name string, callback func(interface{})) {
	ee[name] = append(ee[name], callback)
}
func (ee EventEmitter) emit(name string, param interface{}) {
	list := ee[name]
	for _, cb := range list {
		cb(param)
	}
}

func test_lock() int {
	// var lock sync.RWMutex // lock.RLock() lock.RUnlock() lock.WLock() lock.WUnlock()
	var lock sync.Mutex
	var wg sync.WaitGroup // sem
	var i int
	var f func() = func() {
		lock.Lock()
		defer wg.Done() // sem--
		defer lock.Unlock()
		i++
	}
	wg.Add(4) // sem + 4
	go f()
	go f()
	go f()
	go f()
	wg.Wait() // wait sem == 0
	return i
}

type TMP struct {
	X, Y int
	F float64 `id:"0" str:"[str]"`
}

type private_json_1 struct {
	Code int
	Status string
	Ret []string
}

type private_xml_1 struct {
	XMLName xml.Name `xml:"tag_name"`
	N string `xml:"n,attr"`
	Str string `xml:,comment` // ignore `xml:-` // `xml:",innerxml"` 
	List []pxml_wrap `xml:"wrap"`
}
type pxml_wrap struct {
	N int
	Str string
}
/*

	XMLName xml.Name `xml:"servers"`
	Version string `xml:"Version,attr"`
*/
type Ldir_st struct {
	Name string
	Size int64
	ModTime time.Time
}
func Ldir1(dir string, ch chan Ldir_st, top bool) error {
	entries, err := ioutil.ReadDir(dir)
	for _, entry := range entries {
		fpath := filepath.Join(dir, entry.Name())
		if entry.IsDir() {
			Ldir1(fpath, ch, false)
		} else {
			ch <- Ldir_st{fpath, entry.Size(), entry.ModTime()}
		}
	}
	if top {
		close(ch)
	}
	if err != nil {
		return err
	}
	return nil
}
func Ldir(dir string, ch chan Ldir_st) error {
	return Ldir1(dir, ch, true)
}

// godoc main
func main() {
	var x int
	const Pi float64 = 3.14159265358979323846
	// var ggg gloat32 = 9e10 // 
	/*
	var (
		x int
		k int
		g string
	)
	*/
	var k = 123 // k := 0 // var k int = 10
	// j, k := 1, 2
	// var date1 = "2000-1-1"
	var str = "[str]"
	var s = ""
	// x, k = k, x // swap
	_ = 5
	// fmt.Println(_) // error
	p := point{1, 2}
	fmt.Println("A" + "B")
	fmt.Println(fmt.Sprintf("%d %d %s", k, x, str))
	fmt.Printf("p %v", p) // {1, 2}
	fmt.Printf("p %+v", p) // {x:1, y:2}
	fmt.Printf("p %#v", p) // main.point{x:1, y:2}
	fmt.Printf("p %T", p) // main.point
	fmt.Printf("%t %d %c %x %f %e %E\n", true, 5, 53, 0xFF, 12.3, 12.3, 12.3)
	fmt.Printf("%s %x %q\n", "[str]", "[str]", "[str]")
	// %6d %6.4f %6s %-6d
	// byte rune uint int uintptr
	// uint8 uint16 uint32 uint64 int8 int32 int16 int64
	// float32 float64 complex64 complex128
	var complex1 complex64 = complex(47, 42)
	fmt.Println("complex ", complex1, real(complex1), imag(complex1), complex1 * complex1)

	// bool
	// var var_name type

	var bool1 bool
	var bool2 = false
	bool3 := bool2 == false
	var y, z = 1, 2
	fmt.Printf("x: %d, bool1: %v, bool2: %v, bool3: %v\n", x, bool1, bool2, bool3)
	x, y, z = 1, 2, 3
	fmt.Printf("x: %d, y: %d, z: %d\n", x, y, z)
	const c_int = 1
	// const a, b, c = 1, 2, 3
	s = `abc
	abc
	abc
	`
	const (
		c_str = "[str]"
		c_len = len(c_str)
		c_size = unsafe.Sizeof(c_str)
	)
	// unsafe.Alignof(x ArbitraryType) uintptr
	// OffsetOf Sizeof ArbitraryType Pointer:wq
	// (* int)(unsafe.Pointer(&xxx))
	fmt.Printf("%s, %d, %d, %d\n", c_str, c_len, c_size, c_int)
	// fmt.Println(utf8.RuneCountInString("啊")) // 1
	const (
		c_a = iota // 1 << iota // 1, 2, 4
		c_b
		c_c
	)
	fmt.Printf("%d %d %d\n", c_a, c_b, c_c)
	// + - * / % ++ --
	// == != < > >= <=
	// && || !
	// & | ^ << >>
	// = += -= *= /= %= <<= >>= &= ^= |=
	// & *
	s = "测试"
	// for i := 0;i != len(s);i++ { // s[i] }
	for _, c := range s {
		fmt.Printf("%c %d\n", c, c)
	}
	var x_ptr * int
	// fmt.ScanIn(x_ptr)
	x_ptr = nil
	x_ptr = escape_x(5) // heap // alloc // make([]int, 1000, 1000) make([]int, x, y)
	// go build -gcflags '-m -l' main.go
	x_ptr = new(int)
	x_ptr = &x
	fmt.Printf("x: %d, x_ptr: %d\n",*x_ptr, x_ptr)
	if false {
		// GC
		_ = func() int {
			var p *int = new(int)
			*p = 5
			runtime.SetFinalizer(p, func(p *int) {
				fmt.Println("delete: ", *p)
			})
			return *p
		}()
		for i := 0;i < 5;i++ {
			time.Sleep(time.Second)
			runtime.GC()
		}
	}
	var u8_u u8
	var u8_u_ u8_
	fmt.Printf("u8 %T %T\n", u8_u, u8_u_)

	if x == 1 {
		fmt.Printf("x == 1")
	} else {
		fmt.Printf("x == %d", x)
	}
	switch x {
		case c_a:
			fmt.Printf("x: %d\n", x)
		case c_b, c_c:
			fmt.Printf("x: %d\n", x)
		case 7:
			fallthrough
		default:
			fmt.Printf("x: %d\n", x)
	}
	/*
	switch {
		case x == 1:
			fmt.Println(x)
		case x == 2, x == 3:
			fmt.Println(x)
		default:
			fmt.Println("default")
	}
	*/
	s = "";
	var gg interface{}
	switch t := gg.(type) {
		case nil:
			// s = "nil"
			s = fmt.Sprintf("%T", t)
		case int:
			s = "int"
		case float64, float32:
			s = "float"
		default:
			s = "unknown"
	}
	fmt.Printf("type: %s\n", s)
	// time.Sleep(1)
	c1 := make(chan int)
	c2 := make(chan int)
	go func() {
		time.Sleep(1 * time.Millisecond)
		c1 <- 1
		time.Sleep(1 * time.Millisecond)
		c2 <- 2
	}();
	for x = 0;x < 2;x++ {
		select {
			case msg1 := <-c1:
				fmt.Printf("c1 %d\n", msg1)
			case msg2 := <-c2:
				fmt.Printf("c2 %d\n", msg2)
		}
	}
	y = 0
	for x = 0 ; x < 100 ; x++ {
		if x >= 10 {
			continue
		}
		for x < 10 && y < x {  // while
			if x > 6 {
				break
				// break loop1_continue
			}
			if x > 10 {
				goto loop1_continue
			}
			y++
		}
	loop1_continue:
	}
	fmt.Printf("x, y: %d, %d\n", x, y)
	as := []string{"aa", "bb", "cc"}
	for k, v := range as { // k := range ss // _, v := range ss
		fmt.Printf("as[%d]: %s\n", k, v)
	}
	x, y = ret_1(1, 2)
	swap_1(&x, &y)
	max_2 := func(x, y int) int {
		return max_1(x, y)
	}
	fmt.Printf("max(x, y): %d\n", max_2(x, y))

	f_ipp := getIPP(0) // closure 
	fmt.Printf("ipp: %d\n", f_ipp())
	fmt.Printf("ipp: %d\n", f_ipp())
	fmt.Printf("p m %f\n", p.getM())
	var_g = 5 // global
	fmt.Printf("G: %d\n", getG())
	var add_f func(x, y int) (int)
	add_f = add_1
	add_f = func(x, y int) int { return x + y }
	fmt.Printf("add(x, y): %d\n", add_f(1, 2))
	fmt.Printf("add(1, 2, 3): %d\n", add_2(1, 2, 3))
	print_1(1, add_f, 0.5)
	{
		var pp = PPSTR()
		defer_test(pp)
		fmt.Println("[str]:", pp(""))

		panic_test()

		errordata := pErr{1, 2}
		err := errordata.Error() 
		fmt.Println(err)
	}

	go func() {
		now := time.Now()
		fmt.Println("now", now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second())
		fmt.Println(now.Unix(), now.UnixNano()) // fmt.Println( now, time.Unix(now.Unix(), 0))
		now.Add(time.Second + time.Hour + time.Minute)
		// Sub Equal Before After
		// time.Weekday().String()
		start := time.Now()
		_ = now.Format("2006-01-02")
		_ = now.Format("2006-01-01 00:00:00.000")
		_, _ = time.Parse("2006-01-02", "2006-02-01") // Time, error
		// Func ParseInLocation(layout, value string, loc *Location) (Time, error) // loc = time.Local
		sum := 0
		for i := 0;i < 1000000007;i++ {
			sum++
		}
		// elapsed := time.Since(start)
		elapsed := time.Now().Sub(start)
		fmt.Println("time: ", elapsed)
		ticker := time.Tick(time.Second * 2)
		for i := range ticker {
			fmt.Println("ticker", strings.Replace(fmt.Sprint(i), ":", " : ", -1))
		}
	}()
	// time.Sleep(time.Second)
	{
		str := "[str]"
		Md5Inst := md5.New()
		Md5Inst.Write([]byte(str))
		md5_ret := Md5Inst.Sum([]byte(""))
		Sha1Inst := sha1.New()
		Sha1Inst.Write([]byte(str))
		sha1_ret := Md5Inst.Sum([]byte(""))
		fmt.Printf("%s | md5: %x, sha1: %x\n", str, md5_ret, sha1_ret)

		/*
		TestFile := "test.go"
		f, e := os.open(TestFile)
		if err == nil {
			md5h = md5.New()
			io.Copy(md5h, f)
			fmt.Printf("%x %f\n", md5h.Sum([]byte("")), TestFile)
		}
		else { fmt.Println(e)
		}
		*/
	}


	// var ai [10]int = [10]int{0, 1, 2, 3, 4, 5}
	ai := [...]int{0, 1, 2, 3, 4, 5}
	var ai2 [10]int
	// ai2 == ai // false
	// for k, v := range ai {
	// ai2[k] = v }
	for x = 0;x != len(ai);x++ {
		ai2[x] = ai[x]
	}
	var a2i [2][2]int
	a2i = [2][2]int{{1, 1}, {1, 1}}
	a2iv := [][]int{}
	a2iv = append(a2iv, []int{1, 2, 3})
	a2iv = append(a2iv, []int{4, 5, 6})
	a2iv = append(a2iv, []int{7, 8, 9})
	a2iv = append(a2iv, []int{0, 0})
	a2i[0][0] = a2iv[0][0]
	a2i[0][1] = a2iv[0][1]
	fmt.Println("sum2", sum10(ai2), sum_2_2(a2i))
	// var aip [5]*int
	// var ai2p[5][5]*int
	// var ipp **int

	// struct 
	point_1 := point{1, 2}
	var p1p *point
	p1p = new(point)
	p1p = &point_1
	p1p = &point{x: 1, y: 2}
	fmt.Println("p1x: ", point_1.x, p1p.x)
	_ = func(p *struct{ x, y int}) int {
		return p.x + p.y
	}(&struct{x, y int}{1, 2})

	// slice
	var is1 []int
	// make([]T, length, capacity)
	is1 = make([]int, 5, 10) // []Type, size, cap
	is1 = []int {1, 2, 3, 4, 5}
	// arr[startIndex:endIndex] // reference
	is1 = ai2[:] // ai2[0:len(ai2)] // ai2[0:] // ai2[:len(ai2)]
	fmt.Println("is1[0]: ", is1[0], " len, cap", len(is1), cap(is1))
	// fmt.Println(ai2, ai2[0:1])
	is1 = nil
	is1 = append(is1, 1, 2, 3, 4, 5)
	// copy(destSlice, srcSlice []Type) int
	copy(is1, ai2[0:3])
	fmt.Println("is1 ", is1)
	is1 = is1[1:] // delete is[0]
	fmt.Println("is1 ", is1)
	is1 = append(is1[:1], is1[1 + 1:]...) // delete is[1]
	fmt.Println("is1 ", is1)
	// is1 = is1[0:len(is1) - 1]
	for k, v := range is1 { // _, v
		fmt.Printf("is1[%d]: %d\n", k, v)
	}

	var is2 [][]int
	is2 = [][]int{{123}, {1, 2, 3}}
	is2 = append(is2, []int{1, 2})
	is2[0] = append(is2[0], 4)
	fmt.Println("is2", is2)

	{
		// str = string1[start:end] //string1[:] stirng1[:n] stirng1[n:]// default : string1[0:len(string1)]
		ss := strings.Join([]string{"s","t", "r"}, "") // ss := "s" + "" + "t" + ""  + "r"
		// ss := fmt.Sprintf("%s%s", "st", "r")
		fmt.Println("len", ss, len(s),  bytes.Count([]byte(ss), nil), strings.Count(ss, ""))
		//utf8.RuneCountInString(ss)
		fmt.Println(strings.Split("code=100&status=ok", "&")) // strings.Field(s) Split(s, " ")
		// strings.FieldsFunc(s, f func(rune) bool)
		var buf bytes.Buffer
		for i := 0;i != 1000;i++ {
			buf.WriteString(str)
		}
		fmt.Println(buf.String()[0:100], strings.Count(buf.String(), "str"))
		pos := strings.Index(str, ss)
		// LastIndex
		pos2 := strings.LastIndexAny(str, "str") + 1 // "[str]" /[str][^str]$/

		fmt.Println("sub ", str[pos:pos2] + " ")
		// IndexByte(s string, c byte) int // LastIndexByte IndexRune LastIndexRune
		fmt.Println("hasPrefix", strings.HasPrefix(str, "["))
		// HasSuffix(str, suffix) bool
		fmt.Println("toTitle", strings.ToTitle(str)) // Upper
		// ToLower(s string) string // toUpper
		fmt.Println("TrimSpace", strings.TrimSpace(" < [str] > ")) // "< [str] >"
		// strings.Trim(s string, cutset string) string // strings.Trim(s, " ")
		// TrimLeft TrimLeft TrimPrefix TrimSuffix
		// TrimFunc(s string, f func(rune) bool) string // TrimLeftFunc TrimRightFunc
		fmt.Println("contains", strings.Contains(str, "str"))
		// ContainsRune ContainsAny
		// func Map(mapping func(rune) rune, s string) string
		// strings.Compare(a, b string) int // strings.EqualFold(a, b string) bool /* strings.EqualFold("abc", "ABC") true */ // a == b
		fmt.Println("repeat 5", strings.Repeat(str, 5))
		fmt.Println("r5 replace 3", strings.Replace(strings.Repeat(str, 5), "str", "STR", 3)) // -1 all
		// replace(s, old, new string) string // replace(s, old, new, -1)

		// var ch byte = 'c' // 
		// var ch rune = 'c' // unicode // \u0043 \U00101234
		// unicode.isLetter(ch) unicode.isDigit(ch) unicode.isSpace(ch)

	}

	// make(map[KeyType]ValueType, initialCapacity)
	// var mapname map[keytype]valuetype
	map1 := make(map[string]int)
	// make(map[keytype]valuetype, cap)
	// map[string][]int // struct
	var map2 map[string]int = map[string]int{"a":0, "b":1}
	for k, v := range as { // k := range ss // _, v := range ss
		map1[v] = k
	}
	map1["dd"] = 4
	map1["dd"] = 5
	map1["ccc"] = 10
	delete(map1, "ccc")
	fmt.Println("len(map1): ", len(map1))
	for k, v := range map1 {
		fmt.Printf("map1[%s]: %d\n", k, v)
	}
	map2["c"] = 5
	// v := map1["cc"]
	// k, v := map1["cc"]
	{
		var map3 sync.Map
		map3.Store("a", 1)
		map3.Store("b", 0)
		map3.Store("c", 5)
		if v, ok := map3.Load("b");ok {
			map3.Store("a", v)
			map3.Delete("b")
		}
		map3.Range(func(k, v interface{}) bool {
			fmt.Printf("map3[%s]: %d\n", k, v)
			return true
		})
	}

	// var list1 list.List
	list1 := list.New()
	element_1 := list1.PushBack(5)
	// PushFront
	list1.InsertAfter(4, element_1)
	list1.Remove(element_1)
	for i := list1.Front();i != nil;i = i.Next() {
		fmt.Println(i.Value)
	}


	// nil
	// fmt.Printf("nil %p\n", nil) // error
	// fmt.Printf("nil T %T, %d\n", nil, nil == nil) // error
	// map slice pointer channel func interface  default- nil

	// var ppp []int = new([100]int)[:]
	// var ppp2 []int = make([]int, 100, 100)


	fmt.Println("10! : ", factorial(10))
	retn, _ := strconv.Atoi("123")
	fmt.Println("f ", float64(retn), strconv.Itoa(retn))
	retnf64, err_1 := strconv.ParseFloat("42.177", 64) // ParseInt("97", 10, 64) ParseBool("true")
	// FormatBool(true) FormatFloat(1.0, 'E', -1, 64) FormatInt(5, 10) FormatUint(5, 10)
	// AppendInt([]int, 5, 10)
	fmt.Println("max", math.MaxInt8, math.MaxInt16, math.MaxInt32, math.MaxInt64)
	// fmt.Println(int32(3.14)) // 3
	if err_1 != nil {
		fmt.Println("err_1", err_1)
	} else {
		fmt.Println("retnf64 ", retnf64, strconv.FormatFloat(retnf64, 'f', 4, 64))
	}

	// fmt.Println("l ", p.method_1(0), p3.method_1(0))


	{
		var if1 interface{}
		if1 = "[str]"
		if str, bool_1 := if1.(string);bool_1 {
			fmt.Println("if1", str)
		}

		var if2 interface_1
		var method func(int) int
		p2 := point{5, 4}
		var p3 interface{} = &point3{4, 3, 2}
		if2 = p2
		r1 := if2.method_1(0)
		method = if2.method_1
		if2 = p3.(*point3)
		r2 := if2.method_1(0)
		fmt.Println(r1, r2, method(0))
		r1 = if2.method_2(0)
		if2 = interface_f2(func(if1 interface{}) int {
			if i, b := if1.(int);b {
				return i
			}
			return 0
		})
		r2 = if2.method_2(9)
		fmt.Println(r1, r2)
		// fmt.Printf("point2 method1", ret, err);
		var odd OddStruct = OddStruct{1, 2, 3, 4, point3{1, 2, 3}}
		fmt.Println("odd", odd, odd.int, odd.point3, odd.point3.x)
	}
	var g int 
	g = 10
	// ret , err := strconv.Atoi("100")
	// ret := strconv.Itoa(100)
	for i := 0;i != g;i++ {
		fmt.Println(i)
	}

	{
		s := "[str] [Zn2667] T_T [__str__] [cc2530]"
		reg1 := regexp.MustCompile(`\[.+?\]`)
		if reg1 == nil {
			fmt.Println("reg1_error")
			return
		}
		result := reg1.FindAllStringSubmatch(s, -1)
		fmt.Println("result: ", result)
		ok, _ := regexp.Match(`\d+`, []byte(s))
		_ = ok
		reg2 := regexp.MustCompile(`(?mi)__(.+?)__`) // multi line | ignore
		// regexp.Compile()
		ss := reg2.ReplaceAllString(s, "$1")
		// ReplaceAllStringFunc(src string, repl func(string) string, pattern string)
		fmt.Println("replace", ss)
	}


	{
		pa := SORTPOINT{{1, 2}, {2, 3}, {3, 1}, {1, 5}, {9, 0}, {5, 5}}
		sort.Sort(pa)
		fmt.Println(pa)
	}
	{
		bn := new(big.Int).SetUint64(uint64(1e17)) // Int Rat Float
		// new(big.Rat).SetFloat64(4.7)
		t := new(big.Int).SetUint64(1)
		n1 := new(big.Int).SetUint64(1)
		fmt.Println("big n ", bn)
		bn.SetString("1", 10)
		// func (z *Int) Add(x, y Int) (z *Int) // z = x + y
		// Sign() int
		// Div Mod // func (z *Int) DivMod(x, y, m *Int) (*Int, *Int)
		for i := 1;i < 100;i++ {
			bn.Mul(bn, t)
			t.Add(t, n1)
		}
		fmt.Println("big ! ", bn)
	}
	flag_string := flag.String("flag_string", "[str]", "string")
	flag_int := flag.Int("flag_int", 5, "int")
	flag_bool := flag.Bool("flag_bool", false, "bool")
	flag_duration := flag.Duration("flag_duration", 0, "duration")
	flag.IntVar(&x, "flag_x", 5, "x")
	flag.Parse()
	// flag.Args() flag.NArg() flag.NFlag()
	_, _, _, _ = *flag_string, *flag_int, *flag_bool, *flag_duration
	// log.Print log.Fatal log.Panic
	/* {
		// // import "test1"
		t := test1.NewTest1("str")
		fmt.Println(t.GetStr())
		t.SetStr("Zn2667 [str] ")
		fmt.Println(t.GetStr())
	} */
	// x := i++ // error
	{
		// chan1 := make(chan int)
		chan1 := make(chan int) // channel
		// chan1 := make(chan int, 100) // bufsize
		go goroutine_1(1, chan1)
		go goroutine_1(3, chan1)
		x, ok := <-chan1 // wait ret
		x = <-chan1
		fmt.Println("x", x, ok)
		close(chan1)
		// data, ok := <-chan1
		chan3 := make(chan interface{}, 2)
		chan3 <- 0
		chan3 <- "[str]"
		var if1 interface{}
		if1 = <- chan3
		if1 = <- chan3
		fmt.Println(if1) // [str]
		close(chan3)

		fmt.Println("lock: ", test_lock())
		// cv := sync.NewCond(&sync.Mutex{}) // cv.L.Lock() cv.L.Unlock() cv.Wait() cv.Broadcast()

		var wg sync.WaitGroup

		// ctx, cancel := context.WithTimeout(context.Background(), time.Second * 5) ; defer cancel
		// ctx context.Context
		ctx, cancel := context.WithCancel(context.Background())
		ctx_key := "key"
		ctx_v := context.WithValue(ctx, ctx_key, "[str]")
		var num int64
		run := func(c context.Context, i int) {
			// fmt.Println(c.getValue(), i)
			// time.Sleep(1 * time.Second)
			for {
				select {
					// chan bool // stop = true
					case _ = <-c.Done():
						fmt.Println("exit", i, c.Value(ctx_key))
						time.Sleep(time.Second * 1)
						wg.Done() // wg.Wait()
						return
					// case chan2 <- 0
					case <-time.After(time.Second * 5):
						fmt.Println("timeout", i)
						return
					default:
						fmt.Println("loop", i, c.Value(ctx_key))
						time.Sleep(time.Millisecond * 50)
						atomic.AddInt64(&num, 1)
				}
			}
		}
		n := runtime.NumCPU()
		// runtime.GOMAXPROCS(runtime.NumCPU())
		atomic.StoreInt64(&num, 0)
		for i := 0;i < n;i++ {
			go run(ctx_v, i)
		}
		wg.Add(n)
		time.AfterFunc(time.Millisecond * 100, cancel)
		// s := time.NewTicker(time.Millisecond * 50) // <- s.C 
		wg.Wait() // wg.Done()
		// <- time.After(time.Millisecond * 10000)
		fmt.Println("done", atomic.LoadInt64(&num))
	}
	{
		// address := "127.0.0.1:7788"
		address := "0.0.0.0:7788"
		l, err := net.Listen("tcp", address)
		if err != nil {
			log.Fatal(err)
		}
		defer l.Close()
		run := func(conn net.Conn) {
			reader := bufio.NewReader(conn)
			str, err := reader.ReadString('\n')
			if err == nil {
				conn.Write([]byte(str))
			} else {
				log.Print(err)
			}
			conn.Close()
		}
		go func() {
			for {
				conn, err := l.Accept()

				if err != nil {
					log.Print(err)
					break
				}
				go run(conn)
				break
			}
		}()
		var c net.Conn
		var n int
		c, err = net.Dial("tcp", address)
		if err != nil {
			log.Fatal(err)
		}
		c.Write([]byte("test\n"))
		var buf [100]byte
		n, err = c.Read(buf[:])
		fmt.Println("tcp_test_cmp: ", strings.Compare("test\n", string(buf[:n])), err)
	}
	{
		l, err := net.ListenUDP("udp", &net.UDPAddr {
			IP: net.IPv4(0, 0, 0, 0), Port: 7878 })
		if err != nil {
			log.Fatal(err)
		}
		go func() {
			defer l.Close()
			var buf [1024]byte
			var n int
			var addr *net.UDPAddr
			n, addr, err = l.ReadFromUDP(buf[:])
			if err != nil {
				log.Fatal(err)
			}
			_, err = l.WriteToUDP([]byte(fmt.Sprintf("addr: %v, n: %v\n%v", addr, n, string(buf[:n]))), addr)
			if err != nil {
				log.Fatal(err)
			}
		}()
		{
			l, e := net.DialUDP("udp", nil, &net.UDPAddr{ IP: net.IPv4(0, 0, 0, 0), Port: 7878 })
			if e != nil {
				log.Fatal(e)
			}
			defer l.Close()
			_, err = l.Write([]byte("test\n"))
			var buf [1024]byte
			n, addr, err := l.ReadFromUDP(buf[:])
			if err != nil {
				log.Fatal(err)
			}
			fmt.Printf("addr: %v, n: %v, recv: \n%v\n", addr, n, string(buf[:n])) 
		}
	}
	{
		chan1 := make(chan int)
		go func(chan1 chan int) {
			http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
				headers, forms, query, cookies := "", "", "", ""
				// Form // PostForm // - applicaition/x-www-form-urlencoded
				// type Header map[string][]string
				for k, v := range r.Header {
					headers += fmt.Sprintf("%v: %v ", k, v)
				}
				// r.Header.Get("User-Agent") // r.Header["User-Agent"] // delete(r.Header, "User-Agent") // r.Header.Has("User-Agent") // r.Header.Del("User-Agent") // r.Header.Write(w io.Writer) error
				// type Values map[string][]string
				for k, v := range r.Form {
					forms += fmt.Sprintf("%v: %v ", k, v)
				}
				// r.FormValue("key") r.PostFormValue("key")
				for k, v := range r.URL.Query() {
					query += fmt.Sprintf("%v: %v ", k, v)
				}
				for k, v := range r.URL.Query() {
					cookies += fmt.Sprintf("%v: %v ", k, v)
				}

				if r.Method == "POST" && strings.Contains(r.Header.Get("Content-Type"), "multipart/form-data") {
					
					// https://zhuanlan.zhihu.com/p/625141773
					// r.Body = http.MaxBytesReader(w, r.Body, 1024 * 1024 * 20 + 4096) // 20M
					dir, err := filepath.Abs("./upload")
					if err != nil {
						fmt.Println(err)
						http.Error(w, err.Error(), http.StatusBadRequest)
					}
					reader, err := r.MultipartReader()
					if err != nil {
						fmt.Println(err)
						http.Error(w, err.Error(), http.StatusBadRequest)
						return
					}
					var list [][2]string
					for {
						part, err := reader.NextPart()
						if err != nil {
							if err == io.EOF {
								break
							}
							http.Error(w, err.Error(), http.StatusInternalServerError)
							return
						}
						formName := part.FormName()
						fileName := part.FileName()
						if fileName == "" {
							str, err := ioutil.ReadAll(part)
							if err != nil {
								break
							}
							list = append(list, [2]string{formName, string(str)})
							continue
						}
						fileName = part.Header.Get("Content-Disposition") // "Content-Disposition" "Content-Type
						pos1 := strings.Index(fileName, "filename=\"")
						fileName = fileName[pos1 + 10:len(fileName) - 1]
						// var buf = &bytes.Buffer{}
						// fmt.Println(formName, fileName)
						fileAbsPath := filepath.Join(dir, fileName)
						dirAbsPath := filepath.Dir(fileAbsPath)
						_, err = os.Stat(dirAbsPath)
						if os.IsNotExist(err) {
							err = os.MkdirAll(dirAbsPath, 777)
						}
						if err != nil {
							break
						}
						// os.CreateFile(fileAbsPath, buffer)
						file, err := os.Create(fileAbsPath)
						if err != nil {
							break
						}
						io.Copy(file, part)
						file.Close()
						list = append(list, [2]string{formName, fileName})

					}
					if err != nil {
						http.Error(w, "Error: " + err.Error(), http.StatusInternalServerError)
						return
					}
					data, err := json.Marshal(list)
					http.Error(w, string(data), http.StatusOK)
					return
				}
				if r.RequestURI == "/test4.html" {
					// file, err := os.Open("test4.html")
					file, err := os.Open("./upload.html")
					if err != nil {
						http.Error(w, "404 Not Found.", http.StatusNotFound)
						return
					}
					// w.Header().Set("Location", "https://xxx.com")
					w.Header().Set("Content-Type", "text/html; charset=utf-8")
					// w.write([]byte(http.StatusText(200)))
					w.WriteHeader(200) // http.StatusOK
					io.Copy(w, file)
					return
				}
				/* func Redirect(w ResponseWriter, r *Request, url string, code int) */
				// file, header, err := r.FormFile("file") // header.filename
				// Cancel chan struct{}
				// w.Write([]byte(`{"code":200, "status": "ok"}`))
				// io.WriteHeader(200)
				cookie := &http.Cookie{Name: "cookie_1", Value: url.QueryEscape("[1,2]"), MaxAge: 36000, Path: "/"} // Path, Domain string, RawExpires Expires time.Time  maxAge int secure, httpOnly bool // SameSite SameSite Raw string unparsed []string
				// Expires: time.Now().AddDate(0, 0, 1)
				// http.SetCookie(w, cookie *Cookie)
				w.Header().Add("Set-Cookie", cookie.String())
				// request: Referer() string WithContext(ctx Context) *Request Write(w io.Write)
				fmt.Fprintf(w, "Method: %s\nRequestURI: %s\nURL: %s\nHeader: %s\nForm: %s\nQuery: %s\nCookie: %s\nProto: %s %d.%d\nContent-Length: %d\nTransferEncoding: %v\nClose: %v\nHost: %s\nRemoteAddr: %s\nRequestURI: %v\n", r.Method, r.RequestURI, r.URL, headers, forms, query, cookies, r.Proto, r.ProtoMajor, r.ProtoMinor, r.ContentLength, r.TransferEncoding, r.Close, r.Host, r.RemoteAddr, r.RequestURI)
				// http.Error(w, "400 Bad Request."， http.StatusBadRequest)
				// mime-type : text/html text/plain application/json application/xml applicatoin/javascript image/png image/jpeg audio/mpeg application/octet-stream
				// Response:
				// Status StatusCode Proto ProtoMajor ProtoMinor Header Body ContentLength TransferEncoding Close Uncompressed Trailer Request TLS


				// v, _ := ioutil.ReadFile("./index.html")
				/*
				proxy := &httputil..ReverseProxy{func(req *http.Request) {
					req.URL.scheme = "https"
					req.URL.Host = "xxx.com"
					req.URL.Path = "path"
				}}
				proxy.ServerHTTP(w, r)
				*/
			})
			chan1 <- 0
			http.ListenAndServe("localhost:8078", nil)
			// http.ListenAndServeTLS(":443", "server.crt", "server.key", nil)
		}(chan1)
		<- chan1
		close(chan1)
		const (
			Fkey = "../cert/rsa_private.key" 
			Fcert = "../cert/cert.pem"
			Fca = "../cert/ca.pem"
		)
		var err error = nil
		var transport *http.Transport = &http.Transport{TLSClientConfig: &tls.Config{InsecureSkipVerify: true}}
		for {
			break
			ca_pem, err := ioutil.ReadFile(Fca)
			if err != nil {
				break
			}
			certPool := x509.NewCertPool()
			certPool.AppendCertsFromPEM(ca_pem)
			cert, err := tls.LoadX509KeyPair(Fcert, Fkey)
			if err != nil {
				break
			}
			transport = &http.Transport { TLSClientConfig: &tls.Config { RootCAs: certPool, Certificates: []tls.Certificate{cert}}} // InsercureSkipVerify: true
			break
		}
		/*
		resp, _ := http.Get("http://bing.com");
		data := make(map[string]string); dataJson := json.Marshal(data); reader := bytes.NewBuffer(dataJson)
		resp2, _ := http.Post("http://post.com/post", "application/json;charset=utf-8", reader)
		resp2, _ := http.Post("http://post.com/post", url.Values{"user": "root", "code": 100})
		formValues := url.Values{}
		formValues.Set("key", "value")
		reader := bytes.NewReader([]byte(formValues.Encode()))
		resp, _ := http.Post("http://post.com/post", reader)

		var buffer bytes.Buffer
		f, err := os.open(file)
		writer := multipart.NewWriter(&buffer) // Multipart.Writer
		writer.WriteField("json", `{"code":200, "status": "OK"}`)
		part, err := writer.CreateFormFile(filedName, file) // "file" "main.go"
		io.Copy(part, f)
		writer.Close()
		req, err := http.NewRequest("POST", url, &buffer) // writer
		req.Header.Set("Content-Type", writer.FormDataContentType())
		*/
		var client *http.Client = &http.Client{ Timeout: 5 * time.Second, Transport: transport} // &http.Client{}
		req, err := http.NewRequest("GET", "http://127.0.0.1:8078/?key=key1", nil)
		// func NewRequest(method, url string, body io.Reader) (*Request, error) 
		// req, err := http.NewRequest("GET", "https://www.bing.com/", nil)
		req.Header.Add("User-Agent", "REQUEST")
		// req.AddCookie(cookie *http.Cookie)
		// resp, err := client.Get("http://xxx.com/")
		resp, err := client.Do(req)
		// resp, err = client.Get("http://127.0.0.1:8078/?key=key1")
		if err != nil {
			log.Fatal(err)
		}
		ret, err := ioutil.ReadAll(resp.Body)
		resp.Body.Close();
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println("RET: ", string(ret[:]))
		client.CloseIdleConnections()
	}
	{
		p1 := TMP{1, 2, 4.7}
		var tp reflect.Type = reflect.TypeOf(p1)
		// tp2 := reflect.New()
		fmt.Println(tp.Name(), tp.Kind(), " ", tp.NumField(), tp.Field(0), tp.Field(1))
		// kind: Invalid Bool int Int32 Uint32 Int64 Float64 Chan Array Complex64 Map Interface Ptr Slice String Struct UnsafePointer
		if t, ok := tp.FieldByName("F");  ok {
			fmt.Println(t.Tag.Get("str"))
		}
		var u64 uint64 = 10
		vu := reflect.ValueOf(u64)
		fmt.Printf("%#v\n%#v\n", tp, vu)
		fmt.Println("vu", vu.Type(), vu.Kind() == reflect.Uint64, uint64(vu.Uint()), vu.Interface().(uint64))
		reflect.ValueOf(&u64).Elem().SetUint(5) // reflect.ValueOf(&u64).Elem().CanSet() // true
		// SetInt(int64) SetUint SetFloat SetBool SetBytes SetString
		vp := reflect.ValueOf(&p1).Elem()
		// Elem(): *p // Addr(): &p
		fmt.Println("vp", vp.Type(), vp.CanAddr(), vp.CanSet(), vp.Addr().IsNil(), vp.IsValid())
		for i := 0;i < vp.NumField(); i++ {
			f := vp.Field(i)
			fmt.Printf("%d: %s %s = %v\n", i, vp.Type().Field(i).Name, f.Type(), f.Interface())
		}
		// reflect.Interface

		fv := reflect.ValueOf(max_1)
		params := []reflect.Value{reflect.ValueOf(5), reflect.ValueOf(4)}
		ret := fv.Call(params)
		fmt.Println(ret[0].Int())
	}
	{
		// strings.Compare(s1, s2)
		var s string
		var err error
		s, err = os.Hostname()
		fmt.Println(s, err)
		env := os.Environ()
		for _, v := range env {
			if pos := strings.Index(v, "PATH"); pos == 0 {
				fmt.Println(v)
			}
		}
		_ = os.Getenv("PATH")
		// func Setenv(key, value string) error
		// os.Exit(0)
		// Getuid() Getgid() Getpid()
		s, err = os.Getwd()
		fmt.Println("pwd", s, err)
		// err = os.Mkdir("abc", nil) // Mkdir(name string, perm FileMode) error // MkdirAll
		// Remove(name string) error // RemoveAll(name string)
		s, e := exec.LookPath("go")
		if e == nil {
			fmt.Println("go.exe: ", s)
		}
		// "os/user" // user.Current() (*User, error)
		if false {
			c := make(chan os.Signal, 0)
			signal.Notify(c)
			signal.Stop(c)
			sig := <- c // wait
			fmt.Println("sig: ", sig)
		}
	}
	{
		// func NewReader(rd io.Reader) *Reader // func NewReaderSize(rd io.Reader, bufsize int) *Reader // 
		data := []byte("[str], Zn2667, nullptr")
		var buf [1024]byte
		// var c byte
		var rd *bytes.Reader = bytes.NewReader(data)
		var r *bufio.Reader = bufio.NewReader(rd) // os.Stdin, new.Conn
		n, err := r.Read(buf[:])
		s := string(buf[:n])
		fmt.Println(s, err)
		r = bufio.NewReader(bytes.NewReader(data))
		// c, err = r.ReadByte() (c byte, err error) // string(c)
		// r, er := r.ReadRune() (r rune, size int, err error) // string(r)
		line, e := r.ReadBytes(byte('\n'))
		// line, isPrefix, e := r.ReadLine() // ReadLine() (line []byte, isPrefix bool, err error) // isPrefix = true  len(line) < ReadBytes('\n')
		// line, e := r.ReadSlice(byte('\n')) // ReadSlice(delim byte) (line [byte, error) // no delim  ErrBufferFull
		fmt.Println("readline? ", string(line), e)
		// ss, er := bufio.NewReader(bytes.NewReader(data)).ReadString(byte('\n'))
		// Buffered()
		// Peek(n int) ([]byte, error) // temporary result || io.Reader | bufio.ErrBufferFull | EOF
		// UnreadByte() error // cancel read c
		// UnreadRune() err //
		
		// func NewWriter(wr io.Writer) *Writer
		// NewWriterSize(wr io.Writer, size int) *Writer
		// Available() int // Available-bufsize
		// Discard(5) // skip
		// WriteTo(w Writer) (n int64, err error)
		wr := bytes.NewBuffer(nil)
		w := bufio.NewWriter(wr)
		n, err = w.Write([]byte("[str]"))
		fmt.Println("buf ", w.Available(), w.Buffered(), w.Available() + w.Buffered()) // unused writed
		// Write(p []byte) (nn int, err error)
		// w.Flush()
		// WriteByte(c byte) error
		// WriteRune(r rune) (size int, err error)
		// WriteString(s string) (size int, err error)


		// ReadWriter(r, w)
	}
	{
		f, e := os.Create("f.json")
		if e != nil {
			log.Fatal(e)
		}
		json_s1 := private_json_1{200, "OK", []string{"[str]", "[STR]", "VALUE"}}
		encoder := json.NewEncoder(f)
		err := encoder.Encode(json_s1)
		if err != nil {
			log.Fatal(err)
		}
		f.Close()
		f, e = os.Open("./f.json")
		if err != nil {
			log.Fatal(err)
		}
		defer f.Close()
		decoder := json.NewDecoder(f)
		err = decoder.Decode(&json_s1)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(json_s1)
		var data []byte
		data, e = json.Marshal(json_s1)
		e = json.Unmarshal(data, &json_s1)
		fmt.Println(string(data))

		xml_s1 := private_xml_1{xml.Name{}, "private_xml_1.tag", "[str]", []pxml_wrap{pxml_wrap{1, "a"}, pxml_wrap{2, "b"}}}
		// encoder2 := xml.NewEncoder(f)
		// err = encoder2.Encode(xml_s1)
		data, e = xml.Marshal(xml_s1)
		e = xml.Unmarshal(data, &xml_s1)
		// fmt.Println("x", xml_s1)

		data2 := base64.StdEncoding.EncodeToString(data)
		data, e = base64.StdEncoding.DecodeString(data2)
		// StdEncoding URLEncoding RawStdEncoding RawURLEncoding
		fmt.Println("XML", string(data2), string(data)) 

		f, e = os.OpenFile("f.gob", os.O_RDWR|os.O_CREATE, 0777)
		if e != nil {
			log.Fatal(e)
		}
		//defer f.Close()
		encoder2 := gob.NewEncoder(f)
		err = encoder2.Encode(xml_s1)
		if err != nil {
			log.Fatal(err)
		}
		f.Close()

		f, err = os.OpenFile("f.txt", os.O_WRONLY|os.O_CREATE, 0777)
		if err != nil {
			log.Fatal(err)
		}
		var w1 *bufio.Writer = bufio.NewWriter(f)
		w1.WriteString("[str]\nstr\n[STR]\n[strstr]\n[STRSTR]\n")
		w1.Flush()
		f.Close()
		f, e = os.OpenFile("f.gob", os.O_RDWR, 0777)
		// O_RDONLY OWRONLY O_RDWR O_APPEND O_CREATE O_EXCEL O_SYNC O_TURNC
		if e != nil {
			log.Fatal(e)
		}
		// encodedStr := hex.EncodeToString(src)
		// str, e = hex.DecodeString(encodeStr)
		// fmt.Println(f.Size())
		var buf [1024]byte
		var n int
		var str string = ""
		for {
			n, e = f.Read(buf[:4])
			if e != nil || n == 0 {
				break
			}
			if n < 4 {
				str += hex.EncodeToString(buf[:n])
				break
			}
			var u uint32
			b := bytes.NewBuffer(buf[:n])
			e = binary.Read(b, binary.LittleEndian, &u)
			// binary.Write(&b, binary.LittleEndian, n)
			if e != nil {
				log.Fatal(e)
			}
			str += fmt.Sprintf("%X", u)
		}
		// os.Remove(fileName)
		// os.Mkdir(dname,  ModeDir|os.ModePerm) //
		// os.MkdirAll
		// io.SeekStart io.SeekCurent io.SeekEnd
		fmt.Println(str)
		var cur int64
		cur, e = f.Seek(0, io.SeekStart)
		_ = cur
		// Trurncate(Size int64) error // os.Truncate(name string, size int64) error // file size = size
		// Os.FileInfo
		fmt.Println(f.Stat())
		// Name() Size() Mode() ModTime() IsDir() Sys()
		// ReadAt(buf, off)
		f.Close()
		f, e = os.OpenFile("f.zip", os.O_RDWR | os.O_CREATE, 0777)
		wzip := zip.NewWriter(f) // bf := new(bytes.Buffer)
		ff , e := wzip.Create("d/README.md")
		_, e = ff.Write([]byte("# README\n"))
		ff , e = wzip.Create("a.txt")
		_, e = ff.Write([]byte("[str]\n"))
		wzip.Close()
		// bf.WriteTo(f)
		f.Close()

		rzip, err := zip.OpenReader("f.zip")
		if err != nil {
			log.Fatal(err)
		}
		for t, f := range rzip.File {
			fmt.Printf("f.zip: %s %T\n", f.Name, t)
			r, e := f.Open()
			if e != nil {
				log.Fatal(e)
			}
			// io.Copy(w, r)
			_, e = io.CopyN(os.Stdout, r, int64(f.UncompressedSize64))
			if e != nil {
				log.Fatal(e)
			}
			r.Close()
		}
		rzip.Close()
	}
	// pr, pw := io.Pipe()
	// fmt.Println("\\", filepath.ToSlash("D:\\home\\demo\\"))
	// FromSlash("D:/home/demo/")
	// fmt.Println("dir", filepath.Dir("D:\\home\\demo\\README.md")) // D:\home\demo
	// fmt.Println("base", filepath.Base("D:\\home\\demo\\README.md")) // README.md
	// Func Split(path string) (dir, file string) // dir + file = Dir() + Base()
	// fmt.Println("ext", filepath.Ext("D:\\home\\demo\\README.md")) // .md
	// rel_p, e := filepath.Rel("D:\\home\\demo\\", "D:\\home\\demo\\go"))
	// Join(elem ... string) string  path = elem1 + elem2 + elem3
	// Clean(path string) string // /./././../ ../
	// IsAbs(path string) bool
	// fmt.Println(filepath.Abs("main.exe")) // (ret string, err error)
	// SplitList(path string) []string // /usr/bin/;/home/d/demo/cpp/build/bin
	// fmt.Println("volume", filepath.VolumeName("D:\\home\\demo\\README.md")) // D:
	// Mathch(pattern, name string) (bool, err) // Match("/home/u/*.txt", "/home/u/a.txt")
	// Glob(pattern) ([]string, error) // Glob("D:/home/*.txt") ["D:/home/a.txt", "D:home/level.text"]
	// e = filepaht.Walk(pwd, func(fpath string, info os.FileInfo, err error) error {fmt.Println(fpaht, info.Name(), info.Size(), info.ModTime());return nil})
	ccc := make(chan Ldir_st)
	go Ldir("./", ccc)
	for data := range ccc {
		fmt.Println("c", data.Name, data.Size)
	}
	// syscall.Flock(int(f.Fd()), syscall.LOCK_EX|syscall.LOCK_NB) // LOCK_SH LOCK_EX LOCK_UN
	// ioutil.copy()
	ioutil.Discard.Write([]byte("[str]")) // echo "[str]" > /dev/null
	// ioutil.ReadAll(r io.Reader) ([]byte, error)
	// ioutil.ReadFile(filename string) ([]byte, error) // ReadAll
	// ioutil.WriteFile(filename string, data []byte, perm os.FileMode) error
	// ioutil.ReadDir(dirname string) ([]os.FileInfo, error)
	// ioutil.NopCloser(r io.Reader) io.ReadCloser // r to io.ReadCloser
	// ioutil.TempFile(dir, prefix string) (f *os.File, err error) // temp_file : prefix_xxxx
	// ioutil.TempDir(dir, prefix string) (name string, error)
}
