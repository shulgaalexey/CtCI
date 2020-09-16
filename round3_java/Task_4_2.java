// 4.2 Given a directed graph, design an algorithm to fid out
// whether there is a route between two nodes.
import java.util.*;

public class Task_4_2 {
	static class Node {
		char data;
		List<Node> children = new ArrayList<>();
		Node(char data) {
			this.data = data;
		}
		void addChildren(Node x) {
			children.add(x);
		}
		void addChildren(Node x, Node y) {
			children.add(x);
			children.add(y);
		}
		void addChildren(Node x, Node y, Node z) {
			children.add(x);
			children.add(y);
			children.add(z);
		}
	}

	/**
	 * BFS approach to check connection between two nodes
	 */
	static boolean isConnected(Node a, Node b) {
		Queue<Node> q = new LinkedList<>();
		q.add(a);

		while (!q.isEmpty()) {
			Node n = q.remove();
			if (n == b) {
				return true;
			}
			for (Node c: n.children) {
				q.add(c);
			}
		}
		return false;
	}

	public static void main(String args[]) {
		/*
		 * Connections are directed top-to-bottom and left-to-right
		 *
		 *   A <---> J  connected
		 *   C <---> I  connected
		 *   B <-/-> H  not connecterd
		 *
		 *       A
		 *     / | \
		 *    B  C  D
		 *    |  |  | \
		 *    E  F  G  H
		 *       \ /   |
		 *        J----I
		 */

		Node A = new Node('A');
		Node B = new Node('B');
		Node C = new Node('C');
		Node D = new Node('D');
		Node E = new Node('E');
		Node F = new Node('F');
		Node G = new Node('G');
		Node H = new Node('H');
		Node I = new Node('I');
		Node J = new Node('J');

		A.addChildren(B, C, D);
		B.addChildren(E);
		C.addChildren(F);
		D.addChildren(G, H);
		F.addChildren(J);
		G.addChildren(J);
		H.addChildren(I);
		J.addChildren(I);

		System.out.println(isConnected(A, J) == true);
		System.out.println(isConnected(C, I) == true);
		System.out.println(isConnected(B, H) == false);
	}
}
