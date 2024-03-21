; 1. Write a function to check if an atom is member of a list (the list is non-linear) (use map functions)

(defun linearize (l)
    (cond 
        ((atom l) (list l))
        (t (apply #'append (mapcar #'linearize l)))
    )
)

(defun is-member (atom lst)
    (not (every #'null 
            (mapcar 
                (lambda (elem) 
                    (equal atom elem)
                )
                lst
            )
    ))
)

"(defun is-member-recursive (elem lst)
    (cond
        ((null lst) nil)
        ((atom lst) (equal elem lst))
        ((listp (car lst)) (or (is-member-recursive elem (car lst))
                           (is-member-recursive elem (cdr lst))))
        (t (member elem lst))
    )
)"

"(defun is-member1 (atom lst)
  (not (every #'null
              (mapcar #'(lambda (elem)
                          (is-member-recursive atom elem))
                      lst))))
"

"defun is-member1 (atom lst)
  (not (some #'(lambda (result)
                 (and (not (atom result))
                      result))
             (mapcar #'(lambda (elem)
                         (is-member-recursive atom elem))
                     lst))))"

"defun again (e lst)
  (if (and (listp lst)
           (not (every #'null
                       (mapcar #'(lambda (elem)
                                   (is-member-recursive e elem))
                               lst))))
      t ; then
      nil ; else
    )) ;bad still"


;(defun is-member1 (atom lst)
;  (or (some #'(lambda (elem)
;               (is-member-rec atom elem))
;           lst)
;      t))

(setq my-list '((a b c) (d e f) (g h i)))
(setq nested-list '(a b c (d (e) f) ((g h) () i)))
;(print (linearize my-list))
;(print (linearize nested-list))
(print (is-member 'e (linearize my-list))) ;T
(print (is-member 'x (linearize my-list))) ;NIL
(print (is-member 'e (linearize nested-list))) ;T
(print (is-member 'x (linearize nested-list))) ;NIL

;(print "second version: ")
;(print (is-member1 'e my-list)) ;T
;(print (is-member1 'x my-list)) ;NIL
;(print (is-member1 'e nested-list)) ;T
;(print (is-member1 'x nested-list)) ;NIL