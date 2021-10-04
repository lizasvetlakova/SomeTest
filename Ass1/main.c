//В массиве из 10 чисел обнулить элементы, находящиеся между минимальным и максимальным элементами.

#include <stdio.h>
#define N 10


int main(void)
{
	short mas[N];
	int i;
	char s[] = "%hd";
	char f[] = "%hd ";

	__asm
	{
		mov ecx, N
		lea esi, mas // загрузка в esi адрес начала массива

		input :
		    mov i, ecx
			lea ebx, s
			push esi
			push ebx
			call scanf
			mov ecx, i
			add esp, 8 // освобождение 8 байт стека(эл-т s и эл-т mas)
			add esi, 2 // прибавили смещение на 2 байта(размер переменной)
			loop input

			mov ecx, N
			lea esi, mas
			mov ebx, esi
			mov edx, esi

		func :
		    cmp ecx, 0
			je en         //0 1 2 3 4 
			mov	ax, [esi] //1 2 3 10 5
			mov i, esi
			mov esi, ebx 
			cmp ax, [esi] // сравние текущего эл-та с максимальным
			mov esi, i
			jg max        
			mov esi, edx
			cmp ax, [esi] // сравние текущего эл-та с минимальным
			mov esi, i
			jl min        
			add esi, 2
			dec ecx
			jmp func
		max :
		    mov ebx, esi // запомнили индекс максимального
			add esi, 2
			dec ecx
			jmp func
		min :
		    mov edx, esi // запомнили индекс минимального
			add esi, 2
			dec ecx
			jmp func

		//доп задание: мах-мин = 10 разница (1...11) + к каждому элементу прибавить +10
		en :
			mov ax, [ebx]
			sub ax, [edx]
			cmp ax, 10
			je m
		    cmp edx, ebx //1 ...0 10
			mov esi, ebx //10 2... 1
			jb null_1    // если индекс мин. меньше чем индекс макс. 
			jmp null_2

		m :
			cmp edx, ebx
			mov esi, ebx
			jb ten_1    // если индекс мин. меньше чем индекс макс. 
			jmp ten_2

		ten_1:
			sub esi, 2
			cmp esi, edx
			je ex
			add[esi], 10
			jmp ten_1

		ten_2 :
			add esi, 2
			cmp esi, edx
			je ex
			add[esi], 10
			jmp ten_2

		null_1 :
			sub esi, 2
		    cmp esi, edx
			je ex        // выход если индексы сравнялись
			mov ax, [esi]
			mov ax, 0
			mov[esi], ax 
			jmp null_1

		null_2 :
			add esi, 2
		    cmp esi, edx
			je ex
			mov ax, [esi]
			mov ax, 0
			mov[esi], ax
			jmp null_2

		ex :
			mov ecx, N
			lea esi, mas

		output :
			mov i, ecx
			lea ebx, f
			push [esi]
			push ebx
			call printf
			mov ecx, i
			add esp, 8
			add esi, 2
			loop output
	}
	return 0;
}