class Graph:
    def __init__(self, directed=False, use_matrix=False):
        self.directed = directed
        self.use_matrix = use_matrix
        if use_matrix:
            self.adj_matrix = {}  # Dictionary of dictionaries for matrix representation
        else:
            self.adj_list = {}  # Dictionary for adjacency list
        self.nodes = set()

    def add_edge(self, u, v, weight=1):
        self.nodes.add(u)
        self.nodes.add(v)

        if self.use_matrix:
            if u not in self.adj_matrix:
                self.adj_matrix[u] = {}
            self.adj_matrix[u][v] = weight

            if not self.directed:
                if v not in self.adj_matrix:
                    self.adj_matrix[v] = {}
                self.adj_matrix[v][u] = weight

        else:
            if u not in self.adj_list:
                self.adj_list[u] = []
            self.adj_list[u].append((v, weight))

            if not self.directed:
                if v not in self.adj_list:
                    self.adj_list[v] = []
                self.adj_list[v].append((u, weight))

    def is_connected(self):
        if not self.nodes:
            return True  # Empty graph is considered connected

        start_node = next(iter(self.nodes))  # Choose any node as the starting point
        visited = set()
        self._dfs(start_node, visited)

        return len(visited) == len(self.nodes)

    def _dfs(self, node, visited):
        visited.add(node)
        if self.use_matrix:
            if node in self.adj_matrix:
                for neighbor in self.adj_matrix[node]:
                    if neighbor not in visited:
                        self._dfs(neighbor, visited)
        else:
            if node in self.adj_list:
                for neighbor, _ in self.adj_list[node]:
                    if neighbor not in visited:
                        self._dfs(neighbor, visited)

    def __str__(self):
        if self.use_matrix:
            result = "Adjacency Matrix:\n"
            for u in self.nodes:
                result += f"{u}: {self.adj_matrix.get(u, {})} \n"
            return result
        else:
            result = "Adjacency List:\n"
            for u in self.nodes:
                result += f"{u}: {self.adj_list.get(u, [])}\n"
            return result

# Example Usage (Adjacency List)
graph_list = Graph(directed=False, use_matrix=False)
graph_list.add_edge("Mumbai", "Delhi", 140)  # 140 minutes flight time
graph_list.add_edge("Delhi", "Bangalore", 180)
graph_list.add_edge("Bangalore", "Chennai", 60)
graph_list.add_edge("Chennai", "Mumbai", 100)
graph_list.add_edge("Kolkata","Delhi", 120)

print(graph_list)
print("Is graph connected (list):", graph_list.is_connected())

graph_list2 = Graph(directed=False, use_matrix=False)
graph_list2.add_edge("Mumbai", "Delhi", 140)
graph_list2.add_edge("Bangalore", "Chennai", 60)
print("Is graph connected (list):", graph_list2.is_connected())

# Example Usage (Adjacency Matrix)
graph_matrix = Graph(directed=False, use_matrix=True)
graph_matrix.add_edge("Mumbai", "Delhi", 140)
graph_matrix.add_edge("Delhi", "Bangalore", 180)
graph_matrix.add_edge("Bangalore", "Chennai", 60)
graph_matrix.add_edge("Chennai", "Mumbai", 100)
graph_matrix.add_edge("Kolkata","Delhi", 120)

print(graph_matrix)
print("Is graph connected (matrix):", graph_matrix.is_connected())

graph_matrix2 = Graph(directed=False, use_matrix=True)
graph_matrix2.add_edge("Mumbai", "Delhi", 140)
graph_matrix2.add_edge("Bangalore", "Chennai", 60)
print("Is graph connected (matrix):", graph_matrix2.is_connected())


