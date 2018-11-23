%19. Кондратьев, Давыдов и Федоров живут на нашей улице. 
%Один из них столяр, другой  маляр, третий  водопроводчик. 
%Недавно маляр хотел попросить своего знакомого столяра сделать кое-что для своей квартиры, 
%но ему сказали, что столяр работает в доме водопроводчика. 
%Известно также, что Федоров никогда не слышал о Давыдове. Кто чем занимается? 


prof(carpenter).
prof(painter).
prof(plumber).

heard(painter, carpenter).
heard(carpenter, painter).
heard(carpenter, plumber).
heard(plumber, carpenter).

heard(painter, plumber).

solution([Con, Dav, Fed]) :-
	prof(Pr3), prof(Pr2), Pr3 \== Pr2,
	Fed = Pr3, Dav = Pr2,
	not(heard(Fed, Dav)),
	prof(Pr1), Pr3 \== Pr1, Pr2 \== Pr1, 
	Con = Pr1.
