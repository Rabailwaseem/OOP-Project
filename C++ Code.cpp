#define CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <map>
 


#define ff system("pause");


HANDLE COLOR = GetStdHandle(STD_OUTPUT_HANDLE);
const int MAX_SNAKE_SIZE = 100;
const int WALLS_COLOR = 2;


//class Map;

void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void text(int i)
{
	CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 900;
	fontex.dwFontSize.Y = i;
	SetCurrentConsoleFontEx(hOut, 1, &fontex);
}

void show_map_2()
{


	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	int x;
	gotoxy(0, 0);
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	for (x = 19; x < 58; x++)
	{
		gotoxy(x, 4);

		cout << char(196);
		gotoxy(x, 13);
		cout << char(196);
	}
	cout << endl;

	SetConsoleTextAttribute(COLOR, 7);
	gotoxy(0, 22);

}

void show_map_3()
{
	int x;
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	x = 36;

	while (++x < 40)
	{
		gotoxy(x, 8);
		cout << char(196);
		gotoxy(x, 10);
		cout << char(196);
	}
	gotoxy(36, 8);


	cout << char(218);
	gotoxy(36, 9);


	cout << char(179);
	gotoxy(36, 10);


	cout << char(192);
	gotoxy(40, 9);

	cout << char(179);
	gotoxy(40, 8);

	cout << char(191);
	gotoxy(40, 10);

	cout << char(217);
	x = 20;
	while (++x < 31)
	{
		gotoxy(x, 3);
		cout << char(196);
		gotoxy(x, 14);
		cout << char(196);
	}
	x = 46;
	while (++x < 59)
	{
		gotoxy(x, 3);
		cout << char(196);
		gotoxy(x, 14);

		cout << char(196);
	}
	x = 3;
	while (++x < 7)
	{
		gotoxy(20, x);

		cout << char(179);
		gotoxy(58, x);

		cout << char(179);
	}
	x = 10;
	while (++x < 14)
	{
		gotoxy(20, x);

		cout << char(179);
		gotoxy(58, x);
		cout << char(179);
	}
	gotoxy(58, 3);

	cout << char(191);
	gotoxy(20, 14);

	cout << char(192);
	gotoxy(20, 3);

	cout << char(218);
	gotoxy(58, 14);

	cout << char(217);
	SetConsoleTextAttribute(COLOR, 7);
	gotoxy(0, 22);
}


class Point
{
private:
	int x = -1, y = -1;
public:

	Point(int i = 2, int j = 2) : x(i), y(j) { }
	inline void set_x(int i = -1) { x = i; }
	inline void set_y(int i = -1) { y = i; }
	inline int& get_x() { return x; }
	inline int& get_y() { return y; }
	inline void up() { y--;  if (y < 0) y = 18; };
	inline void down() { y++; if (y > 18) y = 0; }
	inline void left() { x = x - 2; if (x < 0) x = 78; };
	inline void right() { x = x + 2; if (x > 78) x = 0; };
	inline void print(char c)
	{
		gotoxy(x, y);
		cout << c;
	}
	inline void randomize(int i = 0);

	inline bool operator==(const Point& obj) const
	{
		return (x == obj.x) && (y == obj.y);
	}
	inline void operator=(const Point& obj)
	{
		x = obj.x;
		y = obj.y;
	}

	void debug()
	{
		//gotoxy(20,20) ;
		cout << "(" << x << "," << y << ")" << endl;
	}
};



class Map
{
public:
	int size = 0;
	Point map_array[100];
	map <pair<int, int>, bool> hash;


	void load_map(int choice = 0)
	{
		if (!choice) return;
		ifstream map_file;
		string name;
		if (choice == 1)
		{
			name = "map_2.txt";
			size = 78;
			show_map_2();
		}
		else
		{
			name = "map_3.txt";
			size = 75;
			show_map_3();
		}

		map_file.open(name);

		int x = 0;
		int y = 0;
		for (int i = 0; i < size; i++)
		{
			map_file >> x >> y;
			hash.insert({ {x,y},1 });
			map_array[i] = { x,y };
		}
	}
};

class Snake
{
private:
	Point body[MAX_SNAKE_SIZE];
	int size = 5;
public:
	Snake()
	{

	}
	inline const int& get_size() { return size; }
	inline Point& operator[](int i) { return body[i]; }
	inline void increase_size(int i = 0) { size++; }

	inline void turn(char c)
	{
		if (c == 'w')
			body[0].up();
		else if (c == 's')
			body[0].down();
		else if (c == 'd')
			body[0].right();
		else if (c == 'a')
			body[0].left();

	}



	inline void turn_up() { body[0].up(); }
	inline void turn_down() { body[0].down(); }
	inline void turn_right() { body[0].right(); }
	inline void turn_left() { body[0].left(); }
	inline void show(int j = 0) {

	
		// show head differently
		body[0].print(char(2));
		int  i = 1;
		while (i < get_size() - 2)
		{
			body[i++].print(char(4));
		}
	}
	inline Snake& operator=(const Snake& obj)
	{
		size = obj.size;
		for (int i = 0; i < size; i++)
			body[i] = obj.body[i];
		return *this;
	}

	inline void show_colorful(int col = 4)
	{

	}
	void debug()
	{
		for (int i = 0; i < size; i++)
		{
			gotoxy(20, 20 + i);
			_getch();
			body[i].debug();
		}
	}

	void print_all()
	{
		gotoxy(0, 20);
		for (int i = 0; i < size; i++)
		{
			body[i].debug();
		}
	}

};

class Fruit
{
private:
	Point loc;
	int score = 10;
public:
	Fruit()
	{
		loc.randomize();
	}
	void change_pos()
	{
		loc.randomize();
	}
	inline int get_score() { return score; }
	inline void print() {
		SetConsoleTextAttribute(COLOR, 12); 
		loc.print(char(5)); 
		SetConsoleTextAttribute(COLOR, 7);
	}
	inline Point& get_loc() { return loc; }
};

class Orange : public Fruit
{
private:
	int score = 30;
public:

	inline int get_score() { return score; }
	inline void print()
	{
		SetConsoleTextAttribute(COLOR, 14);
		get_loc().print(char(254));
		SetConsoleTextAttribute(COLOR, 7);
	}
	inline void erase()
	{
		get_loc().print(' ');
		get_loc().randomize(1);
	}
};


////// Global vvvvv

Snake current_snake;
Map current_map;
int current_speed;
int high_score;
int current_score;
char current_direction = ' ';
char prev_direction = 'd';








class Game_Statistics
{
public:
	string player_name;
	int score;
	int speed;
	char prev_direction;
	Snake snake;
	int map;
	bool mode;
	int high_score ;



	Game_Statistics()
	{
		score = 0;
		speed = 5;
		prev_direction = 'd';
	}

	inline void save()
	{
		this->speed = current_speed;
		this->snake = current_snake;
		this->score = current_score;
		this->prev_direction = prev_direction;
		if (this->high_score < current_score)
			this->high_score = current_score;
	}

	void reset()
	{
		score = 0;
		speed = 5;
		snake = Snake();
		prev_direction = 'd';
	}


};

void read_data(fstream& file, Game_Statistics& s)
{
	file.open("data.dat", ios::in | ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(Game_Statistics));
	file.close();
}

void write_data(fstream& file, Game_Statistics& obj)
{
	file.open("data.dat", ios::out | ios::binary);
	file.write(reinterpret_cast<char*> (&obj), sizeof(Game_Statistics));
	file.close();
}

void loading_screen()
{
	text(60);
	gotoxy(19, 5);
	SetConsoleTextAttribute(COLOR, 9);
	cout << "Loading...";
	gotoxy(8, 6);
	for (int i = 0; i < 26; i++)
	{
		cout << char(254);
		Sleep(200);
	}
}




void set_front(bool is_boundary, int map_choice)
{
	system("cls");


	int x;
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	if (is_boundary)
	{
		cout << char(218);

	}
	for (x = 0; x < 77; x++)
	{
		if ((x % 2 == 0) && (!is_boundary))
			cout << " ";
		else
			cout << char(196);
	}

	if (is_boundary)
	{
		cout << char(191);
		for (x = 0; x < 17; x++)
		{
			gotoxy(0, x + 1);
			cout << char(179);
			gotoxy(78, x + 1);
			cout << char(179);
		}
		cout << endl;
		cout << char(192);
	}

	gotoxy(1, 18);
	for (x = 0; x < 77; x++)
	{
		if ((x % 2 == 1) && (!is_boundary))
			cout << " ";
		else
			cout << char(196);
	}
	if (is_boundary)
	{
		cout << char(217);
	}

	cout << endl;
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	int box;
	gotoxy(80, 0);
	cout << char(218);
	for (box = 0; box < 16; box++)
	{
		cout << char(196);
	}
	cout << char(191);
	cout << endl;
	gotoxy(80, 5);
	for (box = 0; box < 17; box++)
	{
		cout << char(196);
	}
	SetConsoleTextAttribute(COLOR, 6);
	gotoxy(82, 2);
	cout << "   MADE BY ";
	gotoxy(80, 3);
	cout << "   HEAVY CODARZ";
	gotoxy(80, 9);
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	for (box = 0; box < 17; box++)
	{
		cout << char(196);
	}
	SetConsoleTextAttribute(COLOR, 13);
	gotoxy(80, 7);
	cout << "    SCORE : 0\n";
	gotoxy(80, 8);
	cout << "HIGH SCORE : " << high_score;
	gotoxy(80, 14);
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	for (box = 0; box < 17; box++)
	{
		cout << char(196);
	}
	SetConsoleTextAttribute(COLOR, 12);
	gotoxy(83, 11);
	cout << " STATUS:";
	gotoxy(83, 12);
	cout << " PLAYING";
	if (is_boundary)
	{
		SetConsoleTextAttribute(COLOR, 22);
		gotoxy(81, 15);
		cout << " Mode: Boundary ";
	}
	else
	{
		SetConsoleTextAttribute(COLOR, 22);
		gotoxy(81, 15);
		cout << "Mode:No Boundary";
	}
	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	for (box = 0; box < 18; box++)
	{
		gotoxy(80, box + 1);
		cout << char(179);
		gotoxy(97, box + 1);
		cout << char(179);
	}



	cout << endl;
	gotoxy(80, 18);
	cout << char(192);


	for (box = 0; box < 16; box++)
	{
		cout << char(196);
	}
	cout << char(217);


	SetConsoleTextAttribute(COLOR, 74);
	gotoxy(18, 19);
	cout << "Press 'SPACE' to Pause            Press 'E' to Exit ";

	SetConsoleTextAttribute(COLOR, WALLS_COLOR);
	gotoxy(0, 20);
	cout << char(218);
	for (box = 0; box < 96; box++)
	{
		cout << char(196);
	}

	cout << char(191);
	cout << endl;
	cout << char(179);
	gotoxy(40, 21);
	cout << " SNAKE GAME\n ";
	cout << endl;

	for (box = 20; box < 22; box++)
	{
		gotoxy(0, box + 1);
		cout << char(179);
		gotoxy(97, box + 1);
		cout << char(179);
	}
	cout << endl;
	gotoxy(0, 22);
	cout << char(192);
	for (box = 0; box < 96; box++)
	{
		cout << char(196);
	}
	cout << char(217);
	cout << endl;
	SetConsoleTextAttribute(COLOR, 15);//snake color
	gotoxy(0, 22);



	//// Set Map if selected
	current_map.load_map(map_choice);
}





class Game_Manager
{
	fstream file;
	Game_Statistics stats;

	inline bool is_dead()
	{

		for (int i = 0; i < current_map.size; i++)
		{
			if (current_map.map_array[i] == current_snake[0])
			{
				stats.reset();
				write_data(file, stats);
				return true;
			}
		}
		if ((current_snake[0].get_x() <= 0 || current_snake[0].get_x() >= 77 || current_snake[0].get_y() <= 0 || current_snake[0].get_y() >= 18) && (stats.mode))
		{
			gotoxy(70, 18);
			stats.reset();
			write_data(file, stats);
			return true;
		}

		for (int i = 3; i < current_snake.get_size(); i++)
		{
			if (current_snake[0] == current_snake[i])
			{
				stats.reset();
				write_data(file, stats);
				return true;
			}
		}
		return false;
	}

public:

	void start()
	{
		hidecursor();
		//loading_screen(); // function to
		bool check = 1;
		int main_choice;
		read_data(file, stats);


		while (1)
		{
			Sleep(100);
			system("cls");
			text(60);
			main_choice = _menu();

			if (main_choice == 0)
			{
				text(27);
				set_front(stats.mode, stats.map);
				if (stats.score != 0)
					play();
			}
			else if (main_choice == 1)
			{
				text(27);
				stats.reset();
				set_front(stats.mode, stats.map);
				play();
			}
			else
			{
				switch (_menu('s'))
				{
				case 0:
				{
					stats.map = _menu('m');

					break;
				}
				case 1:
				{
					stats.mode = _menu('b');
					break;
				}
				}
			}

			current_speed = stats.speed;
			current_snake = stats.snake;
			current_score = stats.score;
			prev_direction = stats.prev_direction;
			high_score = stats.high_score;

		}
	}

	void pause_game()
	{
		current_direction = prev_direction;
		current_snake[current_snake.get_size() - 1].print(char(4));
		SetConsoleTextAttribute(COLOR, 9);
		gotoxy(83, 12);
		cout << " PAUSED..";


		for (int i = 1; i < current_snake.get_size(); i++)
			current_snake[i].print(char(4));
		current_snake[0].print(char(2));


		_getch();
		current_snake[current_snake.get_size() - 1].print(' ');
		gotoxy(83, 12);
		SetConsoleTextAttribute(COLOR, 12);
		cout << " PLAYING.";
		//SetConsoleTextAttribute(COLOR, 10);
		SetConsoleTextAttribute(COLOR, 7);

	}

	int _menu(char menu = 0)
	{
		hidecursor();
		string op1, op2, op3;
		int options;
		if (menu == 0) // zero (Main menu)
		{
			op1 = "Continue "; op1 += char(175);
			op2 = "New Game "; op2 += char(175);
			op3 = "Settings ";  op3 += char(15);
			options = 3;
		}
		if (menu == 's')
		{
			stats.reset();
			write_data(file, stats);
			op1 = "Select Map";
			op2 = "Select Mode";
			options = 2;
		}
		else if (menu == 'm')
		{
			stats.reset();
			write_data(file, stats);
			op1 = "Map 1";
			op2 = "Map 2";
			op3 = "Map 3";
			options = 3;
		}
		else if (menu == 'b')
		{
			stats.reset();
			write_data(file, stats);
			op1 = "Without Boundary";
			op2 = "With Boundary";
			options = 2;
		}
		char c;
		int j = 0;
		while (1)
		{
			c = 'z';
			if (_kbhit())
				c = _getch();

			if (c == '\r')
			{
				system("cls");
				return j;
			}

			if (c == 72)
			{
				j--;
			}
			else if (c == 80)
			{
				j++;
			}

			if (j < 0) j = options - 1;

			j = j % options;
			gotoxy(16, 4);
			if (j == 0)
			{
				SetConsoleTextAttribute(COLOR, 7);
				cout << char(16) << op1 << endl;
			}
			else {
				SetConsoleTextAttribute(COLOR, 9);
				cout << " " << op1 << endl;
			}

			if (j == 1)
			{
				gotoxy(16, 5);
				SetConsoleTextAttribute(COLOR, 7);
				cout << char(16) << op2 << endl;
			}
			else
			{
				gotoxy(16, 5);
				SetConsoleTextAttribute(COLOR, 9);
				cout << " " << op2 << endl;
			}
			if (j == 2)
			{
				gotoxy(16, 6);
				SetConsoleTextAttribute(COLOR, 7);
				cout << char(16) << op3 << endl;
			}
			else
			{
				gotoxy(16, 6);
				SetConsoleTextAttribute(COLOR, 9);
				cout << " " << op3 << endl;
			}
		}

	}

	void on_death()
	{
		SetConsoleTextAttribute(COLOR, 4);
		int  i = 1;
		while (i < current_snake.get_size() - 1)
		{
			current_snake[i++].print(char(4));
		}
		current_snake[0].print(char(2));
		Sleep(1000);
		_getch();
	}


	void play()
	{
		// take all stats from file




		int i = 0;
		current_direction = prev_direction;
		int snake_size = current_snake.get_size();
		int count = 3;
		bool time_complete = 0;
		Fruit f;
		Orange o;
		double timer = 14;
		i = 0;
		current_snake.show();
		_getch();
		current_snake[snake_size - 1].print(' ');
		do
		{
			snake_size = current_snake.get_size();


			//// fruit collision
			if (f.get_loc() == current_snake[0])
			{
				f.change_pos();
				current_snake.increase_size();
				current_score += 10;


				current_speed += 4;
				count--;
				if (count == 0)
				{
					f.get_loc().randomize(1);
					//neutralizer = clock();
					timer = 14;
					//time_complete = 0;
					o.get_loc().randomize();
					gotoxy(81, 17);
					SetConsoleTextAttribute(COLOR, 14);
					//// show bar
					for (int i = 0; i < 14; i++)
						cout << char(254);
				}

				gotoxy(91, 7);
				cout << " "<<current_score << endl;
			}


			////// which one to print
			if (count)
				f.print();
			else
			{
				gotoxy(82 + timer, 17);
				cout << " ";
				o.print();
				if (timer < 0)
				{
					o.erase();
					count = 3;
					f.get_loc().randomize();
				}
				//// orange collapse
				if (o.get_loc() == current_snake[0])
				{
					gotoxy(81, 17);
					//// erase bar
					for (int i = 0; i < 14; i++)
						cout << " ";


					current_score += 30;
					current_speed += 4;

					gotoxy(91, 7);
					cout << current_score << endl;
					o.change_pos();
					current_snake.increase_size(1);
					count = 3;
					f.get_loc().randomize();

				}
			}
			prev_direction = current_direction;

			if (_kbhit())
			{
				current_direction = _getch();
				if (
					(prev_direction == 'w' && current_direction == 's') ||
					(prev_direction == 's' && current_direction == 'w') ||
					(prev_direction == 'd' && current_direction == 'a') ||
					(prev_direction == 'a' && current_direction == 'd')
					)
					current_direction = prev_direction;
			}

			if (current_direction == 'e')
				break;

			i = snake_size - 1;
			while (i)
			{
				current_snake[i] = current_snake[i - 1];
				i--;
			}
			if (current_direction == 'a' || current_direction == 'w' || current_direction == 's' || current_direction == 'd')
			{
				current_snake.turn(current_direction);
			}
			else if (current_direction == ' ')
			{
				pause_game();
				current_snake.turn(current_direction);
			}
			else
			{
				current_direction = prev_direction;
				current_snake.turn(current_direction);
			}

			timer = timer - 0.4;


			if (is_dead())
			{
				on_death();
				break;
			}

			stats.save();

			current_snake.show();
			Sleep(180 - current_speed);
			current_snake[current_snake.get_size() - 2].print(' ');

		} while (current_direction != 'e');
		write_data(file, stats);
	}
};

inline void Point::randomize(int i)
{
	if (i)
	{
		x = 90;
		y = 18;
	}
	else
	{
		do
		{
			srand(time(0));
			x = rand() % 40 + 6;
			y = rand() % 11 + 5;
			if (x % 2 != 0)x++;
		} while (current_map.hash[{x, y}]);
	}



}












//#include "Class.h"
int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Game_Manager m;
	m.start();
	return 0;

}
