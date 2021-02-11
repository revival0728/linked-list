#include <iostream>
#include <iterator>
#include <functional>
#include <initializer_list>

template <class T, class size_type=unsigned int>
class vec {
	struct vec_node {
		T val;
		vec_node *next, *last;

		vec_node(T _val, vec_node *_next=nullptr, vec_node *_last=nullptr) : val(_val), next(_next), last(_last) {}

		bool operator==(const vec_node *nd) {
			return (val == nd->val && next == nd->next && last == nd->last);
		}
		bool operator!=(const vec_node *nd) {
			return (val != nd->val && next != nd->next && last != nd->last);
		}
	} *root, *tail, *tmp;


	public:
	vec() { root = tail = new vec_node(T()); tmp = nullptr; }
	void push_back(T val) {
		tmp = tail;
		tail->val = val;
		tail->next = new vec_node(T(), nullptr, tmp);
		tail = tail->next;
	}
	void pop_back() {
		tail = tail->last;
		delete tail->next;
	}
	void push_front(T val) {
		tmp = root;
		root->last = new vec_node(val, root, nullptr);
		root = root->last;
	}
	void pop_front() {
		root = root->next;
		delete root->last;
	}
	T& operator[](int I) {
		switch (I < 0) {
			case true:
				I = -I;
				tmp = tail;
				while(I--)
					tmp = tmp->last;
				return tmp->val;
			case false:
				tmp = root;
				while(I--)
					tmp = tmp->next;
				return tmp->val;
		}
	}
	T& at(int I) {
		try {
			switch (I < 0) {
				case true:
					I = -I;
					tmp = tail;
					while(I--) {
						if(!tmp->last)
							throw "class vec<T>::at() throw \"Index out of range\"";
						tmp = tmp->last;
					}
					return tmp->val;
				case false:
					tmp = root;
					while(I--) {
						if(tmp->next == tail)
							throw "class vec<T>::at() throw \"Index out of range\"";
						tmp = tmp->next;
					}
					return tmp->val;
			}
		} catch (const char *msg) {
			std::cerr << msg << '\n';
		}
	}
	T& front() { return root->val; }
	T& back() { return (tail->last)->val; }


	class iterator : public std::iterator<std::input_iterator_tag, T> {
		vec_node *p;
		friend class vec;

		vec_node* get_node_address() {return p;}

		public:
		iterator(vec_node *x) :p(x) {}
		iterator(const iterator& mit) : p(mit.p) {}
		iterator& operator++() {p=p->next;return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator& operator--() {p=p->last;return *this;}
		iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
		iterator operator+(size_type mv) {while(mv--) p=p->next; return *this;}
		iterator operator-(size_type mv) {while(mv--) p=p->last; return *this;}
		bool operator==(const iterator& rhs) const {return p==rhs.p;}
		bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
		T& operator*() {return p->val;}
	};

	iterator begin() { return iterator(root); }
	iterator end() { return iterator(tail); }

	vec(std::initializer_list<T> inlst) {
		tail = root = new vec_node(T()); tmp = nullptr;
		for(auto& i : inlst)
			this->push_back(i);
	}
	vec(iterator first, iterator last) {
		tail = root = new vec_node(T()); tmp = nullptr;
		while(first != last)
			this->push_back(*first++);
	}
	vec(size_type _size, T val=T()) {
		tail = root = new vec_node(T()); tmp = nullptr;
		while(_size--)
			this->push_back(val);
	}
	vec(const vec<T>& vc) {
		this->vec();
		for(auto& i : vc)
			this->push_back(i);
	}
	vec<T>& operator=(const vec<T>& vc) {
		this->vec();
		for(auto& i : vc)
			this->push_back(i);
	}
	void clear() {
		this->vec();
	}
	void resize(size_type _size, T val=T()) {
		this->vec();
		while(_size--)
			this->push_back(val);
	}

	void insert(iterator itr, T val) {
		vec_node *it = itr.get_node_address();
		if(it == tail) {
			push_back(val);
			return;
		}
		tmp = it->next;
		it->next = new vec_node(it->val, tmp, it);
		it->val = val;
	}
	void erase(iterator itr) {
		vec_node *it = itr.get_node_address();
		if(it == root) {
			pop_front();
			return;
		}
		tmp = it->last;
		tmp->next = it->next;
		(it->next)->last = tmp;
		delete it;
	}

	size_type size() {
		unsigned ret = 0;
		tmp = root;
		while(tmp != tail) {
			tmp = tmp->next;
			ret++;
		}
		return ret;
	}

	void sort(size_type first, size_type last, std::function<T(T, T)> Cmp) {
		size_type mid = (first+last) / 2;
		if(first < last-1) {
			sort(first, mid, Cmp);
			sort(mid, last, Cmp);
		}
		vec<T> lvc(begin()+first, begin()+mid), rvc(begin()+mid, begin()+last);
		iterator it_lvc = lvc.begin(), it_rvc = rvc.begin(), it = begin()+first;
		while(it_lvc != lvc.end() && it_rvc != rvc.end()) {
			if(Cmp(*it_lvc, *it_rvc))
				*it++ = *it_lvc++;
			else
				*it++ = *it_rvc++;
		}
		while(it_lvc != lvc.end())
			*it++ = *it_lvc++;
		while(it_rvc != rvc.end())
			*it++ = *it_rvc++;
	}

	void sort(std::function<T(T, T)> Cmp = std::less<T>()) {
		sort(0, this->size(), Cmp);
	}
};

using namespace std;

int main() {}
