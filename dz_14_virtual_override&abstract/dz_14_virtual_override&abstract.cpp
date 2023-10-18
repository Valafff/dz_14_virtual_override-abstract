// ДЗ с 515й строки
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <io.h>
#include <algorithm>
#include <vector>

using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, A = 97, D = 100, S = 115, W = 119 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}


class MENU
{
	class SUBMENU
	{
		int count_y_slots{ 0 };
		int step_Y{ 0 };
		int sub_start_X{ 0 };
		int sub_start_Y{ 0 };
		int menupoint_Y{ 0 };
		int quit_Y{ 0 };

		Color text_Y{ Red };
		Color background_Y{ White };
		Color text_default_Y{ White };
		Color background_default_Y{ Black };

		string* y_list{ nullptr };

	public:

		SUBMENU() :SUBMENU(2, Red, White)
		{
			for (int i = 0; i < count_y_slots; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
			//y_list[0] = "SUB_1";
			//y_list[1] = "SUB_2";
		}
		SUBMENU(const int def_size) :SUBMENU(def_size, Red, White)
		{
			for (int i = 0; i < def_size; i++)
			{
				y_list[i] += "SUB_";
			}
		}
		SUBMENU(const int f_count_Y, const Color textcolor, const Color backgroung_color, const int X = 0, const int Y = 0, const int f_step_Y = 1)
		{
			count_y_slots = f_count_Y;
			y_list = new string[f_count_Y];
			step_Y = f_step_Y;
			text_Y = textcolor;
			background_Y = backgroung_color;
			quit_Y = f_count_Y;
			sub_start_X = X;
			sub_start_Y = Y;
			menupoint_Y = 1;

		}
		~SUBMENU()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
		}
		void setCount_Y_slots(const int& f_size)
		{
			count_y_slots = f_size;
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
			//!!!ОБЯЗАТЕЛЬНО НУЛЕВОЙ УКАЗАТЕЛЬ - ИНАЧЕ ДЕСТРУКТОР БУДЕТ ПЫТАТЬСЯ ОСВОБОДИТЬ ПАМЯТЬ ДВА РАЗА!!!
			y_list = nullptr;
			for (int i = 0; i < f_size; i++)
			{
				y_list = new string[f_size];
			}
			for (int i = 0; i < f_size; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
		}
		void setY_step(const int& f_size)
		{
			step_Y = f_size;
		}
		void set_BackGround_Y(const Color& f_color)
		{
			background_Y = f_color;
		}
		void set_Text_Y(const Color& f_color)
		{
			text_Y = f_color;
		}
		void setQuit_Y(const int f_size)
		{
			quit_Y = f_size;
		}
		void setSubStart_X(const int X)
		{
			sub_start_X = X;
		}
		void setSubStart_Y(const int Y)
		{
			sub_start_Y = Y;
		}
		void setMenupoint(const int f_menu)
		{
			menupoint_Y = f_menu;
		}
		void setY_list(const int index, const string f_name)
		{
			y_list[index] = f_name;
		}

		Color getBackground_Y() const
		{
			return background_default_Y;
		}
		int getCount_y_slots()
		{
			return count_y_slots;
		}

		// Освобождение вновь выделенной памяти для y_list Т.К. ДЕСТРУКТОР ПЫТАЕТСЯ БАХНУТЬ ПАМЯТЬ ПО АДРЕСУ, КОТОРАЯ ВЫДЕЛЯЛАЛСЬ КОНСТРУКТОРОМ
		void delMem()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
				y_list = nullptr;
			}
		}

		// ПЕЧАТЬ ПОДМЕНЮ ПО ВЕРТИКАЛИ
		void menuPrint_Y(const int& menupoint, const int& f_step_X)
		{
			for (int i = 0; i < count_y_slots; i++)
			{
				setCursor(f_step_X, sub_start_Y + i * step_Y + 1);
				if (i == menupoint)
				{
					setColor(text_Y, background_Y);
				}
				else
				{
					setColor(text_default_Y, background_default_Y);
				}
				cout << y_list[i];
			}
			setColor(text_default_Y, background_default_Y);
		}
		//ОЧИСТКА ПРЕДЫДУЩЕГО ПОДМЕНЮ(по умолчанию происходит с координат 0,1) количество строк для очистки передается как аргумент, длина строки передается как аргумент
		void cleanSubMenuZone(const int count_row, const int string_length, int f_start_x = 0, int f_start_y = 1)
		{
			setCursor(f_start_x, f_start_y);
			setColor(getBackground_Y(), getBackground_Y());
			char** cleanarr = new char* [count_row];
			for (int i = 0; i < count_row; i++)
			{
				cleanarr[i] = new char[string_length];
			}
			for (int i = 0; i < count_row; i++)
			{
				for (int j = 0; j < string_length; j++)
				{
					cleanarr[i][j] = '@';
					cout << cleanarr[i][j];
				}
				cout << endl;
			}
			if (cleanarr != nullptr)
			{
				for (int i = 0; i < count_row; i++)
				{
					delete[] cleanarr[i];
				}
				delete[] cleanarr;
			}
		}
	};

	int count_x_slots{ 0 };
	int step_X{ 0 };
	int quit{ 0 };
	int start_X{ 0 };
	int start_Y{ 0 };
	int menupoint{ 0 };

	Color text{ Red };
	Color background{ White };
	Color text_default{ White };
	Color background_default{ Black };

	//SUBMENU aaa;
	//SUBMENU aaa(10);

	string* x_list;
	SUBMENU* sub_menu;

	// ПЕЧАТЬ МЕНЮ ДЛЯ ГОРИЗОНТАЛИ
	void menuPrint_X(const int menupoint)
	{
		for (int i = 0; i < count_x_slots; i++)
		{
			setCursor(start_X + i * step_X, start_Y);
			if (i == menupoint)
			{
				setColor(text, background);
			}
			else
			{
				setColor(text_default, background_default);
			}
			cout << x_list[i];
		}
		setColor(text_default, background_default);
	}

public:

	MENU() :MENU(4, 18, Red, White)
	{
		x_list[0] = "MENU_1";
		x_list[1] = "MENU_2";
		x_list[2] = "MENU_3";
		x_list[3] = "QUIT";
	}
	//// Далее, через конструктор копирования инициализировать объект
	//MENU(int size): MENU(4, 18, Red, White)
	//{
	//	SUBMENU aaa(size);
	//}
	MENU(const int f_count_X, const int f_step_X, const Color textcolor, const Color backgroung_color, const int X = 0, const int Y = 0, const int f_step_Y = 1)
	{
		x_list = new string[f_count_X];
		sub_menu = new SUBMENU[f_count_X];
		count_x_slots = f_count_X;
		step_X = f_step_X;
		text = textcolor;
		background = backgroung_color;
		quit = f_count_X;
		start_X = X;
		start_Y = Y;
		menupoint = 0;
	}
	~MENU()
	{
		//ВЫЗОВ МЕТОДА ОСВОБОЖДЕНИЯ ПЕРЕВЫДЕЛЕННОЙ ПАМЯТИ ДЛЯ y_list
		this->sub_menu->delMem();
		if (x_list != nullptr)
		{
			delete[] x_list;
		}
		if (sub_menu != nullptr)
		{
			delete[] sub_menu;
		}
	}
	// Установка цвета текста для ГОРИЗОНТАЛЬНОЙ строки
	void setColorText(const Color textcolor)
	{
		text = textcolor;
	}
	// Установка цвета текста для ВЕРТИКАЛЬНОЙ строки
	void setColorText_Y(const Color textcolor)
	{
		for (int i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_Text_Y(textcolor);
		}
	}
	// Установка цвета фона для ВЕРТИКАЛЬНОЙ строки
	void setColorBackGround_Y(const Color backcolor)
	{
		for (int i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_BackGround_Y(backcolor);
		}
	}
	// Установка цвета заднего фона ГОРИЗОНТАЛЬНОЙ строки
	void setColorBackground(const Color f_bakground)
	{
		background = f_bakground;
	}
	// Установка дефолтного цвета текста по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorTextDefault(const Color f_def_text)
	{
		text_default = f_def_text;
	}
	//Установка заднего фона по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorBackgroundDefault(const Color f_def_background)
	{
		background_default = f_def_background;
	}
	// Задание количества слотов меню по ГОРИЗОНТАЛИ
	void setCount_X_Slots(const int f_count)
	{
		count_x_slots = f_count;
	}
	// Задание количества слотов меню по ВЕРТИКАЛИ для подменю
	void setCount_Y_Slots(const int f_index, const int f_count)
	{
		sub_menu[f_index].setCount_Y_slots(f_count);

	}
	// Задание названий пунктов меню по ГОРИЗОНТАЛИ
	void setName_X_list(const int index, const string f_name)
	{
		x_list[index] = f_name;
	}
	// Задание названий пунктов меню по ВЕРТИКАЛИ
	void setName_Y_list(const int index_x, const int index_y, const string f_name)
	{
		sub_menu[index_x].setY_list(index_y, f_name);
	}
	// Установка шага по ГОРИЗОНТАЛИ
	void set_X_step(const int f_step)
	{
		step_X = f_step;
	}
	// получение длины списка по ГОРИЗОНТАЛИ
	int getSizeX()
	{
		return count_x_slots;
	}
	// получение последнего индекса списка по ГОРИЗОНТАЛИ
	int getLast_IndexX()
	{
		return count_x_slots - 1;
	}
	// Получение индекса выбранного меню по ГОРИЗОНТАЛИ
	int getMenuIndex()
	{
		return menupoint;
	}
	// Определение максимального количества строк
	int getMaxRow()
	{
		int temp(0);
		for (int i = 0; i < count_x_slots; i++)
		{
			if (sub_menu[i].getCount_y_slots() > temp)
			{
				temp = sub_menu[i].getCount_y_slots();
			}
		}
		return temp;
	}

	// Назначение клавиш, возврат выбранного пункта меню для ГОРИЗОНТАЛИ И ВЕРТИКАЛИ
	int SelectMenuItem(const int f_lastmenu, const int f_lastmenu_Y, const bool f_flag, const int lenght = 130)
	{
		int menupoint;
		int menupoint_Y;
		if (f_lastmenu == 0)
		{
			menupoint = 1;
		}
		else
		{
			menupoint = f_lastmenu;
		}
		if (f_lastmenu_Y == 0)
		{
			menupoint_Y = 1;
		}
		else
		{
			menupoint_Y = f_lastmenu_Y;
		}

		int lastmenupoint = 1;
		int maxrow = getMaxRow();
		//ВЫХОД - последний член списка
		int key(0);
		do
		{
			if (menupoint != lastmenupoint)
			{
				if (key == Left or key == Right)
				{
					menupoint_Y = 1;
				}
				lastmenupoint = menupoint;
				sub_menu[menupoint - 1].cleanSubMenuZone(maxrow, lenght);
			}
			menuPrint_X(menupoint - 1);
			sub_menu[menupoint - 1].menuPrint_Y(menupoint_Y - 1, step_X * (menupoint - 1));

			key = _getch();
			if (key == Right)
			{
				if (menupoint <= count_x_slots)
				{
					menupoint++;
				}
				if (menupoint > count_x_slots)
				{
					menupoint = 1;
				}
			}
			if (key == Left)
			{
				if (menupoint >= 1)
				{
					menupoint--;
				}
				if (menupoint < 1)
				{
					menupoint = count_x_slots;
				}
			}
			if (key == Down)
			{
				if (menupoint_Y <= sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y++;
				}
				if (menupoint_Y > sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y = 1;
				}
			}
			if (key == Up)
			{
				if (menupoint_Y >= 1)
				{
					menupoint_Y--;
				}
				if (menupoint_Y < 1)
				{
					menupoint_Y = sub_menu[menupoint - 1].getCount_y_slots();
				}
			}
			if (key == Enter)
			{
				if (sub_menu[menupoint - 1].getCount_y_slots() != 0)
				{
					//От 1 до 100 - коды только горизонтального меню, выводится код от 101 до 200 - MENU_1, SUB_1 - SUB_N по ВЕРТИКАЛИ, MENU_2, SUB_1 - SUB_N  201-300...
					return menupoint_Y + (menupoint * 100);
				}
				else
				{
					return menupoint;
				}
			}
		} while (key != Enter);
		return this->quit;
	}
};

void cleanZone(const int X, const int Y, const int row, const int col, const Color color = Black)
{
	Color temptxtcol = White;
	Color tempbackcol = Black;

	setCursor(X, Y);
	setColor(color, color);
	vector <char> cln;
	cln.assign(row * col, '@');
	int count = 1;
	for (auto symbol : cln)
	{
		cout << symbol;
		count++;
		if (count % col == 0)
		{
			cout << endl;
		}
	}
	setColor(temptxtcol, tempbackcol);
	setCursor(X, Y);
}

void formatPrint(const int col_size, const string& originalstr)
{

	int tempindex = 1;
	for (auto s : originalstr)
	{
		tempindex++;
		cout << s;
		if (tempindex % col_size == 0)
		{
			cout << endl;
		}
	}
}
//Описать абстрактный класс ФИГУРА.
//Поля:
//цвет
//координаты левой верхней точки
//высота
//ширина


class Figure
{
protected:

	Color color;
	int X, Y;
	int R, G, B;
	int hight;
	int width;

public:

	Figure() :Figure(5, 10, 2, 2, Red)
	{}

	Figure(const int X, const int Y) :Figure(X, Y, 2, 2, Red)
	{}

	Figure(const int X, const int Y, const int H, const int W, const Color color)
	{
		hight = H;
		width = W;
		this->X = X;
		this->Y = Y;
		this->color = color;
		if (color == Red)
		{
			R = 255; G = 0; B = 0;
		}
		else if (color == Green)
		{
			R = 0; G = 255; B = 0;
		}
		else if (color == Blue)
		{
			R = 0; G = 0; B = 255;
		}
		else
		{
			R = 255; G = 255; B = 255;
		}
	}

	virtual void showFigure() = 0;
	virtual void cleanFigure() = 0;
	// Получить площадь фигуры
	virtual double getSquare() = 0;
	virtual double getPerimeter() = 0;

	void Move()
	{
		int key = -1;
		do
		{
			key = _getch();
			if (key == Right)
			{
				cleanFigure();
				X++;
			}
			if (key == Left)
			{
				cleanFigure();
				X--;
			}
			if (key == Down)
			{
				cleanFigure();
				Y++;
			}
			if (key == Up)
			{
				cleanFigure();
				Y--;
			}
			showFigure();

		} while (key != Esc);
	}


	void setColor_class(Color arg_color)
	{
		color = arg_color;
	}
	void setX(const int arg_x)
	{
		X = arg_x;
	}
	void setY(const int arg_y)
	{
		Y = arg_y;
	}
	void setHight(const int h)
	{
		hight = h;
	}
	void setwidth(const int w)
	{
		width = w;
	}
	Color getColor()
	{
		return color;
	}
	int getX()
	{
		return X;
	}
	int getY()
	{
		return Y;
	}
	int getHight()
	{
		return hight;
	}
	int getwidth()
	{
		return width;
	}
};

//методы :
//показать фигуру - чисто виртуальный метод
//вернуть площадь - чисто виртальный метод
//вернуть периметр - чисто виртуальный метод
//set - методы для всех полей
//get - методы для всех полей
//перемещение фигуры

//Описать набор классов наследников :
//Прямоугольник rectangle
//Равнобедренный треугольник isosceles_triangle
//Прямоугольный треугольник

// Прямоугольник
class mRectangle : public Figure
{

	int x1, y1, x2, y2, x3, y3, x4, y4;


public:

	mRectangle() : Figure(150, 150, 100, 100, Red)
	{}
	mRectangle(const int X, const int Y) : Figure(X, Y, 5, 5, Red)
	{}
	mRectangle(const int X, const int Y, const int H, const int W, const Color color) : Figure(X, Y, H, W, color)
	{}

	void showFigure() override
	{

		x1 = X;
		y1 = Y;
		x2 = x1 + width;
		y2 = y1;
		x3 = x1 + width;
		y3 = y1 + hight;
		x4 = x1;
		y4 = y1 + hight;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(R, G, B)));

		POINT ptr[5] = { {x1,y1},{x2,y2},{x3,y3},{x4,y4},{x1,y1} };
		Polyline(hdc, ptr, 5);

	}
	void cleanFigure() override
	{

		x1 = X;
		y1 = Y;
		x2 = x1 + width;
		y2 = y1;
		x3 = x1 + width;
		y3 = y1 + hight;
		x4 = x1;
		y4 = y1 + hight;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));

		POINT ptr[5] = { {x1,y1},{x2,y2},{x3,y3},{x4,y4},{x1,y1} };
		Polyline(hdc, ptr, 5);

	}

	double getSquare() override
	{
		return round(width * hight * 100) / 100;
	}
	double getPerimeter() override
	{
		return round(2 * (width + hight) * 100) / 100;
	}
};

// Равнобедренный треугольник
class Triangle_isosceles : public Figure
{
	int x1, y1, x2, y2, x3, y3;

public:
	Triangle_isosceles() : Figure(150, 150, 150, 50, Green)
	{}
	Triangle_isosceles(const int X, const int Y) : Figure(X, Y, 10, 10, Green)
	{}
	Triangle_isosceles(const int X, const int Y, const int H, const int W, const Color color) : Figure(X, Y, H, W, color)
	{}

	void showFigure() override
	{
		x1 = X + width / 2;
		y1 = Y;
		x2 = x1 + width / 2;
		y2 = y1 + hight;
		x3 = x1 - width / 2;
		y3 = y1 + hight;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(R, G, B)));
		POINT ptr[4] = { {x1,y1},{x2,y2},{x3,y3},{x1,y1} };
		Polyline(hdc, ptr, 4);
	}
	void cleanFigure() override
	{
		x1 = X + width / 2;
		y1 = Y;
		x2 = x1 + width / 2;
		y2 = y1 + hight;
		x3 = x1 - width / 2;
		y3 = y1 + hight;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));
		POINT ptr[4] = { {x1,y1},{x2,y2},{x3,y3},{x1,y1} };
		Polyline(hdc, ptr, 4);
	}


	double getSquare() override
	{
		return round((width * hight) / 2 * 100) / 100;
	}
	double getPerimeter() override
	{
		return round(((2 * (sqrt(pow(width / 2, 2) + pow(hight, 2))) + width)) * 100) / 100;
	}
};

// Прямоугольный треугольник
class Triangle_right : public Figure
{
	int x1, y1, x2, y2, x3, y3;

public:
	Triangle_right() : Figure(150, 150, 120, 90, Blue)
	{}
	Triangle_right(const int X, const int Y) : Figure(X, Y, 10, 10, Blue)
	{}
	Triangle_right(const int X, const int Y, const int H, const int W, const Color color) : Figure(X, Y, H, W, color)
	{}

	void showFigure() override
	{
		x1 = X;
		y1 = Y;
		x2 = x1;
		y2 = y1 + hight;
		x3 = x1 + width;
		y3 = y2;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(R, G, B)));
		POINT ptr[4] = { {x1,y1},{x2,y2},{x3,y3},{x1,y1} };
		Polyline(hdc, ptr, 4);

	}
	void cleanFigure() override
	{
		x1 = X;
		y1 = Y;
		x2 = x1;
		y2 = y1 + hight;
		x3 = x1 + width;
		y3 = y2;

		HDC hdc = GetDC(GetConsoleWindow());
		SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));
		POINT ptr[4] = { {x1,y1},{x2,y2},{x3,y3},{x1,y1} };
		Polyline(hdc, ptr, 4);
	}

	double getSquare() override
	{
		return round((width * hight) / 2 * 100) / 100;
	}
	double getPerimeter() override
	{
		return round((sqrt(pow(hight, 2) + pow(width, 2) + width + hight)) * 100) / 100;
	}

};



//В main создать вектор указателей на все существующие типы фигур.
//Осуществить возможность работы с любым объектом.
//Добавление / удаление фигуры в массив.

int main()
{
	setlocale(LC_ALL, "rus");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	srand(time(NULL));

	//HDC hdc = GetDC(GetConsoleWindow());
	system("mode con cols=180 lines=60");

	MENU menu(3, 18, Red, Yellow);
	menu.setColorText_Y(Red);
	menu.setColorBackGround_Y(Yellow);
	menu.setName_X_list(0, "ВВОД ДАННЫХ");
	menu.setName_X_list(1, "ДАННЫЕ О ФИГУРЕ");
	menu.setName_X_list(2, "ВЫХОД");
	menu.setCount_Y_Slots(0, 7);
	menu.setCount_Y_Slots(1, 4);
	menu.setCount_Y_Slots(2, 0);

	menu.setName_Y_list(0, 0, "Создать прямоугольник ПО УМОЛЧАНИЮ");
	menu.setName_Y_list(0, 1, "Создать пользовательский прямоугольник");
	menu.setName_Y_list(0, 2, "Создать равнобедренный треугольник ПО УМОЛЧАНИЮ");
	menu.setName_Y_list(0, 3, "Создать пользовательский равнобедренный треугольник");
	menu.setName_Y_list(0, 4, "Создать прямоугольный треугольник ПО УМОЛЧАНИЮ");
	menu.setName_Y_list(0, 5, "Создать пользовательский прямоугольный треугольник");
	menu.setName_Y_list(0, 6, "Удалить фигуру из вектора");

	menu.setName_Y_list(1, 0, "Получить прямоугольники из вектора(после отрисовки фигуру можно двигать)");
	menu.setName_Y_list(1, 1, "Получить равнобедренные треугольники из вектора(после отрисовки фигуру можно двигать)");
	menu.setName_Y_list(1, 2, "Получить прямоугольные треугольники из вектора(после отрисовки фигуру можно двигать)");
	menu.setName_Y_list(1, 3, "Показать все фигуры");

	// Переменные меню
	int select(0);
	int lastmenu(0);
	int lastmenu_Y(0);
	bool flag(false);

	mRectangle someRect;
	Triangle_right some_triangle_right;
	Triangle_isosceles sometriangle_iso;

	vector <Figure*> MyFig;
	int tempH(0), tempW(0);


	do
	{
		select = menu.SelectMenuItem(lastmenu, lastmenu_Y, flag);
		cleanZone(0, 6, 30, 110);
		// Создать прямоугольник по умолчанию
		if (select == 101)
		{
			MyFig.push_back(new mRectangle());
			setCursor(0, 10);
			cout << "Фигура(прямоугольник) добавлена в вектор";

		}
		//  Создать пользовательский прямоугольник
		if (select == 102)
		{
			do
			{
				setCursor(0, 10);
				cout << "Введите высоту фигуры: ";
				cin >> tempH;
				setCursor(0, 10);
				cout << "												";
				setCursor(0, 10);
				cout << "Введите ширину фигуры: ";
				cin >> tempW;
				setCursor(0, 10);
				cout << "												";

			} while (tempH <= 0 or tempH > 500 or tempW <= 0 or tempW > 500);
			MyFig.push_back(new mRectangle(150, 150, tempH, tempW, Color(1 + rand() % 15)));
			setCursor(0, 10);
			cout << "Фигура(пользовательский прямоугольник) добавлена в вектор";

		}
		// Создать равнобедренный треугольник по умолчанию
		if (select == 103)
		{
			MyFig.push_back(new Triangle_isosceles());
			setCursor(0, 10);
			cout << "Фигура(равнобедренный треугольник) добавлена в вектор";
		}
		// Создать пользовательский равнобедренный треугольник
		if (select == 104)
		{
			do
			{
				setCursor(0, 10);
				cout << "Введите высоту фигуры: ";
				cin >> tempH;
				setCursor(0, 10);
				cout << "												";
				setCursor(0, 10);
				cout << "Введите ширину фигуры: ";
				cin >> tempW;
				setCursor(0, 10);
				cout << "												";

			} while (tempH <= 0 or tempH > 500 or tempW <= 0 or tempW > 500);
			MyFig.push_back(new Triangle_isosceles(150, 150, tempH, tempW, Color(1 + rand() % 15)));
			setCursor(0, 10);
			cout << "Фигура(пользовательский треугольник) добавлена в вектор";
		}
		// Создать прямоугольный треугольник по умолчанию
		if (select == 105)
		{
			MyFig.push_back(new Triangle_right());
			setCursor(0, 10);
			cout << "Фигура(прямоугольный треугольник) добавлена в вектор";
		}
		//Создать пользовательский прямоугольный треугольник
		if (select == 106)
		{
			do
			{
				setCursor(0, 10);
				cout << "Введите высоту фигуры: ";
				cin >> tempH;
				setCursor(0, 10);
				cout << "												";
				setCursor(0, 10);
				cout << "Введите ширину фигуры: ";
				cin >> tempW;
				setCursor(0, 10);
				cout << "												";

			} while (tempH <= 0 or tempH > 500 or tempW <= 0 or tempW > 500);
			MyFig.push_back(new Triangle_right(150, 150, tempH, tempW, Color(1 + rand() % 15)));
			setCursor(0, 10);
			cout << "Фигура(пользовательский треугольник) добавлена в вектор";
		}
		//Удалить фигуру из вектора
		if (select == 107)
		{
			int pos;
			setCursor(0, 10);
			cout << "Всего элементов в векторе: " << MyFig.size() << endl;
			cout << "Укажите позицию для удаления от 0 до " << MyFig.size() - 1 << " ";
			do
			{
				cin >> pos;
			} while (pos < 0 or pos >= MyFig.size());

			MyFig.erase(MyFig.begin() + pos);

		}

		//Получить прямоугольники из вектора(после отрисовки фигуру можно двигать
		if (select == 201)
		{
			int flag = 0;
			if (MyFig.size() == 0)
			{
				setCursor(0, 10);
				cout << "Фигур не найдено.";
				_getch();
			}
			else
			{
				for (auto var : MyFig)
				{
					if (mRectangle* object = dynamic_cast<mRectangle*>(var))
					{
						cout << "Площадь фигуры " << var->getSquare() << "  кв.ед. " << "Периметр фигуры " << var->getPerimeter() << " ед.";
						var->showFigure();
						var->Move();
						flag++;
					}
				}
				if (!flag)
				{
					setCursor(0, 10);
					cout << "Фигур не найдено.";
					_getch();
				}
			}


			//cout << "Площадь фигуры " << someRect.getSquare() << "  кв.ед. " << "Периметр фигуры " << someRect.getPerimeter() << " ед.";
			//someRect.showFigure();
			//someRect.Move();
		}
		//Получить равнобедренные треугольники из вектора(после отрисовки фигуру можно двигать
		if (select == 202)
		{
			int flag = 0;
			if (MyFig.size() == 0)
			{
				setCursor(0, 10);
				cout << "Фигур не найдено.";
				_getch();
			}
			else
			{
				for (auto var : MyFig)
				{
					if (Triangle_isosceles* object = dynamic_cast<Triangle_isosceles*>(var))
					{
						cout << "Площадь фигуры " << var->getSquare() << "  кв.ед. " << "Периметр фигуры " << var->getPerimeter() << " ед.";
						var->showFigure();
						var->Move();
						flag++;
					}
				}
				if (!flag)
				{
					setCursor(0, 10);
					cout << "Фигур не найдено.";
					_getch();
				}
			}

			//cout << "Площадь фигуры " << sometriangle_iso.getSquare() << "  кв.ед. " << "Периметр фигуры " << sometriangle_iso.getPerimeter() << " ед.";
			//sometriangle_iso.showFigure();
			//sometriangle_iso.Move();
		}
		// Получить прямоугольные треугольники из вектора(после отрисовки фигуру можно двигать
		if (select == 203)
		{
			int flag = 0;
			if (MyFig.size() == 0)
			{
				setCursor(0, 10);
				cout << "Фигур не найдено.";
				_getch();
			}
			else
			{
				for (auto var : MyFig)
				{
					if (Triangle_right* object = dynamic_cast<Triangle_right*>(var))
					{
						cout << "Площадь фигуры " << var->getSquare() << "  кв.ед. " << "Периметр фигуры " << var->getPerimeter() << " ед.";
						var->showFigure();
						var->Move();
						flag++;
					}
				}
				if (!flag)
				{
					setCursor(0, 10);
					cout << "Фигур не найдено.";
					_getch();
				}
			}

		}
		//Показать все фигуры
		if (select == 204)
		{
			int count = 0;
			int count_y = 1;
			int step = 300;
			int step_y = 200;
			for (auto var : MyFig)
			{

				if (count % 3 == 0 and count != 0)
				{
					var->setX(0);
					count = 0;
					count_y++;
				}
				var->setX(step * count);
				var->setY(step_y * count_y);
				var->showFigure();
				count++;
				Sleep(300);
			}
		}

		// Вспомогательные переменные для фиксирования выбранной позиции меню
		if (select < 101)
		{
			lastmenu = select;
		}
		else
		{
			lastmenu = select / 100;
			lastmenu_Y = select % (100 * lastmenu);
			flag = true;
		}
	} while (select != menu.getSizeX());

	return 0;
}
