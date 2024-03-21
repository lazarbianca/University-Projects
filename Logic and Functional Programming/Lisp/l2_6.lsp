(setq my-tree '(A 2 B 2 C 1 I 0 F 1 G 0 D 2 E 0 H 0))
(defun traverse_left(tree nv nm)
    (cond
        ((null tree)nil)
        ((= nv (+ 1 nm)) nil)
        (t (cons (car tree) (cons (cadr tree) (traverse_left (cddr tree) (+ 1 nv) (+ (cadr tree) nm)) )
            )
        )
    )
)

(defun left(tree)
    (traverse_left (cddr tree) 0 0)
)

(defun traverse_right (tree nv nm)
    (cond
        ((null tree)nil)
        ((= nv (+ 1 nm)) (cons (car tree) (cdr tree)))
        (t (traverse_right (cddr tree) (+ 1 nv) (+ (cadr tree) nm)) )
            )
    )


(defun right(tree)
    (traverse_right (cddr tree) 0 0)
)

(print (left my-tree))
(print (right my-tree))

(defun inorder (tree) 
    (cond
        ((null tree)nil)
        (t (append (inorder (left tree)) (list (car tree)) (inorder (right tree)))
        )
    )
)

(print (inorder my-tree))
(setq tree2 '(A 2 B 0 C 2 D 0 E 0))
(print (inorder tree2))


"(defun M (l)
    (cond 
        ((atom l) NIL)
        ((car l) T)
        (T (M (cdr l)))
    )
)"

;(print "funcall:")
;(print (funcall #'M 2))
;(print (funcall #'M '(NIL NIL)))