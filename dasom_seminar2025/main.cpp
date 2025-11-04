//주제는 할일 관리 앱
//상태 관리, 그래그 앤 드롭, 로컬 스토리지 활용
//프로젝트별 분류, 데드라인 알림, 습관 추적 등
//윈도우 UI까지 활용하고 싶긴 함(일정 창 띄우기)

//일정 기입(월, 일 입력하면 원하는 일정 추가(시간, 제목, 본문, 장소, 반복, 분류 등)
//일정 제거(월, 일, 번호 입력하면 원하는 일정 지우기)
//일정 보기(원하는 일, 주일, 달 등, 혹은 시간별로)
//일정 검색

#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>

class Schedule {
	int year;
	int month;
	int day;
public:
	Schedule(int _year, int _month, int _day) {
		year = _year; month = _month; day = _day;
	}
	
};

void view() {
	cout << "열람하고 싶은 날을 적어주세요 (년도 월 일) : ";
	cin >> year >> month >> day;
	cout << endl;

}
void add() {
	string schedule;
	cout << "추가하고 싶은 날을 적어주세요 (년도 월 일) : ";
	cin >> year >> month >> day;
	Schedule 
	cout << "일정 제목을 기입해주세요 : ";
	cin >> schedule;

}
void del() {

}
void search() {

}


int main() {
	int number;
	while (1) {
		cout << "원하는 서비스를 선택하세요." << endl;
		cout << "1.일정 열람  2. 일정 추가  3. 일정 제거  4. 일정 검색  5. 중단" << endl;
		cin >> number;
		if (number == 1) view();
		else if (number == 2) add();
		else if (number == 3) del();
		else if (number == 4) search();
		else if (number == 5) break;
		else cout << "잘못된 번호를 선택하셨습니다. 다시 실행해주세요.";
		
	}
	cout << "캘린더를 종료합니다.";
	return 0;
}