Program www_fcode_cn
  Implicit None
  Real    :: a( 3 , 4 )
  integer :: FILE_IN , i
  Open( NewUnit = FILE_IN , File = "2d_text.txt" )
  Do i = 1 , size(a,dim=2)
    Read( FILE_IN , * ) a( : , i )
    write( * , * ) a( : , i )
  End Do
  Close( FILE_IN )
End Program www_fcode_cn
