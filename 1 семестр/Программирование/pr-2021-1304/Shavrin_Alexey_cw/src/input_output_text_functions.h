#pragma once
struct Sentence *readSentence();
struct Text *readText();
struct Word *readWord();
void printText(struct Text *text);
void userChoice(struct Text *text);
