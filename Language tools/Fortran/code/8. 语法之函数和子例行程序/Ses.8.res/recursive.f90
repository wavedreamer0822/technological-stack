module def
  Integer , parameter :: DP = Selected_Real_Kind( p = 12 )
end module def

Program www_fcode_cn
  use def
  Implicit None
  Real(Kind=DP) :: Func , r
  r = Func( 5 ) 
  write(*,*) r !// 此处不能写为 write(*,*) Func(5) 
End Program www_fcode_cn

Recursive Function Func( n ) result( r )
  use def
  Implicit None
  Real(Kind=DP) :: r
  Integer :: n
  !write(*,*) 'in:',n
  if ( n > 0 ) then
    r = sqrt( 2.0_DP * Func(n-1) )
  else
    r = sqrt( 2.0_DP )
  end if
  !write(*,*) 'out:',n,r
End Function Func