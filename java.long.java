import java.util.Scanner;

public class CUDAN {
    protected String soPhong;
    protected String tenCD;
    protected String soDT;

    public CUDAN() {}

    public void nhap() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhap so phong: ");
        soPhong = sc.nextLine();
        System.out.print("Nhap ten cu dan: ");
        tenCD = sc.nextLine();
        System.out.print("Nhap so dien thoai: ");
        soDT = sc.nextLine();
    }

    public void xuat() {
        System.out.print(soPhong + "\t" + tenCD + "\t" + soDT);
    }
}


public class HOADONDICHVU extends CUDAN {
    private String tenDV;
    private int soLuongSuDung;
    private double donGia;

    public HOADONDICHVU() {
        super();
    }

    @Override
    public void nhap() {
        super.nhap(); 
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhap ten dich vu: ");
        tenDV = sc.nextLine();
        System.out.print("Nhap so luong su dung: ");
        soLuongSuDung = sc.nextInt();
        System.out.print("Nhap don gia: ");
        donGia = sc.nextDouble();
    }

    public double thanhTien() {
        return soLuongSuDung * donGia;
    }

    @Override
    public void xuat() {
        super.xuat();
        System.out.println("\t" + tenDV + "\t" + soLuongSuDung + "\t" + donGia + "\t" + thanhTien());
    }

    // Ham bo tro de ghi du lieu vao file de dang hon
    public String toStringToFile() {
        return soPhong + "," + tenCD + "," + soDT + "," + tenDV + "," + soLuongSuDung + "," + donGia + "," + thanhTien();
    }
}

import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;

public class QuanLyChungCu {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Nhap so luong hoa don can quan ly: ");
        int n = sc.nextInt();
        
        // Khoi tao mang doi tuong
        HOADONDICHVU[] ds = new HOADONDICHVU[n];

        // 1. Nhap danh sach
        for (int i = 0; i < n; i++) {
            System.out.println("\nNhap hoa don dich vu thu " + (i + 1) + ":");
            ds[i] = new HOADONDICHVU();
            ds[i].nhap();
        }

        // 2. In danh sach va 4. Tinh tong tien
        System.out.println("\n--- DANH SACH HOA DON DICH VU ---");
        System.out.println("Phong\tTen\tSDT\tDich Vu\tSL\tDon Gia\tThanh Tien");
        double tongCong = 0;
        for (int i = 0; i < n; i++) {
            ds[i].xuat();
            tongCong += ds[i].thanhTien();
        }
        System.out.println("----------------------------------------------------------");
        System.out.println("TONG TIEN TAT CA HOA DON: " + tongCong);

        // 3. Luu danh sach vao file hoadondichvu.dat
        try {
            PrintWriter writer = new PrintWriter(new File("hoadondichvu.dat"));
            for (int i = 0; i < n; i++) {
                writer.println(ds[i].toStringToFile());
            }
            writer.close();
            System.out.println("\n=> Da luu thanh cong vao file hoadondichvu.dat");
        } catch (Exception e) {
            System.out.println("Co loi xay ra khi ghi file: " + e.getMessage());
        }
    }
}
