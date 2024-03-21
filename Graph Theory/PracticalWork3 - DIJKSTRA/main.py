import random

from Graph import DirectedGraph
from bfs import connected_components
from dijkstra import dijkstra
from dijkstra import printPath


def printMenu():
    print("\n============== MENU ==============")
    print("0. Exit")
    print("1. Get the number of vertices")
    print("2. Parse the set of vertices")
    print("3. Find out if edge exists between two given vertices")
    print("4. Get the IN degree and OUT degree of specified vertex")
    print("5. Parse the set of outbound edges of specified vertex")
    print("6. Parse the set of inbound edges of specified vertex")
    print("7. Get the cost associated to a specified edge")
    print("8. Set the cost associated to a specified edge")

    print("-------------- Modify Graph --------------")
    print("9. Add an edge.")
    print("10. Remove an edge.")
    print("11. Add a vertex.")
    print("12. Remove a vertex.")

    print("\n13. Make a copy of the graph")
    print("14. Read graph from given textfile (UNDIRECTED)")
    print("15. Read graph from given textfile (DIRECTED)")
    print("16. Write (SAVE) graph to a textfile")
    print("17. Create random graph")
    print("\n18. Display connected components")
    print("19. Dijkstra algorithm")


def readGraphDefaultFormat(fileName):
    """
    Reads the UNDIRECTED graph in the initial, default format
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
                graph.addEdge(startingVertex, endingVertex, costOfEdge)
                # Attention! Modified for Undirected Graphs:
                graph.addEdge(endingVertex, startingVertex, costOfEdge)
            isFirstLine = False
    return True  # graph read successfully


def readDirectedGraphDefaultFormat(fileName):
    """
    Reads the UNDIRECTED graph in the initial, default format
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
                graph.addEdge(startingVertex, endingVertex, costOfEdge)
            isFirstLine = False
    return True  # graph read successfully


def readGraphSecondaryFormat(fileName):
    with open(fileName) as fileDescriptor:  # opens into read mode by default
        for line in fileDescriptor:
            values = line.split(' ')
            if len(values) == 1:
                # we have an isolated vertex
                graph.addVertex(int(values[0]))
            elif len(values) == 3:
                # we have startingVertex, endingVertex, costOfEdge
                startingVertex = int(values[0])
                endingVertex = int(values[1])
                costOfEdge = int(values[2])
                graph.addVertex(startingVertex)
                graph.addVertex(endingVertex)
                graph.addEdge(startingVertex, endingVertex, costOfEdge)
                # Attention! Modified for Undirected Graphs:
                graph.addEdge(endingVertex, startingVertex, costOfEdge)
            else:
                return False  # the format in the file does not match the secondary format
    return True


def readDirectedGraphSecondaryFormat(fileName):
    with open(fileName) as fileDescriptor:  # opens into read mode by default
        for line in fileDescriptor:
            values = line.split(' ')
            if len(values) == 1:
                # we have an isolated vertex
                graph.addVertex(int(values[0]))
            elif len(values) == 3:
                # we have startingVertex, endingVertex, costOfEdge
                startingVertex = int(values[0])
                endingVertex = int(values[1])
                costOfEdge = int(values[2])
                graph.addVertex(startingVertex)
                graph.addVertex(endingVertex)
                graph.addEdge(startingVertex, endingVertex, costOfEdge)
            else:
                return False  # the format in the file does not match the secondary format
    return True


def writeGraphIntoFile(fileName):
    fileDescriptor = open(fileName, 'w')
    fileDescriptor.close()
    with open(fileName, 'a') as fileDescriptor:
        for startVertex in graph.parseSetOfVertices():
            if len(graph.parseSetOfOutboundEdgesOfGivenVertex(startVertex)) == 0:
                fileDescriptor.write(str(startVertex) + '\n')
            else:
                for endVertex in graph.parseSetOfOutboundEdgesOfGivenVertex(startVertex):
                    costOfCurrentEdge = graph.getCostOfGivenEdge(startVertex, endVertex)
                    fileDescriptor.write(str(startVertex) + ' ' + str(endVertex) + ' ' + str(costOfCurrentEdge) + '\n')


def writeGraphIntoEmptyFileForConnectedComponents(fileDescriptor, g):
    for startVertex in g.parseSetOfVertices():
        if len(g.parseSetOfOutboundEdgesOfGivenVertex(startVertex)) == 0:
            fileDescriptor.write(str(startVertex) + '\n')
        else:
            for endVertex in g.parseSetOfOutboundEdgesOfGivenVertex(startVertex):
                fileDescriptor.write(str(startVertex) + ' ' + str(endVertex) + '\n')


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
        # costOfCurrentEdge = random.randint(-20, 20)
        costOfCurrentEdge = random.randint(1, 20)  # non-negative for PW3
        # add the valid edge and its cost to the graph
        graph.addEdge(startVertex, endVertex, costOfCurrentEdge)


if __name__ == '__main__':
    # NOTE: we will assume all operations are done on the original graph; copies of the graph will not be modified
    # NOTE2: when reading from multiple text files one after another, the current graph gets bigger; read only once!
    graph = DirectedGraph()
    continueRun = True
    while continueRun is True:
        printMenu()
        option = int(input("Choose an option: \n"))
        if option == 0:
            continueRun = False
        elif option == 1:
            # get the nr of vertices
            print(graph.getNumberOfVertices())
        elif option == 2:
            # parse the set of vertices
            print(graph.parseSetOfVertices())
        elif option == 3:
            # find if edge exists between two given vertices
            startingVertex = int(input("Enter the starting vertex: "))
            endingVertex = int(input("Enter the ending vertex: "))
            print(graph.isEdge(startingVertex, endingVertex))
        elif option == 4:
            # get the IN and OUT degree of specified vertex
            givenVertex = int(input("Specify a vertex: "))
            print("IN degree: ", graph.getInDegreeOfGivenVertex(givenVertex))
            print("OUT degree: ", graph.getOutDegreeOfGivenVertex(givenVertex))
        elif option == 5:
            # parse the set of OUTBOUND edges of specified vertex
            givenVertex = int(input("Specify a vertex: "))
            print(graph.parseSetOfInboundEdgesOfGivenVertex(givenVertex))
        elif option == 6:
            # parse the set of INBOUND edges of specified vertex
            givenVertex = int(input("Specify a vertex: "))
            print(graph.parseSetOfOutboundEdgesOfGivenVertex(givenVertex))
        elif option == 7:
            # get cost of specified edge
            startingVertex = int(input("Enter the starting vertex: "))
            endingVertex = int(input("Enter the ending vertex: "))
            print(graph.getCostOfGivenEdge(startingVertex, endingVertex))
        elif option == 8:
            # set cost of specified edge
            startingVertex = int(input("Enter the starting vertex: "))
            endingVertex = int(input("Enter the ending vertex: "))
            newCost = int(input("Specify the new cost: "))
            if graph.setCostOfGivenEdge(startingVertex, endingVertex, newCost):
                print("Change was successful.")
            else:
                print("No such edge exists.")
        elif option == 9:
            # add edge
            startingVertex = int(input("Enter the starting vertex: "))
            endingVertex = int(input("Enter the ending vertex: "))
            costOfEdge = int(input("Enter the cost of the given edge: "))
            if graph.addEdge(startingVertex, endingVertex, costOfEdge):
                print("Edge added successfully.")
            else:
                print("Given vertices do not exist.")
        elif option == 10:
            # remove edge
            startingVertex = int(input("Enter the starting vertex: "))
            endingVertex = int(input("Enter the ending vertex: "))
            if graph.removeEdge(startingVertex, endingVertex) and graph.removeEdge(endingVertex, startingVertex):
                print("Edge removed successfully.")
            else:
                print("Given vertices do not exist.")
        elif option == 11:
            # add vertex
            givenVertex = int(input("Specify a vertex: "))
            if graph.addVertex(givenVertex):
                print("Vertex added successfully.")
            else:
                print("Given vertex already exists.")
        elif option == 12:
            # remove vertex
            givenVertex = int(input("Specify a vertex: "))
            if graph.removeVertex(givenVertex):
                print("Vertex removed successfully.")
            else:
                print("Given vertex does not exist.")
        elif option == 13:
            # make copy of graph
            copyOfOriginalGraph = graph.copyGraph()
        elif option == 14:
            # read graph from given textfile (UNDIRECTED)
            print("1. Default input.txt")
            print("2. Secondary input.txt")
            print("3. Graph1k (default)")
            print("4. Graph10k (default)")
            inputMode = int(input("Pick a file: "))
            if inputMode == 1:
                fileName = "input.txt"
            elif inputMode == 2:
                fileName = "secondary_input.txt"
            elif inputMode == 3:
                fileName = "graph1k.txt"
            elif inputMode == 4:
                fileName = "graph10k.txt"
            else:
                print("Invalid option")
                break
            if readGraphDefaultFormat(fileName) or readGraphSecondaryFormat(fileName):
                print("Graph read successfully")
            else:
                print("Graph read failed")
                break
        elif option == 15:
            # read graph from given textfile (DIRECTED)
            print("1. Default input.txt")
            print("2. Secondary input.txt")
            print("3. Graph1k (default)")
            print("4. Graph10k (default)")
            inputMode = int(input("Pick a file: "))
            if inputMode == 1:
                fileName = "input.txt"
            elif inputMode == 2:
                fileName = "secondary_input.txt"
            elif inputMode == 3:
                fileName = "graph1k.txt"
            elif inputMode == 4:
                fileName = "graph10k.txt"
            else:
                print("Invalid option")
                break
            if readDirectedGraphDefaultFormat(fileName) or readDirectedGraphSecondaryFormat(fileName):
                print("Graph read successfully")
            else:
                print("Graph read failed")
                break
        elif option == 16:
            # write graph to textfile (save to textfile)
            writeGraphIntoFile("output.txt")
        elif option == 17:
            # create random graph
            numberOfVertices = int(input("Enter number of vertices: "))
            # maximum numberOfEdges is n*(n-1)
            numberOfEdges = int(input("Enter number of edges: "))
            if 0 <= numberOfEdges <= (numberOfVertices * (numberOfVertices - 1)):  # directed graph
                    # numberOfVertices * (numberOfVertices - 1)) / 2:  # divided by 2 for undirected graph
                createRandomGraph(numberOfVertices, numberOfEdges)
            else:
                with open("output.txt", 'w') as fileDescriptor:
                    fileDescriptor.write("Invalid number of edges!")
                print("Invalid number of edges!")
        elif option == 18:
            filename = "output.txt"
            # Empty output file
            fd = open(filename, 'w')
            fd.close()
            # display connected components
            list = connected_components(graph)
            componentNumber = 0
            fileDescriptor = open(filename, 'a')
            for component in list:
                componentNumber = componentNumber + 1
                # Add component number
                fileDescriptor.write("Component: " + str(componentNumber) + "\n")
                writeGraphIntoEmptyFileForConnectedComponents(fileDescriptor, component)
            fileDescriptor.close()
        elif option == 19:
            startVertex = int(input("Enter the starting vertex: "))
            endVertex = int(input("Enter the ending vertex: "))
            #try:
            distances, prev = dijkstra(graph, startVertex)
            pathList = printPath(startVertex, endVertex, prev)
            if pathList == 1:
                print("There is no path between the two given vertices")
            else:
                print("path:")
                print(pathList)
                print("total cost: ", distances[endVertex])
                # print(distances)
                # print(prev)
            #except KeyError:
            #    print("There is no path between the two given vertices")

# Don't forget to check preconditions !!!
# save in file ONLY when we choose saveFile option!!!
# 2 points out of the 10 total to show manually the execution of your algorithm
# Put in the table the times at which it is convenient for you to present! 2 students at a time
# documentation, prepare graph files, paste the code and EXPLAIN IT! for the required operations
# 6 vertices and 40 edges - display error message
# remove vertex - do not parse all vertices; not efficient! Instead, work directly with the vertex as a key
# when modifying graph, it will lose the format; read with default format, save in second format, create read
# function for the second format
#
# you can identify the format by the file - first line has 2 vals => first

# Din           Dout
# 1 - [1,2]     1 - [3]
# 2 - []        2 - []
# 2 is an isolated vertex;
# format: startVertex endVertex Cost
#         isolatedVertex

# For remove edge, remove from both dictionaries + remove cost
# For remove vertex, BE CAREFUL
