Program www_fcode_cn
  Implicit None
  integer :: i , leng
  character(len=32) :: c
  i = Command_Argument_Count()
  call Get_Command_Argument( 1 , c , leng )
  write(*,*) 'Args Number:' , i
  write(*,*) 'First Args:'  , c
End Program www_fcode_cn