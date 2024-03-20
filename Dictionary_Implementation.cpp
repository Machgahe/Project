#include <bits/stdc++.h>

using namespace std;

#define KEY_EXISTS_DICT(KEY, DICT)  ( (DICT.find(KEY) == DICT.end()) ? (false) : (true))

string INPUT_FILE_NAME = "Data.CS.SFSU.txt";
string POS[] = {"noun", "pronoun", "adjective", "verb", "adverb", "preposition", "conjunction", "interjection"};

string make_lower(string data) {
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

bool check_pos(string pos) {
    for (int i = 0; i < 8; i++) {
        if (POS[i] == make_lower(pos))
            return true;
    }
    return false;
}


void print(vector<string> &v) {
    for (size_t n = 0; n < v.size(); n++)
        cout << "\"" << v[n] << "\"\n";
    cout << endl;
}

class Dictionary {
private:
    string key_name;
    map<string, vector<string> > value;


public:

    Dictionary() {
        key_name = "";
        for (int i = 0; i < 8; i++) {
            value[POS[i]] = vector<string>();
        }
    }

    void add_key_name(string key) {
        key_name = key;
    }

    string get_key_name() {
        return key_name;
    }

    void print_meanings(string pos, bool print=false) {
        if ( print && value[make_lower(pos)].size()==0)
            cout<<"\t\t<Not found.>"<<endl;
        for (string meaning : value[make_lower(pos)]) {
            cout<< "\t\t " << key_name << " [" << pos << "] : " << meaning << endl;
        }
    }

    void add_value(string pos, string meaning) {
        value[make_lower(pos)].push_back(meaning);
    }

    void print_all_value() {
        map<string, vector<string> >::iterator it;

        for (it = value.begin(); it != value.end(); ++it) {
            print_meanings(it->first);
        }
    }

    void print_value(string pos=""){
        if (pos=="")
            print_all_value();
        else
            print_meanings(pos);
    }

};

vector<string> split(string stringToBeSplitted, string delimeter)
{
    vector<string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
        string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + delimeter.size();
    }
    if(startIndex < stringToBeSplitted.size())
    {
        string val = stringToBeSplitted.substr(startIndex);
        splittedString.push_back(val);
    }
    return splittedString;
}


//class

Dictionary parse_line(string line){
    Dictionary dictionary;
    vector<string> key_value;
    key_value = split(line, "|");
    dictionary.add_key_name(key_value[0]);
    for (size_t n = 1; n < key_value.size(); n++){
        vector<string> pos_meaning_pair;
        pos_meaning_pair = split(key_value[n], " => ");
        dictionary.add_value(pos_meaning_pair[0], pos_meaning_pair[1]);
    }
    return dictionary;
}



int main() {
    map<string, Dictionary> dictionary;


    cout<<"! Opening data file... ./"<<INPUT_FILE_NAME<<endl;
    ifstream infile(INPUT_FILE_NAME);
    if (!infile) {
        cout << "unable to open file";
        return false;
    }
    cout<<"! Loading data..."<<endl;
    cout<<endl<<"-----DICTIONARY 340 C++-----"<<endl;
    string input_line;
    while (getline(infile, input_line))
    {
        Dictionary temp_dictionary;
        temp_dictionary = parse_line(input_line);
        dictionary[make_lower(temp_dictionary.get_key_name())] = temp_dictionary;
    }
    cout<<"! Loading completed..."<<endl;

    cout<<"! Closing data file... ./"<<INPUT_FILE_NAME<<endl;


    while (true) {
        string line;
        cout <<"Search: ";
        getline(cin, line);
        if (line=="!Q" || line=="!q"){
            cout<<endl<<"-----THANK YOU-----"<<endl;
            break;
        }

        cout << "\t\t|"<<endl;
        vector<string> search_data;
        search_data = split(line, " ");

        if (search_data.size()>2 || search_data.size()==0)
            cout<<"\t\t<Please enter a search key (and a part of speech).>"<<endl;
        else if (search_data.size()==1){
            if (KEY_EXISTS_DICT(make_lower(search_data[0]),dictionary)){
                dictionary[make_lower(search_data[0])].print_all_value();
            }else{
                cout<<"\t\t<Not found.>"<<endl;
            }
        }else{
            if (check_pos(search_data[1])){
                dictionary[make_lower(search_data[0])].print_meanings(make_lower(search_data[1]), true);
            }else{
                cout<<"\t\t<2nd argument must be a part of speech.>"<<endl;
            }
        }
        cout << "\t\t|"<<endl;

    }




    return 0;
}