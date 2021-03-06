# Отчет по курсовому проекту
## по курсу "Логическое программирование"

### студент: Савина А.А.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |               |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*

## Введение
В результате выполнения курсового проекта я надеюсь познакомиться с файлами в формате GEDCOM, научиться делать парсер, обрабатывающий текстовые данные, на Python и закрепить знания и навыки, полученные из лабораторных работ.
## Задание
 1. Создать родословное дерево своего рода на несколько поколений (3-4) назад в стандартном формате GEDCOM;  
 2. Преобразовать файл в формате GEDCOM в набор утверждений на языке Prolog, используя следующие предикаты: `parent(родитель, ребенок)`, `sex(человек, m/f)`;  
 3. Реализовать предикат проверки/поиска свекрови (mother-in-law);  
 4. Реализовать программу на языке Prolog, которая позволит определять степень родства двух произвольных индивидуумов в дереве;  
 5. Реализовать естественно-языковый интерфейс к системе, позволяющий задавать вопросы относительно степеней родства, и получать осмысленные ответы.  
## Получение родословного дерева
В данной работе используется родословное дерево of William Shakespeare. Изначально в нём было 23 человека, но я добавила в него ещё 16. 
Итого, в дереве [William Shakespeare Tree](shakespearever2.ged) 39 индивидуумов - 6 поколений.
## Конвертация родословного дерева
Для преобразования файла формата GEDCOM в набор утверждений на Прологе я решила использовать Python. На это было две причины.
Во-первых, он позволяет легко проводить обработку текста. Во-вторых, я с ним немного знакома (очень немного: только файлы из папки переименовывать умею. Ведь если названия однотипные и файлов много, то по одному, "руками" делать это долго и скучно).  

Итак, читаем мы из `"shakespearver2.ged"`, пишем в `"pred.pl"`.  
```python
with open("shakespearever2.ged", "r") as rf:
	with open("pred.pl", "w") as wf:
```
В конце программы закроем оба файла, конечно.
```python
wf.close() 
rf.close() 
```
Так как в GEDCOM каждому человеку сопоставлен свой ID, то при первом прохождении и преобразовании в предикаты вида `sex(человек, m/f)` будет необходимо создать словарь из имён.  
Такое представление будет удобнее потому, что в словарях информация представлена не как последовательность, а как набор пар. Наш словарь : 
```python
ID = {}
```
Идём построчно по файлу. Если попадается такое, что в строке до четвёртого символа попадается '0 @I', то  
PID (person ID) становится равным куску строки от 2 до 9 эл (9 не включается). Например, `@I0001@`.
Если line[2:6] (со 2й по 6ую) == 'GIVN', то givn (given name) = оставшейся части строки без пробелов в конце.  
Если попадается в заданных рамках 'SURN', surn (surname) = оставшейся части строки без пробелов в конце; name = surn, пробел и givn, а в словарь `ID` добавляется name с ключом PID.  
Если 'SEX', то sex = 6-ому символу, но не заглавной букве, а строчной. Тогда и можно определить предикат   
`sex(name, sex)` и распечатать его в `pred.pl`.  
```python
		for line in rf:
			if line[:4] == '0 @I':
				PID = line[2:9]
			elif line[2:6] == 'GIVN':
				givn = line[7:].rstrip()
			elif line[2:6] == 'SURN':
				surn = line[7:].rstrip()
				name = '\'' + surn + ' ' + givn + '\''
				ID[PID] = name
			elif line[2:5] == 'SEX':
				sex = line[6].lower()
				predicate = 'sex(' + name + ', ' + sex + ').\n'
				wf.write(predicate)
```
А теперь начинаем всё с начала. Но словарь `ID` уже не пустой.  
В файле GEDCOM ID есть не только у людей, но и ещё и у семей. И в семьях хранится информация об IDs родителей и ребёнка, поэтому начнём с поиска ID семей.  
Если в заданных рамках попадается '0 @F', то husb (husband) = ' ', wife = ' '. Они пока пустые, но необходимо их обозначить, чтобы искать дальше.  
Если 'HUSB', то HID (husband ID) = оставшейся строчке без пробелов в конце, а husb = name из словаря с ключом HID.  
Если 'WIFE', то WID (wife ID) = оставшейся строчке без пробелов в конце, а wife = name из словаря с ключом WID.  
Если 'CHIL', то CID (child ID) = оставшейся строчке без пробелов в конце, а child = name из словаря с ключом CID.  
Можно записывать предикаты: `parent(husb, child)`, `parent(wife, child)`, и печатать их в `pred.pl`.  

```python
		rf.seek(0)
		for line in rf:
			if line[:4] == '0 @F':
				husb = ' '; wife = ' '
			elif line[2:6] == 'HUSB':
				HID = line[7:].rstrip()
				husb = ID.get(HID)
			elif line[2:6] == 'WIFE':
				WID = line[7:].rstrip()
				wife = ID.get(WID)
			elif line[2:6] == 'CHIL':
				CID = line[7:].rstrip()
				child = ID.get(CID)
				predicate1 = 'parent(' + husb + ', ' + child + ').\n'
				predicate2 = 'parent(' + wife + ', ' + child + ').\n'
				wf.write(predicate1)
				wf.write(predicate2)
 ```
Стоит обратить внимание на то, что в данном дереве у всех людей либо 2 родителя, либо их вообще нет. Поэтому ситуация с одним родителем не рассматривается.  
Также в дереве есть "исключение" из позже поставленных правил родства: 'Barnard John' и 'Nash Thomas' - мужья 'Shakespeare Susanna', но ни от одного, ни от другого детей нет. Предикат вида `married(X, Y)` будет обозначен для этих людей в самой программе на Прологе предикатами-фактами.  

Весь код парсера:  [Parser](parser.py)
## Предикат поиска родственника
Задание: реализовать предикат проверки/поиска свекрови (mother-in-law).  

Основной предикат `minlaw(X, Y)` работает следующим образом:   
Если Y женат/замужем на/за каким-нибудь Z и если X - это мать Z, то X - свекровь Y.  
```prolog
minlaw(X, Y) :- married(Z, Y), mother(X, Z).
```
* Предикат `married(X, Y)` отвечает за проверку/поиск партнёра X для Y.  
Так как почти у всех пар есть дети, то проверку на брак можно осуществлять, опираясь на это.  
Итак, если у Y имеется какой-нибудь ребёнок, и у этого ребёнка есть ещё один родитель X, который не равен Y, то X будет парой Y.  
Такой способ работает только если в семье один ребёнок. Если же их несколько, то имя свекрови будет выведено n (количество детей) раз.  
Поэтому воспользуемся отсечением. Выражение `married` будет верным только тогда, когда части по обе стороны от cut верны.  
Раньше, когда мы доходили до ситуации `'Hathaway Anna' \= 'Hathaway Anna'`, то просто начинали искать нового ребёнка (возвращались к `child(Z, Y)`). Но теперь если условия до cut верны, а после - не соблюдены, то мы сразу получаем `fail.`  

Как было раньше отмечено, ситуация "`'Barnard John' и 'Nash Thomas' - мужья 'Shakespeare Susanna'`" - своеобразное исключение. Поэтому для неё написаны соответствующие предикаты-факты.
```prolog
child(X, Y) :- parent(Y, X).

married(X, Y) :- child(Z, Y), !, child(Z, X), X \= Y.
married('Shakespeare Elizabeth', 'Nash Thomas').
married('Nash Thomas', 'Shakespeare Elizabeth').
married('Shakespeare Elizabeth', 'Barnard John').
married('Barnard John', 'Shakespeare Elizabeth').
```
Стоит заметить, что здесь также используется предикат `child(X, Y)`. Смысла в нём нет. Это всего лишь "обратный" предикат `parent`, который здесь можно было использовать. Просто с child легче понимать, что происходит.  

* Предикат `mother(X, Y)` проверяет/ищеть мать X для Y.  
Тут всё просто. Если есть такой X женского пола, что X - родитель Y, то X - мать Y.  
```prolog
mother(X, Y) :- sex(X, f), parent(X, Y).
```
Примеры запросов:
```prolog
?- minlaw(X, 'Hathaway Anne').
X = 'Arden Mary' ;
false.

?- minlaw(X, 'Shakespeare William').
X = 'Hathaway Joan' ;
false.

?- minlaw(X, 'Hart Thomas').
false.

?- minlaw(X, 'Nash Thomas').
X = 'Shakespeare Susanna' ;
false.
```
Были также осуществлён предикат поиска father-in-law `finlaw(X, Y)`. Работает он по такому же принципу.  
```prolog
father(X, Y) :- sex(X, m), parent(X, Y).

finlaw(X, Y) :- married(Z, Y), father(X, Z).
```

Примеры запросов:
```prolog
?- finlaw(X, 'Hathaway Anne').
X = 'Shakespeare John' ;
false.

?- finlaw(X, 'Shakespeare William').
X = 'Hathaway Richard' ;
false.

?- finlaw(X, 'Shakespeare Edmund').
false.

?- finlaw(X, 'Barnard John').
X = 'Hall John' ;
false.
```
[Full листинг](cptree.pl)
## Определение степени родства
Определение степени родства двух произвольных индивидов из дерева я решила разбить на 2 основных предиката: `relatednames(P1, P2, List)` и `relist(X, Y, List)`.  

* `relatednames(P1, P2, List)` - предикат, в который подаются имена двух людей и который выводит список имён, связывающий их.
Так как имена - это узлы дерева, то найти этот список значит найти путь из начального состояния в конечное.
`Initial` и `Final` состояние будут представлены переменными `P1` и `P2`.  

Переходы от одного состояния в другое описаны предикатами типа `relative(Rel, P1, P2)`. Такие предикаты можно использовать и отдельно, чтобы узнать об отношении между двумя людьми.
```prolog
sibling(Sib, Pe) :- father(Pa, Pe), !, father(Pa, Sib), Sib \= Pe.
sibling(Sib, Pe) :- mother(Pa, Pe), mother(Pa, Sib), Sib \= Pe.

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
ggp(X, Y) :- grandparent(X, Z), parent(Z, Y).

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
```
Для предотвращения зацикливания используется предикат вида `filist([Now|T], [New, Now|T], Goal)`. В него подаётся список с последовательностью переходов `[Now|T]` и `Goal` - конечное состояние, а возвращается обновлённый список.  
С помощью предиката `relative(_, Now, New)` находим возможного ребёнка, затем проверяем, является ли он членом уже существующего списка при помощи `not(member(New, [Now|T]))`.  
Если же этот ребёнок оказывается равным нашему `Goal`, то возвращаем обновлённый список с `Goal`.
```prolog
filist([Now|T], [Goal, Now|T], Goal) :-
	relative(_, Now, Goal).
filist([Now|T], [New, Now|T], _) :-
	relative(_, Now, New),
	not(member(New, [Now|T])).
```
  
Теперь необходимо определить, какой поиск лучше всего подходит для нашего случая.  
Ветви дерева состояний не имеют одинаковой длины, и нам необходимо найти кратчайший путь - воспользуемя поиском в ширину.  
Поиск в ширину предусматривает в первую очередь переход к вершинам, ближайшим к корню, затем к их детям и т.д. То есть рассматривает всех детей корня слева направо, а потом переходит к их детям, отбрасывая тех, которые являются тупиками.  
 
Поиск с итеративным погружением для данной задачи кажется заманчивым, но с заданием отношений как в одну, так и в другую сторону я боюсь дать неверное максимальное ограничение.  
   
Однако при использовании поиска в ширину память может закончится очень быстро, так как мы храним список из всех пройденных списков для проверки.  
В дереве 39 людей, и, когда степень родства становится равна количеству поколений дерева, можно получить  
`ERROR: out of global stack`. Для того, чтобы от этого избавиться необходимо сделать правила перехода через  
одно/два поколения как одну, так и в другую сторону. Например, обозначение предикатов `grandmother/father` и `grandson/daughter`.  

Поиск в ширину гарантирует нахождение кратчайшего пути, поэтому нет смысла в предикатах типа `ancestor` и `descendant`. Однако они всё равно реализованы, хоть и не используются.
```prolog
anc(A, P) :- parent(A, P).
anc(A, P) :- parent(Z, P), anc(A, Z).

des(D, P) :- parent(P, D).
des(D, P) :- parent(P, Z), des(D, Z).

%relative(ancestor, P, A) :- anc(A, P).
%relative(descendent, P, D) :- des(D, P).
```
  
Предикат `finame([Now|BeforeNow], Goal, Res)` отвечает за поиск в ширину.  
`[Now|BeforeNow]` - аргумент, в котором хранятся все возможные растущие последовательности переходов.  
Goal - последовательность, являющаяся конечным сотоянием. Res - переменная, в которую пойдёт конечный результат.  
Сначала с помощью стандартного предиката `findall(X, filist(Now, X, Goal), L)` находим всех детей последнего узла в списке и складываем их в список списков возможных детей L. Соединяем существующий список решений `BeforeNow` с новым списком `L` - `CBN`, вызываем `finame(CBN, Goal, Res)`. Если первый список решений будет иметь `Goal` as a head, то `Res` превращается в `[Goal|T]`, то происходит отсечение, и процесс завершается.
```prolog
finame([[Goal|T]|_], Goal, [Goal|T]) :- !.
finame([Now|BeforeNow], Goal, Res) :-
	findall(X, filist(Now, X, Goal), L),
	append(BeforeNow, L, CBN),
	finame(CBN, Goal, Res).
```

Так как в предикате `filist` мы добавляем новые элементы в начало списка, нужно его перевернуть перед выводом. Стандартный предикат `reverse(L, List)` используется для этого.  
  
Основной предикат `relatednames(P1, P2, List)`:
```prolog
relatednames(P1, P2, List) :-
	finame([[P1]], P2, L),
	reverse(L, List).
```
Примеры запросов:
```prolog
?- relatednames('Shakespeare William', 'Hathaway Anne', X).
X = ['Shakespeare William', 'Hathaway Anne'].

?- relatednames('Shakespeare William', 'Quiney Thomas', X).
X = ['Shakespeare William', 'Quiney Thomas'].

?- relatednames('Shakespeare John', 'Nash Thomas', X).
X = ['Shakespeare John', 'Shakespeare Susanna', 'Nash Thomas'].

?- relatednames('Hart Thomas', 'Unknown Joan', X).
X = ['Hart Thomas', 'Shakespeare Joan2', 'Unknown Joan'].

?- relatednames('Shakespeare John Sr.', 'Hathaway Joan', X).
X = ['Shakespeare John Sr.', 'Shakespeare Richard', 'Shakespeare William', 'Hathaway Joan'].

?- relatednames('Hathaway Joan', 'Shakespeare John Sr.', X).
X = ['Hathaway Joan', 'Shakespeare William', 'Shakespeare John Sr.'].
```
Стоит отметить, что вызовы `relatednames('Shakespeare John Sr.', 'Hathaway Joan', X).` и  
`relatednames('Hathaway Joan', 'Shakespeare John Sr.', X).` дали разные результаты.  
Это произошло из-за того, что для второго случая существует отношение `greatgrandfather`, позволяющее перескочить через 2 поколения. Анологичного отношения `greatgrandson\daughter` нет, поэтому у первого запроса 3 связи, и для их поиска уходит заметно больше времени.  
  
  
* `relist(P1, P2, List)` - предикат, в который подаются имена двух людей и который выводит список отношений, связывающих людей между ними.  
  
У нас уже есть предикат для поиска имён между двумя людьми `relatednames(P1, P2, List)`. Используем его, а потом найдём отношения между людьми из `List`.  
  
Предикат `rlist(L1, List)` находит все эти отношения, и возвращает их список.  
`[X, Y|T]` - список имён.  
Сначала ищем отношения между X и Y при помощи `relative(Rel, X, Y)`, затем используем рекурсию для поиска следующего отношения `rlist([Y|T],L1)`.  
Когда в списке имён остаётся только одно имя, то `List` становится пустым списком, поиск завершается, к `List` добавляются все полученные отношения.
```prolog
rlist([_], []) :- !.
rlist([X, Y|T], List) :- 
	relative(Rel, X, Y), 
	rlist([Y|T],L1),
	List = [Rel|L1], !. 

relist(X, Y, List) :- 
	relatednames(X, Y, L1), 
	rlist(L1, List). 
```
Примеры запросов:
```prolog
?- relist('Shakespeare William', 'Hathaway Anne', X).
X = [married].

?- relist('Shakespeare William', 'Quiney Thomas', X).
X = [soninlaw].

?- relist('Shakespeare John', 'Nash Thomas', X).
X = [granddaughter, soninlaw].

?- relist('Hart Thomas', 'Unknown Joan', X).
X = [mother, greatgrandmother].

?- relist('Shakespeare John Sr.', 'Hathaway Joan', X).
X = [son, grandson, motherinlaw].

?- relist('Hathaway Joan', 'Shakespeare John Sr.', X).
X = [soninlaw, greatgrandfather].
```
  
  
* `relation(X, Y, List)` предикат позволяет вывести результаты и `relatednames`, и `relist`.  
В нём нет смысла, просто удобней сразу сопоставлять список отношени и список имён.
```prolog
relation(X, Y, List) :- relist(X, Y, List).
relation(X, Y, List) :- relatednames(X, Y, List).
```
Примеры запросов:
```prolog
?- relation('Hathaway Joan', 'Shakespeare John Sr.', X).
X = [soninlaw, greatgrandfather] ;
X = ['Hathaway Joan', 'Shakespeare William', 'Shakespeare John Sr.'].

?- relation('Shakespeare John Sr.', 'Hathaway Joan', X).
X = [son, grandson, motherinlaw] ;
X = ['Shakespeare John Sr.', 'Shakespeare Richard', 'Shakespeare William', 'Hathaway Joan'].

?- relation('Nash Thomas', 'Hart Thomas', X).
X = [motherinlaw, father, cousin] ;
X = ['Nash Thomas', 'Shakespeare Susanna', 'Shakespeare William', 'Hart Thomas'].

?- relation('Hathaway Richard', 'Unknown Joan', X).
X = [soninlaw, greatgrandmother] ;
X = ['Hathaway Richard', 'Shakespeare William', 'Unknown Joan'].

?- relation('Unknown Joan', 'Hathaway Richard', X).
X = [son, grandson, fatherinlaw] ;
X = ['Unknown Joan', 'Shakespeare Richard', 'Shakespeare William', 'Hathaway Richard'].
```
Например, для `relation('Unknown Joan', 'Hathaway Richard', X).` читается это так:  
Unknown Joan has a son, Shakespeare Richard. Richard has a grandson, Shakespeare William. William has a father-in-law, Hathaway Richard.  
  
[Full листинг](cptree.pl)
## Естественно-языковый интерфейс
Анализ предложений в данной работе упрощённый, и он совмещён вместе с предикатом, позволяющим задавать вопросы относительно родства и получать осмысленные ответы.  
  
Объяснять то, как построен анализ предложения, я буду на основе контекстно-свободной грамматики Пролога (CFG). А при реализации буду использовать Definite Clause Grammar - DCG. Она, по сути, отличается от CFG только тем, что позволяет 'расширять' правила, не ограничиваясь всего лишь двухпараметрическими предикатами. Non-terminals в DCG могут иметь аргументы-предикаты, а terminals могут быть 'произвольными' членами.    
CFG представляет собой систему для определения выражений языка в правилах, которые являются рекурсивными выражениями, называемыми non-terminals (категории, подвыражения - они обычно начинаются с заглавной буквы), и примитивными выражениями - terminals (слова - со строчной).  
  
*  How many brothers\sisters does Person have?  
  
Сколько братьев\сестёр у Имя?  
В предикат подаётся список с частями предложения. Например, `q(['How', 'many', 'brothers', 'does', 'Shakespeare William', 'have', '?']).`  
  
Анализ предложения:
```
Q -> Question Quantity Relation AuxiliaryVerb Person Verb Mark 

Question -> question
Quantity -> question
Relation -> relation
AuxiliaryVerb -> verbphrase
Person -> person
Person -> pronouns
Verb -> verbphrase
Mark -> questionmark
```
Первая часть - грамматические правила, вторая - словарь/лексика.  
  
Стоит заметить, что в данная конструкция позволяет использовать pronouns (he, she, they) вместо имени человека. Но для этого небходимо представить две версии предиката. В первой мы будем искать братьев/сестёр по имени и объявлять глобальную переменную-имя `nb_setval(real, P)`. А во втором, если там будет местоимение, то будем использовать значение этой переменной `nb_getval(real, Name)`. Чтобы поменять значение глобальной переменной, нужно снова задать предложение с именем.  
  
Далее будет необходимо при помощи стандартного предиката `setof(X, relative(W, Name, X), L)`, найти всех братьев/сестёр, посчитать длину списка `length(L, Fin)` и вывести ответ.  
  
Также необходим предикат `writeoo(Rel, N, P)`, который будет выводить правильно построенное предложение, зависящее от количества найденных братьев\сестёр.
```prolog
writeoo(Rel, N, P) :-
	N < 2, !,
	rel(Rel, W),
	format('~w has ~w ~w.',[P, N, W]).
writeoo(Rel, N, P) :-
	format('~w has ~w ~w.',[P, N, Rel]).
```
Словарь:
```prolog
pronouns('he'). 
pronouns('she').
pronouns('they').

question('How', 'many').
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
```
Осуществление предиката:
```prolog
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

```
Примеры запросов:
```prolog
?- q(['How', 'many', 'brothers', 'does', 'Shakespeare William', 'have', '?']).
Shakespeare William has 3 brothers.
true .

?- q(['How', 'many', 'sisters', 'does', 'he', 'have', '?']).
Shakespeare William has 4 sisters.
true .

?- q(['How', 'many', 'sisters', 'does', 'Hart Mary', 'have', '?']).
false.

?- q(['How', 'many', 'brothers', 'does', 'she', 'have', '?']).
Hart Mary has 3 brothers.
true .

?- q(['How', 'many', 'sisters', 'does', 'Shakespeare John', 'have', '?']).
Shakespeare John has 1 sister.
true .
```
    
* Who is P1 to P2?  
  
Кто такой Имя Имю?  
В предикат подаётся список с частями предложения. Например, `q(['Who', 'is', 'Hart Mary', 'to', 'Shakespeare William', '?']).`  
  
Анализ предложения:
```
Q -> Question LinkVerb Person1 To Person2 Mark

Question -> question
LinkVerb -> quesiton
Person1 -> person
Person1 -> pronouns
To -> to
Person2 -> person
Person2 -> pronouns
Mark -> questionmark
``` 
Теперь будет 3 версии предиката: 1) когда оба имени пристутствуют (только второе имя будет значением глобальной переменной); 2) когда присутствует только первое имя, а второе - местоимение; 3) первое имя - местоимение.  
  
Отношение ищем при помощи предиката `relative(Rel, P2, P1)`. Поэтому не все имена будут иметь соотношения.  
  
Для вывода ответа будет использован предикат `writeo(Rel, P1, P2)`, зависящий от Rel (если married, то особый вывод; если aunt\uncle, то aртикль будет 'an').  
```prolog
writeo(Rel, P1, P2) :- Rel = married, format('~w is married to ~w.', [P1, P2]).
writeo(Rel, P1, P2) :- (Rel = aunt; Rel = uncle), format('~w is an ~w to ~w', [P1, Rel, P2]).
writeo(Rel, P1, P2) :- format('~w is a ~w to ~w.', [P1, Rel, P2]).
```
Добавления в словарь:
```prolog
pronouns('his').
pronouns('her'). 
pronouns('them').

question('Who', 'is', 'to').
```
Осуществления предикатов:
```prolog
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
```
Примеры запросов:
```prolog
?-  q(['Who', 'is', 'Hart Mary', 'to', 'Shakespeare William', '?']).
Hart Mary is a niece to Shakespeare William.
true .

?- q(['Who', 'is', 'Hart Mary', 'to', 'him', '?']).
Hart Mary is a niece to Shakespeare William.
true .

?- q(['Who', 'is', 'he', 'to', 'Arden Robert', '?']).
Shakespeare William is a grandson to Arden Robert.
true .

?- q(['Who', 'is', 'Hart Thomas', 'to', 'Shakespeare John Sr.', '?']).
false.

?- q(['Who', 'is', 'Hart Thomas', 'to', 'Shakespeare Margaret', '?']).
Hart Thomas is a cousin to Shakespeare Margaret.
true .

?- q(['Who', 'is', 'she', 'to', 'Hart Thomas', '?']).
Shakespeare Margaret is an aunt to Hart Thomas
true .

?- q(['Who', 'is', 'Shakespeare Elizabeth', 'to', 'Nash Thomas', '?']).
Shakespeare Elizabeth is married to Nash Thomas.
true .
```
[Full листинг](cptree.pl)
## Выводы
Итак, я познакомилась с файлами в формате GEDCOM, научилась делать парсер, обрабатывающий текстовые данные, на Python и, возможно, закрепила знания и навыки, полученные из лабораторных работ.  
А ещё я написала эссе про логические языки и базы данных. На эту тему было довольно мало информации, поэтому пришлось искать источники и на других языках. Вообще, тема интересная, но прорывалась я через огромные куски текстов с формулами, теоремами и доказательствами с  большим трудом. Представление темы в эссе вышло упрощённым, но вроде бы понятным. Но оно всё равно пугает.
  
Благодаря реляционности Пролога выполнение заданий сводилось к написанию фактов и правил. Вроде бы всё кажется легким, но логика обработки и тех, и других порой сильно озадачивает.  
Хотя было приятно, так как такая модель прежде всего нацелена на человека. Она позволяет 'делить' программу на компоненты (правила), реализация которых в общем случае не зависит друг от друга (в другом случае можно заменить ещё не написанные компоненты множеством фактов), тут же тестировать программу и быстрее находить ошибки в необходимом компоненте. А трассировка просто спасает от потери в море информации. trace - главный помощник в понимании того, что вообще происходит при определённом запросе, как работают созданные правила и где необходимо исправить.
