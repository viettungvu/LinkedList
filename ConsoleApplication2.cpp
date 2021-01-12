#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

class Product {
public:
    int key;
    string name;
    Product(int key = 0, string name = "") {
        this->key = key;
        this->name = name;
    }
    Product* init() {
        Product* product = new Product(0, "");
        cout << "-->ID: ";
        cin >> product->key;
        cin.ignore();
        cout << "-->Name: ";
        getline(cin, product->name);
        return product;
    }
};
class Node {
public:
    Product* data;
    Node* next;
    Node(int key = 0, string name = "") {
        data = new Product(key, name);
        next = NULL;
    }
    void ShowNode() {
        cout << setw(10) << left << "ID";		// độ rộng 5 ký tự, canh trái ID
        cout << setw(10) << left << "Name" << endl;
        cout << setfill('-');		// set fill bằng ký tự '-' thay vì ' '
        cout << setw(20) << "-" << endl;
        cout << setfill(' ');
        cout << setw(10) << left <<data->key;
        cout << setw(30) << left <<data->name << endl;
    }
};
class SLL {
public:
    Node* first;
    Node* last;
    SLL();
    SLL(int key, string name);
    SLL(Node* first);
    void init(int key, string name);
    Node* createNode(int key, string name);
    bool checkNode(Node* node);
    void insertAtBegin(int key, string name);
    void insertAtEnd(int key, string name);
    void insertAtMiddle(int key, string name, int pos);
    void removeFirst();
    void removeLast();
    void removeMiddle(int pos);
    Node* searchNode(string);
    void searchSpecial(int crite);
    void print();
    void pswap(Node* a, Node* b, Node* preva, Node* prevb);
    void selectionSort();
    Node* getTail(Node* cur);
    Node* part(Node* first, Node* last, Node** nfirst, Node** nlast);
    Node* recur(Node* first, Node* last);
    void quickSort();
    void removeSpecial(int crite);
    Node* mergeList(Node* first1, Node* first2);
    Node* splitList(int pos);
};
SLL::SLL() {
    first = NULL;
    last = NULL;
}
SLL::SLL(int key, string name) {
    Node* node = new Node(key, name);
    first = node;
    last = node;
}
SLL::SLL(Node* first) {
    this->first = first;
    this->last = first;
}
void SLL::init(int key, string name) {
    Node* node = new Node(key, name);
    first = node;
    last = node;

}
typename Node* SLL::createNode(int key, string name) {
    Node* node = new Node(key, name);
    return node;
}
bool SLL::checkNode(Node* node) {
    if (node->data->name.empty())
        return false;
    return true;
}
void SLL::insertAtBegin(int key, string name) {
    Node* node = createNode(key, name);
    if (first != NULL) {
        node->next = first;
        first = node;
    }
    else {
        first = last = node;
    }
}
void SLL::insertAtEnd(int key, string name) {
    Node* node = createNode(key, name);
    if (last != NULL) {
        last->next = node;
        last = last->next;
    }
    else {
        first = last = node;
    }
}
void SLL::insertAtMiddle(int key, string name, int pos) {
    Node* node = createNode(key, name);
    Node* curr = first;
    while (pos > 1 && curr != NULL) {
        curr = curr->next;
        pos--;
    }
    if (pos == 1) {
        node->next = curr->next;
        curr->next = node;
    }

}
void SLL::removeFirst() {
    if (first == last) {
        delete(first);
    }
    else {
        Node* temp = first;
        first = temp->next;
        delete(temp);
    }
}
void SLL::removeLast() {
    if (first == last) {
        delete(last);
    }
    else {
        Node* temp = first;
        while (temp->next != last) {
            temp = temp->next;
        }
        delete(last);
        last = temp;
        last->next = NULL;

    }
}
void SLL::removeMiddle(int pos) {
    Node* curr = first;
    while (pos > 1 && curr != NULL) {
        curr = curr->next;
        pos--;
    }
    if (pos == 1) {
        Node* temp = curr->next;
        curr->next = temp->next;
        delete(temp);
    }
}
typename Node* SLL::searchNode(string name) {
    Node* curr = first;
    while (curr != NULL) {
        if (curr->data->name== name)
            return curr;
        else
            curr = curr->next;
    }
    return NULL;
}
void SLL::searchSpecial(int crite) {//search nodes having key < crite
    Node* curr = first;
    while (curr != NULL) {
        if (curr->data->key < crite)
            cout << curr->data->key << " " << curr->data->name << endl;
        curr = curr->next;
    }
    cout << "Success\n" << endl;
}
void SLL::print() {
    cout << setw(10) << left << "ID";
    cout << setw(10) << left << "Name" << endl;
    cout << setfill('-');
    cout << setw(20) << "-" << endl;
    cout << setfill(' ');
    Node* curr = first;
    while (curr != NULL) {
        cout << setw(10) <<left<< curr->data->key;
        cout<< setw(30) << left << curr->data->name << endl;
        curr = curr->next;
    }
}
void SLL::pswap(Node* a, Node* b, Node* preva, Node* prevb) {
    if (a != NULL && b != NULL) {
        if (preva != NULL)
            preva->next = b;
        if (prevb != NULL)
            prevb->next = a;
        Node* temp = a->next;
        a->next = b->next;
        b->next = temp;
        if (preva == NULL)
            first = b;
        else if (prevb == NULL)
            first = a;
    }
}
typename Node* SLL::getTail(Node* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}
typename Node* SLL::part(Node* first, Node* last, Node** nfirst, Node** nlast) {
    Node* pivot = last;
    Node* prev = NULL, * cur = first, * tail = pivot;
    while (cur != pivot)
    {
        if (cur->data->key < pivot->data->key)
        {
            if ((*nfirst) == NULL)
                (*nfirst) = cur;

            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*nfirst) == NULL)
        (*nfirst) = pivot;
    (*nlast) = tail;
    return pivot;
}
typename Node* SLL::recur(Node* first, Node* last) {
    if (first == NULL || first == last)
        return first;
    Node* nfirst = NULL, * nlast = NULL;
    Node* pivot = part(first, last, &nfirst, &nlast);
    if (nfirst != pivot) {
        Node* temp = nfirst;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;
        nfirst = recur(nfirst, temp);
        temp = getTail(nfirst);
        temp->next = pivot;
    }
    pivot->next = recur(pivot->next, nlast);
    return nfirst;
}
void SLL::quickSort() {
    first = recur(first, last);
}
void SLL::selectionSort() {
    Node* x = first;
    Node* prevx = NULL;
    while (x != NULL) {
        Node* prevmin = prevx;
        Node* pmin = x;
        Node* y = x->next;
        Node* prevy = x;
        while (y != NULL) {
            if (y->data->key < pmin->data->key) {
                pmin = y;
                prevmin = prevy;
            }
            prevy = y;
            y = y->next;
        }
        pswap(x, pmin, prevx, prevmin);
        prevx = pmin;
        x = pmin->next;
    }
}
void SLL::removeSpecial(int crite) {//remove nodes having key < crite
    Node* curr = first;
    while (curr != NULL) {
        if (curr->data->key < crite) {
            if (curr == first)
                removeFirst();
            else if (curr == last)
                removeLast();
            else {
                Node* temp = first;
                while (temp->next != curr)
                    temp = temp->next;
                temp->next = curr->next;
                delete(curr);
                curr = temp->next;
            }
        }
        curr = curr->next;
    }
    cout << "Success\n" << endl;
}
typename Node* SLL::mergeList(Node* first1, Node* first2) {
    Node* curr = first1;
    if (first1 != NULL && first2 != NULL) {
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = first2;
        return first1;
    }
    else if (first1 == NULL)
        return first2;
    else
        return first1;
}
typename Node* SLL::splitList(int pos) {
    Node* curr = first;
    if (curr != NULL) {
        while (pos > 1 && curr->next != NULL) {
            curr = curr->next;
            pos--;
        }
        if (pos == 1) {
            Node* newList = curr->next;
            curr->next = NULL;
            return newList;
        }
    }
    return NULL;
}
int main()
{
    SLL* a = new SLL();
    /*
    a->insertAtBegin(1, "a");
    a->insertAtEnd(2, "b");
    a->insertAtEnd(3, "c");
    a->insertAtBegin(4, "d");
    a->insertAtMiddle(5, "e", 2);
    SLL* newList = new SLL(a->splitList(3));
    a->mergeList(a->first, newList->first);
    a->print();
    a->removeSpecial(4);
    a->print();
    */

    int key = 0;
    Product* product = new Product(0, "");
    do {
        cout << "=======================&Manage Product&=======================" << endl;
        cout << "1. Create new product\n";
        cout << "2. Insert at begin\n";
        cout << "3. Insert at end\n";
        cout << "4. Insert new product at specially position\n";
        cout << "5. Remove first\n";
        cout << "6. Remove last\n";
        cout << "7. Remove product at specially position\n";
        cout << "8. Remove products have ID < x\n";
        cout << "9. Search by name\n";
        cout << "10. Quick sort\n";
        cout << "11. Selection sort\n";
        cout << "12. Merge 2 lists\n";
        cout << "13. Split list\n";
        cout << "14. Print list\n";
        cout << "0. Exit\n";
        cout << "=======================&Manage Product&=======================" << endl;
        cout << "Select function: ";
        cin >> key;
        switch (key) {
        case 0:
            break;
        case 1: {
            product = product->init();
            if (product == NULL) {
                cout << "\aFailed to create new product" << endl;
            }
            else {
                cout << "Created successful" << endl;
            }
            break;
        }
        case 2:
            if (product == NULL) {
                cout << "\aMust create new product before add to list" << endl;
            }
            else {
                a->insertAtBegin(product->key, product->name);
                cout << "Added successful" << endl;
            }
            break;
        case 3:
            if (product == NULL) {
                cout << "\aMust create new product before add to list" << endl;
            }
            else {
                a->insertAtEnd(product->key, product->name);
                cout << "Added successful" << endl;
            }
            
            break;
        case 4:
            if (product == NULL) {
                cout << "\aMust create new product before add to list" << endl;
            }
            else {
                int pos;
                cout << "Input position: ";
                cin >> pos;
                a->insertAtMiddle(product->key, product->name, pos);
                cout << "Added successful" << endl;
                break;
            }
            
        case 5:
            a->removeFirst();
            cout << "Removed" << endl;
            break;
        case 6:
            a->removeLast();
            cout << "Removed" << endl;
            break;
        case 7:
            int pos;
            cout << "Input position: ";
            cin >> pos;
            a->removeMiddle(pos);
            cout << "Removed" << endl;
            break;
        case 8:
            int id;
            cout << "ID: ";
            cin >> id;
            a->removeSpecial(id);
            cout << "Removed" << endl;
            break;
        case 9: {
            string name;
            cout << "Product name: ";
            cin >> name;  
            Node* x = a->searchNode(name);
            if(x==NULL){
                cout<<"No product with name "<<name<<" \n";
            }
            else{
                x->ShowNode();
            }
            break;
        }
        case 10:
            a->quickSort();
            cout << "Sorted with Quick Sort" << endl;
            break;
        case 11:
            a->selectionSort();
            cout << "Sorted with Selection Sort Algorithm" << endl;
            break;
        case 12: {
            SLL* newList = new SLL(a->splitList(3));
            cout << "New list splited from current list" << endl;
            newList->print();
            break;
        }  
        case 13: {
            SLL* newList1 = new SLL(a->splitList(2));
            a->mergeList(a->first, newList1->first);
            break;
        }
           
        case 14:
            a->print();
            Sleep(3000);
            break;
        default:
            cout << "Invalid function. Try again" << endl;
            break;
        }
        Sleep(1000);
        system("cls");
    } while (key != 0);
    return 0;
}