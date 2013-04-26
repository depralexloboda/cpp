#include "set.h"

set::Node::Node(int x, Node* P = 0){
	this->key = x;
	this->L = 0;
	this->P = P;
	this->R = 0;
}

set::iterator::iterator(Node* smth) :link(smth){}

int& set::iterator::operator*() const{
	return (*link).key;
}

bool set::iterator::operator==(iterator const& smth) const{
	return link == smth.link;
}

bool set::iterator::operator!=(iterator const& smth) const{
	return link != smth.link;
}

set::iterator& set::iterator::operator++(){
	if(link->R){
		link = link->R;
		while(link->L){
			link = link->L;
		}
	} else {
		while(link == link->P->R){
			link = link->P;
		}
		link = link->P;
	}
	return *this;
}

set::iterator set::iterator::operator++(int){
	Node *mem = link;
	if(link->R){
		link = link->R;
		while(link->L){
			link = link->L;
		}
	} else {
		while(link == link->P->R){
			link = link->P;
		}
		link = link->P;
	}
	return iterator(mem);
}

set::iterator& set::iterator::operator--(){
	if(link->L){
		link = link->L;
		while(link->R){
			link = link->R;
		}
	} else {
		while(link->P->L == link){
			link = link->P;
		}
		link = link->P;
	}
	return *this;
}

set::iterator set::iterator::operator--(int){
	Node* mem = link;
	if(link->L){
		link = link->L;
		while(link->R){
			link = link->R;
		}
	} else {
		while(link->P->L == link){
			link = link->P;
		}
		link = link->P;
	}
	return iterator(mem);
}

set::set(){
	head = new Node(0);
}

set::~set(){
	delete head;
}

set::iterator set::begin(){
	Node* cur = head;
	while(cur->L){
		cur = cur->L;
	}
	return iterator(cur);
}

set::iterator set::end(){
	return iterator(head);
}

void set::insert(int x){
	if(!head->L){
		head->L = new Node(x, head);
		return;
	}
	Node *cur = head->L;
	while(true){
		if(x <= cur->key){
			if(cur->L){
				cur = cur->L;
			} else {
				cur->L = new Node(x, cur);
				return;
			}
		} else {
			if(cur->R){
				cur = cur->R;
			} else {
				cur->R = new Node(x, cur);
				return;
			}
		}
	}
}

set::iterator set::find(int x){
	if(!head->L){
		return end();
	}
	Node* cur = head->L;
	while(true){
		if(x < cur->key){
			if(cur->L){
				cur = cur->L;
			} else {
				return end();
			}
		} else if(x > cur->key) {
			if(cur->R){
				cur = cur->R;
			} else {
				return end();
			}
		} else {
			return iterator(cur);
		}
	}
}

void set::erase(iterator it){
	Node *cur = it.link;
	if(!cur->L && !cur->R){
		if(cur == cur->P->L){
			cur->P->L = 0;
		} else {
			cur->P->R = 0;
		}
		delete cur;
		return;
	}
	Node* replace;
	if(cur->L){
		replace = cur->L;
		while(replace->R){
			replace = replace->R;
		}
		if(replace == replace->P->L){
			replace->P->L = replace->L;
		} else {
			replace->P->R = replace->L;
		}
		if(replace->L)
			replace->L->P = replace->P;
	} else {
		replace = cur->R;
		while(replace->L){
			replace = replace->L;
		}
		if(replace == replace->P->L){
			replace->P->L = replace->R;
		} else {
			replace->P->R = replace->R;
		}
		if(replace->R)
			replace->R->P = replace->P;
	}
	cur->key = replace->key;
	delete replace;
	return;
}

void set::copy(Node* s, Node* d){
	if(s->L){
		d->L = new Node(s->L->key, d);
		copy(s->L, d->L);
	}
	if(s->R){
		d->R = new Node(s->R->key, d);
		copy(s->R, d->R);
	}
}

set::set(set const& s){
	head = new Node(0);
	copy(s.head, head);
}

set& set::operator=(set const& s){
	head = new Node(0);
	copy(s.head, head);
	return *this;
}