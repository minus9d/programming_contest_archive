(define (solve a)
  (* a (* a a)))

(let* ((a (read)))
  (display (solve a)))
