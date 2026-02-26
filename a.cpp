#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

using namespace std;

// --- DATA STRUCTURE ---

struct HoaDonDichVu
{
    string soPhong;
    string tenCD;
    string soDT; // -- Phone number
    double dienTich;
    double donGiaPhi;
    double thanhTien;
};

struct Node
{
    HoaDonDichVu data;
    Node *next;
    Node *prev;
};

struct DLIST
{
    Node *Head;
    Node *Tail;
};

Node *CreateNode(HoaDonDichVu x)
{
    Node *p = new Node;
    p->data = x;
    p->next = p->prev = NULL;
    return p;
}

#pragma List Operations

void InitList(DLIST &L) {
    L.Head = L.Tail = NULL;
}

bool AddFirst(DLIST &L, Node *newNode)
{
    if (newNode == NULL)
        return false;
    if (L.Head == NULL)
    {
        L.Head = L.Tail = newNode;
    }
    else
    {
        newNode->next = L.Head;
        L.Head->prev = newNode;
        L.Head = newNode;
    }
    return true;
}

bool AddLast(DLIST &L, Node *newNode)
{
    if (newNode == NULL)
        return false;
    if (L.Head == NULL)
    {
        L.Head = L.Tail = newNode;
    }
    else
    {
        L.Tail->next = newNode;
        newNode->prev = L.Tail;
        L.Tail = newNode;
    }
    return true;
}

bool AddAfter(DLIST &L, Node *q, Node *newNode)
{
    if (q == NULL || newNode == NULL)
        return false;
    Node *p = q->next;
    newNode->next = p;
    newNode->prev = q;
    q->next = newNode;
    if (p != NULL)
        p->prev = newNode;
    if (q == L.Tail)
        L.Tail = newNode;
    return true;
}

bool AddBefore(DLIST &L, Node *q, Node *newNode)
{
    if (q == NULL || newNode == NULL)
        return false;
    Node *p = q->prev;
    newNode->next = q;
    newNode->prev = p;
    q->prev = newNode;
    if (p != NULL)
        p->next = newNode;
    if (q == L.Head)
        L.Head = newNode;
    return true;
}

bool RemoveHead(DLIST &L)
{
    if (L.Head == NULL)
        return false;
    Node *p = L.Head;
    L.Head = L.Head->next;
    if (L.Head != NULL)
        L.Head->prev = NULL;
    else
        L.Tail = NULL;
    delete p;
    return true;
}

bool RemoveAfter(DLIST &L, Node *q)
{
    if (q == NULL || q->next == NULL)
        return false;
    Node *p = q->next;
    q->next = p->next;
    if (p->next != NULL)
        p->next->prev = q;
    else
        L.Tail = q;
    delete p;
    return true;
}

bool RemoveBefore(DLIST &L, Node *q)
{
    if (q == NULL || q->prev == NULL)
        return false;
    Node *p = q->prev;
    q->prev = p->prev;
    if (p->prev != NULL)
        p->prev->next = q;
    else
        L.Head = q;
    delete p;
    return true;
}

#pragma endregion List Operations

#pragma region Requestment 1: Input Invoices

void InputInvoices(DLIST &L)
{
    int n;
    cout << "Enter number of invoices: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        HoaDonDichVu x;
        cout << "\n--- Invoice #" << i + 1 << " ---\n";
        cout << "Room Number: ";
        cin >> x.soPhong;
        cin.ignore();
        cout << "Resident Name: ";
        getline(cin, x.tenCD);
        cout << "Phone: ";
        cin >> x.soDT;
        cout << "Area: ";
        cin >> x.dienTich;
        cout << "Price: ";
        cin >> x.donGiaPhi;
        x.thanhTien = x.dienTich * x.donGiaPhi;
        AddLast(L, CreateNode(x));
    }
}

#pragma endregion Requestment 1 : Input Invoices
#pragma region Requestment 2: Display Invoices

void DisplayInvoices(DLIST L)
{
    cout << "\n"
         << left << setw(10) << "Room" << setw(20) << "Name"
         << setw(15) << "Area" << setw(15) << "Total" << endl;
    cout << string(60, '-') << endl;
    Node *temp = L.Head;
    while (temp)
    {
        cout << left << setw(10) << temp->data.soPhong
             << setw(20) << temp->data.tenCD
             << setw(15) << temp->data.dienTich
             << setw(15) << fixed << setprecision(0) << temp->data.thanhTien
             << endl;
        temp = temp->next;
    }
}

#pragma endregion Requestment 2 : Display Invoices

#pragma region Requestment 3: Search by Name

void SearchByName(DLIST L, string name)
{
    Node *temp = L.Head;
    bool found = false;
    while (temp)
    {
        if (temp->data.tenCD == name)
        {
            cout << "Found: Room " << temp->data.soPhong << " | Amount: " << temp->data.thanhTien << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "No invoice found for resident: " << name << endl;
}
#pragma endregion Requestment 3 : Search by Name

#pragma region Requestment 4: Sort by Area (Ascending)

void SortByAreaAscending(DLIST &L)
{
    for (Node *p = L.Head; p != NULL; p = p->next)
    {
        for (Node *q = p->next; q != NULL; q = q->next)
        {
            if (p->data.dienTich > q->data.dienTich)
            {
                HoaDonDichVu temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}


#pragma endregion Requestment 4 : Sort by Area(Ascending)

#pragma region Requestment 5: Total Revenue

double CalculateTotalSum(DLIST L)
{
    double sum = 0;
    Node *p = L.Head;
    while (p != NULL)
    {
        sum += p->data.thanhTien;
        p = p->next;
    }
    return sum;
}
#pragma endregion Requestment 5 : Total Revenue

#pragma region Requestment 6: Apartments > 70m2

void DisplayLargeApartments(DLIST L, double area = 70)
{
    cout << "\nApartments > " << area << " m2:\n";
    Node *p = L.Head;
    while (p != NULL)
    {
        if (p->data.dienTich > area)
        {
            cout << "- Room: " << p->data.soPhong
                 << " | Area: " << p->data.dienTich << " m2\n";
        }
        p = p->next;
    }
}

#pragma endregion Requestment 6 : Apartments> 70m2

#pragma region Requestment 7: Max Total Amount

void FindMaxInvoice(DLIST L)
{
    if (L.Head == NULL)
        return;
    Node *p = L.Head;
    Node *maxNode = p;
    while (p != NULL)
    {
        if (p->data.thanhTien > maxNode->data.thanhTien)
            maxNode = p;
        p = p->next;
    }
    cout << "\nMax Invoice: " << maxNode->data.tenCD << " (" << maxNode->data.thanhTien << ")" << endl;
}
#pragma endregion Requestment 7 : Max Total Amount

void ShowMenu()
{
    cout << "\n================ SERVICE INVOICE MANAGEMENT ================";
    cout << "\n1. Input Invoices";
    cout << "\n2. Display All Invoices";
    cout << "\n3. Search Invoice by Resident Name";
    cout << "\n4. Sort Invoices by Area (Ascending)";
    cout << "\n5. Calculate Total Revenue";
    cout << "\n6. Display Apartments > 70m2";
    cout << "\n7. Find Invoice with Max Amount";
    cout << "\n0. Exit Program";
    cout << "\n------------------------------------------------------------";
    cout << "\nChoose an option: ";
}

int main()
{
    DLIST invoiceList = {NULL, NULL};
    int choice;
    string searchName;

    do
    {
        ShowMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice)
        {
        case 1:
            InputInvoices(invoiceList);
            break;
        case 2:
            DisplayInvoices(invoiceList);
            break;
        case 3:
            cout << "Enter resident name to search: ";
            cin.ignore();
            getline(cin, searchName);
            SearchByName(invoiceList, searchName);
            break;
        case 4:
            SortByAreaAscending(invoiceList);
            DisplayInvoices(invoiceList);
            break;
        case 5:
            cout << "\nTotal Revenue of all invoices: " << fixed << setprecision(0) << CalculateTotalSum(invoiceList) << endl;
            break;
        case 6:
            DisplayLargeApartments(invoiceList);
            break;
        case 7:
            FindMaxInvoice(invoiceList);
            break;
        case 0:
            cout << "\nExiting program... Goodbye!\n";
            break;
        default:
            cout << "\n[!] Invalid choice. Please try again.\n";
        }

        if (choice != 0)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
