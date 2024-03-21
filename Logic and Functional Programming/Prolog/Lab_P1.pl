% P1 - 11
%a. Write a predicate to substitute an element from a list with
%another element in the list.
%b. Write a predicate to create the
% sublist (lm, …, ln) from the list (l1,…, lk)

%Subst(L-list, N-nr to replace, K-nr to replace with, R-result list)
%flow model (i,i,i,o), (i,i,o,i)
subst([],_,_,[]).
subst([N|T],N,K,R):-
    subst(T,N,K,TailResult),
    R=[K|TailResult].
subst([H|T], N, K, R) :-
    subst(T, N, K, TailResult),
    R = [H|TailResult].
%when Head is N, Substitute with K; otherwise, move on to next elem


%sublist(L-list, m-start position, n-end position, R-result list)
%flow model (i,i,i,o)

sublist([],_,_,[]).
sublist(_,0,0,[]).
sublist([H|T],1,N,[H|R]):-
    N>0,
    NewN is N-1,
    sublist(T,0,NewN,R).

sublist([H|T],0,N,[H|R]):-
    N>0,
    NewN is N-1,
    sublist(T,0,NewN,R).
sublist([_|T],M,N,R):-
    M>1,
    NewM is M-1,
    NewN is N-1,
    sublist(T,NewM,NewN,R).
%if M==N==0, empty list
%if M,N>0, extract Head and decrement M,N
%if M==0, N>0, extract elems and decrement N until it is 0 as well
%if M>0 and N==0


