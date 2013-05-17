#define BOOST_TEST_MODULE set
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "set.cpp"
#include <sstream>
#include <string>

BOOST_AUTO_TEST_CASE(insert){
	// insert() + iterator::operator++(int) + begin() + end() + iterator::end() + iterator::operator* + iterator::operator!=
	set t;
	std::ostringstream s, s2;
	for(int i = 0; i < 100; i++){
		t.insert(i);
		s << i << " ";
	}
	for(set::iterator it = t.begin(); it != t.end(); it++){
		s2 << *it << " ";
	}
	BOOST_CHECK_EQUAL(s.str(), s2.str());
}

BOOST_AUTO_TEST_CASE(erase){
	// erase + find + operator= + iterator::operator++() + set(set const&)
	set t;
	for(int i = 0; i < 100; i++){
		t.insert(i);
	}
	set t2 = t;
	BOOST_CHECK_EQUAL(t.find(50) != t.end(), true);
	t.erase(t.find(50));
	BOOST_CHECK_EQUAL(t.find(50) != t.end(), false);
	BOOST_CHECK_EQUAL(t2.find(50) != t.end(), true);
	set t3(t2);
	set::iterator it = t2.begin();
	++it;
	t2.erase(it);
	BOOST_CHECK_EQUAL(*(++t2.begin()) != *(++t3.begin()), true);
}

BOOST_AUTO_TEST_CASE(decrement_iterator){
	//iterator::operator--(int) + iterator::operator--() + iterator::operator==
	set t;
	for(int i = 0; i < 100; i++){
		t.insert(i);
	}
	set::iterator it = t.end();
	for(int i = 0; i < 100; i++){
		if(i % 2){
			--it;
		} else {
			it--;
		}
	}
	BOOST_CHECK_EQUAL(it == t.begin(), true);
}
