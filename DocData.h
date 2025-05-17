#pragma once

#include "HelperFtns.h"
#include "InputFileData.h"

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
        cout << myText;
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

        char Line[1000];

        DocText.getline(Line, 1000);
        this->myText = assignChar(Line);

        while (!DocText.eof())
        {
            DocText.getline(Line, 1000);
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

        //cout << endl << "after putting !  : " << myText;

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

        //cout << endl << "Without punc : " << myText;


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

        //cout << endl << "Without double sp : " << myText;
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

    }

}*docs;

int DocData::myNumber = 0;