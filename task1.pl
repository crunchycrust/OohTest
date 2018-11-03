% Часть 1: Предикаты работы со списками

% 3. Реализация стандартных предикатов обработки списков.

%membero: 1) X is a member of any list whose head is X;
%	  2) if X is a member of Y(Tail), X is a member of any list whose tail is Y(Tail). 
membero(X, [X|_]).
membero(X, [_|Y]) :-
	membero(X, Y).

%appendo: 1) appending any list X to the empty list results in X list;
%	  2) if appending Z to Y results in W, appending Z to [X|Y] results in [X|W].
appendo([], X, X).
appendo([X|Y], Z, [X|W]) :-
	appendo(Y, Z, W).

%lengtho: 1) the length of the empty list is 0;
%	  2) if the length of a X is N1 and N = N1+1, the list of any head and of X tail has the length of N.
lengtho([], 0).
lengtho([_|X], N) :-
	lengtho(X, N1),
	N is N1+1.

%removeo: 1) if X is the head of the list, then tail is the list without X;
%	  2) if Z is a list without X as the head(T without X), then removal X from [Y|T] results in [Y|Z].  
removeo(X, [X|T], T).
removeo(X, [Y|T], [Y|Z]) :-
	removeo(X, T, Z).

%permuteo: 1) if both lists are empty, all is well;
%	   2) if Tail of our 'asked' list is a permuted Y list, which is a X without H from our 'asked' list, then X is a permutation of the 'asked' list. 
permuteo([], []).
permuteo([H|T], X) :-
    permuteo(T, Y),
    removeo(H, X, Y).

%sublisto: 1) empty list is a sublist of its own;
%	   2) if we get L by appending smth1 to L1 (smthL1) and if we get L1 by appending X to sth2 (Xsth2), then X is a sublist of L list (sth1Xsth2 = L).
sublisto([], []).
sublisto(X, L):-
	appendo(_, L1, L), 
	appendo(X, _, L1).

% Предикаты обработки списков.
% 4. Получение последнего элемента (without basic predicates)
%lasto: 1) if there is only X in the list, then X is the last element;
%	2) if X is the last element of T, then X is the last element of [_|T] (of any head).
lasto([X], X).
lasto([_|T], X) :-
	lasto(T, X).

% 4. Получение последнего элемента (with basic predicates)
% lastoo: if Z is the concatenation of sth and [X](list consisting only of X), then X is the last element. 
lastoo(Z, X) :- 
	append(_, [X], Z).

% Предикаты обработки числовых списков. 
% 5. Вычисление скалярного произведения двух векторов-списков 
%(с учетом возможного несовпадения размерностей) (without basic predicates)

%complen: does L1 has the length of L2? do they HAVE the Same leNGth??
complen(L1, L2) :-
	lengtho(L1, N),
	lengtho(L2, C),
	N =:= C.

%ssum: multiplies H1 by H2, does the same for H1s and H2s of all tails, adds up all that to get X.
ssum([], [], 0). %needed for X1 to start at 0
ssum([H1|T1], [H2|T2], X) :-
	C is H1*H2,
	ssum(T1, T2, X1),
	X is X1 + C. 	

%scalar: if the length is the same + not 0 and if X is a ssum of L1, L2, then X is the scalar product of L1 and L2.
scalar(L1, L2, X) :-
	complen(L1, L2),
	ssum(L1, L2, X).

% 5. Вычисление скалярного произведения двух векторов-списков 
%(с учетом возможного несовпадения размерностей) (with basic predicates)
scalar1(L1, L2, X) :-
	same_length(L1, L2),
	ssum(L1, L2, X).
	
% 6. Содержательный пример совместного использования предикатов, реализованных в пунктах 3 и 4.
% Remove the last element from the list.
removel(L, X) :-
	lasto(L, N),
	removeo(N, L, X).
