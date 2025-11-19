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
#include<algorithm>
#include<iomanip>
using namespace std;

struct Todo {
	string time;
	string title;
	string body;
	string place;
	string repeat;
	string category;
};

class Day {
	int year, month, day;
	vector<Todo>items;   //Todo의 객체
public:
	Day(int y, int m, int d) : year(y),month(m),day(d){}
	
	// 같은 날인지 확인
	bool sameDate(int y, int m, int d) const {
		return year == y && month == m && day == d;
	}
	// 일정 추가, 시간을 쓰지 않을 때를 구분, 시간순으로 정렬
	void add(const Todo& t) {
		items.push_back(t);

		for (int i = 0; i < items.size() - 1; i++) {
			for (int j = i + 1; j < (int)items.size(); j++) {
				string t1 = items[i].time.empty() ? "99:99" : items[i].time;
				string t2 = items[j].time.empty() ? "99:99" : items[j].time;
				if (t1 > t2) swap(items[i], items[j]);
			}
		}
	}
	// items 벡터에서 해당하는 인덱스의 일정 삭제, 리턴값은 bool
	// 파라미터로 받은 번호가 1 이상, 크기 이하인지 확인
	bool removeIdx(int idx) {
		if (idx<1 || idx>(int)items.size()) return false;
		items.erase(items.begin() + (idx - 1));
		return true;
	}
	// 일정 출력
	void print() const {
		cout << "===== " << year << "년 " << month << "월 " << day << "일" << " =====\n";
		for (int i = 0; i < (int)items.size(); ++i) {
			const auto& t = items[i];
			if (t.time.empty()) cout << i + 1 << " )";
			else cout << i + 1 << ") [" << t.time << "]";
			cout << " " << t.title << " { " << t.category << " }\n";
			if (!t.place.empty())  cout << "   - 장소 : " << t.place << "\n";
			if (!t.repeat.empty()) cout << "   - 반복 : " << t.repeat << "\n";
			if (!t.body.empty())   cout << "   - 내용 : " << t.body << "\n";
		}
	}
	// 키워드 컴색. items에 있는 모든 제목과 본문,장소에서 키워드 find
	void searchkey(const string& key) const {
		for (const auto& t : items) {
			string blob = t.title + " " + t.body + " " + t.place;
			if (blob.find(key) != string::npos) {
				if (t.time.empty())
					cout << year << "년 " << month << "월 " << day << "일 " << t.title << " { " << t.category << " }\n";
				else
					cout << year << "년 " << month << "월 " << day << "일 " << " [" << t.time << "] " << t.title << " { " << t.category << " }\n";
			}
		}
	}
};


class Calendar {
	vector<Day> days;

	// 년,월,일을 파라미터로 입력하면 days 벡터에서 해당 날짜의 인덱스를 리턴
	// 왜냐하면 아래에서 일정을 찾을 때 이 함수를 통해 인덱스로 접근할것이기 때문
	int findDayIndex(int y, int m, int d) const {
		for (int i = 0; i < (int)days.size(); ++i)
			if (days[i].sameDate(y,m,d)) return i;
		return -1;
	} 

public:
	// 일정 추가
	void add() {
		int y, m, d;
		cout << "추가하고 싶은 날짜를 적어주세요 (년도 월 일) : ";
		cin >> y >> m >> d;
		cin.ignore();
		printMonth(y, m);
		Todo t;     // struct 객체 생성, 즉 일정 생성
		cout << "시간 (HH:MM, 없으면 엔터) : ";
		getline(cin, t.time);   // 띄어쓰기도 인식되게끔
		cout << "제목: ";    getline(cin, t.title);
		cout << "본문: ";    getline(cin, t.body);
		cout << "장소: ";    getline(cin, t.place);
		cout << "반복: ";    getline(cin, t.repeat);
		cout << "분류: ";    getline(cin, t.category);
		cout << endl;
	
		int idx = findDayIndex(y,m,d);  // days 벡터에서 해당 날짜(요소) 인덱스 찾기
		if (idx == -1) {
			days.emplace_back(y, m, d);  //함수 내에서 객체를 생성해 삽입 =push_back
			idx = (int)days.size() - 1;
		}
		days[idx].add(t);
		days[idx].print();
		cout << "\n\n";
	}
	// 일정 열람
	void view() {
		int y, m, d;
		cout << "열람할 날짜를 적어주세요 (년도 월 일) : ";
		cin >> y >> m >> d;
		cin.ignore();
		printMonth(y, m);
		cout << endl;
		int idx = findDayIndex(y, m, d);
		if (idx == -1)cout << "\n\n\n";   //일정이 없으면 빈 화면이 뜸
		else { days[idx].print(); cout << "\n\n"; }
	}
	// 일정 제거
	void del() {
		int y, m, d;
		cout << "삭제할 날짜를 적어주세요 (년도 월 일) : ";
		cin >> y >> m >> d;
		cin.ignore();
		cout << endl;
		int idx = findDayIndex(y, m, d);
		if (idx == -1) { cout << "삭제할 일정이 없습니다.\n\n"; return; }
		else {
			days[idx].print();
			cout << "\n삭제할 번호 : ";
			int k; cin >> k; cin.ignore();
			if (days[idx].removeIdx(k)) { days[idx].print(); cout << "\n\n"; }
			else cout << "번호가 올바르지 않습니다.\n\n";   // Day class 함수 사용
		}
	}
	//일정 검색
	void search()const {
		cout << "검색어 : ";
		string key; cin.ignore(); getline(cin, key);
		cout << "\n===== 검색결과 =====\n";
		bool result = false;
		for (const auto& d: days) {
			d.searchkey(key);   //일정 찾기, 존재하면 년월일 및 일정 내용 출력
		}
		cout << "\n\n";
	}

	// 달력모양 만들기
	bool isLeapYear(int year) {
		return year % 4 == 0 and year % 100 != 0 or year % 400 == 0;
	}
	int lastDay(int y, int m) {
		int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		month[1] = isLeapYear(y) ? 29 : 28;
		return month[m - 1];
	}
	int totalDay(int y, int m, int d) {
		int sum = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
		for (int i = 1; i < m; i++) 
			sum += lastDay(y, i);
		return sum + d;
	}
	int weekDay(int y, int m, int d) {
		return totalDay(y, m, d) % 7;
	}
	void printMonth(int y, int m) {
		cout << "===============================" << endl;
		cout << "         " << setw(4) << y << "년 " << m << "월" << endl;
		cout << "===============================" << endl;
		cout << "  일  월  화  수  목  금  토  " << endl;
		cout << "===============================" << endl;
		for (int i = 0; i < weekDay(y, m, 1); i++)
			cout << "    ";
		for (int i = 1; i <= lastDay(y, m); i++) {
			cout << " " << setw(2) << i << " ";
			if (weekDay(y, m, i) == 6) cout << "\n";
		}
		cout << "\n===============================" << endl;
	}


	void mainscreen() {
		int number;
		while (1) {
			cout << "원하는 서비스를 선택하세요." << endl;
			cout << "1.일정 열람  2. 일정 추가  3. 일정 제거  4. 일정 검색  5. 중단" << endl;
			cin >> number;
			cout << endl;
			if (number == 1) view();
			else if (number == 2) add();
			else if (number == 3) del();
			else if (number == 4) search();
			else if (number == 5) break;
			else cout << "잘못된 번호를 선택하셨습니다. 다시 실행해주세요.";

		}
		cout << "캘린더를 종료합니다.";
	}
};


int main() {
	Calendar cal;
	cal.mainscreen();
	return 0;
}