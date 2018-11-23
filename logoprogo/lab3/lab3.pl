move(A,B):-
	append(End, ["_", X|Tail], A),
	append(End, [X, "_"|Tail], B).

move(A,B):-
	append(End, [X, "_"|Tail], A),
	append(End, ["_", X|Tail], B).

move(A, B) :-
	append(End, [X, F1, F2, F3, F4, "_"|T], A),
	append(End, ["_", F1, F2, F3, F4, X|T], B).

move(A, B) :-
	append(End, ["_", F1, F2, F3, F4, X|T], A),
	append(End, [X, F1, F2, F3, F4, "_"|T], B).

move(A, B) :-
	append(End, [X, F1, F2, "_"|T], A),
	append(End, ["_", F1, F2, X|T], B).

move(A, B) :-
	append(End, ["_", F1, F2, X|T], A),
	append(End, [X, F1, F2, "_"|T], B).

writeo([]).
writeo([Finish|Start]) :- writeo(Start), write(Finish), nl.

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
	writeo(Res),
	get_time(T2), nl, 
	T is T2 - T1,
	write('TIME: '), write(T), nl, nl.

bf([[Goal|T]|_], Goal, [Goal|T]).
bf([Now|BeforeNow], Goal, Res):-
    	findall(X, findchildren(Now, X), Children),
    	append(BeforeNow, Children, CBN),
    	bf(CBN, Goal, Res).

roomBF(Initial, Final) :-
    	nl, write('Breadth-first search'), nl, nl,
    	get_time(T1),
    	bf([[Initial]], Final, Res),	
    	writeo(Res),
    	get_time(T2), nl,
    	T is T2 - T1,
    	write('TIME: '), write(T), nl, nl.

id([Goal|T], Goal, [Goal|T], _).
id(Now, Goal, Res, Bound):- 
	Bound > 0,
	findchildren(Now, Next),
	NBound is Bound-1,
	id(Next, Goal, Res, NBound).

expbound(X, X).
expbound(B, X):-
	X1 is X + 1,
	expbound(B, X1).

roomI(Initial, Final) :-
	nl, write('Iterative deepening search'), nl, nl,
	get_time(T1),
	expbound(Bound, 1),
	id([Initial], Final, Res, Bound),
	writeo(Res),
	get_time(T2), nl,
	T is T2 - T1,
	write('TIME: '), write(T), nl, nl.
