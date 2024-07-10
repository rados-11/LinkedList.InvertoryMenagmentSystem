#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

const int MAX_CHARACTERS = 15;
const std::string fileNameKnjizaraLuca = "KnjizaraLuca.txt";

struct Item {

	int id; //Unique identifier for the item
	std::string name; // Name of the item
	int quantity; // Quantity of the item in stock
	float price; // Price of the item
	Item* next;

	Item(int id, std::string name, int quantity, float price, Item* next = nullptr) : 
		id(id), name(name), quantity(quantity), price(price), next(next) {} // Default Constructor

};

int listLenght(Item* head);
void addAtTheBeginning(Item*& head, int i, std::string n, int q, float p);
void addAtTheEnd(Item*& head, int i, std::string n, int q, float p);
void addAtIndex(Item*& head, int i, std::string n, int q, float p, int k);
void printList(Item* head);
void removeByID(Item*& head, int id);
void removeByPosition(Item*& head, int p);
void updateItem(Item*& head, int id, std::string newName, int newQuantity, float newPrice);
void displayItem(Item* head, int id);
float totalValue(Item* head);
void buyItem(Item*& head, int id);
void sellItem(Item*& head, int id);
void checkout(Item*& head);
bool login(std::string u, std::string p);
Item*& getItem(Item*& head, int id);
int itemId(Item* i);
std::string itemName(Item* i);
int itemQuantity(Item* i);
float itemPrice(Item* i);
void deleteList(Item* head);
void printBasket(Item* head);
bool searchList(Item* head, int id);
std::string newName(int m);
int newQuantity(int m);
float newPrice(int m);
void saveListToFile(Item* head, const std::string& fileName);
Item* readListFromFile(Item*& head, const std::string& filename);

int main() {

	Item* knjizaraLuca = nullptr;
	Item* korpa = nullptr;

	readListFromFile(knjizaraLuca, fileNameKnjizaraLuca);

	while (true) {

		system("cls");

		int a = 0; //Odabir logovanja
		int b = 0; //Odabir za gosta
		int c = 0; //id itema koji gost zeli da kupi
		int d = 0; //id itema za uklanjanje
		int e = 0; //potvrda placanja
		int f = 0; //odabir placanja
		int g = 0; //login counter
		std::string username = "\0";
		std::string password = "\0";
		bool log = false;
		int h = 0; //neuspjelo logovanje
		int i = 5; //odabir za admina
		int j = 1; //za provjeru stanja
		int k = 0; //id itema za dodavanje
		int l = 0; //ako id itema za dodavanje nije nadjen
		int m = 0; //id itema za izmjenu

		std::cout << "0. Izadji" << std::endl;
		std::cout << "1. Prijavi se kao administrator" << std::endl;
		std::cout << "2. Nastavi kao gost" << std::endl;

		std::cin >> a;
		
		switch (a) // Logovanje
		{
		case 0:
			saveListToFile(knjizaraLuca, fileNameKnjizaraLuca);

			deleteList(knjizaraLuca);
			deleteList(korpa);
			return 0;
			break;
		case 1: // kao admin
			while (true) {
				system("cls");
				std::cout << "Korisnicko ime: ";
				std::cin >> username;
				std::cout << "Lozinka: ";
				std::cin >> password;
				log = login(username, password);
				if (!log) { //neuspjesno logovanje
					system("cls");
					std::cout << "Neuspjesno prijavljivanje!" << std::endl;
					g++;
					if (g == 3) break;
					std::cout << "Ostalo je jos " << 3 - g << " pokusaja!";
					std::cout << std::endl << "0. Nazad" << std::endl << "1. Probaj ponovo" << std::endl;
					std::cin >> h;
					if (h == 0) break;
				}
				else { //uspjesno logovanje
					while (true) {
						system("cls");
						std::cout << "Dobrodosli " << username << '!' << std::endl << std::endl;
						std::cout << "0. Povratak" <<
							std::endl << "1. Stanje" <<
							std::endl << "2. Dopuni" <<
							std::endl << "3. Izmijeni" <<
							std::endl << "4. Dodaj" <<
							std::endl << "5. Ukloni" << std::endl;
						std::cin >> i;
						if (i == 0) break;
						switch (i) {
						case 1: //1. Stanje
							while (true) {
								system("cls");
								printList(knjizaraLuca);
								std::cout << std::endl;
								std::cin >> j;
								break;
							}
							break;
						case 2: //2. Dopuna
							while (true) {
								system("cls");
								std::cout << "Uneiste ID predmeta koji zelite da dodate: ";
								std::cin >> k;
								if (searchList(knjizaraLuca, k)) {
									buyItem(knjizaraLuca, k);
									break;
								}
								else {
									system("cls");
									std::cout << "Predmet s tim IDjem nije pronadjen! Da li mozda zelite da dodate predmet?" << std::endl;
									std::cout << "0. Nazad" << std::endl << "1. Pokusaj ponovo" << std::endl;
									std::cin >> l;
									if (l == 0) break;
								}
							}
							break;
						case 3: //3. Izmijeni
							while (true) {
								system("cls");
								printList(knjizaraLuca);
								std::cout << std::endl << std::endl;
								std::cout << "Unesite ID predmeta koji zelite da izmijenite: ";
								std::cin >> m;
								if (m == 0) break;
								updateItem(knjizaraLuca, m, newName(m), newQuantity(m), newPrice(m));
								break;
							}
							break;
						case 4: //4. Dodaj
							while (true) {
								system("cls");
								std::cout << "Unesite ID artikla: " << std::endl;
								int ID = 0;
								std::cin >> ID;
								if (ID < 0) break;
								std::cout << "Unesite ime artikla: " << std::endl;
								std::string name;
								std::cin.ignore();
								std::getline(std::cin, name);
								std::cout << "Unesite kolicinu artikla: " << std::endl;
								int quantity;
								std::cin >> quantity;
								std::cout << "Unesite cijenu artikla: " << std::endl;
								float price;
								std::cin >> price;
								addAtTheBeginning(knjizaraLuca, ID, name, quantity, price);
								break;
							}
							break;
						case 5: //5. Ukloni
							system("cls");
							std::cout << "Unesite ID artikla koji zelite da uklonite: " << std::endl;
							int ID;
							std::cin >> ID;
							if (ID < 0) break;
							removeByID(knjizaraLuca, ID);
							break;
						default:
							break;
						}
					}
				}
				if (i == 0) break;
				if (g == 3) break;
			}
			break;
		case 2: // kao gost
			while (true) {
				system("cls");
				std::cout << "0. Nazad" << std::endl;
				std::cout << "1. Dodajte u korpu" << std::endl;
				std::cout << "2. Uklonite iz korpe" << std::endl;
				std::cout << "3. Platite" << std::endl;
				std::cout << std::endl;
				printBasket(korpa);
				std::cout << ", " << totalValue(korpa) << std::endl << std::endl;

				std::cin >> b;
				if (b == 0) break; //povratak
				switch (b) { // Radnja gosta
				case 1: //dodavanje u korpu
					while (true) {
						system("cls");
						printBasket(korpa);
						std::cout << std::endl;
						std::cout << "Ukupan iznos: ";
						std::cout << totalValue(korpa) << std::endl << std::endl;
						printList(knjizaraLuca);
						std::cout << std::endl << std::endl;
						std::cout << "Unesite ID predmeta koji zelite da dodate u korpu" << std::endl;
						std::cout << "Unesite 0 za nazad" << std::endl;

						std::cin >> c;
						if (c == 0) break;
						addAtTheBeginning(korpa, itemId(getItem(knjizaraLuca, c)), itemName(getItem(knjizaraLuca, c)),
							itemQuantity(getItem(knjizaraLuca, c)), itemPrice(getItem(knjizaraLuca, c)));
					}
					break;
				case 2: //uklanjanje iz korpe
					while (true) {
						system("cls");
						printBasket(korpa);
						std::cout << std::endl;
						std::cout << "Ukupan iznos: ";
						std::cout << totalValue(korpa) << std::endl << std::endl;
						printList(knjizaraLuca);
						std::cout << std::endl << std::endl;
						std::cout << "Unesite ID predmeta koji zelite da uklonite iz korpe" << std::endl;
						std::cout << "Unesite 0 za nazad" << std::endl;

						std::cin >> d;
						if (d == 0) break;
						removeByID(korpa, d);
					}
					break;
				case 3: //placanje
					while (true) {
						system("cls");
						checkout(korpa);
						std::cin >> f;
						if (f == 0) break;
						system("cls");
						std::cout << "Uspjesno placanje!" << std::endl;
						while (korpa) {
							sellItem(knjizaraLuca, korpa->id);
							korpa = korpa->next;
						}
						deleteList(korpa);
						std::cin >> e;
						korpa = nullptr;
						break;
					}
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

int listLenght(Item* head) {
	int i = 0;
	while (head) {
		i++;
		head = head->next;
	}
	return i;
}

void addAtTheBeginning(Item*& head, int i, std::string n, int q, float p) {
	Item* newItem = new Item(i, n, q, p);
	if (head) newItem->next = head;
	head = newItem;
}

void addAtTheEnd(Item*& head, int i, std::string n, int q, float p) {
	Item* newItem = new Item(i, n, q, p);
	Item* lastItem = head;
	while (lastItem->next) lastItem = lastItem->next;
	lastItem->next = newItem;
}

void addAtIndex(Item*& head, int i, std::string n, int q, float p, int k) {
	Item* newItem = new Item(i, n, q, p);
	Item* curr = head;
	int j = 0;
	while (curr) {
		j++;
		if (j == k - 1) {
			newItem->next = curr->next;
			curr->next = newItem;
			break;
		}
		curr = curr->next;
	}
}

void printList(Item* head) {
	while (head) {
		std::cout << std::setw(2) << std::setfill('0') << head->id << ' ' << std::setw(MAX_CHARACTERS) << std::setfill(' ') << std::left << head->name << ' ';
		std::cout << std::setw(2) << std::setfill('0') << std::right << head->quantity << ' ' << head->price;
		if (head->next) std::cout << std::endl;
		head = head->next;
	}
}

void removeByID(Item*& head, int id) {
	Item* curr = head;
	if (curr->id == id) {
		Item* tmp = curr->next;
		delete curr;
		head = tmp;
	}
	else {
		while (curr) {
			if (curr->next->id == id) {
				Item* tmp = curr->next;
				curr->next = tmp->next;
				delete tmp;
				break;
			}
			curr = curr->next;
		}
	}
}

void removeByPosition(Item*& head, int p) {
	if (p == 1) {
		Item* tmp = head;
		head = tmp->next;
		delete tmp;
		return;
	}
	Item* curr = head;
	int i = 0;
	while (curr) {
		i++;
		if (i == p - 1) {
			Item* tmp = curr->next;
			curr->next = tmp->next;
			delete tmp;
		}
		curr = curr->next;
	}
}

void updateItem(Item*& head, int id, std::string newName, int newQuantity, float newPrice) {
	Item* curr = head;
	while (curr) {
		if (curr->id == id) {
			curr->name = newName;
			curr->quantity = newQuantity;
			curr->price = newPrice;
			break;
		}
		curr = curr->next;
	}
}

void displayItem(Item* head, int id) {
	Item* curr = head;
	while (curr) {
		if (curr->id == id) {
			std::cout << std::setw(2) << std::setfill('0') << curr->id << ' ' << std::setw(MAX_CHARACTERS) << std::setfill(' ') << std::left << curr->name << ' ';
			std::cout << std::setw(2) << std::setfill('0') << std::right << curr->quantity << ' ' << curr->price;
			break;
		}
		curr = curr->next;
	}
}

float totalValue(Item* head) {
	float s = 0;
	while (head) s += head->price, head = head->next;
	return s;
}

void buyItem(Item*& head, int id) {
	Item* curr = head;
	while (curr) {
		if (curr->id == id) {
			curr->quantity++;
			break;
		}
		curr = curr->next;
	}
}

void sellItem(Item*& head, int id) {
	Item* curr = head;
	while (curr) {
		if (curr->id == id) curr->quantity--; break;
		curr = curr->next;
	}
}

void checkout(Item*& head) {
	std::cout << "Vas racun iznosi: " << totalValue(head) << std::endl;
	std::cout << std::endl << "Izaberite nacin placanja" << std::endl;
	std::cout << "Kreditna kartica || Gotovina" << std::endl;
}

bool login(std::string u, std::string p) {
	std::ifstream admins("admins.txt"); 
	if (!admins) {
		std::cerr << "File could not be opened for reading!" << std::endl;
		return 1;
	}
	std::string line = "\0";
	bool check = false;
	while (std::getline(admins, line)) {
		std::string username = "\0";
		std::string password = "\0";
		int i = 0;
		while (line[i] != ',') {
			username += line[i];
			i++;
		}
		if (username == u) {
			i += 2;
			while (line[i]) {
				password += line[i];
				i++;
			}
			if (password == p) {
				check = true;
				break;
			}
		}
	}
	admins.close();
	return check;
}

Item*& getItem(Item*& head, int id) {
	Item* curr = head;
	while (curr) {
		if (curr->id == id) return curr;
		curr = curr->next;
	}
	throw 1;
}

int itemId(Item* i) {
	return i->id;
}

std::string itemName(Item* i) {
	return i->name;
}

int itemQuantity(Item* i) {
	return i->quantity;
}

float itemPrice(Item* i) {
	return i->price;
}

void deleteList(Item* head) {
	while (head) {
		Item* old = head;
		head = head->next;
		delete old;
	}
}

void printBasket(Item* head) {
	std::cout << "Korpa: ";
	while (head) {
		std::cout << head->name << ' ' << head->price;
		if (head->next) std::cout << ", ";
		head = head->next;
	}
}

bool searchList(Item* head, int id) {
	bool check = false;
	while (head) {
		if (head->id == id) {
			check = true;
			break;
		}
		head = head->next;
	}
	return check;
}

std::string newName(int m) {
	std::cout << "Unesite novo ime predmeta s IDjem " << m << ": ";
	std::string name = "\0";
	std::cin.ignore();
	std::getline(std::cin, name);
	return name;
}

int newQuantity(int m) {
	std::cout << "Unesite novu kolicinu predmeta s IDjem " << m << ": ";
	int quantity = 0;
	std::cin >> quantity;
	return quantity;
}

float newPrice(int m) {
	float price = 0;
	std::cout << "Unesite novu cijenu predmeta s IDjem " << m << ": ";
	std::cin >> price;
	return price;
}

void saveListToFile(Item* head, const std::string& fileName) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Neuspjesno otvoren fajl: " << fileName << std::endl;
		return;
	}
	
	Item* curr = head;
	while (curr) {
		file << curr->id << ',' << curr->name << ',' << curr->quantity << ',' << curr->price << std::endl;
		curr = curr->next;
	}

	file.close();
}

Item* readListFromFile(Item*& head, const std::string& filename) {
	std::ifstream file(fileNameKnjizaraLuca);
	if (!file) {
		std::cerr << "Neuspjesno otvaranje fajla: " << fileNameKnjizaraLuca << std::endl;
		return nullptr;
	}

	std::string line;
	while (std::getline(file, line)) {
		int id;
		std::string ids;
		std::string name;
		int quantity;
		std::string quantitys;
		float price;
		std::string prices;
		int i = 0;
		while (line[i] != ',') {
			ids += line[i];
			i++;
		}
		id = stoi(ids);
		i++;
		while (line[i] != ',') {
			name += line[i];
			i++;
		}
		i++;
		while (line[i] != ',') {
			quantitys += line[i];
			i++;
		}
		quantity = stoi(quantitys);
		i++;
		while (line[i]) {
			prices += line[i];
			i++;
		}
		price = stof(prices);

		addAtTheBeginning(head, id, name, quantity, price);
	}

	return head;
}