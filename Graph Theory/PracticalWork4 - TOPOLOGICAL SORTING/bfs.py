import collections

from Graph import DirectedGraph

def accessible(g, s):
    """Returns the set of vertices of the graph g that are accessible
    from the vertex s"""
    accessibleVertices = set()
    accessibleVertices.add(s)
    list = [s]
    while len(list) > 0:
        x = list[0]
        list = list[1:]
        for y in g.parseSetOfOutboundEdgesOfGivenVertex(x):
            if y not in accessibleVertices:
                accessibleVertices.add(y)
                list.append(y)
    return accessibleVertices


def connected_components(g):
    remainingVertices = set(g.parseSetOfVertices())  # the vertices we still have to parse
    listOfConnectedComponents = []
    while len(remainingVertices) > 0:
        v = remainingVertices.pop()
        # Get the set of vertices accessible from vertex v
        acc = accessible(g, v)
        # Create an UndirectedGraph object for the connected component
        component = DirectedGraph()
        for u in acc:
            component.addVertex(u)
            for v in g.parseSetOfOutboundEdgesOfGivenVertex(u):
                if v in acc:
                    if not component.isEdge(u, v):
                        component.addEdge(u, v, 0)
                    if not component.isEdge(v, u):
                        component.addEdge(v, u, 0)
        for u in acc:
            if u in remainingVertices:
                remainingVertices.remove(u)
        listOfConnectedComponents.append(component)
    return listOfConnectedComponents

