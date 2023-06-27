Module SecMod
  Implicit None
  Type ST_Sec   
    Integer :: sec
    Integer(Kind=2) :: mS , uS
  End Type ST_Sec
  
  Interface Operator( - )
    Module Procedure SecDec_Us
  End Interface
  
contains

  Integer(Kind=8) Function SecDec_uS( stSec1 , stSec2 )
    Type ( ST_Sec ) , Intent( IN ) :: stSec1 , stSec2
    Integer(Kind=8) :: n1 , n2
    n1 = stSec1%Sec * 1000000_8 + stSec1%ms * 1000_8 + stSec1%us
    n2 = stSec2%Sec * 1000000_8 + stSec2%ms * 1000_8 + stSec2%us
    SecDec_uS = ABS(n1 - n2)
  End Function SecDec_uS

End Module SecMod

Program main
  use SecMod
  Implicit None
  Type( ST_Sec ) :: st1 = ST_Sec(100,22,20)
  Type( ST_Sec ) :: st2 = ST_Sec(100,20,10)
  write(*,'(a,g0,a)') 'between: ',st2-st1,' uSec'
End Program main

