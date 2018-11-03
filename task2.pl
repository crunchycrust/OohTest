% ����� 2: ����������� ������������� ���������� �������
% ������������� ������ � ��������� �� four.pl
% ������� 3

subject('���������� ����������������', [grade('������',4),grade('����������',2),grade('������',5),grade('����������',5),grade('����������',5),grade('�������',2),grade('��������',4),grade('���������',4),grade('��������',3),grade('������������',4),grade('�����������',4),grade('�����',2),grade('���������������',5),grade('�����',3),grade('����',5),grade('����������',5),grade('������',5),grade('���������������',4),grade('����������',5),grade('������',4),grade('�����������',4),grade('������������',5),grade('�����������������',5),grade('����������������',5),grade('����������',3),grade('������',5),grade('�����������',5),grade('���������������',3)]).

subject('�������������� ������',[grade('������',2),grade('����������',4),grade('������',4),grade('����������',4),grade('����������',4),grade('�������',5),grade('��������',4),grade('���������',5),grade('��������',4),grade('������������',5),grade('�����������',3),grade('�����',4),grade('���������������',3),grade('�����',5),grade('����',4),grade('����������',3),grade('������',4),grade('���������������',4),grade('����������',5),grade('������',3),grade('�����������',4),grade('������������',4),grade('�����������������',5),grade('����������������',4),grade('����������',3),grade('������',5),grade('�����������',4),grade('���������������',5)]).

subject('�������������� ����������������',[grade('������',3),grade('����������',5),grade('������',4),grade('����������',3),grade('����������',3),grade('�������',3),grade('��������',4),grade('���������',5),grade('��������',5),grade('������������',5),grade('�����������',4),grade('�����',5),grade('���������������',5),grade('�����',5),grade('����',4),grade('����������',5),grade('������',3),grade('���������������',3),grade('����������',4),grade('������',4),grade('�����������',3),grade('������������',4),grade('�����������������',4),grade('����������������',5),grade('����������',5),grade('������',4),grade('�����������',4),grade('���������������',4)]).

subject('�����������',[grade('������',4),grade('����������',3),grade('������',3),grade('����������',4),grade('����������',3),grade('�������',4),grade('��������',4),grade('���������',4),grade('��������',3),grade('������������',2),grade('�����������',4),grade('�����',5),grade('���������������',4),grade('�����',5),grade('����',3),grade('����������',4),grade('������',5),grade('���������������',5),grade('����������',4),grade('������',4),grade('�����������',3),grade('������������',5),grade('�����������������',3),grade('����������������',2),grade('����������',4),grade('������',5),grade('�����������',4),grade('���������������',4)]).

subject('���������� ����',[grade('������',4),grade('����������',5),grade('������',3),grade('����������',4),grade('����������',4),grade('�������',5),grade('��������',3),grade('���������',5),grade('��������',5),grade('������������',5),grade('�����������',4),grade('�����',4),grade('���������������',3),grade('�����',5),grade('����',4),grade('����������',3),grade('������',4),grade('���������������',4),grade('����������',2),grade('������',4),grade('�����������',4),grade('������������',5),grade('�����������������',5), grade('����������������',5), grade('����������',3),grade('������',2),grade('�����������',4),grade('���������������',4)]).

subject('����������',[grade('������',5),grade('����������',3),grade('������',3),grade('����������',3),grade('����������',5),grade('�������',3),grade('��������',5),grade('���������',4),grade('��������',5),grade('������������',5),grade('�����������',3),grade('�����',4),grade('���������������',4),grade('�����',4),grade('����',4),grade('����������',2),grade('������',3),grade('���������������',2),grade('����������',4),grade('������',3),grade('�����������',3),grade('������������',5),grade('�����������������',4),grade('����������������',5),grade('����������',5),grade('������',3),grade('�����������',5),grade('���������������',4)]).


group(102,['������','����������','���������','������','������','�����������','����������������','������','���������������']).

group(101,['����������','�������','�����','����������','�����������������']).

group(104,['������','����������','�����','����','���������������','����������']).

group(103,['��������','��������','������������','�����������','���������������','����������','������������','�����������']).

% 1.1) ��� ������� ��������, ����� ������� ����

studsearch([], _, 0).
studsearch([grade(X, Y)|T], Stud, M) :-
	X == Stud, !,
	studsearch(T, Stud, N),
	M is Y + N.
studsearch([_|T], Stud, N) :-
	studsearch(T, Stud, N).

avs(Stud, X) :-
	subject(_, Y),
	studsearch(Y, Stud, X).

average(Stud, S) :-
	bagof(X, avs(Stud, X), L),
	sum_list(L, SL),
	length(L, LL),
	S is SL / LL.

%1.2) ��� ������� ��������, ����� ���� �� �� �������� ��� ���

fcheck(Stud, Sub) :-
	subject(Sub, Y),
	studsearch(Y, Stud, M),
	M > 2.

% 2) ��� ������� ��������, ����� ���������� �� ������� ���������

fcount([], 0).
fcount([grade(_, Y)|T], C) :-
	Y < 3, !,
	fcount(T, N),
	C is N + 1.
fcount([_|T], N) :-
	fcount(T, N).

fail(Sub, X) :-
	subject(Sub, L),
	fcount(L, X).

% 3) ��� ������ ������, ����� �������� (���������) � ������������ ������� ������

avg([H|_], X) :-
	average(H, X).
avg([_|T], X) :-
	avg(T, X).

checkMax([], _, 0).	
checkMax([H|T], Max, LM) :-
	average(H, A),
	A =:= Max, !,
	checkMax(T, Max, LM),
	write(H), nl.
checkMax([_|T], Max, _) :-
	checkMax(T, Max, _).

gmax(N, X) :-
	group(N, Y),
	bagof(M, avg(Y, M), L),
	max_list(L, Max),
	checkMax(Y, Max, X).