#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <windows.h>

using namespace std;

struct time
{
    int hour, minute;
};

struct launch
{
    int date;
    char month[21];
    int year;
};

struct movie
{
    char name[51],genre[21], country[21], language[21], cast[81];
    char storyline[631];
    launch release_date;
    time runtime;
    char production_company[51], awards[81];
    float rating;
};

char denumire_fisier[20];

void afisare_meniu()
{
    /// se schimba culoarea textului din consola

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 3);

    cout << "  ~*~*~*~*~*~*~*~\n";
    cout << "~*~ Movie Buffs ~*~\n";
    cout << "  ~*~*~*~*~*~*~*~\n";

    /// se schimba culoarea textului in alb cu background negru

    SetConsoleTextAttribute(console_color, 15);
    cout << endl;
}

void categorii_filme()
{
    cout << "Categoriile de filme sunt:\n";

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 13);

    cout << "1. Actiune" << "             " << "5. Comedie\n";
    cout << "2. Aventura" << "            " << "6. Crima si Mister\n";
    cout << "3. Animatie" << "            " << "7. Dragoste\n";
    cout << "4. Biografic" << "           " << "8. SF\n";

    SetConsoleTextAttribute(console_color, 15);
    cout << endl;
}

void informatii_filme()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 11);

    cout << "1. Data lansarii\n";
    cout << "2. Durata filmului\n" ;
    cout << "3. Tara si limba\n";
    cout << "4. Actorii principali\n";
    cout << "5. Rating\n";
    cout << "6. Povestea filmului\n";
    cout << "7. O companie de productie\n";
    cout << "8. Premiile obtinute\n";
    cout << "9. Adaugare in lista favorite\n";
    cout << "10. Iesi\n";

    SetConsoleTextAttribute(console_color, 15);
    cout << endl;
}

void optiuni()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 12);

    cout << "1. Afisare informatii despre un film\n";
    cout << "2. Sortare filme dupa an aparitie\n";
    cout << "3. Adaugare film in categorie\n";
    cout << "4. Stergere film\n";
    cout << "5. Lista filme favorite\n";
    cout << "6. Iesi\n";

    SetConsoleTextAttribute(console_color, 15);
    cout << endl;
}

/// se copiaza fisierul ales de catre dumneavoastra in denumirea fisierului care va urma sa fie deschis
/// in functia de citire_fisier, apoi sa fie si citit

void alegere_fisier(char gen[21], int alegere)
{
    if (alegere == 1)
    {
        strcpy(denumire_fisier, "actiune.in");
        strcpy(gen, "actiune");
    }
    else if (alegere == 2)
    {
        strcpy(denumire_fisier, "aventura.in");
        strcpy(gen, "aventura");
    }
    else if (alegere == 3)
    {
        strcpy(denumire_fisier, "animatie.in");
        strcpy(gen, "animatie");
    }
    else if (alegere == 4)
    {
        strcpy(denumire_fisier, "biografic.in");
        strcpy(gen, "biografic");
    }
    else if (alegere == 5)
    {
        strcpy(denumire_fisier, "comedie.in");
        strcpy(gen, "comedie");
    }
    else if (alegere == 6)
    {
        strcpy(denumire_fisier, "crima_mister.in");
        strcpy(gen, "crima si mister");
    }
    else if (alegere == 7)
    {
        strcpy(denumire_fisier, "dragoste.in");
        strcpy(gen, "dragoste");
    }
    else
    {
        strcpy(denumire_fisier, "SF.in");
        strcpy(gen, "SF");
    }
}

/// se citeste fisierul ales

void citire_fisier(movie p[], int &n, char gen[21])
{
    int alegere;

    categorii_filme();

    cout << "Alegeti o optiune: ";
    cin >> alegere;
    cout << endl;

    alegere_fisier(gen, alegere);

    ifstream f(denumire_fisier);
    f >> n;
    f.get();

    for (int i = 1; i <= n; i++)
    {
        f.getline(p[i].name, 51);
        f.getline(p[i].genre, 21);
        f >> p[i].release_date.date;
        f.get();
        f.getline(p[i].release_date.month, 21);
        f >> p[i].release_date.year;
        f.get();
        f >> p[i].runtime.hour >> p[i].runtime.minute;
        f.get();
        f.getline(p[i].country, 21);
        f.getline(p[i].language, 21);
        f.getline(p[i].cast, 81);
        f >> p[i].rating;
        f.get();
        f.getline(p[i].storyline, 631);
        f.getline(p[i].production_company, 51);
        f.getline(p[i].awards, 81);
        f.get();
    }
}

void afisare_titluri_filme(movie p[], int n)
{
    system("cls");
    cout << "Alegeti filmul despre care doriti informatii:" << endl << endl;

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);

    for (int i = 1; i <= n; i++)
        cout << i << ". " << p[i].name << endl;

    SetConsoleTextAttribute(console_color, 15);
    cout << endl;
}

/// se adauga titlurile filmelor preferate intr-un vector numit vector_fav

void adaugare_favorite(char vector_fav[21][51], int &cate_fav, char name_of_fav_movie[51])
{
    strcpy(vector_fav[cate_fav], name_of_fav_movie);
    cate_fav++;
}

/// se afiseaza titlurile filmelor preferate

void afisare_favorite(char vector_fav[21][51], int cate_fav)
{
    cout << "Filmele din lista favorite sunt:\n";
    for(int i = 0; i < cate_fav; i++)
        cout << vector_fav[i] << endl;
}

/// se afiseaza informatiile despre filmul ales din categoria dorita

void prezentare_film(movie p[], int numar, int &alegere, int &cate_fav, char vector_fav[21][51])
{
    /// se sterge din consola tot ce era inainte
    system("cls");

    do
    {
        cout << "Informatiile despre ";

        HANDLE console_color;
        console_color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console_color, 2);

        cout << "'" << p[numar].name << "' ";

        SetConsoleTextAttribute(console_color, 15);

        cout << "sunt:\n";

        informatii_filme();

        cout << "Alegeti optiunea dorita: ";
        cin >> alegere;

        switch (alegere)
        {
        case 1:
            cout << "Data lansarii este: " << p[numar].release_date.date << " " << p[numar].release_date.month << " " << p[numar].release_date.year << endl;
        break;

        case 2:
        {
            cout << "Filmul dureaza " << p[numar].runtime.hour;
            if (p[numar].runtime.hour == 1 && p[numar].runtime.minute == 0)
                cout << " ora" << endl;
            else if (p[numar].runtime.minute == 0)
                cout << " ore" << endl;
            else if (p[numar].runtime.hour == 1)
                cout << " ora si " << p[numar].runtime.minute << " minute" << endl;
            else if (p[numar].runtime.minute == 1)
                cout << " ore si " << p[numar].runtime.minute << " minut" << endl;
            else
                cout << " ore si " << p[numar].runtime.minute << " minute" << endl;
        }
        break;

        case 3:
            cout << "Tara este " << p[numar].country << " si limba in care se vorbeste este " << p[numar].language << endl;
        break;

        case 4:
            cout << "Actorii principali sunt: " << p[numar].cast << endl;
        break;

        case 5:
            cout << "Raiting: " << p[numar].rating << "/10" << endl;
        break;

        case 6:
            cout << "Poveste: " << p[numar].storyline << endl;
        break;

        case 7:
            cout << "Una dintre companiile de productie este: " << p[numar].production_company << endl;
        break;

        case 8:
            cout << "Premiile obtinute: " << p[numar].awards << endl;
        break;

        case 9:
        {
            char name_of_fav_movie[51];
            strcpy(name_of_fav_movie, p[numar].name);
            adaugare_favorite(vector_fav, cate_fav, name_of_fav_movie);
            cout << "Filmul a fost adaugat in lista favorite\n";
        }
        break;
        }

        if (alegere != 10)
        {
            /// getch()-asteapta sa fie introdus un caracter de la tastatura
            /// caracterul fiind '\0' (adica persoana tasteaza Enter)
            getch();
            system("cls");
        }
    }
    while (alegere != 10);
}

/// se face ordonarea filmelor dintr-o anumita categorie aleasa de dumneavoastra

void ordonare_dupa_an(movie p[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            if (p[i].release_date.year > p[j].release_date.year)
            {
                movie aux;
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
        }
    }
    cout << "In ordinea descrescatoare a anilor de lansare:" << endl;

    for (int i = 1; i <= n; i++)
        cout << p[i].release_date.year << ": " << p[i].name << endl;
}

/// se adauga filme in fisierul ales de dumneavoastra, din care s-a si citit

void adaugare_filme(movie p[], int &n, char gen[21])
{
    int nr_filme;

    /// se deschise fisierul de iesire cu acelasi nume ca cel de intrare

    ofstream g(denumire_fisier);

    cout << "Dati numarul de filme pe care doriti sa le adaugati:";
    cin >> nr_filme;

    /// numarul filmelor creste cu cate filme doriti sa adaugati in fisier

    n += nr_filme;

    g << n << endl;

    /// se copiaza elementele care exista in fisierul de intrare

    for (int i = 1; i <= n-nr_filme; i++)
    {
        g << p[i].name << endl;
        g << p[i].genre << endl;
        g << p[i].release_date.date << endl;
        g << p[i].release_date.month << endl;
        g << p[i].release_date.year << endl;
        g << p[i].runtime.hour << endl;
        g << p[i].runtime.minute << endl;
        g << p[i].country << endl;
        g << p[i].language << endl;
        g << p[i].cast << endl;
        g << p[i].rating << endl;
        g << p[i].storyline << endl;
        g << p[i].production_company << endl;
        g << p[i].awards << endl;
        g << endl;
    }

    cin.get();

    /// se citesc elementele noi, care urmeaza sa fie adaugate in fisier si sunt scrise in fisierul de iesire

    for (int i = n - nr_filme + 1; i <= n; i++)
    {
        cout << i << ".Nume film: ";
        cin.getline(p[i].name, 51);
        g << p[i].name << endl;

        strcpy(p[i].genre, p[i - 1].genre);
        g << p[i].genre << endl;

        cout << "Zi lansare: ";
        cin >> p[i].release_date.date;
        g << p[i].release_date.date << endl;
        cin.get();

        cout << "Luna: ";
        cin.getline(p[i].release_date.month, 21);
        g << p[i].release_date.month << endl;

        cout << "An: ";
        cin >> p[i].release_date.year;
        g << p[i].release_date.year << endl;
        cin.get();

        cout << "Durata ore: ";
        cin >> p[i].runtime.hour;
        g << p[i].runtime.hour << endl;

        cout << "Durata minute: ";
        cin >> p[i].runtime.minute;
        g << p[i].runtime.minute << endl;
        cin.get();

        cout << "Tara: ";
        cin.getline(p[i].country, 21);
        g << p[i].country << endl;
        cout << "Limba: ";
        cin.getline(p[i].language, 21);
        g << p[i].language << endl;

        cout << "Actori: ";
        cin.getline(p[i].cast, 81);
        g << p[i].cast << endl;

        cout << "Rating: ";
        cin >> p[i].rating;
        g << p[i].rating << endl ;
        cin.get();

        cout << "Descriere: ";
        cin.getline(p[i].storyline, 631);
        g << p[i].storyline << endl;

        cout << "O companie de productie: ";
        cin.getline(p[i].production_company, 51);
        g << p[i].production_company << endl;

        cout << "Premii: ";
        cin.getline(p[i].awards, 81);
        g << p[i].awards << endl;
        g << endl;
        cin.get();
    }
}

/// se cauta numarul(codul) filmului care ar trebui sters, conform alegerii dumneavoastra

bool film_gasit(int a[], int n, int x)
{
    for (int i = 1; i <= n; i++)
        if (a[i] == x)
            return true;
    return false;
}

void stergere_filme(movie p[], int &n, char gen[21])
{
    /// se deschise fisierul de iesire cu acelasi nume ca cel de intrare

    ofstream g(denumire_fisier);
    int nr_filme;

    cout << "Alegeti numarul de filme pe care doriti sa le stergeti: ";
    cin >> nr_filme;

    /// n scade cu numarul de filme pe care doriri sa-l stergeti din fisier

    n = n-nr_filme;

    /// se initializeaza un vector, in care se vor pune cifrele(codurile) filmelor pe care doriti sa le stergeti

    int a[nr_filme];

    /// se scriu toate filmele cu toate informatiile pe ecran

    for (int i = 1; i <= n + nr_filme; i++)
    {
        cout << i << ". " << p[i].name  << endl;
        cout << p[i].genre << endl;
        cout << p[i].release_date.date << endl;
        cout << p[i].release_date.month << endl;
        cout << p[i].release_date.year << endl;
        cout << p[i].runtime.hour << " " <<  p[i].runtime.minute << endl;
        cout << p[i].country << " " << p[i].language << endl;
        cout << p[i].cast << endl;
        cout << p[i].rating << endl;
        cout << p[i].storyline << endl;
        cout << p[i].production_company << endl;
        cout << p[i].awards << endl;
        cout << endl;
    }

    cout << "Dati cifrele filmelor pe care doriti sa le stergeti: ";

    /// se citeste cifra sau cifrele filmelor pe care doriti sa le stergeti din fisier

    for (int i = 1; i <= nr_filme; i++)
        cin >> a[i];

    g << n << endl;

    /// se scriu toate filmele in fisierul de iesire cu toate informatiile,
    /// inafara de cele pe care doriti sa le stergeti din fisier

    for (int i = 1; i <= n + nr_filme; i++)
    {
        if(film_gasit(a, nr_filme, i) == false)
        {
            g << p[i].name << endl;
            g << p[i].genre << endl;
            g << p[i].release_date.date << endl;
            g << p[i].release_date.month << endl;
            g << p[i].release_date.year << endl;
            g << p[i].runtime.hour << endl;
            g << p[i].runtime.minute << endl;
            g << p[i].country << endl;
            g << p[i].language << endl;
            g << p[i].cast << endl;
            g << p[i].rating << endl;
            g << p[i].storyline << endl;
            g << p[i].production_company << endl;
            g << p[i].awards << endl;
            g << endl;
        }
    }
}

/// se alege optiunea pentru un anumit gen de film
/// (ex: Afisare informatii despre un film, Sortare filme dupa an aparitie, Adaugare film in categorie, Stergere film, Lista filme favorite)

void info_filme(movie p[], int n, char gen[21], int cate_fav, char vector_fav[21][51])
{
    int tasta;
    do
    {
        cout << "Optiunile pentru genul de " << gen << " sunt:\n";
        optiuni();
        cout << "Apasati pe tasta dorita: ";
        cin >> tasta;

        switch(tasta)
        {
        case 1:
        {
            afisare_titluri_filme(p, n);
            int numar, alegere;

            cout << "Alegeti filmul dorit: ";
            cin >> numar;
            prezentare_film(p, numar, alegere, cate_fav, vector_fav);
        }
        break;

        case 2:
            ordonare_dupa_an(p, n);
        break;

        case 3:
            adaugare_filme(p, n, gen);
        break;

        case 4:
            stergere_filme(p, n, gen);
        break;

        case 5:
            afisare_favorite(vector_fav, cate_fav);
        break;
        }
        if(tasta != 6)
        {
            getch();
            system("cls");
        }
    }
    while(tasta != 6);
}

/// meniul aplicatiei

void meniu_aplicatie()
{
    afisare_meniu();

    movie p[2000];
    char gen[21];
    char vector_fav[21][51];
    int n;
    int cate_fav = 0;

    citire_fisier(p, n, gen);
    info_filme(p, n, gen, cate_fav, vector_fav);
}

int main()
{
    /// se apeleaza functia pentru meniul aplicatiei
    meniu_aplicatie();
    return 0;
}
