
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // STL의 함수 객체
#include <ctime>
using namespace std;
int main()
{
	//std::srand(std::time(nullptr)); // use current time as seed for random generator
    //int random_variable = std::rand();
	vector<int> v;
	// 1. 난수를 10개 구해서 v에 넣으세요
	for(int i=0;i<10;i++){
		v.push_back(rand()); 
	}
	int cmd = 0;
    int p;
    int flag = 1;
	while (flag)
	{
        cout << endl;
        cout << "1 : print" << endl;
        cout << "2 : sort" << endl;
        cout << "3 : reverse sort" << endl;
        cout << "4 : delete element" << endl;
        cout << "5 : fill 0 in specific  element" << endl;
        cout << "6 : resize as 20" << endl;
        cout << "press the number:" << endl;
		cin >> cmd;

        switch(cmd){
		// 2. cmd가 1이면 v의 모든 내용을 화면에 출력해 주세요
            case 1:
		        for(auto n : v){ cout << n << endl; }
                break;
		// 3. cmd가 2이면 v를 오름 차순으로 정렬한 후 v의 내용을 화면 출력해 주세요
            case 2:
		        sort(begin(v),end(v));
                for(auto n : v){ cout << n << endl; }
                break;
		// 비교 정책으로 함수 객체를 사용해서 만들어 주세요
		// 4. cmd가 3이면 v를 내림 차순으로 정렬한 후 v의 내용을 화면 출력해 주세요
		// 비교 정책으로 람다 표현식을 사용해 주세요
            case 3:
                sort(begin(v),end(v),[](int a,int b){ return a>b; }  );
                for(auto n : v){ cout << n << endl; }
                break;
                // 5. cmd가 4이면 또 다른 숫자를 하나 입력 받으세요.
                // 해당 숫자가 vector에 있으면 제거한후 vector를 다시 출력해 주세요
            case 4:
                {
                    cout << endl << "delete number : " << endl;
                    cin >> p;
                    auto result = find(begin(v),end(v),p);
                    if(result != end(v)){
                        cout << "found " << p << endl;
                        v.erase(remove(v.begin(), v.end(), p), v.end());
                    } 
                    for(auto n : v){ cout << n << endl; }
                }
                break;
                // 6. cmd가 5이면 또 다른 숫자를 하나 입력 받으세요.
                // 해당 숫자를 찾아서 0으로 변경한후 vector를 다시 출력해 주세요
            case 5:
                cout << endl << "put number to fill zero : " << endl;
                cin >> p;
                {
                    auto result = find(begin(v),end(v),p);
                    if(result != end(v)){
                        *result = 0;
                    } 
                    for(auto n : v){ cout << n << endl; }
                }
                break;
		// 7. cmd가 6이면 v의 size를 20개로 늘린 후 v의 내용을 출력해 주세요
            case 6:
                v.resize(20);
                for(auto n : v){ cout << n << endl; }
                break;
            default:
                flag = 0;
                break;
        }
	}
}
