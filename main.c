#include <stdio.h>
#include <string.h>

#define SCOOTER_SAYISI 3

int guvenliSayiAl(int min, int max) {
    int sayi;
    char c;

    while (1) {
        if (scanf("%d", &sayi) != 1) {
            printf("Hatali giris! Lutfen sadece sayi giriniz.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (sayi < min || sayi > max) {
            printf("Lutfen %d ile %d arasinda giriniz.\n", min, max);
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else {
            while ((c = getchar()) != '\n' && c != EOF);
            return sayi;
        }
    }
}

void makbuzYaz(char kullanici[], char scooter[], int dakika, int odeme, int kalanBakiye) {
    FILE *dosya = fopen("makbuz.txt", "w");

    if (dosya == NULL) {
        printf("Makbuz dosyasi acilamadi!\n");
        return;
    }

    fprintf(dosya, "------------------------------\n");
    fprintf(dosya, "        SCOOTER MAKBUZU       \n");
    fprintf(dosya, "------------------------------\n");
    fprintf(dosya, "Kullanici Adi : %s\n", kullanici);
    fprintf(dosya, "Scooter       : %s\n", scooter);
    fprintf(dosya, "Kullanim      : %d dakika\n", dakika);
    fprintf(dosya, "Odenen Tutar  : %d TL\n", odeme);
    fprintf(dosya, "Kalan Bakiye  : %d TL\n", kalanBakiye);
    fprintf(dosya, "------------------------------\n\n");

    fclose(dosya);
}

int main() {
    int scooter[SCOOTER_SAYISI][2];
    char scooterIsim[SCOOTER_SAYISI][20] = {
        "Scooter-A",
        "Scooter-B",
        "Scooter-C"
    };

    char kullaniciAdi[30];
    int bakiye, dakika, odeme;
    int secilenScooter;
    int i;

    for (i = 0; i < SCOOTER_SAYISI; i++) {
        scooter[i][0] = i + 1;
        scooter[i][1] = 0; 
    }

    printf("\n--- SCOOTER SISTEMI ---\n");
    printf("Kullanici adinizi giriniz: ");
    scanf("%s", kullaniciAdi);

    printf("\nMevcut Scooterlar:\n");
    for (i = 0; i < SCOOTER_SAYISI; i++) {
        printf("%d - %s (%s)\n",
               scooter[i][0],
               scooterIsim[i],
               scooter[i][1] == 0 ? "Bos" : "Dolu");
    }

    printf("Scooter ID seciniz (1-%d): ", SCOOTER_SAYISI);
    secilenScooter = guvenliSayiAl(1, SCOOTER_SAYISI);

    printf("Acilis: 10 TL | Dakika: 9 TL\n");

    printf("Bakiye giriniz (min 50 TL): ");
    bakiye = guvenliSayiAl(50, 100000);

    scooter[secilenScooter - 1][1] = 1;

    do {
        printf("Kullanim suresi (dakika): ");
        dakika = guvenliSayiAl(0, 10000);

        odeme = 10 + dakika * 9;

        if (odeme > bakiye) {
            printf("Yetersiz bakiye!\n");
            printf("Maksimum %d dakika kullanabilirsiniz.\n",
                   (bakiye - 10) / 9);
        }

    } while (odeme > bakiye);

    bakiye -= odeme;
    scooter[secilenScooter - 1][1] = 0;

    printf("\n--- ISLEM OZETI ---\n");
    printf("Kullanici : %s\n", kullaniciAdi);
    printf("Scooter   : %s\n", scooterIsim[secilenScooter - 1]);
    printf("Kullanim  : %d dakika\n", dakika);
    printf("Odeme     : %d TL\n", odeme);
    printf("Kalan Bak : %d TL\n", bakiye);
    printf("Tesekkur ederiz!\n");

    makbuzYaz(
        kullaniciAdi,
        scooterIsim[secilenScooter - 1],
        dakika,
        odeme,
        bakiye
    );

    return 0;
}
