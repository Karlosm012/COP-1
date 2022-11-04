// Karlos Morales Ramos, ka649665
// COP 3503C, Fall 2022
// SkipList project

import java.util.*;
import java.io.*;
import java.lang.*;

class Node<AnyType extends Comparable<AnyType>>
{
	private ArrayList<Node<AnyType>> node;
	private AnyType data;

	// creates a node with data set to null and all other nodes also set to null
	Node(int height)
	{
		data = null;
		node = new ArrayList<Node<AnyType>>(height);

		for (int i = 0; i < height; i++)
			node.add(null);
	}

	// creates a node with an actual value and all other nodes to null
	Node(AnyType data, int height)
	{
		this.data = data;
		node = new ArrayList<Node<AnyType>>(height);

		for (int i = 0; i < height; i++)
			node.add(null);
	}

	// returns the data that we are putting on the node
	public AnyType value()
	{
		return data;
	}

	// returns the height of this node, we use size so we can easily get how long (height) the
	// arraylist node is
	public int height()
	{
		return node.size();
	}

	// if level is less than zero or greater than height, we return null
	public Node<AnyType> next(int level)
	{
		if (level < 0 || level > height() - 1)
			return null;

		return node.get(level);
	}

	// ----------------- Suggested Methods -----------------

	// sets the next reference at level to node
	public void setNext(int level, Node<AnyType> node)
	{
		this.node.set(level, node);
	}

	// adds 1 to height
	public void grow()
	{
		node.add(null);
	}

	// there is a 50% chance to grow the height
	public boolean maybeGrow()
	{
		if (Math.round(Math.random()) == 1)
		{
			grow();
			return true;
		}

		return false;
	}

	// removes the node at height
	public void trim(int height)
	{
		node.remove(height);
	}
}

public class SkipList<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> head;
	private int numNodes = 0;
	private int defHeight = 1;

	// creates a new node called head with the default height
	SkipList()
	{
		head = new Node<AnyType>(defHeight);
	}

	// creates a new node called head with default if the height is lower than 1
	// else we give it the input height
	SkipList(int height)
	{
		if (height < defHeight)
			head = new Node<AnyType>(defHeight);

		else
			head = new Node<AnyType>(height);
	}

	// returns how many nodes are in the skip list
	public int size()
	{
		return numNodes;
	}

	// returns the height of the head
	public int height()
	{
		return head.height();
	}

	// returns the head
	public Node<AnyType> head()
	{
		return head;
	}

	// calls getMaxHeight to create a reference to the max height a node can get
	// depending on how many nodes there are in the skiplist. Afterwards
	// it will generate a random height based on the coinflip.
	// Then it will call insert with the data and the new height.
	public void insert(AnyType data)
	{
		insert(data, generateRandomHeight(getMaxHeight(numNodes + 1)));
	}

	// here we do all the work for counting the nodes that are inserted into the skiplist.
	public void insert(AnyType data, int height)
	{
		numNodes++;

		// if the insert exceeds the skip list's current height, we must grow the skip list
		growSkipList();

		int currLevel = height() - 1;

		// creates a new node for the insert, currnode set to head, and nextnode set to
		// head.next
		Node<AnyType> newNode = new Node<AnyType>(data, height);
		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(currLevel);

		// while we haven't fallen off the node
		while (currLevel >= 0)
		{
			// while the nextnode is not null, we check if the new value is greater than 
			// that of the next node's
			while (nextNode != null && newNode.value().compareTo(nextNode.value()) == 1)
			{
				// move on to the next node
				currNode = nextNode;
				nextNode = currNode.next(currLevel);
			}

			// places the new node in the middle of currNode and nextNode
			if (currLevel <= height - 1)
			{
				// new node at current level is going to have a reference to next node
				newNode.setNext(currLevel, nextNode);

				// current node at current level is going to have a reference to new node
				currNode.setNext(currLevel, newNode);
			}

			// lower the level and continue the skipList
			currLevel--;
			nextNode = currNode.next(currLevel);
		}
	}

	public void delete(AnyType data)
	{
		int currLevel = height() - 1;
		int nodeHeight = 0;

		// we only need to use two node references to delete
		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(currLevel);

		// we need to store the references that the node to be deleted has to be able to
		// connect them once deleted
		ArrayList<Node<AnyType>> refToNode = new ArrayList<Node<AnyType>>();
		ArrayList<Node<AnyType>> refFromNode = new ArrayList<Node<AnyType>>();

		// while we haven't fallen off the node
		while (currLevel >= 0)
		{	
			// while next node is not null and data is greater than nextNode value
			while (nextNode != null && data.compareTo(nextNode.value()) == 1)
			{
				// we continue through the Skiplist
				currNode = nextNode;
				nextNode = currNode.next(currLevel);
			}

			// if data equals to the value of the nextNode
			if (nextNode != null && data.compareTo(nextNode.value()) == 0)
			{
				// stores the ref of the currnode to the deleted node.
				// ref added will push ref that is already inside to the right.
				refToNode.add(0, currNode);

				// stores the ref of the deleted node to the next node
				refFromNode.add(0, nextNode.next(currLevel));

				// if we are about to fall off, the node is deleted fully
				if (currLevel == 0)
				{	
					// store the height of the node we are deleting
					nodeHeight = nextNode.height();

					for (int i = 0; i < nodeHeight; i++)
					{	
						// set the ref from before the deleted node to the node
						// after the deleted node depending on how we saved it in
						// the arraylists
						refToNode.get(i).setNext(i, refFromNode.get(i));
					}
					// we decrease the number of nodes and trim the skip list if necessary
					numNodes--;

					while (height() > getMaxHeight(numNodes))
						trimSkipList();
				}
			}

			// lower the level and continue the skipList
			currLevel--;
			nextNode = currNode.next(currLevel);
		}
	}

	public boolean contains(AnyType data)
	{
		int currLevel = height() - 1;

		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(currLevel);

		while (currLevel >= 0)
		{
			// while data is greater than nextNode value, we continue the skipList
			while (nextNode != null && data.compareTo(nextNode.value()) == 1)
			{
				currNode = nextNode;
				nextNode = currNode.next(currLevel);
			}

			// if the data equals to nextNode value, we return true
			if (nextNode != null && data.compareTo(nextNode.value()) == 0 && currLevel == 0)
				return true;

			// go down a level and continue the skipList
			currLevel--;
			nextNode = currNode.next(currLevel);
		}

		return false;
	}

	public Node<AnyType> get(AnyType data)
	{
		int currLevel = height() - 1;

		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(currLevel);

		while (currLevel >= 0)
		{
			while (nextNode != null && data.compareTo(nextNode.value()) == 1)
			{
				currNode = nextNode;
				nextNode = currNode.next(currLevel);
			}

			// if data equals nextNode value we return the nextNode
			if (nextNode != null && data.compareTo(nextNode.value()) == 0 && currLevel == 0)
				return currNode.next(currLevel);

			currLevel--;
			nextNode = currNode.next(currLevel);
		}

		return null;
	}

	// ----------------- Suggested Methods -----------------

	// Gets the maximum height of a node based on how many nodes the skip list contains.
	private int getMaxHeight(int n)
	{	
		int maxHeight = (int)Math.ceil(Math.log(n) / Math.log(2));

		// if n is less than or equal to 2, we return 1
		if (n <= 2)
			return 1;

		return maxHeight;
	}

	// Generates a random height based on coinflip. If we get heads, we continue
	// adding to height. Tails, we stop and return the height.
	private int generateRandomHeight(int maxHeight)
	{
		int height = 1;

		while (height < maxHeight && Math.round(Math.random()) == 1)
			height++;

		return height;
	}

	// the nodes that will increment are the nodes were maxed out last time
	private void growSkipList()
	{
		// we get the new max height of the node
		int maxHeight = getMaxHeight(numNodes);

		// if height is equal or greater than maxHeight
		// we do not need to grow
		if (height() >= maxHeight)
			return;

		// we get variables for the new level (maxHeight) and for old level
		int newLevel = maxHeight - 1;
		int oldLevel = newLevel - 1;
		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(oldLevel);

		// we have head grow to the max height
		head().grow();

		while (nextNode != null)
		{
			// we call maybe grow for a 50% chance of growing the node
			if (nextNode.maybeGrow())
			{
				// we set the head to refer to the new level of the next node
				currNode.setNext(newLevel, nextNode);
				currNode = nextNode;
			}

			// nextNode will not be the next node at old level for possible growth
			nextNode = nextNode.next(oldLevel);
		}
	}

	// we are trimming the node to a new level
	private void trimSkipList()
	{	
		int maxHeight = getMaxHeight(numNodes);

		if (height() <= maxHeight)
			return;

		int oldLevel = height() - 1;
		Node<AnyType> currNode = head();
		Node<AnyType> nextNode = currNode.next(oldLevel);

		// while nextNode is not null
		while (nextNode != null)
		{
			// current node will be next node
			currNode = nextNode;

			// nextNode will be next node
			nextNode = nextNode.next(oldLevel);

			// we remove current and continue with the other nodes after
			currNode.trim(oldLevel);
		}

		// we go back to head and trim it
		head().trim(oldLevel);
	}

	// ----------------- Project Methods -----------------
	public static double difficultyRating()
	{
		return 5.0;
	}

	public static double hoursSpent()
	{
		return 24.0;
	}
}
