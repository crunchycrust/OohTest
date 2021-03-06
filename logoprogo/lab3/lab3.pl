move(A,B):-
	append(E, ["_", X|Tail], A),
	append(E, [X, "_"|Tail], B).

move(A,B):-
	append(E, [X, "_"|Tail], A),
	append(E, ["_", X|Tail], B).

move(A, B) :-
	append(E, [X, F1, F2, "_"|T], A),
	append(E, ["_", F1, F2, X|T], B).

move(A, B) :-
	append(E, ["_", F1, F2, X|T], A),
	append(E, [X, F1, F2, "_"|T], B).

writeo([]).
writeo([H|T]) :-  write(H), nl, writeo(T).

findchildren([Now|T], [Child, Now|T]) :-
    	move(Now, Child),
    	not(member(Child,[Now|T])).

df([Goal|T], Goal, [Goal|T]).
df(Now, Goal, Res) :-
	findchildren(Now, X),
	df(X, Goal, Res).
 
roomDF(Initial, Final) :-
	nl, write('Depth-first search'), nl, nl, 
    	get_time(T1),
	df([Initial], Final, Res),
	reverse(Res, Ref),
	writeo(Ref),
	get_time(T2), nl, 
	T is T2 - T1,
	write('TIME: '), write(T), nl, nl.

bf([[Goal|T]|_], Goal, [Goal|T]).
bf([Now|BeforeNow], Goal, Res) :-
    	findall(X, findchildren(Now, X), Children),
    	append(BeforeNow, Children, CBN),
    	bf(CBN, Goal, Res).

roomBF(Initial, Final) :-
    	nl, write('Breadth-first search'), nl, nl,
    	get_time(T1),
    	bf([[Initial]], Final, Res),
	reverse(Res, Ref),	
    	writeo(Ref),
    	get_time(T2), nl,
    	T is T2 - T1,
    	write('TIME: '), write(T), nl, nl.

id([Goal|T], Goal, [Goal|T], _).
id(Now, Goal, Res, Bound) :- 
	Bound > 0,
	findchildren(Now, Next),
	NBound is Bound-1,
	id(Next, Goal, Res, NBound).

expbound(X, X).
expbound(B, X) :-
	X1 is X + 1,
	expbound(B, X1).

roomI(Initial, Final) :-
	nl, write('Iterative deepening search'), nl, nl,
	get_time(T1),
	expbound(Bound, 1),
	id([Initial], Final, Res, Bound),
	reverse(Res, Ref),
	writeo(Ref),
	get_time(T2), nl,
	T is T2 - T1,
	write('TIME: '), write(T), nl, nl.
