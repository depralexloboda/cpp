class set{
	struct Node{
		int key;
		Node* L;
		Node* R;
		Node* P;
		Node(int x, Node*);
	};
	Node* head;
	void copy(Node*, Node*);
	void recDel(Node*);
public:
	class iterator{
		friend class set;
		Node* link;
		iterator(Node*);
	public:
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		int& operator*() const;
		bool operator==(iterator const&) const;
		bool operator!=(iterator const&) const;
	};
	set();
	~set();
	set(set const&);
	set& operator=(set const&);
	void insert(int);
	iterator find(int);
	void erase(iterator);
	iterator begin();
	iterator end();
};
