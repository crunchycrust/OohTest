person("Irene").
person("Alex").
person("Peter").
person("Yuna").
person("Anna").
person("Sam").

objects("toys").
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

like(A, B) :-
	append(_, ["likes"|B], A).
dislike(A, B) :-
	append(_, ["does", "not", "like"|B], A).
butph(A, B) :-
	append(_, ["but"|B], A).
butph(A, B) :- 
	append(B, ["but"|_], A).

obj([H|_], H, _) :- objects(H).
obj([_|T], O, P) :- obj(T, O, P).

likeobj(L, likes(P, O), P) :-
	obj(L, O, P).	
dislikeobj(L, doesnotlike(P, O), P) :-
	obj(L, O, P).

butphrase(P, L, X) :-
	butph(L, T), verbphrase(P, T, X).
verbphrase(P, L, X) :-
	like(L, T), likeobj(T, X, P).
verbphrase(P, L, X) :-
	dislike(L, T), dislikeobj(T, X, P).

decompose([H|T], X) :-
	person(H),
	butphrase(H, T, X).
