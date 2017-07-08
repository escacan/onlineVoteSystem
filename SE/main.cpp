#include "class.h"

using namespace std;

bool timeSetting = false;

//�׷����
string group_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();
	int sessionType = getCurrentSessionType();

	while (end_input != 1) {
		sessionName = getCurrentSessionName();
		sessionType = getCurrentSessionType();

		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "�׷����" << endl;
		cout << "5.1. ��ü�׷� ��ȸ\n";
		cout << "5.2. �׷� ����\n";
		cout << "5.3. �׷� ����\n";
		cout << "5.4. ���Ա׷� ��ȸ\n";
		cout << "5.5. �׷� Ż��\n";
		cout << "0. ���� �޴��� ���ư���\n";
		cout << "* �Է¼��� : ";

		cin >> input;

		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� :  ";
			cin >> input;
		}

		switch (input) {
		case 1:
			listGroupUI::startInterface();
			listGroupUI::showGroupList();
			break;

		case 2:
			if (sessionType != 1) {
				cout << endl << "!ERROR : ���� Session������ �׷� ������ �Ұ��մϴ�." << endl;
				break;
			}
			joinGroupUI::startInterface();
			joinGroupUI::selectGroup();

			break;

		case 3:
			if (sessionType != 1) {
				cout << endl << "!ERROR : ���� Session������ �׷� ������ �Ұ��մϴ�." << endl;
				break;
			}
			createGroupUI::startInterface();
			createGroupUI::inputNewname();
			break;

		case 4:
			if (sessionType == 2 || sessionType == 3) {
				listJoinedGroupUI::startInterface();
				listJoinedGroupUI::getJoinedGroup();
				break; // joinedGroupUI�� ������ ��.
			}
			else {
				cout << endl << "!ERROR : ������ �׷��� �����ϴ�." << endl;
				break;
			}
		case 5:
			if (sessionType == 2) { //�׷찡��ȸ���� Ż�𰡴�
				groupWithdrawUI::startInterface();
				groupWithdrawUI::withdraw();
				break; // joinedGroupUI�� ������ ��.
			}
			else {
				cout << endl << "!ERROR : ���� Session������ �׷� Ż�� �Ұ����մϴ�." << endl;
				break;
			}
		case 0:
			end_input = 1;
			break;

		default:
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//�α��� �α׾ƿ�
string login_logout_ui() {
	int input;
	string choice;
	int end_input = 0;
	string sessionName = getCurrentSessionName();

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "Login / Logout" << endl;
		cout << "1.1. Login\n";
		cout << "1.2.Logout\n";
		cout << "0. ���� �޴��� ���ư���\n";
		cout << "* �Է¼��� : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//Session ����/ ����
string session_ui() {
	int input;
	string choice;
	int end_input = 0;
	string sessionName = getCurrentSessionName();

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "Session ����/����" << endl;
		cout << "7.1.Session ����/����\n";
		cout << "0. ���� �޴��� ���ư���\n";
		cout << "* �Է¼��� : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}
	return getCurrentSessionName();
}

//ȸ�� ����      0617 1347 ����.
string member_ui() {
	int input;
	int end_input = 0;

	while (end_input != 1) {
		string sessionName = getCurrentSessionName(); // 0617 ����
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "ȸ������/Ż��" << endl;
		cout << "1. ȸ������\n2. ȸ��Ż��\n";
		cout << "0. ���� �޴��� ���ư���\n* �Է¼��� : ";

		cin >> input;

		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state��������� ����
}

//��ǥ����
string vote_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // ���� �ʿ�

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "3. ��ǥ����" << endl;
		cout << "3.1. ��ǥ����\n";
		cout << "0. ���� �޴��� ���ư���\n* �Է¼��� : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state��������� ����
}

//��ǥ����
string vote_manage_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // ���� �ʿ�

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "4. ��ǥ����" << endl;
		cout << "4.1. ���� �������� ��ǥ����Ʈ\n";
		cout << "4.2. ��ǥ\n";
		cout << "4.3.���� ���� ������ ��ǥ ����Ʈ\n";
		cout << "4.4.����� ��ǥ����Ʈ\n";
		cout << "0. ���� �޴��� ���ư���\n* �Է¼��� : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state��������� ����
}


string timeNow_ui() {
	int input;
	int end_input = 0;
	string sessionName = getCurrentSessionName();  // ���� �ʿ�

	while (end_input != 1) {
		cout << endl << "=====================================================================" << endl;
		cout << "@ ���� Session : " << sessionName << endl;
		cout << endl << "����ð� ����" << endl;
		cout << "6.1. ����ð� ����\n";
		cout << "0. ���� �޴��� ���ư���\n* �Է¼��� : ";

		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
			cout << endl << "!ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;
		}
	}

	return getCurrentSessionName(); // session state��������� ����
}


int main() {
	int input;
	int end_input = 0; // ����� �Է�
	bool currentState = 0; // 1�� �α��� ����.
	string sessionName = "Guest";
	int sessionType = 0;

	while (end_input != 1) {
		sessionType = getCurrentSessionType();
		sessionName = getCurrentSessionName();
		cout << "�¶��� ��ǥ �ý���\n";
		cout << "\n\n";
		cout << "���� Session : " << sessionName << "\n";

		cout << "1. ȸ������/Ż��\n";
		cout << "2. �α���/�α׾ƿ�\n";
		cout << "3. ��ǥ����\n";
		cout << "4. ��ǥ����\n";
		cout << "5. �׷����\n";
		cout << "6. ����ð� ����\n";
		cout << "7. Session ����/����\n";
		cout << "8. ����\n";
		cout << "*�Է� ���� : ";
		cin >> input;
		if (cin.fail())
		{
			cout << "wrong num!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "*�Է� ���� : ";
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
					cout << endl << "! ERROR : ���� �ð��� �����ؾ� �մϴ�." << endl;
					break;
				}
			}
			else {
				cout << endl << "! ERROR : ��ǥ ������ �����ϴ�." << endl;
				break;
			}
		case 4:
			if (sessionType == 0 || sessionType == 1) {
				cout << endl << "! ERROR : ���� ������ �����ϴ�." << endl;
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
				cout << endl << "! ERROR : �ð� ���� ������ �����ϴ�." << endl;
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
			cout << endl << "! ERROR : �ùٸ� ��ȣ�� �Է����ּ���" << endl;
			break;            //���� �Է½� ���ѷ���
		}
	}
	return 0;
}