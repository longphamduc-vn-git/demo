#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// --- DATA STRUCTURE ---

struct HoaDonDichVu
{
    string soPhong;
    string tenCD;
    string soDT;
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

#pragma region List Operations

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

#pragma region Sample Data

void LoadSampleData(DLIST &L)
{
    // Sample data array
    HoaDonDichVu sampleData[] = {
        {"101", "Nguyen Van A", "0912345678", 50.0, 50000, 2500000},
        {"102", "Tran Thi B", "0923456789", 75.0, 50000, 3750000},
        {"103", "Le Van C", "0934567890", 60.0, 50000, 3000000},
        {"104", "Pham Thi D", "0945678901", 85.0, 50000, 4250000},
        {"105", "Hoang Van E", "0956789012", 45.0, 50000, 2250000},
        {"106", "Nguyen Thi F", "0967890123", 90.0, 50000, 4500000},
        {"107", "Vo Van G", "0978901234", 55.0, 50000, 2750000},
        {"108", "Tran Van H", "0989012345", 70.0, 50000, 3500000},
        {"109", "Le Thi I", "0990123456", 65.0, 50000, 3250000},
        {"110", "Phan Van J", "0901234567", 80.0, 50000, 4000000}
    };
    
    int n = sizeof(sampleData) / sizeof(sampleData[0]);
    
    for (int i = 0; i < n; i++)
    {
        AddLast(L, CreateNode(sampleData[i]));
    }
    
    cout << "Da load " << n << " mau hoa don!" << endl;
}

#pragma endregion Sample Data

#pragma region Requestment 1: Input Invoices

void InputInvoices(DLIST &L)
{
    int n;
    cout << "Nhap so luong hoa don: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        HoaDonDichVu x;
        cout << "\n--- Hoa don thu #" << i + 1 << " ---\n";
        cout << "So phong: ";
        cin >> x.soPhong;
        cin.ignore();
        cout << "Ten cu dan: ";
        getline(cin, x.tenCD);
        cout << "So dien thoai: ";
        cin >> x.soDT;
        cout << "Dien tich: ";
        cin >> x.dienTich;
        cout << "Don gia: ";
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
         << left << setw(10) << "Phong" << setw(20) << "Ten"
         << setw(15) << "So DT" << setw(12) << "Dien tich"
         << setw(12) << "Don gia" << setw(15) << "Thanh tien" << endl;
    cout << string(84, '-') << endl;
    Node *temp = L.Head;
    while (temp)
    {
        cout << left << setw(10) << temp->data.soPhong
             << setw(20) << temp->data.tenCD
             << setw(15) << temp->data.soDT
             << setw(12) << temp->data.dienTich
             << setw(12) << fixed << setprecision(0) << temp->data.donGiaPhi
             << setw(15) << fixed << setprecision(0) << temp->data.thanhTien
             << endl;
        temp = temp->next;
    }
}

#pragma endregion Requestment 2 : Display Invoices

#pragma region Requestment 3: Search by Name

void SearchByName(DLIST L, string name)
{
    DLIST resultList = {NULL, NULL};
    Node *temp = L.Head;
    bool found = false;
    while (temp)
    {
        if (temp->data.tenCD == name)
        {
            AddLast(resultList, CreateNode(temp->data));
            found = true;
        }
        temp = temp->next;
    }
    if (found)
    {
        cout << "\nKet qua tim kiem cho \"" << name << "\":\n";
        DisplayInvoices(resultList);
    }
    else
    {
        cout << "Khong tim thay hoa don cho cu dan: " << name << endl;
    }
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
    cout << "\nCac can ho > " << area << " m2:\n";
    Node *p = L.Head;
    while (p != NULL)
    {
        if (p->data.dienTich > area)
        {
            cout << "- Phong: " << p->data.soPhong
                 << " | Dien tich: " << p->data.dienTich << " m2\n";
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
    cout << "\nHoa don cao nhat: " << maxNode->data.tenCD << " (" << maxNode->data.thanhTien << ")" << endl;
}
#pragma endregion Requestment 7 : Max Total Amount

void ShowMenu()
{
    cout << "\n================ QUAN LY HOA DON DICH VU ================";
    cout << "\n1. Nhap hoa don";
    cout << "\n2. Hien thi tat ca hoa don";
    cout << "\n3. Tim kiem hoa don theo ten cu dan";
    cout << "\n4. Sap xep hoa don theo dien tich (Tang dan)";
    cout << "\n5. Tinh tong doanh thu";
    cout << "\n6. Hien thi cac can ho > 70m2";
    cout << "\n7. Tim hoa don co so tien cao nhat";
    cout << "\n8. Load mau du lieu";
    cout << "\n0. Thoat chuong trinh";
    cout << "\n------------------------------------------------------------";
    cout << "\nChon lua chon: ";
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
            cout << "Nhap ten cu dan can tim: ";
            cin.ignore();
            getline(cin, searchName);
            SearchByName(invoiceList, searchName);
            break;
        case 4:
            SortByAreaAscending(invoiceList);
            DisplayInvoices(invoiceList);
            break;
        case 5:
            cout << "\nTong doanh thu cua tat ca hoa don: " << fixed << setprecision(0) << CalculateTotalSum(invoiceList) << endl;
            break;
        case 6:
            DisplayLargeApartments(invoiceList);
            break;
        case 7:
            FindMaxInvoice(invoiceList);
            break;
        case 8:
            LoadSampleData(invoiceList);
            break;
        case 0:
            cout << "\nDang thoat chuong trinh... Tam biet!\n";
            break;
        default:
            cout << "\n[!] Lua chon khong hop le. Vui long thu lai.\n";
        }

        if (choice != 0)
        {
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
