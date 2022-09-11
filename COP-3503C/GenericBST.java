// Sean Szumlanski, Karlos Morales Ramos ka649665
// COP 3503, Fall 2022
// 9/11/22

// ====================
// GenericBST: BST.java
// ====================
// Basic binary search tree (BST) implementation that supports insert() and
// delete() operations. This framework is provided for you to modify as part of
// Programming Assignment #2.


import java.io.*;
import java.util.*;

class Node<AnyType>
{
	AnyType data;
	Node<AnyType> left, right;

	Node(AnyType data)
	{
		this.data = data;
	}
}

public class GenericBST<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> root;

	// wrapper method for insert
	public void insert(AnyType data)
	{
		root = insert(root, data);
	}

	// inserts the new data/node into the tree
	private Node<AnyType> insert(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return new Node<AnyType>(data);
		}

		// utilize compareTo to check if data is lower than what is already
		// in the root and enter the left side
		else if (data.compareTo(root.data) < 0)
		{
			root.left = insert(root.left, data);
		}

		// check if data is greater than what is already in the root
		// and enter the right side
		else if (data.compareTo(root.data) > 0)
		{
			root.right = insert(root.right, data);
		}

		return root;
	}

	// wrapper method for delete
	public void delete(AnyType data)
	{
		root = delete(root, data);
	}

	// recursively goes through the tree to find data and delete it
	private Node<AnyType> delete(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return null;
		}
		else if (data.compareTo(root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = delete(root.right, data);
		}
		else
		{
			if (root.left == null && root.right == null)
			{
				return null;
			}
			else if (root.left == null)
			{
				return root.right;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is not empty.
	private AnyType findMax(Node<AnyType> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	// wrapper method for contains
	public boolean contains(AnyType data)
	{
		return contains(root, data);
	}

	// checks if the tree contains the data we are looking for
	private boolean contains(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return false;
		}
		else if (data.compareTo(root.data) < 0)
		{
			return contains(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			return contains(root.right, data);
		}
		else
		{
			return true;
		}
	}

	// wrapper method for inorder
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	// inorder prints out data: left, root, right
	private void inorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// wrapper method for preorder
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	// preorder prints out data: root, left, right
	private void preorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// wrapper method for postorder
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	// postorder prints out data: left, right, root
	private void postorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

	// difficulty rating of the project
	public static double difficultyRating()
	{
		return 1.0;
	}

	// hours spent on the project
	public static double hoursSpent()
	{
		return 1.0;
	}
}
