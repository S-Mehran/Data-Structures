#include <iostream>
#include <cstring> 
struct Book {
    int id;       
    char* title;   

    Book(int bookId, const char* bookTitle) : id(bookId) {
        title = new char[strlen(bookTitle) + 1]; 
        strcpy(title, bookTitle);               
    }

   
    ~Book() {
        delete[] title; 
    }
};

class Library {
private:
    Book** books;  
    int capacity;  
    int size;      

public:
    Library(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        books = new Book*[capacity]; 
    }

    ~Library() {
        for (int i = 0; i < size; ++i) {
            delete books[i]; 
        }
        delete[] books; 
    }

    void addBook(int id, const char* title) {
        if (size >= capacity) {
            std::cout << "Library is at full capacity. Cannot add more books." << std::endl;
            return;
        }
        books[size++] = new Book(id, title); 
    }

    void displayBooks() const {
        if (size == 0) {
            std::cout << "Library is empty." << std::endl;
        } else {
            for (int i = 0; i < size; ++i) {
                std::cout << "ID: " << books[i]->id << ", Title: " << books[i]->title << std::endl;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Library& library) {
        if (library.size == 0) {
            os << "Library is empty.";
        } else {
            for (int i = 0; i < library.size; ++i) {
                os << "ID: " << library.books[i]->id
                   << ", Title: " << library.books[i]->title << std::endl;
            }
        }
        return os;
    }
};

int main() {
    Library lib(5); 

    lib.addBook(1, "The C++ Programming Language");
    lib.addBook(2, "Clean Code");
    lib.addBook(3, "Effective Modern C++");

    std::cout << "Books in the library (using displayBooks method):" << std::endl;
    lib.displayBooks();

    std::cout << "\nBooks in the library (using overloaded << operator):" << std::endl;
    std::cout << lib;

    return 0;
}

