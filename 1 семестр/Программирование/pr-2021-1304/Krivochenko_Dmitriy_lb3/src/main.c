#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define strLen 1000


int
main ()
{

  char c;
  char *endl = "Dragon flew away!";
  char *sentTern = ".;!?";
  char **text = malloc (sizeof (char *));
  char termChar = '7';
  int flagSent = 1;
  int flagText = 1;
  int sentCount = 0;
  int charCount = 0;
  int countansw = 0;
  while (flagText)
    {
      charCount = 0;
      text = realloc (text, sizeof (char *) * (sentCount + 1));
      text[sentCount] = malloc (sizeof (char) * strLen);
      c = getchar ();
      text[sentCount][charCount] = c;


      do
	{
	  charCount++;
	  c = getchar ();
	  text[sentCount][charCount] = c;
	  flagSent = (strchr (sentTern, c) == NULL);

	}
      while (flagSent == 1);

      text[sentCount][charCount + 1] = '\0';
      c = getchar ();
      flagText = (strstr (text[sentCount], endl) == NULL);
      sentCount++;

    }

  for (int i = 0; i < sentCount; i++)
    {
      if (strchr (text[i], termChar) == NULL)
	{
	  printf ("%s\n", text[i]);
	  countansw++;
	}
      free (text[i]);
    }
  free (text);
  printf("Количество предложений до %d и количество предложений после %d\n", sentCount-1 ,countansw-1);
  return 0;
}
