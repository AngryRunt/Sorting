// Practice_2_Sort.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include <iostream>
using namespace std;

typedef struct List_Digit
{
    int val;
    struct List_Digit* next;
};

class Work_Sorting
{
public:
    Work_Sorting();
    ~Work_Sorting();

    void Run_Sorting();

private:
    void Full_Array();		// Заполнение массива случайным образом
    void Print_Array();		// Печать массива

    void Sorting_Insert();	// Сортировка вставками

    void Sorting_Bubble();	// Пузырьковая сортировка

    void Exchange_Elements_I_J(int i, int j);				// Обмен в массиве элементами с индексами i и j
    void Sorting_Quick_SInsert(int Size_Array, int SizeB);
    int Sorting_Quick_Separate(int i, int j);				// разделение массива на подмассивы (Бытсрая сортировка )
    void Sorting_Quick(int i, int j);						// Бытсрая сортировка



    void Sorting_Radix(int Num_T);				// Поразрядная сортировка

    void  Down_Heap(int Start, int Finish);		// Пирамидальная сортировка (процедура просеивания)
    void  Sorting_Heap();						// Пирамидальная сортировка (главная функция)

    void Sorting_Merge();						// Cортировка прямое слияние



    int Size_Array;
    int *Arr;
};
//----------------------------------------------------------
Work_Sorting::Work_Sorting()
{
    Size_Array = 14;
    Arr = new int[Size_Array];
}
//----------------------------------------------------------
Work_Sorting::~Work_Sorting()
{
    delete[] Arr;
}
//----------------------------------------------------------
// Заполнение массива случайным образом
//----------------------------------------------------------
void Work_Sorting::Full_Array()
{
    Arr[0] = 901;
    Arr[1] = 214;
    Arr[2] = 204;
    Arr[3] = 306;
    Arr[4] = 433;
    Arr[5] = 505;
    Arr[6] = 602;
    Arr[7] = 757;
    Arr[8] = 810;
    Arr[9] = 117;
    Arr[10] = 123;
    Arr[11] = 323;
    Arr[12] = 604;
    Arr[13] = 856;
}
//--------------------------------------------------------------
// Печать массива
//--------------------------------------------------------------
void Work_Sorting::Print_Array()
{
    int i;
    cout << " Массив \n";
    for (int i = 0; i < Size_Array; i++)
    {
        cout << Arr[i] << "; ";
    }
    getchar();
}
//--------------------------------------------------------------
// Сортировка вставками
//--------------------------------------------------------------
void Work_Sorting::Sorting_Insert()
{
    int i, j, xx;

    for (j = 1; j < Size_Array; j++)
    {
        xx = Arr[j];
        for (i = j - 1; i >= 0; i--)
        {
            if (xx > Arr[i]) break;
            Arr[i + 1] = Arr[i];
        }
        Arr[i + 1] = xx;
    }
}
//--------------------------------------------------------------
// Пузырьковая сортировка
//--------------------------------------------------------------
void Work_Sorting::Sorting_Bubble()
{
    int i, j, xx;

    for (i = 1; i < Size_Array; i++)
    {
        for (j = i; j >= 1; j--)
        {
            if (Arr[j] > Arr[j - 1]) break;

            xx			= Arr[j];
            Arr[j]		= Arr[j - 1];
            Arr[j - 1]	= xx;
        }
    }
}
//--------------------------------------------------------------
// Бытсрая сортировка
//--------------------------------------------------------------
//--------------------------------------------------------------
// Бытсрая сортировка
// (обмен в массиве элементами с индексами i и j )
//--------------------------------------------------------------
void Work_Sorting::Exchange_Elements_I_J(int i, int j)
{
    int xx;
    xx		= Arr[i];      //<xi меняем с xj>
    Arr[i]	= Arr[j];
    Arr[j]	= xx;
}
//--------------------------------------------------------------
// Бытсрая сортировка
// (осортировка вставками)
//--------------------------------------------------------------
void Work_Sorting::Sorting_Quick_SInsert(int Left, int Right)
{
    int i, j, xx;

    for (j = Left + 1; j <= Right; j++)
    {
        xx = Arr[j];
        for (i = j - 1; i >= Left; i--)
        {
            if (xx > Arr[i]) break;
            Arr[i + 1] = Arr[i];
        }
        Arr[i + 1] = xx;
    }
}
//--------------------------------------------------------------
// Бытсрая сортировка
// разделение массива на подмассивы
//--------------------------------------------------------------
int Work_Sorting::Sorting_Quick_Separate(int i, int j)
{
    int master;
    master = Arr[i];
    i++;
    while (i <= j)
    {
        while ((Arr[i] < master) && (i <= j)) i++;
        while ((Arr[j] > master) && (i <= j)) j--;

        if (i < j) // < Arr[i] и Arr[j] меняем местами>
        {
            Exchange_Elements_I_J(i, j);
        }
    }
    i--;
    return i;
}
//--------------------------------------------------------------
// Быстрая сортировка
//--------------------------------------------------------------
void Work_Sorting::Sorting_Quick(int i, int j)
{

    int Main_Elem;
    int delta = 3;
    if (i >= j) return;
    if ((j - i) < delta)
    {
        Sorting_Quick_SInsert( i, j);
        return;
    }

    Main_Elem = (i + j) / 2;					// выбор главного жлемента
    Exchange_Elements_I_J(i, Main_Elem);		// <xi меняем с xs>
    Main_Elem = Sorting_Quick_Separate( i, j);	// разделение массива на подмассивы
    Exchange_Elements_I_J( i, Main_Elem);		// <xi меняем с xs>

    if ((Main_Elem - 1 - i) < (j - (Main_Elem + 1)))
    {
        Sorting_Quick( i, Main_Elem - 1);
        Sorting_Quick(Main_Elem + 1, j);
    }
    else
    {
        Sorting_Quick(Main_Elem + 1, j);
        Sorting_Quick( i, Main_Elem - 1);
    }

}
//---------------------------------------------------------------
// Поразрядная сортировка
// Num_T - разрядность ключей
//---------------------------------------------------------------
void Work_Sorting::Sorting_Radix(int Num_T)
{
    int i, j, d;
    int Current_Digit = 1;					// текущий рассматриваемый разряд
    List_Digit* Tmp;						// вспомогательный указатель
    List_Digit* Queue_All_Elem;				// список со всеми элементами массива
    List_Digit* Queue_Head[10];				// массив голов списков
    // (QHead[i] указывает на очередь
    // в которой находяться элементы
    // со значением i в текущем разряде

    List_Digit* Queue_Tail[10];				// массив хвостов списков

    Queue_All_Elem = new List_Digit; 		// формируем первый элемент списка Q
    Queue_All_Elem->val = Arr[0]; 			// как первый элемент массива Arr[0]
    Queue_All_Elem->next = NULL;

    Tmp = Queue_All_Elem;
    for (i = 1; i < Size_Array; i++)		// включаем в список Q
    {										// остальные элементы
        Tmp->next = new List_Digit; 		// массива Arr[i]
        Tmp = Tmp->next;
        Tmp->val = Arr[i];
        Tmp->next = NULL;
    }

    for (j = 1; j <= Num_T; j++)			// j - текущий рассматриваемый разряд чисел
    {
        for (i = 0; i <= 9; i++)			// очищаем очереди
        {
            Queue_Head[i] = NULL;
            Queue_Tail[i] = NULL;
        }

        while (Queue_All_Elem != NULL)		// проходим все элементы очереди Q
        {
            d = ((int)(Queue_All_Elem->val / Current_Digit)) % (int)10;		// у текущего элемента определяем
            // цифру в ткущем разряде

            Tmp = Queue_Tail[d];				// tmp - указывает на последний элемент
            // в очереди в которую мы вставим
            // текущий элемент очереди Q

            if (Queue_Head[d] == NULL)			// если текущая очередь пустая
            {
                Queue_Head[d] = Queue_All_Elem;	// текущий элемент из очереди Q вставляем
                // как первый элемент в очередь QHead[i]
            }
            else								// если в текущей очереди уже есть элементы
            {
                Tmp->next = Queue_All_Elem;		// текущий элемент из очереди Q вставляем
                // в конец очереди QTail[i]
            }

            Queue_Tail[d] = Queue_All_Elem;				// хвост очереди направляем на последний элемент
            Queue_All_Elem = Queue_All_Elem->next;		// переходим к следующему элементу очереди Q
            Queue_Tail[d]->next = NULL;					// элемент хвоста очереди дожен быть последним
        }

        for (i = 0; i <= 9; i++)						// находим первый
        {												// непустой список
            if (Queue_Head[i] != NULL) break;
        }
        Queue_All_Elem = Queue_Head[i];					// первый непустой список
        // включаем в очередь Q
        Tmp = Queue_Tail[i];
        for (d = i + 1; d <= 9; d++)					// включаем в очередь Q
        {												// остальные непустые списки
            if (Queue_Head[d] != NULL)
            {
                Tmp->next = Queue_Head[d];
                Tmp = Queue_Tail[d];
            }
        }
        Current_Digit = Current_Digit * 10;				// переходим к следующему разряду
        Tmp = Queue_All_Elem;							// подготавливаем промежуточные результаты
        for (i = 0; i < Size_Array; i++)
        {
            Arr[i] = Tmp->val;
            Tmp = Tmp->next;
        }
        Print_Array();									// распечатываем промежуточные результаты
    }

    for (i = 0; i < Size_Array; i++)					// очищаем память занятую под очередь Q
    {													// формируем окончательный
        Arr[i]         = Queue_All_Elem->val;			// отсортированный массив
        Tmp            = Queue_All_Elem;
        Queue_All_Elem = Queue_All_Elem->next;
        delete Tmp;
    }
}

//--------------------------------------------------------------
// Пирамидальная сортировка
//--------------------------------------------------------------
//--------------------------------------------------------------
//  Пирамидальная сортировка
//  процедура просеивания  элемента Start
//  До процедуры: a[Start+1]...a[Finish]  - пирамида
//  После:  a[Start]...a[Finish]  - пирамида
//--------------------------------------------------------------
void  Work_Sorting::Down_Heap(int Start, int Finish)
{
    int Child;

    while (Start <= Finish / 2)					// пока у Arr[Start] есть дети
    {
        Child = 2 * Start;						// определяем местоположение левого сына

        if (Child < Finish &&					//  мы не вышли за границы рассматриваемого массива
            Arr[Child] < Arr[Child + 1])		//  выбираем большего сына
        {
            Child++;							// если правый сын больше левого
            // смещаем указатель child на правого сына
        }
        if (Arr[Start] >= Arr[Child]) break;	// если корень больше правого сына то работы закончена

        Exchange_Elements_I_J( Start, Child);	// отца и большего сына меняем местами
        Start = Child;
    }
}
//--------------------------------------------------------------
// Пирамидальная сортировка (главная функция)
//--------------------------------------------------------------
void Work_Sorting::Sorting_Heap()
{
    int i;
    Print_Array();
    for (i = Size_Array / 2 - 1; i >= 0; i--)	// строим пирамиду
    {
        Down_Heap(i, Size_Array - 1);
    }
    // теперь Arr[0]...Arr[Size_Array-1] пирамида

    Print_Array();

    for (i = Size_Array - 1; i > 0; i--)
    {
        Exchange_Elements_I_J(0, i);			// меняем первый(наибольший текущий) с последним
        Print_Array();
        Down_Heap(0, i - 1);					// восстанавливаем пирамидальность Arr[0]...Arr[i-1]
        Print_Array();
    }
}

//--------------------------------------------------------------
// Cортировка прямое слияние
//--------------------------------------------------------------
void Work_Sorting::Sorting_Merge()
{
    int a1, a2, p, i, j, tmp;
    FILE* f, * f1, * f2;
    char Name_Source[]  = "\/home\/angryrunt\/dev\/angryrunt\/sort\/main.txt";
    char Name_Work1[]   = "\/home\/angryrunt\/dev\/angryrunt\/sort\/smsort_1.txt";
    char Name_Work2[]   = "\/home\/angryrunt\/dev\/angryrunt\/sort\/smsort_2.txt";

    f = fopen(Name_Source, "w");
    for (i = 0; i < Size_Array; i++)
    {
        fprintf(f, " %d ", Arr[i]);
    }
    fclose(f);

    p = 1;										// текущий размер серии

    while (p < Size_Array)						// пока полностью не обработаем
    {											// всю последовательность
        //-----------------------------
        // Фаза разбиения
        // распрелеяем массив из главного файла
        // по рабочим файлам
        //
        f = fopen(Name_Source, "r");
        f1 = fopen(Name_Work1, "w");
        f2 = fopen(Name_Work2, "w");
        if (!feof(f)) fscanf(f, "%d", &a1);
        while (!feof(f))
        {
            for (i = 0; (i < p) && (!feof(f)); i++)		// останов - конец серии
            {											// или конец главного файла

                fprintf(f1, "%d ", a1);					// записываем в рабочий файл
                fscanf(f, "%d", &a1);					// считываем из главного файла
            }
            for (j = 0; (j < p) && (!feof(f)); j++)
            {
                fprintf(f2, "%d ", a1);			//
                fscanf(f, "%d", &a1);			// при считывании данных указатель
                // смещаеться дальше
                // последний fscanf_s нужен для выхода
                // из цикла по концу файла
            }
        }
        fclose(f2);
        fclose(f1);
        fclose(f);

        //-----------------------------
        // Фаза слияния
        // распрелеяем массив из главного файла
        // по рабочим файлам
        //
        //fopen_s(&f, Name_Source, "w");
        f1 = fopen(Name_Work1, "r");
        f2 = fopen(Name_Work2, "r");
        if (!feof(f1)) fscanf(f1, "%d", &a1);
        if (!feof(f2)) fscanf(f2, "%d", &a2);
        while (!feof(f1) && !feof(f2))
        {
            i = 0;
            j = 0;
            while (i < p && j < p && !feof(f1) && !feof(f2))
            {
                if (a1 < a2)					// определяем наибольший элемент
                {								// и заносим его в результирующий файл
                    fprintf(f, "%d ", a1);
                    fscanf(f1, "%d", &a1);
                    i++;
                }
                else
                {
                    fprintf(f, "%d ", a2);
                    fscanf(f2, "%d", &a2);
                    j++;
                }
            }
            while (i < p && !feof(f1))			// если вторая подпоследовательность
            {									// закончилась, то переносим остаток первой
                fprintf(f, "%d ", a1);			// в результирующий файл
                fscanf(f1, "%d", &a1);
                i++;
            }
            while (j < p && !feof(f2))			// если первая подпоследовательность
            {									// закончилась, то копируем остаток второй
                fprintf(f, "%d ", a2);			// в результирующий файл
                fscanf(f2, "%d", &a2);
                j++;
            }
        }

        while (!feof(f1))						// ситуация, когда вторая последователность
        {										// изначально пустая
            fprintf(f, "%d ", a1);				// то переносим в результирующий файл
            fscanf(f1, "%d", &a1);			// первую подпоследовательность
        }

        while (!feof(f2))						// ситуация, когда первая последователность
        {										// изначально пустая
            fprintf(f, "%d ", a2);				// то переносим в результирующий файл
            fscanf(f2, "%d", &a2);			// вторую подпоследовательность
        }

        fclose(f2);
        fclose(f1);
        fclose(f);
        p = p * 2;								// увелчиваем размер серии в два раза

    }

    f = fopen(Name_Source, "r");
    for (i = 0; i < Size_Array; i++)
    {
        fscanf(f, "%d", &Arr[i]);
    }
    fclose(f);
}
//-----------------------------------------------------------------
void Work_Sorting::Run_Sorting()
{

	/*// Сортировка вставками
	Full_Array();
	Print_Array();
	Sorting_Insert();
	Print_Array();

	// Пузырьковая ортировка вставками
	Full_Array();
	Print_Array();
	this->Sorting_Bubble();
	Print_Array();

	// Быстрая сортировка
	Full_Array();
	Print_Array();
	Sorting_Quick(0, Size_Array - 1);
	Print_Array();
	Full_Array();
	Print_Array();
	printf("\n Task 01\n");
	Task01(0, Size_Array - 1, 3);
	Print_Array();

	// Поразрядная сортировка
	Full_Array();
	Print_Array();
	Sorting_Radix(3);
	Print_Array();


	// Пирамидальная сортировка
	Full_Array();
	Print_Array();
	Sorting_Heap();
	Print_Array(); */


    // Cортировка слиянием
    Full_Array();
    Print_Array();
    Sorting_Merge();
    Print_Array();





}
//-----------------------------------------------------------------
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    Work_Sorting Obj_Sort;
    Obj_Sort.Run_Sorting();

    getchar();
    return 0;
}