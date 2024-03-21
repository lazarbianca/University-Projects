; a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.
(defun nthElem(l n)
    (cond
        ((null l) ())
        ((= n 1) (car l))
        (T (nthElem(cdr l) (- n 1)))
        )
    )

(print "a)")
(setq myList '(10 20 30 40 50))
(print (nthElem myList 3))

; b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.
(defun isMember(l e)
    (cond 
        ((null l) nil)
        ( (AND (atom (car l)) (equal (car l) e)) t )
        ( (listp (car l)) (or (isMember (car l) e) (isMember (cdr l) e)) )
        ( T (isMember (cdr l) e) )
        )
    )

(print "b)")
(setq myList '(1 2 3 (1) (1 2) (3 4) 5))
(print (isMember myList 1))

; c) Write a function to determine the list of all sublists of a given list, on any level. 
(defun findS (lst)
    (cond
        ((atom lst) nil)  ; base case: if lst is an atom, return nil
        (T (append (list lst) (findS-sublists (cdr lst))))))

(defun findS-sublists (sublist)
    ; helper
    (cond
        ((null sublist) nil)
        (T (append (findS (car sublist)) (findS-sublists (cdr sublist))))
    )
)

(print "c)")
(setq my-list '(1 2 (3 (4 5) (6 7)) 8 (9 10)))
(print (findS my-list))

; d) Write a function to transform a linear list into a set.
; essentially, remove duplicates
(defun appearsInSet (e givenSet)
  (cond 
    ((null givenSet) nil)
    ((equal e (car givenSet)) t)
    (t (appearsInSet e (cdr givenSet)))))


(defun transformNew (l &optional (newList '()))
    (cond
        ((null l) nil)
        ((appearsInSet (car l) newList) (transformNew (cdr l) newList))
        (t (cons (car l) (transformNew (cdr l) (cons (car l) newList))))
    )
)

(print "d)")
(setq example-list '(1 2 2 2 3 4 1))
(print (transformNew example-list))
