Module mod_name
  Implicit None
  real , public     :: pub_var   =1.
  real , private    :: prvat_var =2.
  real , protected  :: prtct_var =3.

contains

  Subroutine sub1( dum_a , dum_b )
    Real , Intent( IN ) :: dum_a 
    Real , Intent( INOUT ) :: dum_b
    real :: loc_1 , loc_2
    write(*,*) dum_a , dum_b , pub_var , prvat_var , prtct_var
    loc_1 = 5.0
    write(*,*) f1( loc_1 , dum_b )
  End Subroutine sub1

  Integer Function f1( dum_1 , dum_2 )
    Real , Intent( IN ) :: dum_1 
    Real , Intent( INOUT ) :: dum_2
    real :: loc_1 , loc_2
    f1    = dum_1 + dum_2 + pub_var + prvat_var + prtct_var
    dum_2 = 40.0
  End Function f1

End Module mod_name

Program main
  use mod_name
  Implicit None
  !call sub1( prvat_var , pub_var ) !// 无法编译，因为 prvat_var 是私有的
  !call sub1( pub_var , prtct_var ) !// 无法编译，因为 prtct_var 是被保护的，无法当做 Intent(OUT) 的变量
  call sub1( prtct_var , pub_var )
End Program main