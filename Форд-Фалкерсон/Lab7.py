import collections
 
# Этот класс представляет собой ориентированный граф с использованием представления матрицы смежности
class Graph:
  
    def __init__(self,graph):
        self.graph = graph  # residual graph
        self.ROW = len(graph)
  
    def BFS(self, s, t, parent):
        visited = [False] * (self.ROW)
        queue = collections.deque()
        queue.append(s)
        visited[s] = True       
        while queue:
            u = queue.popleft()
            for ind, val in enumerate(self.graph[u]):
                if (visited[ind] == False) and (val > 0):
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u
        return visited[t]
             
    def FordFulkerson(self, source, sink):
        parent = [-1] * (self.ROW)
        max_flow = 0 
        while self.BFS(source, sink, parent):
            path_flow = float("Inf")
            s = sink
            while s != source:
                path_flow = min(path_flow, self.graph[parent[s]][s])
                s = parent[s]
            max_flow += path_flow
            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]
 
        return max_flow


if __name__ == "__main__":
   
   adj_matrix = [[0, 16, 13, 0,  0, 0], 
                 [0, 0,  10, 12, 0, 0], 
                 [0, 4,  0,  0,  14,0], 
                 [0, 0,  9,  0,  0, 20], 
                 [0, 0,  0,  7,  0, 4], 
                 [0, 0,  0,  0,  0, 0]] 

   source = 0
   sink = 5
   graph = Graph(adj_matrix)
   max_flow = graph.FordFulkerson(source, sink) 
   print("Максимальная пропускная способность %d " % max_flow) 
   print();
 
  