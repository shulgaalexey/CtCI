// Route Between Nodes: Given a directed graph, design an algorithm to find out whether there is a
// route between two nodes.
import java.util.*;

public class Task_4_1 {
	static class Graph {
		private char data;
		List<Graph> children = new ArrayList<>();
		Graph(char data) {
			this.data = data;
		}
	}

	static boolean isRoute(Graph n1, Graph n2) {
		Set<Graph> visited = new HashSet<>();
		Deque<Graph> q = new LinkedList<>();
		q.offer(n1);
		visited.add(n1);
		while (!q.isEmpty()) {
			Graph g = q.poll();
			if (g == n2) {
				return true;
			}
			for (Graph c: g.children) {
				if (!visited.contains(c)) {
					visited.add(c);
					q.offer(c);
				}
			}
		}
		return false;
	}

	public static void main(String args[]) {
		Graph a = new Graph('a');
		Graph b = new Graph('b');
		Graph c = new Graph('c');
		Graph d = new Graph('d');
		Graph e = new Graph('e');

		a.children.add(b);
		b.children.add(d);
		c.children.add(a);
		c.children.add(b);
		c.children.add(e);
		d.children.add(c);
		e.children.add(e);

		System.out.println(isRoute(a, e) == true);
		System.out.println(isRoute(b, e) == true);
		System.out.println(isRoute(b, a) == true);
		System.out.println(isRoute(e, a) == false);
	}
}
