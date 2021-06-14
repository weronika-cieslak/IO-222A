// projekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include<string>
#include <map>
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::list;
using std::map;

enum class language_level{A1=1, A2=2, B1=3, B2=4, C1=5,C2=6};
std::ostream& operator<<(std::ostream& o, language_level n) {
    switch (n) {
    case language_level::A1: return o << "A1";
    case language_level::A2: return o << "A2";
    case language_level::B1: return o << "B1";
    case language_level::B2: return o << "B2";
    case language_level::C1: return o << "C1";
    case language_level::C2: return o << "C2";
    default: return o << "(invalid value)";
    }
}
enum class skill_level{junior=1, regular=2, senior=3, expert=4};
std::ostream& operator<<(std::ostream& o, skill_level n) {
    switch (n) {
    case skill_level::junior: return o << "junior";
    case skill_level::regular: return o << "regular";
    case skill_level::senior: return o << "senior";
    case skill_level::expert: return o << "expert";
    
    default: return o << "(invalid value)";
    }
}
class User {
protected:
    string login;
    string password;  
    string email;
    string first_name;
    string last_name;
public:
    void set(string login, string password, string email, string first_name, string last_name)
    {
        this->login = login;
        this->password = password;
        this->email = email;
        this->first_name = first_name;
        this->last_name = last_name;
    }
    void register_account()
    {
        cout << "Login: \n";
        cin >> this->login;
        cout << "Haslo: \n";
        cin >> this->password;
        cout << "Imie: \n";
        cin >> this->first_name;
        cout << "Nazwisko: \n";
        cin >> this->last_name;
        cout << "Email: \n";
        cin >> this->email;
        
    }
    void log_in()
    {
        while (true) {
            string login_temp;
            string password_temp;
            cout << "Login: " << "\n";
            cin >> login_temp;
            cout << "Haslo: " << "\n";
            cin >> password_temp;
            if ((password_temp == this->password) && (login_temp == this->login))
            {
                cout << "zalogowano\n";
                break;
            
            }
            else {
                cout << "niepoprawne: login lub haslo\n";
            }
        }

    }
    User get_data()
    {
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const User& sd)
    {
        os << "Imie: " << sd.first_name << "\nNazwisko: " << sd.last_name << "\n";
        return os;
    }
};
struct skills {
    bool certificate;
    skill_level sk;
    string name;
    void set_skill(bool c, skill_level s, std::string n)
    {
        this->certificate = c;
        this->name = n;
        this->sk = s;
    }
    void set_skill_from_input()
    {
        cout << "Nazwa umiejetnosci: \n";
        cin >> name;
        cout << "\nWprowadz poziom tej umiejetnosci: \n";
        cout << "Poziom :\njunior :1\nregular :2\nsenior :3\nexpert :4\n";
        int userInput;
        cin >> userInput;
        sk = static_cast<skill_level>(userInput);
        cout << "Certyfikat potwierdzajacy te kompetencje?\n1-Tak\n0-Nie\n";
        cin >> certificate;
    }
    friend std::ostream& operator<<(std::ostream& os, const skills& sd)
    {
        os << "Umiejetnosc: " << sd.name << "\nPoziom: " << sd.sk << "\nCertyfikat: ";
        if (sd.certificate)
        {
            os << "Obecny\n";
        }
        else {
            os << "Brak\n";
        }
        return os;
    }
};
class Candidate :public User {
    language_level english;
    list <skills> info;
    map<string, string> statuses;
public:
    void set_language_level(language_level l)
    {
        this->english = l;
    }
    list<skills>get_info()
    {
        return info;
    }
    void set_status_of_offer(string order, string status)
    {
        statuses.insert(std::pair<string, string>(order,status));
    }
    void set_data_from_input()
    {
        cout << "Wprowadz troche informacji o sobie: \n";
        cout << "Poziom zaawansowania jezyka angielskiego: \nA1 - 1\nA2 - 2\nB1 - 3\nB2 - 4\nC1 - 5\nC2 - 6\n";
        int userInput;
        cin >> userInput;
        english = static_cast<language_level>(userInput);
        while (true)
        {
            skills s;
            cout << "Wprowadz umiejetnosc: ";
            cin >> s.name;
            cout<<"\nWprowadz poziom tej umiejetnosci: \n";
            cout << "Poziom :\njunior :1\nregular :2\nsenior :3\nexpert :4\n";
            cin >> userInput;
            s.sk = static_cast<skill_level>(userInput);
            cout << "Czy posiadasz certyfikat potwierdzajacy twoje kompetencje?\n1-Tak\n0-Nie\n";
            cin >> s.certificate;
            info.push_back(s);
            cout << "Koniec wypelniania formularza -1\n";
            int temp;
            cin >> temp;
            if (temp == 1)
            {
                break;
            }
        }
    }
    void set_data(skills s) 
    {
        info.push_back(s);
    }
    language_level get_data()
    {
        return english;
    }
    friend std::ostream& operator<<(std::ostream& os, const Candidate& sd)
    {
        os << "Imie: " << sd.first_name << "\nNazwisko: " << sd.last_name << "\n";
        for (auto i : sd.info) {
            os << i;
        }
        os << "Poziom opanowania jezyka angielskiego: " << sd.english<<std::endl;
        return os;
    }
    
};
struct order {
    User customer;
    list<Candidate>result_of_recruitment;
    list<Candidate>applications;
    string name_of_offer;
    vector<skills>requirements;
    language_level english;
    string job_offer;
    int number_of_selected_people;
    void set_status_of_candidate(Candidate x, string status)
    {
        x.set_status_of_offer(name_of_offer, status);
    }
    void set_Candidates(Candidate x)
    {
        applications.push_back(x);
    }
    list<Candidate> get_results()
    {
        return result_of_recruitment;
    }
    void print_applications()
    {
        for (auto i : applications) {
            cout << i << std::endl;
        }
    }
    void print_result()
    {
        for (auto i : result_of_recruitment) {
            cout << i << std::endl;
        }
    }
    void set_order(User c, string name_of_offer,language_level english,string job_offer,int number_of_people)
    {
        this->customer = c;
        this->name_of_offer = name_of_offer;
        this->english = english;
        this->job_offer=job_offer;
        this->number_of_selected_people = number_of_people;
    }
    void set_requirements(skills s)
    {
        requirements.push_back(s);
    }
    void make_order_in(User c)
    {
        customer = c;
        cout << "Nazwa stanowiska: ";
        cin >> name_of_offer;
        cout << "Wpisz opis oferty: ";
        cin.ignore();
        getline(cin,job_offer);
        cout << "Ile osob chcesz zaprosic na rozmowe kwalifikacyjna?\n";
        cin >> number_of_selected_people;
        cin.ignore();
        cout << "Wprowadz wymagania co do oferty pracy: \n";
        cout << "Poziom jezyka angielskiego(1-6) - skala CEFR (A1,A2,B1,B2,C1,C2): \n";
        int userInput;
        cin >> userInput;
        cin.ignore();
        english = static_cast<language_level>(userInput);
        cout << "Ile wymagan chcesz wprowadzic?\n";
        int size;
        cin >> size;
        cin.ignore();
        for (int i = 0; i < size; i++)
        {
            skills temp;
            cout << "Umiejetnosc lub nazwa jezyka programowania: \n";
            cin >> temp.name;
            cin.ignore();
            cout << "Poziom :\njunior :1\nregular :2\nsenior :3\nexpert :4\n";
            cin >> userInput;
            cin.ignore();
            temp.sk = static_cast<skill_level>(userInput);
            cout << "Wymagany certyfikat? Tak-1 Nie-0\n";
            cin >> temp.certificate;
            cin.ignore();
            requirements.push_back(temp);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const order& sd)
    {
        os <<"Pracodawca: \n"<<sd.customer<< "Tytul oferty: " << sd.name_of_offer << "\nOpis oferty: " << sd.job_offer << "\nWymagany poziom angielskiego: " << sd.english<<"\nKompetencje: \n";
        for (auto i : sd.requirements)
            os << i;
        return os;
    }
};
map<string,order> open_recruitments;
void display_recruitments()
{
    for (auto i : open_recruitments) {
        cout << i.first << std::endl;
        cout << i.second << "\n";
    }
}
class Company :public User {
    order request;
public:
    void set_request(User c, string name_of_offer, language_level english, string job_offer, int number_of_people,skills s) {
        request.set_order(c, name_of_offer, english, job_offer, number_of_people);
        request.set_requirements(s);
        open_recruitments.insert(std::pair<string, order>(request.name_of_offer, request));
    }
    void add_require(skills s)
    {
        request.set_requirements(s);
        std::map<string, order>::iterator itr = open_recruitments.find(request.name_of_offer);
        if (itr != open_recruitments.end())
            itr->second = request;
    }
    void make_request() {
        
        request.make_order_in(this->get_data());
        open_recruitments.insert(std::pair<string, order>(request.name_of_offer,request));
    }
    order get_request()
    {
        return request;
    }
    string get_name_of_offer()
    {
        return request.name_of_offer;
    }
};
class Recruiter :public User {
public:
    void recruitment_process()
    {
        map<int, Candidate>scores;
        cout << "Ktora rekrutacje chcesz przeprowadzic?\n";
        display_recruitments();
        string name;
        cin >> name;
        auto it = open_recruitments.find(name);
        order current = it->second;
        for (Candidate c : current.applications)
        {
            int score = 0;
            for (skills candidates_skill : c.get_info())
            {
                for (skills requiremented : current.requirements)
                {
                    if (candidates_skill.name == requiremented.name)
                    {
                        
                        if (candidates_skill.sk == requiremented.sk)
                        {
                            score += 1;
                        }
                        if (candidates_skill.sk > requiremented.sk)
                        {
                            score += (int)candidates_skill.sk;
                        }
                        if (candidates_skill.certificate == 1)
                        {
                            score += 2;
                        }
                        
                    }
                }
            }
            if (c.get_data() == current.english)
            {
                score += 2;
            }
            if (c.get_data() > current.english)
            {
                score += 3;
            }
            scores.emplace(score, c);
        }
    
    int number_of_people = current.number_of_selected_people;
    int temp = 0;
    for (auto iter = scores.rbegin(); iter != scores.rend(); ++iter) 
    {
        if (temp < number_of_people)
        {
           
            open_recruitments[it->first].result_of_recruitment.push_back(iter->second);
            open_recruitments[it->first].print_result();
        }
        temp = temp + 1;
    }
}
};
void Company_function(Company &sd)
{   
    cout << "Zarejestruj sie:\n";
    sd.register_account();
    cout << "Zaloguj:\n";
    sd.log_in();
    
    while (1)
    {
        cout << "Wybor dostepnych opcji: \n";
        cout << "1 - Dodaj nowa oferte pracy\n";
        cout << "2 - Modyfikuj swoja oferte pracy\n";
        cout << "3 - Przegladaj wyniki rekrutacji\n";
        cout << "4 - Zobacz obecne oferty pracy na rynku\n";
        cout << "5 - Wyloguj\n";
        int choice;
        skills s;
        cin >> choice;
        switch (choice) {
        case 1:sd.make_request(); break;
        case 2:
            cout << sd.get_request();
            cout << "Dodaj kolejne wymagania\n";
            s.set_skill_from_input();
            sd.add_require(s); break;
        case 3:open_recruitments[sd.get_name_of_offer()].print_result(); break;
        case 4:display_recruitments(); break;
        case 5:break;
        }
        if (choice == 5)
        {
            break;
        }

    }
    return;
}
void Recruiter_function(Recruiter &sd)
{
    while (true)
    {
        cout << "Wybor dostepnych opcji: \n";
        cout << "1 - Przegladaj oferty pracy\n";
        cout << "2 - Przeprowadz rekrutacje\n";
       
        cout << "3 - Wyloguj\n";
        int choice;
        
        cin >> choice;
        switch (choice) {
        case 1:display_recruitments(); break;
        case 2:sd.recruitment_process(); break;
        case 3:break;
        }
        if(choice==3)
        {
            break;
        }
    }
    return;
}
void Candidate_function(Candidate& sd)
{
    cout << "Zarejestruj sie:\n";
    sd.register_account();
    cout << "Zaloguj:\n";
    sd.log_in();
    sd.set_data_from_input();
    while (true)
    {
        cout << "Wybor dostepnych opcji: \n";
        cout << "1 - Przegladaj oferty pracy\n";
        cout << "2 - Aplikuj\n";
        cout << "3 - Wyloguj\n";
        int choice;
        cin >> choice;
        string name;
        std::map<string, order>::iterator it;
        switch (choice) {
        case 1:display_recruitments(); break;
        case 2:
            cout << "Na ktora oferte pracy chcesz aplikowac?\n";
            display_recruitments();
            cin >> name;
            it = open_recruitments.find(name);
            it->second.set_Candidates(sd); break;
        case 3:break;

        }
        if (choice == 3)
        {
            break;
        }
    }
    return;
}

int main()
{
    Company sz;
    sz.set("szef","123","szf@gmail.com","Konrad","Mars");
    skills s;
    s.set_skill(1, skill_level::regular, "Java");
    sz.set_request(sz, "Regular_Java_Developer", language_level::B1, "Twoim zakresem obowiazkow bedzie tworzenie i rozwoj oprogramowania", 1, s);
    Candidate k;
    k.set("kand34", "123", "awisniewska@gmail.com", "Anna", "Wisniewska");
    s.set_skill(0, skill_level::junior, "Java");
    k.set_data(s);
    Candidate n;
    s.set_skill(0, skill_level::junior, "Java");
    n.set_language_level(language_level::B2);
    n.set("jk", "123", "jk@mail.com", "Jacek", "Kowalski");
    n.set_data(s);
    
    Candidate l;
    l.set("kan4", "1234", "marianoo@gmail.com", "Marian", "Golab");
    s.set_skill(1, skill_level::regular, "Java");
    l.set_language_level(language_level::B2);
    l.set_data(s);

    for (auto i : open_recruitments) {
        
            open_recruitments[i.first].set_Candidates(k);
            open_recruitments[i.first].set_Candidates(l);
            open_recruitments[i.first].set_Candidates(n);
       
    }
    Recruiter r;
    r.set("kw", "1234", "kw@gmail.com", "Jan", "Nowak");
    Company firma;
    while (true)
    {
        cout << "Wybierz profil uzytkownika:\n[F]irma\n[R]ekruter\n[K]andydat na stanowisko pracy\n";
        char choice;
        cin >> choice;
        switch (choice) {
        case 'F':
            Company_function(firma); break;
        case 'R':
            Recruiter_function(r); break;
        case 'K':
            Candidate_function(k); break;
        }
    }

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
