//
// Created by Fatima Gowher on 2019-12-03.
//
#include "FamilySet.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

FamilySet::FamilySet()
{
    iterCount = 0;
}

FamilySet::FamilySet(string file)
{
    ifstream myFile(file);
    string word;

    while (getline(myFile, word))
        masterList.push_back(word);

    myFile.close();
    iterCount = 0;
}

FamilySet::FamilySet(string file, int len)
{
    cout<<len<<endl;
    ifstream myFile(file);
    string word;
/*
    while (getline(myFile, word))
    {
        if ((int)word.size() == len)
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            masterList.push_back(word);
        }
    }
  */

    while(myFile>>word)
    {
        if(word.length()==len)
        {
            masterList.push_back(word);
        }
    }

    myFile.close();
    iterCount = 0;
}

FamilySet::~FamilySet()
{
    // Deliberately empty
}

void FamilySet::filterFamilies(string letter, string guessPattern)
{
    // The first step is to clear dictionaries to prepare
    // for the new filter based on the letter and pattern
    dictionaries.clear();

    // For each word in the master list, you need to classify
    // what family is part of based on the letter and pattern.
    // If you can find letter in the word, then we need to
    // create the new family.
    // Otherwise, if the letter does not exist in the word, then
    // the family is simply the guessPattern.
    // Example 1:Suppose letter is "a", word is "ally", and
    //           guessPattern is ***y.
    //           In this case, the family is a**y. Once this
    //           is determined, then "ally" can be added to
    //           the "a**y" dictionary.
    // Example 2:Suppose letter is "a", word is "cool", and
    //           guessPattern is ***y.
    //           In this case, the family is ***y and "cool"
    //           would be added to the ***y dictionary.
    //dictionaries[guessPattern] = vector<string>();

    for (unsigned int i = 0; i < masterList.size(); i++)
    {
        string word = masterList[i];
        string family = guessPattern;

            // Replace the matching letter to the right '*' in the family
            for (unsigned i = 0; i < word.size(); i++)
            {
                if (word[i] == letter[0])
                {
                    family[i] = letter[0];
                }
                else
                    {
                    family[i]='*';
                }
            }

            // Put it in the dictionary
            dictionaries[family].push_back(word);
            //cout<<endl<<family;
        }
        //use iterator and then cout

        auto it = dictionaries.begin();
        while (it != dictionaries.end())
        {
            cout << it->first << " :: " << it->second.size() << endl;
            it++;
        }
}

void FamilySet::setFamily(string family)
{
    // This updates the master list.  The new master list
    // should contain the words within the dictionary for family.
    // dictionaries should be cleared after updating the master list.
    masterList.clear();
    masterList = dictionaries[family];
    //dictionaries.clear();
}

vector<string> FamilySet::getFamily(string family)
{
    // Returns the dictionary associated with family.
    return dictionaries[family];
}

string FamilySet::getRandomWord()
{
    // Returns random word from master list
    srand(time(0));
    return masterList[rand() % masterList.size()];
}

int FamilySet::numWords()
{
    // This should return the number of words in the master list
    return (int)masterList.size();
}

int FamilySet::numFamilies()
{
    // This should return how many families are in dictionaries
    // (Note FAMILIES, not words)
    //dictionaries.size();
    return (int) dictionaries.size();
}

void FamilySet::resetFamilyIter()
{
    // The iterator should return each family from
    // dictionaries (Note, it should returns the family,
    // not the words).
    // The resetFamilyIter function should be starting
    // iterator for dictionaries.
    iterCount = 0;
}

bool FamilySet::hasNext() {
    // Returns true as long as there is another family to return
    return iterCount < (int) dictionaries.size();
}

string FamilySet::getNextFamily()
{
    // Returns the next family using the unordered_map iterator.

    unordered_map< string, vector<string> >::iterator it = dictionaries.begin();
    int OutCounter=0;
    while(OutCounter != iterCount && it!=dictionaries.end())
    {

        OutCounter++;
        it++;

    }

   // for (int i = 0; i < iterCount; i++)
    //    it++;
    iterCount++;
    return it->first;

}

int FamilySet::familySize(string family)
{
    // Returns the size of the dictionary of family.
    return (int) dictionaries[family].size();
}
