#include <iostream>

class ACaesarCipher
{
public:
    virtual const std::string& coding (int) = 0;

protected:
    virtual bool isSmall (const char);
    virtual bool isCapital (const char);
    virtual bool smallStepInRange (int, int ) = 0;
    virtual bool capitalStepInRange (int, int) = 0;

protected:
    enum  limit {
        ALPHABET = 26,
        CAPITAL_LETTER_BEGIN = 65,
        CAPITAL_LETTER_END = 90,
        SMALL_LETTER_BEGIN = 97,
        SMALL_LETTER_END = 122
    }; 
    std::string _m_line;
};


class CodeCipher : public ACaesarCipher
{
public:
    explicit CodeCipher(const std::string&);
    CodeCipher(const CodeCipher&);
    CodeCipher& operator = (const CodeCipher&);
    ~CodeCipher () {};

public:
    const std::string& coding (int) override;

private:
    bool smallStepInRange (int, int ) override;
    bool capitalStepInRange (int, int) override;
};

class DecodeCipher : public ACaesarCipher
{
public:
    explicit DecodeCipher (const std::string&);
    DecodeCipher(const DecodeCipher&);
    DecodeCipher& operator = (const DecodeCipher&);
    const std::string& coding (int) override;
    ~DecodeCipher () {};

private:
    bool smallStepInRange (int, int ) override ;
    bool capitalStepInRange (int, int) override ;
};



bool ACaesarCipher::isSmall (const char lineSymbol) {
    bool result = true;
    if(lineSymbol >= SMALL_LETTER_BEGIN && lineSymbol <= SMALL_LETTER_END) {
        return result;
    }
    return !result;
}

bool ACaesarCipher::isCapital (const char lineSymbol) {
    bool result = true;
    if(lineSymbol >= CAPITAL_LETTER_BEGIN && lineSymbol <= CAPITAL_LETTER_END) {
        return result;
    }
    return !result;
};

CodeCipher::CodeCipher (const std::string& line) {
    _m_line = line;
} ;

CodeCipher::CodeCipher(const CodeCipher& other) {
    this->_m_line = other._m_line;
};

CodeCipher& CodeCipher::operator = (const CodeCipher& rhs) {
    if(this != &rhs) {
        this->_m_line = rhs._m_line;
    }
    return *this;
};

bool CodeCipher::smallStepInRange (int lineIndex, int step) {
    bool InRange = true;
    if(!(_m_line[lineIndex] - step < SMALL_LETTER_BEGIN)){
        return InRange;
    }
    return !InRange;
}

bool CodeCipher::capitalStepInRange (int lineIndex, int step) {
    bool InRange = true;
    if(!(_m_line[lineIndex] - step < CAPITAL_LETTER_BEGIN)) {
        return InRange;
    } 
    return !InRange;
}

const std::string& CodeCipher::coding (int __step) {
    __step %= ALPHABET;
    for (int lineIndex = 0; lineIndex < _m_line.size(); ++lineIndex) {
        if (isSmall(_m_line[lineIndex])) {
            if (smallStepInRange(lineIndex,__step)) {
                _m_line[lineIndex] = (_m_line[lineIndex] - __step); 
            } else {
                _m_line[lineIndex] = (SMALL_LETTER_END + 1  - (__step - (_m_line[lineIndex] % SMALL_LETTER_BEGIN)));
            }
        } 
        else if (isCapital (_m_line[lineIndex])) {
            if (capitalStepInRange (lineIndex,__step)) {
                _m_line[lineIndex] = (_m_line[lineIndex] - __step);  
            } else {
                _m_line[lineIndex] = (CAPITAL_LETTER_END + 1  - (__step - (_m_line[lineIndex] % CAPITAL_LETTER_BEGIN)));
            }
        }
    }
    return std::move(_m_line);
}

DecodeCipher::DecodeCipher (const std::string& line) {
    _m_line = line;
};

DecodeCipher::DecodeCipher(const DecodeCipher& other) {
    this->_m_line = other._m_line;
};

DecodeCipher& DecodeCipher::operator = (const DecodeCipher& rhs) {
    if(this != &rhs) {
        this->_m_line = rhs._m_line;
    }
    return *this;
};

bool DecodeCipher::smallStepInRange (int lineIndex, int step) {
    bool InRange = true;
    if ((_m_line[lineIndex] + step <= SMALL_LETTER_END)) {
        return InRange;
    }
    return !InRange;
}

bool DecodeCipher::capitalStepInRange (int lineIndex, int step) {
    bool InRange = true;
    if ((_m_line[lineIndex] + step <= CAPITAL_LETTER_END)) {
        return InRange;
    } 
    return !InRange;
}

const std::string& DecodeCipher::coding (int __step) {
    __step %= ALPHABET;
    for (int lineIndex = 0; lineIndex < _m_line.size(); ++lineIndex) {
        if (isSmall(_m_line[lineIndex])) {
            if (smallStepInRange (lineIndex,__step)) {
                _m_line[lineIndex] = (_m_line[lineIndex] + __step); 
            } else {
                _m_line[lineIndex] = (SMALL_LETTER_BEGIN - 1 + __step -  SMALL_LETTER_END + _m_line[lineIndex]);
            }
        } 
        else if (isCapital (_m_line[lineIndex])) {
            if (capitalStepInRange (lineIndex,__step)) {
                _m_line[lineIndex] = (_m_line[lineIndex] + __step); 
            } else {
                _m_line[lineIndex] = (CAPITAL_LETTER_BEGIN - 1 + __step - CAPITAL_LETTER_END + _m_line[lineIndex]);
            }
        }
    }
    return std::move(_m_line);
}
