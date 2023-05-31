#include <iostream>
#include <fstream>

using namespace std;

struct Record
{
	int id;
	string name;
	string email;
};

void insertRecord(const Record &record)
{
	ofstream file("records.dat", ios::binary | ios::app);
	if (!file)
	{
		cerr << "Error opening file." << endl;
		return;
	}

	file.write(reinterpret_cast<const char *>(&record), sizeof(record));
	file.close();

	cout << "Record inserted successfully." << endl;
}

void deleteRecord(int id)
{
	ifstream file("records.dat", ios::binary);
	if (!file)
	{
		cerr << "Error opening file." << endl;
		return;
	}

	ofstream tempFile("temp.dat", ios::binary);
	if (!tempFile)
	{
		cerr << "Error creating temporary file." << endl;
		file.close();
		return;
	}

	Record record;
	bool found = false;
	while (file.read(reinterpret_cast<char *>(&record), sizeof(record)))
	{
		if (record.id != id)
		{
			tempFile.write(reinterpret_cast<const char *>(&record), sizeof(record));
		}
		else
		{
			found = true;
		}
	}

	file.close();
	tempFile.close();

	if (found)
	{
		remove("records.dat");
		rename("temp.dat", "records.dat");
		cout << "Record deleted successfully." << endl;
	}
	else
	{
		remove("temp.dat");
		cout << "Record not found." << endl;
	}
}

int main()
{
	int option;
	Record newRecord;
	int recordIdToDelete;

	while (true)
	{
		cout << "-------------------Menu-------------------" << endl;
		cout << "1. Insert a record" << endl;
		cout << "2. Delete a record" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter the option: ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "Enter the record ID: ";
			cin >> newRecord.id;
			cout << "Enter the record name: ";
			cin >> newRecord.name;
			cout << "Enter the record email: ";
			cin >> newRecord.email;
			insertRecord(newRecord);
			break;
		case 2:
			cout << "Enter the ID of the record to delete: ";
			cin >> recordIdToDelete;
			deleteRecord(recordIdToDelete);
			break;
		case 3:
			return 0;
		default:
			cout << "Invalid option. Please try again." << endl;
		}

		cout << endl;
	}
}
