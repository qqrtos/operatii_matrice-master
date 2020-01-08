#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void citire1(double a[100][100], int& l, int& c) {
	ifstream fin("fisier1.txt");
	fin >> l >> c;
	for (int i = 1; i <= l; i++)
		for (int j = 1; j <= c; j++)
			fin >> a[i][j];
}

void citire2(int a[100][100], int& l, int& c) {
	///Pt adunare, scadere etc.
	ifstream f("fisier2.txt");
	f >> l >> c;
	for (int i = 1; i <= l; i++)
		for (int j = 1; j <= c; j++)
			f >> a[i][j];
}

void afis(double a[100][100], int l, int c) {
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= c; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
	cout << "\n\n";
}

void adunare(double a[100][100], int b[100][100], int l_a, int c_a, int l_b, int c_b) {
	if (l_a != l_b || c_a != c_b)
		cout << "\nInvalid!";
	else {
		for (int i = 1; i <= l_a; i++)
			for (int j = 1; j <= c_a; j++)
				a[i][j] += b[i][j];
		afis(a, l_a, c_a);
	}
}

void scadere(double a[100][100], int b[100][100], int l_a, int c_a, int l_b, int c_b) {
	if (l_a != l_b || c_a != c_b)
		cout << "\nImposibil!\n";
	else {
		for (int i = 1; i <= l_a; i++)
			for (int j = 1; j <= c_a; j++)
				a[i][j] -= b[i][j];
		afis(a, l_a, c_a);
	}
}

void inmultire(double a[100][100], int b[100][100], int l_a, int c_a, int l_b, int c_b) {
	if (c_a != l_b)
		cout << "\nImposibil!\n";
	else {
		double x[100][100];
		for (int i = 1; i <= l_a; i++)
			for (int j = 1; j <= c_b; j++)
				for (int k = 1; k <= c_a; k++)
					x[i][j] += a[i][k] * b[k][j];
		afis(x, l_a, c_b);
	}
}

void adun_col(double a[100][100], int l, int c_de_adunat, int c_pe_care_aduni, double e) {
	///Inmultim coloana cu -b/a si o adunam peste C initiala
	for (int i = 1; i <= l; i++)
		a[i][c_pe_care_aduni] += (a[i][c_de_adunat] * e);
}

void swap_c(double a[100][100], int c1, int c2, int l) {
	///Swap coloane
	for (int i = 1; i <= l; i++)
		swap(a[i][c1], a[i][c2]);
}

void inm_col(double a[100][100], int c, int l) {
	///In cazul in care gasim 0 pe diag principala, facem swap_c si det=det*(-1)
	for (int i = 1; i <= l; i++)
		a[i][c] *= (-1);
}

void dezvolt(double a[100][100], int l) {
	double e;
	for (int i = 1; i<l; i++)
		for (int j = i + 1; j <= l; j++) { ///Dezvoltam deasupra diagonalei principale
			if (a[i][i] == 0) {///Daca gaseste 0 pe diagonala principala, o interschimba cu prima pe care o gaseste si nu are 0 pe dp
				for (int k = i + 1; k <= l; k++)
					if (a[i][k]) {
						swap_c(a, i, k, l);
						inm_col(a, i, l);
						break;
					}
			}
			if (a[i][j]) { ///Daca e necesar sa facem 0
				double aa = a[i][j], bb = a[i][i];
				e = ((-1)*(aa / bb));
				adun_col(a, l, i, j, e);
			}
		}
}

double determinant(double a[100][100], int l) {
	double det = 1;
	dezvolt(a, l);
	for (int i = 1; i <= l; i++)
		det *= a[i][i]; ///Dupa ce am facut 0 deasupra diagonalei principale, inmultim elementele de pe ea
	return det;
}

int semn(int l, int c) { ///Returneaza semnul dat de paritatea sumei dintre nr. liniei si al coloanei
	if ((l + c) % 2 == 0)
		return 1;
	return -1;
}

void mat_tai(double a[100][100], double b[100][100], int l, int c, int n) { ///Taie linia l si coloana c
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[i][j] = a[i][j];
	for (int j = 1; j <= n; j++)
		for (int i = l; i <= n; i++)
			b[i][j] = b[i + 1][j];
	for (int i = 1; i<n; i++)
		for (int j = c; j <= n; j++)
			b[i][j] = b[i][j + 1];
}

void transpusa(double a[100][100], int n, double b[100][100]) {///Face transpusa
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[j][i] = a[i][j];
}

void init(double a[100][100], double aux[100][100], int n) {///Retine matricea a intr-o matrice auxiliara
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			aux[i][j] = a[i][j];
}

void adj(double a[100][100], int n) {///Inlocuieste fiecare element din matrice cu determinantul matricei ramase dupa ce taiem linia si coloana elementului
	double aux[100][100];
	init(a, aux, n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			double b[100][100];
			mat_tai(aux, b, i, j, n);
			double det = determinant(b, n - 1);
			a[i][j] = semn(i, j)*det;
		}
}

void adjuncta(double a[100][100], int n, double b[100][100]) { ///Face transpusa adjunctei
	adj(a, n);
	transpusa(a, n, b);
}

void inmultireS(double a[100][100], int n, double s) {///Inmulteste fiecare element al matricei cu un scalar
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] *= s;
}

void inversa(double a[100][100], int n, double b[100][100]) {///Inmulteste fiecare element din matrice cu inversul determinantului
	double aux[100][100];
	init(a, aux, n);
	double d = determinant(aux, n);
	if (d) {
		adjuncta(a, n, b);
		inmultireS(b, n, 1 / d);
		afis(b, n, n);
	}
	else cout << "Imposibil!\n";
}
