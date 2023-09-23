#pragma warning(disable : 4996)
#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include<chrono>
#include<fstream>
using namespace std;
bool is_sorted_p = false;
struct date {
    int day = 0;
    int month = 0;
    int year = 0;
};
struct KH {
    char hoten[25] = "";
    char cccd[25] = "";
    int tenphongdat = 0;
    date ngaydat;
    date ngaytra;
    long thanhtien = 0;
};
struct phong {
    int tenphong;
    char loaiphong[25];
    long giaphong;
    char tinhtrang[25];
};
struct stack_KH {
    KH info;
    stack_KH* next;
};

struct stack_P {
    phong info;
    stack_P* next;
};

void init_list_kh(stack_KH*& sp) {
    sp = NULL;
}
void init_list_p(stack_P*& sp) {
    sp = NULL;
}
//xác định node đầu stack phòng
stack_P* nodedau_p(stack_P* sp_p) {
    stack_P* p = sp_p;
    while (p != NULL && p->next != NULL) p = p->next;
    return p;
}
//xác định node đầu cảu stack khách hàng
stack_KH* nodedau_kh(stack_KH* sp_kh) {
    stack_KH* p = sp_kh;
    while (p != NULL && p->next != NULL) p = p->next;
    return p;
}
//thêm khách hàng vào danh sách
void push_kh(stack_KH*& sp_kh, KH khachhang) {
    stack_KH* p = new stack_KH;
    if (p == NULL) cout << "khong du bo nho";
    else {
        p->info = khachhang;
        if (sp_kh == NULL) {
            p->next = NULL;
        }
        else p->next = sp_kh;
        sp_kh = p;
    }
}
//thêm thông tin phòng vào danh sach
void push_p(stack_P*& sp_p, phong p) {
    stack_P* q = new stack_P;
    if (q == NULL) cout << "khong du bo nho";
    else {
        q->info = p;
        if (sp_p == NULL) {
            q->next = NULL;
        }
        else q->next = sp_p;
        sp_p = q;
    }
}
//đẩy thông tin khách hàng ra khỏi danh sách
bool pop_KH(stack_KH*& sp_kh, KH& khachhang) {
    if (sp_kh == NULL) return false;
    else {
        stack_KH* p = new stack_KH;
        p = sp_kh;
        khachhang = sp_kh->info;
        sp_kh = sp_kh->next;
        delete p;
        return true;
    }
}
//đẩy thông tin phòng ra khỏi danh sách
bool pop_phong(stack_P*& sp_p, phong& ttp) {
    if (sp_p == NULL) return false;
    else {
        stack_P* p = new stack_P;
        p = sp_p;
        ttp = sp_p->info;
        sp_p = sp_p->next;
        delete p;
        return true;
    }
}
bool KiemTraNgayHopLe(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12)
        return false;

    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }
    else if (month == 2) {
        if ((leapYear && day > 29) || (!leapYear && day > 28))
            return false;
    }

    return true;
}

int TinhSoNgay(date ngay1, date ngay2) {
    std::tm t1 = { 0 };
    t1.tm_year = ngay1.year - 1900;
    t1.tm_mon = ngay1.month - 1;
    t1.tm_mday = ngay1.day;

    std::tm t2 = { 0 };
    t2.tm_year = ngay2.year - 1900;
    t2.tm_mon = ngay2.month - 1;
    t2.tm_mday = ngay2.day;

    std::time_t time1 = std::mktime(&t1);
    std::time_t time2 = std::mktime(&t2);

    if (time1 != -1 && time2 != -1) {
        const int SECONDS_PER_DAY = 60 * 60 * 24;
        std::time_t difference = std::difftime(time2, time1);
        return difference / SECONDS_PER_DAY;
    }

    return 0;
}
/*
    lựa chọn 1: quản lý phòng
*/

//nhập thông tin phòng
void nhapTTP(phong& p) {
    cout << "ten phong:";
    cin >> p.tenphong;
    if (p.tenphong > 50 && p.tenphong < 100) {
        strcpy(p.loaiphong, "phong VIP");
        p.giaphong = 500000;
    }
    else {
        strcpy(p.loaiphong, "phong thuong");
        p.giaphong = 300000;
    }
    cout << "tinh trang phong:";
    cin.ignore(256, '\n');
    cin.getline(p.tinhtrang, '\n');
}
//hiện thông tin phòng
void hienTTP(phong p, int i) {
    cout << left << setw(10) << i;
    cout << left << setw(15) << p.tenphong;
    cout << left << setw(15) << p.loaiphong;
    cout << left << setw(15) << p.giaphong;
    cout << left << setw(15) << p.tinhtrang << endl;
}
//chức năng 1: nhập danh sách phòng
void nhapList_p(stack_P*& sp_p) {
    int n;
    cout << "nhap so luong phong:";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "************************************************\n";
        cout << "nhap thong tin phong " << i + 1 << endl;
        phong p;
        nhapTTP(p);
        push_p(sp_p, p);
    }
}
//chức năng 2: hiện danh sách phòng
void tt2() {
    cout << left << setw(10) << "stt";
    cout << left << setw(15) << "ten phong";
    cout << left << setw(15) << "loai phong";
    cout << left << setw(15) << "gia phong";
    cout << left << setw(15) << "tinh trang" << endl;
}
void hienList_p(stack_P* sp_p) {
    if (sp_p == NULL) {
        cout << "danh sach rong\n";
        return;
    }
    tt2();
    int i = 1;
    stack_P* p = sp_p;
    while (p != NULL) {
        hienTTP(p->info, i++);
        p = p->next;
    }
}
//chức năng 3: tìm thông tin phòng
stack_P* timTTP(stack_P* sp_p, int phong) {
    stack_P* p = nodedau_p(sp_p);
    while (sp_p != NULL) {
        stack_P* mid = sp_p;
        int count = 0;
        while (mid != p) {
            mid = mid->next;
            count++;
        }
        count /= 2;
        mid = sp_p;
        while (count > 0) {
            mid = mid->next;
            count--;
        }
        if (mid->info.tenphong == phong)
            return mid;
        mid->info.tenphong > phong ? p = mid : sp_p = mid->next;
        if (sp_p == p) {
            if (sp_p->info.tenphong == phong)
                return sp_p;
            else
                return NULL;
        }
    }
    return NULL;
}

//chức năng 4: xóa thông tin phòng
int xoaTTP(stack_P*& sp_p, int tenphong) {
    phong ttp;
    stack_P* sp_ptg;
    init_list_p(sp_ptg);
    int kt = 0;
    while (pop_phong(sp_p, ttp)) {
        if (ttp.tenphong == tenphong) continue;
        else {
            push_p(sp_ptg, ttp);
            kt = 1;
        }
    }
    while (pop_phong(sp_ptg, ttp)) {
        push_p(sp_p, ttp);
    }
    return kt;
}
//chức năng 5: sắp xếp danh sách phòng
void sx_p(stack_P*& sp_p) {
    stack_P* sp1, * sp2;
    if (sp_p == NULL || sp_p->next == NULL) return;
    init_list_p(sp1);
    init_list_p(sp2);
    phong tag, x;
    pop_phong(sp_p, tag);
    while (pop_phong(sp_p, x)) {
        if (x.tenphong <= tag.tenphong) push_p(sp1, x);
        else push_p(sp2, x);
    }
    stack_P* temp;
    init_list_p(temp);
    sx_p(sp1);
    sx_p(sp2);
    while (pop_phong(sp1, x))  push_p(temp, x);
    push_p(temp, tag);
    while (pop_phong(sp2, x))  push_p(temp, x);
    while (pop_phong(temp, x)) push_p(sp_p, x);
    return;
}
//chức năng 6:sửa thông tin phòng
void suaTTP(stack_P* sp_p, int tenphong) {
    stack_P* p = timTTP(sp_p, tenphong);
    if (p == NULL) {
        cout << "khong co phong nao co ten " << tenphong << endl;
        return;
    }
    else {
        phong ttp;
        nhapTTP(ttp);
        p->info = ttp;
    }
}
//chức năng 7: đọc file khách hàng
int docfile_p(stack_P*& sp_p, const string& tenfile) {
    init_list_p(sp_p);
    ifstream file_p(tenfile, ios::binary);
    phong p;
    if (file_p) {
        while (file_p.read(reinterpret_cast<char*>(&p), sizeof(phong))) {
            push_p(sp_p, p);
        }
        file_p.close();
        return 1;
    }
    else {
        cout << "Khong the mo file!" << endl;
        return 0;
    }
}
//chức năng 8:ghi file khách hàng
int ghifile_p(stack_P* sp_p, const string& tenfile) {
    ofstream file_kh(tenfile, ios::binary);
    stack_P* p = sp_p;
    int kt = 0;
    while (p != NULL) {
        file_kh.write(reinterpret_cast<const char*>(&p->info), sizeof(phong));
        p = p->next;
        kt = 1;
    }
    file_kh.close();
    return kt;
}

/*
    lựa chọn 2: quản lý thông tin khách hàng
*/

//nhập thông tin khách hàng
void nhapTTKH(KH& khachhang, stack_P*& sp_p) {
    char s[25];
    if (sp_p == NULL) {
        cout << "danh sach phong trong\n";
        return;
    }
    cin.ignore();

    cout << "ma can cuoc cong dan: ";
    cin.getline(khachhang.cccd, sizeof(khachhang.cccd));

    cout << "ho ten: ";
    cin.getline(khachhang.hoten, sizeof(khachhang.hoten));

    // Ngày đặt phòng
    do {
        cout << "ngay dat:\n";
        cout << "ngay: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaydat.day = stoi(s);
        cout << "thang: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaydat.month = stoi(s);
        cout << "nam: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaydat.year = stoi(s);
    } while (!KiemTraNgayHopLe(khachhang.ngaydat.day, khachhang.ngaydat.month, khachhang.ngaydat.year));

    // Ngày trả phòng
    do {
        cout << "ngay tra:\n";
        cout << "ngay: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaytra.day = stoi(s);
        cout << "thang: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaytra.month = stoi(s);
        cout << "nam: ";
        cin.getline(s, sizeof(s));
        khachhang.ngaytra.year = stoi(s);
    } while (!KiemTraNgayHopLe(khachhang.ngaytra.day, khachhang.ngaytra.month, khachhang.ngaytra.year));

    // Tên phòng khách hàng đặt
    stack_P* p;
    do {
        if (is_sorted_p == false) sx_p(sp_p);
        cout << "nhap ten phong khach da dat: ";
        cin.getline(s, sizeof(s));
        khachhang.tenphongdat = stoi(s);
        p = timTTP(sp_p, khachhang.tenphongdat);
        if (p != NULL && strcmp(p->info.tinhtrang, "trong") == 0)
            strcpy(p->info.tinhtrang, "da dat");
    } while (p == NULL);

    // Thành tiền
    long songay = TinhSoNgay(khachhang.ngaydat, khachhang.ngaytra);
    if (songay == 0)
        khachhang.thanhtien = p->info.giaphong;
    else
        khachhang.thanhtien = songay * p->info.giaphong;
}
//hiện thông tin khách hàng
void hienTTKH(KH khachhang) {
    cout << left << setw(20) << khachhang.cccd;
    cout << left << setw(25) << khachhang.hoten;

    cout << setfill('0') << setw(2) << right << khachhang.ngaydat.day << "/";
    cout << setw(2) << right << khachhang.ngaydat.month << "/";
    cout << setfill(' ') << left << setw(11) << khachhang.ngaydat.year;

    cout << setfill('0') << setw(2) << right << khachhang.ngaytra.day << "/";
    cout << setw(2) << right << khachhang.ngaytra.month << "/";
    cout << setfill(' ') << left << setw(11) << khachhang.ngaytra.year;

    cout << left << setw(15) << khachhang.tenphongdat;
    cout << left << setw(15) << khachhang.thanhtien << endl;
}
//chức năng 1: nhập danh sách khách hàng
void nhapList_kh(stack_KH*& sp_kh, stack_P* sp_p) {
    int n;
    cout << "nhap so luong khach hang:";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "************************************************\n";
        cout << "nhap thong tin khach hang " << i + 1 << endl;
        KH khachhang;
        nhapTTKH(khachhang, sp_p);
        push_kh(sp_kh, khachhang);
    }
}
//chức năng 2:nhập danh sách khách hàng
void tt1() {
    cout << left << setw(20) << "can cuoc cong dan";
    cout << left << setw(25) << "ho ten";
    cout << left << setw(17) << "ngay dat";
    cout << left << setw(15) << "ngay tra";
    cout << left << setw(15) << "ten phong dat";
    cout << left << setw(15) << "thanh tien" << endl;
}
void hienList_kh(stack_KH* sp_kh) {
    if (sp_kh == NULL) {
        cout << "danh sach rong\n";
        return;
    }
    cout << left << setw(10) << "stt";
    tt1();
    int i = 1;
    stack_KH* p = sp_kh;
    while (p != NULL) {
        cout << left << setw(10) << i++;
        hienTTKH(p->info);
        p = p->next;
    }
}
//chức năng 3: tìm thông tin khách hàng
void sx_kh_cccd(stack_KH*& sp_kh) {
    stack_KH* sp1, * sp2;
    if (sp_kh == NULL || sp_kh->next == NULL) return;
    init_list_kh(sp1);
    init_list_kh(sp2);
    KH tag, x;
    pop_KH(sp_kh, tag);
    while (pop_KH(sp_kh, x)) {
        if (strcmp(x.cccd, tag.cccd) < 0) push_kh(sp1, x);
        else push_kh(sp2, x);
    }
    stack_KH* temp;
    init_list_kh(temp);
    sx_kh_cccd(sp1);
    sx_kh_cccd(sp2);
    while (pop_KH(sp1, x))  push_kh(temp, x);
    push_kh(temp, tag);
    while (pop_KH(sp2, x))  push_kh(temp, x);
    while (pop_KH(temp, x)) push_kh(sp_kh, x);
}
stack_KH* timTTKH(stack_KH* sp_kh, char cmnd[25]) {
    stack_KH* p = nodedau_kh(sp_kh);
    while (sp_kh != NULL) {
        stack_KH* mid = sp_kh;
        int count = 0;

        while (mid != p) {
            mid = mid->next;
            count++;
        }
        count /= 2;
        mid = sp_kh;
        while (count > 0) {
            mid = mid->next;
            count--;
        }

        if (strcmp(mid->info.cccd, cmnd) == 0)
            return mid;

        strcmp(mid->info.cccd, cmnd) > 0 ? p = mid : sp_kh = mid->next;
        if (sp_kh == p) {
            if (strcmp(sp_kh->info.cccd, cmnd) == 0)
                return sp_kh;
            else
                return NULL;
        }
    }

    return NULL;
}
//chức năng 4: xóa thông tin khách hàng
int  xoaTTKH(stack_KH*& sp_kh, char cmnd[25]) {
    KH khachhang;
    stack_KH* sp_khtg;
    init_list_kh(sp_khtg);
    int kt = 0;
    while (pop_KH(sp_kh, khachhang)) {
        if (strcmp(khachhang.cccd, cmnd) == 0) continue;
        else {
            push_kh(sp_khtg, khachhang);
            kt = 1;
        }
    }
    while (pop_KH(sp_khtg, khachhang)) {
        push_kh(sp_kh, khachhang);
    }
    return kt;
}
//chức năng 5:sắp xếp danh sách khách hàng
string tenKH(string hoten) {
    string ten = "";
    int i = hoten.length() - 1;
    while (i >= 0 && hoten[i] == ' ') i--;
    while (i >= 0 && hoten[i] != ' ') i--;
    i++;

    while (i < hoten.length()) {
        ten += hoten[i];
        i++;
    }

    return ten;
}
void sx_kh(stack_KH*& sp_kh) {
    stack_KH* sp1, * sp2;
    if (sp_kh == NULL || sp_kh->next == NULL) return;
    init_list_kh(sp1);
    init_list_kh(sp2);
    KH tag, x;
    pop_KH(sp_kh, tag);
    while (pop_KH(sp_kh, x)) {
        if (tenKH(x.hoten).compare(tenKH(tag.hoten)) < 0) push_kh(sp1, x);
        else push_kh(sp2, x);
    }
    stack_KH* temp;
    init_list_kh(temp);
    sx_kh(sp1);
    sx_kh(sp2);
    while (pop_KH(sp1, x))  push_kh(temp, x);
    push_kh(temp, tag);
    while (pop_KH(sp2, x))  push_kh(temp, x);
    while (pop_KH(temp, x)) push_kh(sp_kh, x);
}

//sắp xếp danh sách khách hàng giảm dần(thuật toán chọn trực tiếp)
void swap(KH &khachhang1,KH &khachhang2){
    KH khachhangtg;
    khachhangtg = khachhang1;
    khachhang1 = khachhang2;
    khachhang2 = khachhangtg;
}
void sx(stack_KH *&sp_kh){
    if(sp_kh==NULL||sp_kh->next==NULL) return;
    stack_KH *p=sp_kh;
    while(p!=NULL){
        string min = tenKH(p->info.hoten);
        stack_KH *nodemin=p;
        stack_KH *q = p->next;
        while(q!=NULL){
            string tenkh=tenKH(q->info.hoten);
            if(tenkh.compare(min)>0){
                min=tenkh;
                nodemin = q;
            }
            q=q->next;
        }
        swap(p->info,nodemin->info);
        p=p->next;
    }
}
//chức năng 6: sửa thông tin khách hàng
void suaTTKH(stack_KH* &sp_kh, char cmnd[25], stack_P* &sp_p) {
    stack_KH* p = timTTKH(sp_kh, cmnd);
    if (p == NULL) {
        cout << "khong co khach hang nao co ma cccd nay\n";
        return;
    }
    else {
        KH khachhang;
        nhapTTKH(khachhang, sp_p);
        p->info = khachhang;
    }
}
//chức năng 7: đọc file khách hàng
int docfile_kh(stack_KH*& sp_kh, const string& tenfile) {
    init_list_kh(sp_kh);
    ifstream file_kh(tenfile, ios::binary);
    KH khachhang;
    if (file_kh) {
        while (file_kh.read(reinterpret_cast<char*>(&khachhang), sizeof(KH))) {
            push_kh(sp_kh, khachhang);

        }
        file_kh.close();
        return 1;
    }
    else {
        cout << "Khong the mo file!" << endl;
        return 0;
    }
}
//chức năng 8:ghi file khách hàng
int ghifile_kh(stack_KH* sp_kh, const string& tenfile) {
    ofstream file_kh(tenfile, ios::binary);
    stack_KH* p = sp_kh;
    int kt = 0;
    while (p != NULL) {
        file_kh.write(reinterpret_cast<const char*>(&p->info), sizeof(KH));
        p = p->next;
        kt = 1;
    }
    file_kh.close();
    return kt;
}
/*
    lựa chọn 3: báo cáo thống kê
*/

//chức năng 1:thống kê danh sách phòng còn trống
int thongkeptrong(stack_P* sp_p) {
    stack_P* p = sp_p;
    tt2();
    int kt = 0;
    int i = 1;
    while (p != NULL) {
        if (strcmp(p->info.tinhtrang, "trong") == 0) {
            hienTTP(p->info, i++);
            kt = 1;
        }
        p = p->next;
    }
    return kt;
}
//chức năng 2: tính tổng tiền khách hàng
long tongtien(stack_KH* sp_kh) {
    long sum = 0;
    stack_KH* p = sp_kh;
    while (p != NULL) {
        sum += p->info.thanhtien;
        p = p->next;
    }
    return sum;
}
//chức năng 3:thống kê doanh thu theo tháng
void doanhthuthanh(stack_KH* sp_kh, int nam, long a[]) {
    stack_KH* p = sp_kh;
    while (p != NULL) {
        if (p->info.ngaydat.year == nam) {
            switch (p->info.ngaydat.month) {
            case 1: {
                a[0] += p->info.thanhtien;
                break;
            }
            case 2: {
                a[1] += p->info.thanhtien;
                break;;
            }
            case 3: {
                a[2] += p->info.thanhtien;
                break;
            }
            case 4: {
                a[3] += p->info.thanhtien;
                break;;
            }
            case 5: {
                a[4] += p->info.thanhtien;
                break;
            }
            case 6: {
                a[5] += p->info.thanhtien;
                break;;
            }
            case 7: {
                a[6] += p->info.thanhtien;
                break;
            }
            case 8: {
                a[7] += p->info.thanhtien;
                break;;
            }
            case 9: {
                a[8] += p->info.thanhtien;
                break;
            }
            case 10: {
                a[9] += p->info.thanhtien;
                break;;
            }
            case 11: {
                a[10] += p->info.thanhtien;
                break;
            }
            case 12: {
                a[11] += p->info.thanhtien;
                break;;
            }
            }
        }
        p = p->next;
    }

}
void thongkedoanhthu(stack_KH* sp_kh, int nam) {
    long a[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    doanhthuthanh(sp_kh, nam, a);
    cout << "doanh thu trong nam " << nam << " la\n";
    cout << left << setw(10) << "thang" << left << setw(15) << "tong tien\n";
    for (int i = 0; i < 12; i++) {
        cout << left << setw(10) << i + 1;
        cout << left << setw(15) << a[i] << endl;
    }
}
//chức năng 4: đếm số phòng còn trống
int demphongtrong(stack_P* sp_p) {
    stack_P* p = sp_p;
    int dem = 0;
    while (p != NULL) {
        if (strcmp(p->info.tinhtrang, "trong") == 0)
            dem++;
        p = p->next;
    }
    return dem;
}
//chức năng 5: hiện thông tin khách hàng đặt phòng theo tháng
int hienTTKHtrongthang(stack_KH* sp_kh, int thang) {
    stack_KH* p = sp_kh;
    int kt = 0;
    tt1();
    while (p != NULL) {
        if (p->info.ngaydat.month == thang) {
            hienTTKH(p->info);
            kt = 1;
        }
        p = p->next;
    }
    return kt;
}
//chức năng 6:hiện tháng có doanh thu cao nhất
void maxdoanhthuthang(stack_KH* sp_kh, int nam) {
    long a[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    doanhthuthanh(sp_kh, nam, a);
    int vt = 0;
    int max = a[0];
    for (int i = 1; i < 12; i++) {
        if (a[i] > max) {
            vt = i;
            max = a[i];
        }
    }
    cout << "thang co doanh thu cao nhat la:" << vt + 1 << "co doanh thu " << max << endl;
}
//in thong tin phong co so luot thue lon hon x
int demluotthue(stack_KH *sp_kh,int phong, int a[],int i){
    stack_KH *p= sp_kh;
    int dem=0;
    a[i]=phong;
    while(p!=NULL){
        if(p->info.tenphongdat=phong){
            dem+=1;
        }
        p=p->next;
    }
    return dem;
}
void thongke(stack_KH *sp_kh,stack_P *sp_p,int x){
    stack_KH *p = sp_kh;
    int dem = 0;
    int i=0;
    int stt=1;
    int *a=new int[1000];
    a[0]=0;
    tt2();
    while(p!=NULL){
        int kt= 0;
        for(int j=0;j<i;j++){
            if(p->info.tenphongdat == a[j])
                kt=1;
        }
        if(kt!=0)  {
            if(demluotthue(sp_kh,p->info.tenphongdat,a,i++)>x){
                sx_p(sp_p);
                stack_P *q = timTTP(sp_p,p->info.tenphongdat);
                hienTTP(q->info,stt);
            }
        }
        p=p->next;
    }
}
//trung binh con tien cho thue
double tbcthanhtien(stack_KH *sp_kh){
    int dem=0;
    long tong=0;
    stack_KH *p=sp_kh;
    while(p!=NULL){
        tong+=p->info.thanhtien;
        dem+=1;
        p=p->next;
    }
    return (double)tong/dem;
}
void quanlyKH(int& luachon, stack_KH*& sp_kh, stack_P*& sp_p) {
    cout << "=============================QUAN LY KHACH HANG=============================\n";
    cout << "0.thoat\n";
    cout << "1.them thong tin khach hang vao danh sach khach hang\n";
    cout << "2.hien danh sach thong tin khach hang\n";
    cout << "3.tim kiem thong tin khach hang theo cccd\n";
    cout << "4.xoa thong tin 1 khach hang\n";
    cout << "5.sap xep danh sach khach hang tang dan theo ten khach hang \n";
    cout << "6.sua thong tin khach hang\n";
    cout << "7.doc thong tin tu file khach hang\n";
    cout << "8.ghi danh sach doi tuong vao file khach hang\n";
    cout << "9. sap xep danh sach khach hang giam dan\n";
    cout << "nhap lua chon cua ban:";
    cin >> luachon;
    switch (luachon)
    {
    case 1: {//nhập danh sách khách hàng
        nhapList_kh(sp_kh, sp_p);
        cout << "danh sach da nhap la:\n";
        hienList_kh(sp_kh);
        break;
    }
    case 2: {//hiện danh sách khách hàng ->ok
        cout << "danh sach khach hang hien tai la:\n";
        hienList_kh(sp_kh);
        break;
    }
    case 3: {//tim thong tin khách hàng
        sx_kh_cccd(sp_kh);
        char cmnd[25];
        cout << "nhap ma can cuoc cong dan cua khach hang:";
        cin.ignore(256, '\n');
        cin.getline(cmnd, 25);
        stack_KH* p = timTTKH(sp_kh, cmnd);
        if (p == NULL) {
            cout << "khong co khach hang nao co ma cccd " << cmnd << endl;
            break;
        }
        else {
            cout << "thong tin khach hang can tin la:\n";
            tt1();
            hienTTKH(p->info);
        }
        //system("pause");
        break;
    }
    case 4: { // xóa thông tin khách hàng
        sx_kh_cccd(sp_kh);
        char cmnd[25];
        cout << "nhap ma can cuoc cong dan:";
        cin.ignore(256, '\n');
        cin.getline(cmnd, '\n');
        cin.ignore(256, '\n');
        int kt = xoaTTKH(sp_kh, cmnd);
        if (kt == 0) cout << "xoa that bai";
        else {
            cout << "xoa thanh cong\n";
            cout << "danh sach khach hang sau khi xoa la:\n";
            hienList_kh(sp_kh);
        }
        break;
    }
    case 5: {//sắp xếp danh sách khách hàng
        sx_kh(sp_kh);
        cout << "danh sach sau khi sap xep la:\n";
        hienList_kh(sp_kh);
        break;
    }
    case 6: {//sửa thông tin khách hàng
        if (sp_p == NULL) {
            cout << "danh sach phong rong\n";
            break;
        }
        sx_kh_cccd(sp_kh);
        char cmnd[25];
        cout << "nhap ma can cuoc cong dan cua khach hang:";
        cin.ignore(256, '\n');
        cin.getline(cmnd, 25);
        suaTTKH(sp_kh, cmnd, sp_p);
        cout << "danh sach khach hang sau khi sua thong tin cua khach hang " << cmnd << "la:\n";
        hienList_kh(sp_kh);
        break;
    }
    case 7: {//đọc file khách hàng
        string tenfile;
        cout << "nhap ten file khach hang can doc:";
        cin.ignore(256, '\n');
        getline(cin, tenfile);
        if (docfile_kh(sp_kh, tenfile) == 1) {
            cout << "danh sach khach hang doc duoc la:\n";
            hienList_kh(sp_kh);
        }
        else cout << "doc file that bai\n";
        break;
    }
    case 8: {//ghi file khách hàng
        string tenfile;
        cout << "nhap ten file khach hang can ghi:";
        cin.ignore(256, '\n');
        getline(cin, tenfile);
        if (ghifile_kh(sp_kh, tenfile) == 1) cout << "ghi file thanh cong\n";
        else cout << "ghi file that bai\n";
        break;
    }
    case 9:{
        sx(sp_kh);
        cout<<"danh sach sau khi sap xep la:\n";
        hienList_kh(sp_kh);
        break;
    }
    }
}
void quanlyP(int& luachon, stack_P*& sp_p) {
    cout << "=============================QUAN LY PHONG=============================\n";
    cout << "0.thoat\n";
    cout << "1.them thong tin  vao danh sach phong\n";
    cout << "2.hien danh sach thong tin phong\n";
    cout << "3.tim kiem thong tin phong theo ten phong\n";
    cout << "4.xoa thong tin 1 phong\n";
    cout << "5.sap xep danh sach phong theo ten phong\n";
    cout << "6.sua thong tin phong\n";
    cout << "7.doc thong tin tu file phong\n";
    cout << "8.ghi thong tin vao file phong\n";
    cout << "nhap lua chon cua ban:";
    cin >> luachon;
    switch (luachon)
    {
    case 1: {//nhập danh sách phòng ->ok
        nhapList_p(sp_p);
        cout << "danh sach da nhap la:\n";
        hienList_p(sp_p);
        is_sorted_p = false;
        break;
    }

    case 2: {//hiện danh sách phòng ->ok
        cout << "danh sach phong hien tai la:\n";
        hienList_p(sp_p);
        break;
    }

    case 3: {//tìm thông tin phòng ->ok
        if (!is_sorted_p) {
            cout << "hay sap xep danh sach truoc\n";
            break;
        }
        int i = 1;
        int tenphong;
        cout << "nhap ten phong:";
        cin >> tenphong;
        stack_P* p = timTTP(sp_p, tenphong);
        if (p == NULL) {
            cout << "khong co phong nao co ten " << tenphong << endl;
            break;
        }
        else {
            cout << "thong tin phong can tim la:\n";
            tt2();
            hienTTP(p->info, i++);
        }
        break;
    }

    case 4: {//xóa thong tin phòng ->ok
        int tenphong;
        cout << "nhap ten phong:";
        cin >> tenphong;
        int kt = xoaTTP(sp_p, tenphong);
        if (kt == 0) cout << "xoa that bai";
        else {
            cout << "xoa thanh cong\n";
            cout << "danh sach phong sau khi xoa la:\n";
            hienList_p(sp_p);
        }
        break;
    }

    case 5: {// sắp xếp danh sách phòng ->ok
        sx_p(sp_p);
        is_sorted_p = true;
        cout << "danh sach sau khi sap xep la:\n";
        hienList_p(sp_p);
        break;
    }
    case 6: {// sửa thông tin phòng ->ok
        if (!is_sorted_p) {
            cout << "hay sap xep danh sach truoc\n";
            break;
        }
        int tenphong;
        cout << "nhap ten phong:";
        cin >> tenphong;
        suaTTP(sp_p, tenphong);
        cout << "danh sach phong sau khi sua la:\n";
        hienList_p(sp_p);
        is_sorted_p = false;
        break;
    }
    case 7: {//đọc file phòng
        string tenfile;
        cout << "nhap ten file phong can doc:";
        cin.ignore(256, '\n');
        getline(cin, tenfile);
        if (docfile_p(sp_p, tenfile) == 1) {
            cout << "doc file thanh cong\n";
            cout << "thong tin doc duoc tu file la:\n";
            hienList_p(sp_p);
        }
        break;
    }
    case 8: {//ghi file phòng ->ok
        string tenfile;
        cout << "nhap ten file phong can ghi:";
        cin.ignore(256, '\n');
        getline(cin, tenfile);
        if (ghifile_p(sp_p, tenfile) == 1) cout << "ghi file thanh cong\n";
        else cout << "ghi gile that bai\n";
        break;
    }
    }

}
void thongke_baocao(int& luachon, stack_KH* sp_kh, stack_P* sp_p) {
    cout << "=============================THONG KE BAO CAO=============================\n";
    cout << "0.thoat\n";
    cout << "1.thong ke danh sach phong con trong\n";
    cout << "2.tinh tong thanh tien cua tat ca khach hang\n";
    cout << "3.thong ke doanh thu theo thang trong nam\n";
    cout << "4.dem so phong con trong\n";
    cout << "5.hien thong tin khach hang dat phong theo thang\n";
    cout << "6.hien thang co doanh thu nhieu nhat\n";
    cout << "7. trung binh cong thanh tien\n";
    cout<<"8.thong ke\n";
    cout << "nhap lua chon cua ban:";
    cin >> luachon;
    switch (luachon) {
    case 1: {// thống kê phòng còn trống ->ok
        int kt = thongkeptrong(sp_p);
        if (kt == 0) cout << "khong co phong nao con trong\n";
        break;
    }
    case 2: {//tổng thành tiền của tất cả khách hàng
        cout << "tong thanh tien cua tat ca khach hang la :" << tongtien(sp_kh) << endl;
        break;
    }
    case 3: {//thống kế doanh thu 12 tháng trong 1 nam
        int nam;
        cout << "nhap nam can thong ke:";
        cin >> nam;
        thongkedoanhthu(sp_kh, nam);
        break;
    }
    case 4: {//đếm số phòng còn trống ->ok
        cout << "so phong con trong la:" << demphongtrong(sp_p) << endl;
        break;
    }
    case 5: {// thống kê thông tin khách hàng đặt phòng trong 1 tháng
        int thang;
        cout << "nhap thang can thong ke:";
        cin >> thang;
        int kt = hienTTKHtrongthang(sp_kh, thang);
        if (kt == 0)
            cout << "khong co khach hang nao dat phong trong thang " << thang << endl;
        break;
    }
    case 6: {// báo cáo doanh thu tháng cao nhất trong 1 năm
        int nam;
        cout << "nhap nam can bao cao:";
        cin >> nam;
        maxdoanhthuthang(sp_kh, nam);
        break;
    }
    case 7:{
        cout<<setprecision(15)<<"trung binh con thanh tien cua khach hang la: " <<tbcthanhtien(sp_kh);
        break;
    }
    case 8:{
        int x;
        cout<<"nhap so luot:";
        cin>>x;
        cout<<"danh sach phong co so luot thue lon hon "<<x<<" la:\n";
        thongke(sp_kh,sp_p,x);
        break;
    }
    }

}
void menu(int& luachon) {
    cout << "==================================MENU==================================";
    cout << "\n0.ket thuc chuong trinh\n";
    cout << "1.quan ly phong\n";
    cout << "2.quan ly khach hang\n";
    cout << "3.thong ke, bao cao\n";
    cout << "nhap lua chon cua ban:";
    cin >> luachon;
    //cout << "*******************************************************************************\n";
}
int main() {
    stack_P* sp_p;
    stack_KH* sp_kh;
    init_list_kh(sp_kh);
    init_list_p(sp_p);
    int luachon = 0;
    while (true) {
        menu(luachon);
        if (luachon == 0) break;
        switch (luachon) {
        case 1: {
            int luachon1;
            while (true) {
                quanlyP(luachon1, sp_p);
                if (luachon1 == 0) break;
            }
            break;
        }
        case 2: {
            int luachon2;
            while (true) {
                quanlyKH(luachon2, sp_kh, sp_p);
                if (luachon2 == 0) break;
            }
            break;
        }
        case 3: {
            int luachon3;
            while (true) {
                thongke_baocao(luachon3, sp_kh, sp_p);
                if (luachon3 == 0) break;
            }
            break;
        }

        }
    }
}


