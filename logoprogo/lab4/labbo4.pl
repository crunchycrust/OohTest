person("Irene").
person("Alex").
person("Peter").
person("Yuna").
person("Anna").
person("Sam").

%cona("and").
%we don't actually need it, because
%'but' determines everything
but("but").

naction("does").
naction("not").
naction("like").
action("likes").

object("toys").
objects("poems").
objects("songs").
objects("flowers").
objects("bananas").
objects("autumn").
objects("summer").
objects("spring").
objects("winter").
objects("bears").
objects("frogs").
objects("reports").
objects("silence").
objects("peaches").
objects("pigeons").
objects("horses").

%whether we have likes/dislikes in our sentence
%and where to start checking for exact preferences
like(A, B) :-
	append(_, ["likes"|T], A),
	B = T.
dislike(A, B) :-
	append(_, ["does", "not", "like"|T], A),
	B = T.

%is it an object?.. or is it an 'and'??
obj([H|_], O, _) :-
	objects(H),
	O = H.
obj([_|T], O, P) :- conj(T, O, P).

%but conjunction check
conj([H|T], O, P) :-
	not(but(H)), !, 
	obj([H|T], O, P).

%we have to make these deep structures, right?
up(L, likes(P, O), P) :-
	conj(L, O, P).	

down(L, doesnotlike(P, O), P) :-
	conj(L, O, P).

%using like/dislike & up/down.
check(P, L, X) :-
	like(L, T), up(T, X, P).
check(P, L, X) :-
	 dislike(L, T), down(T, X, P).

%main predicate
decompose([H|T], X) :-
	person(H),
	check(H, T, X).