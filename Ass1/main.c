//� ������� �� 10 ����� �������� ��������, ����������� ����� ����������� � ������������ ����������.

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
		lea esi, mas // �������� � esi ����� ������ �������

		input :
		    mov i, ecx
			lea ebx, s
			push esi
			push ebx
			call scanf
			mov ecx, i
			add esp, 8 // ������������ 8 ���� �����(��-� s � ��-� mas)
			add esi, 2 // ��������� �������� �� 2 �����(������ ����������)
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
			cmp ax, [esi] // ������� �������� ��-�� � ������������
			mov esi, i
			jg max        
			mov esi, edx
			cmp ax, [esi] // ������� �������� ��-�� � �����������
			mov esi, i
			jl min        
			add esi, 2
			dec ecx
			jmp func
		max :
		    mov ebx, esi // ��������� ������ �������������
			add esi, 2
			dec ecx
			jmp func
		min :
		    mov edx, esi // ��������� ������ ������������
			add esi, 2
			dec ecx
			jmp func

		//��� �������: ���-��� = 10 ������� (1...11) + � ������� �������� ��������� +10
		en :
			mov ax, [ebx]
			sub ax, [edx]
			cmp ax, 10
			je m
		    cmp edx, ebx //1 ...0 10
			mov esi, ebx //10 2... 1
			jb null_1    // ���� ������ ���. ������ ��� ������ ����. 
			jmp null_2

		m :
			cmp edx, ebx
			mov esi, ebx
			jb ten_1    // ���� ������ ���. ������ ��� ������ ����. 
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
			je ex        // ����� ���� ������� ����������
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