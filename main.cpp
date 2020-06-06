#include <iostream>
#include <fstream>
#include "MainAlgo.h"
#include "Mgzn.h"
#include "Sclad.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace std;

int main(){
	ifstream in;
	char symbol = 0;
	int str = 0, stlb = 0;

	in.open("Map.txt");
	while (symbol != -1){
		symbol = (char) in.get();
		if (symbol == '0'){
			stlb++;
		}
		else if (symbol == '1'){
			stlb++;
		}
		else if (symbol == '2'){
			stlb++;
		}
		else if (symbol == '3'){
			stlb++;
		}
        else if (symbol == '\n'){
			str++;
		}
	}
	in.close();
	stlb = stlb / str;
	int** arr = new int* [str];
	for (int i = 0; i < str; i++){
		arr[i] = new int[stlb];
	}
	in.open("Map.txt");
	for (int i = 0; i < str; i++){
		for (int j = 0; j < stlb; j++){
			in >> arr[i][j];
		}
	}
	in.close();

	int sclad = 0, magaz = 0;
	for (int i = 0; i < str; i++){
		for (int j = 0; j < stlb; j++){
			if (arr[i][j] == 3){
				sclad++;
			}
			if (arr[i][j] == 2){
				magaz++;
			}
			if(arr[i][j] == 3 && arr[i+1][j] == 1 && arr[i-1][j] == 1 && arr[i][j+1] == 1 && arr[i][j-1] == 1){
				cout << "Error (sklad zablokirovan)" << endl;
				return 0;
			} else if (arr[i][j] == 2 && arr[i + 1][j] == 1 && arr[i - 1][j] == 1 && arr[i][j + 1] == 1 && arr[i][j - 1] == 1){
				cout << "Error (magazin zablokirovan)" << endl;
				return 0;
			}
		}
	}


	if (sclad > 1){
		cout << "Error (mnogo skladov)" << endl;
		return 0;
	} else if (sclad == 0){
		cout << "Error (net skladov)" << endl;
		return 0;
	}
	if (magaz == 0){
		cout << "Error (net magazinov)" << endl;
		return 0;
	}

	MainAlgo obj;

	for (int i = 0; i < str; i++){
		for (int j = 0; j < stlb; j++){
			if (arr[i][j] == 2) {
				Mgzn mag(i, j);
				obj.setMgzn(mag);
			}
			else if (arr[i][j] == 3){
				Sclad scl(i, j);
				obj.setSclad(scl);
			}
		}
	}

	vector<Zveno> tN;
	tN.push_back(obj.scl);
	for (Mgzn i : obj.wh){
		tN.push_back(i);
	}

	int iter = tN.size();
	Zveno b, e;
	for (int i = 0; i < iter; i++){
		Road Road;
		if (i==0){
			b = tN[0];
			Road.setbgn (b);
			float min = obj.shrtRoad(b, tN[1]);
			for (int j = 1; j < tN.size(); j++){
				if (obj.shrtRoad(b, tN[j]) < min){
					min = obj.shrtRoad(b, tN[j]);
				}
			}
			for (int j = 1; j < tN.size(); j++){
				if (obj.shrtRoad(b, tN[j]) == min){
					Road.setEnd(tN[j]);
					b = tN[j];
					tN.erase(tN.begin() + j);
					break;
				}
			}
		}
		else if(i == iter-1){
			Road.setbgn(b);
			e = tN.back();
			Road.setEnd(e);
		}
		else{
			Road.setbgn(b);
			float min = obj.shrtRoad(b, tN[iter-i-1]);
			for (int j = 1; j < iter - i; j++){
				if (obj.shrtRoad(b, tN[j]) < min){
					min = obj.shrtRoad(b, tN[j]);
				}
			}
			for (int j = 1; j < iter - i; j++){
				if (obj.shrtRoad(b, tN[j]) == min){
					Road.setEnd(tN[j]);
					b = tN[j];
					tN.erase(tN.begin() + j);
					break;
				}
			}
		}
		obj.setRoad(Road);
	}
	int c = 0;
	for (Road l : obj.Roads){
		int x = l.bgn.i, y = l.bgn.j;

		while ((x != l.end.i) || (y != l.end.j)){

			if (x < l.end.i){
				if (c > stlb * str){
					break;
				}
				if (arr[x + 1][y] != 1){
					x++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x][y + 1] != 1){
					y++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					if (arr[x + 1][y] != 1){
						x++;
						arr[x][y] = 4;
						c++;
						if ((x == l.end.i) && (y == l.end.j)){
							arr[x][y] = 5;
							break;
						}
						continue;
					}
					continue;
				}
				else if (arr[x - 1][y] != 1){
					x--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)) {
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x][y-1] != 1){
					y--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
			}
			if (y < l.end.j){
				if (c > stlb * str){
					break;
				}
				if (arr[x][y + 1] != 1){
					y++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x - 1][y] != 1){
					x--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					if (arr[x][y + 1] != 1){
						y++;
						arr[x][y] = 4;
						c++;
						if ((x == l.end.i) && (y == l.end.j)){
							arr[x][y] = 5;
							break;
						}
						continue;
					}
					continue;
				}
				else if (arr[x + 1][y] != 1){
					x++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x][y - 1] != 1){
					y--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
			}

			if (x > l.end.i){
				if (c > stlb * str){
					break;
				}
				if (arr[x - 1][y] != 1){
					x--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x][y - 1] != 1){
					y--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					if (arr[x - 1][y] != 1) {
						x--;
						arr[x][y] = 4;
						c++;
						if ((x == l.end.i) && (y == l.end.j)){
							arr[x][y] = 5;
							break;
						}
						continue;
					}
					continue;
				}
				else if (arr[x][y + 1] != 1){
					y++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x + 1][y] != 1){
					x++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
			}
			if (y > l.end.j){
				if (c > stlb * str){
					break;
				}
				if (arr[x][y - 1] != 1){
					y--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x + 1][y] != 1){
					x++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					if (arr[x][y - 1] != 1){
						y--;
						arr[x][y] = 4;
						c++;
						if ((x == l.end.i) && (y == l.end.j)){
							arr[x][y] = 5;
							break;
						}
						continue;
					}
					continue;
				}
				else if (arr[x - 1][y] != 1){
					x--;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
				else if (arr[x][y + 1] != 1){
					y++;
					arr[x][y] = 4;
					c++;
					if ((x == l.end.i) && (y == l.end.j)){
						arr[x][y] = 5;
						break;
					}
					continue;
				}
			}
		}
	}

	sf::RenderWindow window(sf::VideoMode(800, 800), "Commi", sf::Style::Default);
	sf::Image img;
	img.loadFromFile("texture.jpg");
	sf::Texture txtr;
	txtr.loadFromImage(img);
	sf::Sprite sprite;
	sprite.setTexture(txtr);


	while (window.isOpen()){
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (int i = 0; i < str; i++){
			for (int j = 0; j < stlb; j++){
				if (arr[i][j] == 5)
                sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
				if (arr[i][j] == 0)
				sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
				if (arr[i][j] == 4)
				sprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
				if (arr[i][j] == 1)
				sprite.setTextureRect(sf::IntRect(256, 0, 64, 64));
				sprite.setPosition(j * 48, i * 48);
				window.draw(sprite);
			}
		}
		window.display();
	}

	cout << "Way: " << c << " steps " << endl;

	for (int i = 0; i < str; i++){
		delete[] arr[i];
	}
}

