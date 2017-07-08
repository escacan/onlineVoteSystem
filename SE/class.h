#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <time.h>

using namespace std;

// Class : voteList
//
// Description:
// voteList struct 는 튜표의 항목을 표시하는 구조체로서
// 항목의 내용과 득표수를 저장한다.
//
// Created: 2017/6/17 22:16
// Author: 김현재
// mail: cleverhj94@naver.com
//
// 
struct voteList {
public:
	string listContents;
	int count;
};

// Class : Member
//
// Description:
// Member 클래스는 이 시스템을 사용하는 모든 사용자들을 포함하는 클래스로서
// Client, Restaurant 클래스와 'is a' 관계를 갖는 부모 클래스이다.
// Member 클래스는 사용자의 ID, PW, 사용자 타입, 로그인 여부를 나타내는 변수를 갖고 있다.
//
// Created: 2017/6/17 11:10
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 11:15 by 권용재
//      What : ~Member함수 수정, checkMember() 함수 이름 수정
//		
//   2. When & Who : 2017/06/17 14:08 by 홍민기
//      What : joinedGroup 변수 추가.
//
//   3. When & Who : 2017/06/17 15:44 by 홍민기
//      What : setJoinedGroup, setMemberType 함수 추가
//
//   4. When & Who : 2017/06/17 17:41 by 홍민기
//      What : getJoinedGroup 함수 추가
// 
class Member {
protected:
	bool loginState;
	string name;
	string ssn;
	string address;
	string email;
	string id;
	string pwd;
	string joinedGroup;

	int memberType;	// 0:guest, 1:그룹 미가입 회원, 2:그룹가입회원, 3:그룹 생성자   
	
public:
	Member() {};
	Member(bool, string, string, string, string, string, string, int);
	string getMemberID();
	int getMemberType();
	string getJoinedGroup();
	void logOut();
	bool checkValue(string, string);
	bool getMemberLogin();
	void deleteMember(string, string);
	void setJoinedGroup(string);
	void setMemberType(int);
	void clear();
};

// Class : Group
//
// Description:
// Group 클래스는 이 시스템의 모든 그룹을 포함하는 클래스이다.
// Group 클래스는 그룹의 이름, 그룹 생성자, 그룹 멤버 리스트를 변수로 가지고 있다.
// 
// Created: 2017/06/16 17:10
// Author: 홍민기
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 13:12 pm by 홍민기
//      What : delete memName array ( same with list.begin )
//   2. When & Who : 2017/06/17 14:22 pm by 홍민기
//      What : 변수를 protected로 수정, getGroup함수 반환형 및 인수 수정
//   3. When & Who : 2017/06/17 15:18 pm by 홍민기
//      What : 그룹 생성자 수정
// 
class Group {
protected:
	string groupName;
	string groupCreator;
public:
	Group() {};
	Group(string);
	string getGroup();
};


// Class : Vote
//
// Description:
// Vote 클래스는 회원들이 제안한 투표들을 포함하는 클래스이다.
// 주제,항목,시작시간,마감시간을 멤버변수로 갖는다.
// Created: 2017/6/17 16:30
// Author: 김현재
// mail: cleverhj94@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 21:34 by 김현재
//      What : getVoteSubject함수 추가 
//	2. When & Who : 2017/06/17 22:17 by 김현재
//      What : list를 listNum으로 수정,  voteList totalList[100]추가 	
//  3. When & Who : 2017/06/17 22:17 by 김현재
//      What : getVoteState() 함수를 추가.
// 
//  4. When & Who : 2017/06/19 22:34 by 황우현
//      What : votedMemberList 추가   checkOverlapVote()에 인자 추가.
//
//  5. When & Who : 2017/06/19 23:03 by 황우현
//      What : getListNum(), getVoteList() 추가.
//
//  6. When & Who : 2017/06/19 23:47 by 황우현
//      What : getTime() 추가.
//
//  7. When & Who : 2017/06/19 23:47 by 황우현
//      What : setListCount(int) 추가.
//
//  8. When & Who : 2017/06/20 1:20 by 황우현
//      What : setVoteState(int) 추가.
//
//  9. When & Who : 2017/06/20 1:58 by 황우현
//      What : groupName, getVoteGroupName() 추가.
//
class Vote {
protected:
	int voteState;  // 0 : 예정  1 : 진행중   2: 종료
	string subject;
	int listNum;
	struct tm starttime;
	struct tm endtime;
	struct voteList totalList[100];
	list<string> votedMemberList;
	string groupName;
public:
	Vote(){};
	Vote(string, int, string*, struct tm, struct tm);
	string getVoteSubject();
	int getVoteState();
	void checkOverlapVote(string);
	int getListNum();
	void getVoteList();
	void getTime();
	void setListCount(int);
	void setVoteState(int);
	string getVoteGroupName();
};


// Control 클래스

// Class : MemberManage
//
// Description:
// MemberManage 클래스는 회원관리와 관련된 UI들로 부터 사용자 요청을 받아드리고 처리하는 역할을 한다.
// LoginUI, LogoutUI, SecessionUI, SessionUI, RegisterUI와 메시지를 주고 받는다.
//
// Created: 2017/6/17 11:35
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
// Revsions : 
//   1. When & Who : 2015/06/16 11:57 by 권용재
//      What : selectMemberType 함수 제거
//				checkValue함수 return 타입 void에서 bool로 변경
//				returnMain함수 return 타입 void에서 bool로 변경
//	2. When & Who : 2017/06/17 12:01 by 권용재
//		What : withdrawMember 함수 수정
class MemberManage {
public:
	static bool checkValue(string, string);
	static void addMember(bool, string, string, string, string, string, string, int);
	static void withdrawMember(string, string);
	static bool returnMain();
};

// Class : GroupManage
//
// Description:
// GroupManage 클래스는 그룹관리와 관련된 UI들로 부터 사용자 요청을 받아드리고 처리하는 역할을 한다.
// joinGroupUI, listGroupUI, createGroupUI, groupWithdrawUI와 메시지를 주고 받는다.
//
// Created: 2015/6/17 13:25
// Author: 홍민기
// mail: escandar@naver.com
//	
// Revsions 
//   1. When & Who : 2017/06/17 18:08 pm by 김현재
//      What : withdrawGroup함수 수정.
// 
class GroupManage {
public:
	static void checkGroupname(string);
	static void showGroupList();
	static void addGroupMember(string);
	static void withdrawGroup(string);
};

// Class : VoteManager
//
// Description:
// VoteManager 클래스는 투표관리와 관련된 UI들로 부터 사용자 요청을 받아드리고 처리하는 역할을 한다.
// SuggestNewVoteUI와 메시지를 주고 받는다.
//
// Created: 2017/6/17 16:30
// Author: 김현재
// mail: cleverhj94@naver.com
// 
// Revsions
//
class VoteManager {
public:
	static void suggestNewVote(string, int, string *, struct tm, struct tm);
	static void getProgressingVote();
	static void getScheduledVote();
	static void getEndedVote();
	static void toVote(string);
};

//boundary

// UI 클래스

// Class : LoginUI
//
// Description:
// LoginUI 클래스는 로그인 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 ID,PW를 넘겨 받는 함수를 갖고 있다.
//
// Created: 2017/6/17 11:38
// Author: 권용재
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 11:55 by 권용재
//      What : inputValue 함수 return 타입 bool에서 void로 변경
// 
class loginUI {
public:
	static void startInterface();
	static void inputValue();
};


// Class : logoutUI
//
// Description:
// logoutUI 클래스는 로그아웃 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 로그아웃을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 12:00
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
class logoutUI {
public:
	static void startInterface();
	static int logout();
};


// Class : joinMemberUI
//
// Description:
// joinMemberUI 클래스는 회원가입 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 회원가입을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 12:30
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
class joinMemberUI {
public:
	static void startInterface();
	static void addMember();
};

// Class : memberWithdrawUI
//
// Description:
// memberWithdrawUI 클래스는 회원탈퇴 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 회원탈퇴를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 13:49
// Author: 권용재
// mail: wkqlwja2@gmail.com
// 
class memberWithdrawUI {
public:
	static void startInterface();
	static void requestWithdraw();
};


// Class : listGroupUI
//
// Description:
// listGroupUI 클래스는 전체 그룹 조회 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 전체 그룹 조회를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 13:22
// Author: 홍민기
// mail: escandar@naver.com
// 
class listGroupUI {
public:
	static void startInterface();
	static void showGroupList();
};

// Class : createGroupUI
//
// Description:
// createGroupUI 클래스는 그룹 생성 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 그룹 생성을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 14:57
// Author: 홍민기
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:58 pm 홍민기
//      What : showDenyMes함수 제거
//
class createGroupUI {
public:
	static void startInterface();
	static void	inputNewname();
};

// Class : joinGroupUI
//
// Description:
// joinGroupUI 클래스는 그룹 가입 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 그룹 가입을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 16:15
// Author: 홍민기
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:58 pm 홍민기
//      What : showDenyMes함수 제거
//
class joinGroupUI {
public:
	static void startInterface();
	static void	selectGroup();
};

// Class : listJoinedGroupUI
//
// Description:
// listjoinedGroupUI 클래스는 가입그룹 조회 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 가입그룹 조회를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 17:34
// Author: 홍민기
// mail: escandar@naver.com
//
//
class listJoinedGroupUI {
public:
	static void startInterface();
	static void	getJoinedGroup();
};

// Class : groupWithdrawUI
//
// Description:
// GroupWithdrawUI 클래스는 그룹 탈퇴 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 그룹 탈퇴를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 17:55
// Author: 김현재
// mail: cleverhj94@naver.com  
//
// Revsions : 
//
class groupWithdrawUI {
public:
	static void startInterface();
	static void	withdraw();	// sequence 수정 필요.
};

// Class : sessionUI
//
// Description:
// sessionUI 클래스는 세션 변경 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 세션 변경을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 19:32
// Author: 김현재
// mail: cleverhj94@naver.com 
//
// Revsions : 
//
class sessionUI {
public:
	static void startInterface();
	static void	selectSession();	// sequence 수정 필요.
};

string getCurrentSessionName();
int getCurrentSessionType();

// Class : SuggestNewVoteUI
//
// Description:
// SuggestNewVoteUI 클래스는 회원로그인 상태에서 투표제안을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 투표제안을 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 16:02
// Author: 김현재
// mail: cleverhj94@naver.com
// 
class suggestNewVoteUI {
public:
	static void startInterface();
	static void suggestNewVote();
};

//vote&information UI 나누기

// Class : ongoingVoteShowUI
//
// Description:
// ongoingVoteShowUI 클래스는 현재 진행중인 투표리스트 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 진행중인 투표 조회를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/17 22:57
// Author: 황우현
// mail: dngus8549@naver.com
//
//
class ongoingVoteShowUI{
public:
	static void startInterface();
	static void	selectProgressingVote();
};

// Class : scheduledVoteShowUI
//
// Description:
// scheduledVoteShowUI 클래스는 실행 예정인 투표리스트 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 실행 예정인 투표 조회를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/19 22:11
// Author: 황우현
// mail: dngus8549@naver.com
//
//
class scheduledVoteShowUI {
public:
	static void startInterface();
	static void	selectScheduledVote();
};

// Class : endedVoteShowUI
//
// Description:
// endedVoteShowUI 클래스는 종료된 투표리스트 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 종료된 투표 조회를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/19 22:22
// Author: 황우현
// mail: dngus8549@naver.com
//
//
class endedVoteShowUI {
public:
	static void startInterface();
	static void	selectEndedVote();
};

// Class : toVoteUI
//
// Description:
// toVoteUI 클래스는 투표 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 투표를 실제 실행하는 함수를 갖고 있다.
//
// Created: 2017/6/19 22:30
// Author: 황우현
// mail: dngus8549@naver.com
//
//
class toVoteUI {
public:
	static void startInterface();
	static void	toVote();
};

// Class : timeNowUI
//
// Description:
// timeNowUI 클래스는 현재시간 설정 상황에서 사용자와 시스템을 연결해 주는 UI 역할을 한다.
// interface를 시작하는 함수와 year, month, day를 넘겨 받는 함수를 갖고 있다.
//
// Created: 2017/6/17 21:47 
// Author: 김현재
// mail: cleverhj94@naver.com 
// 
// Revsions : 
//   1. When & Who : 2017/06/19 21:58 pm by 황우현
//      What : inputDate함수 반환형 수정  
//            
class timeNowUI {
public:
	static void startInterface();
	static bool inputDate();
};