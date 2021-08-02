// HEADER FILES
#include<iostream>
#include<ctype.h>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

// CLASS
 class account
{ int acno;
char name[50];
float deposit;
char type;
public:
void create_account();   // getdata from user
void show_account();     //show data on screen
void modify();                 // add new data
void dep(int);                 // accept amount and add to balance amount
void withdraw(int);        // accept amount and substract to balance amount
void showtable();          // show data in tabular format
int retacno();                // return account number
int retdeposit();            // return
char rettype();
};

void account :: create_account()
{
	system("CLS");
	cout<<"\nEnter new account no. : " ;
	cin>>acno;
	cin.get();
	cout<<"\n\n Enter the name of the account holder : " ;
	cin.getline(name,50);
	cout<<"Enter the type of the account ( C/S ) : ";
	cin>>type;
	type = toupper(type);
	cout<< "\nEnter the initial amount ( >= 500 for Saving and >= 1000 for Current):";
	cin>>deposit;
	cout<<"\n\n\n ACCOUNT CREATED...";
}

void account ::  show_account()
{
    system("CLS");
	cout<<"\nAccount Number :- "<<acno;
	cout<<"\nAccount Holder Name :- "<<name;
	cout<<"\nAccount type :- "<<type;
	cout<<"\nBalance amount :- "<<deposit;
}

void account ::  modify()
{
	system("CLS");
	cout<<"\nAccount Number :- "<<acno;
	cout<<"\nModify Account Name: ";
	cin.getline(name,50);
	cout<<"\nModify Account Type: ";
	cin>> type;
	type = toupper(type);
	cout<<"\nModify balance amount: ";
	cin>>deposit;
}

void account :: dep(int x)
{
	deposit+= x;
}
void account :: withdraw(int x)
{
	deposit-= x;
}
void account :: showtable()
{
	cout<<acno<<"\t\t"<<name<<"\t\t     "<<type<<"\t\t"<<deposit<<endl;
}
int account :: retacno()
{
	return acno;
}
int account :: retdeposit()
{
	return deposit;
}
char account :: rettype()
{
	return type;
}

// FUNCTION PROTOTYPES
void write_account(); //function to write record in binary file
void display_sp(int); //function to display account details given by user
void modify_account(int); //function to modify account record of file
void delete_account(int); //function to delete record of file
void display_all(); //function to display all account details
void deposit_withdraw(int,int); //function to  deposit/withdraw amount for given account
void intro();      // introductory screen function

// MAIN() FUNCTION OF THE PROGRAM

int main()
{
	system("CLS");
	int num;
	intro();
	do
	{
		system("CLS");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t8. EXIT";
		cout<<"\n\n\tSelect Option(1-8)";
		cin>>num;
        system("CLS");
		switch(num)
		{
			case 1:
				write_account();
				break;
			case 2:
				cout<<"\n\n\t Enter Account Number:";
				cin>>num;
				deposit_withdraw(num,1);
				break;
			case 3 :
				cout<<"\n\n\t Enter Account Number:";
				cin>>num;
				deposit_withdraw(num,2);
				break;
			case 4:
				cout<<"\n\n\t Enter Account Number:";
				cin>>num;
				display_sp(num);
				break;
			case 5:
				display_all();
				break;
			case 6:
				cout<<"\n\n\t Enter Account Number:";
				cin>>num;
				delete_account(num);
				break;
			case 7:
				cout<<"\n\n\t Enter Account Number:";
				cin>>num;
				modify_account(num);
				break;
			case 8:
				cout<<"\n\n\t EXITING";
				break;
			default:
				cout<<"\a";
				break;
		}
		cin.get();
	}while(num!=8);
}
// FUNCTION DEFINITIONS

void write_account()
{
	account ac;
	ofstream Fout;
	Fout.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	Fout.write((char*)&ac, sizeof(account));
	Fout.close();
}

void display_sp(int n)
{
	account ac;
	int flag=-1;
	ifstream Fin;
	Fin.open("account.dat",ios::binary);
	if(!Fin)
	{
		cout<<"File could not be opened";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(Fin.read((char*)&ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=0;
		}
	}
	Fin.close();
	if(flag==-1)
	cout<<"\n\nAccount number does not exist";
	cin.get();
}

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat" , ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened";
		return;
	}
	while(!File.eof() && found ==0)
	{
		File.read((char*)&ac, sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\tEnter new details for account"<<endl;
			ac.modify();
			int pos = (-1)*(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write((char*)&ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
	cout<<"\n\n\t Record Not Found";
}

void delete_account(int n)
{
	account ac;
	ifstream Fin;
	ofstream Fout;
	Fin.open("account.dat",ios::binary|ios::out);
	if(!Fin)
	{
		cout<<"File could not be opened ";
		return;
	}
	Fout.open("Temp.dat",ios::binary);
	Fin.seekg(0,ios::beg);
	while(Fin.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			Fout.write((char*)&ac, sizeof(account));
		}
	}
	Fin.close();
	Fout.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted";
}

void display_all()
{
	account ac;
	ifstream Fin;
	Fin.open("account.dat",ios::binary);
	if(!Fin)
	{
		cout<<"File could not be opened";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"===========================================================\n";
	cout<<"A/c no.           Name              Type       Balance\n";
	cout<<"===========================================================\n";
	while(Fin.read((char*)&ac, sizeof(ac)))
	{
		ac.showtable();
	}
	Fin.close();
	cin.get();
}

void deposit_withdraw(int n , int option)
{
	int amt;
	int found = 0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened";
		return;
	}
	while(!File.eof() && found==0)
	{
		File.read((char*)&ac, sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tDEPOSIT";
				cout<<"\n\nEnter the amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tWITHDRAW";
				cout<<"\n\nEnter the amount to be withdrawn";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S')||(bal<1000 && ac.rettype()=='C'))
				cout<<"Insufficient balance";
				else
				ac.withdraw(amt);
			}
			int pos=((sizeof(ac))*(-1));
			File.seekp(pos,ios::cur);
			File.write((char*)&ac, sizeof(account));
			cout<<"\n\n\tRECORD UPDATED";
			found = 1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n RECORD NOT FOUND";
}

void intro()
{         system("CLS");
	cout<<"\n\n\t  BANK";
	cout<<"\n\n\t  MANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n(press enter to continue)";
	cin.get();
}
 // END OF THE PROJECT
