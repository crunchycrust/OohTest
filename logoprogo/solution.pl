%19. Кондратьев, Давыдов и Федоров живут на нашей улице. 
%Один из них столяр, другой  маляр, третий  водопроводчик. 
%Недавно маляр хотел попросить своего знакомого столяра сделать кое-что для своей квартиры, 
%но ему сказали, что столяр работает в доме водопроводчика. 
%Известно также, что Федоров никогда не слышал о Давыдове. Кто чем занимается? 


prof(carpenter).
prof(painter).
prof(plumber).

knows(painter, carpenter).
knows(carpenter, painter).

knownot(painter, plumber).

solution([Con, Dav, Fed]) :-
	prof(Pr1), prof(Pr2), Pr1 \== Pr2,
	prof(Pr3), Pr2 \== Pr3, Pr1 \== Pr3,
	Con = Pr1, Dav = Pr2, Fed = Pr3,
	knownot(Fed, Dav), not(knows(Fed, Dav)).
