#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * BIM 109 - Algoritma ve Programlamaya Giris Projesi
 * Konu: Akilli Envanter ve Stok Yonetim Sistemi
 */

typedef struct {
    int urunID;
    char urunAdi[50];
    int stokAdedi;
    float birimFiyat;
} Urun;

// Fonksiyonlar
void urunEkle();
void stokListele();
void urunAra();

int main() {
    int secim;

    while (1) {
        printf("\n--- SMARTSTOCK YONETIM SISTEMI ---");
        printf("\n1. Yeni Urun Kaydet");
        printf("\n2. Stok Listesini Goruntule");
        printf("\n3. Urun Ara (ID ile)");
        printf("\n0. Cikis");
        printf("\nSeciminiz: ");
        if (scanf("%d", &secim) != 1) {
            fprintf(stderr, "\nGecersiz giris! Programdan cikiliyor.\n");
            return 1;
        }

        switch (secim) {
            case 1: urunEkle(); break;
            case 2: stokListele(); break;
            case 3: urunAra(); break;
            case 0: exit(0);
            default: printf("\nGecersiz secim!\n");
        }
    }
    return 0;
}

void urunEkle() {
    Urun yeni;
    FILE *dosya = fopen("envanter.txt", "a");
    if (!dosya) {
        perror("Dosya acilamadi");
        return;
    }

    printf("Urun ID: ");
    scanf("%d", &yeni.urunID);

    printf("Urun Adi (bosluksuz): ");
    scanf("%49s", yeni.urunAdi);

    printf("Stok Adedi: ");
    scanf("%d", &yeni.stokAdedi);

    printf("Birim Fiyat: ");
    scanf("%f", &yeni.birimFiyat);

    fprintf(dosya, "%d %s %d %.2f\n", yeni.urunID, yeni.urunAdi, yeni.stokAdedi, yeni.birimFiyat);
    fclose(dosya);
    printf("\nUrun basariyla kaydedildi.\n");
}

void stokListele() {
    Urun u;
    FILE *dosya = fopen("envanter.txt", "r");
    if (dosya == NULL) {
        printf("Kayit bulunamadi!\n");
        return;
    }

    printf("\nID\tAd\t\tStok\tFiyat\n");
    printf("---------------------------------------\n");
    while (fscanf(dosya, "%d %49s %d %f", &u.urunID, u.urunAdi, &u.stokAdedi, &u.birimFiyat) == 4) {
        printf("%d\t%s\t\t%d\t%.2f TL\n", u.urunID, u.urunAdi, u.stokAdedi, u.birimFiyat);
    }
    fclose(dosya);
}

void urunAra() {
    int arananID, bulundu = 0;
    Urun u;
    FILE *dosya = fopen("envanter.txt", "r");
    if (!dosya) { printf("Kayit bulunamadi!\n"); return; }

    printf("Aranan Urun ID: ");
    scanf("%d", &arananID);

    while (fscanf(dosya, "%d %49s %d %f", &u.urunID, u.urunAdi, &u.stokAdedi, &u.birimFiyat) == 4) {
        if (u.urunID == arananID) {
            printf("\nUrun Bulundu: %s | Stok: %d | Fiyat: %.2f TL\n", u.urunAdi, u.stokAdedi, u.birimFiyat);
            bulundu = 1;
            break;
        }
    }
    if (!bulundu) printf("\nUrun bulunamadi.\n");
    fclose(dosya);
}
