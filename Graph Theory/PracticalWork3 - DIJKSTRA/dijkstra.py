from Graph import DirectedGraph


class PriorityQueue:
    def __init__(self):
        self.__values = {}

    def isEmpty(self):
        return len(self.__values) == 0

    def pop(self):
        topPriority = None
        topObject = None
        for obj in self.__values:
            objPriority = self.__values[obj]
            if topPriority is None or topPriority > objPriority:
                topPriority = objPriority
                topObject = obj
        del self.__values[topObject]
        return topObject

    def add(self, obj, priority):
        self.__values[obj] = priority

    def contains(self, val):
        return val in self.__values


def dijkstra(g: DirectedGraph, startingVertex):
    prev = {}  # for every key vertex, the previous vertex (from which we arrived)
    queue = PriorityQueue()  # store vertices with their corresponding distance from the starting vertex
    # we use a PriorityQueue so that at every pop, the element with the top priority (the lowest cost)
    queue.add(startingVertex, 0)  # shortest distance from s to s is 0
    distanceFromStartingVertexTo = {}  # stores the shortest distances from the startVertex to each of the other
                                       # vertices
    distanceFromStartingVertexTo[startingVertex] = 0
    visitedVertices = set()
    visitedVertices.add(startingVertex)
    # printDijkstraStep(startingVertex, None, queue, d, prev)
    while not queue.isEmpty():
        x = queue.pop()
        for y in g.parseSetOfOutboundEdgesOfGivenVertex(x):
            if y not in visitedVertices or distanceFromStartingVertexTo[y] > distanceFromStartingVertexTo[x]\
                    + g.getCostOfGivenEdge(x, y):
                distanceFromStartingVertexTo[y] = distanceFromStartingVertexTo[x] + g.getCostOfGivenEdge(x, y)
                visitedVertices.add(y)
                queue.add(y, distanceFromStartingVertexTo[y])
                prev[y] = x
        # printDijkstraStep(startingVertex, x, queue, distanceFromStartingVertexTo, prev)
    return distanceFromStartingVertexTo, prev


def printPath(startingVertex, endingVertex, prev):
    list = []
    if endingVertex not in prev.keys():
        print("There is no path between given vertices")
        return 1
    list.append(endingVertex)  # starting from the last vertex, we will build the path backwards
    current = prev[endingVertex]
    while current != startingVertex:
        list.append(current)
        nextVertex = prev[current]
        current = nextVertex
    list.append(current)
    list.reverse()  # reverse the list in the end for readability
    return list

# def getChildren(x, prev):
#     list = []
#     for i in prev:
#         if prev[i] == x:
#             list.append(i)
#     return list
#
#
# def printDijkstraTree(s, q, d, prev, indent):
#     if q.contains(s):
#         star = ''
#     else:
#         star = '*'
#     print("%s%s [%s]%s" % (indent, s, d[s], star))
#     for x in getChildren(s, prev):
#         printDijkstraTree(x, q, d, prev, indent + '    ')
#
#
# def printDijkstraStep(s, x, q, d, prev):
#     print('----')
#     if x is not None:
#         print('x=%s [%s]' % (x, d[x]))
#     printDijkstraTree(s, q, d, prev, '')
