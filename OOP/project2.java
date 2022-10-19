package main1;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.*;
import java.text.SimpleDateFormat;


/*
 * Project 2
 * Jessica Garcia-Velez, Clarice Elso, Karlos Morales
 */

public class project2
{
	
	public static void main(String[] args) 
	{
		Scanner scnr = new Scanner(System.in);

		int userInput = 0, creditHours = 0;
		double studentGPA = 0.0;
		String facultyName = null, facultyDepartment = null, facultyRank = null;
		String staffName = null, staffDepartment = null, workTime = null;
		String studentName = null;
		String studentID = null, facultyID = null, staffID = null;
		
		Program program = new Program();

		
		System.out.println("\t\t\tWelcome to my Personal Management Program");
		System.out.println("");
		System.out.println("");
		
		while (true) 
		{
			System.out.println("Choose one of the options: ");
			System.out.println("");
			System.out.println("1- Enter the information of a faculty");
			System.out.println("2- Enter the information of a student");
			System.out.println("3- Print tuition invoice for a student");
			System.out.println("4- Print faculty information");
			System.out.println("5- Enter the information of a staff member");
			System.out.println("6- Print the information of a staff member");
			System.out.println("7- Exit Program");
			
			System.out.println("");
			System.out.print("   Enter your selection: ");
		
			
			// if the input is not an integer, it will go to default case
			if(scnr.hasNextInt())
			{
				userInput = scnr.nextInt();
			}
			System.out.println("");
			scnr.nextLine();
			

			switch (userInput) 
			{
			case 1:
				
				
				System.out.println("");
				System.out.println("Enter faculty info: ");
				System.out.print("\tName of the faculty: ");
				facultyName = scnr.nextLine();
					
				//new method
				facultyName = checkWords(facultyName, scnr);
				
				// we want the first name and last name to have upper cased letters 
				// we grab the space between the first name and last name
				int facultyNameSpace = facultyName.indexOf(" ");
				
				// we upper case the first character, then add the substring until the space plus the last name first character
				// then we grab that last name first character and upper case it, then add what's after that character
				facultyName = facultyName.substring(0, 1).toUpperCase() + facultyName.substring(1, facultyNameSpace + 1) + 
						facultyName.substring(facultyNameSpace + 1, facultyNameSpace + 2).toUpperCase() + facultyName.substring(facultyNameSpace + 2);
					
				System.out.print("\tID: ");
				facultyID = scnr.nextLine();
				
				System.out.print("\tRank: ");
				facultyRank = scnr.nextLine();
				
				//replace \n and set to lower case for comparison
				facultyRank = facultyRank.replace("\n","");
				facultyRank = facultyRank.toLowerCase();
				
				//compare and re-get input if invalid
				while(!(facultyRank.equals("professor")) && !(facultyRank.equals("adjunct")))
				{
					System.out.println("");
					System.out.println("\t\"" + facultyRank + "\" is invalid.");
					System.out.println("");
					
					System.out.print("\tRank: ");
					facultyRank = scnr.nextLine();
					
					facultyRank = facultyRank.replace("\n","");
					// this needed to be in the loop or you'd get stuck if you enter something wildly wrong the first time
					facultyRank = facultyRank.toLowerCase();
				}
				
				System.out.print("\tDepartment: ");
				facultyDepartment = scnr.nextLine();
				
				facultyDepartment = facultyDepartment.replace("\n","");
				facultyDepartment = facultyDepartment.toLowerCase();
				//new method
				facultyDepartment = checkDepartment(facultyDepartment, scnr);
				
				// we create the new class with the user input
				Faculty faculty = new Faculty(facultyName, facultyID, facultyDepartment, facultyRank);
				// add it into the array
				program.addFaculty(faculty);
				
				
				userInput = 0;
				break;
				
			case 2:

				System.out.println("Enter the student info: ");
				System.out.print("\tName of Student: ");
				studentName = scnr.nextLine();
				studentName = checkWords(studentName, scnr);
				
				// we want the first name and last name to have upper cased letters 
				// we grab the space between the first name and last name
				int studentNameSpace = studentName.indexOf(" ");
				
				// we upper case the first character, then add the substring until the space plus the last name first character
				// then we grab that last name first character and upper case it, then add what's after that character
				studentName = studentName.substring(0, 1).toUpperCase() + studentName.substring(1, studentNameSpace + 1) + 
						studentName.substring(studentNameSpace + 1, studentNameSpace + 2).toUpperCase() + studentName.substring(studentNameSpace + 2);
					
				System.out.print("\tID: ");
				studentID = scnr.nextLine();
					
				System.out.print("\tGPA: ");
				//new method
				studentGPA = checkGPA(scnr);
				scnr.nextLine();
					
				System.out.print("\tCredit Hours: ");
				while(true) 
				{
					//make sure the input is an integer to avoid a crash
					if(scnr.hasNextInt())	
					{
						creditHours = scnr.nextInt();
						scnr.nextLine();
						break;
					}
						
					else 
					{
						System.out.println("Invalid entry- please try again.");
						scnr.nextLine();
					}
				}
				
				// we create a new class with the user input
				Student student = new Student(studentName, studentID, studentGPA, creditHours);
				// add it into the array
				program.addStudent(student);
					
				userInput = 0;
				break;


			case 3:
				
				program.printTuition();
				
				userInput = 0;
				break;
				
				
			case 4:
				
				program.printFaculty();
				
				userInput = 0;
				break;
				
			case 5:
				
				System.out.print("\tName of the staff member: ");
				staffName = scnr.nextLine();
				staffName = checkWords(staffName, scnr);
				
				// we want the first name and last name to have upper cased letters 
				// we grab the space between the first name and last name
				int staffNameSpace = staffName.indexOf(" ");
				
				// we upper case the first character, then add the substring until the space plus the last name first character
				// then we grab that last name first character and upper case it, then add what's after that character
				staffName = staffName.substring(0, 1).toUpperCase() + staffName.substring(1, staffNameSpace + 1) + 
						staffName.substring(staffNameSpace + 1, staffNameSpace + 2).toUpperCase() + staffName.substring(staffNameSpace + 2);
					
				System.out.print("\tEnter the ID: ");
				staffID = scnr.nextLine();
				System.out.print("\tDepartment: ");
					
				staffDepartment = scnr.nextLine();
				
				staffDepartment = staffDepartment.replace("\n","");
				staffDepartment = staffDepartment.toLowerCase();
				
				staffDepartment = checkDepartment(staffDepartment, scnr);
				
				System.out.print("\tStatus, Enter P for Part Time and Enter F for Full Time: ");
				workTime = scnr.nextLine();
				
				// we create a new class with the user input
				Staff staff = new Staff(staffName, staffID, staffDepartment, workTime);
				// add it into the array
				program.addStaff(staff);
				
					
				userInput = 0;
				break;
				
			case 6:
				
				program.printStaff();
				
				userInput = 0;
				break;
			
			case 7:
				
				String userAnswer = null;
				boolean pass = false;
				
				while(pass == false)
				{
					System.out.println("");
					System.out.print("Would you like to create the report? (Y/N): ");
					userAnswer = scnr.next();
					userAnswer = userAnswer.toLowerCase();
					
					switch(userAnswer)
					{
					case "y":
						System.out.println("Report created!");
						try 
						{
							program.report();
							pass = true;
						} 
						catch (IOException e) 
						{
							System.out.println("Report file could not be created.");
							pass = false;
						}
						
						break;
					
					case "n":
						
						pass = true;
						break;
					
					default:
						System.out.println("Invalid input.");
						break;
					}
				}
				
				System.out.println("");
				System.out.println("Goodbye!");
				//changed this to return instead of break to exit program
				return;
			
			default:
				System.out.println("");
				System.out.println("Invalid entry- please try again.");
				System.out.println("");
			}
		}
	}
	
	
	//method to make sure the name is 2 words, to avoid crashes/logic errors
	public static String checkWords(String name, Scanner scnr) {
		//if it's one word: 
		while(name.indexOf(" ") == -1) {
			System.out.print("\tEnter a first and last name (only): ");
			name = scnr.nextLine();
			name = name.replace("\n","");
			name = name.toLowerCase();
		}
		
		
		//if it's more than 2 words: 
		while(true) 
		{
			int facultyNameSpace = name.indexOf(" ");
			int secondNameSpace = name.indexOf(" ", facultyNameSpace + 1);
			
			if(secondNameSpace == -1 && facultyNameSpace != -1)
			{
				break;
			}
			else
			{
				System.out.print("\tEnter a first and last name (only): ");
				name = scnr.nextLine();
				name = name.replace("\n","");
				name = name.toLowerCase();
			}
		}
		//don't forget to return the string
		return name;
	}
	
	
	
	
	//method to determine if the entered department is valid
	public static String checkDepartment(String dept, Scanner scnr) {
		//same as the rank check in case 1
		dept = dept.replace("\n","");
		dept = dept.toLowerCase();
		
		while(!(dept.equals("mathematics")) && !(dept.equals("engineering")) && !(dept.equals("sciences")))
		{
			System.out.println("");
			System.out.println("\t\"" + dept + "\" is invalid.");
			System.out.println("");
		
			System.out.print("\tDepartment: ");
			dept = scnr.nextLine();
		
			dept = dept.replace("\n","");
			dept = dept.toLowerCase();
		}
		
		return dept;
	}
	
	
	
	
	//method to make sure GPA is a double and keep it in a 0.0 - 4.0
	public static double checkGPA(Scanner scnr) {
		double gpa;
		
		while(true) 
		{
			//make sure it's a double
			if(scnr.hasNextDouble()) 
			{
				gpa = scnr.nextDouble();
				//see if it's not in range
				if((gpa > 4.0) || (gpa < 0.0)) 
				{
					System.out.println("");
					System.out.println("Invalid entry- please try again.");
					System.out.println("");
					System.out.print("\tGPA: ");
					scnr.nextLine();
				} 
				//if it's a double and in range
				else
					break;
			} 
			//not a double
			else 
			{
				System.out.println("Invalid entry- please try again.");
				scnr.nextLine();
			}
		}
		
		return gpa;
	}
}


// NEW STUFF DOWN HERE (delete this when we are done)


// creates the array of person
class Program
{
	Person[] stdntOrEmpl;
	Scanner input = new Scanner(System.in);
	
	// we create a unique character array so that
	// when we look for IDs, we don't mistakenly look for a student
	// ID when searching for an ID in a faculty print
	String[] uniqueString;
	
	// we make the arrays null at start
	public Program()
	{
		stdntOrEmpl = new Person[100];
		uniqueString = new String[100];
		for(int i = 0; i < 100; i++)
		{
			stdntOrEmpl[i] = null;
			uniqueString[i] = null;
		}
	}
	
	public void report() throws IOException
	{
		int i, a = 0, b = 0, c = 0;
		
		// we use this to utilize the date of the computer
		Date date = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy");
		
		// we create strings to be able to use the new prints of class person
		String rankOut = null;
		String depOut = null;
		String statusOut = null;
		String gpaOut = null;
		String creditOut = null;
		
		// this creates the output file
		FileOutputStream fileStream = null;
		PrintWriter outFS = null;
		
		// filling the variables of the output files
		fileStream = new FileOutputStream("report.dat");
		outFS = new PrintWriter(fileStream);
		
		outFS.println("");
		outFS.println("\tReport created on " + formatter.format(date));
		outFS.println("\t****************************");
		
		outFS.println("");
		outFS.println("Faculty Members");
		outFS.println("----------------");
		
		for(i = 0; i < 100; i++)
		{
			
			// we create an exception because the array will most likely be
			// filled with null, so we want to skip that
			try 
			{

				// if the unique string equals faculty, then we will print the 
				// inputs that are in par with the unique string
				if(uniqueString[i].equals("faculty"))
				{
					outFS.println(""+ (a += 1)+ ". " + stdntOrEmpl[i].getName());
					outFS.println("ID: " + stdntOrEmpl[i].getID());
					
					// we grab the return of this print and place the string in the variable
					rankOut = stdntOrEmpl[i].rankPrint();
					
					outFS.print(rankOut);
					outFS.print(", ");
					
					depOut = stdntOrEmpl[i].depPrint();
					
					outFS.println(depOut);
					outFS.println("");
				}
			}
			catch (Exception excpt)
			{}
		}
		
		outFS.println("");
		outFS.println("Staff Members");
		outFS.println("----------------");
		
		for(i = 0; i < 100; i++)
		{
			
			// we create an exception because the array will most likely be
			// filled with null, so we want to skip that
			try 
			{
				if(uniqueString[i].equals("staff")) 
				{
					outFS.println(""+ (b += 1)+ ". " + stdntOrEmpl[i].getName());
					outFS.println("ID: " + stdntOrEmpl[i].getID());
					
					depOut = stdntOrEmpl[i].depPrint();
					
					outFS.print(depOut);
					outFS.print(", ");
					
					statusOut = stdntOrEmpl[i].statusPrint();
					
					outFS.println(statusOut);
					outFS.println("");
				}
			}
			catch (Exception excpt)
			{}
		}
		
		outFS.println("");
		outFS.println("Student Members");
		outFS.println("----------------");
		
		for(i = 0; i < 100; i++)
		{
			
			// we create an exception because the array will most likely be
			// filled with null, so we want to skip that
			try 
			{
				
				if(uniqueString[i].equals("student")) 
				{
					outFS.println(""+ (c += 1)+ ". " + stdntOrEmpl[i].getName());
					outFS.println("ID: " + stdntOrEmpl[i].getID());
					
					gpaOut = stdntOrEmpl[i].gpaPrint();
					
					outFS.println(gpaOut);
					
					creditOut = stdntOrEmpl[i].creditPrint();
					
					outFS.println(creditOut);
					outFS.println("");
				}
			}
			catch (Exception excpt)
			{}
		}
		outFS.close();
	}
	
	
	// adds student to the array person
	public void addStudent(Student stdnt)
	{
		int index;
		
		for(index = 0; index < 100; index++)
		{
			// we add a check to see if the IDs are unique
			// it starts after the first unique ID
			if(stdntOrEmpl[index] != null)
			{
				if(stdntOrEmpl[index].getID().equals(stdnt.getID()))
				{
					System.out.println("");
					System.out.println("Not a unique ID!");
					System.out.println("Please re-enter with the correct ID.");
					System.out.println("");
					break;
				}
			}
			
			else if(stdntOrEmpl[index] == null)
			{
				stdntOrEmpl[index] = stdnt;
				uniqueString[index] = "student";
				
				System.out.println("");
				System.out.println("Student added!");
				System.out.println("");
				break;
			}
		}
	}
	
	// adds employee to the array person
	public void addFaculty(Employee empl)
	{
		int index;
		
		for(index = 0; index < 100; index++)
		{
			// we add a check to see if the IDs are unique
			if(stdntOrEmpl[index] != null)
			{
				// if any IDs match the same as the freshly input ID
				// then we do not add it to the array
				if(stdntOrEmpl[index].getID().equals(empl.getID()))
				{
					System.out.println("");
					System.out.println("Not a unique ID!");
					System.out.println("Please re-enter with the correct ID.");
					System.out.println("");
					break;
				}
			}
			
			else if(stdntOrEmpl[index] == null)
			{
				stdntOrEmpl[index] = empl;
				uniqueString[index] = "faculty";
				
				System.out.println("");
				System.out.println("Faculty added!");
				System.out.println("");
				break;
			}
		}
	}
	
	public void addStaff(Employee staff)
	{
		int index;
		
		for(index = 0; index < 100; index++)
		{
			// we add a check to see if the IDs are unique
			if(stdntOrEmpl[index] != null)
			{
				// if any IDs match the same as the freshly input ID
				// then we do not add it to the array
				if(stdntOrEmpl[index].getID().equals(staff.getID()))
				{
					System.out.println("");
					System.out.println("Not a unique ID!");
					System.out.println("Please re-enter with the correct ID.");
					System.out.println("");
					break;
				}
			}
			
			else if(stdntOrEmpl[index] == null)
			{
				stdntOrEmpl[index] = staff;
				uniqueString[index] = "staff";
				
				System.out.println("");
				System.out.println("Staff member added!");
				System.out.println("");
				break;
			}

		}
	}
	
	// used to search for information based on ID
	public int search(String ID, String unique)
	{
		int index;
		for(index = 0; index < 100; index++)
		{
			
			// we check that the index is not empty
			// we check if the uniqueString at the same index as the person we are looking for
			// is the same uniqueString as the print() we are doing
			// Reason is that since everyone is in the same person array, when we call a print tuition (for student)
			// and we enter the ID of a faculty member, then instead of print tuition, it turns into
			// print faculty
			if(stdntOrEmpl[index] != null && uniqueString[index].equals(unique))
			{
				
				// if the ID matches the ID we are looking for, we return index
				if(stdntOrEmpl[index].getID().equalsIgnoreCase(ID))
				return index;
			}
		}
		
		// returns -1 if it did not find anything
		return -1;
	}
	
	// we use this to search the ID of the student and print the tuition
	public void printTuition()
	{
		String ID;
		String unique = "student";
		
		System.out.print("Enter the student's ID: ");
		ID = input.nextLine();
		
		// we send a unique string to check if this is the right print
		int index = search(ID, unique);
		
		if(index == -1)
		{
			System.out.println("");
			System.out.println("No student matched!");
			System.out.println("");
		}
		
		else
			stdntOrEmpl[index].print();
		
	}
	
	// we use this to search the ID of the faculty member and print their info
	public void printFaculty()
	{
		String ID;
		String unique = "faculty";
		
		System.out.print("Enter the Faculty's ID: ");
		ID = input.nextLine();
		
		// we send a unique string to check if this is the right print
		int index = search(ID, unique);
		
		if(index == -1)
		{
			System.out.println("");
			System.out.println("No Faculty member matched!");
			System.out.println("");
		}
		
		else
			stdntOrEmpl[index].print();
	}
	
	// we use this to search the ID of the staff member and print their info
	public void printStaff()
	{
		String ID;
		String unique = "staff";
		
		System.out.print("Enter the Staff's ID: ");
		ID = input.nextLine();
		
		// we send a unique string to check if this is the right print
		int index = search(ID, unique);
		
		if(index == -1)
		{
			System.out.println("");
			System.out.println("No Staff member matched!");
			System.out.println("");
		}
		
		else
			stdntOrEmpl[index].print();
	}
	
}


abstract class Person
{
	private String name;
	private String ID;
	
	// getter for name
	public String getName()
	{
		return name;
	}
	
	// setter for name
	public void setName(String name)
	{
		this.name = name;
	}
	
	// getter for ID
	public String getID()
	{
		return ID;
	}
	
	// setter for ID
	public void setID(String ID)
	{
		this.ID = ID;
	}
	
	// method with name and ID
	public Person(String name, String ID)
	{
		this.name = name;
		this.ID = ID;
	}
	
	// method with name
	public Person(String name)
	{
		this.name = name;
	}
	
	// default method
	public Person()
	{
		name = "";
		ID = "";
	}
	
	
	public String toString()
	{
		return name + "\t\t" + ID;
	}
	
	public abstract void print();
	
	
	// we create these prints to be able to call them in program
	// cause if not, we have to create static variables which is not good
	public abstract String rankPrint();
	
	public abstract String depPrint();
	
	public abstract String statusPrint();
	
	public abstract String gpaPrint();
	
	public abstract String creditPrint();
	
}


class Student extends Person
{
	private double GPA;
	private int creditHours;
	
	// getter for GPA
	public double getGPA()
	{
		return GPA;
	}
	
	// setter for GPA
	public void setGPA(double GPA)
	{
		this.GPA = GPA;
	}
	
	// getter for credit hours
	public double getCreditHours()
	{
		return creditHours;
	}
	
	// setter for credit hours
	public void setCreditHours(int creditHours)
	{
		this.creditHours = creditHours;
	}
	
	// method for name, id, gpa, credit hours
	// name and id are extends from person
	public Student(String name, String ID, double GPA, int creditHours)
	{
		super(name, ID);
		this.GPA = GPA;
		this.creditHours = creditHours;
	}
	
	// method for name, id, gpa
	// name and id are extends from person
	public Student(String name, String ID, double GPA)
	{
		super(name, ID);
		this.GPA = GPA;
	}
	
	// method for name and gpa
	// name is extend from person
	public Student (String name, double GPA)
	{
		super(name);
		this.GPA = GPA;
	}
	
	// method for name
	// name is extend from person
	public Student (String name)
	{
		super(name);
	}
	
	// default method
	public Student ()
	{
		super();
		GPA = -1;
	}
	
	// do not need to use
	public String rankPrint()
	{
		return null;
	}
	
	public String depPrint()
	{
		return null;
	}
	
	public String statusPrint()
	{
		return null;
	}
	
	// need to use these prints
	public String gpaPrint()
	{
		return "GPA: " + GPA;
	}
	
	public String creditPrint()
	{
		return "Credit Hours: " + creditHours;
	}
	
	@Override
	public String toString()
	{
		return super.toString();
	}
	
	// prints student tuition when called
	public void print()
	{
		double discount = 0.0, totalPayment = 0.0;
		
		if(GPA >= 3.85)
		{
			totalPayment = ((236.45 * creditHours) + 52) * (0.75);
			discount = ((236.45 * creditHours) + 52) * (0.25);
		} 
		
		else
			totalPayment = ((236.45 * creditHours) + 52);
		
		System.out.println("");
		System.out.println("Here is the tuition invoice for " + getName()+ " :");
		System.out.println("");
		System.out.println("----------------------------------------------------------------");
		System.out.println(toString());
		System.out.println("Credit Hours: " + creditHours + " ($236.45/credit hour)");
		System.out.println("Fees: $52");
		
		// we use the same print as C language to utilize the conversions
		System.out.printf("Total payment (after discount): $%.2f \t ($%.2f discount applied)\n", totalPayment, discount);
		System.out.println("----------------------------------------------------------------");
		System.out.println("");
		System.out.println("");
	}
	
}

// abstract employee class that extends from person
abstract class Employee extends Person
{
	
	private String department;
	
	// getter for department
	public String getDepartment()
	{
		return department;
	}
	
	// setter for department
	public void setDepartment(String department)
	{
		this.department = department;
	}
	
	// method for name, id, department
	// name and id are extends from person
	public Employee(String name, String ID, String department)
	{
		super(name, ID);
		this.department = department;
	}
	
	// method for name and id
	// name and id are extends from person
	public Employee(String name, String ID)
	{
		super(name, ID);
	}
	
	// method for name
	// name is an extend from person
	public Employee(String name)
	{
		super(name);
	}
	
	// default method
	public Employee()
	{
		department = "";
	}
	
	public String depPrint()
	{
		department = department.substring(0, 1).toUpperCase() + department.substring(1);
		return department;
	}
	
	@Override
	public String toString()
	{
		department = department.substring(0, 1).toUpperCase() + department.substring(1);
		return department + " Department, ";
	}
	
	
	public abstract void print();
	
}

class Faculty extends Employee
{

	private String rank;
	
	// getter for rank
	public String getRank()
	{
		return rank;
	}
	
	// setter for rank
	public void setRank(String rank)
	{
		this.rank = rank;
	}
	
	// method for name, id, department, rank
	// name, id and department are extends from employee
	public Faculty(String name, String ID, String department, String rank)
	{
		super(name, ID, department);
		this.rank = rank;
	}
	
	// method for name, id, department
	// name, id, department are extends from employee
	public Faculty(String name, String ID, String department)
	{
		super(name, ID, department);
	}
	
	// method for name and id
	// name and id are extends from employee
	public Faculty(String name, String ID)
	{
		super(name, ID);
	}
	
	// method for name
	// name is an extend from employee
	public Faculty(String name)
	{
		super(name);
	}
	
	// default method
	public Faculty()
	{
		rank = "";
	}
	
	// need to use these prints
	public String rankPrint()
	{
		rank = rank.substring(0, 1).toUpperCase() + rank.substring(1);
		return rank;
	}
	
	public String depPrint()
	{
		return super.depPrint();
	}
	
	// do not need to use
	public String statusPrint()
	{
		return null;
	}
	
	public String gpaPrint()
	{
		return null;
	}
	
	public String creditPrint()
	{
		return null;
	}
	
	@Override
	public String toString()
	{
		rank = rank.substring(0, 1).toUpperCase() + rank.substring(1);
		return super.toString() + rank;
	}
	
	// prints faculty member info when called
	public void print() 
	{
		System.out.println("");
		System.out.println("----------------------------------------------------------------");
		System.out.println(getName() + "\t\t" + getID());
		System.out.println(toString());
		System.out.println("----------------------------------------------------------------");
		System.out.println("");
		
	}
	
}

class Staff extends Employee
{

	private String status;
	
	// getter for status
	public String getStatus()
	{
		return status;
	}
	
	// setter for status
	public void setStatus(String status)
	{
		this.status = status;
	}
	
	// method for name, id, department and status
	// name, id, and department are extended from employee
	public Staff(String name, String ID, String department, String status)
	{
		super(name, ID, department);
		this.status = status;
	}
	
	// method for name, id, department
	// name, id, and department are extended from employee
	public Staff(String name, String ID, String department)
	{
		super(name, ID, department);
	}
	
	// method for name and id
	// name and id are extended from employee
	public Staff(String name, String ID)
	{
		super(name, ID);
	}
	
	// method for name
	// name is extended from employee
	public Staff(String name)
	{
		super(name);
	}
	
	// default method
	public Staff()
	{
		status = "";
	}
	
	// need to use these prints
	public String depPrint()
	{
		return super.depPrint();
	}
	
	public String statusPrint()
	{
		if(status.equals("f"))
		{
			status = "Full Time";
		}
		else
			status = "Part Time";
		
		return status;
	}
	
	// do not need to use
	public String rankPrint() 
	{
		return null;
	}
	
	public String gpaPrint()
	{
		return null;
	}
	
	public String creditPrint()
	{
		return null;
	}
	
	@Override
	public String toString()
	{
		if(status.equals("f"))
		{
			status = "Full Time";
		}
		else
			status = "Part Time";
		return super.toString() + status;
	}
	
	// prints staff member info when called
	public void print()
	{
		System.out.println("----------------------------------------------------------------");
		System.out.println(getName() + "\t\t" + getID());
		System.out.println(toString());
		System.out.println("----------------------------------------------------------------");
		System.out.println("");
	}
}

