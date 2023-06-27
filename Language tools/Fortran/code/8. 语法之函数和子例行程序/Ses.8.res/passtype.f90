Module typedef
  Implicit None
  type ST
    real :: a , b
  end type ST
End Module typedef

Program www_fcode_cn
  use typedef
  Implicit None  
  type ( ST ) :: st1
  call sub( st1 )
End Program www_fcode_cn

Subroutine sub( stda )
  use typedef
  Implicit None
  type ( ST ) :: stda
  stda%a = 1.0
End Subroutine sub