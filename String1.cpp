#include <iostream>
#include <string.h>

using namespace std;

class String {
private:
    char* buff;
    size_t size;
    //int* ref;
public:
    String(const char* s){  
        cout << "String(char*)" << endl;
        size = strlen(s);
        buff = new char[size+1];
        strcpy(buff,s);
    }
    String(){  
        cout << "String()" << endl;
        size = 0;
    }
    String(const String& s){  
        cout << "String(String&)" << endl;
        size = s.size;
        buff = new char[size+1];
        strcpy(buff,s.buff);
    }
    String& operator=(const String& s)
    {
        if(&s == this){
            return *this;
        }
        size = s.size;
        delete[] buff;
        buff = new char[size+1];
        strcpy(buff,s.buff);
        return *this;
    }
    ~String(){ 
        cout << "~String()" << endl;  
        if(size > 0) delete[] buff; 
    }
    friend ostream& operator<<(ostream& os, String& s);

};
ostream& operator<<(ostream& os, String& s)
{
    if(s.size > 0){
        cout << s.buff << endl;
    } else {
        cout << "not assigned" << endl;
    }
}

int main() {
// 1단계. 생성자, 소멸자, 화면 출력
    String s1 = "hello";
    cout << s1 << endl;
// 2단계. 복사 생성자
    String s2 = s1;
    cout << s2 << endl;
// 3단계. 대입연산자
    String s3 = "student";
    s3 = s1;
    cout << s3 << endl;
// 4단계. 자신과의 대입
    s1 = s1;
    cout << s1 << endl;
// 5단계. 디폴트 생성자
String s4;
    cout << s4 << endl;
    /*
    */
}
