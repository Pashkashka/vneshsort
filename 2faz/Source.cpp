#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#include <stdbool.h>

bool End_Range(FILE* f) {
	int tmp;
	tmp = fgetc(f);
	tmp = fgetc(f);
	//Возвращаемся на 2 позиции назад
	if (tmp != '\'') fseek(f, -2, 1);
	else fseek(f, 1, 1);
	return tmp == '\'' ? true : false;
}

void NaturalMergingSort() {
	system("cls");
	int s1, s2, a1 = 0, a2 = 0, mark = 0;
	FILE* f, * f1, * f2;
	s1 = s2 = 1;
	//Пока в обоих файлах серия не равна нулю
	while (s1 > 0 && s2 > 0) {
		mark = 1;
		s1 = 0;
		s2 = 0;
		fopen_s(&f, "aa.txt", "r");
		fopen_s(&f1, "bb.txt", "w");
		fopen_s(&f2, "cc.txt", "w");
		//Первое число записываем в f1
		fscanf_s(f, "%d", &a1);
		if (!feof(f)) {
			fprintf(f1, "%d ", a1);
		}
		//Второе число сравниваем с первым и выбираем файл для записи
		//В случае, если будет найдена упорядоченная последовательность, серия увеличится, а время сортировки уменьшится
		if (!feof(f)) fscanf_s(f, "%d", &a2);
		while (!feof(f)) {
			if (a2 < a1) {
				switch (mark) {
				case 1:
					fprintf(f1, "' ");
					mark = 2;
					s1++;
					break;
				case 2:
					fprintf(f2, "' ");
					mark = 1;
					s2++;
					break;
				}
			}
			//Смена файлов
			if (mark == 1) { fprintf(f1, "%d ", a2); s1++; }
			else { fprintf(f2, "%d ", a2); s2++; }
			//Теперь будем сравнивать следующий элемент
			a1 = a2;
			fscanf_s(f, "%d", &a2);
		}
		//Последнее действие после полного прочтения файла, деление серий
		if (s2 > 0 && mark == 2) { fprintf(f2, "'"); }
		if (s1 > 0 && mark == 1) { fprintf(f1, "'"); }
		fclose(f2);
		fclose(f1);
		fclose(f);

		//Сортировка и запись в файл f
		fopen_s(&f, "aa.txt", "w");
		fopen_s(&f1, "bb.txt", "r");
		fopen_s(&f2, "cc.txt", "r");
		if (!feof(f1)) fscanf_s(f1, "%d", &a1);
		if (!feof(f2)) fscanf_s(f2, "%d", &a2);
		bool file1, file2;
		//Пока оба файла не закончились
		while (!feof(f1) && !feof(f2)) {
			//В каждом файле ещё есть серии
			file1 = file2 = false;
			while (!file1 && !file2) {
				if (a1 <= a2) {
					fprintf(f, "%d ", a1);
					//Определяем конец блока
					file1 = End_Range(f1);
					fscanf_s(f1, "%d", &a1);
				}
				else {
					fprintf(f, "%d ", a2);
					//Определяем конец блока
					file2 = End_Range(f2);
					fscanf_s(f2, "%d", &a2);
				}
			}
			//Если закончился второй файл
			while (!file1) {
				fprintf(f, "%d ", a1);
				file1 = End_Range(f1);
				fscanf_s(f1, "%d", &a1);
			}
			//Если закончился первый файл
			while (!file2) {
				fprintf(f, "%d ", a2);
				file2 = End_Range(f2);
				fscanf_s(f2, "%d", &a2);
			}
		}
		//Возвращаем значения
		file1 = file2 = false;
		//Записываем оставшиеся значения в файлах
		while (!file1 && !feof(f1)) {
			fprintf(f, "%d ", a1);
			file1 = End_Range(f1);
			fscanf_s(f1, "%d", &a1);
		}
		while (!file2 && !feof(f2)) {
			fprintf(f, "%d ", a2);
			file2 = End_Range(f2);
			fscanf_s(f2, "%d", &a2);
		}
		fclose(f2);
		fclose(f1);
		fclose(f);
	}
	printf("Успешно!\n");
}

void SimpleMergingSort() {
	system("cls");
	int a1 = 0, a2 = 0, series = 0, i = 0, j = 0, symCount = 0, tmp = 0;
	int number;
	FILE* f, * f1, * f2;

	symCount = 0;

	int count = 0;
	series = 1;

	fopen_s(&f, "aa.txt", "r");
	fopen_s(&f1, "bb.txt", "w");
	fopen_s(&f2, "cc.txt", "w");

	while (!feof(f)) {
		for (i = 0; i < series && !feof(f); i++) {
			if (i < series && feof(f))
				break;
			fscanf_s(f, "%d", &a1);
			fprintf(f1, "%d ", a1);
			symCount += 1;
		}
		fscanf_s(f, "%d", &a1);
		if (feof(f))
			break;
		else {
			fprintf(f2, "%d ", a1);
			symCount += 1;
			continue;
		}
		for (j = 0; j < series && !feof(f); j++) {
			if (j < series && feof(f))
				break;
			fscanf_s(f, "%d", &a1);
			fprintf(f2, "%d ", a1);
			symCount += 1;
		}
	}

	fclose(f2);
	fclose(f1);
	fclose(f);

	fopen_s(&f, "aa.txt", "w");
	fopen_s(&f1, "bb.txt", "r");
	fopen_s(&f2, "cc.txt", "r");

	if (!feof(f1))
		fscanf_s(f1, "%d", &a1);

	if (!feof(f2))
		fscanf_s(f2, "%d", &a2);


	while (!feof(f1) && !feof(f2)) {
		i = 0;
		j = 0;
		while (i < series && j < series && !feof(f1) && !feof(f2)) {
			if (a1 < a2) {
				fprintf(f, "%d ", a1);
				fscanf_s(f1, "%d", &a1);
				i++;
			}
			else {
				fprintf(f, "%d ", a2);
				fscanf_s(f2, "%d", &a2);
				j++;
			}
		}
		while (i < series && !feof(f1)) {
			fprintf(f, "%d ", a1);
			fscanf_s(f1, "%d", &a1);
			i++;
		}
		while (j < series && !feof(f2)) {
			fprintf(f, "%d ", a2);
			fscanf_s(f2, "%d", &a2);
			j++;
		}
	}

	while (!feof(f1)) {
		fprintf(f, "%d ", a1);
		fscanf_s(f1, "%d", &a1);
	}
	while (!feof(f2)) {
		fprintf(f, "%d ", a2);
		fscanf_s(f2, "%d", &a2);
	}
	fclose(f2);
	fclose(f1);
	fclose(f);
	series *= 2;

	while (series < symCount) {

		fopen_s(&f, "aa.txt", "r");
		fopen_s(&f1, "bb.txt", "w");
		fopen_s(&f2, "cc.txt", "w");

		while (!feof(f)) {
			for (i = 0; i < series && !feof(f) && count < symCount; i++) {
				if (i < series && feof(f))
					break;
				count += 1;
				fscanf_s(f, "%d", &a1);
				fprintf(f1, "%d ", a1);
			}

			for (j = 0; j < series && !feof(f) && count < symCount; j++) {
				if (j < series && feof(f))
					break;
				count += 1;
				fscanf_s(f, "%d", &a1);
				fprintf(f2, "%d ", a1);
			}
			if (count == symCount)
				fscanf_s(f, "%d", &number);
		}
		count = 0;
		fclose(f2);
		fclose(f1);
		fclose(f);

		fopen_s(&f, "aa.txt", "w");
		fopen_s(&f1, "bb.txt", "r");
		fopen_s(&f2, "cc.txt", "r");

		if (!feof(f1))
			fscanf_s(f1, "%d", &a1);

		if (!feof(f2))
			fscanf_s(f2, "%d", &a2);


		while (!feof(f1) && !feof(f2)) {
			i = 0;
			j = 0;
			while (i < series && j < series && !feof(f1) && !feof(f2)) {
				if (a1 < a2) {
					fprintf(f, "%d ", a1);
					fscanf_s(f1, "%d", &a1);
					i++;
				}
				else {
					fprintf(f, "%d ", a2);
					fscanf_s(f2, "%d", &a2);
					j++;
				}
			}
			while (i < series && !feof(f1)) {
				fprintf(f, "%d ", a1);
				fscanf_s(f1, "%d", &a1);
				i++;
			}
			while (j < series && !feof(f2)) {
				fprintf(f, "%d ", a2);
				fscanf_s(f2, "%d", &a2);
				j++;
			}
		}
		while (!feof(f1)) {
			fprintf(f, "%d ", a1);
			fscanf_s(f1, "%d", &a1);
		}
		while (!feof(f2)) {
			fprintf(f, "%d ", a2);
			fscanf_s(f2, "%d", &a2);
		}
		fclose(f2);
		fclose(f1);
		fclose(f);
		series *= 2;
	}
	printf("Успешно!\n");
}


void main() {

	setlocale(LC_ALL, "Rus");
	int number;
	char c = ' ';

	while (1) {
		printf("\tМеню\n1. Двухфазная сортировка\n2. Естественная сортировка\nВведите значение: ");

		scanf_s("%d", &number);

		while (c != '\n') {
			c = getchar();
		}


		switch (number) {
		case 1:
			SimpleMergingSort();
			break;
		case 2:
			NaturalMergingSort();
			break;
		default:
			printf("Введено некорректное значение!\nПовторите попытку\n");
			system("cls");
		}
	}
}