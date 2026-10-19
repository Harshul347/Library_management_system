
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;
    string borrower;
    Book* next;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
        borrower = "";
        next = nullptr;
    }
};

class Library {
private:
    Book* head;

    Book* findBook(int id) {
        Book* temp = head;

        while (temp != nullptr) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }

        return nullptr;
    }

public:
    Library() {
        head = nullptr;
    }

    // 1. Add a new book
    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        if (findBook(id) != nullptr) {
            cout << "Book ID already exists!\n";
            return;
        }

        cout << "Enter Book Title: ";
        getline(cin >> ws, title);

        cout << "Enter Author Name: ";
        getline(cin >> ws, author);

        Book* newBook = new Book(id, title, author);

        if (head == nullptr) {
            head = newBook;
        } else {
            Book* temp = head;

            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newBook;
        }

        cout << "Book added successfully!\n";
    }

    // 2. Display all books
    void displayBooks() {
        if (head == nullptr) {
            cout << "\nLibrary is empty!\n";
            return;
        }

        Book* temp = head;

        cout << "\n========== LIBRARY BOOKS ==========\n";

        while (temp != nullptr) {
            cout << "\nBook ID : " << temp->id;
            cout << "\nTitle   : " << temp->title;
            cout << "\nAuthor  : " << temp->author;
            cout << "\nStatus  : "
                 << (temp->issued ? "Issued" : "Available");

            if (temp->issued)
                cout << "\nBorrower: " << temp->borrower;

            cout << "\n-----------------------------------\n";

            temp = temp->next;
        }
    }

    // 3. Search a book
    void searchBook() {
        int id;

        cout << "\nEnter Book ID to search: ";
        cin >> id;

        Book* book = findBook(id);

        if (book == nullptr) {
            cout << "Book not found!\n";
            return;
        }

        cout << "\nBook Found!\n";
        cout << "ID     : " << book->id << '\n';
        cout << "Title  : " << book->title << '\n';
        cout << "Author : " << book->author << '\n';
        cout << "Status : "
             << (book->issued ? "Issued" : "Available") << '\n';

        if (book->issued)
            cout << "Borrower: " << book->borrower << '\n';
    }

    // 4. Issue a book
    void issueBook() {
        int id;
        string name;

        cout << "\nEnter Book ID to issue: ";
        cin >> id;

        Book* book = findBook(id);

        if (book == nullptr) {
            cout << "Book not found!\n";
            return;
        }

        if (book->issued) {
            cout << "Book is already issued!\n";
            return;
        }

        cout << "Enter Borrower's Name: ";
        getline(cin >> ws, name);

        book->issued = true;
        book->borrower = name;

        cout << "Book issued successfully to "
             << name << "!\n";
    }

    // 5. Return a book
    void returnBook() {
        int id;

        cout << "\nEnter Book ID to return: ";
        cin >> id;

        Book* book = findBook(id);

        if (book == nullptr) {
            cout << "Book not found!\n";
            return;
        }

        if (!book->issued) {
            cout << "This book has not been issued.\n";
            return;
        }

        book->issued = false;
        book->borrower = "";

        cout << "Book returned successfully!\n";
    }

    // 6. Delete a book
    void deleteBook() {
        int id;

        cout << "\nEnter Book ID to delete: ";
        cin >> id;

        Book* temp = head;
        Book* prev = nullptr;

        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Book not found!\n";
            return;
        }

        if (temp->issued) {
            cout << "Cannot delete an issued book!\n";
            return;
        }

        if (prev == nullptr)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;

        cout << "Book deleted successfully!\n";
    }

    // 7. Sort books by ID
    void sortBooks() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough books to sort.\n";
            return;
        }

        bool swapped;

        do {
            swapped = false;
            Book** ptr = &head;

            while (*ptr != nullptr && (*ptr)->next != nullptr) {
                Book* first = *ptr;
                Book* second = first->next;

                if (first->id > second->id) {
                    first->next = second->next;
                    second->next = first;
                    *ptr = second;
                    swapped = true;
                }

                ptr = &((*ptr)->next);
            }
        } while (swapped);

        cout << "Books sorted by ID successfully!\n";
    }

    // 8. Count books
    void countBooks() {
        int total = 0, issued = 0, available = 0;
        Book* temp = head;

        while (temp != nullptr) {
            total++;

            if (temp->issued)
                issued++;
            else
                available++;

            temp = temp->next;
        }

        cout << "\nTotal Books     : " << total;
        cout << "\nIssued Books    : " << issued;
        cout << "\nAvailable Books : " << available << '\n';
    }

    // Free dynamically allocated memory
    ~Library() {
        while (head != nullptr) {
            Book* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n\n================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Delete Book";
        cout << "\n7. Sort Books by ID";
        cout << "\n8. Count Books";
        cout << "\n0. Exit";
        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            continue;
        }

        switch (choice) {
            case 1:
                lib.addBook();
                break;

            case 2:
                lib.displayBooks();
                break;

            case 3:
                lib.searchBook();
                break;

            case 4:
                lib.issueBook();
                break;

            case 5:
                lib.returnBook();
                break;

            case 6:
                lib.deleteBook();
                break;

            case 7:
                lib.sortBooks();
                break;

            case 8:
                lib.countBooks();
                break;

            case 0:
                cout << "Thank you for using the library system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
