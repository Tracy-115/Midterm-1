#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //these are constants, which we can call back and they are fixed

class DoublyLinkedList {
private: //this is a function defined only for this class
    struct Node { //this is where variables are grouped for 
        int data; //this means data is an integer
        Node* prev; //this is a pointer to prev which is the previous node
        Node* next; //here, next means the next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //this is a constructor which is used to set initial values and these are parameters
            data = val; 
            prev = p; 
            next = n;
        }
    };
//again here, head and tail means it points to head and tail, which is first and last
    Node* head;
    Node* tail;

public: //this function can be called upon outside of this class, any function in here can be called from the main function
    DoublyLinkedList() { //this here again is a constructor 
        //assigning head and tail to nullptr means they they are empty
        head = nullptr;
        tail = nullptr;
    }
//this function is to insert values after a position as written in the name and the parameters
//also, every return statement in here will result in leaving the function
    void insert_after(int value, int position) {
        if (position < 0) { //if the position is less then zero
            cout << "Position must be >= 0." << endl; //this will be the output
            return;
        }
        //this uses heap, and it is used to create new nodes
        Node* newNode = new Node(value);
        if (!head) { //if head is empty
            head = tail = newNode; //head is equal to tail and both of these become the new node
            return;
        }

        Node* temp = head; //a new pointer is created and it is made to point the value pointer head
        for (int i = 0; i < position && temp; ++i) //for ever i, starting from 0, greater then position and temp, is increased by one, temp is pointing going to be pointing to the next node which is also known as traversing
            temp = temp->next;

        if (!temp) { //if we are at the end of temp, the text below will be outputted and the node will be deleted this is to clean up or freeing the memory 
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next; //this shows that the next pointer which the new node is pointing to will be the name as the next pointer that temp is pointing to
        newNode->prev = temp; //this is similar to the line above, but this time, the previous node from new node will have the name address as the temp

        if (temp->next) //if there is no more nodes after temp
            temp->next->prev = newNode; // this points pack the next node to the previous node and assigns it to newNode
        else
            tail = newNode; //if not, you update the tail

        temp->next = newNode; // and here, the new node gets assigned to temp's next
    }
//this function will be used to delete values 
    void delete_val(int value) {
        if (!head) return; //if the start is empty

        Node* temp = head; 
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }
//this will be used to delte positions, and the parameter is going to be the position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            } else
                temp = temp->next;
        }

        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }
//this function is going to be used to insert values to the end
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
//here, this function is used to insert values to the front, the push_back and push_front performs similarly but the difference tis that one inserts to the head as shown in the if-else statements
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
//this pop_front is used to remove the first value
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;

        delete temp;
    }
//again, pop_back is used to remove the last value, here again, this acts similarly with pop_front, but the only part is that the loops check is the front (head), and back (tails) are empty. 
//in both of these functions, we can see that memories are deleted at the end to clean up the node
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;

        delete temp;
    }
//this here is a destructor, just like how we have to delete nodes after using them, we have to clean up the object once we finish using it 
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
//just like the name, this function is to print the values 
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
//if this function is called upon, the values will be printed in reverse
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return; //if current is empty, this will be the output
        }

        while (current) { //if not, the values will be printed out in reverse
            cout << current->data << " ";
            current = current->prev; //this is what makes the data to be printed in reverse because current is pointed backwards
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    return 0;
}
