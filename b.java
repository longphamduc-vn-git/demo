import java.util.Scanner;

public class CUDAN {
    protected String soPhong;
    protected String tenCD;
    protected String soDT;

    public CUDAN() {}

    public void nhap() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhập số phòng: ");
        soPhong = sc.nextLine();
        System.out.print("Nhập tên cư dân: ");
        tenCD = sc.nextLine();
        System.out.print("Nhập số điện thoại: ");
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
        System.out.print("Nhập tên dịch vụ: ");
        tenDV = sc.nextLine();
        System.out.print("Nhập số lượng sử dụng: ");
        soLuongSuDung = sc.nextInt();
        System.out.print("Nhập đơn giá: ");
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

    // Hàm bổ trợ để ghi dữ liệu vào file dễ dàng hơn
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
        
        System.out.print("Nhập số lượng hóa đơn cần quản lý: ");
        int n = sc.nextInt();
        
        // Khởi tạo mảng đối tượng
        HOADONDICHVU[] ds = new HOADONDICHVU[n];

        // 1. Nhập danh sách
        for (int i = 0; i < n; i++) {
            System.out.println("\nNhập hóa đơn dịch vụ thứ " + (i + 1) + ":");
            ds[i] = new HOADONDICHVU();
            ds[i].nhap();
        }

        // 2. In danh sách và 4. Tính tổng tiền
        System.out.println("\n--- DANH SÁCH HÓA ĐƠN DỊCH VỤ ---");
        System.out.println("Phòng\tTên\tSĐT\tDịch Vụ\tSL\tĐơn Giá\tThành Tiền");
        double tongCong = 0;
        for (int i = 0; i < n; i++) {
            ds[i].xuat();
            tongCong += ds[i].thanhTien();
        }
        System.out.println("----------------------------------------------------------");
        System.out.println("TỔNG TIỀN TẤT CẢ HÓA ĐƠN: " + tongCong);

        // 3. Lưu danh sách vào file hoadondichvu.dat
        try {
            PrintWriter writer = new PrintWriter(new File("hoadondichvu.dat"));
            for (int i = 0; i < n; i++) {
                writer.println(ds[i].toStringToFile());
            }
            writer.close();
            System.out.println("\n=> Đã lưu thành công vào file hoadondichvu.dat");
        } catch (Exception e) {
            System.out.println("Có lỗi xảy ra khi ghi file: " + e.getMessage());
        }
    }
}