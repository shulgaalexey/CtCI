// Build Order: You are given a list of projects and a list of dependencies (which is a list of pairs of
// projects, where the second project is dependent on the first project). All of a project's dependencies
// must be built before the project is. Find a build order that will allow the projects to be built. If there
// is no valid build order, return an error.
// EXAMPLE
// Input:
// projects: a, b, c, d, e, f
// dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
// Output: f, e, a, b, d, c
import java.util.*;

public class Task_4_7 {
	static class Graph {
		char data;
		List<Graph> children = new ArrayList<>();
		List<Graph> parents = new ArrayList<>();
		boolean visited;	// for the topological sort
		Graph(char data) {
			this.data = data;
		}
		@Override
		public String toString() {
			return "" + data;
		}
	}

	static class TaskDep {
		char dep;
		char task;
		TaskDep(char dep, char task) {
			this.dep = dep;
			this.task = task;
		}
		TaskDep(Graph dep, Graph task) {
			this.dep = dep.data;
			this.task = task.data;
		}
	}

	static boolean findLoop(Graph g) {
		if (g.parents.isEmpty()) {
			return false;
		}
		Deque<Graph> q = new LinkedList<>();
		for (Graph p: g.parents) {
			q.offer(p);
		}
		while (!q.isEmpty()) {
			Graph cur = q.poll();
			if (cur == g) {
				return true;
			}
			for (Graph p: cur.parents) {
				q.offer(p);
			}
		}
		return false;
	}

	static List<Graph> buildOrder(List<Graph> projects, List<TaskDep> dependencies) {
		Map<Character, Graph> index = new HashMap<>();
		for (Graph p: projects) {
			index.put(p.data, p);
		}

		for (TaskDep d: dependencies) {
			Graph task = index.get(d.task);
			Graph dep = index.get(d.dep);
			dep.children.add(task);
			task.parents.add(dep);
		}

		// Find loops, that will mean, that project cannot be done
		for (Graph p: projects) {
			if (findLoop(p)) {
				throw new IllegalStateException("ERROR");
			}
		}

		// Detect roots of the sub-projects
		List<Graph> order = new ArrayList<>();
		Deque<Graph> roots = new LinkedList<>();
		Set<Graph> visited = new HashSet<>();
		for (Graph p: projects) {
			if (p.parents.isEmpty()) {
				order.add(p);
				roots.offer(p);
				visited.add(p);
			}
		}

		// Create order starting from detected roots
		while (!roots.isEmpty()) {
			Graph root = roots.poll();
			for (Graph c: root.children) {
				if (!visited.contains(c)) {
					order.add(c);
					roots.offer(c);
					visited.add(c);
				}
			}
		}

		return order;
	}

	static void dfs(Graph g, List<Graph> track) {
		track.add(g);
		g.visited = true;
		for (Graph c: g.parents) {
			if (!c.visited) {
				dfs(c, track);
			}
		}
	}

	static List<Graph> topologicalSort(List<Graph> projects,
			List<TaskDep> dependencies) {
		Map<Character, Graph> index = new HashMap<>();
		for (Graph p: projects) {
			index.put(p.data, p);
		}

		for (TaskDep d: dependencies) {
			Graph task = index.get(d.task);
			Graph dep = index.get(d.dep);
			task.parents.add(dep);
		}

		List<Graph> order = new ArrayList<>();
		while (!projects.isEmpty()) {
			Graph p = projects.get(0);
			List<Graph> orderBuf = new ArrayList<>();
			dfs(p, orderBuf);
			Graph last = orderBuf.get(orderBuf.size() - 1);
			order.add(last);
			projects.remove(last);
		}
		return order;
	}

	public static void main(String args[]) {
		Graph a = new Graph('a');
		Graph b = new Graph('b');
		Graph c = new Graph('c');
		Graph d = new Graph('d');
		Graph e = new Graph('e');
		Graph f = new Graph('f');

		List<Graph> projects = new ArrayList<>();
		projects.add(a);
		projects.add(b);
		projects.add(c);
		projects.add(d);
		projects.add(e);
		projects.add(f);


		List<TaskDep> dependencies = new ArrayList<>();
		dependencies.add(new TaskDep(a, d));
		dependencies.add(new TaskDep(f, b));
		dependencies.add(new TaskDep(b, d));
		dependencies.add(new TaskDep(f, a));
		dependencies.add(new TaskDep(d, c));

		//List<Graph> order = buildOrder(projects, dependencies);
		List<Graph> order = topologicalSort(projects, dependencies);
		System.out.println(order);
	}
}
