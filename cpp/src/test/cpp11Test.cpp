#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <random>
#include <regex>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>

#include "test.h"

// using namespace std;
namespace test1
{
	class wrapInt
	{
		public:
			wrapInt();
			// wrapInt()=delete; // disable
			wrapInt(const int i);
			wrapInt(const wrapInt& c);
			wrapInt(wrapInt&& c);
			~wrapInt();
			int get() const;
			void set(const int);
			int *getptr() const;
			friend std::ostream& operator<<(std::ostream&, const wrapInt&);
		private:
			int *wrap;
	};
	wrapInt::wrapInt()
	{
		wrap = new int;
		*wrap = 0;
	}
	wrapInt::wrapInt(const int i)
	{
		wrap = new int;
		*wrap = i;
	}
	wrapInt::wrapInt(const wrapInt& w)
	{
		wrap = new int;
		*wrap = *(w.getptr());
	}
	wrapInt::wrapInt(wrapInt&& w)
	{
		this->wrap = w.wrap;
		w.wrap = nullptr;
	}
	wrapInt::~wrapInt()
	{
		delete wrap;
	}
	int wrapInt::get() const
	{
		return *wrap;
	}
	void wrapInt::set(const int i)
	{
		*wrap = i;
	}
	int* wrapInt::getptr() const
	{
		return wrap;
	}
	std::ostream& operator<<(std::ostream& o, const wrapInt& w)
	{
		o << w.get();
		return o;
	}


	template <typename T>
	const char* getLR(const T& t)
	{
		(void)t;
		return static_cast<const char *>("L");
	}
	template <typename T>
	const char* getLR(const T&& t)
	{
		(void)t;
		return static_cast<const char *>("R");
	}
	template <typename T>
	const char* getLRF(T && t)
	{
		return getLR(std::forward<T>(t));
	}
	template <typename T>
	T sum(std::initializer_list<T> list)
	{
		T s = 0;
		for(auto it = list.begin();it != list.end();++it)
			s += *it;
		return s;
	}
	class wrapInt2
	{
		private:
			int *ptr;
		public:
			// wrapInt2() = default;
			wrapInt2()
			{
				this->ptr = new int;
			}
			explicit wrapInt2(const int n) : wrapInt2()
			{
				*ptr = n;
			}
			// wrapInt2(const int&& n) = delete;
			explicit wrapInt2(wrapInt2& w) : wrapInt2()
			{
				*ptr = w.get();
			}
			explicit wrapInt2(wrapInt2&& w)
			{
				ptr = w.ptr;
				w.ptr = nullptr;
			}
			~wrapInt2()
			{
				delete ptr;
			}
			int get() const
			{
				return *ptr;
			}
			void set(const int i)
			{
				*ptr = i;
			}
			int *getptr() const
			{
				return ptr;
			}
			virtual int vInt() const
			{
				return 0;
			}
			int *getP() const && // Rvalue
			{
				return ptr;
			}
			int *getP() const &
			{
				return nullptr;
			}
	};
	class wrapInt3 final : public wrapInt2
	{
		using wrapInt2::wrapInt2;
		friend wrapInt2;
		public:
			virtual int vInt() const override
			{
				return 1;
			}
	};
	struct AAA{
		AAA() = default;
		AAA(int a) = delete;
		AAA(const int aa, const int bb):a(aa), b(bb){}
		int a;
		int b;
		void print1(void) const
		{
			std::cout << a << '\t' << b << std::endl;
		}
	};
	enum class Color1 : int
	{
		red,
		green,
		blue,
		yellow,
		gray,
		black,
		white,
		none
	};
	union UA{
		int a;
		wrapInt w;
	};
};


using test1::wrapInt;
using test1::wrapInt2;
using test1::wrapInt3;
using test1::Color1;
using test1::getLR;
using veci = std::vector<int>;

static int func1(const int i)
{
	return i;
}
static std::string strcat5(const std::string a, const std::string b, const std::string c, const std::string d, const std::string e)
{
	return a + b + c + d + e;
}

static void threadTest(void)
{
	using namespace std;
	bool condition1 = true;
	function<void(const int)> f1 = [&condition1](const int j)
	{
		// thread_local int ii = 0; // threadsafe
		std::cout << "t" << j <<" id: " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::nanoseconds(10)); // std::chrono::duration<std::chrono::nanoseconds>
		// std::this_thread::sleep_for(100ms); // C++ 14
		// chrono::microseconds(10) + chrono::milliseconds(10) + chrono::seconds(10) + chrono::minutes(1) + chrono::hours(1)
		// std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1)); // std::chrono::system_clock::time_point // steady_clock system_clock high_resolution_clock
		// duration_cast<std::chrono::microseconds> sub1 = ((std::chrono::system_clock::now() + std::chrono::seconds(1)) - std::chrono::system_clock::now()).count();
		while(!condition1)
			std::this_thread::yield();
	};
	thread t1(f1, 1);
	/*
	if(t1.joinable()) {
		t1.detach();
	}
	*/
	std::cout << "thread_id " << t1.get_id() << "\tcpu: " << thread::hardware_concurrency() << std::endl;
	t1.join();

	int v = 0; // volatile int v = 0;
	std::atomic<int> v2;
	mutex mutex_1;
	// std::timed_mutex mutex_2;
	// std::recursive_mutex mutex_3;
	std::recursive_timed_mutex mutex_4;
	std::once_flag once_flag;
#define LOCK_MODE 1
	function <void(int*)> f2 = [&](int* v)
	{
		int i;
		const int n = 50;
		std::call_once(once_flag, [&]()
			{
				v2 = 0;
			});
		v2 += n; // std::atomic<int> 
#if LOCK_MODE == 0
		std::lock_guard<std::mutex> lock(mutex_1); // lock
		// std::unique_lock<std::mutex> lock(mutex_1);
#endif
		for(i = 0;i != n;++i)
		{
#if LOCK_MODE == 1
			mutex_1.lock(); // try_lock();
#endif
			++(*v);
#if LOCK_MODE == 1
			mutex_1.unlock();
#endif
		}
		{
			std::function<void(void)> func1 = [&](void)
			{
				mutex_4.lock();
				std::this_thread::sleep_for(std::chrono::nanoseconds(10));
				mutex_4.unlock();
			};
			if(mutex_4.try_lock_for(std::chrono::milliseconds(200))) // try_lock() try_lock_until()
			{
				func1(); // same thread
				mutex_4.unlock();
			}
		}
		// lock auto_unlock
	};
	int i = 0;
	thread th[7];
	for(i = 0;i != 7;++i)
		th[i] = thread(f2, &v);
	for(thread& t : th)
		t.join();
	C2(v == 7*50);
	C2(v2 == v); // std::atomic<int>
}
static void threadTest2()
{
	using namespace std;
	int v = 0;
	mutex mutex_1;
	std::condition_variable cv;
	// std::condition_variable_any cv; // std::timed_mutex
	function<void(void)> f1 = [&](void)
	{
		std::unique_lock<std::mutex> lock(mutex_1);
		
		cv.wait(lock, [&v](void){return (v!=0);});
		v += v;
		lock.unlock();
		cv.notify_one();
	};
	function<void(void)> f2 = [&](void)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(200));
		mutex_1.lock();
		v = 7;
		mutex_1.unlock();
		cv.notify_one();
		// cv.nodify_broadcast() // nodify_all;
	};
	std::cout << "start --- \n";
	thread t1(f1);
	thread t2(f1);
	thread t3(f2);
	t1.join();
	t2.join();
	t3.join();
	C2(v == 28);
	std::cout << "end" << std::endl;
	thread t4([&](void)
	{
		std::unique_lock<std::mutex> lock(mutex_1, std::defer_lock);
		lock.lock();
		lock.unlock();
		if(lock.try_lock())
			lock.unlock();
		std::unique_lock<std::mutex> lock2(std::move(lock));
		std::mutex *original_mutex = lock2.release();
		C2(original_mutex == &mutex_1);
	});
	t4.join();
	std::promise<int> p1;
	std::future<int> fu = p1.get_future();
	std::thread t5([](std::future<int>& fu)
	{
		C2(fu.get() == 5);
	}, std::ref(fu));
	p1.set_value(5);
	t5.join();

	std::packaged_task<int(int)> task([](const int i){return i + i;});
	std::future <int> fut = task.get_future();
	std::future_status status;
	std::thread t6(std::move(task), 5);
	std::string s = "-";
	t6.detach();
	status = fut.wait_for(std::chrono::milliseconds(1));
	if(status == std::future_status::ready)
		s = "ready"; // done
	else if(status == std::future_status::timeout)
		s = "timeout";
	else if(status == std::future_status::deferred)
		s = "deferred";
	std::cout << "status1:" << s << std::endl;
	// status = future.wait();
	C2(fut.get() == 10);

	std::future<int> async1 = async(std::launch::async, [](const int i)->int
	{
		return i;
	}, 0);
	// std::launch::deferred // wait() get()
	C2(async1.get() == 0);
	// async1.wait_for();
	// async1.wait();
}
static constexpr int func_constexpr(const int i)
{
	return i * 5;
}

static constexpr int operator"" _type1 (unsigned long long n) {
	return (int)n;
}

std::vector<int> vecXY(const int x, const int y)
{
	return {x, y};
}

void cpp11Test(void)
{
using namespace std;
	auto i = 5; // int a = 5;
	const int& a = i; // & lvaule
	// const auto& ir = i;
	decltype(a) b = i; // const &
	// const int&& r = std::move(5); // && rvalue
	const int&& a5 = 5; // && rvalue
	const int * const ip = &i;
	// const int *ip; ++(*ip) error
	// int * const ip; ++ip error
	// const int * const * const p;
	// const int * const & pp = &i; // int *&pp;
	(void)(i&&a&&b&&a5&&ip);
	wrapInt w1(5);
	wrapInt w2(w1); // w1.getptr() != w2.getptr()
	wrapInt w3 = std::move(w2); // w2.getptr() == nullptr && w3.getptr != nullptr
	C2(w2.getptr() == nullptr && w3.getptr() != nullptr); // TRUE
	C2(getLR(5));
	C2(getLR(i));
	C2(getLR(a));
	C2(getLR(static_cast<int>(i)));
	// C2(getLR(const_cast<int>(i)));
	C2(getLR(std::move(5)));
	C2(getLR(std::forward<int>(i)));
	C2(getLR(std::forward<int&>(i)));
	C2(getLR(std::forward<int&&>(i)));

	// glvalue = lvalue + xvalue
	// rvalue = prvalue + xvalue


	C2(sizeof(long long) == 8);

	int k{5};
	// int* ip = new int{3};
	// int* iarr = new int[] {1, 2, 3};
	int g(5);
	C2(k == g);
	C2(test1::sum({1, 2, 3, 4}));
	// std::vector<int> vec = {1, 2, 3};
	std::function<void(void)> m = cpp11Test;

	m = [](void) {std::cout << "func" << std::endl;};
	std::function<int(void)> func1_5 = std::bind(&func1, 5);
	// auto ff = []<typename T>(T& t1, T& t2) -> T& {return t1 + t2;}; // C++14
	C2(func1_5());
	std::function<int(const wrapInt&)> wrapInt_get = &wrapInt::get;
	C2(wrapInt_get(w1) == 5);
	std::function<std::string(std::string, std::string)> show1 = std::bind(strcat5, "arr[", std::placeholders::_1, "]: ", std::placeholders::_2, ";");
	C2(show1("5", "6"));

	std::function<void(const int&)> l1 = [](const int& i){(void)i;};
	l1(5);
	std::function<int(const int&)> l2 = [](const int& i)->int {return i;};
	C2(l2(5) == 5);
	std::function<wrapInt&(wrapInt&)> l3 = [](wrapInt &w)->wrapInt&{return w;};
	l3(w1);
	std::function<int(void)> fc = [=]()->int{return i;/* i++ */}; // auto i = 5
	C2(fc() == 5);
	fc = [&]()->int{return i++;};
	C2(fc() == --i);
	// [this]
	// [=,&i] // int k, int g, int& i
	// [&,a] // int& k, int& g, int i
	// [&i, k] // int &i, int k
	// using namespace std;using std::placeholders; function<int(int, int, int)> add2 = bind(add, _1, bind(add, _2, bind(add, _1, _3)));
	// std::function<int*(const wrapInt&)> wrapInt_wrap = &wrapInt::wrap; // private


	threadTest();
	threadTest2();

	std::shared_ptr<int> p1 = std::make_shared<int>(); // reference = 1;
	std::shared_ptr<int> p2 = p1; // ++reference
	auto p3 = p2; // ++reference
	int *p4 = p1.get();
	*p4 = 5;
	// p1->
	// p1.reset();
	// p1.swap(p5); // std::swap(p1, p5);
	// std::swap(p1, p5);
	function<int(std::shared_ptr<int> p)> fsp = [](std::shared_ptr<int> p)->int{return *p;};
	C2(fsp(p1) == *p1);
	std::shared_ptr<int> p5(new int,[](int *p){delete p;});
	// std::shared_ptr<int> p17 = std::make_shared<int>();
	std::weak_ptr<int> p6 = p5; // no ++reference
	std::weak_ptr<int> p7 = p1; 
	p6.swap(p7); // swap
	p7.reset();
	C2(p6.use_count() == 3);
	if(!p6.expired())
		p7 = p6.lock(); // null shared_ptr
	C2(p7.lock() == p6.lock());
	// struct C{weak_ptr<int> a};
	std::unique_ptr<int> p8(new int);
	// std::make_unique<int>()
	std::unique_ptr<int> p9 = std::move(p8);
	*p9 = 5;
	p9.release();
	(void)(p1&&p2&&p3&&p4&&p5);
	std::shared_ptr<wrapInt> p10(new wrapInt {5});
	C2(p10->get() == 5);

	std::vector<std::string> vec1 {"abc", "loc", "cc", "lt", "lc"};
	std::string s = "[+]";
	vec1.push_back(std::move(s));
	s = "[str]";
	vec1.push_back(std::move(s));
	s = "";
	for(const std::string& ss : vec1)
	{
		s += ss;
	}
	std::cout << s << std::endl;

	wrapInt3 w4(4);
	C2(w4.get() == 4);
	wrapInt2 w5(dynamic_cast<wrapInt2&&>(w4));
	C2(w5.getP() != std::move(w5).getP());
	// uintptr_t up = reinterpret_cast<uintptr_t>(ip);

	i = func_constexpr(i); // function
	i = func_constexpr(1); // const
	// constexpr size_t isize = sizeof(int);
	// mutable size_t isize = sizeof(int); // isize = 5;

	Color1 c1 = Color1::red;
	C2(c1 == Color1::red);
	using test1::AAA;
	// C2(sizeof(AAA::a) == sizeof(int));
	static_assert(sizeof(AAA::a) == sizeof(int), "static_assert_err1");
	i = 5_type1; // constexpr operator"" _type1

	// std::aligned_storage<sizeof(int), alignof(int)>::type align1; // alignof(int) == std::alignment_of(int)
	// int *ii = new (&align1) int;
	// long long
	// char16_t c16; char32_t c32;
	std::default_random_engine random_1(time(nullptr));
	std::uniform_int_distribution<int> rand_int(0, 99);
	std::uniform_real_distribution<float> rand_float(0.0, 99.0);
	std::cout << rand_int(random_1) << '\t' << rand_float(random_1) << std::endl;

	s = "abcdefg[str]x0y1z3[str]end;";
	int ct = 0;
	std::regex reg_str("\\[str\\]", std::regex_constants::icase);
	if(std::regex_search(s, reg_str))
	{
		std::sregex_iterator begin1(s.begin(), s.end(), reg_str);
		std::sregex_iterator end1 = std::sregex_iterator(); // std::sregex_iterator end1;
		std::sregex_iterator s1;
		// std::cout << std::distance(begin1, end1) << std::endl;
		for(s1 = begin1;s1 != end1;++s1)
		{
			std::smatch match_1 = *s1;
			std::string s2 = match_1.str();
			ct += (int)s2.size();
		}
	}
	C2(ct == 10);
	std::string s3 = "";
	std::smatch results;
	string::const_iterator begin2 = s.begin();
	string::const_iterator end2 = s.end();
	while(std::regex_search(begin2, end2, results, regex("[a-z0-9]+")))
	{
		s3 += results.str() + "\t";
		// s3 += results[0] + "\t";
		begin2 = results[0].second;
	}
	std::cout << s3 << std::endl;
	// std::match(s, regex); std::match(s, results, regex);// std::search(str, results, regex);
	s3 = std::regex_replace(s, std::regex("([0-9a-zA-Z]+)"), "[$1]");
	std::cout << s3 << std::endl;

	// std::forward_list<int> f_list = {1, 2, 3};
	// std::list<int> list<int list = {1, 2, 3}; // LinkedList
	// std::unordered_set std::unordered_map //O(1)
	// std::unordered_multiset std::unordered_multimap
	std::tuple<int, bool, int> tuple1(5, true, 7);
	C2(std::get<0>(tuple1) == 5);
	// make_tuple(1L, 1U, 1.6);
	C2((std::is_same<int, std::tuple_element<0, decltype(tuple1)>::type>::value == true));
	// auto [x, y, z] = tuple1; C2(x == 5 && y == true && z == 1); // C++ 17

	std::vector<int> vec2 {1, 2, 3, 4, 5, 7, 9};
	std::vector<int>::iterator it;
	// iteratro begin() // const_iterator cbegin()
	// int arr1 = {1, 2, 3, 4};
	bool bl;
	bl = std::all_of(vec2.cbegin(), vec2.cend(), [](const int i){return i > 0;}); // true
	// std::all_of(std::begin(arr1), std::end(arr1), [](const int i){return i > 2}); //false
	bl = std::any_of(vec2.cbegin(), vec2.cend(), [](const int i){return i > 5;}); // true
	bl = std::none_of(vec2.cbegin(), vec2.cend(), [](const int i){return i == 0;}); // true
	it = std::find(vec2.begin(), vec2.end(), 5);
	it = std::find_if(vec2.begin(), vec2.end(), [](const int i){return i == 5;});
	it = std::find_if_not(vec2.begin(), vec2.end(), [](const int i){return i < 5;});
	//std::vector<int> vec3(5); std::itoa(vec3.begin(), vec3.end(), 1); // {1, 2, 3, 4, 5}
	std::vector<int> vec3;
	// vec3.reverse(vec2.size() * 2);
	std::copy(vec2.begin(), vec2.end(), std::back_inserter(vec3));
	// std::back_insert_iterator<std::vector<int>> output_iter = std::copy_if(vec2.begin(), vec2.end(), std::back_inserter(vec3), [](const int i) { return i > 2;});
	it = std::copy_if(vec2.begin(), vec2.end(), vec3.begin(), [](const int i) { return i > 2;});
	bl = std::is_sorted(vec2.begin(), vec2.end(), [](const int a, const int b){ return a - b;});
	// vec3.resize(std::distance(vec3.begin(), it));
	// ForwardIterator is_sorted_until (ForwardIterator first, ForwardIterator last, Compare comp); // ForwardInterator is_sorted_until (ForwardIterator first, ForwardIterator last);
	vec3 = vecXY(1, 2);
	// remove_cv; remove_const; remove_volatile; remove_reference; // add_cv add_const add_volatile // moduleTest.cpp
	(void)bl;

}



