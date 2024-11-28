#include <algorithm>
#include<bits/stdc++.h>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;


class StringSet
{
    vector <string> words;
    public:
    StringSet(fstream& file,string& s)
    {
        string word="";
        string* p = &word;
        for(int j = 0 ; j<s.length() ; j++)
        {
            if(s[j]==' ' || s[j]== ',' || s[j]=='.')
            {
                words.push_back(*p);
                *p="";
            }else{
                *p+=tolower(s[j]);
            }
        }
        for(int i = 0 ; i<words.size() ;i++)
        {
            file << words[i];

        }
                     
    }
    StringSet(string& s)
    {
        string word="";
        string* p = &word;
        for(int j = 0 ; j<s.length() ; j++)
        {
            if(s[j]==' ' || s[j]== ',' || s[j]=='.')
            {
                words.push_back(*p);
                *p="";
            }else{
                *p+=tolower(s[j]);
            }
        }
    }
    void add(const string& s)
    {
        string word="";
        for(int i = 0 ; i<s.length() ; i++)
        {
            if(s[i]!=' ')
            {
                word+=tolower(s[i]);
            }
        }words.push_back(word);
    }
    void remove(const string& s)
    {
        string word ="";
        for(int i = 0 ; i<s.length() ; i++)
        {
            if(s[i]!=' ')
            {
                word+=tolower(s[i]);
            }
        }for(int j = 0 ; j<words.size() ; j++)
        {
            if(words[j]==word)
            {
                words.erase(words.begin()+j);
            }
        }
    }

    void clear()
    {
        words.clear();
    }
    int getSize()
    {
        return words.size();
    }
    void show()
    {
        cout<<'{';
        for(int i = 0 ; i<words.size() ; i++)
        {
            cout<<words[i]<<',';
        }
        cout<<'}'<<'\n';
    }
    string getWord(const int& index)
    {
        return words[index];
    }
    vector<string> getSet()
    {
        return words;
    }
    friend vector<string> operator+(StringSet& set1 ,StringSet& set2);
    friend vector<string> operator*(StringSet& set1,StringSet& set2);
    double compare(StringSet& doc, StringSet& query)
    {
        vector<string> intersection = doc*query;
        int size = intersection.size();
        double sim = size/ (sqrt(doc.getSize())*sqrt(query.getSize()));
        return sim;
    }
};

vector<string> operator+( StringSet& set1 , StringSet& set2)
{
    set <string> result(set1.getSet().begin(),set1.getSet().end());
    result.insert(set2.getSet().begin(),set2.getSet().end());
    return vector<string>(result.begin(),result.end());
}


vector<string> operator*(StringSet& set1 , StringSet& set2)
{
    vector<string> v1 = set1.getSet();
    vector<string> v2 = set2.getSet();
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());

    vector<string> intersection;

    set_intersection(v1.begin(), v1.end(),v2.begin(),v2.end(),back_inserter(intersection));
    return intersection;
}

int main()
{
        // Test 1: Constructor from string
    string inputText = "Hello, world. This is a test.";
    StringSet set1(inputText);

    cout << "Testing constructor with string input:" << endl;
    set1.show();
    cout << endl;

    // Test 2: Add a new word
    cout << "Adding 'newword' to the set:" << endl;
    set1.add("newword");
    set1.show();
    cout << endl;

    // Test 3: Remove a word
    cout << "Removing 'world' from the set:" << endl;
    set1.remove("world");
    set1.show();
    cout << endl;

    // Test 4: Clear the set
    cout << "Clearing the set:" << endl;
    set1.clear();
    set1.show();
    cout << "Size of set after clear: " << set1.getSize() << endl;
    cout << endl;

    // Test 5: Constructor from file
    fstream testFile("testFile.txt", ios::out | ios::app);
    testFile.clear();
    testFile.seekg(0);
    string data = "this is some string to put into the file";
    StringSet set2(testFile,data);
    cout << "Testing constructor with file input:" << endl;
    set2.show();
    cout << endl;

    // Test 6: Union and Intersection operators
    cout << "Testing union and intersection operators:" << endl;
    string anotherText = "This is another test. String3 and string4.";
    StringSet set3(anotherText);

    vector<string> unionSet = set2 + set3;
    cout << "Union of sets:" << endl;
    for (const auto& word : unionSet) {
        cout << word << " ";
    }
    cout << endl;

    vector<string> intersectionSet = set2 * set3;
    cout << "Intersection of sets:" << endl;
    for (const auto& word : intersectionSet) {
        cout << word << " ";
    }
    cout << endl;

    // Test 7: Comparison
    cout << "Testing similarity comparison:" << endl;
    double similarity = set2.compare(set2, set3);
    cout << "Similarity: " << similarity << endl;

}
