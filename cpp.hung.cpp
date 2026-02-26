#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// --- DATA STRUCTURE ---

struct TAINGHE
{
    string MaTaiNghe;
    string TenTaiNghe;
    string NuocSX;
    double DonGia;
    int SoLuong;
    double ThanhTien;
};

struct Node
{
    TAINGHE data;
    Node *next;
    Node *prev;
};

struct DLIST
{
    Node *Head;
    Node *Tail;
};

Node *CreateNode(TAINGHE x)
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

#pragma endregion List Operations

#pragma region Requirement 1: Input Headphones List

void InputHeadphones(DLIST &L)
{
    int n;
    cout << "Nhap so luong tai nghe: ";
    cin >> n;
    
    for (int i = 0; i < n; i++)
    {
        TAINGHE x;
        cout << "\n--- Tai nghe thu #" << i + 1 << " ---\n";
        cout << "Ma tai nghe: ";
        cin >> x.MaTaiNghe;
        cin.ignore();
        cout << "Ten tai nghe: ";
        getline(cin, x.TenTaiNghe);
        cout << "Nuoc san xuat: ";
        getline(cin, x.NuocSX);
        cout << "Don gia: ";
        cin >> x.DonGia;
        cout << "So luong: ";
        cin >> x.SoLuong;
        x.ThanhTien = x.DonGia * x.SoLuong;
        AddLast(L, CreateNode(x));
    }
}

#pragma endregion Requirement 1

#pragma region Requirement 2: Display Headphones List

void DisplayHeadphones(DLIST L)
{
    cout << "\n" << left << setw(15) << "Ma tai nghe" 
         << setw(25) << "Ten tai nghe" 
         << setw(15) << "Nuoc SX" 
         << setw(12) << "Don gia" 
         << setw(10) << "So luong" 
         << setw(15) << "Thanh tien" << endl;
    cout << string(92, '-') << endl;
    
    Node *temp = L.Head;
    while (temp)
    {
        cout << left << setw(15) << temp->data.MaTaiNghe 
             << setw(25) << temp->data.TenTaiNghe 
             << setw(15) << temp->data.NuocSX 
             << setw(12) << fixed << setprecision(0) << temp->data.DonGia 
             << setw(10) << temp->data.SoLuong 
             << setw(15) << fixed << setprecision(0) << temp->data.ThanhTien 
             << endl;
        temp = temp->next;
    }
}

#pragma endregion Requirement 2

#pragma region Requirement 3: Search Headphones by Name

void SearchHeadphonesByName(DLIST L, string name)
{
    Node *temp = L.Head;
    bool found = false;
    cout << "\nKet qua tim kiem tai nghe co ten \"" << name << "\":\n";
    cout << left << setw(15) << "Ma tai nghe" 
         << setw(25) << "Ten tai nghe" 
         << setw(15) << "Nuoc SX" 
         << setw(12) << "Don gia" 
         << setw(10) << "So luong" 
         << setw(15) << "Thanh tien" << endl;
    cout << string(92, '-') << endl;
    
    while (temp)
    {
        if (temp->data.TenTaiNghe == name)
        {
            cout << left << setw(15) << temp->data.MaTaiNghe 
                 << setw(25) << temp->data.TenTaiNghe 
                 << setw(15) << temp->data.NuocSX 
                 << setw(12) << fixed << setprecision(0) << temp->data.DonGia 
                 << setw(10) << temp->data.SoLuong 
                 << setw(15) << fixed << setprecision(0) << temp->data.ThanhTien 
                 << endl;
            found = true;
        }
        temp = temp->next;
    }
    
    if (!found)
    {
        cout << "Khong tim thay tai nghe co ten: " << name << endl;
    }
}

#pragma endregion Requirement 3

#pragma region Requirement 4: Sort by Price (Ascending)

void SortByPriceAscending(DLIST &L)
{
    for (Node *p = L.Head; p != NULL; p = p->next)
    {
        for (Node *q = p->next; q != NULL; q = q->next)
        {
            if (p->data.DonGia > q->data.DonGia)
            {
                TAINGHE temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    cout << "\nDa sap xep danh sach tai nghe theo thu tu tang dan cua don gia!\n";
}

#pragma endregion Requirement 4

#pragma region Requirement 5: Calculate Total Amount

double CalculateTotalAmount(DLIST L)
{
    double sum = 0;
    Node *p = L.Head;
    while (p != NULL)
    {
        sum += p->data.ThanhTien;
        p = p->next;
    }
    return sum;
}

#pragma endregion Requirement 5

#pragma region Requirement 6: Display Headphones with Price > 250,000

void DisplayExpensiveHeadphones(DLIST L, double minPrice = 250000)
{
    cout << "\nCac tai nghe co don gia > " << fixed << setprecision(0) << minPrice << " dong:\n";
    Node *p = L.Head;
    bool found = false;
    
    while (p != NULL)
    {
        if (p->data.DonGia > minPrice)
        {
            cout << "- Ten tai nghe: " << p->data.TenTaiNghe 
                 << " | Don gia: " << fixed << setprecision(0) << p->data.DonGia << " dong\n";
            found = true;
        }
        p = p->next;
    }
    
    if (!found)
    {
        cout << "Khong co tai nghe nao co don gia > 250,000 dong!\n";
    }
}

#pragma endregion Requirement 6

#pragma region Requirement 7: Find Headphone with Highest Price

void FindMaxPriceHeadphone(DLIST L)
{
    if (L.Head == NULL)
        return;
    
    Node *p = L.Head;
    Node *maxNode = p;
    
    while (p != NULL)
    {
        if (p->data.DonGia > maxNode->data.DonGia)
            maxNode = p;
        p = p->next;
    }
    
    cout << "\nTai nghe co don gia cao nhat:\n";
    cout << left << setw(15) << "Ma tai nghe" 
         << setw(25) << "Ten tai nghe" 
         << setw(15) << "Nuoc SX" 
         << setw(12) << "Don gia" 
         << setw(10) << "So luong" 
         << setw(15) << "Thanh tien" << endl;
    cout << string(92, '-') << endl;
    cout << left << setw(15) << maxNode->data.MaTaiNghe 
         << setw(25) << maxNode->data.TenTaiNghe 
         << setw(15) << maxNode->data.NuocSX 
         << setw(12) << fixed << setprecision(0) << maxNode->data.DonGia 
         << setw(10) << maxNode->data.SoLuong 
         << setw(15) << fixed << setprecision(0) << maxNode->data.ThanhTien 
         << endl;
}

#pragma endregion Requirement 7

int main()
{
    DLIST headphoneList = {NULL, NULL};
    string searchName;
    
    // Yêu cầu 1: Nhập danh sách tai nghe từ bàn phím
    cout << "================ NHAP DANH SACH TAI NGHE ================\n";
    InputHeadphones(headphoneList);
    
    // Yêu cầu 2: In danh sách tai nghe đã nhập
    cout << "\n================ DANH SACH TAI NGHE DA NHAP ================\n";
    DisplayHeadphones(headphoneList);
    
    // Yêu cầu 3: Tìm kiếm tai nghe có tên là x nào đó
    cout << "\n================ TIM KIEM TAI NGHE THEO TEN ================\n";
    cout << "Nhap ten tai nghe can tim: ";
    cin.ignore();
    getline(cin, searchName);
    SearchHeadphonesByName(headphoneList, searchName);
    
    // Yêu cầu 4: Sắp xếp danh sách tai nghe theo thứ tự tăng dần của đơn giá
    cout << "\n================ SAP XEP THEO DON GIA (TANG DAN) ================\n";
    SortByPriceAscending(headphoneList);
    DisplayHeadphones(headphoneList);
    
    // Yêu cầu 5: Tính tổng tiền của các tai nghe đã nhập
    cout << "\n================ TINH TONG TIEN ================\n";
    cout << "Tong tien cua tat ca tai nghe: " << fixed << setprecision(0) 
         << CalculateTotalAmount(headphoneList) << " dong\n";
    
    // Yêu cầu 6: Hiển thị tên các tai nghe có đơn giá > 250.000 đồng
    cout << "\n================ TAI NGHE DON GIA > 250,000 DONG ================\n";
    DisplayExpensiveHeadphones(headphoneList);
    
    // Yêu cầu 7: Cho biết tên (hoặc thông tin đầy đủ) của tai nghe có đơn giá cao nhất
    cout << "\n================ TAI NGHE DON GIA CAO NHAT ================\n";
    FindMaxPriceHeadphone(headphoneList);
    
    cout << "\n================ KET THUC CHUONG TRINH ================\n";
    
    return 0;
}
