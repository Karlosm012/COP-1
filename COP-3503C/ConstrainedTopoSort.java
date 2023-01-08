// Karlos Morales Ramos, ka649665
// COP 3503C, Fall 2022
// ConstrainedTopoSort project

import java.util.*;
import java.io.*;

public class ConstrainedTopoSort
{
	boolean[][] matrix;
	int vertices;
	int edges;

	// We create a matrix based on the input file 
	public ConstrainedTopoSort(String filename) throws IOException
	{
		// Create the scanner and store the first number indicating
		// the number of vertices we are going to use
		Scanner scanner = new Scanner(new File(filename));
		vertices = scanner.nextInt();
		
		// Initiate the matrix with boolean. 
		matrix = new boolean[vertices][vertices];

		// Stores what is connected to what
		for (int i = 0; i < vertices; i++)
		{
			// this number will indicate how many edges we are going 
			// to have
			edges = scanner.nextInt();

			// based on the graph: 1 is true at 3; 2 is true at 3 and 4;
			// and 3 is true at 4; indicating the digraph
			for (int j = 0; j < edges; j++)
				matrix[i][scanner.nextInt() - 1] = true;
		}
	}

	// Check if the graph has a valid topo sort (no cycles). Dr. Szumlanski
	// webcourse page.
	public boolean isValidTopoSort()
	{
		int[] inDegree = new int[vertices];
		int numInDegree = 0;

		// counts the number of incoming edges to each vertex
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				if (matrix[i][j] == true)
					inDegree[j] += 1;
				else 
					inDegree[j] += 0;

		Queue<Integer> q = new ArrayDeque<Integer>();

		// any vertex with zero incoming edges is ready to be visited,
		// add it to the queue
		for (int i = 0; i < vertices; i++)
			if (inDegree[i] == 0)
				q.add(i);


		while (!q.isEmpty())
		{
			int curr = q.remove();
			numInDegree++;

			// all vertices we can reach via an edge from the current vertex should
			// have their incoming edges counts decrement. If one of these hits zero,
			// add it to queue
			for (int i = 0; i < vertices; i++)
				if (matrix[curr][i] && --inDegree[i] == 0)
					q.add(i);
		}

		// checks to see if we have a graph
		if (numInDegree != vertices)
			return false;

		return true;

	}

	// Check if the matrix starting at vertex x before vertex
	// y is a valid toposort
	public boolean hasConstrainedTopoSort(int x, int y)
	{
		if(!isValidTopoSort())
			return false;

		// Utilize a hash set to store quickly the integer values that we have
		// already checked for
		HashSet<Integer> visited = new HashSet<Integer>();

		// Standard topological queue taught in class by Dr. Szumlanski
		Queue<Integer> q = new ArrayDeque<Integer>();

		// add our x value into the queue and to our visited set adjusting it to the
		// values of our indexes.
		q.add(x - 1);
		visited.add(x - 1);

		// while the q is not empty; BFS traversal utilizing hash set instead
		// of the boolean array
		while (!q.isEmpty())
		{	
			// place the value stored in the q onto our current variable for use
			int curr = q.remove();

			// This is the important part of the code. After setting up the matrix, we want
			// to check if values with y at x and curr(x) at y are true based on the matrix.
			// If what is at the matrix is true than we return false
			if (matrix[y - 1][curr])
				return false;

			for (int i = 0; i < vertices; i++)

				// adds our new values into our queue and our visited hash 
				// set if matrix holds true and the value is still valid
				if (matrix[i][curr] && !visited.contains(i))
				{
					q.add(i);
					visited.add(i);
				}
		}

		return true;
	}


	// ----------------- Project Methods -----------------
	public static double difficultyRating()
	{
		return 3.0;
	}

	public static double hoursSpent()
	{
		return 9.0;
	}
}
