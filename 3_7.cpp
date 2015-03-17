// 3.7 An animal shelter holds only dogs and cats, and operates on a strictly
// "first in,  first out" basis. People must adopt either the "oldest"
// (based on arrival time) of all animals at the shelter, or they can select whether
// they would prefer a dog or a cat (and will receive  the oldest animal of that type).
// They cannot select which specific animal they would like. Create the data structures
// to maintain this system and implement operations such as enqueue,  dequeueAny,
// dequeueDog and dequeueCat. You may use the built-in LinkedList data structure.

#include <iostream>
#include <list>
#include <stack>
#include <stdexcept>

using namespace std;

typedef enum _PET {UNKNOWN, CAT, DOG} PET;

class pet_queue {
	private:
		list<PET> queue;
		int cats;
		int dogs;
	public:
		pet_queue() : cats(0), dogs(0) {}
	public:
		void enqueue(PET p);
		PET dequeueAny();
		PET dequeueCat();
		PET dequeueDog();
	private:
		PET dequeue(PET type);
		void inc(PET p);
		void dec(PET p);
		int count(PET p);
	public:
		void trace();
};

void pet_queue::enqueue(PET p) {
	queue.push_front(p);
	inc(p);
}

PET pet_queue::dequeueAny() {
	if(queue.empty()) throw out_of_range("pet_queue::dequeAny empty queue");
	PET p = queue.back();
	queue.pop_back();
	dec(p);
	return p;
}

PET pet_queue::dequeueCat() {
	return dequeue(CAT);
}

PET pet_queue::dequeueDog() {
	return dequeue(DOG);
}

PET pet_queue::dequeue(PET type) {
	if(count(type) <= 0) throw out_of_range("pet_queue::dequeue absent pet of type");
	if(queue.empty()) throw out_of_range("pet_queue::dequeue empty queue");
	stack<PET> s;
	while(!queue.empty()) {
		PET p = dequeueAny();
		if(p == type) break;
		s.push(p);
	}
	while(!s.empty()) {
		queue.push_back(s.top());
		inc(s.top());
		s.pop();
	}
	return type;
}

void pet_queue::inc(PET type) {
	switch(type) {
		case CAT: cats ++;  break;
		case DOG: dogs ++; break;
		default: break;
	}
}

void pet_queue::dec(PET type) {
	switch(type) {
		case CAT: cats --;  break;
		case DOG: dogs --; break;
		default: break;
	}
}

int pet_queue::count(PET type) {
	switch(type) {
		case CAT: return cats;
		case DOG: return dogs;
		default: return (-1);
	}
}

void pet_queue::trace() {
	for(list<PET>::iterator it = queue.begin(); it != queue.end(); it++) {
		switch(*it) {
			case CAT: cout << "cat" << endl; break;
			case DOG: cout << "dog" << endl; break;
			default: cout << "UNKNOWN ANIMAL TYPE" <<  endl; break;
		}
	}
	cout << endl;
}

int main(void) {
	pet_queue q;

	q.enqueue(DOG);
	q.enqueue(DOG);
	q.enqueue(CAT);
	q.enqueue(DOG);
	q.enqueue(DOG);
	q.enqueue(DOG);
	q.enqueue(CAT);
	q.enqueue(CAT);
	q.enqueue(DOG);

	//q.trace();

	bool ok = true;

	ok &= q.dequeueAny() == DOG;
	//q.trace();
	ok &= q.dequeueAny() == DOG;
	//q.trace();
	ok &= q.dequeueAny() == CAT;
	//q.trace();
	ok &= q.dequeueCat() == CAT;
	//q.trace();
	ok &= q.dequeueAny() == DOG;
	//q.trace();
	ok &= q.dequeueCat() == CAT;
	//q.trace();
	ok &= q.dequeueDog() == DOG;
	//q.trace();

	if(!ok) cout << "PROBLEM!" << endl;

	return 0;
}
