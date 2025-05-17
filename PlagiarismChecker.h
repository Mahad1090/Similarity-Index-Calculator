#pragma once

#include "HelperFtns.h"
#include "InputFileData.h"
#include "DocData.h"


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
			cout << docs[i].getdecNumwords() << endl;
		}
		cout << totalWords;
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
					cout << endl << allWords[index];
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
				if(allWords[i]&&allWords[j])
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
					if (compareArr(docs[i].getWords()[j],uniqueWords[k]))
						docFrequency[i][k]++;
				}
			}
		}

		cout << endl;
		for (int i = 0; i < inpObj->getNoOfDoc(); i++)
		{
			for (int j = 0; j < this->uniqueWordcount; j++)
			{
				cout << docFrequency[i][j] << " ";
			}
			cout << endl;
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