#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm> 
#include <sstream> //Library set waktu format tanggal
#include <ctime> //Bantu waktu
#include <iomanip> //Bantu setfill 

using namespace std;

enum Gender {
    MALE,
    FEMALE
};

enum PaymentMethod {
    BPJS,
    REGULER
};

//Kelas dasar untuk seseorang
class Person {
protected:
    int id;
    string nama;
public:
    // Constructor dari Person
    Person(int id = 0, const string& nama = "") : id(id), nama(nama) {}

    // Getter dan Setter
    int getId() const { return id; }
    string getNama() const { return nama; }
    void setId(int id) { this->id = id; }
    void setNama(const string& nama) { this->nama = nama; }

    // Virtual destructor
    virtual ~Person() {}

    // Virtual function untuk memfasilitasi override dan polymorphism
    virtual void tampilDetail() const {
        cout << "ID: " << id << ", Nama: " << nama;
    }
};

//Kelas turunan Pasien
class Pasien : public Person {
private:
    string diagnosis;
    Gender jenis_kelamin;
public:
    // Constructor dari Pasien
    Pasien(int id = 0, const string& nama = "", Gender jenis_kelamin = MALE, const string& diagnosis = "")
        : Person(id, nama), diagnosis(diagnosis), jenis_kelamin(jenis_kelamin) {}

    // Getter dan Setter
    Gender getJenisKelamin() const { return jenis_kelamin; }
    void setJenisKelamin(Gender jenis_kelamin) { this->jenis_kelamin = jenis_kelamin; }

    string getDiagnosis() const { return diagnosis; }
    void setDiagnosis(const string& diagnosis) { this->diagnosis = diagnosis; }

    // Fungsi override
    void tampilDetail() const override {
        Person::tampilDetail();
        cout << ", Jenis Kelamin: " << (jenis_kelamin == MALE ? "Laki-laki" : "Perempuan")
             << ", Diagnosis: " << diagnosis;
    }
};

//Kelas turunan Dokter
class Dokter : public Person {
private:
    string spesialisasi;
public:
    // Constructor dari Dokter
    Dokter(int id = 0, const string& nama = "", const string& spesialisasi = "")
        : Person(id, nama), spesialisasi(spesialisasi) {}

    // Getter dan Setter
    string getSpesialisasi() const { return spesialisasi; }
    void setSpesialisasi(const string& spesialisasi) { this->spesialisasi = spesialisasi; }

    // Fungsi Override
    void tampilDetail() const override {
        Person::tampilDetail();
        cout << ", Spesialisasi: " << spesialisasi;
    }
};

//Kelas turunan Karyawan
class Karyawan : public Person {
private:
    string posisi;
public:
    // Constructor dari Karyawan
    Karyawan(int id = 0, const string& nama = "", const string& posisi = "")
        : Person(id, nama), posisi(posisi) {}

    // Getter dan Setter
    string getPosisi() const { return posisi; }
    void setPosisi(const string& posisi) { this->posisi = posisi; }

    // Fungsi Override
    void tampilDetail() const override {
        Person::tampilDetail();
        cout << ", Posisi: " << posisi;
    }
};

class Ruangan {
private:
    int nomor;
    string jenis;
    bool Tersedia;
    bool VIP;
public:
    // Constructor dari Ruangan
    Ruangan(int nomor = 0, const string& jenis = "", bool Tersedia = true, bool VIP = false)
        : nomor(nomor), jenis(jenis), Tersedia(Tersedia), VIP(VIP) {}

    // Getter dan Setter
    int getNomor() const { return nomor; }
    string getJenis() const { return jenis; }
    bool isTersedia() const { return Tersedia; }
    bool isVIP() const { return VIP; }
    void setNomor(int nomor) { this->nomor = nomor; }
    void setJenis(const string& jenis) { this->jenis = jenis; }
    void setTersedia(bool Tersedia) { this->Tersedia = Tersedia; }
    void setVIP(bool VIP) { this->VIP = VIP; }
};

class PendaftaranJanjiTemu {
private:
    int id;
    int id_pasien;
    int id_dokter;
    int nomor_ruangan;
    string tanggal_waktu;
    PaymentMethod metode_pembayaran;
public:
    // Constructor dari Janji Temu
    PendaftaranJanjiTemu(int id = 0, int id_pasien = 0, int id_dokter = 0, int nomor_ruangan = 0, const string& tanggal_waktu = "", PaymentMethod metode_pembayaran = REGULER)
        : id(id), id_pasien(id_pasien), id_dokter(id_dokter), nomor_ruangan(nomor_ruangan), tanggal_waktu(tanggal_waktu), metode_pembayaran(metode_pembayaran) {}

    // Getter dan Setter
    int getId() const { return id; }
    int getIdPasien() const { return id_pasien; }
    int getIdDokter() const { return id_dokter; }
    int getNomorRuangan() const { return nomor_ruangan; }
    string getTanggalWaktu() const { return tanggal_waktu; }
    PaymentMethod getMetodePembayaran() const { return metode_pembayaran; }
    void setId(int id) { this->id = id; }
    void setIdPasien(int id_pasien) { this->id_pasien = id_pasien; }
    void setIdDokter(int id_dokter) { this->id_dokter = id_dokter; }
    void setNomorRuangan(int nomor_ruangan) { this->nomor_ruangan = nomor_ruangan; }
    void setTanggalWaktu(const string& tanggal_waktu) { this->tanggal_waktu = tanggal_waktu; }
    void setMetodePembayaran(PaymentMethod metode_pembayaran) { this->metode_pembayaran = metode_pembayaran; }
};

class ManajemenRumahSakit {
private:
    // Karena dia berdasarkan id maka menggunakan map
    unordered_map<int, Pasien> daftarPasien;
    unordered_map<int, Dokter> daftarDokter;
    unordered_map<int, Karyawan> daftarKaryawan;
    unordered_map<int, Ruangan> daftarRuangan;
    vector<PendaftaranJanjiTemu> daftarJanjiTemu;

    // Inisialisasi ruangan awal dengan 1 IGD, 3 VIP, dan 6 Reguler
    void RuanganAwal() {
        daftarRuangan[1] = Ruangan(1, "IGD", true, false);
        for (int i = 2; i <= 4; ++i) {
            daftarRuangan[i] = Ruangan(i, "VIP", true, true);
        }
        for (int i = 5; i <= 10; ++i) {
            daftarRuangan[i] = Ruangan(i, "Reguler", true, false);
        }
    }

public:
    ManajemenRumahSakit() {
        RuanganAwal(); // Inisialisasi ruangan awal
    }

    void tambahPasien(const Pasien& pasien) {
        daftarPasien[pasien.getId()] = pasien;
    }
    void hapusPasien(int id) {
        daftarPasien.erase(id);
    }
    void updatePasien(int id, const Pasien& pasien) {
        daftarPasien[id] = pasien;
    }
    
    // Search pasien berdasarkan id dan polymorphism
    Pasien* cariPasien(int id) {
        if (daftarPasien.find(id) != daftarPasien.end()) {
            daftarPasien[id].tampilDetail();
            return &daftarPasien[id];
        }
        else
        {
            return nullptr;
        }
    }

    // tampil semua pasien berdasar ID dan Objek
    void tampilPasien() const {
        for (const auto& p : daftarPasien) {
            cout << "ID: " << p.second.getId() << ", Nama: " << p.second.getNama()
                << ", Jenis Kelamin: " << (p.second.getJenisKelamin() == MALE ? "Laki-laki" : "Perempuan") << ", Diagnosis: " << p.second.getDiagnosis() << endl;
        }
        if (daftarPasien.empty())
        {
            cout << "Tidak ada data pasien" << endl;
        }
    }

    void tambahDokter(const Dokter& dokter) {
        daftarDokter[dokter.getId()] = dokter;
    }
    void hapusDokter(int id) {
        daftarDokter.erase(id);
    }
    void updateDokter(int id, const Dokter& dokter) {
        daftarDokter[id] = dokter;
    }

    //tampil dokter berdasarkan id dan polymorphism
    Dokter* cariDokter(int id) {
        if (daftarDokter.find(id) != daftarDokter.end()) {
            daftarDokter[id].tampilDetail();
            return &daftarDokter[id];
        }
        else
                {
            return nullptr;
        }
    }

    void tampilDokter() const {
        for (const auto& d : daftarDokter) {
            cout << "ID: " << d.second.getId() << ", Nama: " << d.second.getNama() << ", Spesialisasi: " << d.second.getSpesialisasi() << endl;
        }
        if (daftarDokter.empty())
        {
            cout << "Tidak ada data dokter" << endl;
        }
    }

    void tambahKaryawan(const Karyawan& karyawan) {
        daftarKaryawan[karyawan.getId()] = karyawan;
    }
    void hapusKaryawan(int id) {
        daftarKaryawan.erase(id);
    }
    void updateKaryawan(int id, const Karyawan& karyawan) {
        daftarKaryawan[id] = karyawan;
    }
    Karyawan* cariKaryawan(int id) {
        if (daftarKaryawan.find(id) != daftarKaryawan.end()) {
            daftarKaryawan[id].tampilDetail();
            return &daftarKaryawan[id];
        }
        else
        {
            return nullptr;
        }
    }
    void tampilKaryawan() const {
        for (const auto& k : daftarKaryawan) {
            cout << "ID: " << k.second.getId() << ", Nama: " << k.second.getNama() << ", Posisi: " << k.second.getPosisi() << endl;
        }
        if (daftarKaryawan.empty())
        {
            cout << "Tidak ada data karyawan" << endl;
        }
    }

    void tambahRuangan(const Ruangan& ruangan) {
        daftarRuangan[ruangan.getNomor()] = ruangan;
    }
    void hapusRuangan(int nomor) {
        daftarRuangan.erase(nomor);
    }
    void updateRuangan(int nomor, const Ruangan& ruangan) {
        daftarRuangan[nomor] = ruangan;
    }
    Ruangan* cariRuangan(int nomor) {
        if (daftarRuangan.find(nomor) != daftarRuangan.end()) {
            return &daftarRuangan[nomor];
        }
        else
        {
            return nullptr;
        }
    }
    void tampilRuangan() const {
        for (const auto& r : daftarRuangan) {
            cout << "Nomor: " << r.second.getNomor() << ", Jenis: " << r.second.getJenis()
                << ", Tersedia: " << (r.second.isTersedia() ? "Ya" : "Tidak") << ", VIP: " << (r.second.isVIP() ? "Ya" : "Tidak") << endl;
        }
        if (daftarRuangan.empty())
        {
            cout << "Tidak ada data ruangan" << endl;
        }
    }

    void tambahJanjiTemu(const PendaftaranJanjiTemu& janjiTemu) {
    // Cek apakah ruangan adalah VIP dan metode pembayaran adalah BPJS
    if (cariRuangan(janjiTemu.getNomorRuangan())->isVIP() && janjiTemu.getMetodePembayaran() == BPJS) {
        cout << "Maaf, ruangan VIP tidak dapat dibayar dengan BPJS." << endl;
        return;
    }
    daftarJanjiTemu.push_back(janjiTemu);
    cariRuangan(janjiTemu.getNomorRuangan())->setTersedia(false);
    }

    //Hapus janji Temu berdasarkan id
    void hapusJanjiTemu(int id) {
        auto it = remove_if(daftarJanjiTemu.begin(), daftarJanjiTemu.end(), [id, this](const PendaftaranJanjiTemu& jt) {
            if (jt.getId() == id) {
                cariRuangan(jt.getNomorRuangan())->setTersedia(true);
                return true;
            }
            return false;
        });
        if (it != daftarJanjiTemu.end()) {
            daftarJanjiTemu.erase(it, daftarJanjiTemu.end());
        }
    }

    //Update Janji Temu berdasarkan id
    void updateJanjiTemu(int id, const PendaftaranJanjiTemu& janjiTemu) {
    for (auto& jt : daftarJanjiTemu) {
        if (jt.getId() == id) {
            // Cek update memenuhi kondisi untuk ruangan VIP dan metode pembayaran BPJS
            Ruangan* ruangan = cariRuangan(janjiTemu.getNomorRuangan());
            if (ruangan->isVIP() && janjiTemu.getMetodePembayaran() == BPJS) {
                cout << "Maaf, ruangan VIP tidak dapat dibayar dengan BPJS." << endl;
                return;
            }
            
            // Jika tidak ada masalah, lanjutkan pembaruan
            cariRuangan(jt.getNomorRuangan())->setTersedia(true);
            jt = janjiTemu;
            cariRuangan(jt.getNomorRuangan())->setTersedia(false);
            break;
        }
    }
}

    PendaftaranJanjiTemu* cariJanjiTemu(int id) {
        for (auto& jt : daftarJanjiTemu) {
            if (jt.getId() == id) {
                return &jt;
            }
        }
        return nullptr;
    }

    void tampilJanjiTemu() const {
        for (const auto& jt : daftarJanjiTemu) {
            cout << "ID Janji Temu: " << jt.getId() << ", ID Pasien: " << jt.getIdPasien()
                << ", ID Dokter: " << jt.getIdDokter() << ", Nomor Ruangan: " << jt.getNomorRuangan()
                << ", Tanggal dan Waktu: " << jt.getTanggalWaktu()
                << ", Metode Pembayaran: " << (jt.getMetodePembayaran() == BPJS ? "BPJS" : "Reguler") << endl;
        }
        if (daftarJanjiTemu.empty())
        {
            cout << "Tidak ada data janji temu" << endl;
        }
    }
};

// Fungsi format tanggal
string getFormattedDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << setfill('0') << setw(2) << now->tm_mday << "-"
       << setfill('0') << setw(2) << (now->tm_mon + 1) << "-"
       << (now->tm_year + 1900);
    return ss.str();
}

void menuManajemenPasien(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Manajemen Pasien ===" << endl;
        cout << "1. Tambah Pasien" << endl;
        cout << "2. Hapus Pasien" << endl;
        cout << "3. Update Pasien" << endl;
        cout << "4. Cari Pasien" << endl;
        cout << "5. tampil Semua Pasien" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) break;

        int id;
        string nama;
        int jenis_kelamin;
        string diagnosis_str;
        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Pasien: ";
                cin >> id;
                cout << "Masukkan Nama Pasien: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Jenis Kelamin (0 untuk Laki-laki, 1 untuk Perempuan): ";
                cin >> jenis_kelamin;
                cout << "Masukkan Diagnosis: ";
                cin.ignore();
                getline(cin, diagnosis_str);
                mrs.tambahPasien(Pasien(id, nama, static_cast<Gender>(jenis_kelamin), diagnosis_str));
                break;
            case 2:
                cout << "Masukkan ID Pasien yang akan dihapus: ";
                cin >> id;
                mrs.hapusPasien(id);
                break;
            case 3:
                cout << "Masukkan ID Pasien yang akan diupdate: ";
                cin >> id;
                cout << "Masukkan Nama Baru: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Jenis Kelamin Baru (0 untuk Laki-laki, 1 untuk Perempuan): ";
                cin >> jenis_kelamin;
                cout << "Masukkan Diagnosis Baru: ";
                cin.ignore();
                getline(cin, diagnosis_str);
                mrs.updatePasien(id, Pasien(id, nama, static_cast<Gender>(jenis_kelamin), diagnosis_str));
                break;
            case 4:
                cout << "Masukkan ID Pasien yang akan dicari: ";
                cin >> id;
                if (auto* pasien = mrs.cariPasien(id)) {
                    cout << "\n";
                } else {
                    cout << "Pasien tidak ditemukan." << endl;
                }
                break;
            case 5:
                mrs.tampilPasien();
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

void menuManajemenDokter(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Manajemen Dokter ===" << endl;
        cout << "1. Tambah Dokter" << endl;
        cout << "2. Hapus Dokter" << endl;
        cout << "3. Update Dokter" << endl;
        cout << "4. Cari Dokter" << endl;
        cout << "5. tampil Semua Dokter" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) break;

        int id;
        string nama, spesialisasi;
        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Dokter: ";
                cin >> id;
                cout << "Masukkan Nama Dokter: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Spesialisasi: ";
                getline(cin, spesialisasi);
                mrs.tambahDokter(Dokter(id, nama, spesialisasi));
                break;
            case 2:
                cout << "Masukkan ID Dokter yang akan dihapus: ";
                cin >> id;
                mrs.hapusDokter(id);
                break;
            case 3:
                cout << "Masukkan ID Dokter yang akan diupdate: ";
                cin >> id;
                cout << "Masukkan Nama Baru: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Spesialisasi Baru: ";
                getline(cin, spesialisasi);
                mrs.updateDokter(id, Dokter(id, nama, spesialisasi));
                break;
            case 4:
                cout << "Masukkan ID Dokter yang akan dicari: ";
                cin >> id;
                if (auto* dokter = mrs.cariDokter(id)) {
                    cout << "\n";
                } else {
                    cout << "Dokter tidak ditemukan." << endl;
                }
                break;
            case 5:
                mrs.tampilDokter();
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

void menuManajemenKaryawan(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Manajemen Karyawan ===" << endl;
        cout << "1. Tambah Karyawan" << endl;
        cout << "2. Hapus Karyawan" << endl;
        cout << "3. Update Karyawan" << endl;
        cout << "4. Cari Karyawan" << endl;
        cout << "5. tampil Semua Karyawan" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) break;

        int id;
        string nama, posisi;
        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Karyawan: ";
                cin >> id;
                cout << "Masukkan Nama Karyawan: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Posisi: ";
                getline(cin, posisi);
                mrs.tambahKaryawan(Karyawan(id, nama, posisi));
                break;
            case 2:
                cout << "Masukkan ID Karyawan yang akan dihapus: ";
                cin >> id;
                mrs.hapusKaryawan(id);
                break;
            case 3:
                cout << "Masukkan ID Karyawan yang akan diupdate: ";
                cin >> id;
                cout << "Masukkan Nama Baru: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Posisi Baru: ";
                getline(cin, posisi);
                mrs.updateKaryawan(id, Karyawan(id, nama, posisi));
                break;
            case 4:
                cout << "Masukkan ID Karyawan yang akan dicari: ";
                cin >> id;
                if (auto* karyawan = mrs.cariKaryawan(id)) {
                    cout << "\n";
                } else {
                    cout << "Karyawan tidak ditemukan." << endl;
                }
                break;
            case 5:
                mrs.tampilKaryawan();
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

void menuManajemenRuangan(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Manajemen Ruangan ===" << endl;
        cout << "1. Tambah Ruangan" << endl;
        cout << "2. Hapus Ruangan" << endl;
        cout << "3. Update Ruangan" << endl;
        cout << "4. Cari Ruangan" << endl;
        cout << "5. tampil Semua Ruangan" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) break;

        int nomor;
        string jenis;
        bool Tersedia, VIP;
        switch (pilihan) {
            case 1:
                cout << "Masukkan Nomor Ruangan: ";
                cin >> nomor;
                cout << "Masukkan Jenis Ruangan: ";
                cin.ignore();
                getline(cin, jenis);
                cout << "Apakah ruangan Tersedia? (1 untuk Ya, 0 untuk Tidak): ";
                cin >> Tersedia;
                cout << "Apakah ruangan VIP? (1 untuk Ya, 0 untuk Tidak): ";
                cin >> VIP;
                mrs.tambahRuangan(Ruangan(nomor, jenis, Tersedia, VIP));
                break;
            case 2:
                cout << "Masukkan Nomor Ruangan yang akan dihapus: ";
                cin >> nomor;
                mrs.hapusRuangan(nomor);
                break;
            case 3:
                cout << "Masukkan Nomor Ruangan yang akan diupdate: ";
                cin >> nomor;
                cout << "Masukkan Jenis Baru: ";
                cin.ignore();
                getline(cin, jenis);
                cout << "Apakah ruangan Tersedia? (1 untuk Ya, 0 untuk Tidak): ";
                cin >> Tersedia;
                cout << "Apakah ruangan VIP? (1 untuk Ya, 0 untuk Tidak): ";
                cin >> VIP;
                mrs.updateRuangan(nomor, Ruangan(nomor, jenis, Tersedia, VIP));
                break;
            case 4:
                cout << "Masukkan Nomor Ruangan yang akan dicari: ";
                cin >> nomor;
                if (auto* ruangan = mrs.cariRuangan(nomor)) {
                    cout << "Nomor: " << ruangan->getNomor() << ", Jenis: " << ruangan->getJenis()
                        << ", Tersedia: " << (ruangan->isTersedia() ? "Ya" : "Tidak")
                        << ", VIP: " << (ruangan->isVIP() ? "Ya" : "Tidak") << endl;
                } else {
                    cout << "Ruangan tidak ditemukan." << endl;
                }
                break;
            case 5:
                mrs.tampilRuangan();
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

void menuManajemenJanjiTemu(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Manajemen Janji Temu ===" << endl;
        cout << "1. Tambah Janji Temu" << endl;
        cout << "2. Hapus Janji Temu" << endl;
        cout << "3. Update Janji Temu" << endl;
        cout << "4. Cari Janji Temu" << endl;
        cout << "5. tampil Semua Janji Temu" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) break;

        int id, id_pasien, id_dokter, nomor_ruangan, metode_pembayaran;
        string tanggal_waktu;
        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Janji Temu: ";
                cin >> id;
                cout << "Masukkan ID Pasien: ";
                cin >> id_pasien;
                cout << "Masukkan ID Dokter: ";
                cin >> id_dokter;
                cout << "Masukkan Nomor Ruangan: ";
                cin >> nomor_ruangan;
                cout << "Masukkan Tanggal dan Waktu (dd-mm-yyyy): ";
                cin.ignore();
                getline(cin, tanggal_waktu);
                cout << "Masukkan Metode Pembayaran (0 untuk BPJS, 1 untuk Reguler): ";
                cin >> metode_pembayaran;
                mrs.tambahJanjiTemu(PendaftaranJanjiTemu(id, id_pasien, id_dokter, nomor_ruangan, tanggal_waktu, static_cast<PaymentMethod>(metode_pembayaran)));
                break;
            case 2:
                cout << "Masukkan ID Janji Temu yang akan dihapus: ";
                cin >> id;
                mrs.hapusJanjiTemu(id);
                break;
            case 3:
                cout << "Masukkan ID Janji Temu yang akan diupdate: ";
                cin >> id;
                cout << "Masukkan ID Pasien Baru: ";
                cin >> id_pasien;
                cout << "Masukkan ID Dokter Baru: ";
                cin >> id_dokter;
                cout << "Masukkan Nomor Ruangan Baru: ";
                cin >> nomor_ruangan;
                cout << "Masukkan Tanggal dan Waktu Baru (dd-mm-yyyy): ";
                cin.ignore();
                getline(cin, tanggal_waktu);
                cout << "Masukkan Metode Pembayaran Baru (0 untuk BPJS, 1 untuk Reguler): ";
                cin >> metode_pembayaran;
                mrs.updateJanjiTemu(id, PendaftaranJanjiTemu(id, id_pasien, id_dokter, nomor_ruangan, tanggal_waktu, static_cast<PaymentMethod>(metode_pembayaran)));
                break;
            case 4:
                cout << "Masukkan ID Janji Temu yang akan dicari: ";
                cin >> id;
                if (auto* janjiTemu = mrs.cariJanjiTemu(id)) {
                    cout << "ID Janji Temu: " << janjiTemu->getId() << ", ID Pasien: " << janjiTemu->getIdPasien()
                        << ", ID Dokter: " << janjiTemu->getIdDokter() << ", Nomor Ruangan: " << janjiTemu->getNomorRuangan()
                        << ", Tanggal dan Waktu: " << janjiTemu->getTanggalWaktu()
                        << ", Metode Pembayaran: " << (janjiTemu->getMetodePembayaran() == BPJS ? "BPJS" : "Reguler") << endl;
                } else {
                    cout << "Janji Temu tidak ditemukan." << endl;
                }
                break;
            case 5:
                mrs.tampilJanjiTemu();
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

void menuUtama(ManajemenRumahSakit& mrs) {
    int pilihan;
    while (true) {
        cout << "=== Menu Utama ===" << endl;
        cout << "1. Manajemen Pasien" << endl;
        cout << "2. Manajemen Dokter" << endl;
        cout << "3. Manajemen Karyawan" << endl;
        cout << "4. Manajemen Ruangan" << endl;
        cout << "5. Manajemen Janji Temu" << endl;
        cout << "6. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 6) {
            cout << "Terima kasih telah mengabdi pada Kemanusiaan yang abadi!" << endl;
            break;
        }

        switch (pilihan) {
            case 1:
                menuManajemenPasien(mrs);
                break;
            case 2:
                menuManajemenDokter(mrs);
                break;
            case 3:
                menuManajemenKaryawan(mrs);
                break;
            case 4:
                menuManajemenRuangan(mrs);
                break;
            case 5:
                menuManajemenJanjiTemu(mrs);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }
}

int main() {
    ManajemenRumahSakit mrs;
    menuUtama(mrs);
    return 0;
}
