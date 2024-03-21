(defun aspect-munte (l flag nrElems)
    (cond
        ((and (null l) (equal flag 0)) nil)
        ((and (null l) (equal flag 1)) t)
        ((and (equal nrElems 1) (equal flag 0)) nil)
        ((and (and (cdr l) (< (car l) (cadr l))) (equal flag 1)) nil)
        ((and (cdr l) (> (car l) (cadr l))) (aspect-munte (cdr l) 1 (- nrElems 1)))
        (t (aspect-munte (cdr l) flag (- nrElems 1)))
    )
)
; there is an even easier way to do it: we do not need to keep
; track of nrElems if we check the existence of (cdr l) 
;(there are at least two elements)
(defun easier (l flag)
    (cond
        ((and (null l) (equal flag 0)) nil)
        ((and (null l) (equal flag 1)) t)
        ; case when list increases again after flag changed:
        ((and (and (cdr l) (< (car l) (cadr l))) (equal flag 1)) nil)
        ; case when list decreases for the first time:
        ((and (and (cdr l) (> (car l) (cadr l))) (equal flag 0)) (easier (cdr l) 1))
        (t (easier (cdr l) flag))
    )
)

; flag default call will be 0
(setq myList '(10 18 29 17 11 10))
(setq flag 0)
(setq nrElems 6)
(print "(10 18 29 17 11 10)")
(print (aspect-munte myList flag nrElems))
(print "easier version: ")
(print (easier myList flag))

(print "(10 18 29 17 21 10)")
(setq myList '(10 18 29 17 21 10))
(print (aspect-munte myList 0 nrElems))
(print "easier version: ")
(print (easier myList flag))