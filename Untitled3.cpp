#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class contact {
private:
    char fName[50], lName[50], address[50], email[50];
    long long phNo;

public:
    void createContact() {
        cout << "Enter your first name: ";
        cin >> fName;
        cout << "Enter your last name: ";
        cin >> lName;
        cout << "Enter phone: ";
        cin >> phNo;
        cout << "Enter address: ";
        cin >> address;
        cout << "Enter email: ";
        cin >> email;
    }

    void showContact() {
        cout << "Name: " << fName << " " << lName << endl;
        cout << "Phone: " << phNo << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
    }

    void writeOnFile() {
        char ch;
        ofstream f1;
        f1.open("CMS.dat", ios::binary | ios::app);

        do {
            createContact();
            f1.write(reinterpret_cast<char*>(this), sizeof(*this));
            cout << "Do you have next data?(y/n)";
            cin >> ch;
        } while (ch == 'y');

        cout << "Contact has been successfully created...";
        f1.close();
    }

    void readFromFile() {
        ifstream f2;
        f2.open("CMS.dat", ios::binary);

        cout << "\n================================\n";
        cout << "LIST OF CONTACTS";
        cout << "\n================================\n";

        while (!f2.eof()) {
            if (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                showContact();
                cout << "\n================================\n";
            }
        }
        f2.close();
    }

    void searchOnFile() {
        ifstream f3;
        char name[50];
        cout << "Enter first name: ";
        cin >> name;
        f3.open("CMS.dat", ios::binary);

        bool found = false;
        while (!f3.eof()) {
            if (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (strcmp(fName, name) == 0) {
                    showContact();
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "\n\nNo record found";
        }
        
        f3.close();
    }

    void deleteFromFile() {
        char name[50];
        int flag = 0;
        ofstream f4;
        ifstream f5;

        f5.open("CMS.dat", ios::binary);
        f4.open("temp.dat", ios::binary);

        cout << "Enter first name to delete: ";
        cin >> name;

        while (!f5.eof()) {
            if (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (strcmp(fName, name) != 0) {
                    f4.write(reinterpret_cast<char*>(this), sizeof(*this));
                } else {
                    flag = 1;
                }
            }
        }
        f5.close();
        f4.close();
        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        flag == 1 ?
            cout << endl << endl << "\tContact Deleted..." :
            cout << endl << endl << "\tContact Not Found...";
    }

    void editContact() {
        char name[50];
        fstream f6;

        cout << "Edit contact";
        cout << "\n===============================\n\n";
        cout << "Enter the first name to be edited: ";
        cin >> name;

        f6.open("CMS.dat", ios::binary | ios::out | ios::in);

        bool found = false;
        while (!f6.eof()) {
            if (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (strcmp(fName, name) == 0) {
                    cout << "Enter new record\n";
                    createContact();
                    int pos = -1 * sizeof(*this);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char*>(this), sizeof(*this));
                    cout << endl << endl << "\tContact Successfully Updated...";
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "\n\nNo record found";
        }
        
        f6.close();
    }
};

int main() {
    system("cls");
    system("Color 3F"); // "Color XY", X - background color, Y - text color

    cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
    getch();

    while (1) {
        contact c1;
        int choice;

        system("cls");
        system("Color 03");

        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n=====================\n";
        cout << "[1] Add a new Contact\n";
        cout << "[2] List all Contacts\n";
        cout << "[3] Search for contact\n";
        cout << "[4] Delete a Contact\n";
        cout << "[5] Edit a Contact\n";
        cout << "[0] Exit";
        cout << "\n=====================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                c1.writeOnFile();
                break;

            case 2:
                system("cls");
                c1.readFromFile();
                break;

            case 3:
                system("cls");
                c1.searchOnFile();
                break;

            case 4:
                system("cls");
                c1.deleteFromFile();
                break;

            case 5:
                system("cls");
                c1.editContact();
                break;

            case 0:
                system("cls");
                cout << "\n\n\n\t\t\tThank you for using CMS." << endl << endl;
                exit(0);
                break;

            default:
                continue;
        }

        int opt;
        cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >> opt;

        switch (opt) {
            case 0:
                system("cls");
                cout << "\n\n\n\t\t\tThank you for using CMS." << endl << endl;
                exit(0);
                break;

            default:
                continue;
        }
    }

    return 0;
}

