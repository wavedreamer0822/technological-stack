Module typedef
  Implicit None
  Integer , parameter :: DP = Selected_Real_Kind( p = 9 )
  Type ST_Degree
    Integer(Kind=2) :: d , m
    real :: s    
  End Type ST_Degree
  
contains

  Type( ST_Degree ) Function RDegree_To_TypeDegree( rrDeg ) result( stt )
    Real(Kind=DP) ,Intent( IN ):: rrDeg
    real(Kind=DP) :: rr
    stt%d = int(rrDeg)
    rr = rrDeg - stt%d
    stt%m = ( rr ) * 60.0_DP
    rr = rr - stt%m/60.0_DP
    stt%s = ( rr ) * 60.0_DP**2
  End Function RDegree_To_TypeDegree
  
End Module typedef

Program www_fcode_cn
  use typedef
  Implicit None
  type( ST_Degree ) :: st
  real(kind=DP) :: r
  do
    read( * , * ) r
    st = RDegree_To_TypeDegree( r )
    write(*,*) st
  end do
End Program www_fcode_cn