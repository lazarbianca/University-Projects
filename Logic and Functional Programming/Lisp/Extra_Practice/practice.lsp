; L1 problems
; 2.a) Write a function to return the product of two vectors.
;   b) Write a function to return the depth of a list. Example: the depth of a linear list is 1.
;   c) Write a function to sort a linear list without keeping the double values.
;   d) Write a function to return the intersection of two sets.

(defun dotProd (l1 l2)
    (cond
        ((or (null l1) (null l2)) 0)  ; return 0 for empty lists
        ((not (= (length l1) (length l2))) nil)  ; check if lists have the same length
        (t (+ (* (car l1) (car l2)) (dotProd (cdr l1) (cdr l2)))) ; compute dot prod otherwise
    )
)

(print "2.a) dot product")
(print (dotProd '(1 3 -5) '(4 -2 -1))) ; 3
(print (dotProd '(1 2 3) '(4 5 6))) ; 32
(print (dotProd '(1 2 3) '(4 5))) ; nil

(defun depth (list)
    (if (listp list)
        (+ 1 (reduce #'max (mapcar #'depth list)
                            :initial-value 0))
    0))

(print "2.b) depth of list")
(print (depth '(1 2 3 4)))
(print (depth '(1 2 3 (4))))
(print (depth '(1 (2 3 () (4)))) )

(defun sortNoDuplicates (lst)
    (cond
        ((null lst) nil)

    )
)
(defun bubble-sort (lst)
    (cond 
        ((null lst) nil)
        (t (insert-into-sorted (car lst) (bubble-sort (cdr lst))))
    )
)

(defun insert-into-sorted (elem sortedList)
    (cond
        ((null sortedList) (list elem))
        ((< elem (car sortedList)) (cons elem sortedList))
        ((>= elem (car sortedList)) (cons (car sortedList) (insert-into-sorted elem (cdr sortedList))))
    )
)

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
"(defun remove-duplicates-sorted (sorted-list)
  (if (endp sorted-list)
      nil
      (let ((rest (cdr sorted-list)))
        (if (endp rest)
            (list (car sorted-list))
            (if (= (car sorted-list) (car rest))
                (remove-duplicates-sorted rest)
                (cons (car sorted-list) (remove-duplicates-sorted rest)))))))"


(print "2.c)")
(setq my-list '(3 1 4 1 5 9 2 6 5 3 5))
(print (transformNew (bubble-sort my-list)))


; se da o lista neliniara. sa se returneze setul atomilor numerici
; ( 1 3 4 (A 3(2 3)B)3 4) -> (1 2 3 4)
(defun numerici (l &optional (newList '()))
    (cond 
        ((null l) nil)
        ((and (atom l) (not (numberp l))) nil)
        ((numberp (car l)) (append (list(car l)) (numerici (cdr l))))
        (t (append (numerici (car l)) (numerici (cdr l))))
    )
)

(defun numericiMain (l)
    (transformNew (numerici l))
)
;(and (numberp (car l)) (not (appearsInSet (car l) newList)))
(print "sa se returneze setul atomilor numerici")
(setq myList '(1 3 4 (A 3 (2 3) B) 3 4))
(print (numerici myList))
(print (numericiMain myList))

; find the depth of a tree denoted (node (subtree 1) ... (subtree n))
(defun depth (tree)
    (cond 
        ((atom tree) 0)
        (t (+ 1 (apply #'max (mapcar #'depth tree))))
    )
)

(print "depth of a tree: ")
(setq myTree '(A (B) (C (D))))
(print (depth myTree))

(defun remov(l n)
    (cond 
        ((and (numberp l) (eq 0 (mod l n)))nil)
        ((atom l) (list l))
        (t (list (mapcan #'(lambda (r) (rem r n)) l)))
    )
)
; that last line: (list (apply #' append (mapcar ....)))

(defun remMain (l n)
    (car (remov l n))
)


; tree dinala cu liste
(defun number_children (tree)
  (cond
    ((null (cdr tree)) 0)
    ((null (cddr tree)) 1)
    ((null (cdddr tree)) 2)
    ))

(defun transform_tree (tree)
  (cond
    ((null tree) nil)
    (t (append (list (car tree) (number_children tree))
	       (transform_tree (cadr tree))
	       (transform_tree (caddr tree))))
    ))

(print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
"(defun mountainAspect (l flag nrElems)
  (cond
    ((and (null l) (zerop flag)) nil)
    ((and (null l) (= flag 1)) t)
    ((= (list-length l) 1) (mountainAspect (cdr l) flag (1- nrElems)))
    ((>= (car l) (cadr l)) (mountainAspect (cdr l) 1 (1- nrElems)))
    (t (mountainAspect (cdr l) flag (1- nrElems)))
  )
)"

"(defun m (l flag)
	(cond
		((= (list-length l) 1) (if (= flag 0)))
		((and (< (car l) (cadr l)) (= flag 0)) nil)
		((and (> (car l) (cadr l)) (= flag 1)) (m (cdr l) nil))
		(T (m (cdr l) flag))
	)
)"


(defun mountainAspect (l flag nrElems)
  (cond
    ((and (null l) (equal flag 0)) nil)
    ((and (null l) (equal flag 1)) t)
    ;((and (equal nrElems 1) (equal flag 0)) nil)
    ((and (cdr l) (> (car l) (cadr l))) (mountainAspect (cdr l) 1 (- nrElems 1)))
    ((and (and (cdr l) (< (car l) (cadr l))) (equal flag 1)) nil) ; Check for peak after mountain aspect
    (t (mountainAspect (cdr l) flag (- nrElems 1)))
  )
)


(setq myList '(10 18 29 17 11 10)) ;T
(setq flag 0)
;(print (m myList flag)) ;T
(print (mountainAspect myList flag nrElems))

(setq myList '(10 18 29 17 21 10)) ;NIL
;(print (m myList flag))
(print (mountainAspect myList flag nrElems))

(setq myList '(10 18 29 37 41 50)) ;NIL
;(print (m myList flag))
(print (mountainAspect myList flag nrElems))

(setq myList '(10 8 7 6 5 4)) ;NIL ;debatable
;(print (m myList flag))
(print (mountainAspect myList flag nrElems))

(setq myList '(10 18 29 17 21)) ;NIL
;(print (m myList flag))
(print (mountainAspect myList flag nrElems))
