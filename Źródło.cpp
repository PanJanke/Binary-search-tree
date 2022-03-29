#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct TreeBST {
	TreeBST* up=nullptr;
	TreeBST* left=nullptr;
	TreeBST* right=nullptr;
	int key;
	string name;

};

void In_order(TreeBST* root) {
	if(root->left != nullptr)
		In_order(root->left);
	cout << root->key << "  -  " << root->name << endl;
	if(root->right != nullptr)
		In_order(root->right);

}
/*
struct TreeBST* max_node(TreeBST* root) {
	TreeBST* tmp = root;
	while (tmp->right != nullptr)
		tmp = tmp->right;

	return tmp;
}
*/
struct TreeBST* min_node(TreeBST* root) {
	TreeBST* tmp = root;
	while (tmp->left != nullptr)
		tmp = tmp->left;

	return tmp;
}
/*
struct TreeBST* find_predecressor(TreeBST* tmp) {

	if (tmp->left != nullptr)
		return max_node(tmp->left);

	else {
		TreeBST* tmp2;
		do
		{
			tmp2 = tmp;
			tmp = tmp->up;
		} while (tmp !=nullptr && (tmp->right != tmp2));

		return tmp;
	

	}
}
*/
struct TreeBST* find_successor(TreeBST* tmp) {


	if (tmp->right != nullptr)
		return min_node(tmp->right);

	else {
		TreeBST* tmp2;
			do
			{
				tmp2 = tmp;
				tmp = tmp->up;
			} while (tmp != nullptr && (tmp->left != tmp2));

			return tmp;

	}


}


void add_Node(TreeBST* &root, int key,string name) {
	TreeBST* tmp;

	if (root == nullptr) {
		tmp = new TreeBST;
		tmp->up = nullptr;
		tmp->key = key;
		tmp->name = name;
		root = tmp;
	}
	else if (key < root->key) {
		if (root->left != nullptr)
			add_Node(root->left, key, name);
		else {
			tmp = new TreeBST;
			tmp->up = root;
			tmp->key = key;
			tmp->name = name;
			root->left = tmp;
		}
	}
	else {
		if (root->right != nullptr)
			add_Node(root->right, key, name);
		else {
			tmp = new TreeBST;
			tmp->left = nullptr;
			tmp->right = nullptr;
			tmp->up = root;
			tmp->key = key;
			tmp->name = name;
			root->right = tmp;
		}
	}





}

struct TreeBST* find_node(TreeBST* root, int key){
	if (key == root->key)
		return root;
	else if (key < root->key && root->left != nullptr)
		find_node(root->left,key);
	else if (key > root->key && root->right != nullptr)
		find_node(root->right,key);

	else
	return nullptr;
}

void delete_Node(TreeBST*& root, TreeBST* tmp) {

	//usuwany wezel nie posiada dzieci
	if (tmp->left == nullptr && tmp->right == nullptr) {
		if (tmp->up == nullptr) //przypadek gdy usuwany wezel jest korzeniem
			tmp = nullptr;
		else {
			if (tmp->up->left == tmp) {
				tmp->up->left = nullptr;
				delete tmp;
			}

			else if (tmp->up->right == tmp) {
				tmp->up->right = nullptr;
				delete tmp;
			}
		}
		return;
	}


	// usuwany wezel posiada tylko jedno dziecko
	if (tmp->left == nullptr || tmp->right == nullptr) {

		if (tmp->up == nullptr) {//przypadek gdy usuwany wezel jest korzeniem
			
			if (tmp->left == nullptr) {//istnieje dziecko prawe
				root = tmp->right;
				delete tmp;
			}

			if (tmp->right == nullptr) {//istnieje dziecko lewe
				root = tmp->left;
				delete tmp;
			}

		}





		//istnieje dziecko prawe
		if (tmp->left == nullptr){
			
			if (tmp->up->left == tmp) {
				tmp->up->left = tmp->right;
				delete tmp;
			}

			if (tmp->up->right == tmp) {
				tmp->up->right = tmp->right;
				delete tmp;
			}


		}

		//istnieje dziecko lewe
		if (tmp->right == nullptr) {

			if (tmp->up->left == tmp) {
				tmp->up->left = tmp->left;
				delete tmp;
			}

			else if (tmp->up->right == tmp) {
				tmp->up->right = tmp->left;
				delete tmp;
			}


		}

		return;
	}

	// usuwany wezel posiada dwoje dzieci
	if (tmp->left != nullptr && tmp->right != nullptr) {

		
		TreeBST* tmp2 = find_successor(tmp);
		tmp->key = tmp2->key;
		tmp->name = tmp2->name;
		delete_Node(root,tmp2);


		return;
	}

}

void wait(int sekundy)
{
	clock_t koniec_czekania;
	koniec_czekania = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec_czekania) {}
}


string name_generator(string tab[]) {
	return tab[rand() % 10] + tab[rand() % 10];
}

int main() {

	string tab[10];
	tab[0] = "bo";
	tab[1] = "na";
	tab[2] = "da";
	tab[3] = "ci";
	tab[4] = "li";
	tab[5] = "wu";
	tab[6] = "zy";
	tab[7] = "ma";
	tab[8] = "ro";
	tab[9] = "ka";
	

	
	TreeBST* root = nullptr;
	int a, n, s,klucz, klucz2, czas;
	string name;
	

	jump:
	cout << "Ilu zawodnikow puscic:" << endl;
	cin >> n;
	cout << " Ile sekund przerwy pomiedzy kolejnymi startami:" << endl;
	cin >> s;

	for (int i = 0; i < n; i++) {
		czas = rand() % 360;
		name = name_generator(tab);
		add_Node(root, czas, name);
		cout << "Dodano zawodnika: " << name << " - " << czas << endl;
		wait(s);
	}

	for (;;) {
		cout << "\n1 - dodaj kolejnych zawodnikow" << endl;
		cout << "2 - Wyswietl wyniki rosnaco" << endl;
		cout << "3 - Znajdz zawodnika i zmien mu wynik" << endl;

		cin >> a;
		cout << "\n";
		switch (a) {
		case 1:
			goto jump;
			break;

		case 2:
			In_order(root);
			break;

		case 3:
			jump2:
			cout << "Podaj czas:" << endl;
			cin >> klucz;
			TreeBST* tmp = find_node(root, klucz);
			if (tmp == nullptr) {
				cout << "Nieznaleziono zawodnika o podanym czasie" << endl;
				goto jump2;
			}

			cout << "Podaj nowy czas: " << endl;
			cin >> klucz2;
			string name2 = tmp->name;
			delete_Node(root, tmp);
			add_Node(root, klucz2, name2);
			break;
		}

	}



	return 0;
}