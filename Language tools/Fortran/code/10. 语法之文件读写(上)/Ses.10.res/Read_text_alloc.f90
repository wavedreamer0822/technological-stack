Module DFile_Mod
  Implicit None
  
contains 

  Integer Function GetDataN( cStr )
    Character( Len = * ) , Intent( IN ) :: cStr
    Integer :: i
    Logical :: bIsSeparator , bIsQuote
    GetDataN = 0
    bIsSeparator = .TRUE.
    bIsQuote = .FALSE.
    Do i = 1 , Len_Trim( cStr )
      Select Case( cStr(i:i) )
      Case( '"' , "'" ) !// 如果遇到引号
        If ( .Not.bIsQuote ) GetDataN = GetDataN + 1  !//如果不在引号中，则增加一个数据
        bIsQuote = .Not.bIsQuote !// 引号结束或开始
        bIsSeparator = .FALSE.
      Case( " " , "," , char(9) ) !// 如果遇到分隔符
        If ( .Not.bIsQuote ) then  !// 分隔符如果不在引号中
          bIsSeparator = .TRUE.
        End If
      Case Default      
        If ( bIsSeparator ) then
          GetDataN = GetDataN + 1
        End If
        bIsSeparator = .FALSE.
      End Select
    End Do
  End Function GetDataN
  
  Integer Function GetFileN( iFileUnit )
  !// 此函数应在打开文件后立即调用。调用后读取位置返回文件起始位置
    Implicit None
    Integer , Intent( IN ) :: iFileUnit
    character( Len = 1 ) :: cDummy
    integer :: ierr
    GetFileN = 0
    Rewind( iFileUnit )
    Do
      Read( iFileUnit , * , ioStat = ierr ) cDummy
      If( ierr /= 0 ) Exit
      GetFileN = GetFileN + 1
    End Do
    Rewind( iFileUnit )
  End Function GetFileN 

End Module DFile_Mod

Program www_fcode_cn
  Use DFile_Mod
  Implicit None
  Real , allocatable :: a(:,:)
  Character(len=512) :: cStr
  Real    :: r  
  integer :: FILE_IN , i , nRow , nCol
  Open( NewUnit = FILE_IN , File = "text.txt" )
  nRow = GetFileN( FILE_IN ) - 2 !//获得文件行数 
  Read( FILE_IN , * ) !//跳过第一行
  Read( FILE_IN , * ) !//跳过第二行
  Read( FILE_IN , '(a512)' ) cStr!//读取第三行
  nCol = GetDataN( cStr ) - 1 !//获得第三行有多少列
  write( *, '("Row:",g0," Col: ",g0)' ) nRow , nCol
  Allocate( a( nCol , nRow ) )
  Backspace( FILE_IN ) !//退回到第三行
  Do i = 1 , nRow
    Read( FILE_IN , * ) r , a( : , i )
    write( * , * ) a(:,i)
  End Do
  Deallocate( a )
  Close( FILE_IN )
End Program www_fcode_cn
