// Different graph traversal approaches
import java.util.*;

public class GraphTraverse {
	static List<MyNode> pull = new ArrayList<>();

	static class MyNode {
		char data;
		boolean visited;
		List<MyNode> children = new ArrayList<>();
		MyNode(char data) {
			this.data = data;
			pull.add(this);
		}
		void addChildren(MyNode n1) {
			children.add(n1);
		}
		void addChildren(MyNode n1, MyNode n2) {
			children.add(n1);
			children.add(n2);
		}
		void addChildren(MyNode n1, MyNode n2, MyNode n3) {
			children.add(n1);
			children.add(n2);
			children.add(n3);
		}
	}


	static void bfs(MyNode graph) {
		Queue<MyNode> q = new LinkedList<>();
		q.offer(graph);
		graph.visited = true;
		while (!q.isEmpty()) {
			MyNode node = q.poll();
			System.out.println(node.data);
			for (MyNode child: node.children) {
				if (!child.visited) {
					q.offer(child);
					child.visited = true;
				}
			}
		}
	}

	static void dfs(MyNode graph) {
		System.out.println(graph.data);
		graph.visited = true;
		for (MyNode n: graph.children) {
			if (!n.visited) {
				dfs(n);
			}
		}
	}

	/*
	 *      a-----
	 *     / \    \
	 *    b   c    d---i
	 *    |   |   / \
	 *    e---f  g   h
	 *    \         /
	 *     j-------/
	 *
	 */
	public static void main(String args[]) {
		MyNode a = new MyNode('a');
		MyNode b = new MyNode('b');
		MyNode c = new MyNode('c');
		MyNode d = new MyNode('d');
		MyNode e = new MyNode('e');
		MyNode f = new MyNode('f');
		MyNode g = new MyNode('g');
		MyNode h = new MyNode('h');
		MyNode i = new MyNode('i');
		MyNode j = new MyNode('j');

		a.addChildren(b, c, d);
		b.addChildren(b);
		c.addChildren(f);
		d.addChildren(i, h, g);
		e.addChildren(j, f);
		f.addChildren(c, e);
		g.addChildren(d);
		h.addChildren(h, j);
		//i.addChildren(); no children
		j.addChildren(h);

		bfs(a);

		// Reset node pull
		System.out.println("reset pull");
		for (MyNode n: pull) {
			n.visited = false;
		}

		dfs(a);
	}
}
