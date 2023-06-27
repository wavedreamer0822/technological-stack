Program www_fcode_cn
  Implicit None
  integer :: i , now_year = 2015
  Integer :: PrintCopyRight
  i = PrintCopyRight( "fcode.cn" , now_year )
  i = PrintCopyRight( "www.fcode.cn" , now_year )
End Program www_fcode_cn

Integer Function PrintCopyRight( cDomain , now_year )
  Implicit None
  Character(len=*) , Intent( IN ) :: cDomain
  Integer , Intent( IN ) :: now_year
  write( * , * ) 'Powered by http://' , cDomain , now_year
  PrintCopyRight = now_year  
  !return
End Function PrintCopyRight