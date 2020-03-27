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
}
