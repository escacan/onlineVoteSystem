#include "class.h"

using namespace std;

bool timeSetting = false;

//그룹관리
string group_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();
	int sessionType = getCurrentSessionType();

	while (end_input != 1) {
		sessionName = getCurrentSessionName();
		sessionType = getCurrentSessionType();

		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "그룹관리" << endl;
		cout << "5.1. 전체그룹 조회\n";
		cout << "5.2. 그룹 가입\n";
		cout << "5.3. 그룹 생성\n";
		cout << "5.4. 가입그룹 조회\n";
		cout << "5.5. 그룹 탈퇴\n";
		cout << "0. 메인 메뉴로 돌아가기\n";
		cout << "* 입력선택 : ";

		cin >> input;

		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 :  ";
			cin >> input;
		}

		switch (input) {
		case 1:
			listGroupUI::startInterface();
			listGroupUI::showGroupList();
			break;

		case 2:
			if (sessionType != 1) {
				cout << endl << "!ERROR : 현재 Session에서는 그룹 가입이 불가합니다." << endl;
				break;
			}
			joinGroupUI::startInterface();
			joinGroupUI::selectGroup();

			break;

		case 3:
			if (sessionType != 1) {
				cout << endl << "!ERROR : 현재 Session에서는 그룹 생성이 불가합니다." << endl;
				break;
			}
			createGroupUI::startInterface();
			createGroupUI::inputNewname();
			break;

		case 4:
			if (sessionType == 2 || sessionType == 3) {
				listJoinedGroupUI::startInterface();
				listJoinedGroupUI::getJoinedGroup();
				break; // joinedGroupUI로 변경할 것.
			}
			else {
				cout << endl << "!ERROR : 가입한 그룹이 없습니다." << endl;
				break;
			}
		case 5:
			if (sessionType == 2) { //그룹가입회원만 탈퇴가능
				groupWithdrawUI::startInterface();
				groupWithdrawUI::withdraw();
				break; // joinedGroupUI로 변경할 것.
			}
			else {
				cout << endl << "!ERROR : 현재 Session에서는 그룹 탈퇴가 불가능합니다." << endl;
				break;
			}
		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//로그인 로그아웃
string login_logout_ui() {
	int input;
	string choice;
	int end_input = 0;
	string sessionName = getCurrentSessionName();

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "Login / Logout" << endl;
		cout << "1.1. Login\n";
		cout << "1.2.Logout\n";
		cout << "0. 메인 메뉴로 돌아가기\n";
		cout << "* 입력선택 : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}

		switch (input) {
		case 1:
			loginUI::startInterface();
			loginUI::inputValue();
			end_input = 1;
			break;

		case 2:
			logoutUI::startInterface();
			end_input = logoutUI::logout();
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//Session 선택/ 변경
string session_ui() {
	int input;
	string choice;
	int end_input = 0;
	string sessionName = getCurrentSessionName();

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "Session 선택/변경" << endl;
		cout << "7.1.Session 선택/변경\n";
		cout << "0. 메인 메뉴로 돌아가기\n";
		cout << "* 입력선택 : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}

		switch (input) {
		case 1:
			sessionUI::startInterface();
			sessionUI::selectSession();
			end_input = 1;
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//회원 관리      0617 1347 수정.
string member_ui() {
	int input;
	int end_input = 0;

	while (end_input != 1) {
		string sessionName = getCurrentSessionName(); // 0617 수정
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "회원가입/탈퇴" << endl;
		cout << "1. 회원가입\n2. 회원탈퇴\n";
		cout << "0. 메인 메뉴로 돌아가기\n* 입력선택 : ";

		cin >> input;

		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}
		switch (input) {
		case 1:
			joinMemberUI::startInterface();
			joinMemberUI::addMember();
			break;

		case 2:
			memberWithdrawUI::startInterface();
			memberWithdrawUI::requestWithdraw();
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state가져오기로 수정
}

//투표제안
string vote_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // 수정 필요

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "3. 투표제안" << endl;
		cout << "3.1. 투표생성\n";
		cout << "0. 메인 메뉴로 돌아가기\n* 입력선택 : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}
		switch (input) {
		case 1:
			suggestNewVoteUI::startInterface();
			suggestNewVoteUI::suggestNewVote();
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state가져오기로 수정
}

//투표관리
string vote_manage_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // 수정 필요

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "4. 투표관리" << endl;
		cout << "4.1. 현재 진행중인 투표리스트\n";
		cout << "4.2. 투표\n";
		cout << "4.3.향후 진행 예정인 투표 리스트\n";
		cout << "4.4.종료된 투표리스트\n";
		cout << "0. 메인 메뉴로 돌아가기\n* 입력선택 : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}
		switch (input) {
		case 1:
			ongoingVoteShowUI::startInterface();
			ongoingVoteShowUI::selectProgressingVote();
			break;

		case 2:
			toVoteUI::startInterface();
			toVoteUI::toVote();
			break;

		case 3:
			scheduledVoteShowUI::startInterface();
			scheduledVoteShowUI::selectScheduledVote();
			break;

		case 4:
			endedVoteShowUI::startInterface();
			endedVoteShowUI::selectEndedVote();
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state가져오기로 수정
}


string timeNow_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // 수정 필요

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ 현재 Session : " << sessionName << endl;
		cout << endl << "현재시간 설정" << endl;
		cout << "6.1. 현재시간 설정\n";
		cout << "0. 메인 메뉴로 돌아가기\n* 입력선택 : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}
		switch (input) {
		case 1:
			timeNowUI::startInterface();
			timeSetting = timeNowUI::inputDate();
			break;

		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : 올바른 번호를 입력해주세요" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state가져오기로 수정
}


int main() {
	int input;
	int end_input = 0; // 사용자 입력
	bool currentState = 0; // 1은 로그인 상태.
	string sessionName = "Guest";
	int sessionType = 0;

	while (end_input != 1) {
		sessionType = getCurrentSessionType();
		sessionName = getCurrentSessionName();
		cout << "온라인 투표 시스템\n";
		cout << "\n\n";
		cout << "현재 Session : " << sessionName << "\n";

		cout << "1. 회원가입/탈퇴\n";
		cout << "2. 로그인/로그아웃\n";
		cout << "3. 투표제안\n";
		cout << "4. 투표관리\n";
		cout << "5. 그룹관리\n";
		cout << "6. 현재시간 설정\n";
		cout << "7. Session 변경/선택\n";
		cout << "8. 종료\n";
		cout << "*입력 선택 : ";
		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*입력 선택 : ";
			cin >> input;
		}
		switch (input) {
		case 1:
			sessionName = member_ui();
			break;
		case 2:
			sessionName = login_logout_ui();
			break;
		case 3:
			if (sessionType == 2 || sessionType == 3) {
				if (timeSetting) {
					sessionName = vote_ui();
					break;
				}
				else {
					cout << endl << "! ERROR : 현재 시간을 설정해야 합니다." << endl;
					break;
				}
			}
			else {
				cout << endl << "! ERROR : 투표 권한이 없습니다." << endl;
				break;
			}
		case 4:
			if (sessionType == 0 || sessionType == 1) {
				cout << endl << "! ERROR : 접근 권한이 없습니다." << endl;
				break;
			}
			else {
				sessionName = vote_manage_ui();
				break;
			}
		case 5:
			sessionName = group_ui();
			break;
		case 6:
			if (sessionType == 0) {
				cout << endl << "! ERROR : 시간 설정 권한이 없습니다." << endl;
				break;
			}
			else {
				sessionName = timeNow_ui();
				break;
			}
		case 7:
			sessionName = session_ui();
			break;
		case 8:
			end_input = 1;
			break;
		default:
			cout << endl << "! ERROR : 올바른 번호를 입력해주세요" << endl;
			break;            //글자 입력시 무한루프
		}
	}
	return 0;
}