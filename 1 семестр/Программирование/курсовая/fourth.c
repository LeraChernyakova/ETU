int cmp(const void* a, const void* b){
	wchar_t **f = (wchar_t **)a;
	wchar_t **s = (wchar_t **)b;
	int l1 = wcslen(*f), l2 = wcslen(*s);
	int minl = 0;
	if ((l1< l2) || (l1 == l2))
		minl = l1;
	else
		minl = l2;
	int abc1 = 0, abc2 = 0;
	for (int k = 0; k < minl; k++){
		if (towupper(*f[k]) > towupper(*s[k])){
			abc2 += 1;
			break;
		}
		else if (towupper(*f[k]) <  towupper(*s[k])){
			abc1 += 1;
			break;
		}
		else
			continue;
	}
	if (abc1 < abc2)
		return 1;
	if (abc1 > abc2);
		return -1;
	return 0;		
}

void words_fourth(struct Text *text){
	int cnt_all_words = 0;
	int cnt = 0;
	for (int i = 0; i < text -> cnt_sent;i++){
		cnt = text -> sent[i] -> words;
		cnt_all_words = cnt_all_words + cnt;
	}
	wchar_t **allwords = malloc(sizeof(wchar_t*)*(cnt_all_words + MEM_STEP));
	int ind = 0;
	for (int i = 0; i < text -> cnt_sent; i++){
		wchar_t **wordsinsent = malloc(sizeof(wchar_t*)*((text -> sent[i] -> words) + MEM_STEP));
		int ind_s = 0;
		int len_sent_now = text -> sent[i] -> len;
		wchar_t * sent = malloc(sizeof(wchar_t)*(len_sent_now+ + MEM_STEP));
		wchar_t *sent_to_copy = text->sent[i]->str;
		wcscpy(sent, sent_to_copy);
		wchar_t *buf;
		wchar_t *pwc = wcstok(sent, L" .,",&buf);
		while (pwc != NULL){
			wordsinsent[ind_s] = malloc(sizeof(wchar_t)*(wcslen(pwc) + MEM_STEP));
			wcscpy(wordsinsent[ind_s], pwc);
			pwc = wcstok (NULL, L" .,",&buf);
			ind_s++;
		}
		for (int j = 0; j < ind_s; j++){
			int cnt_w = 0;
			for (int k = 0; k < ind_s; k++){
				if (wcscmp(wordsinsent[j],wordsinsent[k])==0)
					cnt_w++;
			}
			if (cnt_w == 4){
				int check = 0;
				for (int l = 0; l < ind; l++){
					if (wcscmp(wordsinsent[j],allwords[l])==0)
						check++;
				}
				if (check == 0){
					allwords[ind] = malloc(sizeof(wchar_t)*(wcslen(wordsinsent[j])+MEM_STEP));
					wcscpy(allwords[ind],wordsinsent[j]);
				}
			}
		}
			
	}
	for (int i = 0; i < ind; i++)
		wprintf (L"%ls ", allwords[i]);
	wprintf (L"\n");
	qsort(allwords, ind, sizeof(wchar_t*),cmp);
	for (int i = 0; i < ind; i++)
		wprintf (L"%ls ", allwords[i]);
	free (allwords);
	wprintf (L"\n");
}
