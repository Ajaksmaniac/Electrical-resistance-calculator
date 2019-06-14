/*Izraditi konzolni program u jeziku Visual C++, koji omogućava kreiranje modela električnog kola koji se sastoji od proizvoljne serijsko - paralelne mreže otpornika.
 Osnovna klasa ElektricnoKolo treba da ima funkciju člana get_otpor().
 Izvedena klasa Otpornik treba da ima polje r, koje predstavlja otpor pojedinačnog otpornika.
 Izvedene klase SerijskoKolo i ParalenoKolo treba da sadrže pokazivače na vektore serijski ili paralelno povezanih električnih kola(s najviše 100 elemenata).
 Serijska ili paralelna električna kola mogu da se sastoje od pojedinačnih otpornika ili drugih električnih kola.
 U funkciji main() kreirati električno kolo kao na slici i prikazati njen otpor u omima.
	+--------[R1]-------+
	|                   |
 ---+					+--[R4]--
	|                   |
	+---[R2]----[R3]----+
R1 = 10K
R2 = 50
R3 = 220
R4 = 150


*/

#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class ElektricnoKolo {
public:
	float r;


	virtual float getOtpor() const = 0;


private:

};

class Otpornik : public ElektricnoKolo {
public:

	float r;
	Otpornik(float r) : ElektricnoKolo() {

		this->r = r;
	}

	virtual float getOtpor() const override {
		return this->r;
	}
	void setOtpor(float r) {
		this->r;
	}





private:

};

auto accumulate_serijsko = [](float accumulator,  Otpornik* r){
return accumulator + r->getOtpor();
};
auto accumulate_paralelno = [](float accumulator, Otpornik * r) {
	return accumulator +(1/r->getOtpor());
};



class SerijskoKolo : public ElektricnoKolo {
public:
	//R1+R2+R3
	vector <Otpornik*> serijskaVeza;

	SerijskoKolo() : ElektricnoKolo() {}

	


	void addOtpornik(Otpornik* r) {
		serijskaVeza.push_back(r);
	}

	virtual float getOtpor() const override {
		float ukupanOtpor = 0;
		
		return accumulate(serijskaVeza.begin(), serijskaVeza.end(),0, accumulate_serijsko);;
	}

private:

};
class ParalenoKolo : public ElektricnoKolo {
public:
	vector <Otpornik*> paralenaVeza;
	// (1/R1)+(1/R2)+(1/R3)
	ParalenoKolo() : ElektricnoKolo() { }
	void addOtpornik(Otpornik* r) {
		paralenaVeza.push_back(r);
	}
	virtual float getOtpor() const override {
		float ukupanOtpor = 0;
		
		return accumulate(paralenaVeza.begin(), paralenaVeza.end(), 0, accumulate_paralelno);;
	}

private:

};
SerijskoKolo serijskaVeza;
ParalenoKolo paralenaVeza;
int main() {

	Otpornik R1(10000);
	Otpornik R2(50);
	Otpornik R3(220);
	Otpornik R4(150);

	serijskaVeza.addOtpornik(&R2);
	serijskaVeza.addOtpornik(&R3);
	Otpornik R2R3(serijskaVeza.getOtpor());

	paralenaVeza.addOtpornik(&R1);
	paralenaVeza.addOtpornik(&R2R3);

	Otpornik R1R2R3R4(paralenaVeza.getOtpor() + serijskaVeza.getOtpor());
	cout << "Prikaz ukupne otpornosti elektricnog kola" << endl;

	cout << "   +--------[R1]-------+" << endl;
	cout << "   |                   |" << endl;
	cout << "---+		       +--[R4]--" << endl;
	cout << "   |                   |" << endl;
	cout << "   +---[R2]----[R3]----+" << endl;
	cout << "R1 = " << R1.getOtpor() << "KOhm" << endl;
	cout << "R2 = " << R2.getOtpor() << "Ohm" << endl;
	cout << "R3 = " << R3.getOtpor() << "Ohm" << endl;
	cout << "R4 = " << R4.getOtpor() << "Ohm" << endl;
	cout << "Ukupna otpornost = " << R1R2R3R4.getOtpor() << " Ohm" << endl;

	
	return EXIT_SUCCESS;


}