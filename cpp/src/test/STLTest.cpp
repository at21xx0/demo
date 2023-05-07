#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include <array>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <random>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

#include "test.h"

struct TMP_TYPE;
struct TMP_TYPE
{
	int first;
	int second;
	TMP_TYPE (const int a, const int b):first(a), second(b){}
	bool operator<(const TMP_TYPE& b) const
	{
		return this->first < b.first; // priority_queue
	}
	bool operator==(const TMP_TYPE& b) const
	{
		return this->first == b.first; 
	}
};
struct TMP_TYPE_HASH
{
	size_t operator()(const TMP_TYPE& t) const
	{
		return std::hash<int>()(t.first);
	}
};

struct TMP_TYPE_EQUAL_TO
{
	size_t operator()(const TMP_TYPE& t, const TMP_TYPE& k) const
	{
		return t.first == k.second;
	}
};

void STLTest()
{
	using namespace std;
	// voctor set string map queue priority_queue stack pair algorithm
	size_t i;
	std::vector<int> v1; // blank;
	std::vector<int> v2 = {1, 2, 3, 4, 5};
	// std::vector<int> v3 {1, 2, 3, 4, 5};
	std::vector<int> v3(v2);
	std::vector<int> v4(std::move(v3));
	std::vector<int> v5(5);
	// std::vector<int> v5(5, 5); // {5, 5, 5, 5, 5};
	// std::vector<std::string> v7 {"a", "ab", "abc"};
	C2(v5[0] == 0);
	v1.reserve(10); // capacity
	C2(v1.capacity() == 10);
	for(i = 1;i != 6;++i)
	{
		v1.push_back(i);
	}
	// v1.emplace_back(1);
	C2(v1[0] == v1.at(0));
	// v1[5] = 0; // error
	// cout << v2.at(5) << endl; // throw error
	// vector<int>::const_iterator iter;
	std::function<std::string(const std::vector<int>&, const std::string& s)> join1 = [](const std::vector<int>& vec, const std::string& s) -> std::string
	{
		std::string ret = s;
		for(std::vector<int>::const_iterator iter = vec.cbegin();iter != vec.cend();++iter) // cbegin const_begin
			ret += std::to_string(*iter) + s;
		return ret;
	};
	std::function<std::string(const std::vector<int>& vec)> showVector = std::bind(join1, std::placeholders::_1, "|");
	C2(showVector(v1));
	for(vector<int>::reverse_iterator riter = v1.rbegin();riter != v1.rend();++riter)
	{
		v2.push_back(*riter);
	}
	C2(showVector(v2));


	vector<int>::iterator iter = v2.begin();
	v2.insert(iter + 6, 20); COUT(showVector(v2)); // C3
	C3((iter = v2.insert(v2.begin() + 5, 10)), showVector(v2));
	C2(iter == v2.begin() + 5);
	C3(v2.insert(v2.begin() + 5, 3, 7), showVector(v2));
	C3(v2.insert(v2.end(), v1.begin(), v1.end()), showVector(v2));

	C2(*std::find(v2.begin(), v2.end(), 7) == 7);
	C2(std::find(v2.begin(), v2.end(), 17) == v2.end());

	C3(v2.clear(), showVector(v2));
	C2(v2.empty());
	C3(v2.insert(v2.begin() + 0, {0, 1, 2, 3, 4, 5}), showVector(v2));

	C3(v2.pop_back(), showVector(v2));
	C2(v2.size() == 5);
	// C2(v2.max_size());
	C2(v2.capacity());
	C3(v2.erase(v2.begin() + 2), showVector(v2));
	// std::swap(*(v2.begin() + 1), *(v2.end() - 1)); v2.pop_back();
	// std::iter_swap(v2.begin() + 1, *(v2.end() - 1)); v2.pop_back();
	C3(v2.erase(v2.begin() + 1, v2.end()), showVector(v2));
	C3((v2 = v1), showVector(v2));
	i = 3;
	C3(v2.insert(v2.begin() + 2, i, 7), showVector(v2));
	C3((iter = std::remove(v2.begin(), v2.end(), 7)), showVector(v2));
	C3(v2.resize(std::distance(v2.begin(), iter)), showVector(v2));
	// v2.clear();
	C2(v2.capacity());
	vector<int>().swap(v2); // std::swap(new_vector, v2)
	C2(v2.capacity());
	C2(*v1.data() == v1.front());
	C2(*(v1.end() - 1) == v1.back());
	// vector<vector<int>> vv;
	// v1.assign(3, 5) // {5, 5, 5, 4, 5}
	// pop_front
	// v2.resize(v1.size()); 
	// C3(std::copy(v1.begin(), v1.end(), v2.begin()), showVector(v2));
	std::back_insert_iterator<std::vector<int>> back_inserter = std::back_inserter(v1);
	// inserter // T& operator*() { v1.push_back(); return v1.back();}


	C3((*back_inserter = 6), showVector(v1));
	C3((*back_inserter = 6), showVector(v1));

	
	std::set<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	s1.insert(3);
	s1.insert(3);
	s1.insert(4);
	s1.insert(5);
	// set<int>::iterator it;
	std::function<std::string(const std::set<int>&)> showSet = [](const std::set<int>& s)
	{
		string ret = "|";
		std::set<int>::iterator it = s.begin();
		for(;it != s.end();++it)
			ret += std::to_string(*it) + "|";
		return ret;
	};
	C2(*s1.find(3));
	C2(s1.find(10) == s1.end());
	C3(s1.erase(s1.find(3)), showSet(s1));
	C3(s1.erase(2), showSet(s1));
	C2(s1.size());
	C3(s1.erase(s1.begin(), s1.end()), showSet(s1));
	// stringTest.cpp
	
	std::map<std::string, int> m1; // map<key, value> m2
	std::function<std::string(const std::map<std::string, int>&)> showMap = [](const std::map<std::string, int>& m) -> std::string
	{
		std::string ret = "|";
		for(std::map<std::string, int>::const_iterator it = m.begin();it != m.end();++it)
			ret += it->first + ":" + std::to_string(it->second) + "|";
		return ret;
	};
	// pair<std::string, int> a = {"k9", 9};
	m1.insert(pair<std::string, int>("k0", 0));
	m1.insert(map<std::string, int>::value_type("k1", 1));
	// m1.emplace(pair<std::string, int>("k8", 8));
	m1.emplace(std::string("k6"), 6); // build
	m1["k2"] = 2;
	std::pair<map<std::string, int>::iterator, int> insert_ret = m1.insert(pair<std::string, int>("k0", 1));
	if(!insert_ret.second)
		std::cout << "insert_failed: k0, 1" << endl;
	C2(showMap(m1));
	map<std::string, int>::iterator mIter;
	C2((mIter = m1.find("k0")) != m1.end() && mIter->first == "k0" && mIter->second == 1);
	m1.erase(mIter);
	C2(m1.erase("k1"));
	// m1.erase(1);
	// m1.erase(m1.begin(), m1.end());
	C2(m1.size());
	C2(m1.count("k2"));

	C3(m1.insert({"k3", 3}), showMap(m1));
	map<std::string, int>::key_compare cmp = m1.key_comp();
	map<std::string, int>::value_compare cmpV = m1.value_comp();
	C2(cmp(m1.begin()->first, m1.begin()->first) == 0);
	C2(cmpV(*m1.begin(), *m1.begin()) == 0);
	// emplace_hint get_allocator

	m1.clear();
	C2(m1.empty());
	// C2(m1.max_size());
	// std::map<std::string, int> m2(m1);
	// std::map<std::string, int> m2(m1.begin(), m1.end());
	// mIter = m1.lower_bound("zz"); // *mIter < "zz"
	// mIter = m1.upper_bound("zz"); // *mIter > "zz"
	

	std::array<int, 5> a1 = {0, 1, 2, 3, 4}; // int a1[5] = {1, 2, 3, 4, 5};
	// vector
	C2(a1[4] == 4);
	// a1.fill(0);
	// [] at front back data begin end rbegin rend empty size max_size fill swap
	// std::reverse(a1.begin(), a1.end());
	


	std::list<int> l1;
	std::function<std::string(const std::list<int>&)> showList = [](const std::list<int>& l) -> std::string
	{
		std::string ret = "|";
		for(std::list<int>::const_iterator it = l.begin();it != l.end();++it)
			ret += std::to_string(*it) + "|";
		return ret;
	};
	l1.push_back(1);
	l1.push_front(2);
	l1.push_back(3);
	l1.push_back(5);
	// push_front emplace_front
	C2(showList(l1));
	C2(*l1.begin() == l1.front());
	C2(l1.back() == 5);
	C2(!l1.empty() && l1.size() == 4);
	// max_size()
	// l1.clear();
	// insert pop_back pop_front emplace_back emplace_front resize swap
	// resize(size); // resize(size, T()); // resize(size, v)
	// l1.swap(l2);

	std::list<int> l2;
	C3(l2.assign(l1.begin(), l1.end()), showList(l2));

	C3(l1.merge(l2), showList(l1));
	C2(showList(l2));

	C3(l2.assign(3, 7), showList(l2));

	C3(l1.merge(std::move(l2)), showList(l1));
	C2(showList(l2));
	// merge(list, Compare comp)

	C3(l2.assign({1, 2, 3, 4}), showList(l2));
	C3(l1.assign({5, 6, 7, 8}), showList(l1));

	std::list<int>::iterator lit = l1.begin();
	std::advance(lit, 2);

	C3(l1.splice(lit, l2), showList(l1));
	C2(showList(l2));

	C3((l2 = {9, 10, 11, 12}), showList(l2));
	// splice(const_iterator pos, std::list<T>&& other)
	std::list<int>::iterator lit2 = l2.begin();
	C3(l1.splice(lit, l2, lit2), showList(l1));
	C2(showList(l2));

	C3((l2 = {1, 2, 3, 17}), showList(l2));
	C3(l1.splice(lit, l2, l2.begin(), l2.end()), showList(l1));
	C2(showList(l2));

	C3(l1.remove(16), showList(l1));
	C3(l1.remove_if([](const int i){return i > 10;}), showList(l1));

	C3(l1.sort(), showList(l1)); // [](const int i, const int j){ return i - j;}
	C3(l1.reverse(), showList(l1));
	C3(l1.unique(), showList(l1));




	std::queue<int> q1;
	// std::queue<int, std::list<int>> q2; // LIST{T* prev, T* next}
	// std::queue<int, std::deque<int>> q3; // deque = vector + list
	q1.push(1); // push_back
	C2(q1.front() == 1);
	q1.push(2);
	C2(q1.back() == 2);
	q1.push(3);
	q1.emplace(4);
	q1.pop(); // pop_front
	C2(q1.front() == 2);
	C2(!q1.empty() && q1.size() == 3);

	std::priority_queue<int> pq1;
	pq1.push(2);
	pq1.push(4);
	pq1.push(1);
	pq1.emplace(3);
	C2(pq1.top() == 4);
	pq1.pop();
	C2(!pq1.empty() && pq1.size() == 3);

	std::priority_queue<TMP_TYPE> pq2;
	pq2.emplace(3, 2);
	pq2.emplace(7, 0);
	pq2.emplace(TMP_TYPE(1, 4));
	C2(pq2.top().first == 7);
	std::string s = "|";
	while(!pq2.empty())
	{
		s += std::to_string(pq2.top().first) + "," + std::to_string(pq2.top().second) + "|";
		pq2.pop();
	}
	C2(s);

	std::stack<int> s2;
	s2.push(1);
	s2.push(2);
	s2.push(3);
	s2.push(4);
	s2.push(5);
	C2(s2.size() == 5);
	s = "|";
	while(!s2.empty())
	{
		s += std::to_string(s2.top()) + "|";
		s2.pop();
	}
	C2(s);

	// std::find std::find_if // cpp11
	int sum = 0;
	std::vector<int>::iterator it;
	std::for_each(v1.begin(), v1.end(), [&](const int a)
	{
		sum += a;
	});
	it = std::adjacent_find(v1.begin(), v1.end());
	C2(it != v1.end() && *it == 6);

	std::vector<TMP_TYPE> v9;
	v9.push_back(TMP_TYPE(1, 2));
	v9.push_back(TMP_TYPE(2, 2));
	v9.push_back(TMP_TYPE(3, 2));
	v9.push_back(TMP_TYPE(3, 2));

	C2(std::adjacent_find(v9.begin(), v9.end(), [](const TMP_TYPE& a, const TMP_TYPE& b){ return a.first == b.first;}) != v9.end());

	std::function<int(int)> equal_6 = [](const int i)->int{return i == 6;};
	std::function<int(const int&, const int&)> pred = [](const int& a, const int& b)->int{return a < b;};
	// std::less<int>() // pred
	// std::greater<int>()

	C2(std::all_of(v1.cbegin(), v1.cend(), [](const int i){return i > 0;})); // C++11 // cbegin const_iterator
	C2(std::any_of(v1.cbegin(), v1.cend(), equal_6)); // C++11
	C2(std::count(v1.cbegin(), v1.cend(), 6) == 2);
	C2(std::count_if(v1.cbegin(), v1.cend(), equal_6) == 2);
	v2 = v1;
	C2(std::equal(v1.begin(), v1.begin() + 2, v2.begin()));
	// C2(*std::find(v1.begin(), v1.end(), 7) == 7);
	// std::find_if(v1.begin(), vec1.end(), equal_6);
	v1.insert(v1.end(), {7, 6, 6, 7});
	v2 = {6, 6};
	C2(showVector(v1) + "|" + showVector(v2));
	C2((it = std::find_end(v1.begin(), v1.end(), v2.begin(), v2.end())) != v1.end() && *(--it) == 7);
	C2((it = std::search(v1.begin(), v1.end(), v2.begin(), v2.end())) != v1.end() && *(--it) != 7); // it = std::search(v1.begin(), v1.end(), v2.begin(), v2.end(), [](const int a, const int b)->int{return a - b;})
	C2((it = std::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end())) != v1.end() && *(--it) != 7);
	// it = std::find_if(vec2.begin(), vec2.end(), [](const int i){return i == 5;});
	// find_if_not // none_of
	C2(std::search_n(v2.begin(), v2.end(), 2, 6) == v2.begin()); // std::search_n(v2.begin(), v2.end(), 2, 6, pred);
	(void)pred;
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> pair_ret1;
	pair_ret1 = std::mismatch(v1.begin(), v1.end(), v2.begin());
	C2(*pair_ret1.first == v1.front());
	// pair_ret1 = mismatch(v1.begin(), v1.end(),v1.begin(), v1.end());pair_ret1 = mismatch(v1.begin(), v1.end(),v1.begin(), v1.end(), [](const int& a, const int& b)->int{return a - b;});  



	// C3(std::copy(v1.begin(), v1.end(), v2.begin()), showVector(v2));
	C3(std::copy(v1.begin(), v1.end(), std::back_inserter(v2)), showVector(v2)); // v2 = v2 + v1 
	v2.resize(std::distance(v1.begin(), v1.end())); // v1.size()
	C3(std::copy_backward(v1.begin(), v1.end(), v2.end()), showVector(v2));
	// it = std::find_if(v2.begin(), v2.end(), equal_6);
	// it = std::find_if_not(vec2.begin(), equal_6);
	C3(std::random_shuffle(v2.begin(), v2.end()), showVector(v2));
	C3(std::fill(v2.begin(), v2.end(), 0), showVector(v2));
	C3(std::copy_n(v1.begin(), 3, v2.begin()), showVector(v2));
	C3(std::fill_n(v2.begin() + 3, 3, 5), showVector(v2));
	it = v1.begin() + 3;
	std::function<int(void)> gen = [&](void)->int
	{
		if(it == v1.end())
			return 0;
		else
			return *(it++);
	};
	C3(std::generate(v2.begin(), v2.end(), gen), showVector(v2));
	// generate_n(v2.begin(), 3, gen);
	C3(std::iter_swap(v2.begin(), v2.end() - 1), showVector(v2));
	// v2 = std::move(v1);
	// C3(std::move_backward(v1.begin(), v1.end(), v2.end()), showVector(v2));

	std::vector<std::string> v10 = {"a", "aa", "aaa", "b", "a", "a", "c", "d", "aa", "ab", "e", "ah"};
	// remove: it = std::move(deleted_vec);
	std::function<std::string(const std::vector<std::string>&)> showVector2;
	showVector2 = [](const std::vector<std::string>& v)->std::string
	{
		std::string ret = "|"; 
		for(std::vector<std::string>::const_iterator it = v.begin();it != v.end();++it)
			ret += *it + "|";
		return ret;
	};
	std::vector<string>::iterator sit;
	C3((sit = std::remove(v10.begin(), v10.end(), "a")), showVector2(v10));
	C3(s = std::move(*sit), showVector2(v10));
	C3((sit = std::remove_if(v10.begin(), v10.end(), [](const string& s){return s[0] == 'a';})), showVector2(v10));
	C3(s = std::move(*sit), showVector2(v10));
	// C3(std::remove_copy_if(v10.begin(), v10.end(), v11.begin(), [](const string& s){return s.size() > 1;}), showVector2(v10));
	// remove_copy(v10.begin(), v10.end(), v11.begin(), "ab");
	
	C3(std::replace(v2.begin(), v2.end(), 0, 5), showVector(v2));
	C3(std::replace_if(v2.begin(), v2.end(), equal_6, 17), showVector(v2));
	C3(std::replace_copy(v1.begin(), v1.end(), v2.begin(), 0, 5), showVector(v2));
	// C3(std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), equal_6, 5), showVector(v2));
	C3(std::reverse(v2.begin(), v2.end()), showVector(v2));
	C3(std::reverse_copy(v1.begin(), v1.end(), v2.begin()), showVector(v2));
	C3(std::rotate_copy(v1.begin(), v1.begin() + 3, v1.end(), v2.begin()), showVector(v1) + "|" + showVector(v2));
	// rotate(v2.begin(), v2.begin() + 2, v2.end());
	
	std::random_device rd;
	C3(std::shuffle(v2.begin(), v2.end(), rd), showVector(v2)); // random_shuffle
	// std::swap(v1, v2);
	// std::swap_ranges(v1.begin(), v1.begin() + 3, v2.begin()); // swap(v1[0], v2[0]) swap(v1[1], v2[1]) swap(v1[2], v2[2])
	// C3(std::unique(v2.begin(), v2.end()), showVector(v2));
	// std::unique_copy(v1.begin(), v1.end(), std::back_inserter(v2), [](const int& a, const int& b)->{return a == b;});
	C3(std::transform(v2.begin(), v2.end(), v2.begin(), [](const int& i)->int{return i + 5;}), showVector(v2));
	C3(std::transform(v1.begin(), v1.end(), v2.begin(), v2.begin(), std::plus<int>()), showVector(v2));
	// std::plus<int>() = [](const int& a, const int& b)->int{return a + b;}
	

	std::function<int(const int&)> partion_pred = [](const int& i){return i < 14;};
	C3((it = std::partition(v2.begin(), v2.end(), partion_pred)), showVector(v2));
	// stable_partition
	// partion_copy(v2.begin(), v2.end(), true_ret.begin(), false_ret.begin(), partion_pred);
	C2(std::is_partitioned(v2.begin(), v2.end(), partion_pred) && std::partition_point(v2.begin(), v2.end(), partion_pred) == it && !partion_pred(*it)); // [9, 10, 11] : true, [15, 16, 17]: false
	// v2.push_back(5) // is_partitioned false
	
	C3(std::partial_sort(v2.begin(), v2.begin() + 5, v2.end(), std::less<int>()), showVector(v2));
	C3(std::sort(v2.begin() + 6, v2.end(), std::less<int>()), showVector(v2));
	// std::sort(v2.rbegin(), v2.rend());
	C3(std::inplace_merge(v2.begin(), v2.begin() + 5, v2.end(), std::less<int>()), showVector(v2));

	// C3(std::sort(v2.begin(), v2.end()), showVector(v2));
	// C3(std::stable_sort(v2.start(), v2.end(), showVector(v2));
	C2(std::is_sorted(v2.begin(), v2.end()));
	C2((*(it = v2.begin() + 5) = 5) && std::is_sorted_until(v2.begin(), v2.end()) == it);
	C2((*it = 14));
	C3(std::nth_element(v2.begin(), it, v2.end()), showVector(v2));
	C2(*it == 14); // std::sort(v2.begin(), v2.end()); v2[5]
	// nth_element(v2.begin(), v2.end() + 5, v2.end(), std::less<int>());
	// std::sort
	C3(std::partial_sort_copy(v1.begin(), v1.begin() + 5, v2.begin(), v2.end(), std::less<int>()), showVector(v2));

	v1 = {1, 2, 3, 4, 5};
	v2 = {1, 2, 3, 4};
	v4 = {};

	C2(std::includes(v1.begin(), v1.end(), v3.begin(), v3.end(), std::less<int>()));
	// C2(std::includes(v1.begin() + 5, v1.begin() + 7, v2.begin(), v2.begin() + 1)); // std::set<int>
	// C3(std::merge(s1.begin(), s1.end(), s3.begin(), s3.end(), std::back_inserter(s4), std::less<int>()), showSet(s4));

	C3(std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4), std::less<int>()), showVector(v4));
	// inplace_merge
	v4.resize(0);

	C3(std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4), std::less<int>()), showVector(v4)); // v1 - v2
	v4.resize(v1.size() + v2.size());
	C3(std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin(), std::less<int>()), showVector(v4)); // v1 | v2
	v4.resize(0);
	C3(std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4), std::less<int>()), showVector(v4)); 
	v4.resize(0);
	C3(std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4), std::less<int>()), showVector(v4)); // v1 & v2

	v2 = v1;
	C3(std::make_heap(v2.begin(), v2.end(), std::less<int>()), showVector(v2));
	v2.push_back(9);
	C3(std::push_heap(v2.begin(), v2.end(), std::less<int>()), showVector(v2));
	C2(v2.front() == 9);
	C3(std::pop_heap(v2.begin(), v2.end(), std::less<int>()), showVector(v2));
	C3(v2.pop_back(), showVector(v2));
	C2(std::is_heap(v2.begin(), v2.end(), std::less<int>()));
	C3(std::sort_heap(v2.begin(), v2.end(), std::less<int>()), showVector(v2));
	// std::vector<int>::const_iterator heap_end = std::is_heap_until(v2.begin(), v2.end());


	C2(!std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), std::less<int>())); // !(v1 < v2)
	C2(*std::max_element(v1.begin(), v1.end(), std::less<int>()) == std::max(*(v1.end() - 2), *(v1.end() - 1)));
	// min min_element

	std::pair<int, int> int_pair;
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> int_it_pair;
	C2((int_pair = std::minmax(1, 2)).first == 1 && int_pair.second == 2);
	C2((int_it_pair = std::minmax_element(v1.begin(), v1.end(), std::less<int>())).first == v1.begin() && *int_it_pair.second == *(v1.end() - 1));

	v2 = {5, 4, 1, 2, 3};
	C2(showVector(v1) + "," + showVector(v2));
	C2(std::is_permutation(v1.begin(), v1.end(), v2.begin())); // sort(v1.begin(), v1.end()) sort(v2.begin(), v2.end()) v1==v2 // str.begin(), str.end()
	s = "";
	v2 = {1, 2, 3, 4};
	do
	{
		s += std::to_string(v2[0]) + std::to_string(v2[1]) + std::to_string(v2[2]) + std::to_string(v2[3]) + ",";
	}
	while(next_permutation(v2.begin(), v2.end()));
	// prev_permutation
	C2(s);

	// std::vector<int>::reverse_iterator rit;
	// std::reverse_iterator<std::vector<int>::iterator> rit(v1.end());
	// (void) rit;
	it = v1.begin();
	C2(it[0] = *it);
	C2(*next(it, 2) == it[2]);
	std::advance(it, 2);
	C2(*prev(it, 2) == v1[0]); // prev(it, -1)
	// * + ++ += - -- -= -> []
	std::back_insert_iterator<std::vector<int>> it2(v2);
	*it2 = 5;
	*it2 = 5;
	C2(showVector(v2));
	it2 = std::back_inserter(v2);
	// front_insert_iterator

	std::insert_iterator<std::vector<int>> insert_it2(v2, v2.begin() + 3);
	*insert_it2 = 5;
	*insert_it2 = 5;
	C2(showVector(v2));


	std::vector<std::string> v11(std::make_move_iterator(v10.begin()), std::make_move_iterator(v10.end())); // v11[i]  std::move(v10[i])
	std::move_iterator<std::vector<std::string>::iterator> move_it = std::make_move_iterator(v11.begin());
	sit = move_it.base();

	// streambuf_iterator
	// istream_iterator<int> in_it(std::cin), in_e; // 1 2 3 c
	// std::copy(in_it, in_e, std::back_inserter(v2)); // 1 2 3
	cout << showVector(v2) << endl;
	// std::cout.flush();
	std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " ")); // i + ""
	std::cout << endl; 

	std::unordered_map<std::string, int> u1 = {{"k6", 6}, {"k7", 7}}; // O(1)
	u1.insert({"k0", 0});
	u1.insert({"k1", 1});
	u1.insert({"k2", 2});
	u1["k3"] = 3;
	u1.emplace(std::string("k4"), 4);
	C2(u1["k0"] == 0);
	s = "|";
	for(std::unordered_map<std::string, int>::const_iterator it = u1.cbegin(); it != u1.cend();++it)
		s += it->first + ":" + std::to_string(it->second) + "|";
	C2(s);
	// erase count size max_size find clear swap emplace_hint
	// bucket_count() max_bucket_count bucket_size(n): bucket[n]size bucket[key]
	// load_factor max_load_factor reserve() hash_function()

	// template < class Key, class T, class Hash = hash<Key>, class Pred = equal_to<Key>, class Alloc = allocator< pair<const Key,T> > > class unordered_map;
	std::function<size_t(const TMP_TYPE& t)> tmp_hash = [](const TMP_TYPE& t)
	{
		return std::hash<int>()(t.first);
		// return std::hash<int>()(t.first) ^ std::hash<int>(t.second);
	};
	std::unordered_map<TMP_TYPE, int, std::function<size_t(const TMP_TYPE&)>> u2(40, tmp_hash); // size_t(*)(const TMP_TYPE&)
	u2.emplace(TMP_TYPE(1, 1), 1);
	std::pair<unordered_map<TMP_TYPE, int, std::function<size_t(const TMP_TYPE&)>>::iterator, bool> u_insert_ret = u2.emplace(TMP_TYPE(2, 1), 2);
	u2.emplace(TMP_TYPE(3, 1), 3);
	C2(u2[u_insert_ret.first->first] == 2);
	std::unordered_map<TMP_TYPE, int, TMP_TYPE_HASH, TMP_TYPE_EQUAL_TO> u3;
	u3.emplace(TMP_TYPE(1, 0), 1);
	// TMP_TYPE_HASH t; cout << "HASH" << t(TMP_TYPE(1, 2)) << endl;
	
	// std::unordered_multimap
	// std::unordered_set
	// std::unordered_multiset

	// template < class Key, class T, class Hash = hash<Key>, class Pred = equal_to<Key>, class Alloc = allocator< pair<const Key,T> > > class unordered_map;
	

	// std::forward_list<int> l3 // - prev
	// l3.insert_after(l3.begin(), 3) // implace_after erase_after
	
	std::unordered_multimap<int, int> m3;
	m3.emplace(1, 1);
	m3.emplace(1, 2);
	m3.emplace(1, 3);
	m3.emplace(2, 1);
	m3.emplace(2, 2);
	m3.emplace(2, 3);
	// insert erase empty size resize
	// erase(key) erase(it)
	std::unordered_multimap<int, int>::const_iterator mmit = m3.find(2);
	i = 0;
	for(;mmit != m3.end();mmit++)
	{
		if(mmit->first != 2)
			continue;
		i += mmit->second;
	}
	C2(m3.count(2) == 3);
	std::pair<std::unordered_map<int, int>::iterator, std::unordered_map<int, int>::iterator> er = m3.equal_range(2);
	for(mmit = er.first;mmit != er.second;++mmit)
	{
		i -= mmit->second;
	}
	// lower_bound(2) // upper_bound(2) // pair<it, it>
	C2(i == 0);
	C2(m3.key_eq()(1, 1)); // key_comp
	C2(m3.hash_function()(7));
	// .count(n)

	// C2(m3.value_comp()());

	std::allocator<int> ai;
	int* p = ai.allocate(5);
	std::uninitialized_fill(p, p + 4, 0); // int(0)
	// std::uninitialized_fill_n(p, 4, 0);
	new (p + 4) int(5);
	C2(p[0] == p[1]);
	ai.deallocate(p, 5); // p != nullptr

	std::allocator<std::string> ap;
	std::string* pp = ap.allocate(5);

	ap.construct(pp, "cc"); // pair<int, int>(1, 2);
	ap.construct(pp + 1, 2, 'c');
	C2(pp[0] == pp[1]); // cc
	std::uninitialized_copy(pp, pp + 2, pp + 2); // string(s) // ap.construct(pp + 2, *pp);
	// std::uninitialized_copy_n(pp, 2, pp + 2);
	C2(pp[0] == pp[2] && pp[1] == pp[3]);
	ap.destroy(pp);
	ap.destroy(pp + 1);
	ap.destroy(pp + 2);
	ap.destroy(pp + 3);

	ap.deallocate(pp, 5);
}


