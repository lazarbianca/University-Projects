%current_prolog_flag(toplevel_print_options,V).
%   V =[quoted(true),portray(true),max_depth(10),spacing(next_argument)].
% ?- set_prolog_flag(toplevel_print_options, [quoted(true),portray(true), max_depth(0), spacing(next_argument)]).
%   true.

%5a. Substitute all occurrences of an element of a list with all the
% elements of another list.
% Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces
% X=[10,11,2,10,11,3,10,11,4].

% subst(L-list, E-nr to replace, P-list to replace with, R-result)
%flow model (i,i,i,o), (i,i,i,i)
subst([],_,_,[]).
subst([E|T],E,P,R):-
   subst(T,E,P,R1),
   addToList(R1,P,R2),
   R=R2.
subst([H|T],E,P,R):-
    subst(T,E,P,R1),
    R=[H|R1].

% addToList(LAddTo-list, LAddFrom-list, R-result list)
% flow model (i,i,o)
addToList([],L,L). %([],_,[])
addToList(L,[],L).
addToList([H|T],[E|Tail],R):-
    addToList([H|T],Tail,R1),
    R = [E|R1].


%b. For a heterogeneous list, formed from integer numbers and list of
% numbers, replace in every sublist all occurrences of the first element
% from sublist it a new given list. Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1,
% 3, 9], 5, [1, 1, 1], 7] si [11, 11] => [1, [11, 11, 1, 11, 11], 3, 6,
% [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]

% replace(L-list, P-replace with, R-result list)
% flow model (i,o), (i,i)
replace([],_,[]).
replace([H|T],P,R):-
   is_list(H),
   %get_head(H,E),
   H=[E|_],% get_head(H,headOfH), %H=[headOfH|_],
   subst(H,E,P,R1),
   replace(T,P,R2),
   R=[R1|R2].%R=[R1|T].
replace([H|T],P,[H|R]):-
   replace(T,P,R).

% get_head(L-list, H-head of list)
% flow model (i,o)
get_head([H|_], H).
