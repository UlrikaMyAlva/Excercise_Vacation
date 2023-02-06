#include <iostream>
#include <string>
#include <fstream>
#include<ios>
#include<limits>
using namespace std;
//KOMPILATOR :: GNU GCC COMPILER
//DEKLARATION AV KONSTANTER
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;
class Transaktion {
 private:
 string datum;
 string typ;
 string namn;
 double belopp;
 int antal_kompisar;
 string kompisar[MAX_PERSONER];
 public:
 Transaktion();
 ~Transaktion();
 string hamtaNamn();
 double hamtaBelopp();
 int hamtaAntalKompisar();
 bool finnsKompis(const string &namnet);
 bool lasin (istream &is);
 void skrivut (ostream &os);
 void skrivTitel (ostream &os);
};
class Person {
 private:
 string namn;
 double betalat_andras;
 double skyldig;
 public:
 Person();
 Person(const string &namn, double betalat_andras, double skyldig);
 string hamtaNamn();
 double hamtaBetalat();
 double hamtaSkyldig();
 void skrivUt(ostream &os);
};
class PersonLista {
 private:
 int antal_personer;
 Person personer[MAX_PERSONER];
 public:
 PersonLista();
 ~PersonLista();
 void laggTill(Person ny_person);
 void skrivUtOchFixa(ostream &os);
 double summaSkyldig();
 double summaBetalat();
 bool finnsPerson(const string& namn);
 };
class TransaktionsLista {
private:
 int antal_transaktioner;
 Transaktion transaktioner[MAX_TRANSAKTIONER];
public:
 TransaktionsLista();
 ~TransaktionsLista();
 void lasIn(istream & is);
 void skrivUt(ostream & os);
 void laggTill(Transaktion & t);
 double totalKostnad();
 double liggerUteMed(const string &namnet);
 double arSkyldig(const string &namnet);
 PersonLista fixaPersoner();
};
int main() {
TransaktionsLista transaktionsLista;
cout << "Startar med att l\x84sa fr\x86n en fil" << endl;
ifstream fin("resa.txt"); //L ser fr n fil � �
transaktionsLista.lasIn(fin);
int operation = 1;
while (operation !=0) {
 cout << endl;
 cout << "V\x84lj i menyn nedan:" << endl;
 cout << "0. Avsluta. Alla transaktioner sparas p\x86 fil." << endl;
 cout << "1. Skriv ut information om alla transaktioner." << endl;
 cout << "2. L\x84s in en transaktion fr\x86n tangentbordet." << endl;
 cout << "3. Ber\x84kna totala kostnaden." << endl;
 cout << "4. Hur mycket \x84r en viss person skyldig?" << endl;
 cout << "5. Hur mycket ligger en viss person ute med?" << endl;
 cout << "6. Lista alla personer mm och FIXA" << endl;
 cin >> operation;
 cout << endl;
 switch (operation) {
 case 1:
 {
 transaktionsLista.skrivUt(cout);
 break;
 }
 case 2:
 {
 Transaktion transaktion;
 cout << "Skriv in i f\x94ljande format: " << endl;
 transaktion.skrivTitel(cout);
 transaktion.lasin(cin);
 transaktionsLista.laggTill(transaktion);
 break;
 }
 case 3:
 {
 cout << "Den totala kostnanden f\x84r resan var " <<
transaktionsLista.totalKostnad() << "kr." << endl;
 break;
 }
 case 4:
 {
 cout << "Ange personen: ";
 string namn;
 cin >> namn;
 double ar_skyldig = transaktionsLista.arSkyldig(namn);
 if (ar_skyldig == 0.)
 cout << "Kan inte hitta personen " << namn << endl;
 else
 cout << namn << " \x84r skyldig " << ar_skyldig << endl;
 break;
 }
 case 5:
 {
 cout << "Ange personen: ";
 string namn;
 cin >> namn;
 double ligger_ute_med = transaktionsLista.liggerUteMed(namn);
 if (ligger_ute_med == 0.)
 cout << "Kan inte hitta personen " << namn << endl;
 else
 cout << namn << " ligger ute med " << ligger_ute_med << endl;
 break;
 }
 case 6:
 {
 cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
 PersonLista lista = transaktionsLista.fixaPersoner();
 lista.skrivUtOchFixa(cout);
 break;
 }
 }
}
ofstream fout("transaktioner.txt");
//ofstream fout("resa.txt");
transaktionsLista.skrivUt(fout);
return 0;
}
//FUNKTIONER::TRANSAKTION
Transaktion::Transaktion() {
 datum = "";
 typ = "";
 namn = "";
 belopp = 0.0;
 antal_kompisar = 0;
 for (int i = 0; i <MAX_PERSONER; i++) {
 kompisar[i] = "";
 }
}
Transaktion::~Transaktion() {
 //cout << "Nu d das jag!" << endl; �
}
string Transaktion::hamtaNamn () {
 return namn;
}
double Transaktion::hamtaBelopp() {
 return belopp;
}
int Transaktion::hamtaAntalKompisar() {
 return antal_kompisar;
}
bool Transaktion::finnsKompis(const string &namnet) {
 int finns = 0;
 for (int i = 0; i < antal_kompisar; i++) {
 if (namnet == kompisar[i]){
 finns = finns + 1;
 }
 else {
 }
 }
 //Om kompis finns i listan (mer n 0) return true �
 if (finns > 0) {
 return true;
 }
 else {
 return false;
 }
}
bool Transaktion::lasin (istream &is) {
 is >> datum >> typ >> namn >> belopp >> antal_kompisar;
 for (int i = 0; i < antal_kompisar; i++){
 is >> kompisar[i];
 }
 return !is.eof();
}
void Transaktion::skrivut(ostream &os) {
 os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" <<
antal_kompisar << "\t";
 for (int i = 0; i < antal_kompisar; i++){
 os << kompisar[i] << "\t";
 }
 cout << endl;
}
void Transaktion::skrivTitel(ostream &os) {
 os << "Datum\t Aktivitet\t Namn\t Belopp\t Antal\t Lista med kompisar" << endl;
}
//FUNKTIONER::PERSON
Person::Person() {
 namn = "";
 betalat_andras = 0.0;
 skyldig = 0.0;
}
Person::Person(const string &namn, double betalat_andras, double skyldig) {
 this->namn = namn;
 this->betalat_andras = betalat_andras;
 this->skyldig = skyldig;
}
string Person::hamtaNamn() {
 return namn;
}
double Person::hamtaBetalat() {
 return betalat_andras;
}
double Person::hamtaSkyldig() {
 return skyldig;
}
void Person::skrivUt(ostream &os) {
 os << namn << "\t" << betalat_andras << "\t" << skyldig << endl;
}
//FUNKTIONER::PERSONLISTA
PersonLista::PersonLista() {
 Person person;
 for (int i = 0; i < MAX_PERSONER; i++) { //Var tvungen att ta bort <=, annars
krashade det
 personer[i] = Person();
 }
}
PersonLista::~PersonLista() {
 //cout << "Nu d das jag!" << endl; �
}
void PersonLista::laggTill(Person ny_person) {
 for (int i = 0; i < MAX_PERSONER; i++) {
 //Om platsen r tom (dvs det finns inget namn inlagt) �
 if (personer[i].hamtaNamn() == ""){
 //L gg till en ny person d r � �
 personer[i] = Person(ny_person);
 //Fyll p i till max (s att inte personen l ggs in i alla ytterliga � � �
kolumner)
 i = MAX_PERSONER;
 }
 }
}
void PersonLista::skrivUtOchFixa(ostream &os) {
 Person person;
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (personer[i].hamtaNamn() != "") { //S l nge det inte r en "tom" person � � �
 os << personer[i].hamtaNamn() << " ligger ute med " <<
personer[i].hamtaBetalat() << " och \x84r skyldig " << personer[i].hamtaSkyldig();
 if (personer[i].hamtaBetalat() - personer[i].hamtaSkyldig() < 0){ //Om
summan blir negativ ska personen betala detta till potten
 //Multiplicerar med -1 f r att f ett positivt tal � �
 os << ". Skall l\x84gga till " << (personer[i].hamtaBetalat() -
personer[i].hamtaSkyldig()) * (-1) << " till potten!" << endl;
 }
 else { //Om summan r positiv �
 os << ". Skall ha " << personer[i].hamtaBetalat() -
personer[i].hamtaSkyldig() << " fr\x86n potten!" << endl;
 }
 }
 }
 double skyldig = summaSkyldig();
 double betalat = summaBetalat();
// cout << "Summa skyldig: " << skyldig << endl;
// cout << "Summa betalat: " << betalat << endl;
}
double PersonLista::summaSkyldig() {
 double summaSkyldig = 0.0;
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (personer[i].hamtaSkyldig() != 0.0) { //S l nge det inte r en tom � � �
person
 summaSkyldig += personer[i].hamtaSkyldig();
 }
 }
 return summaSkyldig;
}
double PersonLista::summaBetalat() {
 double summaBetalat = 0.0;
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (personer[i].hamtaBetalat() != 0.0) { //S l nge det inte r en tom � � �
person
 summaBetalat += personer[i].hamtaBetalat();
 }
 }
 return summaBetalat;
}
bool PersonLista::finnsPerson(const string& namn) {
 string temp;
 for (int i = 0; i < MAX_PERSONER; i++) {
 temp = personer[i].hamtaNamn();
 if (temp == namn) {
 return true;
 }
 else {
 return false;
 }
 }
}
//FUNKTIONER::TRANSAKTIONSLISTA
TransaktionsLista::TransaktionsLista() {
 Transaktion transaktion;
 for (int i = 0; i <= MAX_PERSONER; i++) {
 transaktioner[i] = Transaktion(); //Max personer s tts till tom transaktion �
(konstruktor)
 }
}
TransaktionsLista::~TransaktionsLista() {
 //cout << "Nu d das jag!" << endl; �
}
void TransaktionsLista::lasIn(istream & is) {
 Transaktion transaktion;
 int i = 0;
 while (transaktion.lasin(is)){
 laggTill( transaktion );
 }
}
void TransaktionsLista::skrivUt(ostream &os){
 Transaktion transaktion;
 //S l nge array Transaktioner har objekt i sig = � �
 for (int i = 0; i < MAX_TRANSAKTIONER; i++) {
 if (transaktioner[i].hamtaBelopp() != 0) { // = vilket r lika med att �
beloppet inte r tomt �
 //S tt det aktuella transaktionsobjeket till transaktioner[i] �
 transaktion = transaktioner[i];
 transaktion.skrivut(os);
 }
 }
}
void TransaktionsLista::laggTill(Transaktion& t) {
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (transaktioner[i].hamtaBelopp() == 0.0) {
 transaktioner[i] = Transaktion(t);
 i = MAX_PERSONER;
 }
 }
}
double TransaktionsLista::totalKostnad() {
 double totalkostnad = 0.0;
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (transaktioner[i].hamtaBelopp() != 0.0) {
 totalkostnad += transaktioner[i].hamtaBelopp();
 }
 }
 return totalkostnad;
}
double TransaktionsLista::liggerUteMed(const string &namnet) {
 double kostnadNamn = 0.0;
 for (int i = 0; i < MAX_PERSONER; i++) {
 if (transaktioner[i].hamtaBelopp() != 0.0 && transaktioner[i].hamtaNamn()
== namnet){
 kostnadNamn += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 /
(transaktioner[i].hamtaAntalKompisar() + 1));
 }
 }
 return kostnadNamn;
}
double TransaktionsLista::arSkyldig(const string &namnet) {
double totalBelopp = 0.0;
bool svar;
 for (int i = 0; i < MAX_TRANSAKTIONER; i++) {
 svar = transaktioner[i].finnsKompis(namnet);
 if (svar == true) {
 totalBelopp += transaktioner[i].hamtaBelopp() /
(transaktioner[i].hamtaAntalKompisar() + 1);
 } else {
 //cout << namnet << " deltog ej i nr " << i + 1 << "transaktion" <<
endl;
 }
 }
return totalBelopp;
}
PersonLista TransaktionsLista::fixaPersoner() {
 PersonLista personlista;
 string tempNamn;
 double tempSkyldig;
 double tempBetalat;
 for (int i = 0; i < MAX_PERSONER; i++) {
 //S l nge namnet inte finns i personlista och namnet inte r tomt, l gg � � � �
till en ny person, som sedan l ggs till i personlista �
 if (!personlista.finnsPerson(transaktioner[i].hamtaNamn()) &&
transaktioner[i].hamtaNamn() != "") {
 tempNamn = transaktioner[i].hamtaNamn();
 tempBetalat = liggerUteMed(tempNamn);
 tempSkyldig = arSkyldig(tempNamn);
 Person person = Person(tempNamn,tempBetalat,tempSkyldig);
 personlista.laggTill(person);
 }
 else{
 //cout << "Personen finns" << endl;
 }
 }
 return personlista;
}
