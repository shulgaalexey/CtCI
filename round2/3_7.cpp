#include <iostream>
#include <vector>
#include <string>
using namespace std;

class animal {
	public:
		int time;
		string name;
		int type; // 0 - dog, 1 - cat
		animal(const string &n, const int t) : time(-1), name(n), type(t) {}
};

class shelter {
	vector<animal> dogs;
	vector<animal> cats;
	int cur_time;
	public:
	shelter() : cur_time(0) {}
	void enqueue(const string &n, const int t) {
		enqueue(animal(n, t));
	}
	void enqueue(animal a) {
		a.time = cur_time ++;
		if(a.type == 0)
			dogs.push_back(a);
		else
			cats.push_back(a);
	}
	animal dequeueDog() {
		if(dogs.empty())
			return animal("error", -1);
		animal a = dogs[0];
		dogs.erase(dogs.begin());
		return a;
	}
	animal dequeueCat() {
		if(cats.empty())
			return animal("error", -1);
		animal a = cats[0];
		cats.erase(cats.begin());
		return a;
	}
	animal dequeueAny() {
		if(dogs.empty())
			return dequeueCat();
		if(cats.empty())
			return dequeueDog();

		if(dogs[0].time < cats[0].time)
			return dequeueDog();
		else
			return dequeueCat();
	}
};

int main(void) {

	shelter s;

	s.enqueue("dog1", 0);
	s.enqueue("cat1", 1);
	s.enqueue("cat2", 1);
	s.enqueue("dog2", 0);
	s.enqueue("dog3", 0);
	s.enqueue("cat3", 1);

	cout << s.dequeueAny().name << endl; // expected "dog1"
	cout << s.dequeueCat().name << endl; // expected "cat1"
	cout << s.dequeueDog().name << endl; // expected "dog2"
	cout << s.dequeueAny().name << endl; // expected "cat2"
	return 0;
}
