Module fcode_Mod
  Implicit None
  Real , save :: a = 0 , b = 0 , c = 0

contains

  Subroutine fc_Init()
    a = 3 ; b = 4 ; c = 5
  End Subroutine fc_Init

End Module fcode_Mod

Program main
  use fcode_Mod
  Implicit None
  write( * , * ) a , b , c
  call fc_Init()
  write( * , * ) a , b , c
  a = 1 ; b = 2 ; c = 3
  write( * , * ) a , b , c
  call fc_Init()
  write( * , * ) a , b , c
End Program main