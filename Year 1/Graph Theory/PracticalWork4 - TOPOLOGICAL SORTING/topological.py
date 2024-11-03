import math
from Graph import DirectedGraph
from queue import Queue


def topologicalSortPredecessorCounting(graph: DirectedGraph):
    sortedList = []  # for storing the vertices in topological order
    queue = Queue()
    # queue = []
    predecessorsDict = {}  # for storing the nr of predecessors of each vertex
    for vertex in graph.parseSetOfVertices():
        predecessorsDict[vertex] = graph.getInDegreeOfGivenVertex(vertex)
        if predecessorsDict[vertex] == 0:
            queue.put(vertex)  #priority_queue.add(vertex, dictionary_with_the_number_of_predecessors[vertex])
            # queue.append(vertex)

    while not queue.empty():
        vertexWithLeastPredecessors = queue.get()
        # vertexWithLeastPredecessors = queue[0]
        # queue[1:]
        sortedList.append(vertexWithLeastPredecessors)
        for destination in graph.parseSetOfOutboundEdgesOfGivenVertex(vertexWithLeastPredecessors):
            predecessorsDict[destination] -= 1
            if predecessorsDict[destination] == 0:
                queue.put(destination)
                # queue.append(destination)

    if len(sortedList) < graph.getNumberOfVertices():
        return None
    return sortedList


def highestCostPath(graph:DirectedGraph, sortedList, startVertex, endVertex):
    highestCostDict = {vertex: -math.inf for vertex in graph.parseSetOfVertices()}
    # will keep track of the highest cost discovered for each vertex
    highestCostDict[startVertex] = 0
    previousVertexDict = {startVertex: -1}
    # will store the previous vertex on the path
    i = 0
    while i < len(sortedList) and sortedList[i] != startVertex:
        i += 1
    while i < len(sortedList) and sortedList[i] != endVertex:
        vertex = sortedList[i]
        for destination in graph.parseSetOfOutboundEdgesOfGivenVertex(vertex):
            new_cost = highestCostDict[vertex] + graph.getCostOfGivenEdge(vertex, destination)
            if new_cost > highestCostDict[destination]:
                highestCostDict[destination] = new_cost
                previousVertexDict[destination] = vertex
        i += 1
    return previousVertexDict, highestCostDict[endVertex]


def printPathPredecessors(currentVertex, startVertex, endVertex, predecessorsDict: dict):
    if startVertex == endVertex:
        print(startVertex)
        return
    if currentVertex == -1:
        return
    else:
        try:  # Or, if no path is found, highest cost path will be -inf
            printPathPredecessors(predecessorsDict[currentVertex], startVertex, endVertex, predecessorsDict)
        except(KeyError):
            print("No path found")
            return
        if currentVertex == endVertex:
            print(currentVertex)
        else:
            print(currentVertex, end=" -> ")
