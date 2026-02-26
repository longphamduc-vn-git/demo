import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;

// Lop co so: PHUKIEN (Accessory)
class PHUKIEN {
    protected String maPK;    // Ma phu kien
    protected String tenPK;   // Ten phu kien
    protected String mauSac;   // Mau sac

    public PHUKIEN() {}

    public void nhap() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhap ma phu kien: ");
        maPK = sc.nextLine();
        System.out.print("Nhap ten phu kien: ");
        tenPK = sc.nextLine();
        System.out.print("Nhap mau sac: ");
        mauSac = sc.nextLine();
    }

    public void xuat() {
        System.out.print(maPK + "\t" + tenPK + "\t" + mauSac);
    }
}

// Lop TAINGHE ke thua tu PHUKIEN
class TAINGHE extends PHUKIEN {
    private String loai;          // Loai tai nghe
    private int soLuongMua;       // So luong mua
    private double donGiaBan;     // Don gia ban

    public TAINGHE() {
        super();
    }

    @Override
    public void nhap() {
        super.nhap();
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhap loai tai nghe: ");
        loai = sc.nextLine();
        System.out.print("Nhap so luong mua: ");
        soLuongMua = sc.nextInt();
        System.out.print("Nhap don gia ban: ");
        donGiaBan = sc.nextDouble();
    }

    // Tinh thanh tien
    public double thanhTien() {
        return soLuongMua * donGiaBan;
    }

    @Override
    public void xuat() {
        super.xuat();
        System.out.println("\t" + loai + "\t" + soLuongMua + "\t" + donGiaBan + "\t" + thanhTien());
    }

    // Ham bo tro de ghi du lieu vao file de dang hon
    public String toStringToFile() {
        return maPK + "," + tenPK + "," + mauSac + "," + loai + "," + soLuongMua + "," + donGiaBan + "," + thanhTien();
    }
}

// Chuong trinh chinh quan ly danh sach tai nghe
public class QuanLyTaiNghe {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Nhap so luong tai nghe can quan ly: ");
        int n = sc.nextInt();
        
        // Khoi tao mang doi tuong
        TAINGHE[] ds = new TAINGHE[n];

        // 1. Nhap danh sach tai nghe tu ban phim
        for (int i = 0; i < n; i++) {
            System.out.println("\nNhap tai nghe thu " + (i + 1) + ":");
            ds[i] = new TAINGHE();
            ds[i].nhap();
        }

        // 2. In lai danh sach tai nghe da duoc nhap
        System.out.println("\n--- DANH SACH TAI NGHE ---");
        System.out.println("MaPK\tTenPK\tMauSac\tLoai\tSL\tDonGia\tThanhTien");
        for (int i = 0; i < n; i++) {
            ds[i].xuat();
        }

        // 4. Tinh tong tien tat ca cac tai nghe
        double tongCong = 0;
        for (int i = 0; i < n; i++) {
            tongCong += ds[i].thanhTien();
        }
        System.out.println("----------------------------------------------------------");
        System.out.println("TONG TIEN TAT CA TAI NGHE: " + tongCong);

        // 3. Luu danh sach tai nghe vao file "tainghe.dat"
        try {
            PrintWriter writer = new PrintWriter(new File("tainghe.dat"));
            for (int i = 0; i < n; i++) {
                writer.println(ds[i].toStringToFile());
            }
            writer.close();
            System.out.println("\n=> Da luu thanh cong vao file tainghe.dat");
        } catch (Exception e) {
            System.out.println("Co loi xay ra khi ghi file: " + e.getMessage());
        }
    }
}
