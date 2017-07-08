#include "class.h"
#pragma warning(disable: 4996) 

Member member(false, "Guest", "", "", "", "", "", 0);  // 현재 접속중인 멤버
Vote vote;
struct tm timeNow { 1, 1, 1, 1, 1, 1 };
struct tm voteStart{1,1,1};
struct tm voteEnd { 1, 1, 1 };
long nowDays; // 투표 시간과 비교
struct voteList *currentVoteList = { 0 };

list<Member> memberList;
list<Group> groupList;
list<Vote> voteList;

long total_days(int year, int month, int day);

// entity
Member::Member(bool logState, string newId, string newPwd, string newName, string newSsn, string newAddress, string newEmail, int memType) {
	loginState = logState;
	
	id = newId;
	pwd = newPwd;
	name = newName;
	ssn = newSsn;
	address = newAddress;
	email = newEmail;
	
	memberType = memType;

	joinedGroup = "";
}

// Function : bool Member::checkValue(string ID, string PW)
//
// Description :
//		이 함수는 로그인 상황에서 사용자가 입력한 ID와 PW가
//		등록된 회원 정보와 일치하는지 확인하는 함수이다.
//		list<T>::iterator를 사용하여 등록된 회원 정보와 입력된 정보를 비교한다.
//
// Parameters : 
//		string ID - 사용자가 입력한 아이디
//		string PW - 사용자가 입력한 비밀번호
//
// Return Value :
//		등록된 회원 정보와 일치하는 지 여부를 나타내는 bool값
//
// Created: 2017/6/17 11:11
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 14:00 
//	   what : 함수 이름 변경
//
bool Member::checkValue(string ID, string PW) {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).id == ID && (*position).pwd == PW) {
			member = *position;
			member.loginState = true;
			return true;
		}
		position++;
	}

	return false;
}

// Function : string Member::getMemberID()
//
// Description :
//		이 함수는 member_ID를 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :																
//
// Created: 2017/6/17 15:30
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
string Member::getMemberID() {
	return id;
}

// Function : string Member::getJoinedGroup()
//
// Description :
//		이 함수는 JoinedGroup을 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :				
//		string joinedGroup - 멤버가 가입한 그룹 이름
//
// Created : 2017/06/17 17:43
// Author : 홍민기
// mail : escandar@naver.com	
// 
string Member::getJoinedGroup() {
	return joinedGroup;
}

// Function : void Member::setJoinedGroup(string groupName)
//
// Description :
//		이 함수는 멤버의 가입그룹을 저장하는 함수이다..
//
// Parameters : string groupName - 가입한 그룹 이름
//
// Return Value :																
//
// Created : 2017/06/17 15:47
// Author : 홍민기
// mail : escandar@naver.com
// 
void Member::setJoinedGroup(string groupName) {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).id == getCurrentSessionName()) {
			(*position).joinedGroup = groupName;
			member.joinedGroup = groupName;
			return;
		}
		position++;
	}
}

// Function : void Member::setMemberType(int type)
//
// Description :
//		이 함수는 멤버의 타입을 저장하는 함수이다..
//
// Parameters : int type - 변경할 멤버의 타입
//
// Return Value :																
//
// Created : 2017/06/17 15:47
// Author : 홍민기
// mail : escandar@naver.com
// 
void Member::setMemberType(int type) {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).id == getCurrentSessionName()) {
			(*position).memberType = type;
			member.memberType = type;
			return;
		}
		position++;
	}
}

// Function : int Member::getMemberType()
//
// Description :
//		이 함수는 member_Type를 반환하는 함수이다.
//
// Parameters : 
//		
// Return Value :																
//
// Created: 2017/6/17 15:45
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
int Member::getMemberType() {
	return memberType;
}

// Function : string Member::getMemberLogin()
//
// Description :
//		이 함수는 member_Login를 반환하는 함수이다.
//
// Parameters : 
//		
// Return Value :																
//
// Created: 2017/6/17 15:55
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
bool Member::getMemberLogin() {
	return loginState;
}	


// Function : void Member::clear()
//
// Description :
//		이 함수는 Member 객체의 변수들을 리셋한다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 16:00
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 14:53 
//	   what : id에 Guest를 저장
//
void Member::clear() {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).id == getCurrentSessionName()) {
			(*position).loginState = false;
			id = "Guest";
			pwd = "";
			memberType = 0;
			loginState = false;
			break;
		}
		position++;
	}
}


// Function : void Member::logOut()
//
// Description :
//		이 함수는 로그아웃 상황에서 사용자의 로그아웃을 수행하는 함수이다.
//		로그인 된 사용자의 정보를 임시로 갖고 있는 객체들을 리셋한다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 16:15
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
void Member::logOut() {
	member.clear();
}


// Function : void Member::deleteMember(string ID, string PW)
//
// Description :
//		이 함수는 회원탈퇴 상황에서 회원의 정보를 실제 삭제하는 함수이다.
//		list<T>::iterator를 사용하여 사용자가 입력한 회원정보를 검색하고 삭제한다.
//
// Parameters : 
//		string ID - 사용자가 삭제하기 원하는 아이디
//		string PW - 사용자가 삭제하기 원하는 아이디의 비밀번호
//						
// Return Value : 														
//
// Created : 2017/06/17 14:11
// Author : 권용재
// mail : wkqlwja2@gmail.com
// 
void Member::deleteMember(string ID, string PW) {
	bool completeDelete = false;

	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).id == ID && (*position).pwd == PW) {
			memberList.erase(position++);
			completeDelete = true;
			break;
		}
		else {
			++position;
		}
	}

	if (completeDelete == false) cout << endl << "! ERROR : 탈퇴가 불가능 합니다." << endl;
	else {
		member.clear();
		cout << endl << "* 회원탈퇴가 완료되었습니다." << endl;
	}
	if (ID == member.getMemberID()) {
		cout << "* 로그아웃 되었습니다\n";			
		member.id = "Guest";
		member.pwd = "";
		member.memberType = 0;
		member.loginState = false;
	}
}

// Function : string Group::getGroup()
//
// Description :
//		이 함수는 groupName을 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :																
//
// Created : 2017/06/17 14:28
// Author : 홍민기
// mail : escandar@naver.com
// 
Group::Group(string newGroupname) {
	groupName = newGroupname;
	groupCreator = getCurrentSessionName();
}

// Function : string Group::getGroup()
//
// Description :
//		이 함수는 groupName을 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :																
//
// Created : 2017/06/17 14:28
// Author : 홍민기
// mail : escandar@naver.com
// 
string Group::getGroup() {
	return groupName;
}

Vote::Vote(string newSubject, int newListNum, string *everyList, struct tm newStartTime, struct tm newEndTime) {
	long startDays, endDays;
	subject = newSubject;
	listNum = newListNum;

	groupName = member.getJoinedGroup();

	for (int i = 0; i < listNum; i++) {
		totalList[i].listContents = everyList[i];
		totalList[i].count = 0;
	}
	starttime = newStartTime;
	endtime = newEndTime;

	startDays = total_days(starttime.tm_year, starttime.tm_mon, starttime.tm_mday);
	endDays = total_days(endtime.tm_year, endtime.tm_mon, endtime.tm_mday);

	if (startDays > nowDays) {
		voteState = 0;
	}
	else if (nowDays > endDays) {
		voteState = 2;
	}
	else {
		voteState = 1;
	}
}

// Function : string Vote::getVoteSubject()
//
// Description :
//		이 함수는 vote subject를 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			string voteSubject - vote의 subject
//
// Created : 2017/06/17 21:37
// Author : 김현재
// mail : cleverhj94@naver.com 
// 
string Vote::getVoteSubject() {
	return subject;
}

// Function : int Vote::getVoteState()
//
// Description :
//		이 함수는 vote state를 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			int voteState - vote의 state
//
// Created : 2017/06/17 23:22
// Author : 황우현
// mail :dngus8549@naver.com
// 
int Vote::getVoteState() {
	return voteState;
}

// Function : void Vote::setVoteState(int newState)
//
// Description :
//		이 함수는 Vote의 state를 갱신하는 함수이다.
//
// Parameters : int newState - 갱신할 Vote의 State
//
// Return Value :														
//			
//
// Created : 2017/06/20 1:22
// Author : 황우현
// mail : dngus8549@naver.com
// 
void Vote::setVoteState(int newState) {
	voteState = newState;
}

// Function : int Vote::getListNum()
//
// Description :
//		이 함수는 listNum을 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			int listNum - vote의 listNum
//
// Created : 2017/06/19 23:22
// Author : 황우현
// mail : dngus8549@naver.com
// 
int Vote::getListNum() {
	return listNum;
}

// Function : void Vote::getVoteList()
//
// Description :
//		이 함수는 vote의 항목인 vote list를 불러오는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/19 23:07
// Author : 황우현
// mail : dngus8549@naver.com
// 
void Vote::getVoteList() {
	currentVoteList= totalList;
}

// Function : void Vote::setListCount(int selectedList)
//
// Description :
//		이 함수는 항목의 count에 1을 더하는 함수이다.
//
// Parameters : int selectedList - count에 1을 더해줄 할 항목의 번호
//
// Return Value :														
//			
//
// Created : 2017/06/20 00:24
// Author : 황우현
// mail : dngus8549@naver.com
// 
void Vote::setListCount(int selectedList) {
	totalList[selectedList - 1].count++;
}


// Function : void Vote::getTime()
//
// Description :
//		이 함수는 vote의 시작시간과 종료시간을 불러오는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/19 23:49
// Author : 황우현
// mail : dngus8549@naver.com
// 
void Vote::getTime() {
	voteStart = starttime;
	voteEnd = endtime;
}

// Function : void Vote::checkOverlapVote(string selectedVote)
//
// Description :
//		이 함수는 투표 상황에서 사용자가 입력한 투표 주제가
//		이미 투표한 주제인지 체크하는 함수이다.
//		list<T>::iterator를 사용하여 투표 참여자 리스트와 현재 Session의 ID를 비교한다.
//
// Parameters : 
//		string selectedVote - 사용자가 입력한 투표 주제
//
// Return Value :
//		
//
// Created : 2017/06/19 22:51
// Author : 황우현
// mail : dngus8549@naver.com
//
// Revsions : 
//
void Vote::checkOverlapVote(string selectedVote) {
	int listNum = 0, i= 0;
	bool alreadyVoted = false;
	list<string>::iterator position1;
	position1 = vote.votedMemberList.begin();

	string currentSessionId = getCurrentSessionName();
	char selectedList[10];// 선택한 항목

	while (position1 != votedMemberList.end()) {
		if (*position1 == currentSessionId) {
			alreadyVoted = true;
			break;
		}
		position1++;
	}

	if (alreadyVoted) {
		cout << endl << "! ERROR : 이미 투표한 주제입니다." << endl;
		return;
	}
	else {
		vote.getVoteList();
		listNum = vote.getListNum();
		cout << "투표 항목\n";
		for(i= 0; i< listNum; i++){
			cout << i+1 << ". " << currentVoteList[i].listContents << " : " << currentVoteList[i].count << "표\n";
		}
		cout << "투표할 항목 번호 : ";
		cin >> selectedList;
		if (atoi(selectedList) > listNum || atoi(selectedList) == 0 ) {
			cout << endl << "! ERROR : 잘못된 입력입니다." << endl;
		}
		else {
			//리스트에 접근해서 실제로 데이터를 수정하는 부분
			list<Vote>::iterator position2;
			position2 = voteList.begin();

			while (position2 != voteList.end()) {
				if ((*position2).getVoteSubject() == vote.getVoteSubject()) {
					break;
				}
				position2++;
			}

			(*position2).setListCount(atoi(selectedList));		// setCount 함수 추가 필요
			(*position2).votedMemberList.push_back(currentSessionId);   // 투표 참여자 리스트에 추가하는 코드
			cout << "투표 되었습니다.\n";
			cout << "투표 결과\n";
			
			(*position2).getVoteList();
			listNum = (*position2).getListNum();

			for (i = 0; i< listNum; i++) {
				cout << i + 1 << ". " << currentVoteList[i].listContents << " : " << currentVoteList[i].count << "표\n";
			}
		}
	}
}

// Function : string Vote::getVoteGroupName()
//
// Description :
//		이 함수는 vote가 속한 그룹이름  groupName을 반환하는 함수이다.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/20 02:04
// Author : 황우현
// mail : dngus8549@naver.com
// 
string Vote::getVoteGroupName() {
	return groupName;
}

// control
// Function : void MemberManage::AddMember(bool newState, string newId, string newPw, string newnName, string newSsn, string newAddress, string newEmail)
//
// Description :
//		이 함수는 회원가입 상황에서 사용자가 선택한 타입에 맞는 생성자를 호출하는 control 클래스의 함수이다.
//		UI클래스로 부터 사용자가 입력한 값들을 전달 받아 사용자가 선택한 회원 종류의 클래스 생성자를 호출한다.
//		만약 입력한 ID가 이미 등록된 사용자라면 오류메시지와 함께 리턴된다.
//
// Parameters : 
//		string ID - 사용자가 입력한 아이디
//		string PW - 사용자가 입력한 비밀번호
//		int choice - 사용자가 선택한 회원 종류를 나타내는 변수
//		string name - 사용자가 입력한 이름
//		string birth - 사용자가 입력한 생년월일
//		string address - 사용자가 입력한 주소
//		string email - 사용자가 입력한 이메일
//		string number - 사용자가 입력한 사업자번호
//		string type - 사용자가 입력한 음식점 타입
//		string time - 사용자가 입력한 영업시간
//		string phone - 사용자가 입력한 전화번호
//
// Return Value :
//
void MemberManage::addMember(bool newState, string newId, string newPw, string newnName, string newSsn, string newAddress, string newEmail, int newType) {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).getMemberID() == newId) {
			cout << endl << "! ERROR : 이미 사용중인 아이디 입니다." << endl;
			return;
		}
		position++;
	}
		
		
	Member *newMember = new Member(newState, newId, newPw, newnName, newSsn, newAddress, newEmail, newType);
	memberList.push_back(*newMember);
	member = *newMember;
}


// Function : bool MemberManage::checkValue(string ID, string PW)
//
// Description :
//		이 함수는 로그인 상황에서 Member 클래스에게 사용자가 입력한 ID와 PW를 비교 하도록 하는
//		control 클래스의 함수이다.
//		Member 클래스에서 확인한 결과값을 bool형식으로 받아 로그인 성공여부에 대한 bool값을 리턴한다.
//
// Parameters : 
//
// Return Value :
//		로그인 성공여부를 나타내는 bool값
//
// Created: 2017/6/17 16:35
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 17:57 by 권용재
//	   what : 함수 이름 변경, 리턴타입 변경
//
bool MemberManage::checkValue(string ID, string PW) {
	if (member.checkValue(ID, PW)) return true;
	else return false;
}

// Function : void MemberManage::withdrawMember(string ID, string PW)
//
// Description :
//		이 함수는 회원탈퇴 상황에서 사용자가입력한 ID와 PW를 사용하여 인증을 거친 후
//		해당 회원정보를 지우는 역할을 하는 control 클래스의 함수이다..
//
// Parameters : 
//		string ID - 사용자가 입력한 아이디
//		string PW - 사용자가 입력한 비밀번호
//
// Return Value :
//
// Created : 2017/06/17 14:06
// Author : 권용재
// mail : wkqlwja2@gmail.com
//
// Revsions : 
//
void MemberManage::withdrawMember(string ID, string PW) {
	member.deleteMember(ID, PW);
}

// Function : bool MemberManage::returnMain()
//
// Description :
//		이 함수는 로그아웃 상황에서 Member::logOut 함수를 호출하는 control클래스의 함수이다.
//
// Parameters : 
//
// Return Value :
//		로그아웃 성공여부를 나타내는 bool값
//
// Created: 2017/6/17 16:50
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 16:55
//	   what : 리턴타입 변경
//
bool MemberManage::returnMain() {
	if (member.getMemberLogin()) {
		member.logOut();
		return true;
	}
	else return false;
}

// Function : void GroupManage::showGroupList()
//
// Description :
//		이 함수는 전체그룹 조회에서 사용자와 시스템을 연결한다.
//		존재하는 모든 그룹의 이름을 출력한다.
//
// Parameters : 
//
// Return Value :
//		
//
// Created : 2017/06/17 14:34
// Author : 홍민기
// mail : escandar@naver.com	
//
// Revsions : 
//
void GroupManage::showGroupList() {
	list<Group>::iterator position;
	position = groupList.begin();
	while (position != groupList.end()) {
		cout << (*position).getGroup() << "\n" << endl;
		position++;
	}
}

// Function : void GroupManage::checkGroupname(string newGroupname)
//
// Description :
//		이 함수는 그룹 생성 상황에서 사용자가 입력한 이름을 체크하는 control 클래스의 함수이다.
//		UI클래스로 부터 사용자가 입력한 이름을 전달 받고 이미 등록된 그룹 이름이라면 오류메시지와 함께 리턴된다.
//		아니라면 그룹을 생성한다.
//
// Parameters : 
//		string newGrouopname - 사용자가 입력한 새로 생성할 그룹 이름
//
// Return Value :
//
void GroupManage::checkGroupname(string newGroupname){
	list<Group>::iterator position;
	position = groupList.begin();

	while (position != groupList.end()) {
		if ((*position).getGroup() == newGroupname) {
			cout << endl << "! ERROR : 이미 사용중인 그룹 이름 입니다." << endl;
			return;
		}
		position++;
	}
	if (!member.getMemberLogin()) {
		cout << endl << "! ERROR : 로그인 상태가 아닙니다." << endl;
		return;
	}
	if (member.getMemberType() == 2 || member.getMemberType() == 3) {
		cout << endl << "! ERROR : 이미 다른 그룹의 회원입니다." << endl;
		return;
	}
	Group *newGroup = new Group(newGroupname);	// 로그인 여부 체크 + 그룹 가입 여부 체크 필요.
	groupList.push_back(*newGroup);

	list<Member>::iterator position2;
	position2 = memberList.begin();

	while (position2 != memberList.end()) {
		if ((*position2).getMemberID() == getCurrentSessionName()) {
			(*position2).setJoinedGroup(newGroupname);
			(*position2).setMemberType(3);
			member = *position2;
			return;
		}
		position2++;
	}
}

// Function : void GroupManage::addGroupMember(string groupName)
//
// Description :
//		이 함수는 그룹 가입 상황에서 받은 그룹이름으로 멤버를 가입시키는 control 클래스의 함수이다.
//		UI클래스로 부터 사용자가 입력한 그룹 이름을 받고 멤버 정보를 수정한다.
//
// Parameters : 
//		string groupName - 사용자가 입력한 가입할 그룹 이름
//
// Return Value :
//
void GroupManage::addGroupMember(string groupName){ // 그룹 가입여부 체크 필요
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).getMemberID() == getCurrentSessionName()) {
			(*position).setJoinedGroup(groupName);
			(*position).setMemberType(2);
			member = *position;
			cout << "Group 가입 완료\n";
			return;	
		}
		position++;
	}
}

// Function : void GroupManage::withdrawGroup(string groupName)
//
// Description :
//		이 함수는 그룹탈퇴 상황에서 사용자가 입력한 groupName을 사용해 가입 정보를 지우는 역할을 하는 control 클래스의 함수이다..
//
// Parameters : 
//		string groupName - 탈퇴할 그룹이름
//
// Return Value :
//
// Created : 2017/06/17 18:14
// Author : 김현재
// mail : cleverhj94@naver.com
//
// Revsions : 
//
void GroupManage::withdrawGroup(string groupName) {
	//멤버 정보 업데이트
	list<Member>::iterator position;
	position = memberList.begin();
	while (position != memberList.end()) {
		if ((*position).getMemberID() == getCurrentSessionName()) {
			//그룹 가입여부 체크
			if ((*position).getJoinedGroup() != groupName) {
				cout << endl << "! ERROR : 그룹의 회원이 아닙니다." << endl;
				return;
			}
			else if ((*position).getMemberType() == 3) {
				cout << endl << "! ERROR : 그룹 생성자는 탈퇴할 수 없습니다." << endl;
				return;
			}
			else {
				(*position).setJoinedGroup("");		//가입한 그룹 이름을 NULL로 초기화
				(*position).setMemberType(1);		//그룹 미가입 회원으로 업데이트
				member = *position;					// 그룹탈퇴하고 투표가능을 막음
				cout << "그룹 탈퇴가 완료되었습니다.\n";
				return;
			}
		}
		position++;
	}
}

// control
// Function : void VoteManager::suggestNewVote(string newSubject, int newListNum, string everyVote[], struct tm newStartTime, struct tm newEndTime)
//
// Description :
//		이 함수는 투표제안 상황에서 사용자가 입력한 값에 맞는 vote 생성자를 호출하는 control 클래스의 함수이다.
//		UI클래스로 부터 사용자가 입력한 값들을 전달 받아 투표 클래스 생성자를 호출한다.
//		
//
// Parameters : 
//		string newSubject - 사용자가 입력한 투표 주제
//		string newListNum - 투표 항목의 개수
//		string everyVote[] - 항목 행렬
//		struct tm newStartTime - 투표 시작시간 (연도,월,일,시,분)
//		struct tm newEndTime - 투표 마감시간 (연도, 월,일,시,분)
//
//
// Return Value
//
// Created : 2017/06/17 17:00
// Author : 김현재
// mail : cleverhj94@naver.com
// 
void VoteManager::suggestNewVote(string newSubject, int newListNum, string everyVote[], struct tm newStartTime, struct tm newEndTime) {
	list<Vote>::iterator position;
	position = voteList.begin();
	string choice= "Y";

	while (position != voteList.end()) {
	if ((*position).getVoteSubject() == newSubject) {			
		cout << endl << "! ERROR : 이미 존재하는 Vote Subject 입니다." << endl;
		return;
	}
	position++;
	}
	
	cout << endl << "투표를 생성하시겠습니까? (Y/N) ";
	cin >> choice;

	if (choice == "N") return;
	else {
		Vote *newVote = new Vote(newSubject, newListNum, everyVote, newStartTime, newEndTime);
		//printf("생성한 날짜:%d,%d,%d,%d\n", newVote->starttime->m_year);
		voteList.push_back(*newVote);
		cout << "투표가 생성되었습니다.\n";
	}
}

// Function : VoteManager::getProgressingVote()
//
// Description :
//		이 함수는 현재 진행중인 투표리스트 상황에서 현재 진행중인 투표 리스트를 출력한다.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/17 23:19
// Author : 황우현
// mail : dngus8549@naver.com
// 
void VoteManager::getProgressingVote(){
	list<Vote>::iterator position;
	position = voteList.begin();

	while (position != voteList.end()) {
		if ((*position).getVoteState() == 1 && (*position).getVoteGroupName() == member.getJoinedGroup()) {
			vote = *position;
			vote.getVoteList();
			vote.getTime();
			cout << endl << "Vote Subject : ";
			cout << (*position).getVoteSubject() << "\n";
			cout << "Vote List : \n";
			for (int i = 0; i < vote.getListNum(); i++) {
				cout << i + 1 << ". " << currentVoteList[i].listContents << "  count : " << currentVoteList[i].count << "\n";
			}
			cout << "남은 시간 : " << total_days(voteEnd.tm_year, voteEnd.tm_mon, voteEnd.tm_mday) - nowDays<< "일\n\n";
		}
		position++;
	}
}

// Function : VoteManager::getScheduledVote()
//
// Description :
//		이 함수는 실행 예정인 투표리스트 상황에서 실행 예정인 투표 리스트를 출력한다.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/19 22:16
// Author : 황우현
// mail : dngus8549@naver.com
// 
void VoteManager::getScheduledVote() {
	list<Vote>::iterator position;
	position = voteList.begin();

	while (position != voteList.end()) {
		if ((*position).getVoteState() == 0 && (*position).getVoteGroupName() == member.getJoinedGroup()) {
			vote = *position;
			vote.getVoteList();
			vote.getTime();
			cout << endl << "Vote Subject : ";
			cout << (*position).getVoteSubject() << "\n";
			cout << "Vote List : \n";
			for (int i = 0; i < vote.getListNum(); i++) {
				cout << i + 1 << ". " << currentVoteList[i].listContents << "  count : " << currentVoteList[i].count << "\n";
			}
			cout << "투표 시작 : " << voteEnd.tm_year << "년 " <<  voteEnd.tm_mon << "월 " <<  voteEnd.tm_mday << "일\n";
			cout << "투표 마감 : " << voteStart.tm_year << "년 " << voteStart.tm_mon << "월 " << voteStart.tm_mday << "일\n";
		}
		position++;
	}
}

// Function : VoteManager::getEndedVote()
//
// Description :
//		이 함수는 종료된 투표리스트 상황에서 종료된 투표 리스트를 출력한다.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/19 22:24
// Author : 황우현
// mail : dngus8549@naver.com
// 
void VoteManager::getEndedVote() {
	struct voteList voteOutcome;
	list<Vote>::iterator position;
	position = voteList.begin();

	while (position != voteList.end()) {
		if ((*position).getVoteState() == 2 && (*position).getVoteGroupName() == member.getJoinedGroup()) {
			vote = *position;
			vote.getVoteList();
			voteOutcome.listContents = currentVoteList[0].listContents;
			voteOutcome.count = currentVoteList[0].count;

			vote.getTime();
			cout << endl << "Vote Subject : ";
			cout << (*position).getVoteSubject() << "\n";
			cout << "Vote List : \n";
			for (int i = 0; i < vote.getListNum(); i++) {
				cout << i + 1 << ". " << currentVoteList[i].listContents << "  count : " << currentVoteList[i].count << "\n";
				if (voteOutcome.count < currentVoteList[i].count) {
					voteOutcome.listContents = currentVoteList[i].listContents;
					voteOutcome.count = currentVoteList[i].count;
				}
			}
			cout << "투표 결과 : \n		" << voteOutcome.listContents << " : " << voteOutcome.count << "표\n\n";
		}
		position++;
	}
}

// Function : VoteManager::toVote(string selectedVote)
//
// Description :
//		이 함수는 투표를 실제로 수행한다.
//		
//
// Parameters : string selectedVote - 투표할 주제
//
//
// Return Value
//
// Created : 2017/06/19 22:41
// Author : 황우현
// mail : dngus8549@naver.com
// 
void VoteManager::toVote(string selectedVote) {
	bool voteExist = false;
	list<Vote>::iterator position;
	position = voteList.begin();

	while (position != voteList.end()) {
		if ((*position).getVoteSubject() == selectedVote && (*position).getVoteGroupName() == member.getJoinedGroup()) {
			voteExist = true;
			vote = (*position);
			break;
		}
		position++;
	}
	if (!voteExist) {
		cout << endl << "! ERROR : 주제를 찾을 수 없습니다." << endl;
		return;
	}
	else {
		vote.checkOverlapVote(selectedVote);
	}
}

//UI

// loginUI------------------------------------------------------------------------------------------------------------

// Function : void loginUI::startInterface()
//
// Description :
//		이 함수는 로그인 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 17:30
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
void loginUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << endl << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "2.1. Login" << endl;
}

// Function : void loginUI::inputValue()
//
// Description :
//		이 함수는 로그인 상황에서 사용자로부터 ID와 PW를 입력 받는 함수이다.
//		입력받은 ID와 PW로 Membermanage::checkValue 함수를 호출한다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 17:55
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
// Revsions : 
//   1. When & Who : 2017/06/17 17:55 by 권용재
//      What : 리턴타입 수정
//
void loginUI::inputValue() {
	string ID, PW;
	string choice = "Y";

	cout << "ID : ";
	cin >> ID;
	cout << endl << "PW : ";
	cin >> PW;

	if (member.getMemberType() != 0) {
		cout << endl << "현재 Session에서 로그아웃하시겠습니까? (Y/N) ";
		cin >> choice;

		if (choice == "N") return;
		else {
			member.logOut();
			if (!member.getMemberLogin()) {
				cout << endl << "* Logout이 완료되었습니다." << endl;
			}
			else {
				cout << endl << "! ERROR : Logout에 실패했습니다." << endl;

				return;
			}
		}
	}


	if (!MemberManage::checkValue(ID, PW)) cout << endl << "! ERROR : Login에 실패했습니다." << endl;
	else 
		cout << endl << "* Login이 완료되었습니다." << endl;
	
	
}

// LogoutUI------------------------------------------------------------------------------------------------------------

// Function : void logoutUI::startInterface()
//
// Description :
//		이 함수는 로그아웃 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:00
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
void logoutUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "2.2. Logout" << endl;
}

// Function : int logoutUI::logout()
//
// Description :
//		이 함수는 로그아웃 상황에서 로그아웃 여부를 확인하는 함수이다.
//		사용자가 'Y'를 입력하면 Membermanage::returnMain 함수를 호출한다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:15
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 18:15 by 권용재
//      What : 리턴타입 수정
//
int logoutUI::logout() {
	string choice;

	while (choice != "Y" && choice != "N") {
		cout << endl << "정말 로그아웃하시겠습니까? (Y/N) ";
		cin >> choice;
	}

	if (choice == "N")return 0;
	else {
		if (MemberManage::returnMain()) {
			cout << endl << "* Logout이 완료되었습니다." << endl;
			return 1;
		}
		else {
			cout << endl << "! ERROR : Logout에 실패했습니다." << endl;
			return 0;
		}
	}
}


//sessionUI-------------------------------------------------
// Function : void sessionUI::startInterface()
//
// Description :
//		이 함수는 세션 변경 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 19:34
// Author : 김현재
// mail : cleverhj94@naver.com 
//
void sessionUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << endl << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "7. 세션 변경/선택" << endl;
}

// Function : void sessionUI::selectSession()
//
// Description :
//		이 함수는 세션 변경 상황에서 사용자로부터 세션을 변경하는 함수이다.
//		입력받은 ID와 PW로 Membermanage::checkValue 함수를 호출한다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 19:37
// Author : 김현재
// mail : cleverhj94@naver.com 
// 
// 
//
void sessionUI::selectSession() {
	string ID, PW;
	string choice;

	cout << "ID : ";
	cin >> ID;
	cout << endl << "PW : ";
	cin >> PW;

	while (choice != "Y"&&  choice != "N") {
		cout << endl << "Session을 변경하시겠습니까 (Y/N) ";
		cin >> choice;
	}

	if (!MemberManage::checkValue(ID, PW)) cout << endl << "! ERROR : Session 변경에 실패했습니다." << endl;
	else cout << endl << "* Session이 변경되었습니다." << endl;
}


//joinMemberUI---------------------------------------
//
// Function : void joinMemberUI::startInterface()
//
// Description :
//		이 함수는 회원가입 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:25
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
void joinMemberUI::startInterface() {
	cout << "회원가입 화면\n";
}

// Function : void joinMemberUI::registerMember()
//
// Description :
//		이 함수는 회원가입 상황에서 사용자로부터 가입하고자 하는 회원의 종류를 선택하고
//		해당 회원에게 필요한 정보값들을 입력받는 함수이다.
//		입력받은 값들은 MemberManage::registerMember 함수에게 전달된다.
//
// Parameters : 
//
// Return Value :
//10
// Created: 2017/6/17 18:55
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
void joinMemberUI::addMember() {
	string ID;
	string PW;
	string name;
	string ssn;
	string address;
	string email;
	string choice;

	cout << endl << "1.1. 회원가입" << endl;
	cout << "ID : ";
	cin >> ID;
	if (ID.length() > 20) {
		cout << endl << "! ERROR : ID는 20자를 넘을 수 없습니다." << endl;
		return;
	}
	cout << "PW : ";
	cin >> PW;
	if (PW.length() > 20) {
		cout << endl << "! ERROR : PW는 20자를 넘을 수 없습니다." << endl;
		return;

	}
	cout << "이름 : ";
	cin >> name;
	if (name.length() > 10) {
		cout << endl << "! ERROR : 이름는 한글 5자 영어 10자를 넘을 수 없습니다." << endl;
		return;

	}
	cout << "주민등록번호 : ";
	cin >> ssn;
	if (ssn.length() != 6) {
		cout << endl << "! ERROR : 올바른 생년월일을 입력하시오." << endl;
		return;

	}
	cout << "주소 : ";
	cin >> address;
	if (address.length() > 30) {
		cout << endl << "! ERROR : 올바른 주소를 입력하시오." << endl;
		return;
	}
	cout << "이메일 : ";
	cin >> email;
	if (email.length() > 30) {
		cout << endl << "! ERROR : 이메일을 입력하시오." << endl;
		return;
	}

	MemberManage::addMember(true, ID, PW, name, ssn, address, email, 1);
	cout <<""<< endl;
	cout << "회원가입이 완료되었습니다." << endl;

	if (groupList.empty()) {
		cout << "시스템에 그룹이 존재하지 않습니다.\n";
		return;
	}
	else {
		cout << "그룹 목록\n";
		GroupManage::showGroupList();
		while (choice != "Y" && choice != "N") {
			cout << endl << "그룹에 가입하시겠습니까? (Y/N) ";
			cin >> choice;
		}

		if (choice == "Y") { joinGroupUI::selectGroup(); }

	}
}

//memberWithdrawUI------------------------------

// Function : void memberWithdrawUI::startInterface()
//
// Description :
//		이 함수는 회원탈퇴 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:52
// Author : 권용재
// mail : wkqlwja2@gmail.com	
//
void memberWithdrawUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "1.2. 회원탈퇴" << endl;
}

// Function : void memberWithdrawUI::requestWithdraw()
//
// Description :
//		이 함수는 회원탈퇴 상황에서 사용자가 입력한 ID와 PW를 Membermanage::withdrawMember 함수에게 넘겨준다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:58
// Author : 권용재
// mail : wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:20 by 권용재
//      What : 리턴타입 수정
//
void memberWithdrawUI::requestWithdraw() {
	string ID, PW;
	string choice;

	cout << "ID : ";
	cin >> ID;
	cout << "PW : ";
	cin >> PW;

	while (choice != "Y" && choice != "N") {
		cout << endl << "탈퇴하시겠습니까? (Y/N) ";
		cin >> choice;
	}

	if (choice == "Y") MemberManage::withdrawMember(ID, PW);
}

// listGroupUI------------------------------------------------------------------------------------------------------------

// Function : void listGroupUI::startInterface()
//
// Description :
//		이 함수는 전체그룹 조회 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:29
// Author : 홍민기
// mail : escandar@naver.com	
//
void listGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "5.1. 전체그룹 조회" << endl;
}

// Function : void listGroupUI::showGroupList()
//
// Description :
//		이 함수는 전체그룹 조회를 실제로 수행하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:31
// Author : 홍민기
// mail : escandar@naver.com	
//
void listGroupUI::showGroupList() {
	
	if (groupList.empty()) {
		cout << "시스템에 그룹이 존재하지 않습니다.\n";
		return;
	}
	else {
		cout << "그룹 목록\n";
		GroupManage::showGroupList();
		if (member.getMemberType() == 2 || member.getMemberType() == 3) {
			return;
		}
		else {
			joinGroupUI::selectGroup();
		}
	}
}

// createGroupUI----------------------------------------------------------------------------
// Function : void createGroupUI::startInterface()
//
// Description :
//		이 함수는 그룹 생성 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 14:56
// Author : 홍민기
// mail : escandar@naver.com	
//
void createGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "5.3. 그룹 생성" << endl;
}

// Function : void createGroupUI::inputNewname()
//
// Description :
//		이 함수는 그룹생성 상황에서 사용자로부터 생성하고자 하는 그룹의 이름을 입력받는 함수이다.
//		입력받은 값들은 GroupManage::checkGroupname 함수에게 전달된다.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 21:00
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
void createGroupUI::inputNewname() {
	string newGroupname;
	
	cout << "그룹 이름 : ";
	cin >> newGroupname;

	GroupManage::checkGroupname(newGroupname);
}

// joinGroupUI----------------------------------------------------------------------------
// Function : void joinGroupUI::startInterface()
//
// Description :
//		이 함수는 그룹 가입 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:19
// Author : 홍민기
// mail : escandar@naver.com	
//
void joinGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "5.2. 그룹 가입" << endl;
}

// joinGroupUI----------------------------------------------------------------------------
// Function : void joinGroupUI::selectGroup()
//
// Description :
//		이 함수는 가입할 그룹 이름을 입력받는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:19
// Author : 홍민기
// mail : escandar@naver.com	
//
void joinGroupUI::selectGroup() {
	string groupName;
	bool groupExist= false; // 그룹 존재여부 체크
	cout << "가입할 그룹 이름 : ";
	cin >> groupName;

	list<Group>::iterator position;
	position = groupList.begin();

	while (position != groupList.end()) {
		if ((*position).getGroup() == groupName) {
			groupExist = true;
			break;
		}
		position++;
	}
	if (groupExist == false) {
		cout << endl << "! ERROR : 올바른 그룹 이름을 입력하세요." << endl;
		return;
	}
	else {
		// use case수정 필요. select해도 회원 정보 출력하지 않기
		GroupManage::addGroupMember(groupName);
	}
}

// listJoinedGroupUI------------------------------------------------------------------------------------------------------------

// Function : void listJoinedGroupUI::startInterface()
//
// Description :
//		이 함수는 가입그룹 조회 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 17:35
// Author : 홍민기
// mail : escandar@naver.com	
//
void listJoinedGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "5.4. 가입그룹 조회" << endl;
}

// Function : void listjoinedGroupUI::getJoinedGroup()
//
// Description :
//		이 함수는 가입그룹 조회를 실제로 수행하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 17:37
// Author : 홍민기
// mail : escandar@naver.com	
//
void listJoinedGroupUI::getJoinedGroup() {
	string choice;

	cout << member.getJoinedGroup() << "\n";

	while (choice != "Y" && choice != "N") {
		cout << endl << "그룹에서 탈퇴하시겠습니까? (Y/N) ";
		cin >> choice;
	}

	if (choice == "Y"){groupWithdrawUI::withdraw();}
}

// GroupWithdrawUI-------------------------------------------------------------------
// Function : void groupWithdrawUI::startInterface()
//
// Description :
//		이 함수는 그룹탈퇴 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:02
// Author : 김현재
// mail : cleverhj94@naver.com 
//
void groupWithdrawUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "5.5. 그룹탈퇴" << endl;
}

// Function : void groupWithdrawUI::withdraw()
//
// Description :
//		이 함수는 그룹탈퇴 상황에서 그룹을 탈퇴하는 함수
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:04
// Author : 김현재
// mail : cleverhj94@naver.com
//
void groupWithdrawUI::withdraw() {
	string groupName;
	string choice;
	bool groupCheck= false; // 그룹 존재여부 체크

	cout << "탈퇴할 그룹 이름 : ";
	cin >> groupName;

	list<Group>::iterator position;
	position = groupList.begin();
	while (position != groupList.end()) {
		if ((*position).getGroup() == groupName) {
			groupCheck = true;
			break;
		}
		position++;
	}
	if (groupCheck == false) {
		cout << endl << "! ERROR : 존재하지 않는 그룹입니다." << endl;
		return;
	}
	else {
		while (choice != "Y" &&choice != "N") {
			cout << endl << "탈퇴하시겠습니까? (Y/N) ";
			cin >> choice;
		}

		if (choice == "Y") GroupManage::withdrawGroup(groupName);
	}
}

//SuggestNewVoteUI---------------------------------------
//
// Function : void SuggestNewVoteUI::startInterface()
//
// Description :
//		이 함수는 투표생성의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:07
// Author : 김현재
// mail : cleverhj94@naver.com
//
void suggestNewVoteUI::startInterface() {
	cout << "투표제안 화면\n";
}

// Function : void SuggestNewVoteUI::SuggestNewVote()
//
// Description :
//		이 함수는 투표제안 상황에서 사용자로부터 투표 주제, 항목, 시작시간, 마감시간을 입력을 받아 투표를 생성한다.
//		해당 회원에게 필요한 정보값들을 입력받는 함수이다.
//      시작시간과 마감시간의 경우에는 tm 구조체를 이용하여 연도,월,일,시,분으로 나누어서 입력을 받도록 하였다.
//		입력받은 값들은 VoteManager::SuggestNewVote 함수에게 전달된다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:00
// Author : 김현재
// mail : cleverhj94@naver.com
//
// Revsions:
//   1. When & Who : 2017/06/17 22:06 pm by 김현재
//      What : list제거, listNum추가
//
//
void suggestNewVoteUI::suggestNewVote() {
	string subject;
	char listNum[10];
	struct tm starttime;
	struct tm endtime;

	long startDays, endDays;

	double dif; // 시간 차이

	string everyList[100];

	//cout << endl << "1.1. 회원가입" << endl;
	cout << "투표 주제 : ";
	cin >> subject;
	if (subject.length() > 20) {
		cout << endl << "! ERROR: 투표 주제는 20글자까지 가능합니다." << endl;
		return;
	}
	cout << "투표 항목 개수 : ";    // 몇개의 항목을 만들것인지 입력받기
	cin >> listNum;
	if (atoi(listNum) == 0) {
		cout << endl << "! ERROR : 숫자를 입력해야 합니다." << endl;
		return;
	}
	else if (atoi(listNum) > 100) {
		cout << endl << "! ERROR : 항목의 개수는 100개까지 가능합니다." << endl;
		return;
	}
	for (int i = 0; i < atoi(listNum); i++) {
		cout << "투표 항목" << i+1 << " : ";
		cin >> everyList[i];
	}
	cout << "------투표 시작시간 입력------\n";
	cout << "연도:";
	scanf("%d", &(starttime.tm_year));
	cout << "월:";
	scanf("%d", &(starttime.tm_mon));
	cout << "일:";
	scanf("%d", &(starttime.tm_mday));

	//cin >> starttime;
	cout << "------투표 마감시간 입력------\n";
	cout << "연도:";
	scanf("%d", &(endtime.tm_year));
	cout << "월:";
	scanf("%d", &(endtime.tm_mon));
	cout << "일:";
	scanf("%d", &(endtime.tm_mday));
	
	startDays = total_days(starttime.tm_year, starttime.tm_mon, starttime.tm_mday);
	endDays = total_days(endtime.tm_year, endtime.tm_mon, endtime.tm_mday);

	dif = endDays - startDays;
	if (dif < 0) {
		cout << endl << "! ERROR : 시간 설정에 오류가 있습니다." << endl;
	}
	else
		VoteManager::suggestNewVote(subject, atoi(listNum), everyList, starttime, endtime);
}

//timeNowUI------------------------------

//timeNowUI::startInterface()---------------------------------------
//
// Function : void timeNowUI::startInterface()
//
// Description :
//		이 함수는 현재시간 설정의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 21:49
// Author : 김현재
// mail : cleverhj94@naver.com
//
void timeNowUI::startInterface() {
	cout << "현재시간 설정 화면\n";
}

// Function : bool timeNowUI::inputDate()
//
// Description :
//		이 함수는 현재시간 설정 상황에서 사용자로부터 year, month, day를 입력을 받아 현재 시간을 설정한다.
//
// Parameters : 
//
// Return Value : true를 반환
//
// Created : 2017/06/17 21:51
// Author : 김현재
// mail : cleverhj94@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/19 21:58 pm by 황우현
//      What : inputDate함수 반환형 수정  
bool timeNowUI::inputDate() {
	struct tm present;

	long countDays; // 기준 년으로부터 경과일 체크

	//vote state갱신에 쓰이는 변수
	long startDays, endDays;
	
	cout << "년 : ";
	cin >> present.tm_year;
	if (present.tm_year < 1 )
	{
		cout << endl << "! ERROR : 부적절한 입력값 입니다." << endl;
		return false;
	}
	cout << "월 : ";   
	cin >> present.tm_mon;
	if (present.tm_mon > 12 || present.tm_mon < 1)
	{
		cout << endl << "! ERROR : 부적절한 입력값 입니다." << endl;
		return false;
	}
	cout << "일:";
	cin >> present.tm_mday;
	if (present.tm_mday > 31 || present.tm_mday < 1)
	{
		cout << endl << "! ERROR : 부적절한 입력값 입니다." << endl;
		return false;
	}

	countDays = total_days(present.tm_year, present.tm_mon, present.tm_mday);

	timeNow = present;
	nowDays= countDays; // 투표 시간과 비교

	cout << "현재시간 : " << present.tm_year << "/" << present.tm_mon << "/" << present.tm_mday << "\n";

	//갱신시, 모든 Vote의 state를 변경한다.
	if (!voteList.empty()) {
		list<Vote>::iterator position;
		position = voteList.begin();
		while (position != voteList.end()) {
			(*position).getTime();

			startDays = total_days(voteStart.tm_year, voteStart.tm_mon, voteStart.tm_mday);
			endDays = total_days(voteEnd.tm_year, voteEnd.tm_mon, voteEnd.tm_mday);

			if (startDays > nowDays) {
				(*position).setVoteState(0);
			}
			else if (nowDays > endDays) {
				//4주가 지난 경우 투표 삭제
				if(nowDays - endDays >= 28){
					voteList.erase(position++);
					continue;
				}
				else {
					(*position).setVoteState(2);
				}
			}
			else {
				(*position).setVoteState(1);
			}
			position++;
		}
	}
	return true;
}

// void ongoingVoteShowUI::startInterface()-------------------------------------------------------------------
// Function : void ongoingVoteShowUI::startInterface()
//
// Description :
//		이 함수는 현재 진행중인 투표리스트 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 23:06
// Author : 황우현
// mail : dngus8549@naver.com
//
void ongoingVoteShowUI::startInterface(){
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "4.1. 현재 진행중인 투표 리스트" << endl;
}

// void ongoingVoteShowUI::selectProgressingVote()-------------------------------------------------------------------
// Function : void ongoingVoteShowUI::selectProgressingVote()
//
// Description :
//		이 함수는 현재 진행중인 투표리스트를 출력하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 23:13
// Author : 황우현
// mail : dngus8549@naver.com
//
void ongoingVoteShowUI::selectProgressingVote() {
	VoteManager::getProgressingVote();
}

// void scheduledVoteShowUI::startInterface()-------------------------------------------------------------------
// Function : void scheduledVoteShowUI::startInterface()
//
// Description :
//		이 함수는 실행될 예정인 투표리스트 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:13
// Author : 황우현
// mail : dngus8549@naver.com
//
void scheduledVoteShowUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "4.3. 향후 진행 예정인 투표 리스트" << endl;
}

// void scheduledVoteShowUI::selectScheduledVote()-------------------------------------------------------------------
// Function : void scheduledVoteShowUI::selectScheduledVote()
//
// Description :
//		이 함수는 실행 예정인 투표리스트를 출력하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:15
// Author : 황우현
// mail : dngus8549@naver.com
//
void scheduledVoteShowUI::selectScheduledVote() {
	VoteManager::getScheduledVote();
}

// void endedVoteShowUI::startInterface()-------------------------------------------------------------------
// Function : void endedVoteShowUI::startInterface()
//
// Description :
//		이 함수는 종료된 투표리스트 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:25
// Author : 황우현
// mail : dngus8549@naver.com	
//
void endedVoteShowUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "4.4. 종료된 투표 리스트" << endl;
}

// void endedVoteShowUI::selectProgressingVote()-------------------------------------------------------------------
// Function : void endedVoteShowUI::selectEndedVote()
//
// Description :
//		이 함수는 종료된 투표리스트를 출력하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:27
// Author : 황우현
// mail : dngus8549@naver.com
//
void endedVoteShowUI::selectEndedVote() {
	VoteManager::getEndedVote();
}

// void toVoteUI::startInterface()-------------------------------------------------------------------
// Function : void toVoteUI::startInterface()
//
// Description :
//		이 함수는 투표 상황의 인터페이스를 시작하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:31
// Author : 황우현
// mail :dngus8549@naver.com
//
void toVoteUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ 현재 Session : " << member.getMemberID() << endl;
	cout << endl << "4.2. 투표" << endl;
}

// void toVoteUI::toVote()-------------------------------------------------------------------
// Function : void toVoteUI::toVote()
//
// Description :
//		이 함수는 투표를 실제로 수행하는 함수이다.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:32
// Author : 황우현
// mail : dngus8549@naver.com
//
void toVoteUI::toVote() {
	string selectedVote;
	cout << "투표할 주제 : ";
	cin >> selectedVote;
	VoteManager::toVote(selectedVote);
}

// 기타 함수----------------------------------------------------------------------------------------------------------

// Function : string getCurrentSessionName()
// Description: 현재 로그인한 회원의 이름을 반환한다.
// Parameters :   x
// Return Value :  member_ID
//
// Created: 2017/6/17 15:10
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
// Revsions : x
// 
string getCurrentSessionName() {
	return member.getMemberID();
}

// Function : int getCurrentSessionType()
// Description: 현재 로그인한 회원의 타입을 반환한다.
// Parameters :   x
// Return Value :  member_Type
//
// Created: 2017/6/17 15:55
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
int getCurrentSessionType() {
	return member.getMemberType();
}

// Function : long total_days(int year, int month, int day)
// Description: 기준일로부터 날짜 경과를 계산하는 함수,
// Parameters :   int year, int month, int day
// Return Value :  long days - 경과일을 반환
//
// Created: 2017/06/17
// Author: 김현재
// 
// 
long total_days(int year, int month, int day)
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i;
	long total = 0L;

	total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	if (!(year % 4) && year % 100 || !(year % 400))
		months[1]++;
	for (i = 0; i<month - 1; i++)
		total += months[i];
	total += day;

	return total;
}
