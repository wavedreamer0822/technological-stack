Program www_fcode_cn
  Implicit None
  integer :: a(5) = [1,2,3,-5,3]
  write(*,*) 'a>0',a>0
  write(*,*) 'all',all(a>0)
  write(*,*) 'a==2',a==2
  write(*,*) 'any',any(a==2)
End Program www_fcode_cn