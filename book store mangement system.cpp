#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Book {
public:
    int id;
    string title, author;
    float price;
    
    void getBookDetails() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        cout << "Enter Price: ";
        cin >> price;
    }

    void displayBook() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author << " | Price: $" << price << endl;
    }
};

// Function to add a book to the file
void addBook() {
    Book book;
    book.getBookDetails();

    ofstream file("books.dat", ios::app | ios::binary);
    file.write((char*)&book, sizeof(Book));
    file.close();

    cout << "Book added successfully!\n";
}

// Function to display all books
void displayBooks() {
    ifstream file("books.dat", ios::in | ios::binary);
    if (!file) {
        cout << "No books available.\n";
        return;
    }

    Book book;
    cout << "\nAvailable Books:\n";
    while (file.read((char*)&book, sizeof(Book))) {
        book.displayBook();
    }

    file.close();
}

// Function to search for a book
void searchBook() {
    int searchID;
    cout << "Enter Book ID to search: ";
    cin >> searchID;

    ifstream file("books.dat", ios::in | ios::binary);
    if (!file) {
        cout << "No books found.\n";
        return;
    }

    Book book;
    bool found = false;
    while (file.read((char*)&book, sizeof(Book))) {
        if (book.id == searchID) {
            cout << "Book Found:\n";
            book.displayBook();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book with ID " << searchID << " not found.\n";

    file.close();
}

// Function to update book details
void updateBook() {
    int searchID;
    cout << "Enter Book ID to update: ";
    cin >> searchID;

    fstream file("books.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No books found.\n";
        return;
    }

    Book book;
    bool found = false;
    while (file.read((char*)&book, sizeof(Book))) {
        if (book.id == searchID) {
            cout << "Current Details:\n";
            book.displayBook();

            cout << "\nEnter New Details:\n";
            book.getBookDetails();

            file.seekp(-sizeof(Book), ios::cur);
            file.write((char*)&book, sizeof(Book));
            cout << "Book updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book with ID " << searchID << " not found.\n";

    file.close();
}

// Function to delete a book
void deleteBook() {
    int deleteID;
    cout << "Enter Book ID to delete: ";
    cin >> deleteID;

    ifstream file("books.dat", ios::in | ios::binary);
    ofstream tempFile("temp.dat", ios::out | ios::binary);

    if (!file) {
        cout << "No books available.\n";
        return;
    }

    Book book;
    bool found = false;
    while (file.read((char*)&book, sizeof(Book))) {
        if (book.id == deleteID) {
            cout << "Book deleted successfully!\n";
            found = true;
        } else {
            tempFile.write((char*)&book, sizeof(Book));
        }
    }

    file.close();
    tempFile.close();

    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (!found)
        cout << "Book with ID " << deleteID << " not found.\n";
}

// Main menu function
void menu() {
    int choice;
    do {
        cout << "\n--- Book Store Management ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
