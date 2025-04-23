// lesson24 Move constructor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cassert>
using namespace std;
class myString {
private:
    size_t _length = 0;
    size_t _capacity = 16;
    char* _text = nullptr;
    void setText(const char* text) {
        assert(!(text == nullptr));
        if (_text != nullptr) delete[] _text;
        size_t len = strlen(text) + 1;
        _text = new char[len];
        strcpy_s(_text, len, text);
        _length = len - 1;
        _capacity = len;
    }
public:
    myString()=default; // Default Constructor
    myString(const char* text)// Constructor with Param
    {
        setText(text);
    }

    myString(const myString& other) // Copy Constructor
    // Constructor with Param
    {
        _length = (other._length);
        _capacity = (other._capacity);
        _text = new char[_capacity];

        strcpy_s(_text, _capacity, other._text);
       
    }
    myString(const size_t count, const char text) {
       
        assert(count > 0); // Əgər count sıfır və ya mənfi olarsa, səhv mesajı veririk
        _length = count;
        _capacity = count + 1; // Nul terminatoru üçün əlavə yer ayırırıq
        _text = new char[_capacity]; // Yaddaş ayırırıq
        for (size_t i = 0; i < count; ++i) {
            _text[i] = text; // Hər bir simvolu təyin edirik
        }
        _text[count] = '\0'; // Nul terminatorunu əlavə edirik
    }
    // Copy Assignment operator
    myString& operator=(const myString& other) {
        if (this == &other) return *this;
        delete[]_text;
        _length = other._length;
        _capacity = other._capacity;
        _text = new char[_capacity];
        strcpy_s(_text, _capacity, other._text);
        return*this;
    }
    char& front() {
        if (_text!=nullptr)
        {
            return _text[0];
        }
    }
    char& back() {
        if (_text!=nullptr && _length>0)
        {
            return _text[-1];
        }
        else {
            cout << "text dogru daxil edilmeyib";
        }
    }
    char& at(size_t index) {
        if (_text!=nullptr && _length>0)
        {
            return _text[index];
        }
    }
    size_t capacity() const {
        return _capacity;

    }
    size_t size() const {
        if (_text!=nullptr)
        {
            return _length;
        }
        return 0;
    }
    size_t find(char chr) const {
        if (_text!=nullptr)
        {for (int i = 0; i < _length; i++)
        {
            if (_text[i] == chr)
            {
                return i;
            }
            
        }
        return -1;
        }  

    }
    size_t rfind(char chr) const {
        if (_text!=nullptr)
        {
            for (int i = _length-1; i >0 ; i--)
            {
        
            if (_text[i] == chr)
            {
                return i;
            }

            }
            
        }
        return -1;

    }
    void clear() {
        delete[] _text;
        _text = nullptr;
        _length = 0;
        _capacity = 0;
    }
    void resize(size_t newSize) {
        if (newSize!=_length)
        {
            char* newText = new char[newSize + 1];
            for (int i = 0; i < _length; i++)
            {
                newText[i] = _text[i];
            }
            if (newSize > _length)
            {
                for (int i = _length; i < newSize; i++)
                {
                    newText[i] = '\0';
                }
            }
            delete[] _text;
            _text = newText;
            _length = newSize;
            _capacity = newSize;

        }
        

    }
    void reserve(size_t newCapacity) {
        if (newCapacity > _capacity) {
            char* newText = new char[newCapacity];
            for (int i = 0; i < _length; i++)
            {
                newText[i] = _text[i];
            }
            delete[] _text;
            _text = newText;
            _capacity = newCapacity;
       }
        
    }
    void shrink_to_fit() {
        if (_capacity>_length+1)
        {
            char* newText = new char[_length + 1];
            for (int i = 0; i < _length; i++)
            {
                newText[i] = _text[i];
            }newText[_length] = '\0';
            delete[] _text;
            _text = newText;
            _capacity = _length + 1;
        }
    }
    bool empty() const {
        return (_text == nullptr || _length == 0);
    }
    myString append(const char* text) // "a".append("b") => "ab"
    {
        if (_text == nullptr) {
            cout << "Text yoxdur";
            exit(1);
       }
       int newTextlen = strlen(text);
       int totallen = newTextlen + _length;
       char* newText = new char[totallen + 1];
       for (int i = 0; i < _length; i++)
       {
           newText[i] = _text[i];
       }
       for (int i = 0; i < newTextlen; i++)
       {
           newText[_length + i] = text[i];
       }newText[totallen] = '\0';
       myString result(newText);
       delete[] newText;
       return result;
    }

    int compare(const myString right) // -1, 0, 1
    {
        int minLen;
        if (_length < right._length) {
            minLen = _length;
        }
        else {
            minLen = right._length;
        }
        for (size_t i = 0; i < minLen; i++) {
            if (_text[i] != right._text[i]) {
                return _text[i] - right._text[i];
            }
        }
        if (_length == right._length)
            return 0;
        else
            return (_length < right._length) ? -1 : 1;
    
    }
    const char* print() const { return _text; }

    ~myString() {
        delete[] _text;
    }
};


int main()
{
    myString str1("Salam");
    myString str2("Sagol");
    cout << "str1: " << str1.print() << endl;
    cout << "str2: " << str2.print() << endl;


    myString str3 = str1.append("Sagol");
    cout << "Append method: " << str3.print() << endl;

    int result = str1.compare(str2);
    cout << "Compare method: " << result << endl;

    int index = str1.find('a');
    cout << "index of first a: " << index << endl;

   int rindex = str1.rfind('a');
    cout << rindex << endl;

    cout << "Size: " << str1.size() << ", Capacity: " << str1.capacity() << endl;


    str1.resize(10);
    cout << "After resize (10): " << str1.print() << endl;

    str1.shrink_to_fit();
    cout << "shrink_to_fit: " << str1.print() << ", Capacity: " << str1.capacity() << endl;

    cout << " empty? " << (str1.empty() ? "Yes" : "No") << endl;

    str1.clear();
    cout << "After clear: " << (str1.empty() ? "empty" : "not empty") << endl;
    return 0;
}

