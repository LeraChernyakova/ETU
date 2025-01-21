#include "decide.h"
#include "print_and_input.h"
#define Size_Buf 100
int main()
{	setlocale(LC_ALL,"");
	printf("Введите Текст:\n");
	printf("Чтобы закончить ввод текста нажмите 2 раза подряд Enter\n");
	struct text Text=readtext();
	if (Text.kol_sym==-1)
			{printf("Ошибка памяти\n");
			return 0;}
	wchar_t a[Size_Buf]=L"";
	Text=removeSentense(Text);
	printf("Ваш текст после удаления повторных предложений\n");
	printText(Text);
	printf("Введите 0,если хотите завершить программу\n");
	printf("Введите 1,если хотите вывести все предложения, в которых каждое слово удовлетворяет введенной строке-условию.\n");
	printf("Введите 2,если хотите отсортировать предложения по средней длине слов в предложении(по возрастанию).\n");
	printf("Введите 3,если хотите преобразовать предложения так, чтобы слова располагались в порядке уменьшения длины слова.\n");
	printf("Введите 4,если хотите удалить все предложения, в котором больше 5 или меньше 2 слов.\n");
	do
	{printf("Ваша команда-");
	fgetws(a,Size_Buf,stdin);
	if (wcslen(a)!=2)
	{	printf("Ваша команда не распознана\n");
		continue;}
	switch (a[0])
		{case L'0':break;
		case L'1': printf("Ваша маска-");
			wchar_t *s=malloc(sizeof(wchar_t)*100);
			if (!s)
				{printf("Ошибка памяти\n");
				free_for_text(Text);
				return 0;}
			fgetws(s,100,stdin);
			int len=wcslen(s)-1;
			s[len]='\0';
			if (!strtok_for_mask(Text,s,len))
				{printf("Ошибка памяти\n");
				free_for_text(Text);
				return 0;}
			printf("\n");
			break;
		case L'2':qsort(Text.sen,Text.kol_sen,sizeof(struct sentense *),cmp);
			break;
		case L'3':for (int i=0;i<Text.kol_sen;i++)
				{Text.sen[i]->str=qsort_for_3(*Text.sen[i]);
				if (!Text.sen[i]->str)
					{printf("Ошибка памяти\n");
					free_for_text(Text);
					return 0;}}
			break;
		case L'4':Text=del_sentense(Text);
			break;
		default:
			printf("Ваша команда не распознана\n");
		}
	if (a[0]==L'2' || a[0]==L'3' || a[0]==L'4')
			printText(Text);
	if (a[0]!='0')
		if (Text.kol_sen==0)
			printf("Весь ваш текст удален,дальшейшая обработака бессмысленна,нажмите 0,чтобы выйти из программы\n");}
	while (a[0]!='0' || wcslen(a)!=2);
	free_for_text(Text);
	return 0;
}
