import random
from Graph import UndirectedGraph

def readGraphDefaultFormat(fileName):
    """
    Reads the graph in the initial, default format
    :param fileName: string containing the file name and extension (e.g.: input.txt)
    :return:
    """
    isFirstLine = True
    with open(fileName) as fileDescriptor:
        for line in fileDescriptor:
            values = line.split(' ')
            if isFirstLine:
                if len(values) != 2:
                    return False  # the format in the file does not match the default format
                else:
                    numberOfVertices = int(values[0])
                    numberOfEdges = int(values[1])
                    # add the vertices to the graph
                    for vertex in range(numberOfVertices):
                        graph.addVertex(vertex)
            else:
                startingVertex = int(values[0])
                endingVertex = int(values[1])
                costOfEdge = int(values[2])
                graph.addEdge(startingVertex, endingVertex)
            isFirstLine = False
    return True  # graph read successfully


def printMenu():
    print("1. Read graph from given textfile")
    print("2. Create random graph")
    print("3. SAVE connected components of graph to textfile")

def createRandomGraph(numberOfVertices, numberOfEdges):
    # add the vertices
    for vertex in range(numberOfVertices):
        graph.addVertex(vertex)
    # add random edges
    for edge in range(numberOfEdges):
        startVertex = random.randint(0, numberOfVertices - 1)
        endVertex = random.randint(0, numberOfVertices - 1)  # the vertices don't have to be distinct
        while graph.isEdge(startVertex, endVertex):
            # the randomised vertex already exists; generate a different one
            startVertex = random.randint(0, numberOfVertices - 1)
            endVertex = random.randint(0, numberOfVertices - 1)
        # at this moment, we have a valid pair of vertices; we now generate its cost
        costOfCurrentEdge = random.randint(-20, 20)
        # add the valid edge and its cost to the graph
        graph.addEdge(startVertex, endVertex)


if __name__ == '__main__':
    graph = UndirectedGraph()
    continueRun = True
    while continueRun:
        printMenu()
        option = int(input("Choose an option: \n"))
        if option == 0:
            continueRun = False
        elif option == 1:
            # read
        elif option ==2:
            # create random graph
            numberOfVertices = int(input("Enter number of vertices: "))
            # maximum numberOfEdges is n*(n-1)
            numberOfEdges = int(input("Enter number of edges: "))
            if 0 <= numberOfEdges <= (numberOfVertices * (numberOfVertices - 1)):
                createRandomGraph(numberOfVertices, numberOfEdges)
            else:
                with open("output.txt", 'w') as fileDescriptor:
                    fileDescriptor.write("Invalid number of edges!")
                print("Invalid number of edges!")
        elif option == 3:
            # connected components

