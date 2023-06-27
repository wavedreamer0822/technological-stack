Program www_fcode_cn
  Implicit None
  Integer , parameter :: DP = Selected_Real_Kind( p = 12 )  
  real(Kind=DP) :: r = sqrt( 2.0_DP )
  integer :: i
  Do i = 1 , 60
    r = sqrt( 2.0_DP * r )
    write(*,*) r
  End Do
End Program www_fcode_cn