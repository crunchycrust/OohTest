:- consult('pred.pl').

child(X, Y) :- parent(Y, X).

married(X, Y) :- child(Z, Y), !, child(Z, X), X \= Y.
married('Shakespeare Elizabeth', 'Nash Thomas').
married('Nash Thomas', 'Shakespeare Elizabeth').
married('Shakespeare Elizabeth', 'Barnard John').
married('Barnard John', 'Shakespeare Elizabeth').

father(X, Y) :- sex(X, m), parent(X, Y).
mother(X, Y) :- sex(X, f), parent(X, Y).

sibling(Sib, Pe) :- father(Pa, Pe), !, father(Pa, Sib), Sib \= Pe.
sibling(Sib, Pe) :- mother(Pa, Pe), mother(Pa, Sib), Sib \= Pe.

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
ggp(X, Y) :- grandparent(X, Z), parent(Z, Y).

minlaw(X, Y) :- married(Z, Y), mother(X, Z).
finlaw(X, Y) :- married(Z, Y), father(X, Z).

anc(A, P) :- parent(A, P).
anc(A, P) :- parent(Z, P), anc(A, Z).

des(D, P) :- parent(P, D).
des(D, P) :- parent(P, Z), des(D, Z).

relative(sister, P, Sis) :- sibling(Sis, P), sex(Sis, f). 
relative(brother, P, Bro) :- sibling(Bro, P), sex(Bro, m).
relative(father, P, Dad) :- father(Dad, P).
relative(mother, P, Mom) :- mother(Mom, P).
relative(son, P, Son) :- parent(P, Son), sex(Son, m).
relative(daughter, P, Dau) :- parent(P, Dau), sex(Dau, f).
relative(child, P, Chi) :- parent(P, Chi).
relative(aunt, P, Aunt) :- parent(Pa, P), relative(sister, Pa, Aunt).
relative(uncle, P, Uncle) :- parent(Pa, P), relative(brother, Pa, Uncle).
relative(niece, P, Niece) :- relative(daughter, Pa, Niece), sibling(Pa, P).
relative(cousin, P, Cousin) :- relative(son, Pa, Cousin), sibling(Pa, P).
relative(grandmother, P, Gp) :- grandparent(Gp, P), sex(Gp, f).
relative(grandfather, P, Gp) :- grandparent(Gp, P), sex(Gp, m).
relative(greatgrandmother, P, Ggp) :- ggp(Ggp, P), sex(Ggp, f).
relative(greatgrandfather, P, Ggp) :- ggp(Ggp, P), sex(Ggp, m).
relative(grandson, P, Gs) :- grandparent(P, Gs), sex(Gs, m).
relative(granddaughter, P, Gd) :- grandparent(P, Gd), sex(Gd, f).
relative(motherinlaw, P, Mil) :- minlaw(Mil, P).
relative(fatherinlaw, P, Fil) :- finlaw(Fil, P).
relative(brotherinlaw, P, Bil) :- married(M, P), relative(brother, M, Bil).
relative(sisterinlaw, P, Sil) :- married(M, P), relative(sister, M, Sil).
relative(soninlaw, P, Sil) :- relative(daughter, P, Z), married(Sil, Z).
relative(daughterinlaw, P, Dil) :- relative(son, P, Z), married(Dil, Z).
relative(married, P, M) :- married(M, P).
%relative(ancestor, P, A) :- anc(A, P).
%relative(descendent, P, D) :- des(D, P).



filist([Now|T], [Goal, Now|T], Goal) :- 
	relative(_, Now, Goal).
filist([Now|T], [New, Now|T], _) :-
	relative(_, Now, New),
	not(member(New, [Now|T])).

finame([[Goal|T]|_], Goal, [Goal|T]) :- !.
finame([Now|BeforeNow], Goal, Res) :-
	findall(X, filist(Now, X, Goal), L),
	append(BeforeNow, L, CBN),
	finame(CBN, Goal, Res).

relatednames(P1, P2, List) :-
	finame([[P1]], P2, L),
	reverse(L, List).

rlist([_], []) :- !.
rlist([X, Y|T], List) :- 
	relative(Rel, X, Y), 
	rlist([Y|T],L1),
	List = [Rel|L1], !. 

relist(X, Y, List) :- 
	relatednames(X, Y, L1), 
	rlist(L1, List). 

relation(X, Y, List) :- relist(X, Y, List).
relation(X, Y, List) :- relatednames(X, Y, List).



%natural langauge
pronouns('he'). 
pronouns('him').
pronouns('she').
pronouns('her'). 
pronouns('they').
pronouns('them').

question('How', 'many').
question('Who', 'is', 'to').
verbphrase('does', 'have').

mark('?').

rel('brother', 'brother').
rel('sister', 'sister').
rel(Rel, X) :-
	Rel = 'brothers',
	X = 'brother'.
rel(Rel, X) :-
	Rel = 'sisters',
	X = 'sister'.

writeo(Rel, P1, P2) :- Rel = married, format('~w is married to ~w.', [P1, P2]).
writeo(Rel, P1, P2) :- (Rel = aunt; Rel = uncle), format('~w is an ~w to ~w', [P1, Rel, P2]).
writeo(Rel, P1, P2) :- format('~w is a ~w to ~w.', [P1, Rel, P2]).

writeoo(Rel, N, P) :-
	N < 2, !,
	rel(Rel, W),
	format('~w has ~w ~w.',[P, N, W]).
writeoo(Rel, N, P) :-
	format('~w has ~w ~w.',[P, N, Rel]).

% How many brothers\sisters does P have?
q([Q, Qua, Rel, Auxv, P, V, M]) :-
	question(Q, Qua),
	verbphrase(Auxv, V),
	mark(M),
	rel(Rel, W),
	sex(P, _),
	nb_setval(real, P),

	setof(X, relative(W, P, X), L),
	length(L, Fin),
	writeoo(Rel, Fin, P).

q([Q, Qua, Rel, Auxv, P, V, M]) :-
	question(Q, Qua),
	verbphrase(Auxv, V),
	mark(M),
	rel(Rel, W),
	pronouns(P),
	nb_getval(real, Name),

	setof(X, relative(W, Name, X), L),
	length(L, Fin),
	writeoo(Rel, Fin, Name).

%who is P1 to P2?
q([Q, Link, P1, To, P2, M]) :-
	question(Q, Link, To),
	mark(M),
	sex(P1, _), sex(P2, _),
	nb_setval(real, P2),

	relative(Rel, P2, P1),
	writeo(Rel, P1, P2).

q([Q, Link, P1, To, P2, M]) :-
	question(Q, Link, To),
	mark(M),
	pronouns(P1),
	nb_getval(real, Name),

	relative(Rel, P2, Name),
	writeo(Rel, Name, P2).

q([Q, Link, P1, To, P2, M]) :-
	question(Q, Link, To),
	mark(M),
	pronouns(P2),
	nb_getval(real, Name),

	relative(Rel, Name, P1),
	writeo(Rel, P1, Name).