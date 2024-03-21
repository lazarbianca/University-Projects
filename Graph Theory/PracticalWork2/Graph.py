import copy


class UndirectedGraph:
    def __init__(self):
        self.__graphOutbound = {}

    def isVertex(self, vertex: int):
        if vertex in self.__graphOutbound:  # search if vertex appears in the keys
            return True
        return False

    def addVertex(self, vertex):
        if self.isVertex(vertex) is False:
            self.__graphOutbound[vertex] = []
            return True
        return False

    def isEdge(self, startingVertex, endingVertex):
        if self.isVertex(startingVertex) and self.isVertex(endingVertex):
            return endingVertex in self.__graphOutbound[startingVertex]

    def addEdge(self, startingVertex, endingVertex):
        """
        Adds an edge between startingVertex and endingVertex. (Undirected => no orientation)
        :param startingVertex:
        :param endingVertex:
        :return: True if adding was successful, False otherwise
        """
        # Adds an edge from x to y. Return True on success, False if the edge already exists.
        # Precond: x and y exists
        # We have to check that the edge doesn't already exist
        if not self.isVertex(startingVertex) or not self.isVertex(endingVertex):
            return False
        if self.isEdge(startingVertex, endingVertex):
            return False
        self.__graphOutbound[startingVertex].append(endingVertex)
        return True

    def getNumberOfVertices(self):
        return len(self.__graphOutbound)

    def parseSetOfVertices(self):
        return list(self.__graphOutbound.keys())

    def getDegreeOfGivenVertex(self, vertex: int):
        if self.isVertex(vertex):
            return len(self.__graphOutbound[vertex])

    def parseSetOfEdgesOfGivenVertex(self, vertex):
        if self.isVertex(vertex):
            return list(self.__graphOutbound[vertex])

    def removeEdge(self, startingVertex, endingVertex):
        if self.isEdge(startingVertex, endingVertex):
            self.__graphOutbound[startingVertex].remove(endingVertex)
            return True
        return False

    def removeVertex(self, vertex):
        if self.isVertex(vertex):  # if it exists, parse all outbound edges and remove them
            while len(self.__graphOutbound[vertex]) > 0:
                self.removeEdge(vertex, self.__graphOutbound[vertex][0])
            self.__graphOutbound.pop(vertex)
            return True
        return False

    def copyGraph(self):
        return copy.deepcopy(self)
