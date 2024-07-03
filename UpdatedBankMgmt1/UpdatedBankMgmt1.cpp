#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class Bank_account
{
	int accountNumber;
	char name[50];
	int deposit;
	char type;

public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char retype() const;
};

void Bank_account::create_account()
{
	cout << "Enter The Account Number: " << endl;
	cin >> accountNumber;
	cout << "Enter The Name of The Account Holder: " << endl;
	cin.ignore();
	cin.getline(name, 50);
	cout << " Enter The Type of The Account (C/S): " << endl;
	cin >> type;
	cout << "Enter Initial Amount: " << endl;
	cin >> deposit;
	cout << "Account Created" << endl;
}

void Bank_account::show_account() const
{
	cout << "Account No.: " << accountNumber << endl;
	cout << "Account Holder Name: " << name << endl;
	cout << "Type of Account: " << type << endl;
	cout << "Balance Amount: " << deposit << endl;
}

void Bank_account::modify()
{
	cout << "Account No.: " << accountNumber << endl;
	cout << "Modify Account Holder Name: " << endl;
	cin.ignore();
	cin.getline(name, 50);
	cout << "Modify Type of Account: " << endl;
	cin >> type;
	cout << "Modify Balance Amount: ";
	cin >> deposit;
}

void Bank_account::dep(int x)
{
	deposit += x;
}

void Bank_account::draw(int x)
{
	deposit -= x;
}

void Bank_account::report() const
{
	cout << accountNumber << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int Bank_account::retacno() const
{
	return accountNumber;
}

int Bank_account::retdeposit() const
{
	return deposit;
}

char Bank_account::retype() const
{
	return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	char ch;
	int num;
	do
	{
		system("CLS");
		cout << "===============================\n";
		cout << "BANK MANAGEMENT SYSTEM\n";
		cout << "===============================\n";
		cout << " :: MAIN MENU: \n";
		cout << "1. NEW ACCOUNT\n";
		cout << "2. DEPOSIT AMOUNT\n";
		cout << "3. WITHDRAW AMOUNT\n";
		cout << "4. BALANCE INQUIRY\n";
		cout << "5. ALL ACCOUNT HOLDERS\n";
		cout << "6. CLOSE ACCOUNT\n";
		cout << "7. MODIFY ACCOUNT\n";
		cout << "8. EXIT\n";
		cout << "Select your option (1-8): ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout << "Enter the Account Number: ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "Enter the Account Number: ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "Enter the Account Number: ";
			cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout << "Enter the Account Number: ";
			cin >> num;
			delete_account(num);
			break;
		case '7':
			system("CLS");
			cout << "Enter the Account Number: ";
			cin >> num;
			modify_account(num);
			break;
		case '8':
			system("CLS");
			cout << "Thank you for using Moussa Bank\n";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

void write_account()
{
	Bank_account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
	outFile.close();
}

void display_sp(int n)
{
	Bank_account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened || Press any key...\n";
		return;
	}
	cout << "BALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (!flag)
		cout << "Account number does not exist\n";
}

void modify_account(int n)
{
	bool found = false;
	Bank_account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened\n";
		return;
	}
	while (!File.eof() && !found)
	{
		File.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "Enter the new details of the account\n";
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(Bank_account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
			cout << "\n\n\t\t\tRecord Updated\n";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "Record not found\n";
}

void delete_account(int n)
{
	Bank_account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened\n";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "Record Deleted\n";
}

void display_all()
{
	Bank_account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened\n";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "===========================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "===========================================\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	Bank_account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened\n";
		return;
	}
	while (!File.eof() && !found)
	{
		File.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "TO DEPOSIT AMOUNT\n";
				cout << "Enter the amount to be deposited: ";
				cin >> amt;
				ac.dep(amt);
			}
			else if (option == 2)
			{
				cout << "TO WITHDRAW AMOUNT\n";
				cout << "Enter the amount to be withdrawn: ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if (bal < 0)
					cout << "Insufficient balance\n";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac), sizeof(Bank_account));
			cout << "\n\n\t\t\tRecord Updated\n";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "Record not found\n";
}
