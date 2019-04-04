let () = Scanf.scanf "%d %d %d" (fun a b c ->
  print_endline @@ if a + b >= c then "Yes" else "No")
