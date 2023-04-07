#pragma once
#include <iostream>
#include <string>
#include <queue>
#include "clsDate.h"

using namespace std;

class clsQueueLine
{
private:
	string _LinePrefix;
	short _ClientServiceTime;
	short _TotalTickets = 0;
	short _ServedClients = 0;
	short _WaitingClients = 0;

	class _clsTicket {
	private:
		string _TicketNum;
		string _Time;
		short _WaitingClients;
	public:

		void SetTicketNum(string TicketNum) {
			_TicketNum = TicketNum;
		}

		string GetTicketNum() {
			return _TicketNum;
		}

		__declspec(property(get = GetTicketNum, put = SetTicketNum)) string TicketNum;

		void SetTime(string Time) {
			_Time = Time;
		}

		string GetTime() {
			return _Time;
		}

		__declspec(property(get = GetTime, put = SetTime)) string Time;

		void SetWaitingClients(short WaitingClients) {
			_WaitingClients = WaitingClients;
		}

		short GetWaitingClients() {
			return _WaitingClients;
		}

		__declspec(property(get = GetWaitingClients, put = SetWaitingClients)) short WaitingClients;

	};

	queue <_clsTicket> Line;

	_clsTicket Ticket;

	void PrintTicketInfo(_clsTicket Ticket) {
		cout << "\n\t\t\t_________________________";
		cout << "\n\t\t\t\t   " << Ticket.TicketNum;
		cout << "\n\t\t\t   " << Ticket.GetTime();
		cout << "\n\t\t\t   Waiting Clients : " << Ticket.WaitingClients;
		cout << "\n\t\t\t   Serve Time in   : " << Ticket.WaitingClients * _ClientServiceTime;
		cout << "\n\t\t\t_________________________";
	}
public:

	clsQueueLine(string LinePrefix, short ClientServiceTime) {
		_LinePrefix = LinePrefix;
		_ClientServiceTime = ClientServiceTime;
	}

	void IssueTicket() {
		clsDate Date;
		_TotalTickets++;
		Ticket.TicketNum = _LinePrefix + to_string(_TotalTickets);
		Ticket.Time = clsDate::DateToString(Date);
		Ticket.WaitingClients = _WaitingClients;
		Line.push(Ticket);
		_WaitingClients++;	
	}

	void ServeNextClient() {
		Line.pop();
		_ServedClients++;
		_WaitingClients--;
	}

	void PrintInfo() {
		cout << "\n\t\t\t_________________________";
		cout << "\n\t\t\t   Prefix          : "<<_LinePrefix;
		cout << "\n\t\t\t   Total Tickets   : "<<_TotalTickets;
		cout << "\n\t\t\t   Served Clients  : "<<_ServedClients;
		cout << "\n\t\t\t   Waiting Clients : "<<_TotalTickets-_ServedClients;
		cout << "\n\t\t\t_________________________";
	}

	void PrintAllTickets() {
		queue <_clsTicket> VirtualLine = Line;
		for (short i = 0; i < Line.size(); i++) {
			PrintTicketInfo(VirtualLine.front());
			VirtualLine.pop();
		}
	}

};

