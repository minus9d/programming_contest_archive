program solve
  integer  :: n
  INTEGER(8) :: L0
  INTEGER(8) :: L1
  INTEGER(8) :: tmp
  read (*,*) n
  
  L0 = 2
  L1 = 1
  do i = 1, n-1
    tmp = L0 + L1
    L0 = L1
    L1 = tmp
  end do
  ! i0 は整数を左寄せでprintするフォーマットの意味 
  PRINT '(i0)', L1
end program solve
