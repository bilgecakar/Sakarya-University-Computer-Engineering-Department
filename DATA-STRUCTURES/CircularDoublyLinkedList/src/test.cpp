#include <CircularDoublyLinkedList.hpp>

int main() {
	CircularDoublyLinkedList<string>* names = new CircularDoublyLinkedList<string>();
	int input = 0;
	string name;
	int index;
	do {
		system("CLS");
		cout << "1.  isim ekle" << endl;
		cout << "2.  isim sil" << endl;
		cout << "3.  konumdan isim sil" << endl;
		cout << "4.  konumdan isim ekle" << endl;
		cout << "5.  konum bul" << endl;
		cout << "6.  isim sayisi" << endl;
		cout << "7.  ilk isim" << endl;
		cout << "8.  son isim" << endl;
		cout << "9.  isimleri listele" << endl;
		cout << "10. isimleri temizle" << endl;
		cout << "11. cikis" << endl;
		cout << "12. isimleri konumdan basa kadar tersten listele" << endl;
		cout << "13. isimleri tersten listele" << endl;
		cout << "secim:" << endl;
		cin >> input;
		system("CLS");
		switch (input) {
		case 1:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Add(name);
			break;
		case 2:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Remove(name);
			break;
		case 3:
			cout << "konum:";
			cin >> index;
			names->RemoveAt(index);
			break;
		case 4:
			cout << "konum:";
			cin >> index;
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Insert(index, name);
			break;
		case 5:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			cout << "konum:" << names->IndexOf(name);
			cin.get();
			break;
		case 6:
			cout << "isim sayisi:" << names->Count() << endl;
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "ilk isim:" << names->First() << endl;
			cin.ignore();
			cin.get();
			break;
		case 8:
			cout << "son isim:" << names->Last() << endl;
			cin.ignore();
			cin.get();
			break;
		case 9:
			cout << "isimler:" << endl;
			cout << *names << endl;
			cin.ignore();
			cin.get();
			break;
		case 10:
			names->Clear();
			cout << endl << "isimler silindi." << endl;
			cin.ignore();
			cin.get();
			break;
		case 11:
			cout << "cikiliyor..";
			cin.ignore();
			cin.get();
			break;
		case 12:
			cout << "konum:";
			cin >> index;
			names->PrintAllFromIndexReversed(index);
			cin.ignore();
			cin.get();
			break;
		case 13:
			names->PrintAllReversed();
			cin.ignore();
			cin.get();
			break;
		default:
			cout << endl << "hatali giris!" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("CLS");
	} while (input != 11);
	delete names;
	return 0;
}