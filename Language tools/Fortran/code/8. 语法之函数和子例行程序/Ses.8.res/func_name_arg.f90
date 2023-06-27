Program www_fcode_cn
  Implicit None
  write( * , * ) integral( x2 , 1.0 , 2.0 , 0.01 )
  write( * , * ) 2.0**3/3 - 1.0**3/3
  write( * , * ) integral( x3 , 1.0 , 2.0 , 0.01 )
  write( * , * ) 2.0**4/4 - 1.0**4/4
contains

  Real Function x2( x )
    real :: x
    x2 = x*x
  End Function x2  
  
  Real Function x3( x )
    real :: x
    x3 = x*x*x
  End Function x3
  
  Real Function integral( func , low_bound , up_bound , delta ) result ( y )
    !Real , External :: func
    Interface 
      Real Function func( x )
        real :: x
      End Function func
    End Interface
    Real , intent( IN ) :: low_bound , up_bound , delta
    integer :: i
    real :: x
    y = 0.0
    x = low_bound + delta/2.0
    Do !// Do x = low_bound , up_bound , delta
      y = y + func( x )
      x = x + delta
      if ( x > up_bound ) exit
    End Do
    y = y * delta
  End Function integral

End Program www_fcode_cn

