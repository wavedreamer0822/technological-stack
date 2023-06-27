Program www_fcode_cn
  Implicit None
  call sub( 7 , 6 )
  call sub( 5 , 4 , 3 )
contains

  Subroutine sub( a , b , c )
    Integer :: a , b
    Integer , optional :: c
    write( * , * ) a , b
    if ( present( c ) ) write(*,*) 'optional:' , c
  End Subroutine sub

End Program www_fcode_cn

