#include "class.h"
#pragma warning(disable: 4996) 

Member member(false, "Guest", "", "", "", "", "", 0);  // ���� �������� ���
Vote vote;
struct tm timeNow { 1, 1, 1, 1, 1, 1 };
struct tm voteStart{1,1,1};
struct tm voteEnd { 1, 1, 1 };
long nowDays; // ��ǥ �ð��� ��
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
//		�� �Լ��� �α��� ��Ȳ���� ����ڰ� �Է��� ID�� PW��
//		��ϵ� ȸ�� ������ ��ġ�ϴ��� Ȯ���ϴ� �Լ��̴�.
//		list<T>::iterator�� ����Ͽ� ��ϵ� ȸ�� ������ �Էµ� ������ ���Ѵ�.
//
// Parameters : 
//		string ID - ����ڰ� �Է��� ���̵�
//		string PW - ����ڰ� �Է��� ��й�ȣ
//
// Return Value :
//		��ϵ� ȸ�� ������ ��ġ�ϴ� �� ���θ� ��Ÿ���� bool��
//
// Created: 2017/6/17 11:11
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 14:00 
//	   what : �Լ� �̸� ����
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
//		�� �Լ��� member_ID�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :																
//
// Created: 2017/6/17 15:30
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
string Member::getMemberID() {
	return id;
}

// Function : string Member::getJoinedGroup()
//
// Description :
//		�� �Լ��� JoinedGroup�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :				
//		string joinedGroup - ����� ������ �׷� �̸�
//
// Created : 2017/06/17 17:43
// Author : ȫ�α�
// mail : escandar@naver.com	
// 
string Member::getJoinedGroup() {
	return joinedGroup;
}

// Function : void Member::setJoinedGroup(string groupName)
//
// Description :
//		�� �Լ��� ����� ���Ա׷��� �����ϴ� �Լ��̴�..
//
// Parameters : string groupName - ������ �׷� �̸�
//
// Return Value :																
//
// Created : 2017/06/17 15:47
// Author : ȫ�α�
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
//		�� �Լ��� ����� Ÿ���� �����ϴ� �Լ��̴�..
//
// Parameters : int type - ������ ����� Ÿ��
//
// Return Value :																
//
// Created : 2017/06/17 15:47
// Author : ȫ�α�
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
//		�� �Լ��� member_Type�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//		
// Return Value :																
//
// Created: 2017/6/17 15:45
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
int Member::getMemberType() {
	return memberType;
}

// Function : string Member::getMemberLogin()
//
// Description :
//		�� �Լ��� member_Login�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//		
// Return Value :																
//
// Created: 2017/6/17 15:55
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
bool Member::getMemberLogin() {
	return loginState;
}	


// Function : void Member::clear()
//
// Description :
//		�� �Լ��� Member ��ü�� �������� �����Ѵ�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 16:00
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 14:53 
//	   what : id�� Guest�� ����
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
//		�� �Լ��� �α׾ƿ� ��Ȳ���� ������� �α׾ƿ��� �����ϴ� �Լ��̴�.
//		�α��� �� ������� ������ �ӽ÷� ���� �ִ� ��ü���� �����Ѵ�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 16:15
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
void Member::logOut() {
	member.clear();
}


// Function : void Member::deleteMember(string ID, string PW)
//
// Description :
//		�� �Լ��� ȸ��Ż�� ��Ȳ���� ȸ���� ������ ���� �����ϴ� �Լ��̴�.
//		list<T>::iterator�� ����Ͽ� ����ڰ� �Է��� ȸ�������� �˻��ϰ� �����Ѵ�.
//
// Parameters : 
//		string ID - ����ڰ� �����ϱ� ���ϴ� ���̵�
//		string PW - ����ڰ� �����ϱ� ���ϴ� ���̵��� ��й�ȣ
//						
// Return Value : 														
//
// Created : 2017/06/17 14:11
// Author : �ǿ���
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

	if (completeDelete == false) cout << endl << "! ERROR : Ż�� �Ұ��� �մϴ�." << endl;
	else {
		member.clear();
		cout << endl << "* ȸ��Ż�� �Ϸ�Ǿ����ϴ�." << endl;
	}
	if (ID == member.getMemberID()) {
		cout << "* �α׾ƿ� �Ǿ����ϴ�\n";			
		member.id = "Guest";
		member.pwd = "";
		member.memberType = 0;
		member.loginState = false;
	}
}

// Function : string Group::getGroup()
//
// Description :
//		�� �Լ��� groupName�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :																
//
// Created : 2017/06/17 14:28
// Author : ȫ�α�
// mail : escandar@naver.com
// 
Group::Group(string newGroupname) {
	groupName = newGroupname;
	groupCreator = getCurrentSessionName();
}

// Function : string Group::getGroup()
//
// Description :
//		�� �Լ��� groupName�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :																
//
// Created : 2017/06/17 14:28
// Author : ȫ�α�
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
//		�� �Լ��� vote subject�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			string voteSubject - vote�� subject
//
// Created : 2017/06/17 21:37
// Author : ������
// mail : cleverhj94@naver.com 
// 
string Vote::getVoteSubject() {
	return subject;
}

// Function : int Vote::getVoteState()
//
// Description :
//		�� �Լ��� vote state�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			int voteState - vote�� state
//
// Created : 2017/06/17 23:22
// Author : Ȳ����
// mail :dngus8549@naver.com
// 
int Vote::getVoteState() {
	return voteState;
}

// Function : void Vote::setVoteState(int newState)
//
// Description :
//		�� �Լ��� Vote�� state�� �����ϴ� �Լ��̴�.
//
// Parameters : int newState - ������ Vote�� State
//
// Return Value :														
//			
//
// Created : 2017/06/20 1:22
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
void Vote::setVoteState(int newState) {
	voteState = newState;
}

// Function : int Vote::getListNum()
//
// Description :
//		�� �Լ��� listNum�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			int listNum - vote�� listNum
//
// Created : 2017/06/19 23:22
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
int Vote::getListNum() {
	return listNum;
}

// Function : void Vote::getVoteList()
//
// Description :
//		�� �Լ��� vote�� �׸��� vote list�� �ҷ����� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/19 23:07
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
void Vote::getVoteList() {
	currentVoteList= totalList;
}

// Function : void Vote::setListCount(int selectedList)
//
// Description :
//		�� �Լ��� �׸��� count�� 1�� ���ϴ� �Լ��̴�.
//
// Parameters : int selectedList - count�� 1�� ������ �� �׸��� ��ȣ
//
// Return Value :														
//			
//
// Created : 2017/06/20 00:24
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
void Vote::setListCount(int selectedList) {
	totalList[selectedList - 1].count++;
}


// Function : void Vote::getTime()
//
// Description :
//		�� �Լ��� vote�� ���۽ð��� ����ð��� �ҷ����� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/19 23:49
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
void Vote::getTime() {
	voteStart = starttime;
	voteEnd = endtime;
}

// Function : void Vote::checkOverlapVote(string selectedVote)
//
// Description :
//		�� �Լ��� ��ǥ ��Ȳ���� ����ڰ� �Է��� ��ǥ ������
//		�̹� ��ǥ�� �������� üũ�ϴ� �Լ��̴�.
//		list<T>::iterator�� ����Ͽ� ��ǥ ������ ����Ʈ�� ���� Session�� ID�� ���Ѵ�.
//
// Parameters : 
//		string selectedVote - ����ڰ� �Է��� ��ǥ ����
//
// Return Value :
//		
//
// Created : 2017/06/19 22:51
// Author : Ȳ����
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
	char selectedList[10];// ������ �׸�

	while (position1 != votedMemberList.end()) {
		if (*position1 == currentSessionId) {
			alreadyVoted = true;
			break;
		}
		position1++;
	}

	if (alreadyVoted) {
		cout << endl << "! ERROR : �̹� ��ǥ�� �����Դϴ�." << endl;
		return;
	}
	else {
		vote.getVoteList();
		listNum = vote.getListNum();
		cout << "��ǥ �׸�\n";
		for(i= 0; i< listNum; i++){
			cout << i+1 << ". " << currentVoteList[i].listContents << " : " << currentVoteList[i].count << "ǥ\n";
		}
		cout << "��ǥ�� �׸� ��ȣ : ";
		cin >> selectedList;
		if (atoi(selectedList) > listNum || atoi(selectedList) == 0 ) {
			cout << endl << "! ERROR : �߸��� �Է��Դϴ�." << endl;
		}
		else {
			//����Ʈ�� �����ؼ� ������ �����͸� �����ϴ� �κ�
			list<Vote>::iterator position2;
			position2 = voteList.begin();

			while (position2 != voteList.end()) {
				if ((*position2).getVoteSubject() == vote.getVoteSubject()) {
					break;
				}
				position2++;
			}

			(*position2).setListCount(atoi(selectedList));		// setCount �Լ� �߰� �ʿ�
			(*position2).votedMemberList.push_back(currentSessionId);   // ��ǥ ������ ����Ʈ�� �߰��ϴ� �ڵ�
			cout << "��ǥ �Ǿ����ϴ�.\n";
			cout << "��ǥ ���\n";
			
			(*position2).getVoteList();
			listNum = (*position2).getListNum();

			for (i = 0; i< listNum; i++) {
				cout << i + 1 << ". " << currentVoteList[i].listContents << " : " << currentVoteList[i].count << "ǥ\n";
			}
		}
	}
}

// Function : string Vote::getVoteGroupName()
//
// Description :
//		�� �Լ��� vote�� ���� �׷��̸�  groupName�� ��ȯ�ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :														
//			
//
// Created : 2017/06/20 02:04
// Author : Ȳ����
// mail : dngus8549@naver.com
// 
string Vote::getVoteGroupName() {
	return groupName;
}

// control
// Function : void MemberManage::AddMember(bool newState, string newId, string newPw, string newnName, string newSsn, string newAddress, string newEmail)
//
// Description :
//		�� �Լ��� ȸ������ ��Ȳ���� ����ڰ� ������ Ÿ�Կ� �´� �����ڸ� ȣ���ϴ� control Ŭ������ �Լ��̴�.
//		UIŬ������ ���� ����ڰ� �Է��� ������ ���� �޾� ����ڰ� ������ ȸ�� ������ Ŭ���� �����ڸ� ȣ���Ѵ�.
//		���� �Է��� ID�� �̹� ��ϵ� ����ڶ�� �����޽����� �Բ� ���ϵȴ�.
//
// Parameters : 
//		string ID - ����ڰ� �Է��� ���̵�
//		string PW - ����ڰ� �Է��� ��й�ȣ
//		int choice - ����ڰ� ������ ȸ�� ������ ��Ÿ���� ����
//		string name - ����ڰ� �Է��� �̸�
//		string birth - ����ڰ� �Է��� �������
//		string address - ����ڰ� �Է��� �ּ�
//		string email - ����ڰ� �Է��� �̸���
//		string number - ����ڰ� �Է��� ����ڹ�ȣ
//		string type - ����ڰ� �Է��� ������ Ÿ��
//		string time - ����ڰ� �Է��� �����ð�
//		string phone - ����ڰ� �Է��� ��ȭ��ȣ
//
// Return Value :
//
void MemberManage::addMember(bool newState, string newId, string newPw, string newnName, string newSsn, string newAddress, string newEmail, int newType) {
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).getMemberID() == newId) {
			cout << endl << "! ERROR : �̹� ������� ���̵� �Դϴ�." << endl;
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
//		�� �Լ��� �α��� ��Ȳ���� Member Ŭ�������� ����ڰ� �Է��� ID�� PW�� �� �ϵ��� �ϴ�
//		control Ŭ������ �Լ��̴�.
//		Member Ŭ�������� Ȯ���� ������� bool�������� �޾� �α��� �������ο� ���� bool���� �����Ѵ�.
//
// Parameters : 
//
// Return Value :
//		�α��� �������θ� ��Ÿ���� bool��
//
// Created: 2017/6/17 16:35
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 17:57 by �ǿ���
//	   what : �Լ� �̸� ����, ����Ÿ�� ����
//
bool MemberManage::checkValue(string ID, string PW) {
	if (member.checkValue(ID, PW)) return true;
	else return false;
}

// Function : void MemberManage::withdrawMember(string ID, string PW)
//
// Description :
//		�� �Լ��� ȸ��Ż�� ��Ȳ���� ����ڰ��Է��� ID�� PW�� ����Ͽ� ������ ��ģ ��
//		�ش� ȸ�������� ����� ������ �ϴ� control Ŭ������ �Լ��̴�..
//
// Parameters : 
//		string ID - ����ڰ� �Է��� ���̵�
//		string PW - ����ڰ� �Է��� ��й�ȣ
//
// Return Value :
//
// Created : 2017/06/17 14:06
// Author : �ǿ���
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
//		�� �Լ��� �α׾ƿ� ��Ȳ���� Member::logOut �Լ��� ȣ���ϴ� controlŬ������ �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//		�α׾ƿ� �������θ� ��Ÿ���� bool��
//
// Created: 2017/6/17 16:50
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//	1. when : 2017/06/17 16:55
//	   what : ����Ÿ�� ����
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
//		�� �Լ��� ��ü�׷� ��ȸ���� ����ڿ� �ý����� �����Ѵ�.
//		�����ϴ� ��� �׷��� �̸��� ����Ѵ�.
//
// Parameters : 
//
// Return Value :
//		
//
// Created : 2017/06/17 14:34
// Author : ȫ�α�
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
//		�� �Լ��� �׷� ���� ��Ȳ���� ����ڰ� �Է��� �̸��� üũ�ϴ� control Ŭ������ �Լ��̴�.
//		UIŬ������ ���� ����ڰ� �Է��� �̸��� ���� �ް� �̹� ��ϵ� �׷� �̸��̶�� �����޽����� �Բ� ���ϵȴ�.
//		�ƴ϶�� �׷��� �����Ѵ�.
//
// Parameters : 
//		string newGrouopname - ����ڰ� �Է��� ���� ������ �׷� �̸�
//
// Return Value :
//
void GroupManage::checkGroupname(string newGroupname){
	list<Group>::iterator position;
	position = groupList.begin();

	while (position != groupList.end()) {
		if ((*position).getGroup() == newGroupname) {
			cout << endl << "! ERROR : �̹� ������� �׷� �̸� �Դϴ�." << endl;
			return;
		}
		position++;
	}
	if (!member.getMemberLogin()) {
		cout << endl << "! ERROR : �α��� ���°� �ƴմϴ�." << endl;
		return;
	}
	if (member.getMemberType() == 2 || member.getMemberType() == 3) {
		cout << endl << "! ERROR : �̹� �ٸ� �׷��� ȸ���Դϴ�." << endl;
		return;
	}
	Group *newGroup = new Group(newGroupname);	// �α��� ���� üũ + �׷� ���� ���� üũ �ʿ�.
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
//		�� �Լ��� �׷� ���� ��Ȳ���� ���� �׷��̸����� ����� ���Խ�Ű�� control Ŭ������ �Լ��̴�.
//		UIŬ������ ���� ����ڰ� �Է��� �׷� �̸��� �ް� ��� ������ �����Ѵ�.
//
// Parameters : 
//		string groupName - ����ڰ� �Է��� ������ �׷� �̸�
//
// Return Value :
//
void GroupManage::addGroupMember(string groupName){ // �׷� ���Կ��� üũ �ʿ�
	list<Member>::iterator position;
	position = memberList.begin();

	while (position != memberList.end()) {
		if ((*position).getMemberID() == getCurrentSessionName()) {
			(*position).setJoinedGroup(groupName);
			(*position).setMemberType(2);
			member = *position;
			cout << "Group ���� �Ϸ�\n";
			return;	
		}
		position++;
	}
}

// Function : void GroupManage::withdrawGroup(string groupName)
//
// Description :
//		�� �Լ��� �׷�Ż�� ��Ȳ���� ����ڰ� �Է��� groupName�� ����� ���� ������ ����� ������ �ϴ� control Ŭ������ �Լ��̴�..
//
// Parameters : 
//		string groupName - Ż���� �׷��̸�
//
// Return Value :
//
// Created : 2017/06/17 18:14
// Author : ������
// mail : cleverhj94@naver.com
//
// Revsions : 
//
void GroupManage::withdrawGroup(string groupName) {
	//��� ���� ������Ʈ
	list<Member>::iterator position;
	position = memberList.begin();
	while (position != memberList.end()) {
		if ((*position).getMemberID() == getCurrentSessionName()) {
			//�׷� ���Կ��� üũ
			if ((*position).getJoinedGroup() != groupName) {
				cout << endl << "! ERROR : �׷��� ȸ���� �ƴմϴ�." << endl;
				return;
			}
			else if ((*position).getMemberType() == 3) {
				cout << endl << "! ERROR : �׷� �����ڴ� Ż���� �� �����ϴ�." << endl;
				return;
			}
			else {
				(*position).setJoinedGroup("");		//������ �׷� �̸��� NULL�� �ʱ�ȭ
				(*position).setMemberType(1);		//�׷� �̰��� ȸ������ ������Ʈ
				member = *position;					// �׷�Ż���ϰ� ��ǥ������ ����
				cout << "�׷� Ż�� �Ϸ�Ǿ����ϴ�.\n";
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
//		�� �Լ��� ��ǥ���� ��Ȳ���� ����ڰ� �Է��� ���� �´� vote �����ڸ� ȣ���ϴ� control Ŭ������ �Լ��̴�.
//		UIŬ������ ���� ����ڰ� �Է��� ������ ���� �޾� ��ǥ Ŭ���� �����ڸ� ȣ���Ѵ�.
//		
//
// Parameters : 
//		string newSubject - ����ڰ� �Է��� ��ǥ ����
//		string newListNum - ��ǥ �׸��� ����
//		string everyVote[] - �׸� ���
//		struct tm newStartTime - ��ǥ ���۽ð� (����,��,��,��,��)
//		struct tm newEndTime - ��ǥ �����ð� (����, ��,��,��,��)
//
//
// Return Value
//
// Created : 2017/06/17 17:00
// Author : ������
// mail : cleverhj94@naver.com
// 
void VoteManager::suggestNewVote(string newSubject, int newListNum, string everyVote[], struct tm newStartTime, struct tm newEndTime) {
	list<Vote>::iterator position;
	position = voteList.begin();
	string choice= "Y";

	while (position != voteList.end()) {
	if ((*position).getVoteSubject() == newSubject) {			
		cout << endl << "! ERROR : �̹� �����ϴ� Vote Subject �Դϴ�." << endl;
		return;
	}
	position++;
	}
	
	cout << endl << "��ǥ�� �����Ͻðڽ��ϱ�? (Y/N) ";
	cin >> choice;

	if (choice == "N") return;
	else {
		Vote *newVote = new Vote(newSubject, newListNum, everyVote, newStartTime, newEndTime);
		//printf("������ ��¥:%d,%d,%d,%d\n", newVote->starttime->m_year);
		voteList.push_back(*newVote);
		cout << "��ǥ�� �����Ǿ����ϴ�.\n";
	}
}

// Function : VoteManager::getProgressingVote()
//
// Description :
//		�� �Լ��� ���� �������� ��ǥ����Ʈ ��Ȳ���� ���� �������� ��ǥ ����Ʈ�� ����Ѵ�.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/17 23:19
// Author : Ȳ����
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
			cout << "���� �ð� : " << total_days(voteEnd.tm_year, voteEnd.tm_mon, voteEnd.tm_mday) - nowDays<< "��\n\n";
		}
		position++;
	}
}

// Function : VoteManager::getScheduledVote()
//
// Description :
//		�� �Լ��� ���� ������ ��ǥ����Ʈ ��Ȳ���� ���� ������ ��ǥ ����Ʈ�� ����Ѵ�.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/19 22:16
// Author : Ȳ����
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
			cout << "��ǥ ���� : " << voteEnd.tm_year << "�� " <<  voteEnd.tm_mon << "�� " <<  voteEnd.tm_mday << "��\n";
			cout << "��ǥ ���� : " << voteStart.tm_year << "�� " << voteStart.tm_mon << "�� " << voteStart.tm_mday << "��\n";
		}
		position++;
	}
}

// Function : VoteManager::getEndedVote()
//
// Description :
//		�� �Լ��� ����� ��ǥ����Ʈ ��Ȳ���� ����� ��ǥ ����Ʈ�� ����Ѵ�.
//		
//
// Parameters : 
//
//
// Return Value
//
// Created : 2017/06/19 22:24
// Author : Ȳ����
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
			cout << "��ǥ ��� : \n		" << voteOutcome.listContents << " : " << voteOutcome.count << "ǥ\n\n";
		}
		position++;
	}
}

// Function : VoteManager::toVote(string selectedVote)
//
// Description :
//		�� �Լ��� ��ǥ�� ������ �����Ѵ�.
//		
//
// Parameters : string selectedVote - ��ǥ�� ����
//
//
// Return Value
//
// Created : 2017/06/19 22:41
// Author : Ȳ����
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
		cout << endl << "! ERROR : ������ ã�� �� �����ϴ�." << endl;
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
//		�� �Լ��� �α��� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 17:30
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
void loginUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << endl << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "2.1. Login" << endl;
}

// Function : void loginUI::inputValue()
//
// Description :
//		�� �Լ��� �α��� ��Ȳ���� ����ڷκ��� ID�� PW�� �Է� �޴� �Լ��̴�.
//		�Է¹��� ID�� PW�� Membermanage::checkValue �Լ��� ȣ���Ѵ�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 17:55
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
// Revsions : 
//   1. When & Who : 2017/06/17 17:55 by �ǿ���
//      What : ����Ÿ�� ����
//
void loginUI::inputValue() {
	string ID, PW;
	string choice = "Y";

	cout << "ID : ";
	cin >> ID;
	cout << endl << "PW : ";
	cin >> PW;

	if (member.getMemberType() != 0) {
		cout << endl << "���� Session���� �α׾ƿ��Ͻðڽ��ϱ�? (Y/N) ";
		cin >> choice;

		if (choice == "N") return;
		else {
			member.logOut();
			if (!member.getMemberLogin()) {
				cout << endl << "* Logout�� �Ϸ�Ǿ����ϴ�." << endl;
			}
			else {
				cout << endl << "! ERROR : Logout�� �����߽��ϴ�." << endl;

				return;
			}
		}
	}


	if (!MemberManage::checkValue(ID, PW)) cout << endl << "! ERROR : Login�� �����߽��ϴ�." << endl;
	else 
		cout << endl << "* Login�� �Ϸ�Ǿ����ϴ�." << endl;
	
	
}

// LogoutUI------------------------------------------------------------------------------------------------------------

// Function : void logoutUI::startInterface()
//
// Description :
//		�� �Լ��� �α׾ƿ� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:00
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
void logoutUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "2.2. Logout" << endl;
}

// Function : int logoutUI::logout()
//
// Description :
//		�� �Լ��� �α׾ƿ� ��Ȳ���� �α׾ƿ� ���θ� Ȯ���ϴ� �Լ��̴�.
//		����ڰ� 'Y'�� �Է��ϸ� Membermanage::returnMain �Լ��� ȣ���Ѵ�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:15
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 18:15 by �ǿ���
//      What : ����Ÿ�� ����
//
int logoutUI::logout() {
	string choice;

	while (choice != "Y" && choice != "N") {
		cout << endl << "���� �α׾ƿ��Ͻðڽ��ϱ�? (Y/N) ";
		cin >> choice;
	}

	if (choice == "N")return 0;
	else {
		if (MemberManage::returnMain()) {
			cout << endl << "* Logout�� �Ϸ�Ǿ����ϴ�." << endl;
			return 1;
		}
		else {
			cout << endl << "! ERROR : Logout�� �����߽��ϴ�." << endl;
			return 0;
		}
	}
}


//sessionUI-------------------------------------------------
// Function : void sessionUI::startInterface()
//
// Description :
//		�� �Լ��� ���� ���� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 19:34
// Author : ������
// mail : cleverhj94@naver.com 
//
void sessionUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << endl << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "7. ���� ����/����" << endl;
}

// Function : void sessionUI::selectSession()
//
// Description :
//		�� �Լ��� ���� ���� ��Ȳ���� ����ڷκ��� ������ �����ϴ� �Լ��̴�.
//		�Է¹��� ID�� PW�� Membermanage::checkValue �Լ��� ȣ���Ѵ�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 19:37
// Author : ������
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
		cout << endl << "Session�� �����Ͻðڽ��ϱ� (Y/N) ";
		cin >> choice;
	}

	if (!MemberManage::checkValue(ID, PW)) cout << endl << "! ERROR : Session ���濡 �����߽��ϴ�." << endl;
	else cout << endl << "* Session�� ����Ǿ����ϴ�." << endl;
}


//joinMemberUI---------------------------------------
//
// Function : void joinMemberUI::startInterface()
//
// Description :
//		�� �Լ��� ȸ������ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 18:25
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
void joinMemberUI::startInterface() {
	cout << "ȸ������ ȭ��\n";
}

// Function : void joinMemberUI::registerMember()
//
// Description :
//		�� �Լ��� ȸ������ ��Ȳ���� ����ڷκ��� �����ϰ��� �ϴ� ȸ���� ������ �����ϰ�
//		�ش� ȸ������ �ʿ��� ���������� �Է¹޴� �Լ��̴�.
//		�Է¹��� ������ MemberManage::registerMember �Լ����� ���޵ȴ�.
//
// Parameters : 
//
// Return Value :
//10
// Created: 2017/6/17 18:55
// Author: �ǿ���
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

	cout << endl << "1.1. ȸ������" << endl;
	cout << "ID : ";
	cin >> ID;
	if (ID.length() > 20) {
		cout << endl << "! ERROR : ID�� 20�ڸ� ���� �� �����ϴ�." << endl;
		return;
	}
	cout << "PW : ";
	cin >> PW;
	if (PW.length() > 20) {
		cout << endl << "! ERROR : PW�� 20�ڸ� ���� �� �����ϴ�." << endl;
		return;

	}
	cout << "�̸� : ";
	cin >> name;
	if (name.length() > 10) {
		cout << endl << "! ERROR : �̸��� �ѱ� 5�� ���� 10�ڸ� ���� �� �����ϴ�." << endl;
		return;

	}
	cout << "�ֹε�Ϲ�ȣ : ";
	cin >> ssn;
	if (ssn.length() != 6) {
		cout << endl << "! ERROR : �ùٸ� ��������� �Է��Ͻÿ�." << endl;
		return;

	}
	cout << "�ּ� : ";
	cin >> address;
	if (address.length() > 30) {
		cout << endl << "! ERROR : �ùٸ� �ּҸ� �Է��Ͻÿ�." << endl;
		return;
	}
	cout << "�̸��� : ";
	cin >> email;
	if (email.length() > 30) {
		cout << endl << "! ERROR : �̸����� �Է��Ͻÿ�." << endl;
		return;
	}

	MemberManage::addMember(true, ID, PW, name, ssn, address, email, 1);
	cout <<""<< endl;
	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;

	if (groupList.empty()) {
		cout << "�ý��ۿ� �׷��� �������� �ʽ��ϴ�.\n";
		return;
	}
	else {
		cout << "�׷� ���\n";
		GroupManage::showGroupList();
		while (choice != "Y" && choice != "N") {
			cout << endl << "�׷쿡 �����Ͻðڽ��ϱ�? (Y/N) ";
			cin >> choice;
		}

		if (choice == "Y") { joinGroupUI::selectGroup(); }

	}
}

//memberWithdrawUI------------------------------

// Function : void memberWithdrawUI::startInterface()
//
// Description :
//		�� �Լ��� ȸ��Ż�� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:52
// Author : �ǿ���
// mail : wkqlwja2@gmail.com	
//
void memberWithdrawUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "1.2. ȸ��Ż��" << endl;
}

// Function : void memberWithdrawUI::requestWithdraw()
//
// Description :
//		�� �Լ��� ȸ��Ż�� ��Ȳ���� ����ڰ� �Է��� ID�� PW�� Membermanage::withdrawMember �Լ����� �Ѱ��ش�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:58
// Author : �ǿ���
// mail : wkqlwja2@gmail.com
//
// Revsions : 
//   1. When & Who : 2017/06/17 14:20 by �ǿ���
//      What : ����Ÿ�� ����
//
void memberWithdrawUI::requestWithdraw() {
	string ID, PW;
	string choice;

	cout << "ID : ";
	cin >> ID;
	cout << "PW : ";
	cin >> PW;

	while (choice != "Y" && choice != "N") {
		cout << endl << "Ż���Ͻðڽ��ϱ�? (Y/N) ";
		cin >> choice;
	}

	if (choice == "Y") MemberManage::withdrawMember(ID, PW);
}

// listGroupUI------------------------------------------------------------------------------------------------------------

// Function : void listGroupUI::startInterface()
//
// Description :
//		�� �Լ��� ��ü�׷� ��ȸ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:29
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void listGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "5.1. ��ü�׷� ��ȸ" << endl;
}

// Function : void listGroupUI::showGroupList()
//
// Description :
//		�� �Լ��� ��ü�׷� ��ȸ�� ������ �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 13:31
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void listGroupUI::showGroupList() {
	
	if (groupList.empty()) {
		cout << "�ý��ۿ� �׷��� �������� �ʽ��ϴ�.\n";
		return;
	}
	else {
		cout << "�׷� ���\n";
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
//		�� �Լ��� �׷� ���� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 14:56
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void createGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "5.3. �׷� ����" << endl;
}

// Function : void createGroupUI::inputNewname()
//
// Description :
//		�� �Լ��� �׷���� ��Ȳ���� ����ڷκ��� �����ϰ��� �ϴ� �׷��� �̸��� �Է¹޴� �Լ��̴�.
//		�Է¹��� ������ GroupManage::checkGroupname �Լ����� ���޵ȴ�.
//
// Parameters : 
//
// Return Value :
//
// Created: 2017/6/17 21:00
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
//
void createGroupUI::inputNewname() {
	string newGroupname;
	
	cout << "�׷� �̸� : ";
	cin >> newGroupname;

	GroupManage::checkGroupname(newGroupname);
}

// joinGroupUI----------------------------------------------------------------------------
// Function : void joinGroupUI::startInterface()
//
// Description :
//		�� �Լ��� �׷� ���� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:19
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void joinGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "5.2. �׷� ����" << endl;
}

// joinGroupUI----------------------------------------------------------------------------
// Function : void joinGroupUI::selectGroup()
//
// Description :
//		�� �Լ��� ������ �׷� �̸��� �Է¹޴� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:19
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void joinGroupUI::selectGroup() {
	string groupName;
	bool groupExist= false; // �׷� ���翩�� üũ
	cout << "������ �׷� �̸� : ";
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
		cout << endl << "! ERROR : �ùٸ� �׷� �̸��� �Է��ϼ���." << endl;
		return;
	}
	else {
		// use case���� �ʿ�. select�ص� ȸ�� ���� ������� �ʱ�
		GroupManage::addGroupMember(groupName);
	}
}

// listJoinedGroupUI------------------------------------------------------------------------------------------------------------

// Function : void listJoinedGroupUI::startInterface()
//
// Description :
//		�� �Լ��� ���Ա׷� ��ȸ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 17:35
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void listJoinedGroupUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "5.4. ���Ա׷� ��ȸ" << endl;
}

// Function : void listjoinedGroupUI::getJoinedGroup()
//
// Description :
//		�� �Լ��� ���Ա׷� ��ȸ�� ������ �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 17:37
// Author : ȫ�α�
// mail : escandar@naver.com	
//
void listJoinedGroupUI::getJoinedGroup() {
	string choice;

	cout << member.getJoinedGroup() << "\n";

	while (choice != "Y" && choice != "N") {
		cout << endl << "�׷쿡�� Ż���Ͻðڽ��ϱ�? (Y/N) ";
		cin >> choice;
	}

	if (choice == "Y"){groupWithdrawUI::withdraw();}
}

// GroupWithdrawUI-------------------------------------------------------------------
// Function : void groupWithdrawUI::startInterface()
//
// Description :
//		�� �Լ��� �׷�Ż�� ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:02
// Author : ������
// mail : cleverhj94@naver.com 
//
void groupWithdrawUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "5.5. �׷�Ż��" << endl;
}

// Function : void groupWithdrawUI::withdraw()
//
// Description :
//		�� �Լ��� �׷�Ż�� ��Ȳ���� �׷��� Ż���ϴ� �Լ�
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:04
// Author : ������
// mail : cleverhj94@naver.com
//
void groupWithdrawUI::withdraw() {
	string groupName;
	string choice;
	bool groupCheck= false; // �׷� ���翩�� üũ

	cout << "Ż���� �׷� �̸� : ";
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
		cout << endl << "! ERROR : �������� �ʴ� �׷��Դϴ�." << endl;
		return;
	}
	else {
		while (choice != "Y" &&choice != "N") {
			cout << endl << "Ż���Ͻðڽ��ϱ�? (Y/N) ";
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
//		�� �Լ��� ��ǥ������ �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 16:07
// Author : ������
// mail : cleverhj94@naver.com
//
void suggestNewVoteUI::startInterface() {
	cout << "��ǥ���� ȭ��\n";
}

// Function : void SuggestNewVoteUI::SuggestNewVote()
//
// Description :
//		�� �Լ��� ��ǥ���� ��Ȳ���� ����ڷκ��� ��ǥ ����, �׸�, ���۽ð�, �����ð��� �Է��� �޾� ��ǥ�� �����Ѵ�.
//		�ش� ȸ������ �ʿ��� ���������� �Է¹޴� �Լ��̴�.
//      ���۽ð��� �����ð��� ��쿡�� tm ����ü�� �̿��Ͽ� ����,��,��,��,������ ����� �Է��� �޵��� �Ͽ���.
//		�Է¹��� ������ VoteManager::SuggestNewVote �Լ����� ���޵ȴ�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 18:00
// Author : ������
// mail : cleverhj94@naver.com
//
// Revsions:
//   1. When & Who : 2017/06/17 22:06 pm by ������
//      What : list����, listNum�߰�
//
//
void suggestNewVoteUI::suggestNewVote() {
	string subject;
	char listNum[10];
	struct tm starttime;
	struct tm endtime;

	long startDays, endDays;

	double dif; // �ð� ����

	string everyList[100];

	//cout << endl << "1.1. ȸ������" << endl;
	cout << "��ǥ ���� : ";
	cin >> subject;
	if (subject.length() > 20) {
		cout << endl << "! ERROR: ��ǥ ������ 20���ڱ��� �����մϴ�." << endl;
		return;
	}
	cout << "��ǥ �׸� ���� : ";    // ��� �׸��� ��������� �Է¹ޱ�
	cin >> listNum;
	if (atoi(listNum) == 0) {
		cout << endl << "! ERROR : ���ڸ� �Է��ؾ� �մϴ�." << endl;
		return;
	}
	else if (atoi(listNum) > 100) {
		cout << endl << "! ERROR : �׸��� ������ 100������ �����մϴ�." << endl;
		return;
	}
	for (int i = 0; i < atoi(listNum); i++) {
		cout << "��ǥ �׸�" << i+1 << " : ";
		cin >> everyList[i];
	}
	cout << "------��ǥ ���۽ð� �Է�------\n";
	cout << "����:";
	scanf("%d", &(starttime.tm_year));
	cout << "��:";
	scanf("%d", &(starttime.tm_mon));
	cout << "��:";
	scanf("%d", &(starttime.tm_mday));

	//cin >> starttime;
	cout << "------��ǥ �����ð� �Է�------\n";
	cout << "����:";
	scanf("%d", &(endtime.tm_year));
	cout << "��:";
	scanf("%d", &(endtime.tm_mon));
	cout << "��:";
	scanf("%d", &(endtime.tm_mday));
	
	startDays = total_days(starttime.tm_year, starttime.tm_mon, starttime.tm_mday);
	endDays = total_days(endtime.tm_year, endtime.tm_mon, endtime.tm_mday);

	dif = endDays - startDays;
	if (dif < 0) {
		cout << endl << "! ERROR : �ð� ������ ������ �ֽ��ϴ�." << endl;
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
//		�� �Լ��� ����ð� ������ �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 21:49
// Author : ������
// mail : cleverhj94@naver.com
//
void timeNowUI::startInterface() {
	cout << "����ð� ���� ȭ��\n";
}

// Function : bool timeNowUI::inputDate()
//
// Description :
//		�� �Լ��� ����ð� ���� ��Ȳ���� ����ڷκ��� year, month, day�� �Է��� �޾� ���� �ð��� �����Ѵ�.
//
// Parameters : 
//
// Return Value : true�� ��ȯ
//
// Created : 2017/06/17 21:51
// Author : ������
// mail : cleverhj94@naver.com
//
// Revsions : 
//   1. When & Who : 2017/06/19 21:58 pm by Ȳ����
//      What : inputDate�Լ� ��ȯ�� ����  
bool timeNowUI::inputDate() {
	struct tm present;

	long countDays; // ���� �����κ��� ����� üũ

	//vote state���ſ� ���̴� ����
	long startDays, endDays;
	
	cout << "�� : ";
	cin >> present.tm_year;
	if (present.tm_year < 1 )
	{
		cout << endl << "! ERROR : �������� �Է°� �Դϴ�." << endl;
		return false;
	}
	cout << "�� : ";   
	cin >> present.tm_mon;
	if (present.tm_mon > 12 || present.tm_mon < 1)
	{
		cout << endl << "! ERROR : �������� �Է°� �Դϴ�." << endl;
		return false;
	}
	cout << "��:";
	cin >> present.tm_mday;
	if (present.tm_mday > 31 || present.tm_mday < 1)
	{
		cout << endl << "! ERROR : �������� �Է°� �Դϴ�." << endl;
		return false;
	}

	countDays = total_days(present.tm_year, present.tm_mon, present.tm_mday);

	timeNow = present;
	nowDays= countDays; // ��ǥ �ð��� ��

	cout << "����ð� : " << present.tm_year << "/" << present.tm_mon << "/" << present.tm_mday << "\n";

	//���Ž�, ��� Vote�� state�� �����Ѵ�.
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
				//4�ְ� ���� ��� ��ǥ ����
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
//		�� �Լ��� ���� �������� ��ǥ����Ʈ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 23:06
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void ongoingVoteShowUI::startInterface(){
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "4.1. ���� �������� ��ǥ ����Ʈ" << endl;
}

// void ongoingVoteShowUI::selectProgressingVote()-------------------------------------------------------------------
// Function : void ongoingVoteShowUI::selectProgressingVote()
//
// Description :
//		�� �Լ��� ���� �������� ��ǥ����Ʈ�� ����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/17 23:13
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void ongoingVoteShowUI::selectProgressingVote() {
	VoteManager::getProgressingVote();
}

// void scheduledVoteShowUI::startInterface()-------------------------------------------------------------------
// Function : void scheduledVoteShowUI::startInterface()
//
// Description :
//		�� �Լ��� ����� ������ ��ǥ����Ʈ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:13
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void scheduledVoteShowUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "4.3. ���� ���� ������ ��ǥ ����Ʈ" << endl;
}

// void scheduledVoteShowUI::selectScheduledVote()-------------------------------------------------------------------
// Function : void scheduledVoteShowUI::selectScheduledVote()
//
// Description :
//		�� �Լ��� ���� ������ ��ǥ����Ʈ�� ����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:15
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void scheduledVoteShowUI::selectScheduledVote() {
	VoteManager::getScheduledVote();
}

// void endedVoteShowUI::startInterface()-------------------------------------------------------------------
// Function : void endedVoteShowUI::startInterface()
//
// Description :
//		�� �Լ��� ����� ��ǥ����Ʈ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:25
// Author : Ȳ����
// mail : dngus8549@naver.com	
//
void endedVoteShowUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "4.4. ����� ��ǥ ����Ʈ" << endl;
}

// void endedVoteShowUI::selectProgressingVote()-------------------------------------------------------------------
// Function : void endedVoteShowUI::selectEndedVote()
//
// Description :
//		�� �Լ��� ����� ��ǥ����Ʈ�� ����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:27
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void endedVoteShowUI::selectEndedVote() {
	VoteManager::getEndedVote();
}

// void toVoteUI::startInterface()-------------------------------------------------------------------
// Function : void toVoteUI::startInterface()
//
// Description :
//		�� �Լ��� ��ǥ ��Ȳ�� �������̽��� �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:31
// Author : Ȳ����
// mail :dngus8549@naver.com
//
void toVoteUI::startInterface() {
	cout << endl << "=====================================================================" << endl;
	cout << "@ ���� Session : " << member.getMemberID() << endl;
	cout << endl << "4.2. ��ǥ" << endl;
}

// void toVoteUI::toVote()-------------------------------------------------------------------
// Function : void toVoteUI::toVote()
//
// Description :
//		�� �Լ��� ��ǥ�� ������ �����ϴ� �Լ��̴�.
//
// Parameters : 
//
// Return Value :
//
// Created : 2017/06/19 22:32
// Author : Ȳ����
// mail : dngus8549@naver.com
//
void toVoteUI::toVote() {
	string selectedVote;
	cout << "��ǥ�� ���� : ";
	cin >> selectedVote;
	VoteManager::toVote(selectedVote);
}

// ��Ÿ �Լ�----------------------------------------------------------------------------------------------------------

// Function : string getCurrentSessionName()
// Description: ���� �α����� ȸ���� �̸��� ��ȯ�Ѵ�.
// Parameters :   x
// Return Value :  member_ID
//
// Created: 2017/6/17 15:10
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
// Revsions : x
// 
string getCurrentSessionName() {
	return member.getMemberID();
}

// Function : int getCurrentSessionType()
// Description: ���� �α����� ȸ���� Ÿ���� ��ȯ�Ѵ�.
// Parameters :   x
// Return Value :  member_Type
//
// Created: 2017/6/17 15:55
// Author: �ǿ���
// mail: wkqlwja2@gmail.com
// 
int getCurrentSessionType() {
	return member.getMemberType();
}

// Function : long total_days(int year, int month, int day)
// Description: �����Ϸκ��� ��¥ ����� ����ϴ� �Լ�,
// Parameters :   int year, int month, int day
// Return Value :  long days - ������� ��ȯ
//
// Created: 2017/06/17
// Author: ������
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
