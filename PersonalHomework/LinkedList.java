import java.util.*;
import java.io.*;

// node class
class Node
{
	int data;
	Node next;

	Node()
	{}

	Node(int data)
	{
		this.data = data;
	}

	Node(int data, Node next)
	{
		this.data = data;
		this.next = next;
	}
}

public class LinkedList
{
	static Node head;

	// creates the first instance of the linked list
	public LinkedList()
	{
		head = new Node();
	}

	// print the linked list
	public static void printList()
	{
		Node currNode = head;

		while (currNode != null)
		{
			System.out.print(currNode.data + " ");
			currNode = currNode.next;
		}

		System.out.println("");
	}

	// insert into the linked list
	public static void add(int data)
	{
		Node currNode = head;
		Node newNode;

		// we ask this first because we do not want our first number to be a 0
		// when we did not input a 0
		if (currNode.data == 0)
		{
			newNode = new Node(data);
			head = newNode;
		}

		else 
		{
			while (currNode.next != null)
				currNode = currNode.next;

			newNode = new Node(data);
			currNode.next = newNode;
		}
	}

	// reverse the linked list
	public static Node reverse(Node head)
	{
		Node currNode = head;
		Node reverse = null;

		while (currNode != null)
		{
			Node next = currNode.next;
			currNode.next = reverse;
			reverse = currNode;
			currNode = next;
		}

		return reverse;
	}

	public static void main(String[] args)
	{
		LinkedList list = new LinkedList();

		list.add(1);
		list.add(2);
		list.add(3);
		list.add(4);

		System.out.print("Normal LinkedList: ");
		list.printList();

		head = list.reverse(head);

		System.out.print("Reversed LinkedList: ");
		list.printList();
	}
}
