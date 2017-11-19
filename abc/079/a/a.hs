main :: IO ()
main = do
  s <- getLine
  let s1 = tail s
  let s2 = take 3 s
  if judge s1 || judge s2
    then print "Yes"
    else print "No"

judge s
  | s !! 0 == s !! 1 == s !! 2 = True
  | otherwise                  = False
