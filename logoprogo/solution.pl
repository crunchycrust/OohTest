%19. ����������, ������� � ������� ����� �� ����� �����. 
%���� �� ��� ������, ������  �����, ������  �������������. 
%������� ����� ����� ��������� ������ ��������� ������� ������� ���-��� ��� ����� ��������, 
%�� ��� �������, ��� ������ �������� � ���� ��������������. 
%�������� �����, ��� ������� ������� �� ������ � ��������. ��� ��� ����������? 

prof(plumber).
prof(carpenter).
prof(painter).

knows(painter, carpenter).
knows(carpenter, painter).

knownot(painter, plumber).

difcheck([Con, Dav, Fed]) :-
	Con \== Dav,
	Dav \== Fed,
	Con \== Fed.	

solution([Con, Dav, Fed]) :-
	prof(Pr1), prof(Pr2), prof(Pr3),
	Con = Pr1, Dav = Pr2, Fed = Pr3,
	Aaa = [Con, Dav, Fed],
	difcheck(Aaa),
	knownot(Fed, Dav), not(knows(Fed, Dav)).