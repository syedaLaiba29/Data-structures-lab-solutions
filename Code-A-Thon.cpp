#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int ID;
    Student* next;

    Student(string n, int id) {
        name = n;
        ID = id;
        next = nullptr;
    }
};

class Code_of_Thon {
private:
    Student* head;

public:
    Code_of_Thon() : head(nullptr) {}

    void insertAtEnd(string n, int id) {
        Student* student = new Student(n, id);
        if (head == nullptr) {
            head = student;
            return;
        }
        Student* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = student;
    }

    bool deleteFromBeginning(string* removedName = nullptr, int* removedID = nullptr) {
        if (head == nullptr) return false;
        Student* temp = head;
        if (removedName) *removedName = temp->name;
        if (removedID) *removedID = temp->ID;
        head = head->next;
        delete temp;
        return true;
    }

    void deleteAtPosition(int position) {
        if (head == nullptr) {
            cout << "Queue is empty, nothing to delete." << endl;
            return;
        }
        if (position < 0) {
            cout << "Invalid position." << endl;
            return;
        }
        if (position == 0) { // delete first node
            Student* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Student* temp = head;
        for (int i = 0; temp != nullptr && i < position - 1; i++) {
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position is out of bounds." << endl;
            return;
        }
        Student* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
    }

    int count() {
        int count = 0;
        Student* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display() {
        Student* temp = head;
        while (temp != nullptr) {
            cout << temp->name << "(" << temp->ID << ") -> ";
            temp = temp->next;
        }
        cout << "Null" << endl;
    }
};

int main() {
    Code_of_Thon queue;
    int id, pos;
    string name;
    int choice;

    do {
        cout << "\n===== Code of Thon =====\n";
        cout << "1. Add student to queue\n";
        cout << "2. Serve student from beginning\n";
        cout << "3. A student leaves (delete at position)\n";
        cout << "4. Display queue\n";
        cout << "5. Count students in queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student's name: ";
                cin >> name;
                cout << "Enter Student's ID: ";
                cin >> id;
                queue.insertAtEnd(name, id);
                cout << name << " has been added to the queue." << endl;
                break;

            case 2: {
                string removedName;
                int removedID;
                if (queue.deleteFromBeginning(&removedName, &removedID)) {
                    cout << removedName << " (ID: " << removedID << ") has been served." << endl;
                } else {
                    cout << "Queue is empty, no student to serve." << endl;
                }
                break;
            }

            case 3:
                cout << "Enter Student's position to leave (0-based index): ";
                cin >> pos;
                queue.deleteAtPosition(pos);
                break;

            case 4:
                cout << "Current queue: ";
                queue.display();
                break;

            case 5:
                cout << "Number of students in queue: " << queue.count() << endl;
                break;

            case 6:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}