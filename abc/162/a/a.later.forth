( 文字列をbuffに読み込み https://stackoverflow.com/questions/11814343/how-do-i-read-something-from-stdin-in-gforth-and-store-it-in-a-variable )
create buff 3 allot
buff 3 stdin read-line throw

( 文字列buffに入った3つの文字を順番にスタックに積む )
buff c@ buff 1+ c@ buff 2 + c@

( スタックの上から順番に、「もし値が55ならYesを出力」を3回行い )
( 55 が1個もなければNoを出力する関数 )
: SOLVE
  55 = IF ." Yes" ELSE
  55 = IF ." Yes" ELSE
  55 = IF ." Yes" ELSE
    ." No"
  THEN THEN THEN ;

( 関数を呼び出し。CRは改行)
SOLVE CR


( 以下はデバッグ確認用 )
( buff c@ . CR )
( buff 1+ c@ . CR )
( buff 2 + c@ . CR )
( buff c@ buff 1+ c@ buff 2 + c@ . . . CR )
