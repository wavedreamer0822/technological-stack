Program www_fcode_cn
  Implicit None
  character(len=64) :: str,temp,cfind
  real :: weight , distance
  integer :: i
  str = "Informatin: weight=1.5kg distance=100.0km"
  !//换成下面这行的格式也可以正常读取
  !str = "Informatin: distance=100km weight=  01.5KG"
  cfind= "weight="
  i = index(str,trim(cfind))
  temp = str(i+len_trim(cfind):)
  i = verify(temp,"1234567890. ")
  read( temp(:i-1) , * ) weight
  write(*,*) trim(cfind) , weight
  cfind= "distance="
  i = index(str,trim(cfind))
  temp = str(i+len_trim(cfind):)
  i = verify(temp,"1234567890. ")
  read( temp(:i-1) , * ) distance
  write(*,*) trim(cfind) , distance
End Program www_fcode_cn