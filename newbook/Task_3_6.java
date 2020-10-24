// Animal Shelter: An animal shelter, which holds only dogs and cats, operates on a strictly"first in, first
// out" basis. People must adopt either the "oldest" (based on arrival time) of all animals at the shelter,
// or they can select whether they would prefer a dog or a cat (and will receive the oldest animal of
// that type). They cannot select which specific animal they would like. Create the data structures to
// maintain this system and implement operations such as enqueue, dequeueAny, dequeueDog,
// and dequeueCat. You may use the built-in Linked list data structure.
import java.util.*;

public class Task_3_6 {
	static class MyPair {
		String s;
		int n;
		MyPair(String s, int n) {
			this.s = s;
			this.n = n;
		}

		@Override
		public String toString() {
			return s + ":" + n;
		}
	}

	static class AnimalShelter {
		private List<MyPair> cats = new LinkedList<>();
		private List<MyPair> dogs = new LinkedList<>();
		private int time = 0;

		void enqueue(String name, boolean isCat) {
			if (isCat) {
				cats.add(new MyPair(name, time++));
			} else {
				dogs.add(new MyPair(name, time++));
			}
		}

		String dequeueAny() {
			if (dogs.isEmpty()) {
				return dequeueCat();
			}
			if (cats.isEmpty()) {
				return dequeueDog();
			}
			if (dogs.get(0).n < cats.get(0).n) {
				return dequeueDog();
			} else {
				return dequeueCat();
			}
		}

		String dequeueDog() {
			final String name = dogs.get(0).s;
			dogs.remove(0);
			return name;
		}

		String dequeueCat() {
			final String name = cats.get(0).s;
			cats.remove(0);
			return name;
		}
		void dbgTrace() {
			System.out.println(cats);
			System.out.println(dogs);
		}
	}

	public static void main(String args[]) {
		AnimalShelter s = new AnimalShelter();

		s.enqueue("Kat", true);
		s.enqueue("Doggo", false);
		s.enqueue("Kitty", true);
		s.enqueue("Mur", true);
		s.enqueue("Gav", false);

		s.dbgTrace();

		System.out.println(s.dequeueAny() == "Kat");
		System.out.println(s.dequeueCat() == "Kitty");
		System.out.println(s.dequeueDog() == "Doggo");
		System.out.println(s.dequeueAny() == "Mur");
	}
}
