#pragma once
void removingSentence(struct Sentence sent);
void freeSentence(struct Sentence sent);
void freeText(struct Text *text);
void removingDuplicateSentences(struct Text *text);
void sumSec(struct Text *text);
void removingSertainSentences(struct Text *text);
int sumCode(struct Sentence *sent);
int funccmp(const void *x1, const void *x2);
void replaceSymbol(struct Text *text);
