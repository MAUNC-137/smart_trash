# Smart Trash Bin

Prototype tempat sampah otomatis yang membuka tutup ketika tangan atau
objek terdeteksi mendekat. Proyek ini menggunakan Arduino, sensor
ultrasonik, dan servo motor.

> **Status dokumentasi: rancangan awal.** Jenis servo, kebutuhan
> dayanya, serta kondisi modul step-up/step-down MAUNC masih harus
> diperiksa. Jangan menganggap seluruh komponen sudah teruji.

## 1. Gambaran Sistem

1.  Sensor ultrasonik HC-SR04 mengukur jarak objek di depan tempat
    sampah.
2.  Arduino membaca hasil pengukuran.
3.  Jika objek berada di bawah ambang jarak yang ditentukan, Arduino
    menggerakkan servo untuk membuka tutup.
4.  Setelah jeda beberapa detik, servo mengembalikan tutup ke posisi
    tertutup.

## 2. Daftar Komponen

  ---------------------------------------------------------------------------
  No.              Komponen                           Jumlah Status / catatan
  ---------------- ------------------- --------------------- ----------------
  1                Arduino Uno atau                        1 Gunakan board
                   Mega                                      yang sudah lolos
                                                             Blink Test

  2                Sensor ultrasonik                       1 Tercatat 10 unit
                   HC-SR04                                   di inventaris;
                                                             fungsi tiap unit
                                                             belum
                                                             diverifikasi

  3                Servo motor                             1 Pilih servo
                                                             kecil atau besar
                                                             setelah model
                                                             dan
                                                             spesifikasinya
                                                             diperiksa

  4                Breadboard                              1 Tercatat
                                                             tersedia di
                                                             inventaris

  5                Kabel jumper                   Secukupnya Periksa
                                                             ketersediaan dan
                                                             kondisi

  6                Kabel USB                               1 Untuk upload
                                                             program dan daya
                                                             board

  7                Bahan miniatur                 Secukupnya Kardus/foam
                   tempat sampah                             board atau bahan
                                                             ringan lainnya

  8                Engsel dan                     Secukupnya Untuk mekanisme
                   perekat/pengikat                          tutup

  9                Sumber daya servo                       1 **Belum
                   yang sesuai                               terkonfirmasi
                                                             tersedia**;
                                                             tentukan setelah
                                                             membaca
                                                             spesifikasi
                                                             servo

  10               Modul DC-DC               Jika diperlukan Tercatat di
                   step-down/step-up                         inventaris,
                                                             tetapi tipe dan
                                                             fungsinya belum
                                                             diverifikasi
  ---------------------------------------------------------------------------

### Catatan pemilihan servo

-   Servo kecil dapat diuji lebih dahulu dengan mekanisme tutup yang
    sangat ringan.
-   Servo besar tidak boleh langsung diberi daya dari pin 5V Arduino.
-   Kebutuhan tegangan dan arus harus mengikuti datasheet atau label
    servo.
-   Modul step-down hanya menurunkan tegangan; modul step-up hanya
    menaikkan tegangan. Keduanya bukan sumber energi dan tetap
    membutuhkan sumber DC yang sesuai.
-   Jangan menghubungkan baterai LiPo atau adaptor sebelum tegangan,
    polaritas, dan kemampuan arusnya dipastikan.

## 3. Wiring Sensor Ultrasonik

### HC-SR04 ke Arduino

  Pin HC-SR04   Arduino Uno (acuan)
  ------------- ---------------------
  VCC           5V
  GND           GND
  TRIG          D9
  ECHO          D10

Jika memakai Arduino Mega, pin digital D9 dan D10 juga dapat digunakan.
Pastikan nomor pin pada program sama dengan wiring.

## 4. Wiring Servo

Wiring servo bergantung pada model servo dan hasil pemeriksaan sumber
dayanya.

### A. Sinyal kontrol

  Kabel servo (warna umum)   Sambungan
  -------------------------- ---------------------------------------
  Signal (kuning/oranye)     D6 Arduino
  VCC (merah)                Positif sumber daya servo yang sesuai
  GND (cokelat/hitam)        Negatif/GND sumber daya servo

Warna kabel dapat berbeda antarprodusen. Periksa label atau datasheet
sebelum menyambungkan.

### B. Jika servo kecil diuji dengan suplai 5V Arduino

Untuk pengujian awal tanpa beban berat, servo mikro tertentu dapat
dicoba menggunakan 5V Arduino. Cara ini **bukan jaminan** bahwa suplai
Arduino cukup untuk servo tersebut.

-   Signal servo → D6.
-   VCC servo → 5V Arduino.
-   GND servo → GND Arduino.

Hentikan pengujian jika board restart, servo bergetar, kabel atau
regulator terasa panas, atau tegangan turun. Jangan memaksa servo
menahan tutup.

### C. Jika menggunakan sumber daya eksternal

Setelah sumber daya yang sesuai tersedia dan terverifikasi:

-   Signal servo → D6 Arduino.
-   VCC servo → positif sumber daya eksternal sesuai spesifikasi servo.
-   GND servo → negatif sumber daya eksternal.
-   GND sumber daya eksternal → GND Arduino (**common ground**).

**Jangan menyambungkan positif 5V eksternal ke pin 5V Arduino secara
sembarangan.** Pada konfigurasi ini, sumber eksternal memberi daya ke
servo, sedangkan Arduino memberikan sinyal kontrol. Pastikan tegangan
sumber daya sesuai dengan spesifikasi servo.

## 5. Diagram Koneksi

Diagram berikut menunjukkan koneksi sinyal dan sensor. Jalur daya servo
masih harus disesuaikan setelah tipe servo dan sumber dayanya diketahui.

``` mermaid
flowchart TD
    A[Arduino Uno / Mega]
    B[HC-SR04]
    C[Servo Motor]
    D[Sumber daya servo<br/>sesuai spesifikasi]

    A -- "5V dan GND" --> B
    A -- "D9 ke TRIG" --> B
    A -- "D10 ke ECHO" --> B
    A -- "D6 ke Signal" --> C
    D -- "V+ sesuai spesifikasi" --> C
    D -- "GND" --> C
    D -. "GND disatukan<br/>(common ground)" .-> A
```

## 6. Rancangan Mekanik

-   Pasang HC-SR04 di bagian depan tempat sampah, menghadap area tempat
    tangan didekatkan.
-   Pasang servo pada sisi atau bagian belakang tutup.
-   Gunakan tutup miniatur yang ringan.
-   Buat sambungan mekanis sederhana dari horn servo ke tutup.
-   Pastikan tutup dapat bergerak bebas dan tidak tersangkut.
-   Atur sudut buka dan tutup agar servo tidak dipaksa mencapai batas
    mekanis.

## 7. Pemeriksaan Sebelum Perakitan

-   [ ] Arduino berhasil menjalankan Blink Test.
-   [ ] HC-SR04 berhasil membaca jarak melalui Serial Monitor.
-   [ ] Model dan tegangan kerja servo sudah diketahui.
-   [ ] Servo berhasil diuji tanpa beban.
-   [ ] Sumber daya servo sesuai tegangan dan kebutuhan arusnya.
-   [ ] Modul step-up/step-down (jika dipakai) sudah diperiksa tipe dan
    output-nya.
-   [ ] GND Arduino dan sumber daya servo dapat disatukan dengan benar.
-   [ ] Mekanisme tutup bergerak bebas tanpa membebani servo.

## 8. Catatan Keselamatan

1.  Matikan seluruh sumber daya sebelum mengubah wiring.
2.  Periksa polaritas VCC dan GND sebelum menyalakan rangkaian.
3.  Jangan mengambil daya servo besar langsung dari pin 5V Arduino.
4.  Jangan menganggap modul DC-DC dapat menggantikan baterai/adaptor.
5.  Jangan menggunakan baterai LiPo tanpa mengetahui jumlah sel,
    tegangan, polaritas, dan kondisi baterai.
6.  Lakukan pengujian pertama tanpa memasang tutup pada servo.
7.  Proyek ini merupakan prototype edukasi, bukan produk tempat sampah
    otomatis siap pakai.

## 9. Informasi yang Masih Harus Dikonfirmasi

Dokumentasi wiring final baru dapat ditetapkan setelah pemeriksaan
komponen MAUNC:

-   Model servo kecil dan servo besar.
-   Tegangan kerja dan arus servo.
-   Tipe modul step-down dan step-up.
-   Kondisi kerja modul DC-DC.
-   Sumber daya DC yang benar-benar tersedia.
-   Kondisi HC-SR04 yang akan digunakan.

**Jangan merakit bagian daya servo besar berdasarkan diagram sementara
ini sebelum seluruh spesifikasi diverifikasi.**
