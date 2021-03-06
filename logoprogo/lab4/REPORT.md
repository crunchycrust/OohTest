#№ Отчет по лабораторной работе №4
## по курсу "Логическое программирование"

## Обработка естественного языка

### студент: Савина А.А.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |               |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*


## Введение
Существует 2 основных способа анализа естественных и искусственных языков:  
1) Анализ ключевых слов/лексический анализ, основанный на ключевых словах, являющихся значениями переменнных предикатов, и в котором грамматическая корректность предложения не играет роли;  
2) Грамматический/синтаксический анализ делится на 2 вида: контекстно-свободный и контекстно-зависимый.  
	2.1) Контекстно-свободный анализ - анализ, в котором предложения классифицируются в зависимости от их структуры, соответсвующей грамматическим правилам;  
	2.2) Контекстно-зависимый/прагматический/семантический анализ - связан прежде всего со смыслом фраз.  

В Прологе есть класс грамматики для описания естественного языка, называемый грамматикой фразовой структуры (phrase-structure grammar), с помощью которого легко представить различный фразы и предложения. Это и есть основная причина того, что Пролог является удобным для решения задач обработки языков.

## Задание

10. Реализовать разбор фраз языка, представляющих собой положительные и отрицательные высказывания. В результате предикат должен выдавать все атомарные глубинные структуры.  

Пример:  
Запрос:  
```prolog
?- decompose(["Саша", "любит", "игрушки", "но", "не", "любит", "кубики", "и", "мячи"],X).
?- decompose(["Ира", "не", "любит", "стихи", "и", "прозы", "а", "любит", "пьесы"],X).
```
Результат:   
```prolog
X=likes("Саша", "игрушки");
X=not_likes("Саша", "кубики");
X=not_likes("Саша", "мячи").

X=not_likes("Ира", "стихи"); 
X=not_likes("Ира", "прозы"); 
X=likes("Ира", "пьесы").
```

## Принцип решения
Грамматику фразовой стуктуры можно разделить на 2 вида: CFG и DCG.  

Контекстно-свободные грамматики (CFG) представляют собой систему для определения выражений языка в правилах, которые являются рекурсивными выражениями, называемыми non-terminals (категории, подвыражения - они обычно начинаются с заглавной буквы), и примитивными выражениями - terminals (слова - с маленькой буквы).

В данной работе разбор предложений при помощи CFG можно представить следующим образом (это упрощённый пример):
```
Decompose-> Subject ButPhrase
Butphrase -> But VerbPhrase
VerbPhrase -> Like LikeObj
VerbPhrase -> Dislike DislikeObj
LikeObj -> Obj
DislikeObj -> Obj

Subject -> person
But -> but
Like -> like
Dislike -> dislike
Obj -> objects
```
Первая часть - грамматические правила, вторая - словарь/лексика.  
Такую классификацию выражения и его подвыражений можно представить в дереве фразовой структуры (phrase-structure tree) или parse tree.  

Далее эти выражения необходимо преобразовать в предикаты вида:  
1) Для правил `dec(X, Y) :- sub(X, Z), bp(Z, Y).`;
2) Для лексики `sub(X, Y) :- connects(person, X, Y).`.

Но всё же в этой работе используется грамматика, построенная на определённых предложениях (Definite Clause Grammar - DCG). Она, по сути, отличается от CFG только тем, что позволяет 'расширять' правила, не ограничиваясь всего лишь двухпараметрическими предикатами. Non-terminals в DCG могут иметь аргументы-предикаты, а terminals могут быть 'произвольными' членами.  


Словарь для задачи:
```prolog
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
```

Грамматические правила повторяют почти все, описанные выше.
```prolog
butph(A, B) :-
	append(_, ["but"|B], A).
butph(A, B) :- 
	append(B, ["but"|_], A).

like(A, B) :-
	append(_, ["likes"|B], A).
dislike(A, B) :-
	append(_, ["does", "not", "like"|B], A).

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
```

## Результаты
```prolog
?- decompose(["Alex", "likes", "toys", "but", "he", "does", "not", "like", "poems", "and", "peaches"], X).
X = doesnotlike("Alex", "poems") ;
X = doesnotlike("Alex", "peaches") ;
X = likes("Alex", "toys") ;
false.

?- decompose(["Irene", "does", "not", "like", "songs", "and", "poems", "but", "likes", "bears"], X).
X = likes("Irene", "bears") ;
X = doesnotlike("Irene", "songs") ;
X = doesnotlike("Irene", "poems") ;
false.

?- decompose(["Peter", "does", "not", "like", "reports", "flowers", "frogs", "and", "winter", "but", "she", "likes", "bears"], X).
X = likes("Peter", "bears") ;
X = doesnotlike("Peter", "reports") ;
X = doesnotlike("Peter", "flowers") ;
X = doesnotlike("Peter", "frogs") ;
X = doesnotlike("Peter", "winter") ;
false.

?- decompose(["Yuna", "likes", "bananas", "but", "does", "not", "like", "winter"], X).
X = doesnotlike("Yuna", "winter") ;
X = likes("Yuna", "bananas") ;
false.
```
## Выводы


Задача грамматического разбора\синтаксического анализа состоит в том, чтобы определить, является ли последовательность слов предложением языка, и чтобы создать представление структуры этого предложения в зависимости от грамматических правил.  
И у Пролога есть специальная грамматика для этого.  
А DC грамматика может ещё и фиксировать особенности естественного языка, которые описываются контекстно-зависимыми правилами. Это было использованно в данной работе. Предложение делилось на две части - до и после "but". Затем эти куски обрабатывались в зависимости от того, встречались ли в них конструкции like или dislike.  

DCG очень удобна, и в Прологе существует специальное обозначение для её записи без, порой, слишком длинного, "ручного" преобразования в предикаты (`-->`). Однако в этой работе оно не используется. Почему? Я запуталась. Смысл использования обозначения понятен, а вот написание программы вызывает затруднения.

Ух, последняя работа. Мне понравилось. Но стоит ещё во многих вещах разобраться. Впрочем, отчёт снова писался долго и мучительно. Конец :)
