#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


typedef struct Musteri 
{

   int musteriNo;
   char TC[11];
   char adSoyad[50];
   char dogumTarih[11];
   char cinsiyet[10];
   char adres[100];
   char telefon[11];
   char eposta[50];
   int sifre;
   float bakiye;
   int sifreDurum;   // sifre degistirilmis ise 1 , degistirilmemisse 0
   int hesapDurum;  // aktif ise 1 , pasif ise 0


} musteri ;


typedef struct Hareket
{
    
    int musteriNo;
    char adSoyad[50];
    char sube[50];
    char islem[20];
    time_t tarih;


} hareket;


void musteriEkle()
{
   
    srand(time(0));
    system("cls");
    system("color B");
    printf("Musteri Ekleme Ekranina Hosgeldiniz\n");
    musteri m1;

    printf("TC: ");
    scanf("%s",m1.TC);
    printf("Ad Soyad: ");
    scanf("%s",m1.adSoyad);
    printf("Dogum Tarihi: ");
    scanf("%s",m1.dogumTarih);
    printf("Cinsiyet: ");
    scanf("%s",m1.cinsiyet);
    printf("Adres: ");
    scanf("%s",m1.adres);
    printf("Telefon: ");
    scanf("%s",m1.telefon);
    printf("Eposta: ");
    scanf("%s",m1.eposta);

    m1.musteriNo=rand()%1000 +1000;
    m1.sifre=rand()%1000 +1000;
    m1.sifreDurum=0;
    m1.hesapDurum=1;
    m1.bakiye=0.0;

    FILE *ptr = fopen("musteriler.dat","a+b");
    fwrite(&m1,sizeof(musteri),1,ptr);
    fclose(ptr);

    printf("\nMusteri kaydi basarili sekilde yapildi \n");
    printf("Musteri No: %s \n",m1.musteriNo,m1.adSoyad);
    printf("Tek kullanimlik sifreniz telefon numaraniza gonderilmistir (lutfen bu bilgiyi kimseyle paylasmayiniz) \n",m1.telefon);
    printf("Sifreniz: %s \n",m1.sifre);
    
}

void musteriSil()
{

    system("cls");
    system("color B");
    printf("Musteri Silme Ekranina Hosgeldiniz\n");
    musteri m1;
    char tc[11];

    printf("Silmek istediginiz musteri TC'sini giriniz: ");
    scanf("%s",tc);

    int sonuc=0;
    int silSonuc=0;

    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m1,sizeof(musteri),1,ptr) !=NULL)
    {
        if(strcmp(m1.TC,tc)==0)
        {
            sonuc=1;
            break;
        }
    }
    
    fclose(ptr);
    if(sonuc==0)
    printf("%s numarali musteri kaydina ulasilamadi \n",tc);
    else
    {
        char tercih;
        printf("%s hesabini silmek istediginize emin misiniz? (e/h) ",m1.adSoyad);
        scanf("%s",&tercih);

        if(tercih== 'e' || tercih == 'h')

        {

        ptr = fopen("musteriler.dat","r+b");
        FILE *yptr = fopen("yedek.dat","w+b");
        while(fread(&m1,sizeof(musteri),1,ptr)!=NULL)
        {
            if(strcmp(m1.TC,tc)==0)
        {
            silSonuc=1;         
        }
        else
        
            fwrite(&m1,sizeof(musteri),1,yptr);
        }
        fclose(ptr);
        fclose(yptr);

        if (silSonuc==1)
        {
            remove("musteriler.dat"); // silme islemi
            rename("yedek.dat","musteriler.dat"); // yedek dosyayi silinen dosyanin adiyla degistirme islemi
            printf("%s hesabi basariyla silindi \n",tc);
        }
        else
        
            printf("%s hesabi silinemedi \n",tc);
        
        }
        else
        printf("hesap silme islemi iptal edildi \n");

      }
    }

        


void hesapDondur()
{

    system("cls");
    system("color B");
    printf("Hesap Dondurme Ekranina Hosgeldiniz\n");
    musteri m1;
    char tc[11];

    printf("Dondurmak istediginiz musteri TC'sini giriniz: ");
    scanf("%s",tc);

    int sonuc=0;
    int sayac=0;
    int dondurSonuc=0;


    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m1,sizeof(musteri),1,ptr)!=NULL)
    {
        if(strcmp(m1.TC,tc)==0)
        {
            sonuc=1;
            break;
        }

        sayac++;
    }
  
  if(sonuc==0)
  printf("%s numarali hesap kaydi bulunamadi \n",tc);
  else
  {
    rewind(ptr);
    fseek(ptr,sayac*sizeof(musteri),0);
    m1.hesapDurum=0;
    fwrite(&m1,sizeof(musteri),1,ptr);
    printf("%s numarali hesap basariyla donduruldu \n",tc);

}
 
fclose(ptr);
}

void hesapAktiflestir()
{

    system("cls");
    system("color B");
    printf("Hesap Aktif Etme Ekranina Hosgeldiniz\n");
    musteri m1;
    char tc[11];

    printf("Aktif etmek istediginiz musteri TC'sini giriniz: ");
    scanf("%s",tc);

    int sonuc=0;
    int aktifSonuc=0;
    int sayac=0;

    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m1,sizeof(musteri),1,ptr)!=NULL)
    {
        if(strcmp(m1.TC,tc)==0)
        {
            sonuc=1;
            break;
        }

        sayac++;
    }
  
  if(sonuc==0)
  printf("%s numarali hesap kaydi bulunamadi \n",tc);
  else
  {
    rewind(ptr);
    fseek(ptr,sayac*sizeof(musteri),0);
    m1.hesapDurum=1;
    fwrite(&m1,sizeof(musteri),1,ptr);
    printf("%s numarali hesap basariyla aktif edildi \n",tc);

}

fclose(ptr);

}

void musteriListele()
{

    system("cls");
    system("color B");
    printf("Musteri Listeleme Ekranina Hosgeldiniz\n");
    musteri m1;
    int sayac;
    sayac=0;

    FILE *ptr = fopen("musteriler.dat","r+b");
    printf("%-10s%-15s%-30s%-15s%-10s%-30s%-20s%-30s%-10s%-10s%-10s\n", "Mst.NO", "TC", "AD-SOYAD", "DOG-TARIH","CINSIYET", "ADRES", "TELEFON", "E-POSTA","BAKIYE", "SIF-DURUM", "HSP-DURUM"  ) ;  
    while (fread(&m1,sizeof(musteri),1,ptr) !=NULL)

    {

     printf("%-10d%-15s%-30s%-15s%-10c%-30s%-20s%-30s%-10.2f%-10d%-10d\n", m1.musteriNo, m1.TC, m1.adSoyad, m1.dogumTarih, m1.cinsiyet, m1.adres, m1.telefon, m1.eposta, m1.bakiye, m1.sifreDurum, m1.hesapDurum    ); 

	sayac++; 

	}	

    fclose(ptr); 
	printf("\nMusteri sayisi : %d \n\n", sayac  ) ; 
	
		

    }

   int yetkiliMenu()

   {

    int secim;
    printf("\n\n\tYETKILI MENU\n\n");
    printf("\n1. Musteri Ekleme\n");
    printf("\n2. Musteri Silme\n");
    printf("\n3. Hesap Dondurma\n");
    printf("\n4. Hesap Aktif Etme\n");
    printf("\n5. Musteri Listeleme\n");
    printf("\n0. Cikis\n");
    printf("\nSeciminiz: ");
    scanf("%d",&secim);

    return secim;

}

void yetkili()
{

  system("cls");
  system("color B");
  int secim;
  secim=yetkiliMenu();

  while(secim!=0)
  {
    switch(secim)

    {
        case 1:
            musteriEkle();
            break;

        case 2:
            musteriSil();
            break;

        case 3:
            hesapDondur();
            break;

        case 4:
            hesapAktiflestir();
            break;

        case 5:
            musteriListele();
            break;

        case 0:
            break;

        default:
        printf("Hatali secim yaptiniz \n");
    }

    secim=yetkiliMenu();
  }
  
  system("cls");
  printf("\nCikis yapiliyor... \n");
   
}

void yetkiliGiris()
{

    system("cls");
    system("color B");
    char tc[11];
    char parola[11];

    printf("Yetkili Giris Ekranina Hosgeldiniz(admin 123)\n\n");
    printf("TC: ");
    scanf("%s",tc);
    printf("Parola: ");
    scanf("%s",parola);

    if(strcmp(tc,"admin")==0 && strcmp(parola,"123")==0)
    {
        printf("Giris basarili \n");
        yetkili();
    }
    else
    {
        printf("Giris basarisiz \n");
    }

}

void hareketKaydet(musteri m1 , char *islemPtr)
{

    hareket h1;

    h1.musteriNo=m1.musteriNo;
    strcpy(h1.adSoyad,m1.adSoyad);
    strcpy(h1.islem,islemPtr);
    strcpy(h1.sube,"Esenyurt Subesi");
    h1.tarih=time(0);


    char dosyaAdi[20];
    strcpy(dosyaAdi,m1.TC);
    strcat(dosyaAdi,".dat"); // dosya adi olusturuldu
    FILE *ptr = fopen(dosyaAdi,"a+b");
    fwrite(&h1,sizeof(hareket),1,ptr);
    fclose(ptr);

    // bankamatik icinde yapmıs oldugumuz dosya islemleri tammalanmı bulunmaktadir !

}

void bakiyeGuncelle(musteri m2 , int ucret)
{
    
    system("cls");
    system("color B");
    musteri m1;

    int sonuc;
    int sayac;

    sonuc=0;
    sayac=0;

    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m1,sizeof(musteri),1,ptr)!=NULL)
    {
        if(strcmp(m2.TC,m1.TC)==0)
        {
            sonuc=1;
            break;
        }

        sayac++;
    }
    if(sonuc==0)
    printf("%s numarali hesap kaydi bulunamadi \n",m2.TC);
    else
    {
        rewind(ptr); // dosya basina don
        fseek(ptr,sayac*sizeof(musteri),0);
        m1.bakiye=m1.bakiye+ucret;
        fwrite(&m1,sizeof(musteri),1,ptr);

        // bakiye guncelleme islemi tamamlandi
    }

    fclose(ptr);

}

void paraCek(musteri m1)
{

    system("cls");
    system("color B");
    printf("Para Cekme Ekranina Hosgeldiniz\n",m1.adSoyad);
    float ucret;
    printf("Cekmek istediginiz tutar: ");
    scanf("%f",&ucret);

    musteri m2;
    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m2,sizeof(musteri),1,ptr))
    {
        if(strcmp(m1.TC,m2.TC)==0)
        {
           
            break;
        }
    }
     fclose(ptr);
     if(ucret > m2.bakiye)
     {
         printf("Yetersiz bakiye \n");
     }
     else
     {
         bakiyeGuncelle(m2,-ucret);
         hareketKaydet(m2,"Para Cekme");
         printf(" Para cekme Islemi basarili \n");

     }
}

void paraYatir(musteri m1)
{
   
    system("cls");
    system("color B");
    printf("Para Yatirma Ekranina Hosgeldiniz\n",m1.adSoyad);
    float ucret;
    printf("Yatirmak istediginiz tutar: ");
    scanf("%f",&ucret);

    musteri m2;
    FILE *ptr = fopen("musteriler.dat","r+b");
    while (fread(&m2,sizeof(musteri),1,ptr))
    {
        if(strcmp(m1.TC,m2.TC)==0)
        {
           
            break;
        }
    }
     fclose(ptr);
     bakiyeGuncelle(m2,ucret);
     hareketKaydet(m2,"Para Yatirma");
     printf(" Para yatirma Islemi basarili \n");


}


void havaleEFT(musteri m1)
{
   
    system("cls");
    system("color B");
    printf("Havale/EFT Ekranina Hosgeldiniz\n",m1.adSoyad);
    float ucret;
    int hspNo;
    char adSoyad[30];

    printf("Hesap Numarasi: ");
    scanf("%d",&hspNo);
    printf("Ad Soyad: ");
    scanf("%s",adSoyad);
    printf("Tutar: ");
    scanf("%f",&ucret);

    musteri m2,m3;
    int sonuc=0;
    FILE *ptr = fopen("musteriler.dat","r+b");
    while(fread(&m2,sizeof(musteri),1,ptr) !=NULL)
    {
        if(strcmp(m2.adSoyad,adSoyad)==0 && m2.musteriNo==hspNo)
        {
            sonuc=1;
            break;
        }
       
    }
    fclose(ptr);
    if(sonuc==0)
    printf("Girmis oldugunuz ad - soyad ve hesap numarasi bilgilerinde hata var!!!\n");
    else
    {
        ptr = fopen("musteriler.dat","r+b");
        while(fread(&m3,sizeof(musteri),1,ptr) !=NULL)
        {
            if(strcmp(m3.TC,m1.TC)==0)
            {
                break;
            }
        }
       
       if(ucret >m3.bakiye)
       {
           printf("Yetersiz bakiye \n");
       }
       else
       {
           bakiyeGuncelle(m3,-ucret);
           bakiyeGuncelle(m2,ucret);
           hareketKaydet(m3,"Havale/EFT Gonderildi");
           hareketKaydet(m2,"Havale/EFT Geldi");
           printf("Havale/EFT Islemi basarili \n");
       }
    }

}


void bakiyeSorgula(musteri m1)
{
   
    system("cls");
    system("color B");
    FILE *ptr = fopen("musteriler.dat","r+b");
    musteri m2;
    int sonuc;
    sonuc=0;
    while (fread(&m2,sizeof(musteri),1,ptr) !=NULL)
    {
        if(strcmp(m1.TC,m2.TC)==0)
        {
            sonuc=1;
            break;
        }
    }
    
    fclose(ptr);
    if(sonuc==0)
    printf("Bakiye Gosterilemedi \n");
    else
    {
        printf("Bakiyeniz: %f \n",m2.bakiye);
        hareketKaydet(m2,"Bakiye Sorgulama");
    }
        
}

void sifreDegistir(musteri m1)
{

    system("cls");
    system("color B");
    printf("Sifre Degistirme Ekranina Hosgeldiniz\n");
    int eski;
    int yeni;
    int yeniTekrar;

    printf("\nEski Sifre: ");
    scanf("%d",&eski);
    printf("\nYeni Sifre: ");
    scanf("%d",&yeni);
    printf("\nYeni Sifre Tekrar: ");
    scanf("%d",&yeniTekrar);

    if(m1.sifre == eski && yeni== yeniTekrar)
    {
        musteri m2;
        int sonuc;
        sonuc=0;
        int sayac;
        sayac=0;

        FILE *ptr = fopen("musteriler.dat","r+b");
        while (fread(&m2,sizeof(musteri),1,ptr) !=NULL)
        {
            if(strcmp(m1.TC,m2.TC)==0)
            {
                sonuc=1;
                break;
            }
            sayac++;
        }

        rewind(ptr);
        fseek(ptr,sayac*sizeof(musteri),0);
        m1.sifre=yeni;
        fwrite(&m1,sizeof(musteri),1,ptr);
        printf("Sifre degistirme islemi basarili \n");
        fclose(ptr);

        hareketKaydet(m1,"Sifre Degistirme");
    }
    else
    {
        printf("Sifre degistirme islemi basarisiz \n");
    }




}

void hareketDokumu(musteri m1)
{

    system("cls");
    system("color B");
    printf("Hareket Dokumu Ekranina Hosgeldiniz\n",m1.adSoyad);

    hareket h1;

    char dosyaAdi[30];
    strcpy(dosyaAdi,m1.TC);
    strcat(dosyaAdi,".dat");
    FILE *ptr = fopen(dosyaAdi,"r+b");
    if(ptr==NULL)
    {
        printf("%s hareket kaydi yok \n",m1.adSoyad);
    }
    else
    {
        printf("%-20s %-20s %-20s% 20s% 20s% 20s\n \n","Tarih","Islem","MS.NO","AD-SOYAD","sube");

        while(fread(&h1,sizeof(hareket),1,ptr) !=NULL)
        {
            printf("%-20s %-20s %-20d %-20s %-20s %-20s\n",ctime(&h1.tarih),h1.islem,h1.musteriNo,h1.adSoyad,h1.sube);
        }
    }


    fclose(ptr);
}

int musteriMenu(musteri m1)
{

    int secim;

    printf("\n\n\tMusteri Menu Ekranina Hosgeldiniz\n\n");
    printf("AD/SOYAD: %s\n",m1.adSoyad);
    printf("HS. NO: %d\n",m1.musteriNo);

    printf("\n1-Para Cek\n");
    printf("\n2-Para Yatir\n");
    printf("\n3-Havale/EFT\n");
    printf("\n4-Bakiye Sorgula\n");
    printf("\n5-Sifre Degistir\n");
    printf("\n6-Hareket Dokumu\n");
    printf("\n0-Cikis\n");
    printf("\nSeciminiz: ");
    scanf("%d",&secim);

    return secim;
} 


void sifreDegisstirTek(musteri m1)
{

   int eski;
   int yeni;
   int yeniTekrar;

    printf("\nEski Sifre: ");
    scanf("%d",&eski);
    printf("\nYeni Sifre: ");
    scanf("%d",&yeni);
    printf("\nYeni Sifre Tekrar: ");
    scanf("%d",&yeniTekrar);
   
   if( m1.sifre == eski && yeni == yeniTekrar)
   {

     musteri m2;
     int sonuc;
     sonuc=0;
     int sayac;
     sayac=0;
    
        FILE *ptr = fopen("musteriler.dat","r+b");
        while (fread(&m2,sizeof(musteri),1,ptr) !=NULL)
        {
            if(strcmp(m1.TC,m2.TC)==0)
            {
                sonuc=1;
                break;
            }
            sayac++;
        }

        rewind(ptr); // dosya basina gider
        fseek(ptr,sayac*sizeof(musteri),0); // dosya basindan sayac kadar kaydirir.
        m1.sifreDurum=1;
        m1.sifre=yeni;
        fwrite(&m1,sizeof(musteri),1,ptr);
        printf("Sifre degistirme islemi basarili \n");
        fclose(ptr);

   }

   else
   {
   
      printf("Sifre degistirme islemi basarisiz \n");
   }

}

void musterimiz(musteri m1)
{
        system("cls");
        system("color B");

        if(m1.sifreDurum==0)
        {
            printf("%s Tek kullanimlik sifrenizi degistiriniz,,,,,, \n",m1.adSoyad);
            sifreDegisstirTek(m1);
        }

        else if (m1.hesapDurum==0)
        {
            printf("%s Hesabiniz askida durmaktadir (lutfen sube ile iletisime geciniz) \n",m1.adSoyad);
            
        }
        else
        {
            int secim;
            secim=musteriMenu(m1);
            while (secim!=0)
            {
                switch (secim)
            
            {
                case 1:
                    paraCek(m1);
                    break;

                case 2:
                    paraYatir(m1);
                    break;

                case 3: 
                    havaleEFT(m1);
                    break;

                case 4:
                    bakiyeSorgula(m1);
                    break;

                case 5:
                    sifreDegistir(m1);
                    break;

                case 6:
                    hareketDokumu(m1);
                    break;

                case 0:
                    break;

                default:
                    printf("Yanlis secim yaptiniz \n");
        
            }

            secim=musteriMenu(m1);
            }

            system("cls");
            printf("\nCikis yapiliyor \n\n",m1.adSoyad);
           
        }

}   

void musteriGiris()
{
    
    system("cls");
    system("color B");

    char tc[12];
    int sifre;
    int sonuc;
    sonuc=0;

    printf("\nMusteri Giris Ekranina Hosgeldiniz\n\n");
    printf("TC Kimlik No: ");
    scanf("%s",tc);
    printf("Sifre: ");
    scanf("%d",&sifre);

    musteri m1;
    FILE *ptr = fopen("musteriler.dat","r+b");
    while(fread(&m1,sizeof(musteri),1,ptr) !=NULL)
    {
        if(strcmp(tc,m1.TC)==0 && sifre==m1.sifre)
        {
            sonuc=1;
            break;
        }
    }

    fclose(ptr);
    if(sonuc==1)
    musterimiz(m1);
    else
    printf("TC Kimlik No veya Sifre Hatali \n");

}


int menu()
{

    int secim;
    printf("\n\n\tBANKAMATIK OTOMASYONU \n\n");
    printf("\n\t1-Musteri GIRIS\n");
    printf("\n\t2-YETKILI GIRIS\n");
    printf("\n\t0-CIKIS\n");
    printf("\n\tSeciminiz: ");
    scanf("%d",&secim);

    return secim;

}

int main ()
{

    int secim;
    secim=menu();

    while(secim!=0)
    {
        switch(secim)
    {
        case 1:
            musteriGiris();
            break;

        case 2:
            yetkiliGiris();
            break;

        case 0:
            break;

        default:
            printf("Yanlis secim yaptiniz \n"); 
    }

    secim=menu();


    }


   printf("\nCikis yapiliyor \n\n");

    return 0;


}