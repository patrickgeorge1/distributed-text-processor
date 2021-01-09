#include "TextProcessor.h"

TextProcessor::TextProcessor()
{
}

TextProcessor::~TextProcessor()
{
}

bool TextProcessor::isValidWord(string s) {
    for (char const &c: s) {
        if (isalpha(c)) return true;        
    }
    return false;
}

string TextProcessor::processWordAsFantasy(string word) {
    char c = word[0];
    if (isalpha(c)) c = toupper(c);
    return (c + word.substr(1, string::npos));
}



string TextProcessor::processWordAsSF(string s) {
    string delimiter = " ";
    size_t pos = 0;
    string word;
    string processed_lines = "";
    int counter = 0;
    cout << s << endl;

    while ((pos = s.find(delimiter)) != std::string::npos && counter < 6)
    {
        word = s.substr(0, pos);
        processed_lines += word;
        processed_lines += " ";
        s.erase(0, pos + delimiter.length());
        if (isValidWord(word)) counter++;

    }
    // 7 th word
    pos = s.find(delimiter);
    word = s.substr(0, pos);
    reverse(word.begin(), word.end());
    processed_lines += word;
    processed_lines += " ";
    s.erase(0, pos + delimiter.length());

    // rest of s
    processed_lines += s;

    return processed_lines;
}

ParagraphPiece TextProcessor::processAsHorror(ParagraphPiece p) {
    string lines = p.getLines();
    string processed_lines = "";
    string consonants = "QZWSXDCRFVTGBYHNJMKLPqzwsxdcrfvtgbyhnjmklp";

    for (char const &c: lines) {
        if (consonants.find(c) == string::npos)
        {
            processed_lines += c;
        } else {
            processed_lines += c;
            processed_lines += tolower(c);
        }
    }
    p.setLines(processed_lines);
    return p;
}


ParagraphPiece TextProcessor::processAsSF(ParagraphPiece p){
    string s = p.getLines();
    string delimiter = "\n";
    size_t pos = 0;
    string word;
    string processed_lines = "";

    while ((pos = s.find(delimiter)) != string::npos)
    {
        word = s.substr(0, pos);
        string copy(word);
        processed_lines += processWordAsSF(copy);
        processed_lines += '\n';

        s.erase(0, pos + delimiter.length());
    }
    processed_lines += processWordAsSF(s);

    p.setLines(processed_lines);
    return p;
}



ParagraphPiece TextProcessor::processAsComedy(ParagraphPiece p){
    string processed_lines = "";
    string lines = p.getLines();
    int counter = 0;

    for (string::size_type i = 0; i < lines.size(); i++) {
        int ascii =  lines[i] - '\0';
        char c = lines[i];
        if ((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122))
        {
            counter++;
            if (counter % 2 == 0)
            {
                c = toupper(c);
            }
        } else {
            counter = 0;
        }
        processed_lines += c;
    }

    p.setLines(processed_lines);
    return p;  
}

ParagraphPiece TextProcessor::processAsFantasy(ParagraphPiece p){
    string s = p.getLines();
    string delimiter = " ";
    size_t pos = 0;
    string word;
    string processed_lines = "";

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        word = s.substr(0, pos);
        processed_lines += processWordAsFantasy(word);
        processed_lines += " ";
        s.erase(0, pos + delimiter.length());
    }
    processed_lines += processWordAsFantasy(s);


    p.setLines(processed_lines);
    return p;   
}

ParagraphPiece TextProcessor::processPiece(ParagraphPiece p) {
    switch (p.getGenre())
    {
    case GENRE_HORROR:
        return processAsHorror(p);
        break;

    case GENRE_SF:
        return processAsSF(p);
        break;

    case GENRE_COMEDY:
        return processAsComedy(p);
        break;

    case GENRE_FANTASY:
        return processAsFantasy(p);
        break;
    
    default:
        cout << "invalid genre" << endl;
        exit(1);
        break;
    }
}