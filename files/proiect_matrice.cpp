#include "stdafx.h"
#include "matrice.h"

void main() {
	int x = 1;
	while (x) {
		cout << "\nOptiuni:\n";
		cout << "1-Citire";
		cout << "\n2-Afisare";
		cout << "\n3-Adunare (cititi matricea)";
		cout << "\n4-Scadere (cititi matricea)";
		cout << "\n5-Inmultire (cititi matricea)";
		cout << "\n6-Determinant";
		cout << "\n7-Inversa";
		cout << "\n8-Clear screen";
		cout << "\n9-Iesire\n\n";

		int a, l, c;
		double m[100][100];
		cout << "Optiune:  ";
		cin >> a;

		switch (a) {
		case 1: {
			system("CLS");
			citire1(m, l, c);
			break;
		}
		case 2: {
			system("CLS");
			afis(m, l, c);
			break;
		}
		case 3: {
			system("CLS");
			int n[100][100], l_n, c_n;
			citire2(n, l_n, c_n);
			adunare(m, n, l, c, l_n, c_n);
			break;
		}
		case 4: {
			system("CLS");
			int n[100][100], l_n, c_n;
			citire2(n, l_n, c_n);
			scadere(m, n, l, c, l_n, c_n);
			break;
		}
		case 5: {
			system("CLS");
			int n[100][100], l_n, c_n;
			citire2(n, l_n, c_n);
			inmultire(m, n, l, c, l_n, c_n);
			break;
		}
		case 6: {
			system("CLS");
			if (l == c)
				cout << determinant(m, l) << "\n\n";
			else
				cout << "\nImposibil!\n";
			break;
		}
		case 7: {
			system("CLS");
			double n[100][100];
			inversa(m, l, n);
			break;
		}
		case 8: {
			system("CLS");
			break;
		}

		case 9: {
			x = 0;
		}
		}
	}
}
