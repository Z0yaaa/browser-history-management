#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node 
{
    string url;
    Node* prev;
    Node* next;

    Node(string u) {
        url = u;
        prev = nullptr;
        next = nullptr;
    }
};

class History 
{
private:
    Node* head;
    Node* tail;
    Node* current;

    void deleteForward(Node* start) {
        if (start == nullptr) return;

        Node* temp = start;
        while (temp != nullptr) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
    }

public:
    History() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~History() {
        deleteForward(head);
    }

    void visit(string url) {
        Node* newPage = new Node(url);

        if (head == nullptr) {
            head = tail = current = newPage;
        } 
        else {
            if (current->next != nullptr) {
                deleteForward(current->next);
                current->next = nullptr;
            }

            current->next = newPage;
            newPage->prev = current;
            tail = newPage;
            current = newPage;
        }

        cout << "Visited: " << url << endl;
    }

    void back() {
        if (current == nullptr || current->prev == nullptr) {
            cout << "No previous page." << endl;
            return;
        }
        current = current->prev;
        cout << "Back to: " << current->url << endl;
    }

    void forward() {
        if (current == nullptr || current->next == nullptr) {
            cout << "No forward page." << endl;
            return;
        }
        current = current->next;
        cout << "Forward to: " << current->url << endl;
    }

    void showHistory() {
        if (head == nullptr) {
            cout << "History is empty." << endl;
            return;
        }

        Node* temp = head;
        int index = 1;

        while (temp != nullptr) {
            if (temp == current)
                cout << index << ". " << temp->url << "  <-- current" << endl;
            else
                cout << index << ". " << temp->url << endl;

            temp = temp->next;
            index++;
        }
    }
};

void showMenu() {
    cout << endl;
    cout << endl;
    cout << "Commands:" << endl;
    cout << " visit <url>" << endl;
    cout << " back" << endl;
    cout << " forward" << endl;
    cout << " history" << endl;
    cout << " help" << endl;
    cout << " quit" << endl;
}

int main() {
    History h;
    string input;

    showMenu();

    while (true) {
        cout << "\n> ";
        getline(cin, input);

        if (input.empty()) continue;

        stringstream ss(input);
        string cmd;
        ss >> cmd;

        if (cmd == "quit") {
            cout << "See you later ~Zoya" << endl;
            break;
        }
        else if (cmd == "visit") {
            string url;
            ss >> url;

            if (url.empty())
                cout << "Please enter a URL." << endl;
            else
                h.visit(url);
        }
        else if (cmd == "back") {
            h.back();
        }
        else if (cmd == "forward") {
            h.forward();
        }
        else if (cmd == "history") {
            h.showHistory();
        }
        else if (cmd == "help") {
            showMenu();
        }
        else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
