#include "Caesar_cipher.h"


int main() {
    system("clear");
    
    std::string str = "Hello World!";
    std::cout << std::endl <<  "Before coding  ---> " << str << std::endl << std::endl;
    CodeCipher obj1{str};
    str = obj1.coding(12);
    std::cout << "After coding   ---> " << str << std::endl << std::endl;
    DecodeCipher obj2 {str};
    str = obj2.coding(12);
    std::cout << "After decoding ---> " << str << std::endl << std::endl;

    return 0;
}
