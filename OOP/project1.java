package main1;
import java.util.Scanner;

/*
 * Project 1
 * Jessica Garcia-Velez, Clarice Elso, Karlos Morales
 */


public class project1 
{
	
	public static void main(String[] args) 
	{
		Scanner scnr = new Scanner(System.in);

		int userInput = 0, creditHours1 = 0, creditHours2 = 0, whichStudent = 0;
		double student1GPA = 0.0, student2GPA = 0.0;
		String facultyName = null, facultyDepartment = null, facultyRank = null;
		String staffName = null, staffDepartment = null, workTime = null;
		String student1 = null, student2 = null;
		String student1ID = null, student2ID = null, facultyID = null, staffID = null;
		String replaceInput = null;
		boolean pass = false;

		
		System.out.println("\t\t\tWelcome to my Personal Management Program");
		System.out.println("");
		System.out.println("");
		
		while (true) 
		{
			System.out.println("Choose one of the options: ");
			System.out.println("");
			System.out.println("1- Enter the information of the faculty");
			System.out.println("2- Enter the information of the two students");
			System.out.println("3- Print tuition invoice");
			System.out.println("4- Print faculty information");
			System.out.println("5- Enter the information of the staff member");
			System.out.println("6- Print the information of the staff member");
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
				//check faculty input
				if (facultyName != null)
				{
					System.out.println("You already have a faculty member filled in. Do you want to update their information?");
					
					while (pass == false)
					{
						System.out.print("Yes or No: ");
						replaceInput = scnr.next();
						replaceInput = replaceInput.toLowerCase();
					
					
						switch (replaceInput)
						{
						// if there is, we start the replace case
						case "yes": 
							facultyName = null;
							facultyID = null;
							facultyRank = null;
							facultyDepartment = null;
							pass = true;
							scnr.nextLine();
							break;
					
							// if not, we just break
						case "no":
							userInput = 0;
							pass = true;
							System.out.println("");
							scnr.nextLine();
							break;
						
						default:
							pass = false;
						
						}
					}
				}
				
				while(facultyName == null)
				{
					System.out.println("");
					System.out.println("Enter faculty info: ");
					System.out.print("\tName of the faculty: ");
					facultyName = scnr.nextLine();
					
					//new method
					facultyName = checkWords(facultyName, scnr);
					
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
					
					System.out.println("\tFaculty successfully added!");
					System.out.println("");
				} 
				
				// we say userInput = 0 before very important breaks (ending cases breaks)
				// so that userInput is reset and does not continue with a case number
				// since it will be updated by any other integer
				pass = false;
				userInput = 0;
				break;
				
			case 2:
				
				// checks if there are already student input saved
				if (student1 != null && student2 != null)
				{
					System.out.println("You already have two students filled in. Do you want to update their information?");
					
					while (pass == false)
					{
						System.out.print("Yes or No: ");
						replaceInput = scnr.next();
						replaceInput = replaceInput.toLowerCase();
					
						
						switch (replaceInput)
						{
						// if there is, we start the replace case
						case "yes": 
							student1 = null;
							student1ID = null;
							student1GPA = 0.0;
							creditHours1 = 0;
							student2 = null;
							student2ID = null;
							student2GPA = 0.0;
							creditHours2 = 0;
							pass = true;
							scnr.nextLine();
							break;
					
							// if not, we just break
						case "no":
							userInput = 0;
							pass = true;
							System.out.println("");
							scnr.nextLine();
							break;
							
						default:
							pass = false;
							
						}
					}
				}
				
				// if we select no in previous case, student1 will have an input neglecting this
				// if we select yes, then everything is null and this will activate
				while (student1 == null)
				{
					// student 1
					System.out.println("Enter student 1 info: ");
					System.out.print("\tName of Student: ");
					student1 = scnr.nextLine();
					student1 = checkWords(student1, scnr);
					
					System.out.print("\tID: ");
					student1ID = scnr.nextLine();
					
					System.out.print("\tGPA: ");
					//new method
					student1GPA = checkGPA(scnr);
					scnr.nextLine();
					
					System.out.print("\tCredit Hours: ");
					while(true) 
					{
						//make sure the input is an integer to avoid a crash
						if(scnr.hasNextInt())	
						{
							creditHours1 = scnr.nextInt();
							break;
						}
						
						else 
						{
							System.out.println("Invalid entry- please try again.");
							scnr.nextLine();
						}
					}
					
					scnr.nextLine();
					System.out.println("Thanks!");
					System.out.println("");
					System.out.println("");
					
					
					// student 2
					System.out.println("Enter student 2 info: ");
					System.out.print("\tName of Student: ");
					student2 = scnr.nextLine();
					student2 = checkWords(student2, scnr);
					
					System.out.print("\tID: ");
					student2ID = scnr.nextLine();
					
					System.out.print("\tGPA: ");
					student2GPA = checkGPA(scnr);
					scnr.nextLine();
					
					System.out.print("\tCredit Hours: ");
					while(true) 
					{
						if(scnr.hasNextInt()) 
						{
							creditHours2 = scnr.nextInt();
							break;
						}
						
						else 
						{
							System.out.println("Invalid entry- please try again.");
							scnr.nextLine();
						}
					}
					
					scnr.nextLine();
					System.out.println("Thanks!");
					System.out.println("");
					System.out.println("");
					break;
					
				}
				
				pass = false;
				userInput = 0;
				break;

			case 3:
				// if no student input, we give an error and return to menu
				if (student1 == null)
				{
					System.out.println("Sorry! No Student member entered yet.");
					System.out.println("");
					userInput = 0;
					break;
				}
				
				// if there is the first student input, then we continue the case
				while (student1 != null)
				{
					System.out.print("Which student? Enter 1 for " + student1 + " or Enter 2 for " + student2 + " ? ");
					whichStudent = scnr.nextInt();
					scnr.nextLine();

					switch (whichStudent) {
					case 1:
						//new method
						tutInvoice(student1, student1ID, creditHours1, student1GPA);
						break;
					case 2:
						tutInvoice(student2, student2ID, creditHours2, student2GPA);
						break;
					}
					break;
				}
				userInput = 0;
				break;
				
				
			case 4:
				// if no faculty input, we give an error and return to menu
				if (facultyName == null)
				{
					System.out.println("Sorry! No Faculty member entered yet.");
					System.out.println("");
					userInput = 0;
					break;
				}
				
				// if there is input, we continue the case
				while (facultyName != null)
				{
					// first letter is set to upper case
					facultyDepartment = facultyDepartment.substring(0, 1).toUpperCase() + facultyDepartment.substring(1);
					facultyRank = facultyRank.substring(0, 1).toUpperCase() + facultyRank.substring(1);
					
					// we want the first name and last name to have upper cased letters 
					// we grab the space between the first name and last name
					int facultyNameSpace = facultyName.indexOf(" ");
					
					// we upper case the first character, then add the substring until the space plus the last name first character
					// then we grab that last name first character and upper case it, then add what's after that character
					facultyName = facultyName.substring(0, 1).toUpperCase() + facultyName.substring(1, facultyNameSpace + 1) + 
							facultyName.substring(facultyNameSpace + 1, facultyNameSpace + 2).toUpperCase() + facultyName.substring(facultyNameSpace + 2);
					
					
					
					System.out.println("");
					System.out.println("----------------------------------------------------------------");
					System.out.println(facultyName + "\t" + facultyID);
					System.out.println(facultyDepartment + " Department, " + facultyRank);
					System.out.println("----------------------------------------------------------------");
					System.out.println("");
					break;
				}
				userInput = 0;
				break;
				
			case 5:
				
				if (staffName != null)
				{
					System.out.println("You already have a staff member filled in. Do you want to update their information?");
					
					while(pass == false)
					{
						System.out.print("Yes or No: ");
						replaceInput = scnr.next();
						replaceInput = replaceInput.toLowerCase();
					
					
						switch (replaceInput)
						{
						// if there is, we start the replace case
						case "yes": 
							staffName = null;
							staffID = null;
							staffDepartment = null;
							workTime = null;
							pass = true;
							scnr.nextLine();
							break;
					
							// if not, we just break
						case "no":
							userInput = 0;
							pass = true;
							System.out.println("");
							scnr.nextLine();
							break;
							
						default:
							pass = false;
							
						}
					}
				}
				
				while(staffName == null)
				{
					System.out.print("\tName of the staff member: ");
					staffName = scnr.nextLine();
					staffName = checkWords(staffName, scnr);
					
					System.out.print("\tEnter the ID: ");
					staffID = scnr.nextLine();
					System.out.print("\tDepartment: ");
					
					staffDepartment = scnr.nextLine();
				
					staffDepartment = staffDepartment.replace("\n","");
					staffDepartment = staffDepartment.toLowerCase();
				
					staffDepartment = checkDepartment(staffDepartment, scnr);
				
					System.out.print("\tStatus, Enter P for Part Time and Enter F for Full Time: ");
					workTime = scnr.nextLine();
				
				
					System.out.println("\tStaff member added!");
					System.out.println("");
				}
				
				pass = false;
				userInput = 0;
				break;
				
			case 6:
				// if no staff input, we give an error and return to menu
				if (staffName == null)
				{
					System.out.println("Sorry! No Staff member entered yet.");
					System.out.println("");
					userInput = 0;
					break;
				}
				
				// if there is input, we continue the case
				while (staffName != null)
				{
					// we place the string lower case first
					workTime = workTime.toLowerCase();
					
					// we equal it to lower case f now
					if(workTime.equals("f"))
					{
						workTime = "Full Time";
					}
					else
						workTime = "Part Time";
					
					// first letter is set to upper case
					staffDepartment = staffDepartment.substring(0, 1).toUpperCase() + staffDepartment.substring(1);
					
					// we want the first name and last name to have upper cased letters 
					// we grab the space between the first name and last name
					int staffNameSpace = staffName.indexOf(" ");
					
					// we upper case the first character, then add the substring until the space plus the last name first character
					// then we grab that last name first character and upper case it, then add what's after that character
					staffName = staffName.substring(0, 1).toUpperCase() + staffName.substring(1, staffNameSpace + 1) + 
							staffName.substring(staffNameSpace + 1, staffNameSpace + 2).toUpperCase() + staffName.substring(staffNameSpace + 2);
					
					System.out.println("----------------------------------------------------------------");
					System.out.println(staffName + "\t" + staffID);
					System.out.println(staffDepartment + " Department, " + workTime);
					System.out.println("----------------------------------------------------------------");
					System.out.println("");
					break;
				}
				userInput = 0;
				break;
			
			case 7:
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
	
	
	
	
	//method to calculate/print tuition invoice
	public static void tutInvoice(String student, String id, int creditHours, double gpa) 
	{
		double discount = 0.0, totalPayment = 0.0;
		
		if (gpa >= 3.85) 
		{
			totalPayment = ((236.45 * creditHours) + 52) * (0.85);
			discount = ((236.45 * creditHours) + 52) * (0.15);
		} 
		
		else
			totalPayment = ((236.45 * creditHours) + 52);
		
		// we want the first name and last name to have upper cased letters 
		// we grab the space between the first name and last name
		int studentNameSpace = student.indexOf(" ");
		
		// we upper case the first character, then add the substring until the space plus the last name first character
		// then we grab that last name first character and upper case it, then add what's after that character
		student = student.substring(0, 1).toUpperCase() + student.substring(1, studentNameSpace + 1) + 
				student.substring(studentNameSpace + 1, studentNameSpace + 2).toUpperCase() + student.substring(studentNameSpace + 2);
		
		System.out.println("");
		System.out.println("Here is the tuition invoice for " + student + " :");
		System.out.println("");
		System.out.println("----------------------------------------------------------------");
		System.out.println(student + "\t" + id);
		System.out.println("Credit Hours: " + creditHours + " ($236.45/credit hour)");
		System.out.println("Fees: $52");
		
		// we use the same print as C language to utilize the conversions
		System.out.printf("Total payment (after discount): $%.2f \t ($%.2f discount applied)\n", totalPayment, discount);
		System.out.println("----------------------------------------------------------------");
		System.out.println("");
		System.out.println("");
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
		
		while(!(dept.equals("mathematics")) && !(dept.equals("engineering")) && !(dept.equals("english")))
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
					System.out.println("Invalid entry- please try again.");
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