; exam practice
; A6
;1.1 initial function
(defun f1(l1 l2)
  (append (f1(car l1) l2)
    (cond
      ((null l1) (cdr l2))
      (t (list (f1(car l1) l2) (car l2)))
    )
  )
)


;refactored to avoid the double recursive call f(car l1)
(defun f(l1 l2)
  (
    (lambda (v)
      (append v
        (cond
          ((null l1) (cdr l2))
          (t (list v (car l2)))
        )
      )
    )
    (f (car l1) l2)
  )
)

;(print (f '(1 2 3) '(4 5)))

(defun g(l)
    (mapcon #'list l)
)

(defun h(l)
    (mapcan #'list l)
)

(print (g '(a b c d e)))
(print (h '(a b c d e)))
;(print (g '(1 2 (3 (4 5) 6 (7 (8)())))))
;(print (h '(1 2 (3 (4 5) 6 (7 (8)())))))

;(print (apply #'append (mapcon #'g '(1 2))))
(print (apply #'append (mapcon #'g '(a b c d e))))

(defun remov(l)
    (cond 
        ((and (numberp l) (eq 0 (mod l 3)))nil)
        ((atom l) (list l))
        (t (list (mapcan #'(lambda (r) (remov r)) l)))
    )
)
; that last line: (list (apply #' append (mapcar ....)))

(defun remMain (l)
    (car (remov l))   ; because we get an extra (  )
)

(print (remMain '(1 (2 A (3 A)) (6))))  ;(1 (2 A (A)) NIL)
(print (remov '(1 (2 A (3 A)) (6))))    ;((1 (2 A (A)) NIL))
(print (remMain '(1 (2 (C)))))
(print (remov '(1 (2 (C)))))


(defun f4(x &rest y)
  (cond
    ((null y)x)
    (t (append x (mapcar #'car y)))
  )
)

(print "1.3.")
(print (f4 '(1 2)))
(print (f4 '(3 4) '(5 6) '(7 8)))
(print (append (f4 '(1 2))(f4 '(3 4) '(5 6) '(7 8))))

(defun f5(l k)
  (cond 
    ((null l) nil)
    ((and (atom l) (eq k 0)) 0)
    ((atom l) l)
    (t (mapcar #'(lambda (newL) (f5 newL (- k 1))) l)) ;l is list
  )
)

(print (f5 '(a (1 g (2 b)) (c (d))) 2))