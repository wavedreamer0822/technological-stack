Program pcm
  Implicit None
  Integer :: FID , i
  Real :: a, b , c
  Open( NewUnit=FID , File="text_direct.txt" , form="formatted" , access="Direct" , RecL=64 )
  Read( FID , '(i7,3(1x,g15.6))' , rec=5 ) i , a , b , c
  Write( * , * ) i , a , b , c
  Close( FID )
End Program pcm