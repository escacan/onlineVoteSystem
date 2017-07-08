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
// voteList struct �� Ʃǥ�� �׸��� ǥ���ϴ� ����ü�μ�
// �׸��� ����� ��ǥ���� �����Ѵ�.
//
// Created: 2017/6/17 22:16
// Author: ������
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
// Member Ŭ������ �� �ý����� ����ϴ� ��� ����ڵ��� �����ϴ� Ŭ�����μ�
// Client, Restaurant Ŭ������ 'is a' ���踦 ���� �θ� Ŭ�����̴�.
// Member Ŭ������ ������� ID, PW, ����� Ÿ��, �α��� ���θ� ��Ÿ���� ������ ���� �ִ�.
//
// Created: 2017/6/17 11:10
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 11:15 by �ǿ���
//      What : ~Member�Լ� ����, checkMember() �Լ� �̸� ����
//		
//   2. When & Who : 2017/06/17 14:08 by ȫ�α�
//      What : joinedGroup ���� �߰�.
//
//   3. When & Who : 2017/06/17 15:44 by ȫ�α�
//      What : setJoinedGroup, setMemberType �Լ� �߰�
//
//   4. When & Who : 2017/06/17 17:41 by ȫ�α�
//      What : getJoinedGroup �Լ� �߰�
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

	int memberType;	// 0:guest, 1:�׷� �̰��� ȸ��, 2:�׷찡��ȸ��, 3:�׷� ������   
	
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
// Group Ŭ������ �� �ý����� ��� �׷��� �����ϴ� Ŭ�����̴�.
// Group Ŭ������ �׷��� �̸�, �׷� ������, �׷� ��� ����Ʈ�� ������ ������ �ִ�.
// 
// Created: 2017/06/16 17:10
// Author: ȫ�α�
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 13:12 pm by ȫ�α�
//      What : delete memName array ( same with list.begin )
//   2. When & Who : 2017/06/17 14:22 pm by ȫ�α�
//      What : ������ protected�� ����, getGroup�Լ� ��ȯ�� �� �μ� ����
//   3. When & Who : 2017/06/17 15:18 pm by ȫ�α�
//      What : �׷� ������ ����
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
// Vote Ŭ������ ȸ������ ������ ��ǥ���� �����ϴ� Ŭ�����̴�.
// ����,�׸�,���۽ð�,�����ð��� ��������� ���´�.
// Created: 2017/6/17 16:30
// Author: ������
// mail: cleverhj94@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 21:34 by ������
//      What : getVoteSubject�Լ� �߰� 
//	2. When & Who : 2017/06/17 22:17 by ������
//      What : list�� listNum���� ����,  voteList totalList[100]�߰� 	
//  3. When & Who : 2017/06/17 22:17 by ������
//      What : getVoteState() �Լ��� �߰�.
// 
//  4. When & Who : 2017/06/19 22:34 by Ȳ����
//      What : votedMemberList �߰�   checkOverlapVote()�� ���� �߰�.
//
//  5. When & Who : 2017/06/19 23:03 by Ȳ����
//      What : getListNum(), getVoteList() �߰�.
//
//  6. When & Who : 2017/06/19 23:47 by Ȳ����
//      What : getTime() �߰�.
//
//  7. When & Who : 2017/06/19 23:47 by Ȳ����
//      What : setListCount(int) �߰�.
//
//  8. When & Who : 2017/06/20 1:20 by Ȳ����
//      What : setVoteState(int) �߰�.
//
//  9. When & Who : 2017/06/20 1:58 by Ȳ����
//      What : groupName, getVoteGroupName() �߰�.
//
class Vote {
protected:
	int voteState;  // 0 : ����  1 : ������   2: ����
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


// Control Ŭ����

// Class : MemberManage
//
// Description:
// MemberManage Ŭ������ ȸ�������� ���õ� UI��� ���� ����� ��û�� �޾Ƶ帮�� ó���ϴ� ������ �Ѵ�.
// LoginUI, LogoutUI, SecessionUI, SessionUI, RegisterUI�� �޽����� �ְ� �޴´�.
//
// Created: 2017/6/17 11:35
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
// Revsions : 
//   1. When & Who : 2015/06/16 11:57 by �ǿ���
//      What : selectMemberType �Լ� ����
//				checkValue�Լ� return Ÿ�� void���� bool�� ����
//				returnMain�Լ� return Ÿ�� void���� bool�� ����
//	2. When & Who : 2017/06/17 12:01 by �ǿ���
//		What : withdrawMember �Լ� ����
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
// GroupManage Ŭ������ �׷������ ���õ� UI��� ���� ����� ��û�� �޾Ƶ帮�� ó���ϴ� ������ �Ѵ�.
// joinGroupUI, listGroupUI, createGroupUI, groupWithdrawUI�� �޽����� �ְ� �޴´�.
//
// Created: 2015/6/17 13:25
// Author: ȫ�α�
// mail: escandar@naver.com
//	
// Revsions 
//   1. When & Who : 2017/06/17 18:08 pm by ������
//      What : withdrawGroup�Լ� ����.
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
// VoteManager Ŭ������ ��ǥ������ ���õ� UI��� ���� ����� ��û�� �޾Ƶ帮�� ó���ϴ� ������ �Ѵ�.
// SuggestNewVoteUI�� �޽����� �ְ� �޴´�.
//
// Created: 2017/6/17 16:30
// Author: ������
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

// UI Ŭ����

// Class : LoginUI
//
// Description:
// LoginUI Ŭ������ �α��� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ID,PW�� �Ѱ� �޴� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 11:38
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 11:55 by �ǿ���
//      What : inputValue �Լ� return Ÿ�� bool���� void�� ����
// 
class loginUI {
public:
	static void startInterface();
	static void inputValue();
};


// Class : logoutUI
//
// Description:
// logoutUI Ŭ������ �α׾ƿ� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� �α׾ƿ��� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 12:00
// Author: �ǿ���
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
// joinMemberUI Ŭ������ ȸ������ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ȸ�������� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 12:30
// Author: �ǿ���
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
// memberWithdrawUI Ŭ������ ȸ��Ż�� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ȸ��Ż�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 13:49
// Author: �ǿ���
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
// listGroupUI Ŭ������ ��ü �׷� ��ȸ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ��ü �׷� ��ȸ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 13:22
// Author: ȫ�α�
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
// createGroupUI Ŭ������ �׷� ���� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� �׷� ������ ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 14:57
// Author: ȫ�α�
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:58 pm ȫ�α�
//      What : showDenyMes�Լ� ����
//
class createGroupUI {
public:
	static void startInterface();
	static void	inputNewname();
};

// Class : joinGroupUI
//
// Description:
// joinGroupUI Ŭ������ �׷� ���� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� �׷� ������ ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 16:15
// Author: ȫ�α�
// mail: escandar@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:58 pm ȫ�α�
//      What : showDenyMes�Լ� ����
//
class joinGroupUI {
public:
	static void startInterface();
	static void	selectGroup();
};

// Class : listJoinedGroupUI
//
// Description:
// listjoinedGroupUI Ŭ������ ���Ա׷� ��ȸ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ���Ա׷� ��ȸ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 17:34
// Author: ȫ�α�
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
// GroupWithdrawUI Ŭ������ �׷� Ż�� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� �׷� Ż�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 17:55
// Author: ������
// mail: cleverhj94@naver.com  
//
// Revsions : 
//
class groupWithdrawUI {
public:
	static void startInterface();
	static void	withdraw();	// sequence ���� �ʿ�.
};

// Class : sessionUI
//
// Description:
// sessionUI Ŭ������ ���� ���� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ���� ������ ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 19:32
// Author: ������
// mail: cleverhj94@naver.com 
//
// Revsions : 
//
class sessionUI {
public:
	static void startInterface();
	static void	selectSession();	// sequence ���� �ʿ�.
};

string getCurrentSessionName();
int getCurrentSessionType();

// Class : SuggestNewVoteUI
//
// Description:
// SuggestNewVoteUI Ŭ������ ȸ���α��� ���¿��� ��ǥ������ ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ��ǥ������ ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 16:02
// Author: ������
// mail: cleverhj94@naver.com
// 
class suggestNewVoteUI {
public:
	static void startInterface();
	static void suggestNewVote();
};

//vote&information UI ������

// Class : ongoingVoteShowUI
//
// Description:
// ongoingVoteShowUI Ŭ������ ���� �������� ��ǥ����Ʈ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� �������� ��ǥ ��ȸ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 22:57
// Author: Ȳ����
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
// scheduledVoteShowUI Ŭ������ ���� ������ ��ǥ����Ʈ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ���� ������ ��ǥ ��ȸ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/19 22:11
// Author: Ȳ����
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
// endedVoteShowUI Ŭ������ ����� ��ǥ����Ʈ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ����� ��ǥ ��ȸ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/19 22:22
// Author: Ȳ����
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
// toVoteUI Ŭ������ ��ǥ ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� ��ǥ�� ���� �����ϴ� �Լ��� ���� �ִ�.
//
// Created: 2017/6/19 22:30
// Author: Ȳ����
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
// timeNowUI Ŭ������ ����ð� ���� ��Ȳ���� ����ڿ� �ý����� ������ �ִ� UI ������ �Ѵ�.
// interface�� �����ϴ� �Լ��� year, month, day�� �Ѱ� �޴� �Լ��� ���� �ִ�.
//
// Created: 2017/6/17 21:47 
// Author: ������
// mail: cleverhj94@naver.com 
// 
// Revsions : 
//   1. When & Who : 2017/06/19 21:58 pm by Ȳ����
//      What : inputDate�Լ� ��ȯ�� ����  
//            
class timeNowUI {
public:
	static void startInterface();
	static bool inputDate();
};