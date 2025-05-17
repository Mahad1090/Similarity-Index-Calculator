#pragma once

#include "generalHF.h"
#include "PlagiarismChecker.h"

//////////////////////////////		PROTOTYPES		///////////////////////////////

int countChar(char* text);
int strToNum(char* str);
char* assignChar(char* src);
char* append(char* ch1, char* ch2);
bool compareArr(char* ch1, char* ch2);
int countWords(char* text);
int* spaceIndices(char* text);
char* assignInrange(char* text, int start, int end);
char** generateWords(char* text);
void displayWords(char** words, int numWords);
int dotProdcalc(int* arr1, int* arr2);
double calcMagnitude(int* arr1, int* arr2);
double calcCosineSimilarity(int i, int j, int** docFreq);

//////////////////////////////		DEFINITION		///////////////////////////////

int countChar(char* text)
{
    if (!text)
        return 0;

    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
        count++;

    return count;
}

int strToNum(char* c)
{
    if (!c)
        return 0;

    int num = 0;
    int i = 0;

    while (c[i])
    {
        int temp = c[i] - 48;
        num += num * 10 + temp;
        i++;
    }

    return num;
}

char* assignChar(char* src)
{
    if (!src)
        return nullptr;

    int count = countChar(src);

    char* des = new char[count + 1];

    for (int i = 0; i < count; i++)
        des[i] = src[i];

    des[count] = '\0';

    return des;
}

char* append(char* ch1, char* ch2)
{
    if (!ch1 && !ch2)
        return nullptr;
    else if (!ch1)
        return ch2;
    else if (!ch2)
        return ch1;

    char* final = nullptr;

    int count1 = countChar(ch1);

    int count2 = countChar(ch2);

    int total = count1 + count2 + 1;

    final = new char[total];

    for (int i = 0; i < count1; i++)
        final[i] = ch1[i];

    for (int i = 0; i < count2; i++)
        final[count1 + i] = ch2[i];

    final[total - 1] = '\0';

    return final;
}

bool compareArr(char* ch1, char* ch2)
{
    if (!ch1 && !ch2)
        return true;
    else if (!ch1)
        return false;
    else if (!ch2)
        return false;

    int count1 = countChar(ch1), count2 = countChar(ch2);

    if (count1 != count2)
        return false;

    for (int i = 0; i < count1; i++)
    {
        if (ch1[i] != ch2[i])
            return false;
    }

    return true;
}

int countWords(char* text)
{
    if (!text)
        return -1;

    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
            count++;
    }

    count++;
    return count;
}

int* spaceIndices(char* text)
{
    if (!text)
        return nullptr;

    int* spaceIndice = new int[countWords(text) - 1];

    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            spaceIndice[count] = i;
            count++;
        }
    }

    return spaceIndice;
}

char* assignInrange(char* text, int start, int end)
{
    if (!text)
        return nullptr;

    char* temp = new char[end - start + 1];

    int count = 0;

    for (int i = start; i < end; i++)
    {
        temp[count] = text[i];
        count++;
    }

    temp[end - start] = '\0';

    return temp;
}

char** generateWords(char* text)
{
    if (!text)
        return nullptr;

    int wordCount = countWords(text);
    char** words = new char* [wordCount];
    int* spaceIndice = spaceIndices(text);

    for (int i = 0; i < wordCount - 1; i++)
    {
        if (i == 0)
            words[i] = assignInrange(text, 0, spaceIndice[0]);
        else
            words[i] = assignInrange(text, spaceIndice[i - 1] + 1, spaceIndice[i]);
    }

    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
        count++;

    words[wordCount - 1] = assignInrange(text, spaceIndice[wordCount - 2] + 1, count + 1);

    return words;
}

void displayWords(char** words, int numWords)
{
    if (!words)
        return;

    for (int i = 0; i < numWords; i++)
    {
        if(words[i])
            cout << words[i] << endl;
    }
}

int dotProdcalc(int* arr1, int* arr2)
{
    int size = plagCheck->getUniquewordNum();

    int *productArray = new int[size];

    for (int i = 0; i < size; i++)
    {
        productArray[i] = 1;
        productArray[i] *= (arr1[i] * arr2[i]);
    }

    int dotProduct = 0;

    for (int i = 0; i < size; i++)
        dotProduct += productArray[i];

    return dotProduct;
}

double calcMagnitude(int* arr1, int* arr2)
{
    int size = plagCheck->getUniquewordNum();

    double magnitudes[2];

    for (int i = 0; i < 2; i++)
    {
        magnitudes[i] = 1;

        for (int j = 0; j < size; i++)
        {
            magnitudes[i] += (arr1[j] * arr2[j]);
        }

        magnitudes[i] = sqrt(magnitudes[i]);
    }

    return (magnitudes[0] * magnitudes[1]);
}

double calcCosineSimilarity(int i, int j, int** docFreq)
{
    return dotProdcalc(docFreq[i], docFreq[j]) / calcMagnitude(docFreq[i], docFreq[j]);
}