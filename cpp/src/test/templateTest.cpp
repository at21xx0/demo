#include <iostream>
#include <type_traits>
#include <vector>
#include <cstring>
#include <string>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#include "test.h"




namespace template1
{
	// modluleTest.hpp
	using std::size_t;
	template <typename T> T add(const T a, const T b)
	{
		return a + b;
	}
	template <typename T> T& add2(const T& a, const T& b)
	{
		return a + b;
	}
	int add2(const int a, const int b)
	{
		return a + b;
	}
	/* C++ 14
	template <typename T, typename Q> auto add3(T t, Q q)
	{
		return t + q;
	}
	*/
	template <typename T = int, T N = 5>
	/* inline */ constexpr T mulC(T t)
	{
		return N * t;
	}
	template <size_t N> void char0(char (&arr)[N])
	{
		char *p = reinterpret_cast<char*>(arr);
		char *e = p + N;
		for(;p != e;++p)
		{
			*p = 0;
		}
	}
	struct struct1
	{
		int t;
		typedef int type;
		struct1()=default;
		struct1(const int)=delete;
		struct1(const struct1&)=default;
		~struct1()=default;
		struct1(std::nullptr_t):t(0){}
		int get() const
		{
			return t;
		}
		void set(const int i)
		{
			this->t = i;
		}
	};
	template <typename T>
	class wrapT
	{
		private:
			T *t;
		public:
			typedef T type;
			typedef T* ptr;
			typedef T* wrapptr;
			typedef wrapT<T> this_type;
			friend T; // t private
			explicit wrapT()
			{
				t = new T();
			}
			explicit wrapT(const wrapT<T>& t)
			{
				this->t = new T(t.get());
			}
			explicit wrapT(wrapT<T>&& t)
			{
				this->t = t;
				t.t = nullptr;
			}
			explicit wrapT(T&& t)
			{
				this->t = new T(t);
			}
			explicit wrapT(T* t)
			{
				this->t = t;
			}
			~wrapT()
			{
				delete t;
			}
			T& operator*() const
			{
				return *t;
			}
			T* operator->() const
			{
				return t;
			}
			T& get() const
			{
				return *t;
			}
			ptr getptr() const
			{
				return t;
			}
			void set(T&& t)
			{
				*(this->t) = t;
			}
			void set(const T& t)
			{
				*(this->t) = t;
			}
			wrapT<T>& operator=(T&& t)
			{
				*(this->t) = std::forward<T>(t);
				return *this;
			}
			wrapT<T>& operator=(wrapT<T>&& t)
			{
				if(this != &t)
				{
					delete this->t;
					this->t = t;
					t.t = nullptr;
				}
				// else throw
				return *this;
			}
			wrapT<T>& operator=(const wrapT<T>& t)
			{
				set(t);
				return *this;
			}
			operator T&() const
			{
				return *(this->t);
			}
			operator T*() const
			{
				return this->t;
			}
	};
	template <typename T>
	class wrapT2
	{
		private:
			T* t;
		public:
			typedef typename T::type type;
			typedef T WT;
			typedef typename T::ptr WP;
			friend T;
			friend typename T::type;
			friend WT;
			wrapT2()=delete;
			explicit wrapT2(const T& t)
			{
				this->t = new T(t);
			}
			explicit wrapT2(const T* t)
			{
				this->t = t;
			}
			~wrapT2()
			{
				delete t;
			}
			template <typename N> void setW(N&& n)
			{
				this->t->set(std::forward<N>(n));
			}
			template <typename N> typename T::type& set2(N&&);
			// template <typename Iter> typename wrapT2<T>& itertest(Iter begin, Iter end);
			typename T::type& set2(struct1&&) = delete;
			typename T::type& set2(void)
			{
				return this->t->get();
			};
			typename T::type& getW() const
			{
				return this->t->get();
			}
			template <typename K, typename U>
			friend bool wrapT2Cmp(const wrapT2<K>&, const wrapT<U>&);
	};
	template <typename T>
	template <typename N>
	typename T::type& wrapT2<T>::set2(N&& n)
	{
		this->t->set(std::forward<N>(n));
		return t->get();
	}
	int wrapintpp(wrapT<int>& t)
	{
		int i = t.get();
		t.set(i + 1);
		return i;
	}

	template <typename T>
	auto sum1(T& begin, T& end) -> typename std::remove_reference<decltype(*begin)>::type // decltype(auto) sum1() // C++ 14
	{
		T iter = begin;
		decltype(*iter) ret = 0;
		for(;iter != end;++iter)
		{
			ret += *iter;
		}
		return iter;
	}
	template <typename T>
	void voidF(T& t)
	{
		(void)t;
		// T = const int // const int i = 5;voidF(i);
		// T = int // int i = 5;voidF(i);
	}
	template <typename T>
	void voidFconst(const T& t)
	{
		(void)t;
		// T = int // const int a;int b; // voidF(a) || voidF(b) || voidF(5);
	}
	/*
	template <typename T>
	void void
	*/
	template <typename T>
	const char * getLR(T& t)
	{
		(void)t;
		return (const char *)"L";
	}
	template <typename T>
	const char * getLR(T&& t)
	{
		(void)t;
		return (const char *)"R";
	}
	template <typename T>
	const char * getLRF(T&& t)
	{
		return getLR(std::forward<T>(t)); // && & = &    T = &// && && = &&    T = &&
	}
	template <typename T> std::string to_string_1(const T *p)
	{
		return std::to_string(*p);
	}	
	template <typename T> std::string to_string_1(const T& t)
	{
		return std::to_string(t);
	}
	std::string to_string_1(char *p)
	{
		return std::string(p);
	}
	std::string to_string_1(const char *p)
	{
		return std::string(p);
	}
	template <>
	class wrapT2<struct1>
	{
		wrapT2() = delete;
		wrapT2(struct1&&) = delete;
		wrapT2(struct1&) = delete;
		~wrapT2() = delete;
	};
	/*
	template <typename T>
	class wrapT2<T&&>
	{
	};
	// wrapT2<T&&>::t // T
	template <typename T>
	class wrapT2<T*>
	{
		public:
			typedef T originT;
		T* get(void) const
		{
			// code
		}
	}
	*/
	template <> void wrapT<struct1>::set(struct1&&) = delete;
	

	template <typename T, typename... Targs>
	T add(const T& t, const Targs& ... args)
	{
		// return t + (args + ...)
		return t + add(args ...);
	}
	template <typename T, typename...Targs>
	T avg(const Targs&... args)
	{
		return (T)add(args ...) / static_cast<T>(sizeof...(Targs));
		// return add(((T)args / static_cast<T>(sizeof...(Targs))) ...);
		// return add(add((T)args / static_cast<T>(sizeof...(Targs)), 0) ...);
		// T avg(const Targs&&... t) // add(std::forward<T>(t) ...)
	}
	/*
	template <typename T>
	T& operator=(const wrapT<T>& t)
	{
		return *(t.t);
	}
	*/
	template <typename K, typename U>
	bool wrapT2Cmp(const wrapT2<K>& t, const wrapT<U>& k)
	{
		// t.t private
		return t.t->get() == k.get();
	}

	template <template<class> class W>
	int getWrapInt(W<int>& w)
	{
		return w.get();
	}

	template <typename T>
	using wrapT2T = wrapT2<wrapT<T>>;
	class logC
	{
		private:
			static std::vector<std::string> log;
			std::string name;
		public:
			static std::vector<std::string>& get()
			{
				return log;
			}
			static void clear()
			{
				log.clear();
			}
			static std::string logString()
			{
				std::vector<std::string>::const_iterator iter;
				std::string s = "| ";
				for(iter = log.begin();iter != log.end();++iter)
					s += *iter + " | ";
				return s;
			}
			explicit logC()
			{
				log.push_back(std::string("default"));
			}
			explicit logC(std::string& s)
			{
				this->name = s;
				log.push_back("string&: " + this->name);
			}
			explicit logC(std::string&& s)
			{
				this->name = s;
				log.push_back("string&&: " + this->name);
			}
			explicit logC(logC& l)
			{
				this->name = " &_" + l.getName();
				log.push_back("logC&: " + this->name);
			}
			explicit logC(logC&& l)
			{
				this->name = l.name;
				this->name = " &&_" + l.getName();
				l.name = "expired: " + l.name;
				log.push_back("logC&&: " + this->name);
			}
			~logC()
			{
				log.push_back("~: " + this->name);
			}
			std::string getName() const
			{
				return name;
			}
			logC& operator=(logC&& c)
			{
				std::string cs = (*getLR(std::forward<logC>(c)) == 'L')?"&":"&&";
				log.push_back("logC" + cs + ": " + c.getName());
				this->name = c.name + " (ori: " + this->name + " " + cs + "=)";
				if(cs == "&&")
					c.name = "expired: " + c.name;
				return *this;
			}
			logC& operator=(std::string&& c)
			{
				std::string s = c;
				std::string cs = (*getLR(std::forward<std::string>(c)) == 'L')?"&":"&&";
				log.push_back("string" + cs + ": " + s);
				this->name = cs + " (ori: " + this->name + " " + cs + "=)";
				if(cs == "&&")
					c = "expired";
				return *this;
			}
	};
	std::vector<std::string> logC::log = {};



	template <size_t N>
	struct wrapN
	{
		static constexpr const size_t value = N;
	};
	// template <size_t N> using wrapN = std::integral_constant<size_t, N>;
	template <size_t N>
	struct FAB
	{
		// const static constexpr size_t value = FAB<N - 1>::value + FAB<N - 2>::value;
		enum {value = FAB<N - 1>::value + FAB<N - 2>::value};
	};
	template <>
	struct FAB<0>
	{
		// const static size_t value = 1;
		enum {value = 1};
	};
	template <>
	struct FAB<1> : public FAB<0> {};
	template <>
	struct FAB<2> : public FAB<0> {};

	template <size_t N>
	constexpr size_t STRSIZE(const char(&)[N])
	{
		return N;
	};

	template <size_t N, size_t... NN>
	struct SUM
	{
		const static constexpr size_t value = N + SUM<NN ...>::value; 
	};
	template <size_t N>
	struct SUM<N>
	{
		const static constexpr size_t value = N;
	};

	template <size_t M, size_t N = 0, size_t... NN>
	struct MAX
	{
		const static constexpr int value = MAX<MAX<M, N>::value, NN ...>::value;
	};
	// template <size_t M, size_t N = 0>
	template <size_t M, size_t N>
	struct MAX<M, N>
	{
		const static constexpr int value = (M > N)?M:N;
	};

	template <typename T, typename ... TT>
	struct TARGN_BACK
	{
		typedef typename TARGN_BACK<TT ...>::type type;
	};
	template <typename T>
	struct TARGN_BACK<T>
	{
		typedef T type;
	};

	template <typename T>
	T&& ARGN_BACK(T&& t)
	{
		return std::forward<T>(t);
	}
	template <typename T, typename ... TT>
	typename TARGN_BACK<TT ...>::type&& ARGN_BACK(T&&, TT&& ... tt)
	{
		return ARGN_BACK(std::forward<TT>(tt) ...);
	}


	template <size_t INDEX, typename T, typename... TT>
	struct TARGN
	{
		static_assert(INDEX < sizeof...(TT) + 1, "TARGN OUT_OF_RANGE");
		typedef typename TARGN<INDEX - 1, TT ...>::type type;
	};
	template <typename T, typename... TT>
	struct TARGN<0, T, TT ...>
	{
		typedef T type;
	};

	template <size_t INDEX, size_t N, size_t ...NN>
	struct SARGN : public SARGN<INDEX - 1, NN ...> 
	{
		static_assert(INDEX < sizeof...(NN) + 1, "SARGN OUT_OF_RANGE");
	};
	template <size_t N, size_t ...NN>
	struct SARGN<0, N, NN ...>
	{
		static constexpr size_t value = N;
	};

	template <typename T, typename... TT>
	constexpr T&& ARGN_HELPER(wrapN<0>, T&& t, TT&&...)
	{
		return std::forward<T>(t);
	}

	template <size_t N, typename T, typename... TT>
	constexpr typename TARGN<N, T, TT ...>::type&& ARGN_HELPER(wrapN<N>, T&&, TT&&... tt)
	{
		static_assert(sizeof...(TT) != 0, "ARGN OUT_OF_RANGE");
		return ARGN_HELPER(wrapN<N - 1>(), std::forward<TT>(tt) ...);
	}
	template <size_t INDEX, typename T, typename... TT>
	constexpr typename TARGN<INDEX, T, TT ...>::type ARGN(T&& t, TT&&... tt)
	{
		return ARGN_HELPER(wrapN<INDEX>(), std::forward<T>(t), std::forward<TT>(tt) ...);
	}

	template <typename T>
	auto STR_CAST(T& t) -> const char(&)[sizeof(t)]
	{
		return reinterpret_cast<const char(&)[sizeof(t)]>(t);
	}

	struct STR_BASE
	{
		operator const char*() const
		{
			return reinterpret_cast<const char*>(this);
		}
		char operator[](const size_t n) const
		{
			return *(reinterpret_cast<const char*>(this) + n);
		}
	};

	template <size_t N>
	struct STR : STR<N - 1>
	{
		constexpr STR(const char *s):STR<N - 1>(s), c(s[N - 1]){};
		protected:
			char c;
	};
	template <>
	struct STR<1> : public STR_BASE
	{
		constexpr STR(const char* s): c(*s){}
		protected:
			char c;
	};
	template <> struct STR<0> : public STR_BASE {}; // sizeof(STR<0>)


	template <size_t N, size_t... SS>
	struct STRSTR : STRSTR<N - 1, SS ...>
	{
		protected:
			STR<SARGN<N - 1, SS ...>::value> s;
		public:
			template <typename... TT>
			constexpr STRSTR(TT&&... tt):STRSTR<N - 1, SS ...>(std::forward<TT>(tt) ...), s(ARGN<N - 1>(std::forward<TT>(tt) ...)) {}
	};
	template <size_t... SS>
	struct STRSTR<0, SS ...>
	{
		template <typename... TT>
		constexpr STRSTR(TT&&... ) {}
		operator const char*() const
		{
			return reinterpret_cast<const char*>(this);
		}
	};

	template <size_t N>
	constexpr STR<N> CSTR(const char (&s)[N])
	{
		return STR<N>(s);
	}


	template <typename... TT>
	constexpr STRSTR<sizeof...(TT) + 1, (sizeof(TT) - 1) ..., 1> CSTRSTR_BASIC(TT&&... tt)
	{
		return STRSTR<sizeof...(TT) + 1, (sizeof(TT) - 1) ..., 1>(std::forward<TT>(tt) ..., "");
	}

	template <size_t N>
	struct CSTRSTR_HELPER
	{
		template <typename T, typename... TT>
		static constexpr auto CH(T&& t, TT&&... tt) -> decltype(CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(std::forward<TT>(tt) ..., std::forward<T>(t)))
		{
			return CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(std::forward<TT>(tt) ..., std::forward<T>(t));
		}
	};
	template <>
	struct CSTRSTR_HELPER<1>
	{
		template <typename T, typename... TT>
		static constexpr auto CH(T&&, TT&&... tt) -> decltype(CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(std::forward<TT>(tt) ...))
		{
			return CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(std::forward<TT>(tt) ...);
		}
	};
	template <>
	struct CSTRSTR_HELPER<0>
	{
		static const char END[0];
		template <typename T, typename... TT>
		static constexpr auto CH(T&&, TT&&... tt) -> decltype(CSTRSTR_BASIC(std::forward<TT>(tt) ...))
		{
			return CSTRSTR_BASIC(std::forward<TT>(tt) ...);
		}
	};

	template <typename... TT>
	constexpr auto CSTRSTR(TT&&... tt) -> decltype(CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(tt ..., CSTRSTR_HELPER<0>::END))
	{
		return CSTRSTR_HELPER<sizeof(typename TARGN<0, TT ...>::type)>::CH(tt ..., CSTRSTR_HELPER<0>::END);
	}

	template <bool B, size_t N>
	constexpr const char(&CONDSTR(const char (&s)[N]))[(B)?N:1]
	{
		return reinterpret_cast<const char (&)[(B)?N:1]>(*(s + ((B)?0:N - 1)));
	}


	// enable_if<false, int>::type = 0 // failed // SFINAE // Substitution failure is not an error
	template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
	ssize_t to_ssize_t(T t)
	{
		return static_cast<ssize_t>(t);
	}
	template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
	ssize_t to_ssize_t(T t)
	{
		return static_cast<ssize_t>(t);
	}

	template <typename T, class ENABLE = void>
	struct TEST1
	{
		const static int value = 0;
	};
	template <typename T>
	struct TEST1<T, typename std::enable_if<std::is_integral<T>::value>::type>
	{
		const static int value = 1;
	};

	template <typename T>
	class wrapC
	{
		public:
			static_assert(std::is_trivial<T>::value && std::is_standard_layout<T>::value, "pod"); // C
			typedef T type;
			T t;
			wrapC()=default;
			wrapC(const wrapC&)=default;
			wrapC(wrapC&&)=default;
			wrapC<T>& operator=(const wrapC<T>&)=default;
			wrapC<T>& operator=(wrapC<T>&&)=default;
			~wrapC()=default;
			explicit wrapC(const T& tt)
			{
				set(tt);
			}
			template <typename N, typename... NN, typename std::enable_if<(std::is_same<typename std::decay<N>::type, T>::value == false && std::is_same<typename std::decay<N>::type, wrapC<T>>::value == false) || sizeof...(NN) != 0, int>::type = 0>
			explicit wrapC(N&& n, NN&&... nn)
			{
				new (&t) T(std::forward<N>(n), std::forward<NN>(nn) ...);
			}
			operator T&()
			{
				return this->t;
			}
			operator const T&() const
			{
				return this->t;
			}
			typename std::conditional<std::is_scalar<T>::value, T, T&>::type get()
			{
				return this->t;
			}
			wrapC& operator=(const T& t)
			{
				set(t);
			}
			template <typename N = T>
			typename std::enable_if<std::is_scalar<N>::value, void>::type set(const N& t)
			{
				this->t = t;
			}
			template <typename N = T>
			typename std::enable_if<std::is_scalar<N>::value == false, void>::type set(const N& t)
			{
				static_assert(std::is_same<typename std::decay<N>::type, T>::value, "T");
				std::memcpy(&this->t, &t, sizeof(T));
				// std::memmove(&this->t, &t, sizeof(T)); // safe
			}
			typename std::conditional<std::is_class<T>::value, T*, wrapC<T>*>::type operator->()
			{
				return *this->t;
			}
	};
	template <typename T>
	class wrapINT : public wrapC<T>
	{
		public:
			static_assert(std::is_integral<T>::value, "T");
			explicit wrapINT():wrapC<T>(0){}
			template <typename N>
			explicit wrapINT(N&& n): wrapC<T>(std::forward<N>(n)){}
			template <typename N>
			typename std::enable_if<std::is_convertible<N, T>::value, wrapINT<T>&>::type operator=(N&& n)
			{
				wrapC<T>::set(static_cast<T>(std::forward<N>(n)));
				return *this;
			}
			template <typename N>
			typename std::enable_if<std::is_same<typename std::decay<N>::type, T (*)(void)>::value, wrapINT<T>&>::type operator=(N&& n)
			{
				wrapC<T>::set(std::forward<N>(n)());
				return *this;
			}
			wrapINT<T>& operator=(T* n)
			{
				wrapC<T>::set(*n);
				return *this;
			}
			template <typename N>
			typename std::enable_if<std::is_pointer<N>::value && std::is_convertible<typename std::remove_pointer<N>::type, T>::value, wrapINT<T>&>::type operator=(N&& n)
			{
				wrapC<T>::set(static_cast<T>(*std::forward<N>(n)));
				return *this;
			}
			static T getV(const wrapINT<T>& w)
			{
				return w.get();
			}
	};
	template <typename T, class WT = typename std::conditional<std::is_integral<T>::value == false, typename std::conditional<std::is_trivial<T>::value, wrapC<T>, wrapT<T>>::type, wrapINT<T>>::type>
	class wrapT3 : public WT
	{
		static_assert(std::is_member_function_pointer<decltype(&T::get)>::value, "get");
		static_assert(std::is_member_object_pointer<decltype(&T::t)>::value, "t");
		static_assert(std::is_void<decltype(std::declval<T>().set(std::declval<T>().get()))>::value || true, "set");
		static_assert(std::is_function<decltype(T::getV)>::value, "getV");
		public:
			friend T;
			template <typename N, typename std::enable_if<std::is_base_of<typename std::decay<N>::type, WT>::value, int>::type = 0>
			explicit wrapT3(N&& n): WT(std::forward<N>(n)) {}
			template <typename N, typename... NN, typename std::enable_if<std::is_base_of<typename std::decay<N>::type, WT>::value == false, int>::type = 0>
			explicit wrapT3(N&& n, NN&&... nn): WT(new T(std::forward<N>(n), std::forward<NN>(nn) ...)) {}
			decltype(std::declval<typename WT::type>().get()) getV() const
			{
				return WT::get().get();
			}
			template <typename N, typename std::enable_if<std::is_void<decltype(std::declval<T>().set(std::declval<N>))>::value || true, int>::type = 0>
			void setV(N&& n)
			{
				WT::get().set(std::forward<N>(n));
			}
	};
	template <typename T>
	class wrapT3<T, wrapINT<T>> : public wrapINT<T>
	{
		private:
			using WT = wrapINT<T>;
		public:
			typedef T type;
			template <typename... TT, typename std::enable_if<std::is_constructible<WT, TT ...>::value, int>::type = 0>
			explicit wrapT3(TT&&... tt): WT(std::forward<T>(tt) ...){}
			T getV()
			{
				return WT::get();
			}
			void setV(const T& t)
			{
				WT::set(t);
			}
	};
	template <typename T>
	class wrapT3<T, wrapC<T>> : public wrapC<T>
	{
		public:
			typedef T type;
			decltype(std::declval<T>().get()) getV()
			{
				return wrapC<T>::get().get();
			}
			template <typename N>
			typename std::enable_if<std::is_void<decltype(std::declval<T>().set(std::declval<N>()))>::value || true, void>::type setV(N&& n)
			// void setV(const typename T::type& t)
			{
				wrapC<T>::get().set(std::forward<N>(n));
			}
	};

#if 0 || 0
	template <size_t M, size_t N, typename... TT> constexpr typename std::enable_if<(N > 1), char>::type STR2_HELPER(char (&d)[M], const char (&s)[N], TT&&... tt);
	template <size_t M, size_t N, typename... TT> constexpr typename std::enable_if<(N < 2), char>::type STR2_HELPER(char (&s)[M], const char (&)[N], TT&&... tt);
	constexpr char STR2_HELPER(char*)
	{
		return '\0';
	}
	template <size_t M, size_t N, typename... TT>
	constexpr typename std::enable_if<(N < 2), char>::type STR2_HELPER(char (&s)[M], const char (&)[N], TT&&... tt)
	{
		return STR2_HELPER(reinterpret_cast<char (&)[M]>(s[0]), std::forward<TT>(tt) ...);
	}
	template <size_t M, size_t N, typename... TT>
	constexpr typename std::enable_if<(N > 1), char>::type STR2_HELPER(char (&d)[M], const char (&s)[N], TT&&... tt)
	{
		d[0] = s[0]; // C++ 14
		return STR2_HELPER(reinterpret_cast<char (&)[M - 1]>(d[1]), reinterpret_cast<const char (&)[N - 1]>(s[1]), std::forward<TT>(tt) ...);
	}
	template <size_t N>
	struct STR2 : public STR_BASE
	{
		char value[N];
		char e;
		template <typename... TT>
		constexpr STR2(TT&&... tt): e(STR2_HELPER(reinterpret_cast<char (&)[N + 1]>(value), std::forward<TT>(tt) ...)){}
	};
	template <typename... TT, size_t N = SUM<sizeof(TT) ...>::value - sizeof...(TT)>
	constexpr STR2<N> CSTR2(TT&&... tt)
	{
		return STR2<N>(std::forward<TT>(tt) ...);
	}
#endif


	template <typename T, typename K>
	typename std::common_type<T, K>::type add(T t, K k) 
	{
		return t + k;
	}


	template <typename T>
	const char* showT()
	{
#ifdef __GNUC__
		return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
#else
		return typeid(T).name();
#endif
	}

	template <size_t... NN>
	struct STR3 : public STR_BASE
	{
		static_assert(sizeof...(NN) == 0, "");
		template <typename... TT>
		constexpr STR3(TT&&...){}
	};
	template <size_t... NN>
	struct STR3<0, NN ...> : STR3<NN ...> {
		template <typename T, typename... TT>
		constexpr STR3(T&&, TT&&... tt): STR3<NN ...>(std::forward<TT>(tt) ...){}
	};
	template <size_t N, size_t... NN>
	struct STR3<N, NN ...> : STR3<N - 1, NN ...>
	{
		template <typename T, typename... TT>
		constexpr STR3(T&& t, TT&&... tt): STR3<N - 1, NN ...>(std::forward<T>(t), std::forward<TT>(tt) ...), c(t[N - 1]){}
		protected:
			char c;
	};
	template <template<size_t...> class STRSTR, typename... TT>
	constexpr STRSTR<(sizeof(TT) - 1)..., 1> CSTRSTR_M(TT&&... tt)
	{
		return STRSTR<(sizeof(TT) - 1)..., 1>(std::forward<TT>(tt) ..., "");
	}
	// push_back && resize()
	
	template <size_t INDEX, typename T, typename... TT>
	constexpr typename std::enable_if<INDEX == 0, typename TARGN<INDEX, T, TT ...>::type>::type ARGN2(T&& t, TT&&...)
	{
		return std::forward<T>(t);
	}
	template <size_t INDEX, typename T, typename... TT>
	constexpr typename std::enable_if<INDEX != 0, typename TARGN<INDEX != 0, T, TT ...>::type>::type ARGN2(T&&, TT&&... tt)
	{
		static_assert(INDEX < sizeof...(TT) + 1, "ARGN OUT_OF_RANGE");
		return ARGN2<INDEX - 1>(std::forward<TT>(tt) ...);
	}
};

void testLogC(void)
{
	using template1::wrapT;
	using template1::logC;
	wrapT<logC> w1(new logC {"w1"});
	wrapT<logC> w2(w1);
	wrapT<logC> w3(std::move(w2));
	wrapT<logC> w4;
	w4 = logC("ww4");
}



void templateTest() // noexcept // no throw err // noexcept(false);
{
using namespace std;
using namespace template1;
	C2(add(2, 3) == add2(3, 2));
	int (*addF)(const int, const int) = &add;
	(void)addF;
	char chararr1[10];
	char0(chararr1); // memset
	int i = mulC<int, 5>(1);
	C2(i == 5);
	C2(typeid(wrapT<int>::type) == typeid(int)); // typeid(int).name();

	std::vector<int> vec {1, 2, 3, 4, 5};
	wrapT<int> w1(5);
	wrapT<std::vector<int>> w2(std::move(vec));
	C2(*w1 == w2->at(4));
	i = w1; // i = (int)w1;
	C2(*(int *)w1 == (int)w1);

	wrapT<int> w3(std::move(w1));
	wrapT2<wrapT<int>> w4(w3);
	C2(*w3 = w4.getW());
	C2(wrapT2Cmp(w4, w3));
	C2(getWrapInt(w3) == 5);

	// wrapT2<template1::struct1> www(static_cast<template1::struct1 *>(nullptr)); // delete

	wrapT<logC>* w5 = new wrapT<logC>(new logC("c1"));
	delete w5;
	testLogC();
	C2(logC::logString());

	wrapT2T<int>* w6 = &w4; // wrapT2T<T, wrapT2<wrapT<T>>>
	// wrapT2T<int, wrapT<T>>
	(void)w6;
	

	

	// C2(typeid(wrapT<int>).name());
	const int *p = &i;
	// T && && = T &&
	// T & && = T &
	// T && & = T &
	// T & &  = T &
	int& ir = i;
	int&& irr = std::move(i); // static_cast<std::remover_reference<decltype(i)>::type>(i);
	C2(getLR(i) == getLRF(i)); // & 
	C2(getLR(ir) == getLRF(ir)); // && & // T = &
	C2(getLR(irr) == getLRF(irr));//  && && // T = &&
	// C2(getLR(std::move(i)) == getLRF(std::move(i)));
	// const int& j = const_cast<int&>(i);
	// std::reference<T>(t) // static_cast<T&&>(t);
	char s5[2] = {'5', '\0'};
	C2(to_string_1(5) == to_string_1(p) && to_string_1(s5) == to_string_1((const char *)"5")); // static_cast<const char *>("5")
	// wrapT2<template1::struct1> _disabled;
	C2(add(1, 2, 3) == 6);
	C2(avg<float>(1, 2, 1, 2) > 1.3);

	C2((FAB<11>::value == 89));
	C2((SUM<1, 2, 3, 4, 5>::value == 15));
	C2((MAX<1, 2, 3, 7, 4>::value == 7));
	C2(ARGN_BACK(1, 2, 3, 4, 5) == 5);
	C2((std::is_same<TARGN_BACK<int, char, long long, unsigned int>::type, unsigned int>::value == true));

	C2((SARGN<2, 0, 1, 2, 3>::value == 2));
	C2((SARGN<2, 0, 1, 2>::value == 2));
	C2((std::is_same<TARGN<2, int, char, unsigned int, float>::type, unsigned int>::value == true));
	C2(ARGN<2>(0, 1, 2, 3) == 2);

	auto strcmp1 = [](const char* a, const char* b)
	{
		for(;*a != '\0' && *a == *b;++a, ++b);
		return *a == *b;
	};
	const auto c1 = STR<6>("[str]");
	const char* cc = c1;
	C2(sizeof(c1) == 6);
	C2(cc);

	const auto c2 = CSTR("mosfet");
	C2(sizeof(c2) == 7); // strlen((const char*)c2) + 1
	C2((const char*)c2);

	const auto c3 = STRSTR<4, 1, 3, 1, 1>("[", "str", "]", "");
	C2(sizeof(c3) == 6 && strcmp1(c1, c3));
	
	const auto c4 = CSTRSTR_BASIC("[", "str", "]");
	C2(sizeof(c4) == sizeof(STR_CAST(c4)) && sizeof(c4) != sizeof(const char*) && strcmp1(c4, STR_CAST(c1)));
	// C2(strcmp1(c4, STR_CAST(c4)));

	//  glvalue = lvalue + xvalue
	// rvalue = prvalue + xvalue

	C2((sizeof(CONDSTR<true>("STR"))));
	C2((sizeof(CONDSTR<false>("STR"))));
	C2(CONDSTR<true>("str"));
	C2(CONDSTR<false>("str"));

	const auto c10 = CSTRSTR("", "", "abc", "abc", "", "endl");
	C2(sizeof(c10));
	C2(c10[0] == 'a');
	C2(STR_CAST(c10));



	C2(to_ssize_t<int>(5) == to_ssize_t<float>(5.5));
	static_assert(1 == 1, "1 != 1");
	static_assert(std::integral_constant<int, 5>::value == 5, "true"); // value = 5 value_type = int type = interal_constant
	static_assert(std::integral_constant<bool, true>::value == true, "true");
	// is_xxx : public std::integral_constant<bool, is_convertible<T, xxx>::value> {}
	static_assert(std::true_type::value == true && std::false_type::value == false, "true_type false_type");
	static_assert(std::is_same<int, int>::value, "is_same");
	static_assert(std::is_same<decltype(nullptr), std::nullptr_t>::value, "nullptr");
	static_assert(std::is_same<std::conditional<true, std::true_type, std::false_type>::type, std::true_type>::value, "conditional");

	static_assert(std::is_void<void>::value && std::is_null_pointer<decltype(nullptr)>::value, "void null_pointer"); // void std::nullptr_t
	static_assert(std::is_integral<int>::value, "integral"); // char short int long char8_t char16_t char32_t
	static_assert(std::is_floating_point<float>::value, "floating_point");
	static_assert(std::is_array<int[5]>::value, "array");
	static_assert(std::is_function<int(int)>::value, "function");
	static_assert(std::is_function<std::remove_pointer<int (*)(int)>::type>::value, "func");
	static_assert(std::is_pointer<int*>::value, "pointer");
	static_assert(std::is_lvalue_reference<int&>::value && std::is_rvalue_reference<int&&>::value, "& &&");

	static_assert(std::is_same<std::enable_if<true, int>::type, int>::value, "enable_if");
	static_assert(std::is_array<int[5]>::value && std::extent<int[5]>::value == 5 && std::extent<int[5], 0>::value == 5, "assert");
	static_assert(std::is_arithmetic<int>::value, "arthmetic"); // int char float
	static_assert(std::is_fundamental<int>::value, "fundmental"); // arithmetic void nullptr
	static_assert(std::is_scalar<int>::value && std::is_scalar<void*>::value, "scalar"); // arithmetic enum pointer member_pointer null_pointer
	static_assert(std::is_object<wrapINT<int>>::value, "object"); // scalar array union class
	static_assert(std::is_compound<struct1>::value, "common_type"); // !fundamental
	// is_reference // lreference rreference
	
	static_assert(std::is_same<decltype(std::declval<int>()), int&&>::value, "declval");
	static_assert(std::is_same<decltype(std::declval<wrapT2<wrapT<int>>>().getW()), int&>::value, ""); // wrapT2()=delete; // decltype(wrapT2<wrapT<int>>().getW()) failed

	struct1 w7;
	int (struct1::*struct1_get)() const = &struct1::get; // std::function<int(const struct1&)> struct1_get
	int struct1::*struct1_t = &struct1::t; // std::function<int(struct1&)> struct1;
	C2((w7 .* struct1_get)() == w7.get()); // w7ptr->*struct1_get
	C2(((&w7) ->* struct1_t) == w7.t);
	static_assert(std::is_member_function_pointer<decltype(&struct1::get)>::value, "member_function_pointer"); // struct1::*
	static_assert(std::is_member_function_pointer<int& (struct1::*)()>::value, "");
	static_assert(std::is_member_pointer<decltype(&struct1::t)>::value, "member_pointer");
	static_assert(std::is_member_object_pointer<decltype(&struct1::t)>::value, "member_object_pointer"); // member_pointer && !member_function_pointer

	static_assert(std::is_const<const int>::value, "const");
	static_assert(std::is_volatile<const volatile int>::value, "volatile");

	static_assert(std::is_default_constructible<wrapINT<int>>::value && std::is_constructible<wrapINT<int>, int>::value, "constructible"); // wrapINT<int>() && wrapINT<int>(std::declval<int>())
	// is_constructible is_trivially_constructible is_nothrow_constructible
	// is_default_constructible is_trivially_default_constructible is_nothrow_defalt_constructible
	static_assert(std::is_copy_constructible<wrapINT<int>>::value, "copy_constructible"); // wrapINT<int> dst(src);
	static_assert(std::is_copy_assignable<wrapINT<int>>::value, "copy_assignable"); // dst = src;
	static_assert(std::is_move_constructible<wrapINT<int>>::value, "move_constructible"); // wrapINT<int> dst(std::move(src));
	static_assert(std::is_move_assignable<wrapINT<int>>::value, "move_assignable"); // dst = std::move(src);
	static_assert(std::is_assignable<wrapINT<int>, int>::value, "assignable"); // wrap_int_1 = 5;
	// is_assignable is_trivially_assignable is_nothrow_assignable
	static_assert(std::is_destructible<wrapINT<int>>::value, "destrutible"); // is_destructible is_trivially_destructible is_nothrow_destructible
	static_assert(std::has_virtual_destructor<std::false_type>::value == false, "has_virtual_destructible");



	// is_pod<T>::value // memcpy(&dst, &src, sizeof(src)) // extern "C" struct TYPE{int a, int b;}src, dst = {1, 2}; // is_trivial && is_standard_layout
	// struct pod_2{int a;int b; pod_2()=default;pod_2(const pod_2&)=default;pod_2(pod_2&&)=default;pod_2& operator=(const pod_2&)=default;pod_2& operator=(pod_2&&)=default}; // trivial

	static_assert(std::is_trivial<wrapT<int>>::value == false, "trivial"); // trivially_copyable && trivially_defalut_constructible
	// false // class A: virtual public BASE{virtual get() const;};
	// true // struct A{int a;int b; pod_2()=default;pod_2(const pod_2&)=default;pod_2(pod_2&&)=default;pod_2& operator=(const pod_2&)=default;pod_2& operator=(pod_2&&)=default}; // struct A{int a;int b;}; 
	
	static_assert(std::is_standard_layout<int>::value, "standard_layout");
	// false // class A: virtual public BASE{virtual int get() const{}};
	// false // class A: {public: int a; int b;private: int c;}; // true // public|private|protected: int a; int b; int c;
	// false // class B{static int a;};class B{static int b;};class A: B, C{}; // true // class A : B{}:
	// false // class A: BASE{A a;int b;}; // true // class A: BASE {int b;A a;};

	static_assert(std::is_trivially_copyable<int>::value, "trivially_copyable"); // memcpy(&dst, &src, sizeof(src)) 
	static_assert(std::is_trivially_copyable<wrapT<int>>::value == false, ""); // decltype(wrapT<int>().t) : int*
	// is_trivially_copyable :
	//  is_trivially_copy_constructible dst = new T(src) memcpy(new T, &src, sizeof(T))
	//  is_trivially_copy_assignable dst = src memcpy(&dst, &src, sizof(dst))
	//  is_trivially_move_constructible dst = new T(std::move(src))// is_trivially_move_assignable dst = std::move(src)
	//  is_trivially_destructible // do nothing

	static_assert(std::is_trivially_default_constructible<int>::value && std::is_trivially_destructible<int>::value, "trivially_default_constructible"); // constructor()=default; // new T() // T() do nothing // new T
	static_assert(std::is_trivially_default_constructible<struct1>::value && std::is_trivially_default_constructible<wrapT<int>>::value == false, ""); // struct1()=default; // wrapT(){}

	static_assert(std::is_empty<std::false_type>::value, "empty"); // struct false_type{};
	static_assert(std::is_polymorphic<std::false_type>::value == false, "polymorphic"); // true // class A{virtual int get() const;};
	static_assert(std::is_abstract<std::false_type>::value == false, "abstract"); // true // class A{virtual int get() cosnt;}; // class B: public A;
	// is_final C++ 14
	static_assert(std::is_signed<int>::value && std::is_unsigned<std::size_t>::value, "signed unsigned");

	static_assert(std::extent<int[5][7]>::value == 5 && std::extent<int[5][7], 1>::value == 7, "assert");
	static_assert(std::rank<int[2][5][7]>::value == 3, "rank"); // rank<int>::value
	static_assert(std::alignment_of<unsigned char>::value >= sizeof(unsigned char), "alignment_of"); // struct A{int a; unsigned char c;}; // sizeof(int)*2

	static_assert(std::is_same<int, int>::value, "same");
	static_assert(std::is_base_of<std::integral_constant<bool, true>, std::true_type>::value, "is_base_of");
	static_assert(std::is_base_of<wrapC<int>, wrapINT<int>>::value, "is_base_of"); // class wrapINT<int> : public wrapC<int>
	static_assert(std::is_convertible<int, const int>::value, "convertible");

	static_assert(std::is_same<std::remove_cv<const volatile int>::type, int>::value, "remove_cv"); // remove_const + remove_volatile
	static_assert(std::is_same<std::add_cv<int>::type, const volatile int>::value, "add_cv"); // add_const + add_volatile

	static_assert(std::is_same<std::remove_reference<int&>::type, int>::value, "remove_reference");
	// add_lvalue_reference add_rvalue_reference
	static_assert(std::is_same<std::remove_pointer<int*>::type, int>::value, "remove_pointer");
	// add_pointer
	//
	static_assert(std::is_same<std::make_unsigned<int>::type, unsigned int>::value, "make_signed");
	// make_unsigned
	// remove_extent
	// remove_all_extents

	static_assert(std::is_same<decltype(std::declval<int>()), int&&>::value, "declval");
	static_assert(std::is_same<decltype(void(5), 5), int>::value, "void");
	static_assert(std::is_same<std::decay<int[5]>::type, int*>::value, "decay");
	static_assert(std::is_same<std::decay<int(&)[5]>::type, int*>::value, "decay");
	static_assert(std::is_same<std::decay<const int&&>::type, int>::value, "decay");
	static_assert(std::is_same<std::decay<int(int)>::type, int (*)(int)>::value, "decay");
	static_assert(std::is_same<std::common_type<int, float>::type, float>::value, "common_type");
	// std::aligned_storage<sizeof(int), alignof(int)>::type data[5];
	static_assert(sizeof(std::aligned_storage<sizeof(int) + sizeof(char), 4>::type) == 8, "aligned_storage");
	static_assert(sizeof(std::aligned_union<sizeof(long long), int, unsigned char>::type) == sizeof(long long), "aligned_union"); // union A{int a;unsigned char b;}; max(sizeof(long long), sizeof(A)) 
	// emplate< std::size_t Len, class... Types > struct aligned_union;
	wrapINT<int> w8(3.7);
	wrapINT<int> w9(w8);
	w8 = 5.3;
	w9 = &i;
	C2(w8 == w9);
	float f = 5.5;
	w8 = &f;
	w9 = static_cast<int(*)(void)>([](void)->int{return 5;});
	C2(w8 == w9);
	w8 = 0;
	w8 = w9;
	// cout << __cplusplus << endl;
	wrapINT<int> w11;
	wrapT3<wrapINT<int>> w10(5);
	// C2(w10.getV() == 5);
	wrapT3<int> w12(5);
	C2(w12.getV() == 5);
	w10.setV(7);
	w12.setV(7);
	C2(w10.getV() == w10.getV());

	wrapT3<struct1> w13;
	w13.get().t = 0;
	// C2(w13.get().t == w13.getV());
	C2(w13.getV() == 0);
	w13.setV(0);
	// static_assert(sizeof(decltype(w12.getV())), "");
	static_assert(std::is_trivial<decltype(w13)>::value, "");
	wrapC<struct1> w14(w13.get());
	w14.get().t = 0;
	static_assert(std::is_trivial<wrapC<struct1>>::value, "");
	static_assert(std::is_trivial<struct1>::value, "");
	static_assert(std::is_trivial<wrapC<struct1>>::value, "");
	wrapC<struct1> w15(nullptr);
	C2(w15.get().get() == 0);


	// static_assert(std::is_same<wrapT3<wrapINT<int>>::type, int>::value, "");
	// static_assert_1(1);
#if 0 != 0
	const auto c11 = STR2<5>("abcde");
	static_assert(sizeof(c11) == 5 + 1, "");
	C2(c11);
	const auto c12 = STR2<15>("abc", "def", "HIJ", "cc", "", "a", "dll"); 
	const auto c13 = CSTR2("abc", "def", "HIJ", "cc", "", "a", "dll"); 
	// is_base_of<T, BASE>::value
	static_assert(sizeof(c12) == 15 + 1 && sizeof(c13) == 15 + 1, "");
	C2(strcmp1(c12, c13));
#endif
	const auto c14 = STR3<1, 2, 3>("", "de", "abc");
	C2(STR_CAST(c14));
	const auto c15 = CSTRSTR_M<STR3>("abc\n", "def", "", "end");
	C2((const char*)c15 + 1);

	C2((showT<decltype(c15)>()));

}


// template class template1::wrapT<int>;

// other_file.cpp
// extern template class template1::wrapT<int>;
// template int template1::add(const int, const int);

