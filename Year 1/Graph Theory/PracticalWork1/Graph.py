import copy


class DirectedGraph:
    def __init__(self):
        # self.__numberOfVertices = 0
        # self.__numberOfEdges = 0

        # self.__allVerticesIds = {} //
        self.__graphIn = {}  # predecessors
        self.__graphOut = {}  # successors
        self.__graphCost = {}

    def isVertex(self, vertex: int):
        if vertex in self.__graphIn:    # search if it appears in the keys
            return True
        return False

    def addVertex(self, vertex):
        if self.isVertex(vertex) is False:
            self.__graphIn[vertex] = []
            self.__graphOut[vertex] = []
            return True
        return False

# the added vertex doesn't need to be between 0, n-1; it can be 99999999919398290 and should still work!

    def isEdge(self, startingVertex, endingVertex):
        # check that self.__graphIn[endingVertex] == startingVertex? ...if you want
        if self.isVertex(startingVertex) and self.isVertex(endingVertex):
            if endingVertex in self.__graphOut[startingVertex] and startingVertex in self.__graphIn[endingVertex]:
                return True
        return False

    def addEdge(self, startingVertex, endingVertex, costOfEdgeBetween):
        """
        Adds an edge from startingVertex to endingVertex.
        :param startingVertex:
        :param endingVertex:
        :return: True if adding was successful, False otherwise
        """
        # We have to check that the edge from startingVertex to endingVertex doesn't already exist
        if not self.isVertex(startingVertex) or not self.isVertex(endingVertex):
            return False
        if endingVertex in self.__graphOut[startingVertex]:  # Edge already exists
            return False
        self.__graphOut[startingVertex].append(endingVertex)
        self.__graphIn[endingVertex].append(startingVertex)
        self.__graphCost[(startingVertex, endingVertex)] = costOfEdgeBetween
        # graphCost is going to have as keys the tuple (startingVertex, endingVertex)
        return True

    def getNumberOfVertices(self):
        return len(self.__graphIn)

    def parseSetOfVertices(self):
        return list(self.__graphIn.keys())

    def getInDegreeOfGivenVertex(self, vertex: int):
        if self.isVertex(vertex):
            return len(self.__graphIn[vertex])

    def getOutDegreeOfGivenVertex(self, vertex: int):
        if self.isVertex(vertex):
            return len(self.__graphOut[vertex])

    def parseSetOfOutboundEdgesOfGivenVertex(self, vertex):
        if self.isVertex(vertex):
            return self.__graphOut[vertex]
    # this is a list

    def parseSetOfInboundEdgesOfGivenVertex(self, vertex):
        if self.isVertex(vertex):
            return self.__graphIn[vertex]

    def getCostOfGivenEdge(self, startingVertex, endingVertex):
        if self.isEdge(startingVertex, endingVertex):
            return self.__graphCost[(startingVertex, endingVertex)]

    def setCostOfGivenEdge(self, startingVertex, endingVertex, newCost):
        if self.isEdge(startingVertex, endingVertex):
            self.__graphCost[(startingVertex, endingVertex)] = newCost
            return True
        else:
            return False

    def removeEdge(self, startingVertex, endingVertex):
        if self.isEdge(startingVertex, endingVertex):
            self.__graphIn[endingVertex].remove(startingVertex)
            self.__graphOut[startingVertex].remove(endingVertex)
            del self.__graphCost[(startingVertex, endingVertex)]
            return True
        return False

    def removeVertex(self, vertex):
        if self.isVertex(vertex):  # if it exists, parse all outbound/inbound edges and remove them
            while len(self.__graphIn[vertex]) > 0:
                self.removeEdge(self.__graphIn[vertex][0], vertex)
            while len(self.__graphOut[vertex]) > 0:
                self.removeEdge(vertex, self.__graphOut[vertex][0])
            self.__graphIn.pop(vertex)
            self.__graphOut.pop(vertex)
            return True
        return False

    def copyGraph(self):
        return copy.deepcopy(self)

    def __str__(self):
        for startVertex in self.parseSetOfVertices():
            if len(self.parseSetOfOutboundEdgesOfGivenVertex(startVertex)) == 0:
                print(str(startVertex) + '\n')
            else:
                for endVertex in self.parseSetOfOutboundEdgesOfGivenVertex(startVertex):
                    # costOfCurrentEdge = graph.getCostOfGivenEdge(startVertex, endVertex)
                    print(str(startVertex) + ' ' + str(endVertex) + '\n')

