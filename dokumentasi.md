# Tugas 1 – Data Encryption System with Counter
## KIJ Kelompok F10
* •	Deni Ismail (5114100022)
* •	Ahmad Ismail H W (5114100032)
## Pendahuluan
Saat ini, dunia komunikasi data dan keamanan jaringan menjadi hal yang sangat penting. Mengingat laju data dalam internet sangatlah banyak, dan banyak kemungkinan terjadi pencurian data. Perlu kita sadari bahwa untuk mencapai suatu keamanan itu adalah suatu hal yang sangat mustahil. Namun kita bisa melakukan pencagahan untuk mengurangi gangguan tersebut. 
Salah satu cara mencegah mencegah hal yang tidak diinginkan adalah dengan menggunakan enkripsi. Algoritma enkripsi sangatlah banyak,namun ada satu yang dijadikan standar dalam enkripsi, yaitu algoritma DES.
DES (Data Encryption Standard) adalah algoritma cipher blok yang populer karena dijadikan standard algoritma enkripsi kunci-simetri, meskipun saat ini standard tersebut telah digantikan dengan algoritma yang baru, AES, karena DES sudah dianggap tidak aman lagi. Sebenarnya DES adalah nama standard enkripsi simetri, nama algoritma enkripsinya sendiri adalah DEA (Data Encryption Algorithm), namun nama DES lebih populer daripada DEA. Algoritma DES dikembangkan di IBM dibawah kepemimpinan W.L. Tuchman pada tahun 1972. Algoritma ini didasarkan pada algoritma Lucifer yang dibuat oleh Horst Feistel. Algoritma ini telah disetujui oleh National Bureau of Standard (NBS) setelah penilaian kekuatannya oleh National Security Agency (NSA) Amerika Serikat.
DES termasuk ke dalam sistem kriptografi simetri dan tergolong jenis cipher blok. DES beroperasi pada ukuran blok 64 bit. DES mengenkripsikan 64 bit plainteks menjadi 64 bit cipherteks dengan menggunakan 56 bit kunci internal (internal key) atau upa-kunci (subkey). Kunci internal dibangkitkan dari kunci eksternal (external key) yang panjangnya 64 bit.
## Dasar Teori
### Kemanan Jaringan
Keamanan jaringan adalah suatu cara atau suatu system yang digunakan untuk memberikan proteksi atau perlindungan pada suatu jaringan agar terhindar dari berbagai ancaman luar yang mampu merusak jaringan.
### Enkripsi
Enkripsi adalah suatu metode yang digunakan untuk mengkodekan data sedemikian rupa sehingga keamanan informasinya terjaga dan tidak dapat dibaca tanpa di dekripsi (kebalikan dari proses enkripsi) dahulu. Encryption berasal dari bahasa yunani kryptos yang artinya tersembunyi atau rahasia.
### Dekripsi
Deskripsi adalah satu kaidah upaya pengolahan data menjadi sesuatu yang dapat diutarakan secara jelas dan tepat dengan tujuan agar dapat dimengerti oleh orang yang tidak langsung mengalaminya sendiri.
### DES
Dalam bidang kriptografi, Data Encryption Standard (DES) adalah sebuah algoritma enkripsi sandi blok kunci simetrik dengan ukuran blok 64-bit dan ukuran kunci 56-bit.
## Langkah – Langkah
    1.	Ubahlah plaintext dan key ke dalam bentuk biner
    2.	Lakukan Initial Permutation (IP) pada bit plaintext menggunakan tabel IP berikut:
        Tabel Initial Permutation(IP)

            58	50	42	34	26	18	10	2
            60	52	44	36	28	20	12	4
            62	54	46	38	30	22	14	6
            64	56	48	40	32	24	16	8
            57	49	41	33	25	17	9	1
            59	51	43	35	27	19	11	3
            61	53	45	37	29	21	13	5
            63	55	47	39	31	23	15	7

        Urutan bit pada plaintext urutan ke 58 ditaruh diposisi 1,
        Urutan bit pada plaintext urutan ke 50 ditaruh di posisi 2,
        Urutan bit pada plaintext urutan ke 42 ditaruh di posisi 3, dst
    3. Generate kunci yang akan digunakan untuk mengenkripsi plaintext dengan menggunakan tabel permutasi kompresi PC-1, pada langkah ini terjadi kompresi dengan membuang 1 bit masing-masing blok kunci dari 64 bit menjadi 56 bit.
        Tabel PC-1

            57	49	41	33	25	17	9
            1	58	50	42	34	26	18
            10	2	59	51	43	35	27
            19	11	3	60	52	44	36
            63	55	47	39	31	23	15
            7	62	54	45	38	30	22
            14	6	61	53	45	37	29
            21	13	5	28	20	12	4

    4. Lakukan pergeseran kiri (Left Shift) pada C0 dan D0, sebanyak 1 atau 2 kali berdasarkan kali putaran yang ada pada tabel putaran sebagai berikut:
    Tabel Left Shift
    Putaran ke - i	     Jumlah Pergeseran(Left Shift)
            1	                  1
            2	                  1
            3	                  2
            4	                  2
            5	                  2
            6	                  2
            7	                  2
            8	                  2
            9	                  1
            10	                  2
            11	                  2
            12	                  2
            13	                  2
            14	                  2
            15	                  2
            16	                  1

    Untuk putaran ke 1, dilakukan pegeseran 1 bit ke kiri
    Untuk putaran ke 2, dilakukan pergeseran 1 bit kekiri
    Untuk putaran ke 3, dilakukan pergeseran 2 bit kekiri, dst

    Setiap hasil putaran digabungkan kembali menjadi CiDi dan diinput kedalam tabel Permutation Compression 2 (PC-2) dan terjadi kompresi data CiDi 56 bit menjadi CiDi 48 bit.

        Tabel PC-2

            14	17	11	24	1	5
            3	28	15	6	21	10
            23	19	12	4	26	8
            16	7	27	20	13	2
            41	52	31	37	47	55
            30	40	51	45	33	48
            44	49	39	56	34	53
            46	42	50	36	29	32

    5. Pada langkah ini, kita akan meng-ekspansi data Ri-1 32 bit menjadi Ri 48 bit sebanyak 16 kali putaran dengan nilai perputaran 1<= i <=16 menggunakan Tabel Ekspansi (E).

        Tabel Ekspansi(E)
            32	1	2	3	4	5
            4	5	6	7	8	9
            8	9	10	11	12	13
            12	13	14	15	16	17
            16	17	18	19	20	21
            20	21	22	23	24	25
            24	25	26	27	28	29
            28	29	30	31	32	1


    Hasil E(Ri-1) kemudian di XOR dengan Ki dan menghasilkan Vektor Matriks Ai.
    6. Setiap Vektor Ai disubstitusikan kedelapan buah S-Box(Substitution Box), dimana blok pertama disubstitusikan dengan S1, blok kedua dengan S2 dan seterusnya dan menghasilkan output vektor Bi 32 bit.
    S1 :
            14,	4,	13,	1,	2,	15,	11,	8, 3,	10,	6,	12,	5,	9,	0,	7,
             0,	15,	7,	4,	14,	2,	13,	1, 10,	6,	12,	11,	9,	5,	3,	8,
             4,	1,	14,	8,	13,	6,	2,	11, 15,	12,	9,	7,	3,	10,	5,	0,
             15,	12,	8,	2,	4,	9,	1,	7, 5,	11,	3,	14,	10,	0,	6,	13
    S2 :
            15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5, 10,
            3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
            0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
            13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9
    S3 :
             10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
             13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
             13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
             1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12
    S4 :
             7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
             13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
             10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
             3,	15,	0,	6,	10,	1,	13,	18,	9,	4,	5,	11,	12,	7,	2,	14
    S5 :
             2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
             14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	15,
             4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
             11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3,
    S6 :
             12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
             10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
             9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
             4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13
    S7 :
             4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
             13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
             1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
             6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12
    S8 :
             13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
             1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
             7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
             2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11
    Kita ambil contoh S1, dan bit 100110. Kita pisahkan blok menjadi 2 yaitu:
    Bit pertama dan terakhir yaitu 1 dan 0 digabungkan menjadi 10
    Bit kedua hingga ke lima 0011
    Kemudian dibandingkan dengan memeriksa perpotongan antara keduanya didapatkan nilai 1000 dan seterusnya untuk blok kedua hingga blok kedelapan kita bandingkan dengan S2 hingga S8.

    7. Setelah didapatkan nilai vektor Bi, langkah selanjutnya adalah memutasikan bit vektor Bi menggunakan tabel P-Box, kemudian dikelompokkan menjadi 4 blok dimana tiap-tiap blok memiliki 32 bit data.

    Tabel P-Box

            16	7	20	21	29	12	28	17
            1	15	23	26	5	18	31	10
            2	8	24	14	32	27	3	9
            19	13	30	6	22	11	4	25

    Hasil P(Bi) kemudian di XOR kan dengan Li-1 untuk mendapatkan nilai Ri.
    Sedangkan nilai Li sendiri diperoleh dari Nilai Ri-1 untuk nilai 1 <= i <= 16.
    8. Langkah terakhir adalah menggabungkan R16 dengan L16 kemudian dipermutasikan untuk terakhir kali dengan tabel Invers Initial Permutasi(IP-1).

    Tabel IP-1

            40	8	48	16	56	24	64	32
            39	7	47	15	55	23	63	31
            38	6	46	14	54	22	62	30
            37	5	45	13	53	21	61	29
            36	4	44	12	52	20	60	28
            35	3	43	11	51	19	59	27
            34	2	42	10	50	18	58	26
            33	1	41	9	49	17	57	25
