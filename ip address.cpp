#include <iostream>
using namespace std;

class Node {
public:
    string ip;
    Node* next;
    Node* prev;

    Node(string x) {
        ip = x;
        next = nullptr;
        prev = nullptr;
    }
};

class IP {
private:
    Node* head;
    Node* tail;

public:
    IP() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(string x) {
        Node* newnode = new Node(x);

        if (head == nullptr) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
    }

    void display_forward() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->ip << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void display_backward() {
        Node* curr = tail;
        while (curr != nullptr) {
            cout << curr->ip << " ";
            curr = curr->prev;
        }
        cout << endl;
    }

    void free_memory() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    IP ipList;
    string current_ip = "";
    string ip_data = "192.168.1.10,10.0.0.5,172.16.0.1,203.0.113.5,198.51.100.23,8.8.8.8,8.8.4.4,192.0.2.45,10.10.10.10,172.20.14.2,52.214.10.7,34.102.136.180,185.199.108.153,13.35.66.1,44.240.20.10";

    for (int i = 0; i < ip_data.length(); i++) {
        char ch = ip_data[i];
        if (ch == ',') {
            ipList.insert(current_ip);
            current_ip = ""; // reset to empty string
        } else {
            current_ip += ch;
        }
    }

    // Insert the last IP (after the final comma)
    if (!current_ip.empty()) {
        ipList.insert(current_ip);
    }

    cout << "Forward Traversal:" << endl;
    ipList.display_forward();

    cout << "Backward Traversal:" << endl;
    ipList.display_backward();

    ipList.free_memory();
    return 0;
}
