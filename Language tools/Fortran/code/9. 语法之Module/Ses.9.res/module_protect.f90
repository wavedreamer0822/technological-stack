Module Grid_Mod
  Implicit None
  Type ST_Info
    integer :: m , n
  End Type ST_Info
  Type( ST_Info ) , protected     :: grd_stInfo
  Real            , allocatable   :: grd_rData( : , : )
  Character(len=512)              :: grd_cFilename

contains

  Logical Function Grid_Alloc( x , y ) result( bAlloc )
    Integer , Intent( IN ) :: x , y
    integer :: i
    bAlloc = .false.
    if ( (x * y) > 1000 ) return
    allocate( grd_rData( x , y ) , STAT = i )
    if ( i/=0 ) return
    grd_stInfo%m = x
    grd_stInfo%n = y
    bAlloc = .true.    
  End Function Grid_Alloc

  Logical Function Grid_DeAlloc()
    Grid_DeAlloc = .false.
    if ( allocated( grd_rData ) ) then
      Deallocate( grd_rData )
      Grid_DeAlloc = .true.
    end if
  End Function Grid_DeAlloc

End Module Grid_Mod

Program main
  use Grid_Mod
  Implicit None
  logical :: b
  integer :: i
  b = Grid_Alloc( 5 , 5 )
  if ( .not.b ) stop "cann't allocate"
  write( * , '(a,g0,"x",g0)' ) 'Grid Size: ' , grd_stInfo  
  !grd_stInfo%m = 50 !// ³ö´í  
  call FillGrid()
  write( * , * ) 'Grid: '
  Do i = 1 , grd_stInfo%n
    write( * , '(999f6.2)' ) grd_rData( : , i )
  End Do
  b = Grid_Dealloc()
End Program main

Subroutine FillGrid()
  use Grid_Mod
  Implicit None
  integer :: i , j
  Do i = 1 , grd_stInfo%n
    Do j = 1 , grd_stInfo%m
      grd_rData(i,j) = i * j
    End Do
  End Do
End Subroutine FillGrid