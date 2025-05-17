#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_WORDS = 1000;
const int MAX_LINE_LENGTH = 1000;

// Global Classes and Variables
// Use of classes is must 

//////////////////////////////		PROTOTYPES OF HELPER FUNCTIONS	///////////////////////////////

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


///////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////		PROTOTYPES OF REQUIRED FUNCTIONS	///////////////////////////////

void readInput(const char* pathofInputFile);
int getNumberOfDocument();
char* getText(int documentNumber);
void removePunctuationMarks();
void convertUpperToLowerCase();
void removeStopWords();
void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency);
int getFrequency(char* word, int documentNum);
void calculateAllCosineSimilarities(double**& similarities, int** documentFrequency);
double similarityIn(int doucmentNum1, int documentNum2);

///////////////////////////////////////////////////////////////////////////////////////////



///////////////  1st Class with Global Pointer to Object /////////////////////////

class InputFileData
{
private:
    int noOfdoc;
    int noOfStopwords;
    char** docPaths;
    char** stopWords;
    char* stopWordline;
    char* inputFilepath;

public:
    InputFileData() :noOfdoc(0), noOfStopwords(0), docPaths(nullptr), stopWords(nullptr), stopWordline(nullptr), inputFilepath(nullptr) {}

    int getNoOfDoc()
    {
        return noOfdoc;
    }

    int getNoOfStopwords()
    {
        return this->noOfStopwords;
    }

    void setNoOfDoc(int num)
    {
        noOfdoc = num;
    }

    char** getDocPaths()
    {
        return docPaths;
    }

    void setDocPaths(char** paths)
    {
        docPaths = paths;
    }

    char** getStopWords()
    {
        return stopWords;
    }

    void setStopWords(char** words)
    {
        stopWords = words;
    }

    char* getStopWordLine()
    {
        return stopWordline;
    }

    void setStopWordLine(char* line)
    {
        this->stopWordline = assignChar(line);
        this->stopWordline = assignChar(stopWordline + 12);
    }

    char* getInputFilePath()
    {
        return inputFilepath;
    }

    void setInputFilePath(char* path)
    {
        inputFilepath = path;
    }

    void generateStopWords()
    {
        this->noOfStopwords = countWords(stopWordline);
        stopWords = generateWords(this->stopWordline);
    }

    void displayStopWords()
    {
        displayWords(stopWords, noOfStopwords);
    }

};

InputFileData* inpObj;

///////////////////////////////////////////////////////////////////////////

///////////////  2nd Class with Global Pointer to Object /////////////////////////

class DocData
{
private:
    static int myNumber;
    int numWords;
    char* myPath;
    char* myText;
    char** myWords;
    int decNumwords;
public:
    DocData() :numWords(0), decNumwords(0), myPath(nullptr), myText(nullptr), myWords(nullptr)
    {
        this->myNumber++;
    }

    void setPath(char* path)
    {
        this->myPath = assignChar(path);
    }

    char* getPath()
    {
        return this->myPath;
    }

    void setText(char* text)
    {
        this->myText = assignChar(text);
    }

    char* getText()
    {
        return this->myText;
    }

    char** getWords()
    {
        return myWords;
    }

    int getdecNumwords()
    {
        return decNumwords;
    }

    int getNumwords()
    {
        return this->numWords;
    }

    void readText()
    {
        ifstream DocText(this->myPath);

        if (DocText.eof())
            return;

        char Line[MAX_LINE_LENGTH];

        DocText.getline(Line, MAX_LINE_LENGTH);
        this->myText = assignChar(Line);

        while (!DocText.eof())
        {
            DocText.getline(Line, MAX_LINE_LENGTH);
            this->myText = append(this->myText, Line);
        }
    }

    void removePunct()
    {
        for (int i = 0; myText[i] != '\0'; i++)
        {
            if ((myText[i] != 32 && myText[i] < 65) || (myText[i] > 90 && myText[i] < 97) || myText[i] > 122)
                myText[i] = '!';
        }

        int count = 0;

        for (int i = 0; myText[i] != '\0'; i++)
        {
            if (myText[i] != '!')
                count++;
        }

        char* temp = new char[count + 1];

        int indice = 0;

        for (int i = 0; myText[i] != '\0'; i++)
        {
            if (myText[i] != '!')
            {
                temp[indice] = myText[i];
                indice++;
            }
        }

        temp[count] = '\0';

        this->myText = temp;

        if (myText[0] == ' ')
            myText[0] = '!';

        if (myText[count - 1] == ' ')
            myText[count - 1] = '!';

        for (int i = 1; myText[i] != '\0'; i++)
        {
            if (myText[i - 1] == ' ' && myText[i] == ' ')
                myText[i - 1] = '!';
        }

        count = 0;

        for (int i = 0; myText[i] != '\0'; i++)
        {
            if (myText[i] != '!')
                count++;
        }

        temp = new char[count + 1];

        indice = 0;

        for (int i = 0; myText[i] != '\0'; i++)
        {
            if (myText[i] != '!')
            {
                temp[indice] = myText[i];
                indice++;
            }
        }

        temp[count] = '\0';

        this->myText = temp;

    }

    void allLowerCase()
    {
        for (int i = 0; myText[i] != '\0'; i++)
        {
            if (myText[i] >= 65 && myText[i] <= 90)
                myText[i] += 32;
        }
    }

    void generateDocWords()
    {
        numWords = countWords(myText);
        myWords = generateWords(this->myText);
    }

    void displayDocWords()
    {
        displayWords(myWords, numWords);
    }

    void removeStopWords()
    {
        generateDocWords();
        decNumwords = numWords;
        for (int i = 0; i < this->numWords; i++)
        {
            for (int j = 0; j < inpObj->getNoOfStopwords(); j++)
            {
                if (compareArr(this->myWords[i], inpObj->getStopWords()[j]))
                {
                    delete[] myWords[i];
                    myWords[i] = nullptr;
                    this->decNumwords--;
                }
            }
        }
		updateText();
    }

    void updateText()
    {
        char* sp = new char[2];

        sp[0] = ' ';
		sp[1] = '\0';

        if (myText != nullptr)
        {
			delete[] myText;
            myText = nullptr;
            myText = "";
        }

        for (int i = 0; i < numWords; i++)
        {
            if (myWords[i])
            {
                if(i==0)
					myText = append(myText, myWords[i]);
				else
				{
					myText = append(myText, sp);
					myText = append(myText, myWords[i]);
				}
            }
        }
    }

};

int DocData::myNumber = 0;

DocData* docs;

///////////////////////////////////////////////////////////////////////////

///////////////  3rd Class with Global Pointer to Object /////////////////////////

class PlagiarismChecker
{
private:
    char** uniqueWords;
    int uniqueWordcount;
    int numAllwords;
    int** docFrequency;
    double** cosSimilarities;
    char** allWords;
public:
    PlagiarismChecker() :uniqueWords(nullptr), uniqueWordcount(0), numAllwords(0), docFrequency(nullptr), allWords(nullptr) {}

    void setcosSimilarities(double** arr)
    {
        this->cosSimilarities = arr;
    }

    double** getcosSimilarities()
    {
        return cosSimilarities;
    }

    void gatherAllWords()
    {
        int totalWords = 0;

        for (int i = 0; i < inpObj->getNoOfDoc(); i++)
        {
            totalWords += docs[i].getdecNumwords();
        }
        this->numAllwords = totalWords;
        allWords = new char* [totalWords];

        int index = 0;

        for (int i = 0; i < inpObj->getNoOfDoc(); i++)
        {
            for (int j = 0; j < docs[i].getNumwords(); j++)
            {
                if (docs[i].getWords()[j])
                {
                    allWords[index] = docs[i].getWords()[j];
                    index++;
                }
            }
        }
    }

    void countUniqueWords()
    {
        this->uniqueWordcount = numAllwords;
        for (int i = 0; i < numAllwords; i++)
        {
            for (int j = i + 1; j < numAllwords; j++)
            {
                if (allWords[i] && allWords[j])
                {
                    if (compareArr(allWords[i], allWords[j]))
                    {
                        allWords[j] = nullptr;
                        uniqueWordcount--;
                    }
                }
            }
        }
    }

    void generateUniqueWords()
    {
        uniqueWords = new char* [uniqueWordcount];

        int index = 0;

        for (int i = 0; i < numAllwords; i++)
        {
            if (allWords[i])
            {
                uniqueWords[index] = allWords[i];
                index++;
            }
        }
    }

    void displayUniqueWords()
    {
        displayWords(uniqueWords, uniqueWordcount);
    }

    void generateFrequencies()
    {
        this->docFrequency = new int* [inpObj->getNoOfDoc()];

        for (int i = 0; i < inpObj->getNoOfDoc(); i++)
            docFrequency[i] = new int[this->uniqueWordcount];

        for (int i = 0; i < inpObj->getNoOfDoc(); i++)
        {
            for (int j = 0; j < this->uniqueWordcount; j++)
                docFrequency[i][j] = 0;
        }

        for (int k = 0; k < this->uniqueWordcount; k++)
        {
            for (int i = 0; i < inpObj->getNoOfDoc(); i++)
            {
                for (int j = 0; j < docs[i].getNumwords(); j++)
                {
                    if (compareArr(docs[i].getWords()[j], uniqueWords[k]))
                        docFrequency[i][k]++;
                }
            }
        }
    }

    char** getUniquewords()
    {
        return uniqueWords;
    }

    int getUniquewordNum()
    {
        return this->uniqueWordcount;
    }

    int** getDocFreq()
    {
        return this->docFrequency;
    }

};

PlagiarismChecker* plagCheck;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////// DEFINITIONS OF REQUIRED FUNCTIONS ////////////////////////////////

void readInput(const char* pathofInputFile)
{
    ifstream inputFile(pathofInputFile);   // Object to read input

    if (inputFile.eof())
        return;
    else
        inpObj = new InputFileData;


    char Line[1000];

    inputFile.getline(Line, 1000);

    inpObj->setStopWordLine(Line);

    inputFile.getline(Line, 1000);

    int numDocs = strToNum(Line);
    inpObj->setNoOfDoc(numDocs);

    if (numDocs <= 0)
        return;


    docs = new DocData[numDocs];

    for (int i = 0; i < numDocs; i++)
    {
        inputFile.getline(Line, 1000);
        docs[i].setPath(Line);
        docs[i].readText();
    }

    inpObj->generateStopWords();
}

int getNumberOfDocument()
{
    return inpObj->getNoOfDoc();
}

char* getText(int documentNumber)
{
    if (docs)
        return docs[documentNumber - 1].getText();
}

void removePunctuationMarks()
{
    int numDocs = inpObj->getNoOfDoc();

    for (int i = 0; i < numDocs; i++)
    {
        if (docs)
            docs[i].removePunct();
    }
}

void convertUpperToLowerCase()
{
    int numDocs = inpObj->getNoOfDoc();

    for (int i = 0; i < numDocs; i++)
    {
        if (docs)
            docs[i].allLowerCase();
    }
}

void removeStopWords()
{
    int numDocs = inpObj->getNoOfDoc();

    for (int i = 0; i < numDocs; i++)
    {
        if (docs)
            docs[i].removeStopWords();
    }
}

void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency)
{
    plagCheck = new PlagiarismChecker;
    plagCheck->gatherAllWords();
    plagCheck->countUniqueWords();
    plagCheck->generateUniqueWords();
    plagCheck->generateFrequencies();

    uniqueWords = plagCheck->getUniquewords();
    uniqueCount = plagCheck->getUniquewordNum();
    documentFrequency = plagCheck->getDocFreq();
}

int getFrequency(char* word, int documentNum)
{
    for (int i = 0; i < plagCheck->getUniquewordNum(); i++)
    {
        if (compareArr(word, plagCheck->getUniquewords()[i]))
            return plagCheck->getDocFreq()[documentNum - 1][i];
    }

    return -1;
}

void calculateAllCosineSimilarities(double**& similarities, int** documentFrequency)
{
    similarities = new double* [inpObj->getNoOfDoc()];

    for (int i = 0; i < inpObj->getNoOfDoc(); i++)
        similarities[i] = new double[inpObj->getNoOfDoc()];

    for (int i = 0; i < inpObj->getNoOfDoc(); i++)
    {
        for (int j = 0; j < inpObj->getNoOfDoc(); j++)
        {
            if (i == j)
                similarities[i][j] = 100.00;
            else
                similarities[i][j] = calcCosineSimilarity(i, j, documentFrequency);
        }
    }

    plagCheck->setcosSimilarities(similarities);
}

double similarityIn(int doucmentNum1, int documentNum2)
{
    return plagCheck->getcosSimilarities()[doucmentNum1 - 1][documentNum2 - 1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////		DEFINITION OF HELPER FUNCTIONS	///////////////////////////////

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
        if (words[i])
            cout << words[i] << endl;
    }
}

int dotProdcalc(int* arr1, int* arr2)
{
    int size = plagCheck->getUniquewordNum();

    int* productArray = new int[size];

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

    double magnitudes[2] = { 0, 0 };

    for (int j = 0; j < size; j++)
        magnitudes[0] += arr1[j] * arr1[j];

    magnitudes[0] = sqrt(magnitudes[0]);

    for (int j = 0; j < size; j++)
        magnitudes[1] += arr2[j] * arr2[j];

    magnitudes[1] = sqrt(magnitudes[1]);

    return (magnitudes[0] * magnitudes[1]);
}

double calcCosineSimilarity(int i, int j, int** docFreq)
{
    return 100*dotProdcalc(docFreq[i], docFreq[j]) / calcMagnitude(docFreq[i], docFreq[j]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
