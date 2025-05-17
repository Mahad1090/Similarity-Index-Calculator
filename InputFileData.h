#pragma once

#include "HelperFtns.h"
#include "DocData.h"

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

}*inpObj;