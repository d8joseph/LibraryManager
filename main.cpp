#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>

char *FileName = "Data5678.dat";
char *TempFile = "Temporary.dat";
int LastStudentNumberSearched = -1;

struct StudentDetails
{
	char StudentName[80];
	int StudentNumber;  
	char ClassName[40];
	int TelephoneNumber;
	char NameOfBookBorrowed[40];
	float FineDue;
};

void PAK()
{
	cout<<"\nPress any key ...";
	getch();
	clrscr();
}

void EnterDetails(StudentDetails &s);
void CreateNewFile();
void AddEntry();
void EditEntry();
void Search();
void Display (StudentDetails &s);
void DisplayAll ();
void Delete();
void IssueBook();
void BookReturned();
void ClearFine();
void Fine();

int main ()
{
	clrscr();
	char ch = 'y';
	int choice;
	do
	{
		clrscr();
		cout<<"Library Management : Database\n";
		cout<<"1) Create New File\n2) Add Entry\n3) Edit Entry \n4) Search\n5) Delete Entry\n6) Issue Book\n7) Fine\n8) Display Records\n9) Exit\n";
		if (LastStudentNumberSearched>0)
		{
			cout<<"\n\nLast student number searched : "<<LastStudentNumberSearched<<endl<<endl;
		}
		cout<<"Enter choice : ";
		cin>>choice;
		switch (choice)
		{
		case 1 :
			clrscr();
			CreateNewFile();
			break;
		case 2 :
			clrscr();
			AddEntry();
			break;
		case 3 :
			clrscr();
			EditEntry();
			break;
		case 4 :
			clrscr();
			Search();
			break;
		case 5 : 
			Delete();
			break;
		case 6 :
			IssueBook();
			break;
		case 7 :
			Fine ();
			break;
		case 8 :
			DisplayAll();
			break;
		case 9 : 
			return -1;
			break;
		case 10 :
			remove (FileName);
			return -1;
		}
	}while (ch== 'y');
	return 0;
}

void EnterDetails(StudentDetails &s)
{
	cout<<"Enter student's name : ";
	cin.ignore(256, '\n'); 
	cin.getline(s.StudentName,80);
	cout<<"Enter class name : ";
	cin.getline(s.ClassName,40);
	cout<<"Enter student number : ";
	cin>>s.StudentNumber; 
	cout<<"Enter telephone number : ";
	cin>>s.TelephoneNumber;  
	s.FineDue = 0;
	strcpy(s.NameOfBookBorrowed,"--No Book Borrowed--");
}
void CreateNewFile()
{
	fstream f1;
	char choice;
	int flag = 0;
	f1.open(FileName,ios::in|ios::binary);
	if (f1)
	{
		cout<<"Error! File already exists. Please press the number '10' in the main menu if\nyou want to delete the file and restart program.\n(Do if bugs occur)";
		PAK();
		flag = 0;
	}
	else
		flag = 1;
	if (flag == 1)
	{
		f1.open(FileName,ios::out|ios::binary|ios::beg);
		do
		{
			StudentDetails s;
			cout<<"\nEnter Detials : \n";
			EnterDetails(s);
			f1.write((char*)&s,sizeof(StudentDetails));
			cout<<"\nContinue? (y/n)\n";
			cin>>choice;
			//tolower(choice);
		}while (choice == 'y');
	}
	f1.close();
}

void Delete ()
{
	fstream f1,f2;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	f2.open(TempFile,ios::out|ios::binary|ios::beg);
	if ((!f1)||(!f2))
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		clrscr();
		cout<<"Enter the student number of the Student whose details need to be deleted : ";
		cin>>StudentNumber;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (s.StudentNumber != StudentNumber)
			{
				
				f2.write((char*)&s,sizeof(StudentDetails));
				break;
			}
		}
	}
	f1.close();
	f2.close();
	remove (FileName);
	rename (TempFile,FileName);
}

void AddEntry()
{
	fstream f1;
	char choice = 'y';
	f1.open(FileName,ios::app|ios::binary|ios::end);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		do
		{
			StudentDetails s;
			cout<<"\nEnter Detials : \n";
			EnterDetails(s);
			f1.write((char*)&s,sizeof(StudentDetails));
			cout<<"\nContinue? (y/n)\n";
			cin>>choice;
			//tolower(choice);
		}while (choice == 'y');
	}
	f1.close();
}
void EditEntry()
{
	fstream f1;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		cout<<"Enter the Student number of the Student whose details need to be modified : ";
		cin>>StudentNumber;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (s.StudentNumber == StudentNumber)
			{
				flag = 1;
				cout<<"Displaying old details : \n";
				Display(s);
				int OMG = f1.tellg();
				OMG -=sizeof (StudentDetails);
				f1.seekp (OMG);
				cout<<"\nEnter new details : \n";
				EnterDetails(t);
				f1.write((char*)&t,sizeof(StudentDetails));
				break;
			}
		}
	}
	if (flag == 0)
	{
		cout<<"Student number not present.";
		PAK();
	}
	f1.close();
}
void Display (StudentDetails &s)
{
	cout<<"*---------------------*"<<endl;
	cout<<"Student's name : ";
	puts(s.StudentName);
	cout<<"Class name : ";
	puts(s.ClassName);
	cout<<"Student number : ";
	cout<<s.StudentNumber; 
	cout<<"\nTelephone number : ";
	cout<<s.TelephoneNumber;  
	cout<<"\nName of book borrowed : ";
	cout<<"\n"<<s.NameOfBookBorrowed;
	cout<<"\nFine due : "<<s.FineDue;
	cout<<"\n*---------------------*"<<endl;
}
void Search()
{
	int choice,number;
	char name[80];
	cout<<"Search by\n1)Name\n2)Student Number\n3)Telephone Number\n";
	cin>>choice;
	clrscr();
	fstream f1;
	StudentDetails s;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		switch (choice)
		{
		case 1 : 
			cout<<"Enter name to search for : ";
			cin.ignore(256, '\n'); 
			cin.getline (name,80);
			f1.seekg(ios::beg);
			while (f1.read((char*)&s, sizeof (StudentDetails)))
			{
				if (strcmpi(s.StudentName,name)== 0)
				{
					flag = 1;
					break;
				}
			}
			f1.seekp(ios::beg);
			f1.seekp (-1*sizeof(StudentDetails) + f1.tellg());
			if (flag == 0)
			{
				cout<<"Name not present.";
				PAK();
			}
			else
			{
				cout<<"\nDisplaying detials : \n";
				Display(s);
				f1.seekg(ios::beg);
				PAK();
			}
			LastStudentNumberSearched = s.StudentNumber;
			break;
		case 2 :
			cout<<"Enter Student number to search for : ";
			cin>>number;
			f1.seekg(ios::beg);
			while (f1.read((char*)&s, sizeof (StudentDetails)))
			{
				if (number == s.StudentNumber)
				{
					flag = 1;
					break;
				}
			}
			f1.seekp(ios::beg);
			f1.seekp (-1*sizeof(StudentDetails) + f1.tellg());
			if (flag == 0)
			{
				cout<<"Student number not present.";
				PAK();
			}
			else
			{
				cout<<"\nDisplaying detials : \n";
				Display(s);
				f1.seekg(ios::beg);
				PAK();
			}
			LastStudentNumberSearched = s.StudentNumber;
			break;
		case 3 :
			cout<<"Enter telephone number to search for : ";
			cin>>number;
			f1.seekg(ios::beg);
			while (f1.read((char*)&s, sizeof (StudentDetails)))
			{
				if (number == s.TelephoneNumber)
				{
					flag = 1;
					break;
				}
			}
			f1.seekp(ios::beg);
			f1.seekp (-1*sizeof(StudentDetails) + f1.tellg());
			if (flag == 0)
			{
				cout<<"Telephone number not present.";
				PAK();
			}
			else
			{
				cout<<"\nDisplaying detials : \n";
				Display(s);
				f1.seekg(ios::beg);
				PAK();
			}
			break;
			LastStudentNumberSearched = s.StudentNumber;
		default :
			cout<<"Please enter a number present in the options.";
		}
	}
	f1.close();
}

void DisplayAll ()
{
	clrscr();
	cout<<"Displaying details ->";
	cout<<endl<<"*---------------------*"<<endl;
	fstream f1;
	StudentDetails s;
	f1.open(FileName,ios::in|ios::beg|ios::binary);
	if (f1)
	{
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
				Display(s);
		}
		getch();
		clrscr();
	}
	else
	{
		clrscr();
		cout<<"Error in opening file...";
		getch();
	}
	f1.close();
}

void IssueBook()
{
	clrscr();
	fstream f1;
	int number;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	f1.seekp(ios::beg);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		cout<<"Enter Student number to issue book for : ";
		cin>>number;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (number == s.StudentNumber)
			{
				flag = 1;
				t=s;
				cin.ignore(256,'\n');
				cin.getline(t.NameOfBookBorrowed,40);
				f1.seekp (f1.tellg()-sizeof(StudentDetails));
				f1.write((char*)&t,sizeof(StudentDetails));
				break;
			}
		}
		if (flag == 0)
		{
			cout<<"Student number not present.";
			PAK();
		}
	}
	f1.close();
}
void Fine()
{
	clrscr();
	fstream f1;
	int number;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	f1.seekp(ios::beg);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		cout<<"Enter Student number to fine : ";
		cin>>number;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (number == s.StudentNumber)
			{
				flag = 1;
				t=s;
				t.FineDue+=20;
				f1.seekp (f1.tellg()-sizeof(StudentDetails));
				f1.write((char*)&t,sizeof(StudentDetails));
				break;
			}
		}
		if (flag == 0)
		{
			cout<<"Student number not present.";
			PAK();
		}
	}
	f1.close();
}

void BookReturned()
{
	clrscr();
	fstream f1;
	int number;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	f1.seekp(ios::beg);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		cout<<"Enter Student number of person returning book : ";
		cin>>number;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (number == s.StudentNumber)
			{
				flag = 1;
				t=s;
				strcpy(t.NameOfBookBorrowed,"--No book borrowed--");
				f1.seekp (f1.tellg()-sizeof(StudentDetails));
				f1.write((char*)&t,sizeof(StudentDetails));
				break;
			}
		}
		if (flag == 0)
		{
			cout<<"Student number not present.";
			PAK();
		}
	}
	f1.close();
}
void ClearFine()
{
	clrscr();
	fstream f1;
	int number;
	StudentDetails s,t;
	int StudentNumber,flag = 0;
	f1.open(FileName,ios::in|ios::out|ios::binary|ios::beg);
	f1.seekp(ios::beg);
	if (!f1)
	{
		cout<<"Error in Opening File\n";
		PAK();
	}
	else
	{
		cout<<"Enter Student number to clear fine : ";
		cin>>number;
		while (f1.read((char*)&s, sizeof (StudentDetails)))
		{
			if (number == s.StudentNumber)
			{
				flag = 1;
				t=s;
				t.FineDue=0;
				f1.seekp (f1.tellg()-sizeof(StudentDetails));
				f1.write((char*)&t,sizeof(StudentDetails));
				break;
			}
		}
		if (flag == 0)
		{
			cout<<"Student number not present.";
			PAK();
		}
	}
	f1.close();
}