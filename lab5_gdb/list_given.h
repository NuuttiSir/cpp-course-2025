// Created by Jack Toole, Fall 2011
// Modified by Veer Dedhia, Spring 2014
// Modified in Spring 2025 by Anna LaValle and Elmeri Uotila

// Iterator code, initially from C++ reference:
// http://www.cplusplus.com/reference/std/iterator/iterator/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
class ListIterator : public std::iterator<std::forward_iterator_tag, T>
{
	ListNode* p;
	public:
	ListIterator() : p(NULL) { }
	ListIterator(ListNode * x) : p(x) { }
	ListIterator& operator++()   { p = p->next; return *this; } // Pre-Increment
	ListIterator operator++(int) { ListNode* r = p; p = p->next; return ListIterator(r); } // Post-Increment
	bool operator==(const ListIterator& rhs) { return p == rhs.p; }
	bool operator!=(const ListIterator& rhs) { return p != rhs.p; }
	const T & operator*() const  { return p->data; }
	const T * operator->() const { return &(p->data); }
	T & operator*() { return p->data; }
	T * operator->() { return &(p->data); }
};
typedef const ListIterator const_iterator;
const_iterator         begin()  const { return ListIterator(head); }
const_iterator         end()    const { return ListIterator(NULL); }
#pragma GCC diagnostic pop
