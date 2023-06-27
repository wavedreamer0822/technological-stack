Program www_fcode_cn
  Implicit None
  Interface
    Subroutine sub( x )
      Real :: x(:,:)
    End Subroutine sub
  End Interface
  
  Real :: a( 30 , 30 )
  call sub( a )
  call call_sub()
End Program www_fcode_cn

Subroutine sub( x )
  Implicit None
  Real :: x(:,:)
  write(*,*) size(x,dim=1) , size(x,dim=2)
End Subroutine sub


Subroutine call_sub()
  Implicit None
  Interface
    Subroutine sub( x )
      Real :: x(:,:)
    End Subroutine sub
  End Interface
  Real :: b( 15 , 15 )
  call sub( b )
End Subroutine call_sub
