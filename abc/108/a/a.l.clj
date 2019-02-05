(defn solve [k]
  (* (quot k 2) (quot (+ k 1) 2)))
 
(println (solve (read)))
