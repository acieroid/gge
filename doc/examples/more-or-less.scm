; Here is a simple scheme program to show that you can use GGE as a
; scheme interpreter.
; Though this program can also be executed with `guile -s`, there's no
; advantages to use GGE here, but in more sophisticated games you
; could use GGE functions, like logging, arguments, ... 
; (yes, most of these functions can also be written in scheme, so
; there's no real advantages)

(define *nb* (random 100))

(letrec ((found #f)
         (ask-and-check
           (lambda () 
            (display "Enter a number : ")
            (let ((n (read)))
              (cond ((< n *nb*)
                      (begin 
                        (display "Too small\n")
                        (ask-and-check)))
                    ((> n *nb*)
                      (begin 
                        (display "Too big\n")
                        (ask-and-check)))
                    (else (display "Right !\n")))))))
  (ask-and-check))
        
