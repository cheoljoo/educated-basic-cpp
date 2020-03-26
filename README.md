# educated-basic-cpp

- 소스 : https://github.com/codenuri/CPP1

# 2. namespace
- 관련된 요소를 묶어서 관리가 편하다.
- 이름 충돌을 막을수 있다.

## namespace에 있는 요소 접근하는 3가지 방법
1. qualified name을 이용 -> Audio::init();
1. using 선언을 사용하는 방법 -> using Audio::init;
1. using 지시어 -> using namespace Audio;

- using 선언 및 지시어는 함수 안에 바깥에 놓을수 있다 .
- 가능하면 qualified name 을 이용하는게 가장좋다.
- ::init() 을 하면 무조건 global에 있는 것을 쓰면 된다. 

## 함수를 선언 파일과 구현 파일로 분리 할때
1. 함수의 선언부와 구현부를 모두 namespace로 묶어야 한다.  namespace Audio {  ....  ... }
1. 구현부를 만드는 2가지 방법 : 대부분 1번 방법을 사용하는게 가장 좋다. 

## namespace std
- count는 std에 도 있다.  이름 충돌이 나올수 있다. 
- ```cpp
    int count=0;
    ::count
  ```

## C++ 표준 헤더 파일 
- 헤더 파일의 확장자를 사용하지 않는다.
- <cstdio> 은 <stdio.h> 에서 뒤의 확장자 없애고 앞에 c를 붙이면 된다.

### <stdio.h> vs <cstdio>
- C++은 표준 요소를 std 이름 공간에 제공한다.
- <stdio.h> : printf()등의 표준 함수가 "global namespace" 에 있다.
- <cstdio> 는 printf가 "std" 이름 공간에 있다. 그리고, global namespace에도 있다.

### 전역 공간에 있는 함수를 namespace에 포함하는 방법
```cpp
void foo() {}
namespace Audio {
    using ::foo;
}
```


# 3. C++ 표준 입출력
## 표준 입출력
- std::cout
- std::cin

## iomanipulator  (조정자 함수)
- std::cout << std::hex << n << std::endl;   // 16진수로 출력원할때
- std::hex는 뒤에도 영향을 미친다. 
- std::cout << std::hex;  를 넣으면 이 뒤는 모두 16진수로 출력하는 것이다. 
- std::setw   문자열 출력시 개수 지정
- std::setfill   공백을 채울 문자 지정
- std::left   왼쪽 정렬


# 4. C++ 변수의 특징 
## C++ 변수의 특징
- 함수의 중간에 변수 선언 가능
- 구조체를 만들때 struct를 표기하지 않다도 된다. 
```cpp
struct Point { }
Point pt;
```
- 구조체를 만들때 초기화 가능
- 2진수 표기법 , 자릿수 표기법 : 0b10   1'000'000   코드의 가독성을 높이기 위한 것임  ' 은 compile할때 무시됨.
- 새로운 data type : bool , long long  , char16_t (UTF16) , char32_t (UTF32)

## 일관된 초기화 : uniform initialization
- 중괄호를 사용해서 초기화 가능 : {} 
- 기존 초기화 방법의 문제점
    - 초기화 방법이 다양 : =값 , (값) , {값}
    - 암시적 형 변환에 따른 데이터 손실
- uniform initialization의 장점
    - 하나의 방식
    - 데이터 손실이 발생하는 모든 코드는 compile error
- ```foo({10});``` 으로 사용할수 있다.  함수의 인자로 중괄호를 사용한 초기값 전달 가능
    - goo( {1,2} );
- 초기화 방법
    - copy초기화 : int n1 = {0};
    - direct 초기화 : int n2{0};  n2(0)
    - explicit 생성자를 가지는 타입은 "direct 초기화"만 가능하다. 

## audo/decltype
- decltype(n1) n3;  n1의 type을 가지고 n3의 type을 설정하라.
    - compile 시간에 결정
    - ()안의 표현식이 배열이면 "()안의 표현식과 완전히 동일한 배열 타입"으로 추촌
        - 이경우 동일 표현식으로 초기화 할 수 없다.
- audo : 우변의 수식으로 좌변의 타입을 결정 
    - 반드시 초기값이 필요
    - **우변이 배열이면 "요소를 가리키는 포인터 타입"으로 추론**
```cpp
int x[3] = {1,2,3};
auto a2 = x ;  // 1. int a2[3] = x; 라고 추론하면 에러
                // 2. int* a2 = x; 라고 추론하면 OK
decltype(x) d2;   // int d2[3]으로 추론
decltype(x) d3 = x;  // int d3[3] = x ; 컴파일 에러

int y[2] = {1,2};
auto a4 = y[0]; // int
decltype(y[0]) d4; // int   -> d4에서 에러 : int가 아니고 int& 으로 선언된다. 
```

### decltype과 함수 호출식
```cpp
int foo(int a , double d) {}
foo(1, 3.1);
decltype(foo) d1; // 함수 타입 - int(int,double)
decltype(&foo) d2 ; // 함수 포인터 타입 - int(*)(int , double)
decltype( foo(1, 3.1) ) d3;  // 함수 반환타입 - int   진짜로 호출하지는 않는다. (unevaluated expression)
cout << typeid(d1).name() << endl;
```
- decltype(함수 이름) => 함수 타입
- decltype(&함수 이름) => 함수 포인터 타입

- g++의 경우 `실행파일 | c++filt -t` 하면 demangling해서 보여준다. 
    - const , volatile , reference가 출력되지 않음.


### using
```cpp
typedef int DWORD;
typedef void(*F)(int,int);

using DWORD = int;
using F = void(*)(int,int);
```
- 기존 타입의 별칭
- using은 type뿐 아니라 template의 별칭도 가능  (template alias)


# 5. C++ 변수의 특징 #2
## constexpr
```cpp
constexpr int c2=10;
c2=20; //error
```
- 컴파일 시간에 결정되는 상수 값
```cpp
int s1=10;
int arr2[s1]; // C99문법에는 배열의 크기로 변수도 사용가능

const int s2=10;
int arr3[s2];

const int s3 = s1;  // 10 이 아닌 변수로 초기화 (컴파일 시간에 크기를 알아야 한다.)
int arr4[s3];   // compile할때 s3를 모른다. error
```
- compile시간에 크기를 알수 있는 상수와 알수 없는 상수 (알수 없다는 것은 결국 못 바꾼다는 의미만 가진다.)

### const vs constexpr
```cpp
const int c1 = 10; // 컴파일 시간 상수. 배열 크기 사용가능
const int c2= n;  // 실행 시간 상수. 배열 크기 안됨.

constexpr int c3 = 10; // ok
constexpr int c4 = n;  // error
```
- constexpr은 template 인자로 사용될수 있다. 
- constexpr은 literal 만으로 초기화가 가능하다.  (변수로 초기화 안됨.)

## structured binding (C++17)
```cpp
struct Point { int x; int y; }
Point pt;
auto [x,y] = pt;

int arr[2] = {1,2};
auto [x,y] = arr;

int [x,y] = pt; // error  여기는 int 대신 auto만 가능하다.

const auto [x,y] = pt;  // ok
int x=10; // error  (x가 위에 변수로 선언되어져있으므로 )
```

## string
- <string>
- std::string 


# 6. C++ 함수의 특징 #1
## default parameter
```cpp
void setAlarm(int h , int m=0, int s=0){ }
```
- 미리 지정된 인자값 사용
- 주의 사항 
    - 마지막 인자부터 차례대로 디폴트
    - 함수의 선언부에만 default값 표시

## function overloading
- 동일한 이름의 함수를 2개 이상 만들수 있다. 단 , 인자의 개수나 인자의 타입이 달라야 한다.
- 인자의 개수가 달라도 디폴트 밧이 있는 경우는 주의해야 한다.
- 반환 타입만 다른 경우는 오버로딩 할수 없다.
```cpp
void v5(int n){}
void f5(char* s){}
f5(0); // f5(int);
f5(nullptr);   // f5(char*) C++11
```
- 정수 타입과 포인터 타입에 대한 오버로딩은 사용하지 않는 것이 좋다. 

## function template
```cpp
template <typename T>
T square(T a){ return a*a; }

square<int>(3);
square<double>(3.3);
```
- type deduction (타입 추론/연역)  square(3);  square<int>(3);으로 compiler가 추론

```cpp
template <typename T>
struct Point {
    T x;
    T y;
}
```
- 구조체도 template가능하다. 
- C++ 17부터는 생성자가 있으면 "템플릿 파라미터 전달을 생략" 할수 있다.

## inline function
- inline을 표기한 함수
- "-fno-inline" , "-finline-small-functions" , "-findirect-inlining" 등 option이 존재
- 요즘은 inline 치환보다는 linkage의 의미가 더 커지고 있다. (중급 이상)


# 7. 함수의 특징 #2
## delete function
```cpp
void foo(int) = delete;  // 함수 삭제
```
- 삭제된 함수를 호출하면 "컴파일 시간에 오류"가 발생
- delete function은 언제 어떻게 활용 할까?

- CPP에서도 double 은 암시적으로 int로 변환이 된다. 
```cpp
int gcd(int a , int b) { return 1; }
gcd (2,10); // ok
gcd(2.2 , 3.3); // ok : 암시적으로 int로 형변환된다.

// compile time에 double을 에러로 만들고 싶다면
double gcd(double a , double b) = delete; 
```

1. 암시적 변환에 의해 의도하지 않은 함수를 호출되는 것을 막기 위해서
1. 템플릿이 특정 타입의 함수를 생성하지 못하게 하기 위해서
1. **컴파일러가 자동으로 생성하는 멤버함수를 사용하지 못하게 (생성하지 못하게) 하기 위해** <- 가장 널리 사용
```cpp
template <typename T>
T square(T a){ return a*a; }

char square(char) = delete;

square(3);
square('a');  // error
```

## suffix return type (후위 반환 타입)
```cpp
auto square(int a) -> int
{
    return a*a;
}
```
1. 새로운 표기법: 이름 앞에 auto 뒤에 "-> 반환타입"
1. trailing return type 또는 suffix return type
1. C++11부터 지원
1. **람다 표현식이나 함수 템플릿을 만들때 주로 사용**

```cpp
template <typename T>
T add(T a , T b){
    return a+b;
}

add(1, 2.1);  // 2개가 다른 타입이어 error
```

```cpp
template <typename T1, typename T2>
decltype(a+b) add(T1 a , T2 b){
    return a+b;
}

add(1, 2.1);  // compiler가 int , double로 판단하나 error가 나온다. 
        // a was not declared in this scope  : 이때 return 값을 선언부보다 뒤로 가면 해결됨.
```

```cpp
template <typename T1, typename T2>
auto add(T1 a , T2 b) -> decltype(a+b)
{
    return a+b;
}

add(1, 2.1);  // a was not declared in this scope  : 이때 return 값을 선언부보다 뒤로 가면 해결됨.

// C++14 : 알아서 return 을 보고 return type 추론
auto add(T1 a , T2 b)
{
    return a+b;
}
```

## constexpr function
```cpp
constexpr int add(int a , int b)
{
    return a+b;
}

int n1 = add(1,1); // literal  -> 컴파일 시간에 함수를 실행 
int n2 = add(x,y); 
```
1. constexprt 상수 : 변수를 넣을수 없다. 
1. if constexpr : if constexpr9c == 10)
1. constexpr function
    - 함수 인자 값을 컴파일 시간에 결정할수 있으면 "컴파일 시간에 함수를 실행"
        - compile시간에 뭔가를 하는 것을 meta programming
    - **함수의 인자 값을 컴파일 시간에 결정할수 없으면 "실행시간에 함수를 실행"**

```cpp
template <typename T , int N>
struct Buffer {
    T data[N];
};

constexpr int add(int a , int b)
{
    return a+b;
}

Buffer<int , 1024> b1;
Buffer<int , x> b2; // error
Buffer<int , add(1,2)> b3; // ok
Buffer<int , add(x,2)> b4; // error
```
- template parameter
    - 템플릿 인자로 타입 뿐 아니라 정수형 상수도 사용 가능
    - 모든 템플릿 인자는 컴파일 시간에 결정되어야 한다. 

- constexpr의 제약 사항
    - return 문장이 한번만 나와야 한다.  (C++11)
        - C++14에서는 이 제약조건은 없어졌다.
    - C++14 : 파일 오픈하거나 동적으로 메모리 할당 할수 없다. 가상함수가 될수 없다. 
    
## Lambda Expression
- 일반적인 함수
    - global space에 만들어 놓고 필요할때 "함수의 이름을 사용해서 호출"한다.
```cpp
// 람다 표현식
[](int a){
    std::cout << "foo:" << a << std::endl;
} (10);   // 이게 호출
```
- 람다 표현식
    - 코드 안에서 이름이 없는 함수를 만들어서 사용
    - 익명의 함수 , 함수 리터럴
    - 함수 반환 타입과 이름을 제거 하고 []을 표기
- 람다 표현식의 모양
    - []
        - lambda introducer 라고 불림.
```cpp
int n2 = [](int a,int b) { return a+b; } (1,2);

int x[10] = {1,2,3,4,5,6,7,8,9,10};
std::sort(x,x+10);   // 시작, 마지막 요소의 다음 주소

std::sort(x,x+10, [](int a,int b){ return a>b; } );    // 크기 비교 함수를 넣어 순서를 거꾸로
```


# 8. range-for  : 제어문과 반복문
## range-for
```cpp
int x[10] = {1,2,3,4,5,6,7,8,9,10};
for(int i=0;i<10;i++){
}

// C++11부터 지원하는 새로운 모양의 반복문
for(int n: x){
}

// auto와 같이 사용 가능
for(auto n : x){
}

// 사용자가 만든 list도 사용 가능
```

## if init , switch init (C++17)
```cpp
if(ret == -1){}

if (int ret = foo() ; ret == -1)  // if 문에 초기값을 먼저 수행할수 있다. if init
{
}

switch(int n = foo() ; n)
{
    case 10:break;
}
```

## if constexpr (C++17)
- static if 라고도 불림
```cpp
if constexpr (n == 0)     // 컴파일 시간에 조건식을 조사  : error
{
}

if constexpr(sizeof(n) == 0) // ok
{
}
```
- template을 만들때 주로 사용
```cpp
template <typename T>
void foo(T a)
{
    if(0)
        *a =0;
}

foo(&n); // T : int*  ok
foo(n);  // T : int error
```
    - if(0)이라도 실행시간에 조사하므로 에러
    - if constexpr(0) 이라고 하면 아래의 *a=0의 코드도 생성하지 않으므로 문제가 안된다.




# 9. reference
## reference 개념
1. 변수
    - 메모리의 특정 위치를 가리키는 이름
    - 코드 안에서 해당 메모리에 접근하기 위해서 사용
1. 레퍼런스 변수
    - 기존 변수에 또 다른 이름(alias)를 부여

### 함수 인자 전달 방식
- call by value
- call by reference

### pointer 와 reference의 차이
```cpp
int n=10;
int* p1 = &n;
int& r1 = n;  // n을 가리키는 r1이라는 새로운 이름

int* p2 = 0;  // null pointer 가능
int& r2;    // error : 초기값이 꼭 있어야 한다.

*p1 = 20;
r1 = 20;  // 자동 * 연산되는 포인터

if(p1 != 0){}
if(r1 != 0){}   // r1은 if문으로 조사할 필요 없다. r1은 0일수가 없다.

```
- 유사한점 : 기존 변수를 가리킨다.
- 차이점
    - 포인터
        - 변수 주소로 초기화 : 초기값 생략 가능
        - * 연산자 사용
        - NULL값 가질수 있다.
        - 포인터 변수의 주소
    - reference
        - 변수 이름으로 초기화 : **초기값이 반드시 필요**
        - *연산자 필요없다.
        - NULL값 가질수 없다.
        - 기존변수와 동일 주소

## const reference
- const reference 인자 : const Date& d
    1. call by value 의 특징
        - 복사본 생성
        - 복사본에 대한 오버헤드
    1. 인자의 값을 변경하지 못하는 함수를 만들려면 
        - call by value보다는 const reference를 사용
    1. const reference의 장점
        - 인자에 대한 복사본을 만들지 않는다.
        - 복사 생성자와 소멸자를 호출하지 않는다.
- 함수 인자 전달 방법 정리 (인자 값을 변경하기 원하지 않을때)
    - 표준 타입들은  call by value로 받을때 훨씬 최적화가 잘 된다. 
    - **user define type일때는 const reference가 좋다.**

## retuen by reference
```cpp
void f1(Point pt){}
void f2(Point& pt){}  // 복사본 생성하지 않음.

Point pt = {0,0};

Point foo()  // 값 타입 반환   return by value
{
    return pt;   // 새로 복사하여 리턴용 임시 객체를 return
}

Point& foo()     // 진짜 pt를 반환한다.
{
    return pt;
}
```

```cpp
int x=10;
void f1(){ return x;}
void& f2(){ return x;}

f1() = 20;  // 10 = 20
f2() = 20;  // x = 20 ok

int& f3()
{
    int n=10;
    return n;
}

```
- 함수가 값을 반환하면 , 함수 호출식이 lvalue가 될수 없다.
- **함수가 참조를 반환하면 , 함수 호출식이 lvalue가 될수 있다.**
    - f3()과 같이 지역변수를 참조로 반환하면 안됨

## rvalue reference
```cpp
int v1=0,v2=0;

v1 = 10; // ok   오른쪽에 올수 있는것은 10:rvalue
10 =  v1; // error   v1: lvalue  (lvalue는 왼쪽 오른쪽 모두 올수 있다.)
v2 = v1;

// & lvalue reference
int& r1 = v1;  // ok
int& r2 = 10;  // error

const int& r3 = v1;  // ok
const int& r4 = 10;  // ok

// && rvalue reference : rvalue만 가리킨다. 
int&& r5 = v1;  // error 
int&& r6 = 10;  // ok
```
- && 을 rvalue reference라고 부른다. 
    - move semantics
    - perfect forwarding에서 사용

- lvaule reference : lvalue 만 가리킬수 있다.
- const lvalue reference : lvalue , rvalue를 모두 가리킬수 있다.
- rvalue reference : rvalue만 가리킬수 있다. (C++11 추가)


# 10. C++ explicit casting
## C++ explicit casting
```cpp
int* p1 = malloc(sizeof(int)*10);
    // C : ok
    // C++ : error

int* p1 = (int*) malloc(sizeof(int)*10);  
int* p1 = static_cast<int*>(malloc(sizeof(int)*10));  
```

## C언어 방식 캐스팅의 단점
```cpp
int n = 0;
double* p1 = &n;  // error

double*p2 = (double*) &n;       // ok
*p2 = 3.4;      // 위험 . n은 4 byte인데 , p2도 4 byte를 가리키는 pointer , 그러나 3.4는 8 byte

const int c = 10;
int* p3 = &c;  // error : 상수의 주소를 int에 담을수 없다. 

int* p3 = (int*)&c; // ok
*p3 = 20;
cout << c << endl;   // 10? 20?   => g++에서는 10으로 나옴.
```
- 논리적으로 위험한 캐스팅도 아무런 경고 없이 허용한다.
    - 개발자의 의도인지 실수 인지를 명확하게 구별할 수 없다.
- C++언어의 해결책
    - 용도 별로 다른 캐스팅 방법을 사용하자.
    - 용도 별로 4개의 캐스팀 연산자를 제공한다.

## C++ casting 연산자
1. static cast
    - 가장 기본적인 캐스팅 연산자
    - 정수 / 실수 사이의 변환 , 열거형과 정수 사이의 변환
    - void * -> 다른 타입 * 변환
    - 배열 -> 포인터
    - 함수 -> 함수 포인터 등
    - 상수성을 제거하거나 서로 다른 타입의 포인터끼리의 변환은 허용되지 않는다. (단 , 상속관계는 허용)
```cpp
void foo(int){}
void foo(double){}
const int c =10;
double d = 3.4;

int n = static_cast<int>(d);
int* p1 = static_cast<int*>(malloc(100));
auto p2 = static_cast<void(*)(int)>(&foo);  // 함수 이름이 여러개 overloading될때
int* p3 = static_cast<int*>(&d);  // error
int* p4 = static_cast<int*>(&c);  // error : 상수 제거 에러
```
1. reinterpret_cast
    - 서로 다른 포인터 타입끼리의 변환
    - 정수와 포인터 사이의 변환
```cpp
int n = 10;
double*  p1 = reinterpret_cast<double*>(&n);  // 다시 해석 casting
// 역참조 하면 안됨

// int* p2 = 10;  // 강제로 주소를 주고 싶을때
int* p2 = reinterpret_cast<int*>(10);
double d = reinterpret_cast<double>(n);   // error : reinterpret_cast 용도가 아님
```
1. const_cast
    - 포인터와 참조형의 상수성과 volatile 속성을 제거하는데 사용
```cpp
const int c = 10;
volitile int v = 20;

int n = c;

int* p1 = const_cast<int*>(&c);
int* p2 = const_cast<int*>(&v);

double* p3 = const_cast<double*>(&c);  // error : const만 없애는 것이지 type변환이 되는것은 아님
```
1. dynamic_cast
    - 안전한 다운 캐스팅(기반 클래스 포인터를 안전하게 파생 클래스 타입의 포인터로 캐스팅 할때 사용)
    - 실행 시간 캐스팅 - 실행 시간 오버헤드 존재

- 변환 방법 : 무조건 static으로 바꾸고 , 에러 나고 꼭 사용하기 원하면 다른 cast를 사용
- const int 를 char * 으로 변환하는 방법 2가지
```cpp
const int c = 10;
char *p = reinterpret_cast<char*> (
        const_cast<int*>(&c)  );

char *p = const_cast<char*> (
        reinterpret_cast<const char*>(&c)  );

char* p3 = (char*) &c;   // C type
```


# 11. new / delete / nullptr
## C++ 동적 메모리 할당
- C : malloc / free
- C++ : new / delete
```cpp
int* p2 = new int;  // 4 byte
delete p2;

int* p3 = new int[10];
delete[] p3;

int* p4 = new int[10][2];  // 80
delete[] p4;
```

- new는 생성자를 호출한다.

## nullptr
```cpp
int* p1 = 0;
int* p2 = nullptr;
```
- 새로운 키워드
- pointer literal

1. 리터럴
    - 소스 코드 내에서 사용되는 고정된 값
    - 변수 초기화에서 구문 등에서 많이 사용된다.
    - 모든 리터럴은 데이터 타입이 있다.
        - 0 : 정수형 , int
        - 0.0 : 실수형 , double
        - false : boolean , bool
        - nullptr : pointer , ? (std::nullptr_t)

## nullptr과 코드의 가독성
```cpp
int* foo(){ return 0; }

auto ret = foo();
// if(ret == 0)
if(ret == nullptr)
{
    // ...
}
```

## nullptr과 데이터 타입
- nullptr  // std::nullptr_t
    - std::nullptr_t는 모든 타입의 포인터로 암시적 변환된다.
    - **int 타입으로 변환될수 없다.**
```cpp
int* p1 = nullptr;
char* p2 = nullptr;
void(*f)() = nullptr;

int n = nullptr;   // error

bool b2 = nullptr; // error : 복사 초기화
bool b2(nullptr);  // ok
bool b3{nullptr};  // ok  직접 초기화
bool b4 = {nullptr}; // error
```

## NULL 과 nullptr의 차이
```cpp
void foo(int n){}
void foo(void* p){}
void goo(char* n){}

foo(0); // int
foo( (void*)0 ); // void*
#ifdef __cplusplus
    #define NULL 0
#else 
    #define NULL (void*)0
#endif
foo(NULL);  // int

goo(NULL);  // ok
```
- C : void* -> 다른 타입의 * 로 암시적 형변환 허용
- C++ : void* -> 암시적 형변환 안됨.
- 일반적으로 NULL은 일반 정수 리터럴 0 으로 해석

