#include<iostream>
using namespace std;

template<class T> class PrioList;

template<class T>
class Element {
	friend class PrioList<T>;
	public:
		Element() {
			_next = nullptr;
			_prev = nullptr;
		}
		// Element(T value): Element(), _value(value) {}
		Element(T value): Element() {
			_value   = value;
			_N_value = 1;
			_prio    = 0;
		}
		~Element() {}

	private:
		unsigned int _prio;
		T _value;
		T _N_value;
		Element<T> *_next;
		Element<T> *_prev;
};

template<class T>
class PrioList {
	friend class Element<T>;
	public:
		PrioList() {
			_size = 0;
		}

		~PrioList() {
			cout << "Destructor called" << endl;
			Element<T> *e;
			int N = _size;
			for(int i=0; i<N; i++) {
				e = front();
				if(e == nullptr) {
					cout << "nullptr" << endl;
				}
				cout << "Deleing element >> prio:" << e->_prio << ", value:" << e->_value << ", #:" << e->_N_value << endl;
				pop();
			}
		}

		void print() {
			Element<T> *current = _front;
			for(int i=0; i<_size; i++) {
				cout << current->_value << "(" << current->_prio << ") " << endl;
				current = current->_next;
			}
			cout << endl;
		}

		void push(T value) {
			Element<T> *_new = new Element<T>(value);
			if(_size == 0) {
				_front = _new;
				_back  = _new;
			} else {
				_back->_next = _new;
				_new->_prev   = _back;
				_back        = _back->_next;
			}
			_size++;
		}

		Element<T>* front() {
			return(_front);
		}

		void pop() {
			if(_size > 0) {
				Element<T> *element = _front;
				if(_size == 1) {
					_front        = nullptr;
					_back         = nullptr;
				} else {
					_front        = _front->_next;
					_front->_prev = nullptr;
				}
				delete element;
				_size--;
			}
		}

		void find(T value) {
			Element<T> *node_2_move = remove(value);
			if(node_2_move != nullptr) {
				cout << "Removed element with value " << node_2_move->_value << endl;
				print();
			} else {
				cout << "Value " << value << " does not exist." << endl;
			}
			insert(node_2_move);
			cout << "end of find" << endl;
		}

		Element<T>* remove(T value) {
			Element<T> *current = _front;
			Element<T> *result  = nullptr;

			for(int i=0; i<_size; i++) {
				if(current->_value == value) {
					result = current;
					_size--;
					if(current == _front) {
						_front = _front->_next;
						_front->_prev = nullptr;
					}
					if(current == _back) {
						_back = current->_prev;
						_back->_next = nullptr;
					}
					if(i > 0 && i < _size-1) {
						Element<T> *before = current->_prev;
						Element<T> *after  = current->_next;

						before->_next = after;
						after->_prev  = before;
					}
					result->_next = nullptr;
					result->_prev = nullptr;
					i = _size;
				} else {
					current = current->_next;
				}
			}
			return(result);
		}

	private:
		unsigned int _size;
		Element<T> *_front;
		Element<T> *_back;

		void insert(Element<T> *elem) {
			if(elem != nullptr) {
				elem->_prio++;
				Element<T> *next = _front;
				Element<T> *tmp;
				if(_size == 0) {
					_front = elem;
					_back  = elem;
				}
				for(int i=0; i<_size; i++) {
					if(next == nullptr && i == _size-1) {
						_back->_next = elem;
						elem->_prev  = _back;
						_back        = elem;
					}

					if(elem->_prio >= next->_prio) {
						cout << "elem->_prio >= next->_prio : " << elem->_prio << " >= " << next->_prio << " | values:" << elem->_value << "," << next->_value << endl;
						tmp = next->_prev;
						next->_prev = elem;
						elem->_prev = tmp;
						elem->_next = next;
						if(tmp != nullptr) {
							tmp->_next = elem;
						} else {
							cout << "_front = elem;" << endl;
							_front = elem;
						}
						cout << "i = ++_size;" << endl;
						i = ++_size;
					}
					cout << "}" << endl;

					if(next != nullptr) next = next->_next;
					cout << "if(next != nullptr) next = next->_next;" << endl;
				}
			}
			cout << "end of insert" << endl;
			cout << "_front:" << _front << "   " << _front->_value << endl;
			cout << "_back:"  << _back  << "   " << _back->_value << endl;
		}
};

int main(int argc, char **argv) {

	PrioList<int> pq;
	for(int i=1; i<argc; i++) {
		pq.push( atoi(argv[i]) );
	}
	pq.print();

	char opt = 'Y';
	int  input;
	do {
		cout << "Find an element? [Y/n]: ";
		cin  >> opt;
		if(opt == 'n' || opt == 'N') break;
		cout << "Look for: ";
		cin  >> input;
		pq.find(input);
		pq.print();
	} while(opt != 'n' || opt != 'N');

	return(0);
}
