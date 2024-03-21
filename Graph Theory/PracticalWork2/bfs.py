from Graph import UndirectedGraph


def bfs(g, s, t=None):
    '''Performs a Breadth-First Search in graph g starting from vertex s.
    The search will stop if vertex t is reached. If t is None, the processing
    won't stop until all accessible vertices are processed.
    Returns a tuple where:
      - the first element is a dictionary where the key are the accessible vertices and,
        for each vertex, the value is the parent in the BFS tree. For s, the value
        will be None
      - the second is a dictionary where the keys are the accessible vertices and
        for each vertex, the value is the list of children
      - the third is a dictionary where the keys are the accessible vertices and
        for each vertex, the value is the distance (as int) from s to that vertex.
    '''
    parent = {s: None}
    children = {s: []}
    dist = {s: 0}
    queue = [s]
    while len(queue) != 0:
        current_vertex = queue.pop(0)
        if current_vertex == t:
            break
        for next in g.parseNOut(current_vertex):
            if next not in parent.keys():
                parent[next] = current_vertex
                children[next] = []
                children[current_vertex].append(next)
                dist[next] = dist[current_vertex] + 1
                queue.append(next)
        # print(current_vertex, parent, children, dist)
    return (parent, children, dist)


def accessible(g, s):
    """Returns the set of vertices of the graph g that are accessible
    from the vertex s"""
    accessibleVertices = set()
    accessibleVertices.add(s)
    list = [s]
    while len(list) > 0:
        x = list[0]
        list = list[1:]
        for y in g.parseSetOfEdgesOfGivenVertex(x):
            if y not in accessibleVertices:
                accessibleVertices.add(y)
                list.append(y)
    return accessibleVertices


def connected_components(g):
    remaining = set(g.parseSetOfVertices())
    components = []
    while len(remaining) > 0:
        v = remaining.pop()
        acc = accessible(g, v)
        # Create an UndirectedGraph object for the connected component
        component = UndirectedGraph()
        for u in acc:
            component.addVertex(u)
            for v in g.parseSetOfEdgesOfGivenVertex(u):
                if v in acc:
                    component.addEdge(u, v)
        for u in acc:
            if u in remaining:
                remaining.remove(u)
        components.append(component)
    return components

