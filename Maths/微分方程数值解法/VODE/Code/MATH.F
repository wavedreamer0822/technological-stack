      subroutine daxpy(n,da,dx,incx,dy,incy)
c
c     constant times a vector plus a vector.
c     uses unrolled loops for increments equal to one.
c     jack dongarra, linpack, 3/11/78.
c
      double precision dx(1),dy(1),da
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if (da .eq. 0.0d0) return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        dy(iy) = dy(iy) + da*dx(ix)
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,4)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dy(i) = dy(i) + da*dx(i)
   30 continue
      if( n .lt. 4 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,4
        dy(i) = dy(i) + da*dx(i)
        dy(i + 1) = dy(i + 1) + da*dx(i + 1)
        dy(i + 2) = dy(i + 2) + da*dx(i + 2)
        dy(i + 3) = dy(i + 3) + da*dx(i + 3)
   50 continue
      return
      end
      subroutine saxpy(n,sa,sx,incx,sy,incy)
c
c     constant times a vector plus a vector.
c     uses unrolled loop for increments equal to one.
c     jack dongarra, linpack, 3/11/78.
c
      real sx(1),sy(1),sa
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if (sa .eq. 0.0) return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        sy(iy) = sy(iy) + sa*sx(ix)
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,4)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        sy(i) = sy(i) + sa*sx(i)
   30 continue
      if( n .lt. 4 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,4
        sy(i) = sy(i) + sa*sx(i)
        sy(i + 1) = sy(i + 1) + sa*sx(i + 1)
        sy(i + 2) = sy(i + 2) + sa*sx(i + 2)
        sy(i + 3) = sy(i + 3) + sa*sx(i + 3)
   50 continue
      return
      end
      subroutine  dcopy(n,dx,incx,dy,incy)
c
c     copies a vector, x, to a vector, y.
c     uses unrolled loops for increments equal to one.
c     jack dongarra, linpack, 3/11/78.
c
      double precision dx(1),dy(1)
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        dy(iy) = dx(ix)
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,7)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dy(i) = dx(i)
   30 continue
      if( n .lt. 7 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,7
        dy(i) = dx(i)
        dy(i + 1) = dx(i + 1)
        dy(i + 2) = dx(i + 2)
        dy(i + 3) = dx(i + 3)
        dy(i + 4) = dx(i + 4)
        dy(i + 5) = dx(i + 5)
        dy(i + 6) = dx(i + 6)
   50 continue
      return
      end
      subroutine scopy(n,sx,incx,sy,incy)
c
c     copies a vector, x, to a vector, y.
c     uses unrolled loops for increments equal to 1.
c     jack dongarra, linpack, 3/11/78.
c
      real sx(1),sy(1)
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        sy(iy) = sx(ix)
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,7)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        sy(i) = sx(i)
   30 continue
      if( n .lt. 7 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,7
        sy(i) = sx(i)
        sy(i + 1) = sx(i + 1)
        sy(i + 2) = sx(i + 2)
        sy(i + 3) = sx(i + 3)
        sy(i + 4) = sx(i + 4)
        sy(i + 5) = sx(i + 5)
        sy(i + 6) = sx(i + 6)
   50 continue
      return
      end
      double precision function ddot(n,dx,incx,dy,incy)
c
c     forms the dot product of two vectors.
c     uses unrolled loops for increments equal to one.
c     jack dongarra, linpack, 3/11/78.
c
      double precision dx(1),dy(1),dtemp
      integer i,incx,incy,ix,iy,m,mp1,n
c
      ddot = 0.0d0
      dtemp = 0.0d0
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        dtemp = dtemp + dx(ix)*dy(iy)
        ix = ix + incx
        iy = iy + incy
   10 continue
      ddot = dtemp
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,5)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dtemp = dtemp + dx(i)*dy(i)
   30 continue
      if( n .lt. 5 ) go to 60
   40 mp1 = m + 1
      do 50 i = mp1,n,5
        dtemp = dtemp + dx(i)*dy(i) + dx(i + 1)*dy(i + 1) +
     *   dx(i + 2)*dy(i + 2) + dx(i + 3)*dy(i + 3) + dx(i + 4)*dy(i + 4)
   50 continue
   60 ddot = dtemp
      return
      end
      real function sdot(n,sx,incx,sy,incy)
c
c     forms the dot product of two vectors.
c     uses unrolled loops for increments equal to one.
c     jack dongarra, linpack, 3/11/78.
c
      real sx(1),sy(1),stemp
      integer i,incx,incy,ix,iy,m,mp1,n
c
      stemp = 0.0e0
      sdot = 0.0e0
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c        code for unequal increments or equal increments
c          not equal to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        stemp = stemp + sx(ix)*sy(iy)
        ix = ix + incx
        iy = iy + incy
   10 continue
      sdot = stemp
      return
c
c        code for both increments equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,5)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        stemp = stemp + sx(i)*sy(i)
   30 continue
      if( n .lt. 5 ) go to 60
   40 mp1 = m + 1
      do 50 i = mp1,n,5
        stemp = stemp + sx(i)*sy(i) + sx(i + 1)*sy(i + 1) +
     *   sx(i + 2)*sy(i + 2) + sx(i + 3)*sy(i + 3) + sx(i + 4)*sy(i + 4)
   50 continue
   60 sdot = stemp
      return
      end
      subroutine dgbfa(abd,lda,n,ml,mu,ipvt,info)
      integer lda,n,ml,mu,ipvt(1),info
      double precision abd(lda,1)
c
c     dgbfa factors a double precision band matrix by elimination.
c
c     dgbfa is usually called by dgbco, but it can be called
c     directly with a saving in time if  rcond  is not needed.
c
c     on entry
c
c        abd     double precision(lda, n)
c                contains the matrix in band storage.  the columns
c                of the matrix are stored in the columns of  abd  and
c                the diagonals of the matrix are stored in rows
c                ml+1 through 2*ml+mu+1 of  abd .
c                see the comments below for details.
c
c        lda     integer
c                the leading dimension of the array  abd .
c                lda must be .ge. 2*ml + mu + 1 .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c                0 .le. ml .lt. n .
c
c        mu      integer
c                number of diagonals above the main diagonal.
c                0 .le. mu .lt. n .
c                more efficient if  ml .le. mu .
c     on return
c
c        abd     an upper triangular matrix in band storage and
c                the multipliers which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        info    integer
c                = 0  normal value.
c                = k  if  u(k,k) .eq. 0.0 .  this is not an error
c                     condition for this subroutine, but it does
c                     indicate that dgbsl will divide by zero if
c                     called.  use  rcond  in dgbco for a reliable
c                     indication of singularity.
c
c     band storage
c
c           if  a  is a band matrix, the following program segment
c           will set up the input.
c
c                   ml = (band width below the diagonal)
c                   mu = (band width above the diagonal)
c                   m = ml + mu + 1
c                   do 20 j = 1, n
c                      i1 = max0(1, j-mu)
c                      i2 = min0(n, j+ml)
c                      do 10 i = i1, i2
c                         k = i - j + m
c                         abd(k,j) = a(i,j)
c                10    continue
c                20 continue
c
c           this uses rows  ml+1  through  2*ml+mu+1  of  abd .
c           in addition, the first  ml  rows in  abd  are used for
c           elements generated during the triangularization.
c           the total number of rows needed in  abd  is  2*ml+mu+1 .
c           the  ml+mu by ml+mu  upper left triangle and the
c           ml by ml  lower right triangle are not referenced.
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas daxpy,dscal,idamax
c     fortran max0,min0
c
c     internal variables
c
      double precision t
      integer i,idamax,i0,j,ju,jz,j0,j1,k,kp1,l,lm,m,mm,nm1
c
c
      m = ml + mu + 1
      info = 0
c
c     zero initial fill-in columns
c
      j0 = mu + 2
      j1 = min0(n,m) - 1
      if (j1 .lt. j0) go to 30
      do 20 jz = j0, j1
         i0 = m + 1 - jz
         do 10 i = i0, ml
            abd(i,jz) = 0.0d0
   10    continue
   20 continue
   30 continue
      jz = j1
      ju = 0
c
c     gaussian elimination with partial pivoting
c
      nm1 = n - 1
      if (nm1 .lt. 1) go to 130
      do 120 k = 1, nm1
         kp1 = k + 1
c
c        zero next fill-in column
c
         jz = jz + 1
         if (jz .gt. n) go to 50
         if (ml .lt. 1) go to 50
            do 40 i = 1, ml
               abd(i,jz) = 0.0d0
   40       continue
   50    continue
c
c        find l = pivot index
c
         lm = min0(ml,n-k)
         l = idamax(lm+1,abd(m,k),1) + m - 1
         ipvt(k) = l + k - m
c
c        zero pivot implies this column already triangularized
c
         if (abd(l,k) .eq. 0.0d0) go to 100
c
c           interchange if necessary
c
            if (l .eq. m) go to 60
               t = abd(l,k)
               abd(l,k) = abd(m,k)
               abd(m,k) = t
   60       continue
c
c           compute multipliers
c
            t = -1.0d0/abd(m,k)
            call dscal(lm,t,abd(m+1,k),1)
c
c           row elimination with column indexing
c
            ju = min0(max0(ju,mu+ipvt(k)),n)
            mm = m
            if (ju .lt. kp1) go to 90
            do 80 j = kp1, ju
               l = l - 1
               mm = mm - 1
               t = abd(l,j)
               if (l .eq. mm) go to 70
                  abd(l,j) = abd(mm,j)
                  abd(mm,j) = t
   70          continue
               call daxpy(lm,t,abd(m+1,k),1,abd(mm+1,j),1)
   80       continue
   90       continue
         go to 110
  100    continue
            info = k
  110    continue
  120 continue
  130 continue
      ipvt(n) = n
      if (abd(m,n) .eq. 0.0d0) info = n
      return
      end
      subroutine sgbfa(abd,lda,n,ml,mu,ipvt,info)
      integer lda,n,ml,mu,ipvt(1),info
      real abd(lda,1)
c
c     sgbfa factors a real band matrix by elimination.
c
c     sgbfa is usually called by sgbco, but it can be called
c     directly with a saving in time if  rcond  is not needed.
c
c     on entry
c
c        abd     real(lda, n)
c                contains the matrix in band storage.  the columns
c                of the matrix are stored in the columns of  abd  and
c                the diagonals of the matrix are stored in rows
c                ml+1 through 2*ml+mu+1 of  abd .
c                see the comments below for details.
c
c        lda     integer
c                the leading dimension of the array  abd .
c                lda must be .ge. 2*ml + mu + 1 .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c                0 .le. ml .lt. n .
c
c        mu      integer
c                number of diagonals above the main diagonal.
c                0 .le. mu .lt. n .
c                more efficient if  ml .le. mu .
c     on return
c
c        abd     an upper triangular matrix in band storage and
c                the multipliers which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        info    integer
c                = 0  normal value.
c                = k  if  u(k,k) .eq. 0.0 .  this is not an error
c                     condition for this subroutine, but it does
c                     indicate that sgbsl will divide by zero if
c                     called.  use  rcond  in sgbco for a reliable
c                     indication of singularity.
c
c     band storage
c
c           if  a  is a band matrix, the following program segment
c           will set up the input.
c
c                   ml = (band width below the diagonal)
c                   mu = (band width above the diagonal)
c                   m = ml + mu + 1
c                   do 20 j = 1, n
c                      i1 = max0(1, j-mu)
c                      i2 = min0(n, j+ml)
c                      do 10 i = i1, i2
c                         k = i - j + m
c                         abd(k,j) = a(i,j)
c                10    continue
c                20 continue
c
c           this uses rows  ml+1  through  2*ml+mu+1  of  abd .
c           in addition, the first  ml  rows in  abd  are used for
c           elements generated during the triangularization.
c           the total number of rows needed in  abd  is  2*ml+mu+1 .
c           the  ml+mu by ml+mu  upper left triangle and the
c           ml by ml  lower right triangle are not referenced.
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas saxpy,sscal,isamax
c     fortran max0,min0
c
c     internal variables
c
      real t
      integer i,isamax,i0,j,ju,jz,j0,j1,k,kp1,l,lm,m,mm,nm1
c
c
      m = ml + mu + 1
      info = 0
c
c     zero initial fill-in columns
c
      j0 = mu + 2
      j1 = min0(n,m) - 1
      if (j1 .lt. j0) go to 30
      do 20 jz = j0, j1
         i0 = m + 1 - jz
         do 10 i = i0, ml
            abd(i,jz) = 0.0e0
   10    continue
   20 continue
   30 continue
      jz = j1
      ju = 0
c
c     gaussian elimination with partial pivoting
c
      nm1 = n - 1
      if (nm1 .lt. 1) go to 130
      do 120 k = 1, nm1
         kp1 = k + 1
c
c        zero next fill-in column
c
         jz = jz + 1
         if (jz .gt. n) go to 50
         if (ml .lt. 1) go to 50
            do 40 i = 1, ml
               abd(i,jz) = 0.0e0
   40       continue
   50    continue
c
c        find l = pivot index
c
         lm = min0(ml,n-k)
         l = isamax(lm+1,abd(m,k),1) + m - 1
         ipvt(k) = l + k - m
c
c        zero pivot implies this column already triangularized
c
         if (abd(l,k) .eq. 0.0e0) go to 100
c
c           interchange if necessary
c
            if (l .eq. m) go to 60
               t = abd(l,k)
               abd(l,k) = abd(m,k)
               abd(m,k) = t
   60       continue
c
c           compute multipliers
c
            t = -1.0e0/abd(m,k)
            call sscal(lm,t,abd(m+1,k),1)
c
c           row elimination with column indexing
c
            ju = min0(max0(ju,mu+ipvt(k)),n)
            mm = m
            if (ju .lt. kp1) go to 90
            do 80 j = kp1, ju
               l = l - 1
               mm = mm - 1
               t = abd(l,j)
               if (l .eq. mm) go to 70
                  abd(l,j) = abd(mm,j)
                  abd(mm,j) = t
   70          continue
               call saxpy(lm,t,abd(m+1,k),1,abd(mm+1,j),1)
   80       continue
   90       continue
         go to 110
  100    continue
            info = k
  110    continue
  120 continue
  130 continue
      ipvt(n) = n
      if (abd(m,n) .eq. 0.0e0) info = n
      return
      end
      subroutine dgbsl(abd,lda,n,ml,mu,ipvt,b,job)
      integer lda,n,ml,mu,ipvt(1),job
      double precision abd(lda,1),b(1)
c
c     dgbsl solves the double precision band system
c     a * x = b  or  trans(a) * x = b
c     using the factors computed by dgbco or dgbfa.
c
c     on entry
c
c        abd     double precision(lda, n)
c                the output from dgbco or dgbfa.
c
c        lda     integer
c                the leading dimension of the array  abd .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c
c        mu      integer
c                number of diagonals above the main diagonal.
c
c        ipvt    integer(n)
c                the pivot vector from dgbco or dgbfa.
c
c        b       double precision(n)
c                the right hand side vector.
c
c        job     integer
c                = 0         to solve  a*x = b ,
c                = nonzero   to solve  trans(a)*x = b , where
c                            trans(a)  is the transpose.
c
c     on return
c
c        b       the solution vector  x .
c
c     error condition
c
c        a division by zero will occur if the input factor contains a
c        zero on the diagonal.  technically this indicates singularity
c        but it is often caused by improper arguments or improper
c        setting of lda .  it will not occur if the subroutines are
c        called correctly and if dgbco has set rcond .gt. 0.0
c        or dgbfa has set info .eq. 0 .
c
c     to compute  inverse(a) * c  where  c  is a matrix
c     with  p  columns
c           call dgbco(abd,lda,n,ml,mu,ipvt,rcond,z)
c           if (rcond is too small) go to ...
c           do 10 j = 1, p
c              call dgbsl(abd,lda,n,ml,mu,ipvt,c(1,j),0)
c        10 continue
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas daxpy,ddot
c     fortran min0
c
c     internal variables
c
      double precision ddot,t
      integer k,kb,l,la,lb,lm,m,nm1
c
      m = mu + ml + 1
      nm1 = n - 1
      if (job .ne. 0) go to 50
c
c        job = 0 , solve  a * x = b
c        first solve l*y = b
c
         if (ml .eq. 0) go to 30
         if (nm1 .lt. 1) go to 30
            do 20 k = 1, nm1
               lm = min0(ml,n-k)
               l = ipvt(k)
               t = b(l)
               if (l .eq. k) go to 10
                  b(l) = b(k)
                  b(k) = t
   10          continue
               call daxpy(lm,t,abd(m+1,k),1,b(k+1),1)
   20       continue
   30    continue
c
c        now solve  u*x = y
c
         do 40 kb = 1, n
            k = n + 1 - kb
            b(k) = b(k)/abd(m,k)
            lm = min0(k,m) - 1
            la = m - lm
            lb = k - lm
            t = -b(k)
            call daxpy(lm,t,abd(la,k),1,b(lb),1)
   40    continue
      go to 100
   50 continue
c
c        job = nonzero, solve  trans(a) * x = b
c        first solve  trans(u)*y = b
c
         do 60 k = 1, n
            lm = min0(k,m) - 1
            la = m - lm
            lb = k - lm
            t = ddot(lm,abd(la,k),1,b(lb),1)
            b(k) = (b(k) - t)/abd(m,k)
   60    continue
c
c        now solve trans(l)*x = y
c
         if (ml .eq. 0) go to 90
         if (nm1 .lt. 1) go to 90
            do 80 kb = 1, nm1
               k = n - kb
               lm = min0(ml,n-k)
               b(k) = b(k) + ddot(lm,abd(m+1,k),1,b(k+1),1)
               l = ipvt(k)
               if (l .eq. k) go to 70
                  t = b(l)
                  b(l) = b(k)
                  b(k) = t
   70          continue
   80       continue
   90    continue
  100 continue
      return
      end
      subroutine sgbsl(abd,lda,n,ml,mu,ipvt,b,job)
      integer lda,n,ml,mu,ipvt(1),job
      real abd(lda,1),b(1)
c
c     sgbsl solves the real band system
c     a * x = b  or  trans(a) * x = b
c     using the factors computed by sgbco or sgbfa.
c
c     on entry
c
c        abd     real(lda, n)
c                the output from sgbco or sgbfa.
c
c        lda     integer
c                the leading dimension of the array  abd .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c
c        mu      integer
c                number of diagonals above the main diagonal.
c
c        ipvt    integer(n)
c                the pivot vector from sgbco or sgbfa.
c
c        b       real(n)
c                the right hand side vector.
c
c        job     integer
c                = 0         to solve  a*x = b ,
c                = nonzero   to solve  trans(a)*x = b , where
c                            trans(a)  is the transpose.
c
c     on return
c
c        b       the solution vector  x .
c
c     error condition
c
c        a division by zero will occur if the input factor contains a
c        zero on the diagonal.  technically this indicates singularity
c        but it is often caused by improper arguments or improper
c        setting of lda .  it will not occur if the subroutines are
c        called correctly and if sgbco has set rcond .gt. 0.0
c        or sgbfa has set info .eq. 0 .
c
c     to compute  inverse(a) * c  where  c  is a matrix
c     with  p  columns
c           call sgbco(abd,lda,n,ml,mu,ipvt,rcond,z)
c           if (rcond is too small) go to ...
c           do 10 j = 1, p
c              call sgbsl(abd,lda,n,ml,mu,ipvt,c(1,j),0)
c        10 continue
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas saxpy,sdot
c     fortran min0
c
c     internal variables
c
      real sdot,t
      integer k,kb,l,la,lb,lm,m,nm1
c
      m = mu + ml + 1
      nm1 = n - 1
      if (job .ne. 0) go to 50
c
c        job = 0 , solve  a * x = b
c        first solve l*y = b
c
         if (ml .eq. 0) go to 30
         if (nm1 .lt. 1) go to 30
            do 20 k = 1, nm1
               lm = min0(ml,n-k)
               l = ipvt(k)
               t = b(l)
               if (l .eq. k) go to 10
                  b(l) = b(k)
                  b(k) = t
   10          continue
               call saxpy(lm,t,abd(m+1,k),1,b(k+1),1)
   20       continue
   30    continue
c
c        now solve  u*x = y
c
         do 40 kb = 1, n
            k = n + 1 - kb
            b(k) = b(k)/abd(m,k)
            lm = min0(k,m) - 1
            la = m - lm
            lb = k - lm
            t = -b(k)
            call saxpy(lm,t,abd(la,k),1,b(lb),1)
   40    continue
      go to 100
   50 continue
c
c        job = nonzero, solve  trans(a) * x = b
c        first solve  trans(u)*y = b
c
         do 60 k = 1, n
            lm = min0(k,m) - 1
            la = m - lm
            lb = k - lm
            t = sdot(lm,abd(la,k),1,b(lb),1)
            b(k) = (b(k) - t)/abd(m,k)
   60    continue
c
c        now solve trans(l)*x = y
c
         if (ml .eq. 0) go to 90
         if (nm1 .lt. 1) go to 90
            do 80 kb = 1, nm1
               k = n - kb
               lm = min0(ml,n-k)
               b(k) = b(k) + sdot(lm,abd(m+1,k),1,b(k+1),1)
               l = ipvt(k)
               if (l .eq. k) go to 70
                  t = b(l)
                  b(l) = b(k)
                  b(k) = t
   70          continue
   80       continue
   90    continue
  100 continue
      return
      end
      subroutine dgefa(a,lda,n,ipvt,info)
      integer lda,n,ipvt(1),info
      double precision a(lda,1)
c
c     dgefa factors a double precision matrix by gaussian elimination.
c
c     dgefa is usually called by dgeco, but it can be called
c     directly with a saving in time if  rcond  is not needed.
c     (time for dgeco) = (1 + 9/n)*(time for dgefa) .
c
c     on entry
c
c        a       double precision(lda, n)
c                the matrix to be factored.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c     on return
c
c        a       an upper triangular matrix and the multipliers
c                which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        info    integer
c                = 0  normal value.
c                = k  if  u(k,k) .eq. 0.0 .  this is not an error
c                     condition for this subroutine, but it does
c                     indicate that dgesl or dgedi will divide by zero
c                     if called.  use  rcond  in dgeco for a reliable
c                     indication of singularity.
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas daxpy,dscal,idamax
c
c     internal variables
c
      double precision t
      integer idamax,j,k,kp1,l,nm1
c
c
c     gaussian elimination with partial pivoting
c
      info = 0
      nm1 = n - 1
      if (nm1 .lt. 1) go to 70
      do 60 k = 1, nm1
         kp1 = k + 1
c
c        find l = pivot index
c
         l = idamax(n-k+1,a(k,k),1) + k - 1
         ipvt(k) = l
c
c        zero pivot implies this column already triangularized
c
         if (a(l,k) .eq. 0.0d0) go to 40
c
c           interchange if necessary
c
            if (l .eq. k) go to 10
               t = a(l,k)
               a(l,k) = a(k,k)
               a(k,k) = t
   10       continue
c
c           compute multipliers
c
            t = -1.0d0/a(k,k)
            call dscal(n-k,t,a(k+1,k),1)
c
c           row elimination with column indexing
c
            do 30 j = kp1, n
               t = a(l,j)
               if (l .eq. k) go to 20
                  a(l,j) = a(k,j)
                  a(k,j) = t
   20          continue
               call daxpy(n-k,t,a(k+1,k),1,a(k+1,j),1)
   30       continue
         go to 50
   40    continue
            info = k
   50    continue
   60 continue
   70 continue
      ipvt(n) = n
      if (a(n,n) .eq. 0.0d0) info = n
      return
      end
      subroutine sgefa(a,lda,n,ipvt,info)
      integer lda,n,ipvt(1),info
      real a(lda,1)
c
c     sgefa factors a real matrix by gaussian elimination.
c
c     sgefa is usually called by sgeco, but it can be called
c     directly with a saving in time if  rcond  is not needed.
c     (time for sgeco) = (1 + 9/n)*(time for sgefa) .
c
c     on entry
c
c        a       real(lda, n)
c                the matrix to be factored.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c     on return
c
c        a       an upper triangular matrix and the multipliers
c                which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        info    integer
c                = 0  normal value.
c                = k  if  u(k,k) .eq. 0.0 .  this is not an error
c                     condition for this subroutine, but it does
c                     indicate that sgesl or sgedi will divide by zero
c                     if called.  use  rcond  in sgeco for a reliable
c                     indication of singularity.
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas saxpy,sscal,isamax
c
c     internal variables
c
      real t
      integer isamax,j,k,kp1,l,nm1
c
c
c     gaussian elimination with partial pivoting
c
      info = 0
      nm1 = n - 1
      if (nm1 .lt. 1) go to 70
      do 60 k = 1, nm1
         kp1 = k + 1
c
c        find l = pivot index
c
         l = isamax(n-k+1,a(k,k),1) + k - 1
         ipvt(k) = l
c
c        zero pivot implies this column already triangularized
c
         if (a(l,k) .eq. 0.0e0) go to 40
c
c           interchange if necessary
c
            if (l .eq. k) go to 10
               t = a(l,k)
               a(l,k) = a(k,k)
               a(k,k) = t
   10       continue
c
c           compute multipliers
c
            t = -1.0e0/a(k,k)
            call sscal(n-k,t,a(k+1,k),1)
c
c           row elimination with column indexing
c
            do 30 j = kp1, n
               t = a(l,j)
               if (l .eq. k) go to 20
                  a(l,j) = a(k,j)
                  a(k,j) = t
   20          continue
               call saxpy(n-k,t,a(k+1,k),1,a(k+1,j),1)
   30       continue
         go to 50
   40    continue
            info = k
   50    continue
   60 continue
   70 continue
      ipvt(n) = n
      if (a(n,n) .eq. 0.0e0) info = n
      return
      end
      subroutine dgesl(a,lda,n,ipvt,b,job)
      integer lda,n,ipvt(1),job
      double precision a(lda,1),b(1)
c
c     dgesl solves the double precision system
c     a * x = b  or  trans(a) * x = b
c     using the factors computed by dgeco or dgefa.
c
c     on entry
c
c        a       double precision(lda, n)
c                the output from dgeco or dgefa.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c        ipvt    integer(n)
c                the pivot vector from dgeco or dgefa.
c
c        b       double precision(n)
c                the right hand side vector.
c
c        job     integer
c                = 0         to solve  a*x = b ,
c                = nonzero   to solve  trans(a)*x = b  where
c                            trans(a)  is the transpose.
c
c     on return
c
c        b       the solution vector  x .
c
c     error condition
c
c        a division by zero will occur if the input factor contains a
c        zero on the diagonal.  technically this indicates singularity
c        but it is often caused by improper arguments or improper
c        setting of lda .  it will not occur if the subroutines are
c        called correctly and if dgeco has set rcond .gt. 0.0
c        or dgefa has set info .eq. 0 .
c
c     to compute  inverse(a) * c  where  c  is a matrix
c     with  p  columns
c           call dgeco(a,lda,n,ipvt,rcond,z)
c           if (rcond is too small) go to ...
c           do 10 j = 1, p
c              call dgesl(a,lda,n,ipvt,c(1,j),0)
c        10 continue
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas daxpy,ddot
c
c     internal variables
c
      double precision ddot,t
      integer k,kb,l,nm1
c
      nm1 = n - 1
      if (job .ne. 0) go to 50
c
c        job = 0 , solve  a * x = b
c        first solve  l*y = b
c
         if (nm1 .lt. 1) go to 30
         do 20 k = 1, nm1
            l = ipvt(k)
            t = b(l)
            if (l .eq. k) go to 10
               b(l) = b(k)
               b(k) = t
   10       continue
            call daxpy(n-k,t,a(k+1,k),1,b(k+1),1)
   20    continue
   30    continue
c
c        now solve  u*x = y
c
         do 40 kb = 1, n
            k = n + 1 - kb
            b(k) = b(k)/a(k,k)
            t = -b(k)
            call daxpy(k-1,t,a(1,k),1,b(1),1)
   40    continue
      go to 100
   50 continue
c
c        job = nonzero, solve  trans(a) * x = b
c        first solve  trans(u)*y = b
c
         do 60 k = 1, n
            t = ddot(k-1,a(1,k),1,b(1),1)
            b(k) = (b(k) - t)/a(k,k)
   60    continue
c
c        now solve trans(l)*x = y
c
         if (nm1 .lt. 1) go to 90
         do 80 kb = 1, nm1
            k = n - kb
            b(k) = b(k) + ddot(n-k,a(k+1,k),1,b(k+1),1)
            l = ipvt(k)
            if (l .eq. k) go to 70
               t = b(l)
               b(l) = b(k)
               b(k) = t
   70       continue
   80    continue
   90    continue
  100 continue
      return
      end
      subroutine sgesl(a,lda,n,ipvt,b,job)
      integer lda,n,ipvt(1),job
      real a(lda,1),b(1)
c
c     sgesl solves the real system
c     a * x = b  or  trans(a) * x = b
c     using the factors computed by sgeco or sgefa.
c
c     on entry
c
c        a       real(lda, n)
c                the output from sgeco or sgefa.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c        ipvt    integer(n)
c                the pivot vector from sgeco or sgefa.
c
c        b       real(n)
c                the right hand side vector.
c
c        job     integer
c                = 0         to solve  a*x = b ,
c                = nonzero   to solve  trans(a)*x = b  where
c                            trans(a)  is the transpose.
c
c     on return
c
c        b       the solution vector  x .
c
c     error condition
c
c        a division by zero will occur if the input factor contains a
c        zero on the diagonal.  technically this indicates singularity
c        but it is often caused by improper arguments or improper
c        setting of lda .  it will not occur if the subroutines are
c        called correctly and if sgeco has set rcond .gt. 0.0
c        or sgefa has set info .eq. 0 .
c
c     to compute  inverse(a) * c  where  c  is a matrix
c     with  p  columns
c           call sgeco(a,lda,n,ipvt,rcond,z)
c           if (rcond is too small) go to ...
c           do 10 j = 1, p
c              call sgesl(a,lda,n,ipvt,c(1,j),0)
c        10 continue
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas saxpy,sdot
c
c     internal variables
c
      real sdot,t
      integer k,kb,l,nm1
c
      nm1 = n - 1
      if (job .ne. 0) go to 50
c
c        job = 0 , solve  a * x = b
c        first solve  l*y = b
c
         if (nm1 .lt. 1) go to 30
         do 20 k = 1, nm1
            l = ipvt(k)
            t = b(l)
            if (l .eq. k) go to 10
               b(l) = b(k)
               b(k) = t
   10       continue
            call saxpy(n-k,t,a(k+1,k),1,b(k+1),1)
   20    continue
   30    continue
c
c        now solve  u*x = y
c
         do 40 kb = 1, n
            k = n + 1 - kb
            b(k) = b(k)/a(k,k)
            t = -b(k)
            call saxpy(k-1,t,a(1,k),1,b(1),1)
   40    continue
      go to 100
   50 continue
c
c        job = nonzero, solve  trans(a) * x = b
c        first solve  trans(u)*y = b
c
         do 60 k = 1, n
            t = sdot(k-1,a(1,k),1,b(1),1)
            b(k) = (b(k) - t)/a(k,k)
   60    continue
c
c        now solve trans(l)*x = y
c
         if (nm1 .lt. 1) go to 90
         do 80 kb = 1, nm1
            k = n - kb
            b(k) = b(k) + sdot(n-k,a(k+1,k),1,b(k+1),1)
            l = ipvt(k)
            if (l .eq. k) go to 70
               t = b(l)
               b(l) = b(k)
               b(k) = t
   70       continue
   80    continue
   90    continue
  100 continue
      return
      end
*DECK DP1VLU
      SUBROUTINE DP1VLU (L, NDER, X, YFIT, YP, A)
C***BEGIN PROLOGUE  DP1VLU
C***PURPOSE  Use the coefficients generated by DPOLFT to evaluate the
C            polynomial fit of degree L, along with the first NDER of
C            its derivatives, at a specified point.
C***LIBRARY   SLATEC
C***CATEGORY  K6
C***TYPE      DOUBLE PRECISION (PVALUE-S, DP1VLU-D)
C***KEYWORDS  CURVE FITTING, LEAST SQUARES, POLYNOMIAL APPROXIMATION
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C***DESCRIPTION
C
C     Abstract
C
C     The subroutine  DP1VLU  uses the coefficients generated by  DPOLFT
C     to evaluate the polynomial fit of degree  L , along with the first
C     NDER  of its derivatives, at a specified point.  Computationally
C     stable recurrence relations are used to perform this task.
C
C     The parameters for  DP1VLU  are
C
C     Input -- ALL TYPE REAL variables are DOUBLE PRECISION
C         L -      the degree of polynomial to be evaluated.  L  may be
C                  any non-negative integer which is less than or equal
C                  to  NDEG , the highest degree polynomial provided
C                  by  DPOLFT .
C         NDER -   the number of derivatives to be evaluated.  NDER
C                  may be 0 or any positive value.  If NDER is less
C                  than 0, it will be treated as 0.
C         X -      the argument at which the polynomial and its
C                  derivatives are to be evaluated.
C         A -      work and output array containing values from last
C                  call to  DPOLFT .
C
C     Output -- ALL TYPE REAL variables are DOUBLE PRECISION
C         YFIT -   value of the fitting polynomial of degree  L  at  X
C         YP -     array containing the first through  NDER  derivatives
C                  of the polynomial of degree  L .  YP  must be
C                  dimensioned at least  NDER  in the calling program.
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  XERMSG
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   890911  Removed unnecessary intrinsics.  (WRB)
C   891006  Cosmetic changes to prologue.  (WRB)
C   891006  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ)
C   900510  Convert XERRWV calls to XERMSG calls.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  DP1VLU
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      INTEGER I,IC,ILO,IN,INP1,IUP,K1,K1I,K2,K3,K3P1,K3PN,K4,K4P1,K4PN,
     * KC,L,LM1,LP1,MAXORD,N,NDER,NDO,NDP1,NORD
      DOUBLE PRECISION A(*),CC,DIF,VAL,X,YFIT,YP(*)
      CHARACTER*8 XERN1, XERN2
C***FIRST EXECUTABLE STATEMENT  DP1VLU
      IF (L .LT. 0) GO TO 12
      NDO = MAX(NDER,0)
      NDO = MIN(NDO,L)
      MAXORD = A(1) + 0.5D0
      K1 = MAXORD + 1
      K2 = K1 + MAXORD
      K3 = K2 + MAXORD + 2
      NORD = A(K3) + 0.5D0
      IF (L .GT. NORD) GO TO 11
      K4 = K3 + L + 1
      IF (NDER .LT. 1) GO TO 2
      DO 1 I = 1,NDER
 1      YP(I) = 0.0D0
 2    IF (L .GE. 2) GO TO 4
      IF (L .EQ. 1) GO TO 3
C
C L IS 0
C
      VAL = A(K2+1)
      GO TO 10
C
C L IS 1
C
 3    CC = A(K2+2)
      VAL = A(K2+1) + (X-A(2))*CC
      IF (NDER .GE. 1) YP(1) = CC
      GO TO 10
C
C L IS GREATER THAN 1
C
 4    NDP1 = NDO + 1
      K3P1 = K3 + 1
      K4P1 = K4 + 1
      LP1 = L + 1
      LM1 = L - 1
      ILO = K3 + 3
      IUP = K4 + NDP1
      DO 5 I = ILO,IUP
 5      A(I) = 0.0D0
      DIF = X - A(LP1)
      KC = K2 + LP1
      A(K4P1) = A(KC)
      A(K3P1) = A(KC-1) + DIF*A(K4P1)
      A(K3+2) = A(K4P1)
C
C EVALUATE RECURRENCE RELATIONS FOR FUNCTION VALUE AND DERIVATIVES
C
      DO 9 I = 1,LM1
        IN = L - I
        INP1 = IN + 1
        K1I = K1 + INP1
        IC = K2 + IN
        DIF = X - A(INP1)
        VAL = A(IC) + DIF*A(K3P1) - A(K1I)*A(K4P1)
        IF (NDO .LE. 0) GO TO 8
        DO 6 N = 1,NDO
          K3PN = K3P1 + N
          K4PN = K4P1 + N
 6        YP(N) = DIF*A(K3PN) + N*A(K3PN-1) - A(K1I)*A(K4PN)
C
C SAVE VALUES NEEDED FOR NEXT EVALUATION OF RECURRENCE RELATIONS
C
        DO 7 N = 1,NDO
          K3PN = K3P1 + N
          K4PN = K4P1 + N
          A(K4PN) = A(K3PN)
 7        A(K3PN) = YP(N)
 8      A(K4P1) = A(K3P1)
 9      A(K3P1) = VAL
C
C NORMAL RETURN OR ABORT DUE TO ERROR
C
 10   YFIT = VAL
      RETURN
C
   11 WRITE (XERN1, '(I8)') L
      WRITE (XERN2, '(I8)') NORD
      CALL XERMSG ('SLATEC', 'DP1VLU',
     *   'THE ORDER OF POLYNOMIAL EVALUATION, L = ' // XERN1 //
     *   ' REQUESTED EXCEEDS THE HIGHEST ORDER FIT, NORD = ' // XERN2 //
     *   ', COMPUTED BY DPOLFT -- EXECUTION TERMINATED.', 8, 2)
      RETURN
C
   12 CALL XERMSG ('SLATEC', 'DP1VLU',
     +   'INVALID INPUT PARAMETER.  ORDER OF POLYNOMIAL EVALUATION ' //
     +   'REQUESTED IS NEGATIVE.', 2, 2)
      RETURN
      END
*DECK PVALUE
      SUBROUTINE PVALUE (L, NDER, X, YFIT, YP, A)
C***BEGIN PROLOGUE  PVALUE
C***PURPOSE  Use the coefficients generated by POLFIT to evaluate the
C            polynomial fit of degree L, along with the first NDER of
C            its derivatives, at a specified point.
C***LIBRARY   SLATEC
C***CATEGORY  K6
C***TYPE      SINGLE PRECISION (PVALUE-S, DP1VLU-D)
C***KEYWORDS  CURVE FITTING, LEAST SQUARES, POLYNOMIAL APPROXIMATION
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C***DESCRIPTION
C
C     Written by L. F. Shampine and S. M. Davenport.
C
C     Abstract
C
C     The subroutine  PVALUE  uses the coefficients generated by  POLFIT
C     to evaluate the polynomial fit of degree  L , along with the first
C     NDER  of its derivatives, at a specified point.  Computationally
C     stable recurrence relations are used to perform this task.
C
C     The parameters for  PVALUE  are
C
C     Input --
C         L -      the degree of polynomial to be evaluated.  L  may be
C                  any non-negative integer which is less than or equal
C                  to  NDEG , the highest degree polynomial provided
C                  by  POLFIT .
C         NDER -   the number of derivatives to be evaluated.  NDER
C                  may be 0 or any positive value.  If NDER is less
C                  than 0, it will be treated as 0.
C         X -      the argument at which the polynomial and its
C                  derivatives are to be evaluated.
C         A -      work and output array containing values from last
C                  call to  POLFIT .
C
C     Output --
C         YFIT -   value of the fitting polynomial of degree  L  at  X
C         YP -     array containing the first through  NDER  derivatives
C                  of the polynomial of degree  L .  YP  must be
C                  dimensioned at least  NDER  in the calling program.
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  XERMSG
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   890531  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ)
C   900510  Convert XERRWV calls to XERMSG calls.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  PVALUE
      DIMENSION YP(*),A(*)
      CHARACTER*8 XERN1, XERN2
C***FIRST EXECUTABLE STATEMENT  PVALUE
      IF (L .LT. 0) GO TO 12
      NDO = MAX(NDER,0)
      NDO = MIN(NDO,L)
      MAXORD = A(1) + 0.5
      K1 = MAXORD + 1
      K2 = K1 + MAXORD
      K3 = K2 + MAXORD + 2
      NORD = A(K3) + 0.5
      IF (L .GT. NORD) GO TO 11
      K4 = K3 + L + 1
      IF (NDER .LT. 1) GO TO 2
      DO 1 I = 1,NDER
 1      YP(I) = 0.0
 2    IF (L .GE. 2) GO TO 4
      IF (L .EQ. 1) GO TO 3
C
C L IS 0
C
      VAL = A(K2+1)
      GO TO 10
C
C L IS 1
C
 3    CC = A(K2+2)
      VAL = A(K2+1) + (X-A(2))*CC
      IF (NDER .GE. 1) YP(1) = CC
      GO TO 10
C
C L IS GREATER THAN 1
C
 4    NDP1 = NDO + 1
      K3P1 = K3 + 1
      K4P1 = K4 + 1
      LP1 = L + 1
      LM1 = L - 1
      ILO = K3 + 3
      IUP = K4 + NDP1
      DO 5 I = ILO,IUP
 5      A(I) = 0.0
      DIF = X - A(LP1)
      KC = K2 + LP1
      A(K4P1) = A(KC)
      A(K3P1) = A(KC-1) + DIF*A(K4P1)
      A(K3+2) = A(K4P1)
C
C EVALUATE RECURRENCE RELATIONS FOR FUNCTION VALUE AND DERIVATIVES
C
      DO 9 I = 1,LM1
        IN = L - I
        INP1 = IN + 1
        K1I = K1 + INP1
        IC = K2 + IN
        DIF = X - A(INP1)
        VAL = A(IC) + DIF*A(K3P1) - A(K1I)*A(K4P1)
        IF (NDO .LE. 0) GO TO 8
        DO 6 N = 1,NDO
          K3PN = K3P1 + N
          K4PN = K4P1 + N
 6        YP(N) = DIF*A(K3PN) + N*A(K3PN-1) - A(K1I)*A(K4PN)
C
C SAVE VALUES NEEDED FOR NEXT EVALUATION OF RECURRENCE RELATIONS
C
        DO 7 N = 1,NDO
          K3PN = K3P1 + N
          K4PN = K4P1 + N
          A(K4PN) = A(K3PN)
 7        A(K3PN) = YP(N)
 8      A(K4P1) = A(K3P1)
 9      A(K3P1) = VAL
C
C NORMAL RETURN OR ABORT DUE TO ERROR
C
 10   YFIT = VAL
      RETURN
C
   11 WRITE (XERN1, '(I8)') L
      WRITE (XERN2, '(I8)') NORD
      CALL XERMSG ('SLATEC', 'PVALUE',
     *   'THE ORDER OF POLYNOMIAL EVALUATION, L = ' // XERN1 //
     *   ' REQUESTED EXCEEDS THE HIGHEST ORDER FIT, NORD = ' // XERN2 //
     *   ', COMPUTED BY POLFIT -- EXECUTION TERMINATED.', 8, 2)
      RETURN
C
   12 CALL XERMSG ('SLATEC', 'PVALUE',
     +   'INVALID INPUT PARAMETER.  ORDER OF POLYNOMIAL EVALUATION ' //
     +   'REQUESTED IS NEGATIVE -- EXECUTION TERMINATED.', 2, 2)
      RETURN
      END
*DECK DPOLFT
      SUBROUTINE DPOLFT (N, X, Y, W, MAXDEG, NDEG, EPS, R, IERR, A)
C***BEGIN PROLOGUE  DPOLFT
C***PURPOSE  Fit discrete data in a least squares sense by polynomials
C            in one variable.
C***LIBRARY   SLATEC
C***CATEGORY  K1A1A2
C***TYPE      DOUBLE PRECISION (POLFIT-S, DPOLFT-D)
C***KEYWORDS  CURVE FITTING, DATA FITTING, LEAST SQUARES, POLYNOMIAL FIT
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C           Huddleston, R. E., (SNLL)
C***DESCRIPTION
C
C     Abstract
C
C     Given a collection of points X(I) and a set of values Y(I) which
C     correspond to some function or measurement at each of the X(I),
C     subroutine  DPOLFT  computes the weighted least-squares polynomial
C     fits of all degrees up to some degree either specified by the user
C     or determined by the routine.  The fits thus obtained are in
C     orthogonal polynomial form.  Subroutine  DP1VLU  may then be
C     called to evaluate the fitted polynomials and any of their
C     derivatives at any point.  The subroutine  DPCOEF  may be used to
C     express the polynomial fits as powers of (X-C) for any specified
C     point C.
C
C     The parameters for  DPOLFT  are
C
C     Input -- All TYPE REAL variables are DOUBLE PRECISION
C         N -      the number of data points.  The arrays X, Y and W
C                  must be dimensioned at least  N  (N .GE. 1).
C         X -      array of values of the independent variable.  These
C                  values may appear in any order and need not all be
C                  distinct.
C         Y -      array of corresponding function values.
C         W -      array of positive values to be used as weights.  If
C                  W(1) is negative,  DPOLFT  will set all the weights
C                  to 1.0, which means unweighted least squares error
C                  will be minimized.  To minimize relative error, the
C                  user should set the weights to:  W(I) = 1.0/Y(I)**2,
C                  I = 1,...,N .
C         MAXDEG - maximum degree to be allowed for polynomial fit.
C                  MAXDEG  may be any non-negative integer less than  N.
C                  Note -- MAXDEG  cannot be equal to  N-1  when a
C                  statistical test is to be used for degree selection,
C                  i.e., when input value of  EPS  is negative.
C         EPS -    specifies the criterion to be used in determining
C                  the degree of fit to be computed.
C                  (1)  If  EPS  is input negative,  DPOLFT  chooses the
C                       degree based on a statistical F test of
C                       significance.  One of three possible
C                       significance levels will be used:  .01, .05 or
C                       .10.  If  EPS=-1.0 , the routine will
C                       automatically select one of these levels based
C                       on the number of data points and the maximum
C                       degree to be considered.  If  EPS  is input as
C                       -.01, -.05, or -.10, a significance level of
C                       .01, .05, or .10, respectively, will be used.
C                  (2)  If  EPS  is set to 0.,  DPOLFT  computes the
C                       polynomials of degrees 0 through  MAXDEG .
C                  (3)  If  EPS  is input positive,  EPS  is the RMS
C                       error tolerance which must be satisfied by the
C                       fitted polynomial.  DPOLFT  will increase the
C                       degree of fit until this criterion is met or
C                       until the maximum degree is reached.
C
C     Output -- All TYPE REAL variables are DOUBLE PRECISION
C         NDEG -   degree of the highest degree fit computed.
C         EPS -    RMS error of the polynomial of degree  NDEG .
C         R -      vector of dimension at least NDEG containing values
C                  of the fit of degree  NDEG  at each of the  X(I) .
C                  Except when the statistical test is used, these
C                  values are more accurate than results from subroutine
C                  DP1VLU  normally are.
C         IERR -   error flag with the following possible values.
C             1 -- indicates normal execution, i.e., either
C                  (1)  the input value of  EPS  was negative, and the
C                       computed polynomial fit of degree  NDEG
C                       satisfies the specified F test, or
C                  (2)  the input value of  EPS  was 0., and the fits of
C                       all degrees up to  MAXDEG  are complete, or
C                  (3)  the input value of  EPS  was positive, and the
C                       polynomial of degree  NDEG  satisfies the RMS
C                       error requirement.
C             2 -- invalid input parameter.  At least one of the input
C                  parameters has an illegal value and must be corrected
C                  before  DPOLFT  can proceed.  Valid input results
C                  when the following restrictions are observed
C                       N .GE. 1
C                       0 .LE. MAXDEG .LE. N-1  for  EPS .GE. 0.
C                       0 .LE. MAXDEG .LE. N-2  for  EPS .LT. 0.
C                       W(1)=-1.0  or  W(I) .GT. 0., I=1,...,N .
C             3 -- cannot satisfy the RMS error requirement with a
C                  polynomial of degree no greater than  MAXDEG .  Best
C                  fit found is of degree  MAXDEG .
C             4 -- cannot satisfy the test for significance using
C                  current value of  MAXDEG .  Statistically, the
C                  best fit found is of order  NORD .  (In this case,
C                  NDEG will have one of the values:  MAXDEG-2,
C                  MAXDEG-1, or MAXDEG).  Using a higher value of
C                  MAXDEG  may result in passing the test.
C         A -      work and output array having at least 3N+3MAXDEG+3
C                  locations
C
C     Note - DPOLFT  calculates all fits of degrees up to and including
C            NDEG .  Any or all of these fits can be evaluated or
C            expressed as powers of (X-C) using  DP1VLU  and  DPCOEF
C            after just one call to  DPOLFT .
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  DP1VLU, XERMSG
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   891006  Cosmetic changes to prologue.  (WRB)
C   891006  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ)
C   900911  Added variable YP to DOUBLE PRECISION declaration.  (WRB)
C   920501  Reformatted the REFERENCES section.  (WRB)
C   920527  Corrected erroneous statements in DESCRIPTION.  (WRB)
C***END PROLOGUE  DPOLFT
      INTEGER I,IDEGF,IERR,J,JP1,JPAS,K1,K1PJ,K2,K2PJ,K3,K3PI,K4,
     * K4PI,K5,K5PI,KSIG,M,MAXDEG,MOP1,NDEG,NDER,NFAIL
      DOUBLE PRECISION TEMD1,TEMD2
      DOUBLE PRECISION A(*),DEGF,DEN,EPS,ETST,F,FCRIT,R(*),SIG,SIGJ,
     * SIGJM1,SIGPAS,TEMP,X(*),XM,Y(*),YP,W(*),W1,W11
      DOUBLE PRECISION CO(4,3)
      SAVE CO
      DATA  CO(1,1), CO(2,1), CO(3,1), CO(4,1), CO(1,2), CO(2,2),
     1      CO(3,2), CO(4,2), CO(1,3), CO(2,3), CO(3,3),
     2  CO(4,3)/-13.086850D0,-2.4648165D0,-3.3846535D0,-1.2973162D0,
     3          -3.3381146D0,-1.7812271D0,-3.2578406D0,-1.6589279D0,
     4          -1.6282703D0,-1.3152745D0,-3.2640179D0,-1.9829776D0/
C***FIRST EXECUTABLE STATEMENT  DPOLFT
      M = ABS(N)
      IF (M .EQ. 0) GO TO 30
      IF (MAXDEG .LT. 0) GO TO 30
      A(1) = MAXDEG
      MOP1 = MAXDEG + 1
      IF (M .LT. MOP1) GO TO 30
      IF (EPS .LT. 0.0D0 .AND.  M .EQ. MOP1) GO TO 30
      XM = M
      ETST = EPS*EPS*XM
      IF (W(1) .LT. 0.0D0) GO TO 2
      DO 1 I = 1,M
        IF (W(I) .LE. 0.0D0) GO TO 30
 1      CONTINUE
      GO TO 4
 2    DO 3 I = 1,M
 3      W(I) = 1.0D0
 4    IF (EPS .GE. 0.0D0) GO TO 8
C
C DETERMINE SIGNIFICANCE LEVEL INDEX TO BE USED IN STATISTICAL TEST FOR
C CHOOSING DEGREE OF POLYNOMIAL FIT
C
      IF (EPS .GT. (-.55D0)) GO TO 5
      IDEGF = M - MAXDEG - 1
      KSIG = 1
      IF (IDEGF .LT. 10) KSIG = 2
      IF (IDEGF .LT. 5) KSIG = 3
      GO TO 8
 5    KSIG = 1
      IF (EPS .LT. (-.03D0)) KSIG = 2
      IF (EPS .LT. (-.07D0)) KSIG = 3
C
C INITIALIZE INDEXES AND COEFFICIENTS FOR FITTING
C
 8    K1 = MAXDEG + 1
      K2 = K1 + MAXDEG
      K3 = K2 + MAXDEG + 2
      K4 = K3 + M
      K5 = K4 + M
      DO 9 I = 2,K4
 9      A(I) = 0.0D0
      W11 = 0.0D0
      IF (N .LT. 0) GO TO 11
C
C UNCONSTRAINED CASE
C
      DO 10 I = 1,M
        K4PI = K4 + I
        A(K4PI) = 1.0D0
 10     W11 = W11 + W(I)
      GO TO 13
C
C CONSTRAINED CASE
C
 11   DO 12 I = 1,M
        K4PI = K4 + I
 12     W11 = W11 + W(I)*A(K4PI)**2
C
C COMPUTE FIT OF DEGREE ZERO
C
 13   TEMD1 = 0.0D0
      DO 14 I = 1,M
        K4PI = K4 + I
        TEMD1 = TEMD1 + W(I)*Y(I)*A(K4PI)
 14     CONTINUE
      TEMD1 = TEMD1/W11
      A(K2+1) = TEMD1
      SIGJ = 0.0D0
      DO 15 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = TEMD1*A(K4PI)
        R(I) = TEMD2
        A(K5PI) = TEMD2 - R(I)
 15     SIGJ = SIGJ + W(I)*((Y(I)-R(I)) - A(K5PI))**2
      J = 0
C
C SEE IF POLYNOMIAL OF DEGREE 0 SATISFIES THE DEGREE SELECTION CRITERION
C
      IF (EPS) 24,26,27
C
C INCREMENT DEGREE
C
 16   J = J + 1
      JP1 = J + 1
      K1PJ = K1 + J
      K2PJ = K2 + J
      SIGJM1 = SIGJ
C
C COMPUTE NEW B COEFFICIENT EXCEPT WHEN J = 1
C
      IF (J .GT. 1) A(K1PJ) = W11/W1
C
C COMPUTE NEW A COEFFICIENT
C
      TEMD1 = 0.0D0
      DO 18 I = 1,M
        K4PI = K4 + I
        TEMD2 = A(K4PI)
        TEMD1 = TEMD1 + X(I)*W(I)*TEMD2*TEMD2
 18     CONTINUE
      A(JP1) = TEMD1/W11
C
C EVALUATE ORTHOGONAL POLYNOMIAL AT DATA POINTS
C
      W1 = W11
      W11 = 0.0D0
      DO 19 I = 1,M
        K3PI = K3 + I
        K4PI = K4 + I
        TEMP = A(K3PI)
        A(K3PI) = A(K4PI)
        A(K4PI) = (X(I)-A(JP1))*A(K3PI) - A(K1PJ)*TEMP
 19     W11 = W11 + W(I)*A(K4PI)**2
C
C GET NEW ORTHOGONAL POLYNOMIAL COEFFICIENT USING PARTIAL DOUBLE
C PRECISION
C
      TEMD1 = 0.0D0
      DO 20 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = W(I)*((Y(I)-R(I))-A(K5PI))*A(K4PI)
 20     TEMD1 = TEMD1 + TEMD2
      TEMD1 = TEMD1/W11
      A(K2PJ+1) = TEMD1
C
C UPDATE POLYNOMIAL EVALUATIONS AT EACH OF THE DATA POINTS, AND
C ACCUMULATE SUM OF SQUARES OF ERRORS.  THE POLYNOMIAL EVALUATIONS ARE
C COMPUTED AND STORED IN EXTENDED PRECISION.  FOR THE I-TH DATA POINT,
C THE MOST SIGNIFICANT BITS ARE STORED IN  R(I) , AND THE LEAST
C SIGNIFICANT BITS ARE IN  A(K5PI) .
C
      SIGJ = 0.0D0
      DO 21 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = R(I) + A(K5PI) + TEMD1*A(K4PI)
        R(I) = TEMD2
        A(K5PI) = TEMD2 - R(I)
 21     SIGJ = SIGJ + W(I)*((Y(I)-R(I)) - A(K5PI))**2
C
C SEE IF DEGREE SELECTION CRITERION HAS BEEN SATISFIED OR IF DEGREE
C MAXDEG  HAS BEEN REACHED
C
      IF (EPS) 23,26,27
C
C COMPUTE F STATISTICS  (INPUT EPS .LT. 0.)
C
 23   IF (SIGJ .EQ. 0.0D0) GO TO 29
      DEGF = M - J - 1
      DEN = (CO(4,KSIG)*DEGF + 1.0D0)*DEGF
      FCRIT = (((CO(3,KSIG)*DEGF) + CO(2,KSIG))*DEGF + CO(1,KSIG))/DEN
      FCRIT = FCRIT*FCRIT
      F = (SIGJM1 - SIGJ)*DEGF/SIGJ
      IF (F .LT. FCRIT) GO TO 25
C
C POLYNOMIAL OF DEGREE J SATISFIES F TEST
C
 24   SIGPAS = SIGJ
      JPAS = J
      NFAIL = 0
      IF (MAXDEG .EQ. J) GO TO 32
      GO TO 16
C
C POLYNOMIAL OF DEGREE J FAILS F TEST.  IF THERE HAVE BEEN THREE
C SUCCESSIVE FAILURES, A STATISTICALLY BEST DEGREE HAS BEEN FOUND.
C
 25   NFAIL = NFAIL + 1
      IF (NFAIL .GE. 3) GO TO 29
      IF (MAXDEG .EQ. J) GO TO 32
      GO TO 16
C
C RAISE THE DEGREE IF DEGREE  MAXDEG  HAS NOT YET BEEN REACHED  (INPUT
C EPS = 0.)
C
 26   IF (MAXDEG .EQ. J) GO TO 28
      GO TO 16
C
C SEE IF RMS ERROR CRITERION IS SATISFIED  (INPUT EPS .GT. 0.)
C
 27   IF (SIGJ .LE. ETST) GO TO 28
      IF (MAXDEG .EQ. J) GO TO 31
      GO TO 16
C
C RETURNS
C
 28   IERR = 1
      NDEG = J
      SIG = SIGJ
      GO TO 33
 29   IERR = 1
      NDEG = JPAS
      SIG = SIGPAS
      GO TO 33
 30   IERR = 2
      CALL XERMSG ('SLATEC', 'DPOLFT', 'INVALID INPUT PARAMETER.', 2,
     +   1)
      GO TO 37
 31   IERR = 3
      NDEG = MAXDEG
      SIG = SIGJ
      GO TO 33
 32   IERR = 4
      NDEG = JPAS
      SIG = SIGPAS
C
 33   A(K3) = NDEG
C
C WHEN STATISTICAL TEST HAS BEEN USED, EVALUATE THE BEST POLYNOMIAL AT
C ALL THE DATA POINTS IF  R  DOES NOT ALREADY CONTAIN THESE VALUES
C
      IF(EPS .GE. 0.0  .OR.  NDEG .EQ. MAXDEG) GO TO 36
      NDER = 0
      DO 35 I = 1,M
        CALL DP1VLU (NDEG,NDER,X(I),R(I),YP,A)
 35     CONTINUE
 36   EPS = SQRT(SIG/XM)
 37   RETURN
      END
*DECK POLFIT
      SUBROUTINE POLFIT (N, X, Y, W, MAXDEG, NDEG, EPS, R, IERR, A)
C***BEGIN PROLOGUE  POLFIT
C***PURPOSE  Fit discrete data in a least squares sense by polynomials
C            in one variable.
C***LIBRARY   SLATEC
C***CATEGORY  K1A1A2
C***TYPE      SINGLE PRECISION (POLFIT-S, DPOLFT-D)
C***KEYWORDS  CURVE FITTING, DATA FITTING, LEAST SQUARES, POLYNOMIAL FIT
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C           Huddleston, R. E., (SNLL)
C***DESCRIPTION
C
C     Abstract
C
C     Given a collection of points X(I) and a set of values Y(I) which
C     correspond to some function or measurement at each of the X(I),
C     subroutine  POLFIT  computes the weighted least-squares polynomial
C     fits of all degrees up to some degree either specified by the user
C     or determined by the routine.  The fits thus obtained are in
C     orthogonal polynomial form.  Subroutine  PVALUE  may then be
C     called to evaluate the fitted polynomials and any of their
C     derivatives at any point.  The subroutine  PCOEF  may be used to
C     express the polynomial fits as powers of (X-C) for any specified
C     point C.
C
C     The parameters for  POLFIT  are
C
C     Input --
C         N -      the number of data points.  The arrays X, Y and W
C                  must be dimensioned at least  N  (N .GE. 1).
C         X -      array of values of the independent variable.  These
C                  values may appear in any order and need not all be
C                  distinct.
C         Y -      array of corresponding function values.
C         W -      array of positive values to be used as weights.  If
C                  W(1) is negative,  POLFIT  will set all the weights
C                  to 1.0, which means unweighted least squares error
C                  will be minimized.  To minimize relative error, the
C                  user should set the weights to:  W(I) = 1.0/Y(I)**2,
C                  I = 1,...,N .
C         MAXDEG - maximum degree to be allowed for polynomial fit.
C                  MAXDEG  may be any non-negative integer less than  N.
C                  Note -- MAXDEG  cannot be equal to  N-1  when a
C                  statistical test is to be used for degree selection,
C                  i.e., when input value of  EPS  is negative.
C         EPS -    specifies the criterion to be used in determining
C                  the degree of fit to be computed.
C                  (1)  If  EPS  is input negative,  POLFIT  chooses the
C                       degree based on a statistical F test of
C                       significance.  One of three possible
C                       significance levels will be used:  .01, .05 or
C                       .10.  If  EPS=-1.0 , the routine will
C                       automatically select one of these levels based
C                       on the number of data points and the maximum
C                       degree to be considered.  If  EPS  is input as
C                       -.01, -.05, or -.10, a significance level of
C                       .01, .05, or .10, respectively, will be used.
C                  (2)  If  EPS  is set to 0.,  POLFIT  computes the
C                       polynomials of degrees 0 through  MAXDEG .
C                  (3)  If  EPS  is input positive,  EPS  is the RMS
C                       error tolerance which must be satisfied by the
C                       fitted polynomial.  POLFIT  will increase the
C                       degree of fit until this criterion is met or
C                       until the maximum degree is reached.
C
C     Output --
C         NDEG -   degree of the highest degree fit computed.
C         EPS -    RMS error of the polynomial of degree  NDEG .
C         R -      vector of dimension at least NDEG containing values
C                  of the fit of degree  NDEG  at each of the  X(I) .
C                  Except when the statistical test is used, these
C                  values are more accurate than results from subroutine
C                  PVALUE  normally are.
C         IERR -   error flag with the following possible values.
C             1 -- indicates normal execution, i.e., either
C                  (1)  the input value of  EPS  was negative, and the
C                       computed polynomial fit of degree  NDEG
C                       satisfies the specified F test, or
C                  (2)  the input value of  EPS  was 0., and the fits of
C                       all degrees up to  MAXDEG  are complete, or
C                  (3)  the input value of  EPS  was positive, and the
C                       polynomial of degree  NDEG  satisfies the RMS
C                       error requirement.
C             2 -- invalid input parameter.  At least one of the input
C                  parameters has an illegal value and must be corrected
C                  before  POLFIT  can proceed.  Valid input results
C                  when the following restrictions are observed
C                       N .GE. 1
C                       0 .LE. MAXDEG .LE. N-1  for  EPS .GE. 0.
C                       0 .LE. MAXDEG .LE. N-2  for  EPS .LT. 0.
C                       W(1)=-1.0  or  W(I) .GT. 0., I=1,...,N .
C             3 -- cannot satisfy the RMS error requirement with a
C                  polynomial of degree no greater than  MAXDEG .  Best
C                  fit found is of degree  MAXDEG .
C             4 -- cannot satisfy the test for significance using
C                  current value of  MAXDEG .  Statistically, the
C                  best fit found is of order  NORD .  (In this case,
C                  NDEG will have one of the values:  MAXDEG-2,
C                  MAXDEG-1, or MAXDEG).  Using a higher value of
C                  MAXDEG  may result in passing the test.
C         A -      work and output array having at least 3N+3MAXDEG+3
C                  locations
C
C     Note - POLFIT  calculates all fits of degrees up to and including
C            NDEG .  Any or all of these fits can be evaluated or
C            expressed as powers of (X-C) using  PVALUE  and  PCOEF
C            after just one call to  POLFIT .
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  PVALUE, XERMSG
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   890531  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ)
C   920501  Reformatted the REFERENCES section.  (WRB)
C   920527  Corrected erroneous statements in DESCRIPTION.  (WRB)
C***END PROLOGUE  POLFIT
      DOUBLE PRECISION TEMD1,TEMD2
      DIMENSION X(*), Y(*), W(*), R(*), A(*)
      DIMENSION CO(4,3)
      SAVE CO
      DATA  CO(1,1), CO(2,1), CO(3,1), CO(4,1), CO(1,2), CO(2,2),
     1      CO(3,2), CO(4,2), CO(1,3), CO(2,3), CO(3,3),
     2  CO(4,3)/-13.086850,-2.4648165,-3.3846535,-1.2973162,
     3          -3.3381146,-1.7812271,-3.2578406,-1.6589279,
     4          -1.6282703,-1.3152745,-3.2640179,-1.9829776/
C***FIRST EXECUTABLE STATEMENT  POLFIT
      M = ABS(N)
      IF (M .EQ. 0) GO TO 30
      IF (MAXDEG .LT. 0) GO TO 30
      A(1) = MAXDEG
      MOP1 = MAXDEG + 1
      IF (M .LT. MOP1) GO TO 30
      IF (EPS .LT. 0.0  .AND.  M .EQ. MOP1) GO TO 30
      XM = M
      ETST = EPS*EPS*XM
      IF (W(1) .LT. 0.0) GO TO 2
      DO 1 I = 1,M
        IF (W(I) .LE. 0.0) GO TO 30
 1      CONTINUE
      GO TO 4
 2    DO 3 I = 1,M
 3      W(I) = 1.0
 4    IF (EPS .GE. 0.0) GO TO 8
C
C DETERMINE SIGNIFICANCE LEVEL INDEX TO BE USED IN STATISTICAL TEST FOR
C CHOOSING DEGREE OF POLYNOMIAL FIT
C
      IF (EPS .GT. (-.55)) GO TO 5
      IDEGF = M - MAXDEG - 1
      KSIG = 1
      IF (IDEGF .LT. 10) KSIG = 2
      IF (IDEGF .LT. 5) KSIG = 3
      GO TO 8
 5    KSIG = 1
      IF (EPS .LT. (-.03)) KSIG = 2
      IF (EPS .LT. (-.07)) KSIG = 3
C
C INITIALIZE INDEXES AND COEFFICIENTS FOR FITTING
C
 8    K1 = MAXDEG + 1
      K2 = K1 + MAXDEG
      K3 = K2 + MAXDEG + 2
      K4 = K3 + M
      K5 = K4 + M
      DO 9 I = 2,K4
 9      A(I) = 0.0
      W11 = 0.0
      IF (N .LT. 0) GO TO 11
C
C UNCONSTRAINED CASE
C
      DO 10 I = 1,M
        K4PI = K4 + I
        A(K4PI) = 1.0
 10     W11 = W11 + W(I)
      GO TO 13
C
C CONSTRAINED CASE
C
 11   DO 12 I = 1,M
        K4PI = K4 + I
 12     W11 = W11 + W(I)*A(K4PI)**2
C
C COMPUTE FIT OF DEGREE ZERO
C
 13   TEMD1 = 0.0D0
      DO 14 I = 1,M
        K4PI = K4 + I
        TEMD1 = TEMD1 + DBLE(W(I))*DBLE(Y(I))*DBLE(A(K4PI))
 14     CONTINUE
      TEMD1 = TEMD1/DBLE(W11)
      A(K2+1) = TEMD1
      SIGJ = 0.0
      DO 15 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = TEMD1*DBLE(A(K4PI))
        R(I) = TEMD2
        A(K5PI) = TEMD2 - DBLE(R(I))
 15     SIGJ = SIGJ + W(I)*((Y(I)-R(I)) - A(K5PI))**2
      J = 0
C
C SEE IF POLYNOMIAL OF DEGREE 0 SATISFIES THE DEGREE SELECTION CRITERION
C
      IF (EPS) 24,26,27
C
C INCREMENT DEGREE
C
 16   J = J + 1
      JP1 = J + 1
      K1PJ = K1 + J
      K2PJ = K2 + J
      SIGJM1 = SIGJ
C
C COMPUTE NEW B COEFFICIENT EXCEPT WHEN J = 1
C
      IF (J .GT. 1) A(K1PJ) = W11/W1
C
C COMPUTE NEW A COEFFICIENT
C
      TEMD1 = 0.0D0
      DO 18 I = 1,M
        K4PI = K4 + I
        TEMD2 = A(K4PI)
        TEMD1 = TEMD1 + DBLE(X(I))*DBLE(W(I))*TEMD2*TEMD2
 18     CONTINUE
      A(JP1) = TEMD1/DBLE(W11)
C
C EVALUATE ORTHOGONAL POLYNOMIAL AT DATA POINTS
C
      W1 = W11
      W11 = 0.0
      DO 19 I = 1,M
        K3PI = K3 + I
        K4PI = K4 + I
        TEMP = A(K3PI)
        A(K3PI) = A(K4PI)
        A(K4PI) = (X(I)-A(JP1))*A(K3PI) - A(K1PJ)*TEMP
 19     W11 = W11 + W(I)*A(K4PI)**2
C
C GET NEW ORTHOGONAL POLYNOMIAL COEFFICIENT USING PARTIAL DOUBLE
C PRECISION
C
      TEMD1 = 0.0D0
      DO 20 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = DBLE(W(I))*DBLE((Y(I)-R(I))-A(K5PI))*DBLE(A(K4PI))
 20     TEMD1 = TEMD1 + TEMD2
      TEMD1 = TEMD1/DBLE(W11)
      A(K2PJ+1) = TEMD1
C
C UPDATE POLYNOMIAL EVALUATIONS AT EACH OF THE DATA POINTS, AND
C ACCUMULATE SUM OF SQUARES OF ERRORS.  THE POLYNOMIAL EVALUATIONS ARE
C COMPUTED AND STORED IN EXTENDED PRECISION.  FOR THE I-TH DATA POINT,
C THE MOST SIGNIFICANT BITS ARE STORED IN  R(I) , AND THE LEAST
C SIGNIFICANT BITS ARE IN  A(K5PI) .
C
      SIGJ = 0.0
      DO 21 I = 1,M
        K4PI = K4 + I
        K5PI = K5 + I
        TEMD2 = DBLE(R(I)) + DBLE(A(K5PI)) + TEMD1*DBLE(A(K4PI))
        R(I) = TEMD2
        A(K5PI) = TEMD2 - DBLE(R(I))
 21     SIGJ = SIGJ + W(I)*((Y(I)-R(I)) - A(K5PI))**2
C
C SEE IF DEGREE SELECTION CRITERION HAS BEEN SATISFIED OR IF DEGREE
C MAXDEG  HAS BEEN REACHED
C
      IF (EPS) 23,26,27
C
C COMPUTE F STATISTICS  (INPUT EPS .LT. 0.)
C
 23   IF (SIGJ .EQ. 0.0) GO TO 29
      DEGF = M - J - 1
      DEN = (CO(4,KSIG)*DEGF + 1.0)*DEGF
      FCRIT = (((CO(3,KSIG)*DEGF) + CO(2,KSIG))*DEGF + CO(1,KSIG))/DEN
      FCRIT = FCRIT*FCRIT
      F = (SIGJM1 - SIGJ)*DEGF/SIGJ
      IF (F .LT. FCRIT) GO TO 25
C
C POLYNOMIAL OF DEGREE J SATISFIES F TEST
C
 24   SIGPAS = SIGJ
      JPAS = J
      NFAIL = 0
      IF (MAXDEG .EQ. J) GO TO 32
      GO TO 16
C
C POLYNOMIAL OF DEGREE J FAILS F TEST.  IF THERE HAVE BEEN THREE
C SUCCESSIVE FAILURES, A STATISTICALLY BEST DEGREE HAS BEEN FOUND.
C
 25   NFAIL = NFAIL + 1
      IF (NFAIL .GE. 3) GO TO 29
      IF (MAXDEG .EQ. J) GO TO 32
      GO TO 16
C
C RAISE THE DEGREE IF DEGREE  MAXDEG  HAS NOT YET BEEN REACHED  (INPUT
C EPS = 0.)
C
 26   IF (MAXDEG .EQ. J) GO TO 28
      GO TO 16
C
C SEE IF RMS ERROR CRITERION IS SATISFIED  (INPUT EPS .GT. 0.)
C
 27   IF (SIGJ .LE. ETST) GO TO 28
      IF (MAXDEG .EQ. J) GO TO 31
      GO TO 16
C
C RETURNS
C
 28   IERR = 1
      NDEG = J
      SIG = SIGJ
      GO TO 33
 29   IERR = 1
      NDEG = JPAS
      SIG = SIGPAS
      GO TO 33
 30   IERR = 2
      CALL XERMSG ('SLATEC', 'POLFIT', 'INVALID INPUT PARAMETER.', 2,
     +   1)
      GO TO 37
 31   IERR = 3
      NDEG = MAXDEG
      SIG = SIGJ
      GO TO 33
 32   IERR = 4
      NDEG = JPAS
      SIG = SIGPAS
C
 33   A(K3) = NDEG
C
C WHEN STATISTICAL TEST HAS BEEN USED, EVALUATE THE BEST POLYNOMIAL AT
C ALL THE DATA POINTS IF  R  DOES NOT ALREADY CONTAIN THESE VALUES
C
      IF(EPS .GE. 0.0  .OR.  NDEG .EQ. MAXDEG) GO TO 36
      NDER = 0
      DO 35 I = 1,M
        CALL PVALUE (NDEG,NDER,X(I),R(I),YP,A)
 35     CONTINUE
 36   EPS = SQRT(SIG/XM)
 37   RETURN
      END
*DECK DPCOEF
      SUBROUTINE DPCOEF (L, C, TC, A)
C***BEGIN PROLOGUE  DPCOEF
C***PURPOSE  Convert the DPOLFT coefficients to Taylor series form.
C***LIBRARY   SLATEC
C***CATEGORY  K1A1A2
C***TYPE      DOUBLE PRECISION (PCOEF-S, DPCOEF-D)
C***KEYWORDS  CURVE FITTING, DATA FITTING, LEAST SQUARES, POLYNOMIAL FIT
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C***DESCRIPTION
C
C     Abstract
C
C     DPOLFT  computes the least squares polynomial fit of degree  L  as
C     a sum of orthogonal polynomials.  DPCOEF  changes this fit to its
C     Taylor expansion about any point  C , i.e. writes the polynomial
C     as a sum of powers of (X-C).  Taking  C=0.  gives the polynomial
C     in powers of X, but a suitable non-zero  C  often leads to
C     polynomials which are better scaled and more accurately evaluated.
C
C     The parameters for  DPCOEF  are
C
C     INPUT -- All TYPE REAL variables are DOUBLE PRECISION
C         L -      Indicates the degree of polynomial to be changed to
C                  its Taylor expansion.  To obtain the Taylor
C                  coefficients in reverse order, input  L  as the
C                  negative of the degree desired.  The absolute value
C                  of L  must be less than or equal to NDEG, the highest
C                  degree polynomial fitted by  DPOLFT .
C         C -      The point about which the Taylor expansion is to be
C                  made.
C         A -      Work and output array containing values from last
C                  call to  DPOLFT .
C
C     OUTPUT -- All TYPE REAL variables are DOUBLE PRECISION
C         TC -     Vector containing the first LL+1 Taylor coefficients
C                  where LL=ABS(L).  If  L.GT.0 , the coefficients are
C                  in the usual Taylor series order, i.e.
C                    P(X) = TC(1) + TC(2)*(X-C) + ... + TC(N+1)*(X-C)**N
C                  If L .LT. 0, the coefficients are in reverse order,
C                  i.e.
C                    P(X) = TC(1)*(X-C)**N + ... + TC(N)*(X-C) + TC(N+1)
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  DP1VLU
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   891006  Cosmetic changes to prologue.  (WRB)
C   891006  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  DPCOEF
C
      INTEGER I,L,LL,LLP1,LLP2,NEW,NR
      DOUBLE PRECISION A(*),C,FAC,SAVE,TC(*)
C***FIRST EXECUTABLE STATEMENT  DPCOEF
      LL = ABS(L)
      LLP1 = LL + 1
      CALL DP1VLU (LL,LL,C,TC(1),TC(2),A)
      IF (LL .LT. 2) GO TO 2
      FAC = 1.0D0
      DO 1 I = 3,LLP1
        FAC = FAC*(I-1)
 1      TC(I) = TC(I)/FAC
 2    IF (L .GE. 0) GO TO 4
      NR = LLP1/2
      LLP2 = LL + 2
      DO 3 I = 1,NR
        SAVE = TC(I)
        NEW = LLP2 - I
        TC(I) = TC(NEW)
 3      TC(NEW) = SAVE
 4    RETURN
      END
*DECK PCOEF
      SUBROUTINE PCOEF (L, C, TC, A)
C***BEGIN PROLOGUE  PCOEF
C***PURPOSE  Convert the POLFIT coefficients to Taylor series form.
C***LIBRARY   SLATEC
C***CATEGORY  K1A1A2
C***TYPE      SINGLE PRECISION (PCOEF-S, DPCOEF-D)
C***KEYWORDS  CURVE FITTING, DATA FITTING, LEAST SQUARES, POLYNOMIAL FIT
C***AUTHOR  Shampine, L. F., (SNLA)
C           Davenport, S. M., (SNLA)
C***DESCRIPTION
C
C     Written BY L. F. Shampine and S. M. Davenport.
C
C     Abstract
C
C     POLFIT  computes the least squares polynomial fit of degree  L  as
C     a sum of orthogonal polynomials.  PCOEF  changes this fit to its
C     Taylor expansion about any point  C , i.e. writes the polynomial
C     as a sum of powers of (X-C).  Taking  C=0.  gives the polynomial
C     in powers of X, but a suitable non-zero  C  often leads to
C     polynomials which are better scaled and more accurately evaluated.
C
C     The parameters for  PCOEF  are
C
C     INPUT --
C         L -      Indicates the degree of polynomial to be changed to
C                  its Taylor expansion.  To obtain the Taylor
C                  coefficients in reverse order, input  L  as the
C                  negative of the degree desired.  The absolute value
C                  of L  must be less than or equal to NDEG, the highest
C                  degree polynomial fitted by  POLFIT .
C         C -      The point about which the Taylor expansion is to be
C                  made.
C         A -      Work and output array containing values from last
C                  call to  POLFIT .
C
C     OUTPUT --
C         TC -     Vector containing the first LL+1 Taylor coefficients
C                  where LL=ABS(L).  If  L.GT.0 , the coefficients are
C                  in the usual Taylor series order, i.e.
C                    P(X) = TC(1) + TC(2)*(X-C) + ... + TC(N+1)*(X-C)**N
C                  If L .LT. 0, the coefficients are in reverse order,
C                  i.e.
C                    P(X) = TC(1)*(X-C)**N + ... + TC(N)*(X-C) + TC(N+1)
C
C***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston,
C                 Curve fitting by polynomials in one variable, Report
C                 SLA-74-0270, Sandia Laboratories, June 1974.
C***ROUTINES CALLED  PVALUE
C***REVISION HISTORY  (YYMMDD)
C   740601  DATE WRITTEN
C   890531  Changed all specific intrinsics to generic.  (WRB)
C   890531  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  PCOEF
C
      DIMENSION A(*), TC(*)
C***FIRST EXECUTABLE STATEMENT  PCOEF
      LL = ABS(L)
      LLP1 = LL + 1
      CALL PVALUE (LL,LL,C,TC(1),TC(2),A)
      IF (LL .LT. 2) GO TO 2
      FAC = 1.0
      DO 1 I = 3,LLP1
        FAC = FAC*(I-1)
 1      TC(I) = TC(I)/FAC
 2    IF (L .GE. 0) GO TO 4
      NR = LLP1/2
      LLP2 = LL + 2
      DO 3 I = 1,NR
        SAVE = TC(I)
        NEW = LLP2 - I
        TC(I) = TC(NEW)
 3      TC(NEW) = SAVE
 4    RETURN
      END
      subroutine  dscal(n,da,dx,incx)
c
c     scales a vector by a constant.
c     uses unrolled loops for increment equal to one.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      double precision da,dx(1)
      integer i,incx,m,mp1,n,nincx
c
      if( n.le.0 .or. incx.le.0 )return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      nincx = n*incx
      do 10 i = 1,nincx,incx
        dx(i) = da*dx(i)
   10 continue
      return
c
c        code for increment equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,5)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dx(i) = da*dx(i)
   30 continue
      if( n .lt. 5 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,5
        dx(i) = da*dx(i)
        dx(i + 1) = da*dx(i + 1)
        dx(i + 2) = da*dx(i + 2)
        dx(i + 3) = da*dx(i + 3)
        dx(i + 4) = da*dx(i + 4)
   50 continue
      return
      end
      subroutine sscal(n,sa,sx,incx)
c
c     scales a vector by a constant.
c     uses unrolled loops for increment equal to 1.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      real sa,sx(1)
      integer i,incx,m,mp1,n,nincx
c
      if( n.le.0 .or. incx.le.0 )return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      nincx = n*incx
      do 10 i = 1,nincx,incx
        sx(i) = sa*sx(i)
   10 continue
      return
c
c        code for increment equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,5)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        sx(i) = sa*sx(i)
   30 continue
      if( n .lt. 5 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,5
        sx(i) = sa*sx(i)
        sx(i + 1) = sa*sx(i + 1)
        sx(i + 2) = sa*sx(i + 2)
        sx(i + 3) = sa*sx(i + 3)
        sx(i + 4) = sa*sx(i + 4)
   50 continue
      return
      end
      subroutine dgbco(abd,lda,n,ml,mu,ipvt,rcond,z)
      integer lda,n,ml,mu,ipvt(1)
      double precision abd(lda,1),z(1)
      double precision rcond
c
c     dgbco factors a double precision band matrix by gaussian
c     elimination and estimates the condition of the matrix.
c
c     if  rcond  is not needed, dgbfa is slightly faster.
c     to solve  a*x = b , follow dgbco by dgbsl.
c     to compute  inverse(a)*c , follow dgbco by dgbsl.
c     to compute  determinant(a) , follow dgbco by dgbdi.
c
c     on entry
c
c        abd     double precision(lda, n)
c                contains the matrix in band storage.  the columns
c                of the matrix are stored in the columns of  abd  and
c                the diagonals of the matrix are stored in rows
c                ml+1 through 2*ml+mu+1 of  abd .
c                see the comments below for details.
c
c        lda     integer
c                the leading dimension of the array  abd .
c                lda must be .ge. 2*ml + mu + 1 .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c                0 .le. ml .lt. n .
c
c        mu      integer
c                number of diagonals above the main diagonal.
c                0 .le. mu .lt. n .
c                more efficient if  ml .le. mu .
c
c     on return
c
c        abd     an upper triangular matrix in band storage and
c                the multipliers which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        rcond   double precision
c                an estimate of the reciprocal condition of  a .
c                for the system  a*x = b , relative perturbations
c                in  a  and  b  of size  epsilon  may cause
c                relative perturbations in  x  of size  epsilon/rcond .
c                if  rcond  is so small that the logical expression
c                           1.0 + rcond .eq. 1.0
c                is true, then  a  may be singular to working
c                precision.  in particular,  rcond  is zero  if
c                exact singularity is detected or the estimate
c                underflows.
c
c        z       double precision(n)
c                a work vector whose contents are usually unimportant.
c                if  a  is close to a singular matrix, then  z  is
c                an approximate null vector in the sense that
c                norm(a*z) = rcond*norm(a)*norm(z) .
c
c     band storage
c
c           if  a  is a band matrix, the following program segment
c           will set up the input.
c
c                   ml = (band width below the diagonal)
c                   mu = (band width above the diagonal)
c                   m = ml + mu + 1
c                   do 20 j = 1, n
c                      i1 = max0(1, j-mu)
c                      i2 = min0(n, j+ml)
c                      do 10 i = i1, i2
c                         k = i - j + m
c                         abd(k,j) = a(i,j)
c                10    continue
c                20 continue
c
c           this uses rows  ml+1  through  2*ml+mu+1  of  abd .
c           in addition, the first  ml  rows in  abd  are used for
c           elements generated during the triangularization.
c           the total number of rows needed in  abd  is  2*ml+mu+1 .
c           the  ml+mu by ml+mu  upper left triangle and the
c           ml by ml  lower right triangle are not referenced.
c
c     example..  if the original matrix is
c
c           11 12 13  0  0  0
c           21 22 23 24  0  0
c            0 32 33 34 35  0
c            0  0 43 44 45 46
c            0  0  0 54 55 56
c            0  0  0  0 65 66
c
c      then  n = 6, ml = 1, mu = 2, lda .ge. 5  and abd should contain
c
c            *  *  *  +  +  +  , * = not used
c            *  * 13 24 35 46  , + = used for pivoting
c            * 12 23 34 45 56
c           11 22 33 44 55 66
c           21 32 43 54 65  *
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     linpack dgbfa
c     blas daxpy,ddot,dscal,dasum
c     fortran dabs,dmax1,max0,min0,dsign
c
c     internal variables
c
      double precision ddot,ek,t,wk,wkm
      double precision anorm,s,dasum,sm,ynorm
      integer is,info,j,ju,k,kb,kp1,l,la,lm,lz,m,mm
c
c
c     compute 1-norm of a
c
      anorm = 0.0d0
      l = ml + 1
      is = l + mu
      do 10 j = 1, n
         anorm = dmax1(anorm,dasum(l,abd(is,j),1))
         if (is .gt. ml + 1) is = is - 1
         if (j .le. mu) l = l + 1
         if (j .ge. n - ml) l = l - 1
   10 continue
c
c     factor
c
      call dgbfa(abd,lda,n,ml,mu,ipvt,info)
c
c     rcond = 1/(norm(a)*(estimate of norm(inverse(a)))) .
c     estimate = norm(z)/norm(y) where  a*z = y  and  trans(a)*y = e .
c     trans(a)  is the transpose of a .  the components of  e  are
c     chosen to cause maximum local growth in the elements of w  where
c     trans(u)*w = e .  the vectors are frequently rescaled to avoid
c     overflow.
c
c     solve trans(u)*w = e
c
      ek = 1.0d0
      do 20 j = 1, n
         z(j) = 0.0d0
   20 continue
      m = ml + mu + 1
      ju = 0
      do 100 k = 1, n
         if (z(k) .ne. 0.0d0) ek = dsign(ek,-z(k))
         if (dabs(ek-z(k)) .le. dabs(abd(m,k))) go to 30
            s = dabs(abd(m,k))/dabs(ek-z(k))
            call dscal(n,s,z,1)
            ek = s*ek
   30    continue
         wk = ek - z(k)
         wkm = -ek - z(k)
         s = dabs(wk)
         sm = dabs(wkm)
         if (abd(m,k) .eq. 0.0d0) go to 40
            wk = wk/abd(m,k)
            wkm = wkm/abd(m,k)
         go to 50
   40    continue
            wk = 1.0d0
            wkm = 1.0d0
   50    continue
         kp1 = k + 1
         ju = min0(max0(ju,mu+ipvt(k)),n)
         mm = m
         if (kp1 .gt. ju) go to 90
            do 60 j = kp1, ju
               mm = mm - 1
               sm = sm + dabs(z(j)+wkm*abd(mm,j))
               z(j) = z(j) + wk*abd(mm,j)
               s = s + dabs(z(j))
   60       continue
            if (s .ge. sm) go to 80
               t = wkm - wk
               wk = wkm
               mm = m
               do 70 j = kp1, ju
                  mm = mm - 1
                  z(j) = z(j) + t*abd(mm,j)
   70          continue
   80       continue
   90    continue
         z(k) = wk
  100 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
c
c     solve trans(l)*y = w
c
      do 120 kb = 1, n
         k = n + 1 - kb
         lm = min0(ml,n-k)
         if (k .lt. n) z(k) = z(k) + ddot(lm,abd(m+1,k),1,z(k+1),1)
         if (dabs(z(k)) .le. 1.0d0) go to 110
            s = 1.0d0/dabs(z(k))
            call dscal(n,s,z,1)
  110    continue
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
  120 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
c
      ynorm = 1.0d0
c
c     solve l*v = y
c
      do 140 k = 1, n
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
         lm = min0(ml,n-k)
         if (k .lt. n) call daxpy(lm,t,abd(m+1,k),1,z(k+1),1)
         if (dabs(z(k)) .le. 1.0d0) go to 130
            s = 1.0d0/dabs(z(k))
            call dscal(n,s,z,1)
            ynorm = s*ynorm
  130    continue
  140 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
      ynorm = s*ynorm
c
c     solve  u*z = w
c
      do 160 kb = 1, n
         k = n + 1 - kb
         if (dabs(z(k)) .le. dabs(abd(m,k))) go to 150
            s = dabs(abd(m,k))/dabs(z(k))
            call dscal(n,s,z,1)
            ynorm = s*ynorm
  150    continue
         if (abd(m,k) .ne. 0.0d0) z(k) = z(k)/abd(m,k)
         if (abd(m,k) .eq. 0.0d0) z(k) = 1.0d0
         lm = min0(k,m) - 1
         la = m - lm
         lz = k - lm
         t = -z(k)
         call daxpy(lm,t,abd(la,k),1,z(lz),1)
  160 continue
c     make znorm = 1.0
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
      ynorm = s*ynorm
c
      if (anorm .ne. 0.0d0) rcond = ynorm/anorm
      if (anorm .eq. 0.0d0) rcond = 0.0d0
      return
      end
      subroutine sgbco(abd,lda,n,ml,mu,ipvt,rcond,z)
      integer lda,n,ml,mu,ipvt(1)
      real abd(lda,1),z(1)
      real rcond
c
c     sgbco factors a real band matrix by gaussian
c     elimination and estimates the condition of the matrix.
c
c     if  rcond  is not needed, sgbfa is slightly faster.
c     to solve  a*x = b , follow sgbco by sgbsl.
c     to compute  inverse(a)*c , follow sgbco by sgbsl.
c     to compute  determinant(a) , follow sgbco by sgbdi.
c
c     on entry
c
c        abd     real(lda, n)
c                contains the matrix in band storage.  the columns
c                of the matrix are stored in the columns of  abd  and
c                the diagonals of the matrix are stored in rows
c                ml+1 through 2*ml+mu+1 of  abd .
c                see the comments below for details.
c
c        lda     integer
c                the leading dimension of the array  abd .
c                lda must be .ge. 2*ml + mu + 1 .
c
c        n       integer
c                the order of the original matrix.
c
c        ml      integer
c                number of diagonals below the main diagonal.
c                0 .le. ml .lt. n .
c
c        mu      integer
c                number of diagonals above the main diagonal.
c                0 .le. mu .lt. n .
c                more efficient if  ml .le. mu .
c
c     on return
c
c        abd     an upper triangular matrix in band storage and
c                the multipliers which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        rcond   real
c                an estimate of the reciprocal condition of  a .
c                for the system  a*x = b , relative perturbations
c                in  a  and  b  of size  epsilon  may cause
c                relative perturbations in  x  of size  epsilon/rcond .
c                if  rcond  is so small that the logical expression
c                           1.0 + rcond .eq. 1.0
c                is true, then  a  may be singular to working
c                precision.  in particular,  rcond  is zero  if
c                exact singularity is detected or the estimate
c                underflows.
c
c        z       real(n)
c                a work vector whose contents are usually unimportant.
c                if  a  is close to a singular matrix, then  z  is
c                an approximate null vector in the sense that
c                norm(a*z) = rcond*norm(a)*norm(z) .
c
c     band storage
c
c           if  a  is a band matrix, the following program segment
c           will set up the input.
c
c                   ml = (band width below the diagonal)
c                   mu = (band width above the diagonal)
c                   m = ml + mu + 1
c                   do 20 j = 1, n
c                      i1 = max0(1, j-mu)
c                      i2 = min0(n, j+ml)
c                      do 10 i = i1, i2
c                         k = i - j + m
c                         abd(k,j) = a(i,j)
c                10    continue
c                20 continue
c
c           this uses rows  ml+1  through  2*ml+mu+1  of  abd .
c           in addition, the first  ml  rows in  abd  are used for
c           elements generated during the triangularization.
c           the total number of rows needed in  abd  is  2*ml+mu+1 .
c           the  ml+mu by ml+mu  upper left triangle and the
c           ml by ml  lower right triangle are not referenced.
c
c     example..  if the original matrix is
c
c           11 12 13  0  0  0
c           21 22 23 24  0  0
c            0 32 33 34 35  0
c            0  0 43 44 45 46
c            0  0  0 54 55 56
c            0  0  0  0 65 66
c
c      then  n = 6, ml = 1, mu = 2, lda .ge. 5  and abd should contain
c
c            *  *  *  +  +  +  , * = not used
c            *  * 13 24 35 46  , + = used for pivoting
c            * 12 23 34 45 56
c           11 22 33 44 55 66
c           21 32 43 54 65  *
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     linpack sgbfa
c     blas saxpy,sdot,sscal,sasum
c     fortran abs,amax1,max0,min0,sign
c
c     internal variables
c
      real sdot,ek,t,wk,wkm
      real anorm,s,sasum,sm,ynorm
      integer is,info,j,ju,k,kb,kp1,l,la,lm,lz,m,mm
c
c
c     compute 1-norm of a
c
      anorm = 0.0e0
      l = ml + 1
      is = l + mu
      do 10 j = 1, n
         anorm = amax1(anorm,sasum(l,abd(is,j),1))
         if (is .gt. ml + 1) is = is - 1
         if (j .le. mu) l = l + 1
         if (j .ge. n - ml) l = l - 1
   10 continue
c
c     factor
c
      call sgbfa(abd,lda,n,ml,mu,ipvt,info)
c
c     rcond = 1/(norm(a)*(estimate of norm(inverse(a)))) .
c     estimate = norm(z)/norm(y) where  a*z = y  and  trans(a)*y = e .
c     trans(a)  is the transpose of a .  the components of  e  are
c     chosen to cause maximum local growth in the elements of w  where
c     trans(u)*w = e .  the vectors are frequently rescaled to avoid
c     overflow.
c
c     solve trans(u)*w = e
c
      ek = 1.0e0
      do 20 j = 1, n
         z(j) = 0.0e0
   20 continue
      m = ml + mu + 1
      ju = 0
      do 100 k = 1, n
         if (z(k) .ne. 0.0e0) ek = sign(ek,-z(k))
         if (abs(ek-z(k)) .le. abs(abd(m,k))) go to 30
            s = abs(abd(m,k))/abs(ek-z(k))
            call sscal(n,s,z,1)
            ek = s*ek
   30    continue
         wk = ek - z(k)
         wkm = -ek - z(k)
         s = abs(wk)
         sm = abs(wkm)
         if (abd(m,k) .eq. 0.0e0) go to 40
            wk = wk/abd(m,k)
            wkm = wkm/abd(m,k)
         go to 50
   40    continue
            wk = 1.0e0
            wkm = 1.0e0
   50    continue
         kp1 = k + 1
         ju = min0(max0(ju,mu+ipvt(k)),n)
         mm = m
         if (kp1 .gt. ju) go to 90
            do 60 j = kp1, ju
               mm = mm - 1
               sm = sm + abs(z(j)+wkm*abd(mm,j))
               z(j) = z(j) + wk*abd(mm,j)
               s = s + abs(z(j))
   60       continue
            if (s .ge. sm) go to 80
               t = wkm - wk
               wk = wkm
               mm = m
               do 70 j = kp1, ju
                  mm = mm - 1
                  z(j) = z(j) + t*abd(mm,j)
   70          continue
   80       continue
   90    continue
         z(k) = wk
  100 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
c
c     solve trans(l)*y = w
c
      do 120 kb = 1, n
         k = n + 1 - kb
         lm = min0(ml,n-k)
         if (k .lt. n) z(k) = z(k) + sdot(lm,abd(m+1,k),1,z(k+1),1)
         if (abs(z(k)) .le. 1.0e0) go to 110
            s = 1.0e0/abs(z(k))
            call sscal(n,s,z,1)
  110    continue
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
  120 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
c
      ynorm = 1.0e0
c
c     solve l*v = y
c
      do 140 k = 1, n
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
         lm = min0(ml,n-k)
         if (k .lt. n) call saxpy(lm,t,abd(m+1,k),1,z(k+1),1)
         if (abs(z(k)) .le. 1.0e0) go to 130
            s = 1.0e0/abs(z(k))
            call sscal(n,s,z,1)
            ynorm = s*ynorm
  130    continue
  140 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
      ynorm = s*ynorm
c
c     solve  u*z = w
c
      do 160 kb = 1, n
         k = n + 1 - kb
         if (abs(z(k)) .le. abs(abd(m,k))) go to 150
            s = abs(abd(m,k))/abs(z(k))
            call sscal(n,s,z,1)
            ynorm = s*ynorm
  150    continue
         if (abd(m,k) .ne. 0.0e0) z(k) = z(k)/abd(m,k)
         if (abd(m,k) .eq. 0.0e0) z(k) = 1.0e0
         lm = min0(k,m) - 1
         la = m - lm
         lz = k - lm
         t = -z(k)
         call saxpy(lm,t,abd(la,k),1,z(lz),1)
  160 continue
c     make znorm = 1.0
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
      ynorm = s*ynorm
c
      if (anorm .ne. 0.0e0) rcond = ynorm/anorm
      if (anorm .eq. 0.0e0) rcond = 0.0e0
      return
      end
      subroutine dgeco(a,lda,n,ipvt,rcond,z)
      integer lda,n,ipvt(1)
      double precision a(lda,1),z(1)
      double precision rcond
c
c     dgeco factors a double precision matrix by gaussian elimination
c     and estimates the condition of the matrix.
c
c     if  rcond  is not needed, dgefa is slightly faster.
c     to solve  a*x = b , follow dgeco by dgesl.
c     to compute  inverse(a)*c , follow dgeco by dgesl.
c     to compute  determinant(a) , follow dgeco by dgedi.
c     to compute  inverse(a) , follow dgeco by dgedi.
c
c     on entry
c
c        a       double precision(lda, n)
c                the matrix to be factored.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c     on return
c
c        a       an upper triangular matrix and the multipliers
c                which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        rcond   double precision
c                an estimate of the reciprocal condition of  a .
c                for the system  a*x = b , relative perturbations
c                in  a  and  b  of size  epsilon  may cause
c                relative perturbations in  x  of size  epsilon/rcond .
c                if  rcond  is so small that the logical expression
c                           1.0 + rcond .eq. 1.0
c                is true, then  a  may be singular to working
c                precision.  in particular,  rcond  is zero  if
c                exact singularity is detected or the estimate
c                underflows.
c
c        z       double precision(n)
c                a work vector whose contents are usually unimportant.
c                if  a  is close to a singular matrix, then  z  is
c                an approximate null vector in the sense that
c                norm(a*z) = rcond*norm(a)*norm(z) .
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     linpack dgefa
c     blas daxpy,ddot,dscal,dasum
c     fortran dabs,dmax1,dsign
c
c     internal variables
c
      double precision ddot,ek,t,wk,wkm
      double precision anorm,s,dasum,sm,ynorm
      integer info,j,k,kb,kp1,l
c
c
c     compute 1-norm of a
c
      anorm = 0.0d0
      do 10 j = 1, n
         anorm = dmax1(anorm,dasum(n,a(1,j),1))
   10 continue
c
c     factor
c
      call dgefa(a,lda,n,ipvt,info)
c
c     rcond = 1/(norm(a)*(estimate of norm(inverse(a)))) .
c     estimate = norm(z)/norm(y) where  a*z = y  and  trans(a)*y = e .
c     trans(a)  is the transpose of a .  the components of  e  are
c     chosen to cause maximum local growth in the elements of w  where
c     trans(u)*w = e .  the vectors are frequently rescaled to avoid
c     overflow.
c
c     solve trans(u)*w = e
c
      ek = 1.0d0
      do 20 j = 1, n
         z(j) = 0.0d0
   20 continue
      do 100 k = 1, n
         if (z(k) .ne. 0.0d0) ek = dsign(ek,-z(k))
         if (dabs(ek-z(k)) .le. dabs(a(k,k))) go to 30
            s = dabs(a(k,k))/dabs(ek-z(k))
            call dscal(n,s,z,1)
            ek = s*ek
   30    continue
         wk = ek - z(k)
         wkm = -ek - z(k)
         s = dabs(wk)
         sm = dabs(wkm)
         if (a(k,k) .eq. 0.0d0) go to 40
            wk = wk/a(k,k)
            wkm = wkm/a(k,k)
         go to 50
   40    continue
            wk = 1.0d0
            wkm = 1.0d0
   50    continue
         kp1 = k + 1
         if (kp1 .gt. n) go to 90
            do 60 j = kp1, n
               sm = sm + dabs(z(j)+wkm*a(k,j))
               z(j) = z(j) + wk*a(k,j)
               s = s + dabs(z(j))
   60       continue
            if (s .ge. sm) go to 80
               t = wkm - wk
               wk = wkm
               do 70 j = kp1, n
                  z(j) = z(j) + t*a(k,j)
   70          continue
   80       continue
   90    continue
         z(k) = wk
  100 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
c
c     solve trans(l)*y = w
c
      do 120 kb = 1, n
         k = n + 1 - kb
         if (k .lt. n) z(k) = z(k) + ddot(n-k,a(k+1,k),1,z(k+1),1)
         if (dabs(z(k)) .le. 1.0d0) go to 110
            s = 1.0d0/dabs(z(k))
            call dscal(n,s,z,1)
  110    continue
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
  120 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
c
      ynorm = 1.0d0
c
c     solve l*v = y
c
      do 140 k = 1, n
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
         if (k .lt. n) call daxpy(n-k,t,a(k+1,k),1,z(k+1),1)
         if (dabs(z(k)) .le. 1.0d0) go to 130
            s = 1.0d0/dabs(z(k))
            call dscal(n,s,z,1)
            ynorm = s*ynorm
  130    continue
  140 continue
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
      ynorm = s*ynorm
c
c     solve  u*z = v
c
      do 160 kb = 1, n
         k = n + 1 - kb
         if (dabs(z(k)) .le. dabs(a(k,k))) go to 150
            s = dabs(a(k,k))/dabs(z(k))
            call dscal(n,s,z,1)
            ynorm = s*ynorm
  150    continue
         if (a(k,k) .ne. 0.0d0) z(k) = z(k)/a(k,k)
         if (a(k,k) .eq. 0.0d0) z(k) = 1.0d0
         t = -z(k)
         call daxpy(k-1,t,a(1,k),1,z(1),1)
  160 continue
c     make znorm = 1.0
      s = 1.0d0/dasum(n,z,1)
      call dscal(n,s,z,1)
      ynorm = s*ynorm
c
      if (anorm .ne. 0.0d0) rcond = ynorm/anorm
      if (anorm .eq. 0.0d0) rcond = 0.0d0
      return
      end
      subroutine sgeco(a,lda,n,ipvt,rcond,z)
      integer lda,n,ipvt(1)
      real a(lda,1),z(1)
      real rcond
c
c     sgeco factors a real matrix by gaussian elimination
c     and estimates the condition of the matrix.
c
c     if  rcond  is not needed, sgefa is slightly faster.
c     to solve  a*x = b , follow sgeco by sgesl.
c     to compute  inverse(a)*c , follow sgeco by sgesl.
c     to compute  determinant(a) , follow sgeco by sgedi.
c     to compute  inverse(a) , follow sgeco by sgedi.
c
c     on entry
c
c        a       real(lda, n)
c                the matrix to be factored.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c     on return
c
c        a       an upper triangular matrix and the multipliers
c                which were used to obtain it.
c                the factorization can be written  a = l*u  where
c                l  is a product of permutation and unit lower
c                triangular matrices and  u  is upper triangular.
c
c        ipvt    integer(n)
c                an integer vector of pivot indices.
c
c        rcond   real
c                an estimate of the reciprocal condition of  a .
c                for the system  a*x = b , relative perturbations
c                in  a  and  b  of size  epsilon  may cause
c                relative perturbations in  x  of size  epsilon/rcond .
c                if  rcond  is so small that the logical expression
c                           1.0 + rcond .eq. 1.0
c                is true, then  a  may be singular to working
c                precision.  in particular,  rcond  is zero  if
c                exact singularity is detected or the estimate
c                underflows.
c
c        z       real(n)
c                a work vector whose contents are usually unimportant.
c                if  a  is close to a singular matrix, then  z  is
c                an approximate null vector in the sense that
c                norm(a*z) = rcond*norm(a)*norm(z) .
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     linpack sgefa
c     blas saxpy,sdot,sscal,sasum
c     fortran abs,amax1,sign
c
c     internal variables
c
      real sdot,ek,t,wk,wkm
      real anorm,s,sasum,sm,ynorm
      integer info,j,k,kb,kp1,l
c
c
c     compute 1-norm of a
c
      anorm = 0.0e0
      do 10 j = 1, n
         anorm = amax1(anorm,sasum(n,a(1,j),1))
   10 continue
c
c     factor
c
      call sgefa(a,lda,n,ipvt,info)
c
c     rcond = 1/(norm(a)*(estimate of norm(inverse(a)))) .
c     estimate = norm(z)/norm(y) where  a*z = y  and  trans(a)*y = e .
c     trans(a)  is the transpose of a .  the components of  e  are
c     chosen to cause maximum local growth in the elements of w  where
c     trans(u)*w = e .  the vectors are frequently rescaled to avoid
c     overflow.
c
c     solve trans(u)*w = e
c
      ek = 1.0e0
      do 20 j = 1, n
         z(j) = 0.0e0
   20 continue
      do 100 k = 1, n
         if (z(k) .ne. 0.0e0) ek = sign(ek,-z(k))
         if (abs(ek-z(k)) .le. abs(a(k,k))) go to 30
            s = abs(a(k,k))/abs(ek-z(k))
            call sscal(n,s,z,1)
            ek = s*ek
   30    continue
         wk = ek - z(k)
         wkm = -ek - z(k)
         s = abs(wk)
         sm = abs(wkm)
         if (a(k,k) .eq. 0.0e0) go to 40
            wk = wk/a(k,k)
            wkm = wkm/a(k,k)
         go to 50
   40    continue
            wk = 1.0e0
            wkm = 1.0e0
   50    continue
         kp1 = k + 1
         if (kp1 .gt. n) go to 90
            do 60 j = kp1, n
               sm = sm + abs(z(j)+wkm*a(k,j))
               z(j) = z(j) + wk*a(k,j)
               s = s + abs(z(j))
   60       continue
            if (s .ge. sm) go to 80
               t = wkm - wk
               wk = wkm
               do 70 j = kp1, n
                  z(j) = z(j) + t*a(k,j)
   70          continue
   80       continue
   90    continue
         z(k) = wk
  100 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
c
c     solve trans(l)*y = w
c
      do 120 kb = 1, n
         k = n + 1 - kb
         if (k .lt. n) z(k) = z(k) + sdot(n-k,a(k+1,k),1,z(k+1),1)
         if (abs(z(k)) .le. 1.0e0) go to 110
            s = 1.0e0/abs(z(k))
            call sscal(n,s,z,1)
  110    continue
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
  120 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
c
      ynorm = 1.0e0
c
c     solve l*v = y
c
      do 140 k = 1, n
         l = ipvt(k)
         t = z(l)
         z(l) = z(k)
         z(k) = t
         if (k .lt. n) call saxpy(n-k,t,a(k+1,k),1,z(k+1),1)
         if (abs(z(k)) .le. 1.0e0) go to 130
            s = 1.0e0/abs(z(k))
            call sscal(n,s,z,1)
            ynorm = s*ynorm
  130    continue
  140 continue
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
      ynorm = s*ynorm
c
c     solve  u*z = v
c
      do 160 kb = 1, n
         k = n + 1 - kb
         if (abs(z(k)) .le. abs(a(k,k))) go to 150
            s = abs(a(k,k))/abs(z(k))
            call sscal(n,s,z,1)
            ynorm = s*ynorm
  150    continue
         if (a(k,k) .ne. 0.0e0) z(k) = z(k)/a(k,k)
         if (a(k,k) .eq. 0.0e0) z(k) = 1.0e0
         t = -z(k)
         call saxpy(k-1,t,a(1,k),1,z(1),1)
  160 continue
c     make znorm = 1.0
      s = 1.0e0/sasum(n,z,1)
      call sscal(n,s,z,1)
      ynorm = s*ynorm
c
      if (anorm .ne. 0.0e0) rcond = ynorm/anorm
      if (anorm .eq. 0.0e0) rcond = 0.0e0
      return
      end
      double precision function dasum(n,dx,incx)
c
c     takes the sum of the absolute values.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      double precision dx(1),dtemp
      integer i,incx,m,mp1,n,nincx
c
      dasum = 0.0d0
      dtemp = 0.0d0
      if( n.le.0 .or. incx.le.0 )return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      nincx = n*incx
      do 10 i = 1,nincx,incx
        dtemp = dtemp + dabs(dx(i))
   10 continue
      dasum = dtemp
      return
c
c        code for increment equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,6)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dtemp = dtemp + dabs(dx(i))
   30 continue
      if( n .lt. 6 ) go to 60
   40 mp1 = m + 1
      do 50 i = mp1,n,6
        dtemp = dtemp + dabs(dx(i)) + dabs(dx(i + 1)) + dabs(dx(i + 2))
     *  + dabs(dx(i + 3)) + dabs(dx(i + 4)) + dabs(dx(i + 5))
   50 continue
   60 dasum = dtemp
      return
      end
      real function sasum(n,sx,incx)
c
c     takes the sum of the absolute values.
c     uses unrolled loops for increment equal to one.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      real sx(1),stemp
      integer i,incx,m,mp1,n,nincx
c
      sasum = 0.0e0
      stemp = 0.0e0
      if( n.le.0 .or. incx.le.0 )return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      nincx = n*incx
      do 10 i = 1,nincx,incx
        stemp = stemp + abs(sx(i))
   10 continue
      sasum = stemp
      return
c
c        code for increment equal to 1
c
c
c        clean-up loop
c
   20 m = mod(n,6)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        stemp = stemp + abs(sx(i))
   30 continue
      if( n .lt. 6 ) go to 60
   40 mp1 = m + 1
      do 50 i = mp1,n,6
        stemp = stemp + abs(sx(i)) + abs(sx(i + 1)) + abs(sx(i + 2))
     *  + abs(sx(i + 3)) + abs(sx(i + 4)) + abs(sx(i + 5))
   50 continue
   60 sasum = stemp
      return
      end
      subroutine  dswap (n,dx,incx,dy,incy)
c
c     interchanges two vectors.
c     uses unrolled loops for increments equal one.
c     jack dongarra, linpack, 3/11/78.
c
      double precision dx(1),dy(1),dtemp
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c       code for unequal increments or equal increments not equal
c         to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        dtemp = dx(ix)
        dx(ix) = dy(iy)
        dy(iy) = dtemp
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c       code for both increments equal to 1
c
c
c       clean-up loop
c
   20 m = mod(n,3)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        dtemp = dx(i)
        dx(i) = dy(i)
        dy(i) = dtemp
   30 continue
      if( n .lt. 3 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,3
        dtemp = dx(i)
        dx(i) = dy(i)
        dy(i) = dtemp
        dtemp = dx(i + 1)
        dx(i + 1) = dy(i + 1)
        dy(i + 1) = dtemp
        dtemp = dx(i + 2)
        dx(i + 2) = dy(i + 2)
        dy(i + 2) = dtemp
   50 continue
      return
      end
      subroutine sswap (n,sx,incx,sy,incy)
c
c     interchanges two vectors.
c     uses unrolled loops for increments equal to 1.
c     jack dongarra, linpack, 3/11/78.
c
      real sx(1),sy(1),stemp
      integer i,incx,incy,ix,iy,m,mp1,n
c
      if(n.le.0)return
      if(incx.eq.1.and.incy.eq.1)go to 20
c
c       code for unequal increments or equal increments not equal
c         to 1
c
      ix = 1
      iy = 1
      if(incx.lt.0)ix = (-n+1)*incx + 1
      if(incy.lt.0)iy = (-n+1)*incy + 1
      do 10 i = 1,n
        stemp = sx(ix)
        sx(ix) = sy(iy)
        sy(iy) = stemp
        ix = ix + incx
        iy = iy + incy
   10 continue
      return
c
c       code for both increments equal to 1
c
c
c       clean-up loop
c
   20 m = mod(n,3)
      if( m .eq. 0 ) go to 40
      do 30 i = 1,m
        stemp = sx(i)
        sx(i) = sy(i)
        sy(i) = stemp
   30 continue
      if( n .lt. 3 ) return
   40 mp1 = m + 1
      do 50 i = mp1,n,3
        stemp = sx(i)
        sx(i) = sy(i)
        sy(i) = stemp
        stemp = sx(i + 1)
        sx(i + 1) = sy(i + 1)
        sy(i + 1) = stemp
        stemp = sx(i + 2)
        sx(i + 2) = sy(i + 2)
        sy(i + 2) = stemp
   50 continue
      return
      end
      subroutine dgedi(a,lda,n,ipvt,det,work,job)
      integer lda,n,ipvt(1),job
      double precision a(lda,1),det(2),work(1)
c
c     dgedi computes the determinant and inverse of a matrix
c     using the factors computed by dgeco or dgefa.
c
c     on entry
c
c        a       double precision(lda, n)
c                the output from dgeco or dgefa.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c        ipvt    integer(n)
c                the pivot vector from dgeco or dgefa.
c
c        work    double precision(n)
c                work vector.  contents destroyed.
c
c        job     integer
c                = 11   both determinant and inverse.
c                = 01   inverse only.
c                = 10   determinant only.
c
c     on return
c
c        a       inverse of original matrix if requested.
c                otherwise unchanged.
c
c        det     double precision(2)
c                determinant of original matrix if requested.
c                otherwise not referenced.
c                determinant = det(1) * 10.0**det(2)
c                with  1.0 .le. dabs(det(1)) .lt. 10.0
c                or  det(1) .eq. 0.0 .
c
c     error condition
c
c        a division by zero will occur if the input factor contains
c        a zero on the diagonal and the inverse is requested.
c        it will not occur if the subroutines are called correctly
c        and if dgeco has set rcond .gt. 0.0 or dgefa has set
c        info .eq. 0 .
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas daxpy,dscal,dswap
c     fortran dabs,mod
c
c     internal variables
c
      double precision t
      double precision ten
      integer i,j,k,kb,kp1,l,nm1
c
c
c     compute determinant
c
      if (job/10 .eq. 0) go to 70
         det(1) = 1.0d0
         det(2) = 0.0d0
         ten = 10.0d0
         do 50 i = 1, n
            if (ipvt(i) .ne. i) det(1) = -det(1)
            det(1) = a(i,i)*det(1)
c        ...exit
            if (det(1) .eq. 0.0d0) go to 60
   10       if (dabs(det(1)) .ge. 1.0d0) go to 20
               det(1) = ten*det(1)
               det(2) = det(2) - 1.0d0
            go to 10
   20       continue
   30       if (dabs(det(1)) .lt. ten) go to 40
               det(1) = det(1)/ten
               det(2) = det(2) + 1.0d0
            go to 30
   40       continue
   50    continue
   60    continue
   70 continue
c
c     compute inverse(u)
c
      if (mod(job,10) .eq. 0) go to 150
         do 100 k = 1, n
            a(k,k) = 1.0d0/a(k,k)
            t = -a(k,k)
            call dscal(k-1,t,a(1,k),1)
            kp1 = k + 1
            if (n .lt. kp1) go to 90
            do 80 j = kp1, n
               t = a(k,j)
               a(k,j) = 0.0d0
               call daxpy(k,t,a(1,k),1,a(1,j),1)
   80       continue
   90       continue
  100    continue
c
c        form inverse(u)*inverse(l)
c
         nm1 = n - 1
         if (nm1 .lt. 1) go to 140
         do 130 kb = 1, nm1
            k = n - kb
            kp1 = k + 1
            do 110 i = kp1, n
               work(i) = a(i,k)
               a(i,k) = 0.0d0
  110       continue
            do 120 j = kp1, n
               t = work(j)
               call daxpy(n,t,a(1,j),1,a(1,k),1)
  120       continue
            l = ipvt(k)
            if (l .ne. k) call dswap(n,a(1,k),1,a(1,l),1)
  130    continue
  140    continue
  150 continue
      return
      end
      subroutine sgedi(a,lda,n,ipvt,det,work,job)
      integer lda,n,ipvt(1),job
      real a(lda,1),det(2),work(1)
c
c     sgedi computes the determinant and inverse of a matrix
c     using the factors computed by sgeco or sgefa.
c
c     on entry
c
c        a       real(lda, n)
c                the output from sgeco or sgefa.
c
c        lda     integer
c                the leading dimension of the array  a .
c
c        n       integer
c                the order of the matrix  a .
c
c        ipvt    integer(n)
c                the pivot vector from sgeco or sgefa.
c
c        work    real(n)
c                work vector.  contents destroyed.
c
c        job     integer
c                = 11   both determinant and inverse.
c                = 01   inverse only.
c                = 10   determinant only.
c
c     on return
c
c        a       inverse of original matrix if requested.
c                otherwise unchanged.
c
c        det     real(2)
c                determinant of original matrix if requested.
c                otherwise not referenced.
c                determinant = det(1) * 10.0**det(2)
c                with  1.0 .le. abs(det(1)) .lt. 10.0
c                or  det(1) .eq. 0.0 .
c
c     error condition
c
c        a division by zero will occur if the input factor contains
c        a zero on the diagonal and the inverse is requested.
c        it will not occur if the subroutines are called correctly
c        and if sgeco has set rcond .gt. 0.0 or sgefa has set
c        info .eq. 0 .
c
c     linpack. this version dated 08/14/78 .
c     cleve moler, university of new mexico, argonne national lab.
c
c     subroutines and functions
c
c     blas saxpy,sscal,sswap
c     fortran abs,mod
c
c     internal variables
c
      real t
      real ten
      integer i,j,k,kb,kp1,l,nm1
c
c
c     compute determinant
c
      if (job/10 .eq. 0) go to 70
         det(1) = 1.0e0
         det(2) = 0.0e0
         ten = 10.0e0
         do 50 i = 1, n
            if (ipvt(i) .ne. i) det(1) = -det(1)
            det(1) = a(i,i)*det(1)
c        ...exit
            if (det(1) .eq. 0.0e0) go to 60
   10       if (abs(det(1)) .ge. 1.0e0) go to 20
               det(1) = ten*det(1)
               det(2) = det(2) - 1.0e0
            go to 10
   20       continue
   30       if (abs(det(1)) .lt. ten) go to 40
               det(1) = det(1)/ten
               det(2) = det(2) + 1.0e0
            go to 30
   40       continue
   50    continue
   60    continue
   70 continue
c
c     compute inverse(u)
c
      if (mod(job,10) .eq. 0) go to 150
         do 100 k = 1, n
            a(k,k) = 1.0e0/a(k,k)
            t = -a(k,k)
            call sscal(k-1,t,a(1,k),1)
            kp1 = k + 1
            if (n .lt. kp1) go to 90
            do 80 j = kp1, n
               t = a(k,j)
               a(k,j) = 0.0e0
               call saxpy(k,t,a(1,k),1,a(1,j),1)
   80       continue
   90       continue
  100    continue
c
c        form inverse(u)*inverse(l)
c
         nm1 = n - 1
         if (nm1 .lt. 1) go to 140
         do 130 kb = 1, nm1
            k = n - kb
            kp1 = k + 1
            do 110 i = kp1, n
               work(i) = a(i,k)
               a(i,k) = 0.0e0
  110       continue
            do 120 j = kp1, n
               t = work(j)
               call saxpy(n,t,a(1,j),1,a(1,k),1)
  120       continue
            l = ipvt(k)
            if (l .ne. k) call sswap(n,a(1,k),1,a(1,l),1)
  130    continue
  140    continue
  150 continue
      return
      end
*DECK FDUMP
      SUBROUTINE FDUMP
C***BEGIN PROLOGUE  FDUMP
C***PURPOSE  Symbolic dump (should be locally written).
C***LIBRARY   SLATEC (XERMSG)
C***CATEGORY  R3
C***TYPE      ALL (FDUMP-A)
C***KEYWORDS  ERROR, XERMSG
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C        ***Note*** Machine Dependent Routine
C        FDUMP is intended to be replaced by a locally written
C        version which produces a symbolic dump.  Failing this,
C        it should be replaced by a version which prints the
C        subprogram nesting list.  Note that this dump must be
C        printed on each of up to five files, as indicated by the
C        XGETUA routine.  See XSETUA and XGETUA for details.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C
C***REFERENCES  (NONE)
C***ROUTINES CALLED  (NONE)
C***REVISION HISTORY  (YYMMDD)
C   790801  DATE WRITTEN
C   861211  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C***END PROLOGUE  FDUMP
C***FIRST EXECUTABLE STATEMENT  FDUMP
      RETURN
      END
      integer function isamax(n,sx,incx)
c
c     finds the index of element having max. absolute value.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      real sx(1),smax
      integer i,incx,ix,n
c
      isamax = 0
      if( n.lt.1 .or. incx.le.0 ) return
      isamax = 1
      if(n.eq.1)return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      ix = 1
      smax = abs(sx(1))
      ix = ix + incx
      do 10 i = 2,n
         if(abs(sx(ix)).le.smax) go to 5
         isamax = i
         smax = abs(sx(ix))
    5    ix = ix + incx
   10 continue
      return
c
c        code for increment equal to 1
c
   20 smax = abs(sx(1))
      do 30 i = 2,n
         if(abs(sx(i)).le.smax) go to 30
         isamax = i
         smax = abs(sx(i))
   30 continue
      return
      end
      integer function idamax(n,dx,incx)
c
c     finds the index of element having max. absolute value.
c     jack dongarra, linpack, 3/11/78.
c     modified 3/93 to return if incx .le. 0.
c
      double precision dx(1),dmax
      integer i,incx,ix,n
c
      idamax = 0
      if( n.lt.1 .or. incx.le.0 ) return
      idamax = 1
      if(n.eq.1)return
      if(incx.eq.1)go to 20
c
c        code for increment not equal to 1
c
      ix = 1
      dmax = dabs(dx(1))
      ix = ix + incx
      do 10 i = 2,n
         if(dabs(dx(ix)).le.dmax) go to 5
         idamax = i
         dmax = dabs(dx(ix))
    5    ix = ix + incx
   10 continue
      return
c
c        code for increment equal to 1
c
   20 dmax = dabs(dx(1))
      do 30 i = 2,n
         if(dabs(dx(i)).le.dmax) go to 30
         idamax = i
         dmax = dabs(dx(i))
   30 continue
      return
      end
*DECK J4SAVE
      FUNCTION J4SAVE (IWHICH, IVALUE, ISET)
C***BEGIN PROLOGUE  J4SAVE
C***SUBSIDIARY
C***PURPOSE  Save or recall global variables needed by error
C            handling routines.
C***LIBRARY   SLATEC (XERROR)
C***TYPE      INTEGER (J4SAVE-I)
C***KEYWORDS  ERROR MESSAGES, ERROR NUMBER, RECALL, SAVE, XERROR
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C     Abstract
C        J4SAVE saves and recalls several global variables needed
C        by the library error handling routines.
C
C     Description of Parameters
C      --Input--
C        IWHICH - Index of item desired.
C                = 1 Refers to current error number.
C                = 2 Refers to current error control flag.
C                = 3 Refers to current unit number to which error
C                    messages are to be sent.  (0 means use standard.)
C                = 4 Refers to the maximum number of times any
C                     message is to be printed (as set by XERMAX).
C                = 5 Refers to the total number of units to which
C                     each error message is to be written.
C                = 6 Refers to the 2nd unit for error messages
C                = 7 Refers to the 3rd unit for error messages
C                = 8 Refers to the 4th unit for error messages
C                = 9 Refers to the 5th unit for error messages
C        IVALUE - The value to be set for the IWHICH-th parameter,
C                 if ISET is .TRUE. .
C        ISET   - If ISET=.TRUE., the IWHICH-th parameter will BE
C                 given the value, IVALUE.  If ISET=.FALSE., the
C                 IWHICH-th parameter will be unchanged, and IVALUE
C                 is a dummy parameter.
C      --Output--
C        The (old) value of the IWHICH-th parameter will be returned
C        in the function value, J4SAVE.
C
C***SEE ALSO  XERMSG
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  (NONE)
C***REVISION HISTORY  (YYMMDD)
C   790801  DATE WRITTEN
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900205  Minor modifications to prologue.  (WRB)
C   900402  Added TYPE section.  (WRB)
C   910411  Added KEYWORDS section.  (WRB)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  J4SAVE
      LOGICAL ISET
      INTEGER IPARAM(9)
      SAVE IPARAM
      DATA IPARAM(1),IPARAM(2),IPARAM(3),IPARAM(4)/0,2,0,10/
      DATA IPARAM(5)/1/
      DATA IPARAM(6),IPARAM(7),IPARAM(8),IPARAM(9)/0,0,0,0/
C***FIRST EXECUTABLE STATEMENT  J4SAVE
      J4SAVE = IPARAM(IWHICH)
      IF (ISET) IPARAM(IWHICH) = IVALUE
      RETURN
      END
*DECK XERCNT
      SUBROUTINE XERCNT (LIBRAR, SUBROU, MESSG, NERR, LEVEL, KONTRL)
C***BEGIN PROLOGUE  XERCNT
C***SUBSIDIARY
C***PURPOSE  Allow user control over handling of errors.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3C
C***TYPE      ALL (XERCNT-A)
C***KEYWORDS  ERROR, XERROR
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C     Abstract
C        Allows user control over handling of individual errors.
C        Just after each message is recorded, but before it is
C        processed any further (i.e., before it is printed or
C        a decision to abort is made), a call is made to XERCNT.
C        If the user has provided his own version of XERCNT, he
C        can then override the value of KONTROL used in processing
C        this message by redefining its value.
C        KONTRL may be set to any value from -2 to 2.
C        The meanings for KONTRL are the same as in XSETF, except
C        that the value of KONTRL changes only for this message.
C        If KONTRL is set to a value outside the range from -2 to 2,
C        it will be moved back into that range.
C
C     Description of Parameters
C
C      --Input--
C        LIBRAR - the library that the routine is in.
C        SUBROU - the subroutine that XERMSG is being called from
C        MESSG  - the first 20 characters of the error message.
C        NERR   - same as in the call to XERMSG.
C        LEVEL  - same as in the call to XERMSG.
C        KONTRL - the current value of the control flag as set
C                 by a call to XSETF.
C
C      --Output--
C        KONTRL - the new value of KONTRL.  If KONTRL is not
C                 defined, it will remain at its original value.
C                 This changed value of control affects only
C                 the current occurrence of the current message.
C
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  (NONE)
C***REVISION HISTORY  (YYMMDD)
C   790801  DATE WRITTEN
C   861211  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900206  Routine changed from user-callable to subsidiary.  (WRB)
C   900510  Changed calling sequence to include LIBRARY and SUBROUTINE
C           names, changed routine name from XERCTL to XERCNT.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XERCNT
      CHARACTER*(*) LIBRAR, SUBROU, MESSG
C***FIRST EXECUTABLE STATEMENT  XERCNT
      RETURN
      END
*DECK XERMSG
      SUBROUTINE XERMSG (LIBRAR, SUBROU, MESSG, NERR, LEVEL)
C***BEGIN PROLOGUE  XERMSG
C***PURPOSE  Process error messages for SLATEC and other libraries.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3C
C***TYPE      ALL (XERMSG-A)
C***KEYWORDS  ERROR MESSAGE, XERROR
C***AUTHOR  Fong, Kirby, (NMFECC at LLNL)
C***DESCRIPTION
C
C   XERMSG processes a diagnostic message in a manner determined by the
C   value of LEVEL and the current value of the library error control
C   flag, KONTRL.  See subroutine XSETF for details.
C
C    LIBRAR   A character constant (or character variable) with the name
C             of the library.  This will be 'SLATEC' for the SLATEC
C             Common Math Library.  The error handling package is
C             general enough to be used by many libraries
C             simultaneously, so it is desirable for the routine that
C             detects and reports an error to identify the library name
C             as well as the routine name.
C
C    SUBROU   A character constant (or character variable) with the name
C             of the routine that detected the error.  Usually it is the
C             name of the routine that is calling XERMSG.  There are
C             some instances where a user callable library routine calls
C             lower level subsidiary routines where the error is
C             detected.  In such cases it may be more informative to
C             supply the name of the routine the user called rather than
C             the name of the subsidiary routine that detected the
C             error.
C
C    MESSG    A character constant (or character variable) with the text
C             of the error or warning message.  In the example below,
C             the message is a character constant that contains a
C             generic message.
C
C                   CALL XERMSG ('SLATEC', 'MMPY',
C                  *'THE ORDER OF THE MATRIX EXCEEDS THE ROW DIMENSION',
C                  *3, 1)
C
C             It is possible (and is sometimes desirable) to generate a
C             specific message--e.g., one that contains actual numeric
C             values.  Specific numeric values can be converted into
C             character strings using formatted WRITE statements into
C             character variables.  This is called standard Fortran
C             internal file I/O and is exemplified in the first three
C             lines of the following example.  You can also catenate
C             substrings of characters to construct the error message.
C             Here is an example showing the use of both writing to
C             an internal file and catenating character strings.
C
C                   CHARACTER*5 CHARN, CHARL
C                   WRITE (CHARN,10) N
C                   WRITE (CHARL,10) LDA
C                10 FORMAT(I5)
C                   CALL XERMSG ('SLATEC', 'MMPY', 'THE ORDER'//CHARN//
C                  *   ' OF THE MATRIX EXCEEDS ITS ROW DIMENSION OF'//
C                  *   CHARL, 3, 1)
C
C             There are two subtleties worth mentioning.  One is that
C             the // for character catenation is used to construct the
C             error message so that no single character constant is
C             continued to the next line.  This avoids confusion as to
C             whether there are trailing blanks at the end of the line.
C             The second is that by catenating the parts of the message
C             as an actual argument rather than encoding the entire
C             message into one large character variable, we avoid
C             having to know how long the message will be in order to
C             declare an adequate length for that large character
C             variable.  XERMSG calls XERPRN to print the message using
C             multiple lines if necessary.  If the message is very long,
C             XERPRN will break it into pieces of 72 characters (as
C             requested by XERMSG) for printing on multiple lines.
C             Also, XERMSG asks XERPRN to prefix each line with ' *  '
C             so that the total line length could be 76 characters.
C             Note also that XERPRN scans the error message backwards
C             to ignore trailing blanks.  Another feature is that
C             the substring '$$' is treated as a new line sentinel
C             by XERPRN.  If you want to construct a multiline
C             message without having to count out multiples of 72
C             characters, just use '$$' as a separator.  '$$'
C             obviously must occur within 72 characters of the
C             start of each line to have its intended effect since
C             XERPRN is asked to wrap around at 72 characters in
C             addition to looking for '$$'.
C
C    NERR     An integer value that is chosen by the library routine's
C             author.  It must be in the range -99 to 999 (three
C             printable digits).  Each distinct error should have its
C             own error number.  These error numbers should be described
C             in the machine readable documentation for the routine.
C             The error numbers need be unique only within each routine,
C             so it is reasonable for each routine to start enumerating
C             errors from 1 and proceeding to the next integer.
C
C    LEVEL    An integer value in the range 0 to 2 that indicates the
C             level (severity) of the error.  Their meanings are
C
C            -1  A warning message.  This is used if it is not clear
C                that there really is an error, but the user's attention
C                may be needed.  An attempt is made to only print this
C                message once.
C
C             0  A warning message.  This is used if it is not clear
C                that there really is an error, but the user's attention
C                may be needed.
C
C             1  A recoverable error.  This is used even if the error is
C                so serious that the routine cannot return any useful
C                answer.  If the user has told the error package to
C                return after recoverable errors, then XERMSG will
C                return to the Library routine which can then return to
C                the user's routine.  The user may also permit the error
C                package to terminate the program upon encountering a
C                recoverable error.
C
C             2  A fatal error.  XERMSG will not return to its caller
C                after it receives a fatal error.  This level should
C                hardly ever be used; it is much better to allow the
C                user a chance to recover.  An example of one of the few
C                cases in which it is permissible to declare a level 2
C                error is a reverse communication Library routine that
C                is likely to be called repeatedly until it integrates
C                across some interval.  If there is a serious error in
C                the input such that another step cannot be taken and
C                the Library routine is called again without the input
C                error having been corrected by the caller, the Library
C                routine will probably be called forever with improper
C                input.  In this case, it is reasonable to declare the
C                error to be fatal.
C
C    Each of the arguments to XERMSG is input; none will be modified by
C    XERMSG.  A routine may make multiple calls to XERMSG with warning
C    level messages; however, after a call to XERMSG with a recoverable
C    error, the routine should return to the user.  Do not try to call
C    XERMSG with a second recoverable error after the first recoverable
C    error because the error package saves the error number.  The user
C    can retrieve this error number by calling another entry point in
C    the error handling package and then clear the error number when
C    recovering from the error.  Calling XERMSG in succession causes the
C    old error number to be overwritten by the latest error number.
C    This is considered harmless for error numbers associated with
C    warning messages but must not be done for error numbers of serious
C    errors.  After a call to XERMSG with a recoverable error, the user
C    must be given a chance to call NUMXER or XERCLR to retrieve or
C    clear the error number.
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  FDUMP, J4SAVE, XERCNT, XERHLT, XERPRN, XERSVE
C***REVISION HISTORY  (YYMMDD)
C   880101  DATE WRITTEN
C   880621  REVISED AS DIRECTED AT SLATEC CML MEETING OF FEBRUARY 1988.
C           THERE ARE TWO BASIC CHANGES.
C           1.  A NEW ROUTINE, XERPRN, IS USED INSTEAD OF XERPRT TO
C               PRINT MESSAGES.  THIS ROUTINE WILL BREAK LONG MESSAGES
C               INTO PIECES FOR PRINTING ON MULTIPLE LINES.  '$$' IS
C               ACCEPTED AS A NEW LINE SENTINEL.  A PREFIX CAN BE
C               ADDED TO EACH LINE TO BE PRINTED.  XERMSG USES EITHER
C               ' ***' OR ' *  ' AND LONG MESSAGES ARE BROKEN EVERY
C               72 CHARACTERS (AT MOST) SO THAT THE MAXIMUM LINE
C               LENGTH OUTPUT CAN NOW BE AS GREAT AS 76.
C           2.  THE TEXT OF ALL MESSAGES IS NOW IN UPPER CASE SINCE THE
C               FORTRAN STANDARD DOCUMENT DOES NOT ADMIT THE EXISTENCE
C               OF LOWER CASE.
C   880708  REVISED AFTER THE SLATEC CML MEETING OF JUNE 29 AND 30.
C           THE PRINCIPAL CHANGES ARE
C           1.  CLARIFY COMMENTS IN THE PROLOGUES
C           2.  RENAME XRPRNT TO XERPRN
C           3.  REWORK HANDLING OF '$$' IN XERPRN TO HANDLE BLANK LINES
C               SIMILAR TO THE WAY FORMAT STATEMENTS HANDLE THE /
C               CHARACTER FOR NEW RECORDS.
C   890706  REVISED WITH THE HELP OF FRED FRITSCH AND REG CLEMENS TO
C           CLEAN UP THE CODING.
C   890721  REVISED TO USE NEW FEATURE IN XERPRN TO COUNT CHARACTERS IN
C           PREFIX.
C   891013  REVISED TO CORRECT COMMENTS.
C   891214  Prologue converted to Version 4.0 format.  (WRB)
C   900510  Changed test on NERR to be -9999999 < NERR < 99999999, but
C           NERR .ne. 0, and on LEVEL to be -2 < LEVEL < 3.  Added
C           LEVEL=-1 logic, changed calls to XERSAV to XERSVE, and
C           XERCTL to XERCNT.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XERMSG
      CHARACTER*(*) LIBRAR, SUBROU, MESSG
      CHARACTER*8 XLIBR, XSUBR
      CHARACTER*72  TEMP
      CHARACTER*20  LFIRST
C***FIRST EXECUTABLE STATEMENT  XERMSG
      LKNTRL = J4SAVE (2, 0, .FALSE.)
      MAXMES = J4SAVE (4, 0, .FALSE.)
C
C       LKNTRL IS A LOCAL COPY OF THE CONTROL FLAG KONTRL.
C       MAXMES IS THE MAXIMUM NUMBER OF TIMES ANY PARTICULAR MESSAGE
C          SHOULD BE PRINTED.
C
C       WE PRINT A FATAL ERROR MESSAGE AND TERMINATE FOR AN ERROR IN
C          CALLING XERMSG.  THE ERROR NUMBER SHOULD BE POSITIVE,
C          AND THE LEVEL SHOULD BE BETWEEN 0 AND 2.
C
      IF (NERR.LT.-9999999 .OR. NERR.GT.99999999 .OR. NERR.EQ.0 .OR.
     *   LEVEL.LT.-1 .OR. LEVEL.GT.2) THEN
         CALL XERPRN (' ***', -1, 'FATAL ERROR IN...$$ ' //
     *      'XERMSG -- INVALID ERROR NUMBER OR LEVEL$$ '//
     *      'JOB ABORT DUE TO FATAL ERROR.', 72)
         CALL XERSVE (' ', ' ', ' ', 0, 0, 0, KDUMMY)
         CALL XERHLT (' ***XERMSG -- INVALID INPUT')
         RETURN
      ENDIF
C
C       RECORD THE MESSAGE.
C
      I = J4SAVE (1, NERR, .TRUE.)
      CALL XERSVE (LIBRAR, SUBROU, MESSG, 1, NERR, LEVEL, KOUNT)
C
C       HANDLE PRINT-ONCE WARNING MESSAGES.
C
      IF (LEVEL.EQ.-1 .AND. KOUNT.GT.1) RETURN
C
C       ALLOW TEMPORARY USER OVERRIDE OF THE CONTROL FLAG.
C
      XLIBR  = LIBRAR
      XSUBR  = SUBROU
      LFIRST = MESSG
      LERR   = NERR
      LLEVEL = LEVEL
      CALL XERCNT (XLIBR, XSUBR, LFIRST, LERR, LLEVEL, LKNTRL)
C
      LKNTRL = MAX(-2, MIN(2,LKNTRL))
      MKNTRL = ABS(LKNTRL)
C
C       SKIP PRINTING IF THE CONTROL FLAG VALUE AS RESET IN XERCNT IS
C       ZERO AND THE ERROR IS NOT FATAL.
C
      IF (LEVEL.LT.2 .AND. LKNTRL.EQ.0) GO TO 30
      IF (LEVEL.EQ.0 .AND. KOUNT.GT.MAXMES) GO TO 30
      IF (LEVEL.EQ.1 .AND. KOUNT.GT.MAXMES .AND. MKNTRL.EQ.1) GO TO 30
      IF (LEVEL.EQ.2 .AND. KOUNT.GT.MAX(1,MAXMES)) GO TO 30
C
C       ANNOUNCE THE NAMES OF THE LIBRARY AND SUBROUTINE BY BUILDING A
C       MESSAGE IN CHARACTER VARIABLE TEMP (NOT EXCEEDING 66 CHARACTERS)
C       AND SENDING IT OUT VIA XERPRN.  PRINT ONLY IF CONTROL FLAG
C       IS NOT ZERO.
C
      IF (LKNTRL .NE. 0) THEN
         TEMP(1:21) = 'MESSAGE FROM ROUTINE '
         I = MIN(LEN(SUBROU), 16)
         TEMP(22:21+I) = SUBROU(1:I)
         TEMP(22+I:33+I) = ' IN LIBRARY '
         LTEMP = 33 + I
         I = MIN(LEN(LIBRAR), 16)
         TEMP(LTEMP+1:LTEMP+I) = LIBRAR (1:I)
         TEMP(LTEMP+I+1:LTEMP+I+1) = '.'
         LTEMP = LTEMP + I + 1
         CALL XERPRN (' ***', -1, TEMP(1:LTEMP), 72)
      ENDIF
C
C       IF LKNTRL IS POSITIVE, PRINT AN INTRODUCTORY LINE BEFORE
C       PRINTING THE MESSAGE.  THE INTRODUCTORY LINE TELLS THE CHOICE
C       FROM EACH OF THE FOLLOWING THREE OPTIONS.
C       1.  LEVEL OF THE MESSAGE
C              'INFORMATIVE MESSAGE'
C              'POTENTIALLY RECOVERABLE ERROR'
C              'FATAL ERROR'
C       2.  WHETHER CONTROL FLAG WILL ALLOW PROGRAM TO CONTINUE
C              'PROG CONTINUES'
C              'PROG ABORTED'
C       3.  WHETHER OR NOT A TRACEBACK WAS REQUESTED.  (THE TRACEBACK
C           MAY NOT BE IMPLEMENTED AT SOME SITES, SO THIS ONLY TELLS
C           WHAT WAS REQUESTED, NOT WHAT WAS DELIVERED.)
C              'TRACEBACK REQUESTED'
C              'TRACEBACK NOT REQUESTED'
C       NOTICE THAT THE LINE INCLUDING FOUR PREFIX CHARACTERS WILL NOT
C       EXCEED 74 CHARACTERS.
C       WE SKIP THE NEXT BLOCK IF THE INTRODUCTORY LINE IS NOT NEEDED.
C
      IF (LKNTRL .GT. 0) THEN
C
C       THE FIRST PART OF THE MESSAGE TELLS ABOUT THE LEVEL.
C
         IF (LEVEL .LE. 0) THEN
            TEMP(1:20) = 'INFORMATIVE MESSAGE,'
            LTEMP = 20
         ELSEIF (LEVEL .EQ. 1) THEN
            TEMP(1:30) = 'POTENTIALLY RECOVERABLE ERROR,'
            LTEMP = 30
         ELSE
            TEMP(1:12) = 'FATAL ERROR,'
            LTEMP = 12
         ENDIF
C
C       THEN WHETHER THE PROGRAM WILL CONTINUE.
C
         IF ((MKNTRL.EQ.2 .AND. LEVEL.GE.1) .OR.
     *       (MKNTRL.EQ.1 .AND. LEVEL.EQ.2)) THEN
            TEMP(LTEMP+1:LTEMP+14) = ' PROG ABORTED,'
            LTEMP = LTEMP + 14
         ELSE
            TEMP(LTEMP+1:LTEMP+16) = ' PROG CONTINUES,'
            LTEMP = LTEMP + 16
         ENDIF
C
C       FINALLY TELL WHETHER THERE SHOULD BE A TRACEBACK.
C
         IF (LKNTRL .GT. 0) THEN
            TEMP(LTEMP+1:LTEMP+20) = ' TRACEBACK REQUESTED'
            LTEMP = LTEMP + 20
         ELSE
            TEMP(LTEMP+1:LTEMP+24) = ' TRACEBACK NOT REQUESTED'
            LTEMP = LTEMP + 24
         ENDIF
         CALL XERPRN (' ***', -1, TEMP(1:LTEMP), 72)
      ENDIF
C
C       NOW SEND OUT THE MESSAGE.
C
      CALL XERPRN (' *  ', -1, MESSG, 72)
C
C       IF LKNTRL IS POSITIVE, WRITE THE ERROR NUMBER AND REQUEST A
C          TRACEBACK.
C
      IF (LKNTRL .GT. 0) THEN
         WRITE (TEMP, '(''ERROR NUMBER = '', I8)') NERR
         DO 10 I=16,22
            IF (TEMP(I:I) .NE. ' ') GO TO 20
   10    CONTINUE
C
   20    CALL XERPRN (' *  ', -1, TEMP(1:15) // TEMP(I:23), 72)
         CALL FDUMP
      ENDIF
C
C       IF LKNTRL IS NOT ZERO, PRINT A BLANK LINE AND AN END OF MESSAGE.
C
      IF (LKNTRL .NE. 0) THEN
         CALL XERPRN (' *  ', -1, ' ', 72)
         CALL XERPRN (' ***', -1, 'END OF MESSAGE', 72)
         CALL XERPRN ('    ',  0, ' ', 72)
      ENDIF
C
C       IF THE ERROR IS NOT FATAL OR THE ERROR IS RECOVERABLE AND THE
C       CONTROL FLAG IS SET FOR RECOVERY, THEN RETURN.
C
   30 IF (LEVEL.LE.0 .OR. (LEVEL.EQ.1 .AND. MKNTRL.LE.1)) RETURN
C
C       THE PROGRAM WILL BE STOPPED DUE TO AN UNRECOVERED ERROR OR A
C       FATAL ERROR.  PRINT THE REASON FOR THE ABORT AND THE ERROR
C       SUMMARY IF THE CONTROL FLAG AND THE MAXIMUM ERROR COUNT PERMIT.
C
      IF (LKNTRL.GT.0 .AND. KOUNT.LT.MAX(1,MAXMES)) THEN
         IF (LEVEL .EQ. 1) THEN
            CALL XERPRN
     *         (' ***', -1, 'JOB ABORT DUE TO UNRECOVERED ERROR.', 72)
         ELSE
            CALL XERPRN(' ***', -1, 'JOB ABORT DUE TO FATAL ERROR.', 72)
         ENDIF
         CALL XERSVE (' ', ' ', ' ', -1, 0, 0, KDUMMY)
         CALL XERHLT (' ')
      ELSE
         CALL XERHLT (MESSG)
      ENDIF
      RETURN
      END
*DECK XERPRN
      SUBROUTINE XERPRN (PREFIX, NPREF, MESSG, NWRAP)
C***BEGIN PROLOGUE  XERPRN
C***SUBSIDIARY
C***PURPOSE  Print error messages processed by XERMSG.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3C
C***TYPE      ALL (XERPRN-A)
C***KEYWORDS  ERROR MESSAGES, PRINTING, XERROR
C***AUTHOR  Fong, Kirby, (NMFECC at LLNL)
C***DESCRIPTION
C
C This routine sends one or more lines to each of the (up to five)
C logical units to which error messages are to be sent.  This routine
C is called several times by XERMSG, sometimes with a single line to
C print and sometimes with a (potentially very long) message that may
C wrap around into multiple lines.
C
C PREFIX  Input argument of type CHARACTER.  This argument contains
C         characters to be put at the beginning of each line before
C         the body of the message.  No more than 16 characters of
C         PREFIX will be used.
C
C NPREF   Input argument of type INTEGER.  This argument is the number
C         of characters to use from PREFIX.  If it is negative, the
C         intrinsic function LEN is used to determine its length.  If
C         it is zero, PREFIX is not used.  If it exceeds 16 or if
C         LEN(PREFIX) exceeds 16, only the first 16 characters will be
C         used.  If NPREF is positive and the length of PREFIX is less
C         than NPREF, a copy of PREFIX extended with blanks to length
C         NPREF will be used.
C
C MESSG   Input argument of type CHARACTER.  This is the text of a
C         message to be printed.  If it is a long message, it will be
C         broken into pieces for printing on multiple lines.  Each line
C         will start with the appropriate prefix and be followed by a
C         piece of the message.  NWRAP is the number of characters per
C         piece; that is, after each NWRAP characters, we break and
C         start a new line.  In addition the characters '$$' embedded
C         in MESSG are a sentinel for a new line.  The counting of
C         characters up to NWRAP starts over for each new line.  The
C         value of NWRAP typically used by XERMSG is 72 since many
C         older error messages in the SLATEC Library are laid out to
C         rely on wrap-around every 72 characters.
C
C NWRAP   Input argument of type INTEGER.  This gives the maximum size
C         piece into which to break MESSG for printing on multiple
C         lines.  An embedded '$$' ends a line, and the count restarts
C         at the following character.  If a line break does not occur
C         on a blank (it would split a word) that word is moved to the
C         next line.  Values of NWRAP less than 16 will be treated as
C         16.  Values of NWRAP greater than 132 will be treated as 132.
C         The actual line length will be NPREF + NWRAP after NPREF has
C         been adjusted to fall between 0 and 16 and NWRAP has been
C         adjusted to fall between 16 and 132.
C
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  I1MACH, XGETUA
C***REVISION HISTORY  (YYMMDD)
C   880621  DATE WRITTEN
C   880708  REVISED AFTER THE SLATEC CML SUBCOMMITTEE MEETING OF
C           JUNE 29 AND 30 TO CHANGE THE NAME TO XERPRN AND TO REWORK
C           THE HANDLING OF THE NEW LINE SENTINEL TO BEHAVE LIKE THE
C           SLASH CHARACTER IN FORMAT STATEMENTS.
C   890706  REVISED WITH THE HELP OF FRED FRITSCH AND REG CLEMENS TO
C           STREAMLINE THE CODING AND FIX A BUG THAT CAUSED EXTRA BLANK
C           LINES TO BE PRINTED.
C   890721  REVISED TO ADD A NEW FEATURE.  A NEGATIVE VALUE OF NPREF
C           CAUSES LEN(PREFIX) TO BE USED AS THE LENGTH.
C   891013  REVISED TO CORRECT ERROR IN CALCULATING PREFIX LENGTH.
C   891214  Prologue converted to Version 4.0 format.  (WRB)
C   900510  Added code to break messages between words.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XERPRN
      CHARACTER*(*) PREFIX, MESSG
      INTEGER NPREF, NWRAP
      CHARACTER*148 CBUFF
      INTEGER IU(5), NUNIT
      CHARACTER*2 NEWLIN
      PARAMETER (NEWLIN = '$$')
C***FIRST EXECUTABLE STATEMENT  XERPRN
      CALL XGETUA(IU,NUNIT)
C
C       A ZERO VALUE FOR A LOGICAL UNIT NUMBER MEANS TO USE THE STANDARD
C       ERROR MESSAGE UNIT INSTEAD.  I1MACH(4) RETRIEVES THE STANDARD
C       ERROR MESSAGE UNIT.
C
      N = I1MACH(4)
      DO 10 I=1,NUNIT
         IF (IU(I) .EQ. 0) IU(I) = N
   10 CONTINUE
C
C       LPREF IS THE LENGTH OF THE PREFIX.  THE PREFIX IS PLACED AT THE
C       BEGINNING OF CBUFF, THE CHARACTER BUFFER, AND KEPT THERE DURING
C       THE REST OF THIS ROUTINE.
C
      IF ( NPREF .LT. 0 ) THEN
         LPREF = LEN(PREFIX)
      ELSE
         LPREF = NPREF
      ENDIF
      LPREF = MIN(16, LPREF)
      IF (LPREF .NE. 0) CBUFF(1:LPREF) = PREFIX
C
C       LWRAP IS THE MAXIMUM NUMBER OF CHARACTERS WE WANT TO TAKE AT ONE
C       TIME FROM MESSG TO PRINT ON ONE LINE.
C
      LWRAP = MAX(16, MIN(132, NWRAP))
C
C       SET LENMSG TO THE LENGTH OF MESSG, IGNORE ANY TRAILING BLANKS.
C
      LENMSG = LEN(MESSG)
      N = LENMSG
      DO 20 I=1,N
         IF (MESSG(LENMSG:LENMSG) .NE. ' ') GO TO 30
         LENMSG = LENMSG - 1
   20 CONTINUE
   30 CONTINUE
C
C       IF THE MESSAGE IS ALL BLANKS, THEN PRINT ONE BLANK LINE.
C
      IF (LENMSG .EQ. 0) THEN
         CBUFF(LPREF+1:LPREF+1) = ' '
         DO 40 I=1,NUNIT
            WRITE(IU(I), '(A)') CBUFF(1:LPREF+1)
   40    CONTINUE
         RETURN
      ENDIF
C
C       SET NEXTC TO THE POSITION IN MESSG WHERE THE NEXT SUBSTRING
C       STARTS.  FROM THIS POSITION WE SCAN FOR THE NEW LINE SENTINEL.
C       WHEN NEXTC EXCEEDS LENMSG, THERE IS NO MORE TO PRINT.
C       WE LOOP BACK TO LABEL 50 UNTIL ALL PIECES HAVE BEEN PRINTED.
C
C       WE LOOK FOR THE NEXT OCCURRENCE OF THE NEW LINE SENTINEL.  THE
C       INDEX INTRINSIC FUNCTION RETURNS ZERO IF THERE IS NO OCCURRENCE
C       OR IF THE LENGTH OF THE FIRST ARGUMENT IS LESS THAN THE LENGTH
C       OF THE SECOND ARGUMENT.
C
C       THERE ARE SEVERAL CASES WHICH SHOULD BE CHECKED FOR IN THE
C       FOLLOWING ORDER.  WE ARE ATTEMPTING TO SET LPIECE TO THE NUMBER
C       OF CHARACTERS THAT SHOULD BE TAKEN FROM MESSG STARTING AT
C       POSITION NEXTC.
C
C       LPIECE .EQ. 0   THE NEW LINE SENTINEL DOES NOT OCCUR IN THE
C                       REMAINDER OF THE CHARACTER STRING.  LPIECE
C                       SHOULD BE SET TO LWRAP OR LENMSG+1-NEXTC,
C                       WHICHEVER IS LESS.
C
C       LPIECE .EQ. 1   THE NEW LINE SENTINEL STARTS AT MESSG(NEXTC:
C                       NEXTC).  LPIECE IS EFFECTIVELY ZERO, AND WE
C                       PRINT NOTHING TO AVOID PRODUCING UNNECESSARY
C                       BLANK LINES.  THIS TAKES CARE OF THE SITUATION
C                       WHERE THE LIBRARY ROUTINE HAS A MESSAGE OF
C                       EXACTLY 72 CHARACTERS FOLLOWED BY A NEW LINE
C                       SENTINEL FOLLOWED BY MORE CHARACTERS.  NEXTC
C                       SHOULD BE INCREMENTED BY 2.
C
C       LPIECE .GT. LWRAP+1  REDUCE LPIECE TO LWRAP.
C
C       ELSE            THIS LAST CASE MEANS 2 .LE. LPIECE .LE. LWRAP+1
C                       RESET LPIECE = LPIECE-1.  NOTE THAT THIS
C                       PROPERLY HANDLES THE END CASE WHERE LPIECE .EQ.
C                       LWRAP+1.  THAT IS, THE SENTINEL FALLS EXACTLY
C                       AT THE END OF A LINE.
C
      NEXTC = 1
   50 LPIECE = INDEX(MESSG(NEXTC:LENMSG), NEWLIN)
      IF (LPIECE .EQ. 0) THEN
C
C       THERE WAS NO NEW LINE SENTINEL FOUND.
C
         IDELTA = 0
         LPIECE = MIN(LWRAP, LENMSG+1-NEXTC)
         IF (LPIECE .LT. LENMSG+1-NEXTC) THEN
            DO 52 I=LPIECE+1,2,-1
               IF (MESSG(NEXTC+I-1:NEXTC+I-1) .EQ. ' ') THEN
                  LPIECE = I-1
                  IDELTA = 1
                  GOTO 54
               ENDIF
   52       CONTINUE
         ENDIF
   54    CBUFF(LPREF+1:LPREF+LPIECE) = MESSG(NEXTC:NEXTC+LPIECE-1)
         NEXTC = NEXTC + LPIECE + IDELTA
      ELSEIF (LPIECE .EQ. 1) THEN
C
C       WE HAVE A NEW LINE SENTINEL AT MESSG(NEXTC:NEXTC+1).
C       DON'T PRINT A BLANK LINE.
C
         NEXTC = NEXTC + 2
         GO TO 50
      ELSEIF (LPIECE .GT. LWRAP+1) THEN
C
C       LPIECE SHOULD BE SET DOWN TO LWRAP.
C
         IDELTA = 0
         LPIECE = LWRAP
         DO 56 I=LPIECE+1,2,-1
            IF (MESSG(NEXTC+I-1:NEXTC+I-1) .EQ. ' ') THEN
               LPIECE = I-1
               IDELTA = 1
               GOTO 58
            ENDIF
   56    CONTINUE
   58    CBUFF(LPREF+1:LPREF+LPIECE) = MESSG(NEXTC:NEXTC+LPIECE-1)
         NEXTC = NEXTC + LPIECE + IDELTA
      ELSE
C
C       IF WE ARRIVE HERE, IT MEANS 2 .LE. LPIECE .LE. LWRAP+1.
C       WE SHOULD DECREMENT LPIECE BY ONE.
C
         LPIECE = LPIECE - 1
         CBUFF(LPREF+1:LPREF+LPIECE) = MESSG(NEXTC:NEXTC+LPIECE-1)
         NEXTC  = NEXTC + LPIECE + 2
      ENDIF
C
C       PRINT
C
      DO 60 I=1,NUNIT
         WRITE(IU(I), '(A)') CBUFF(1:LPREF+LPIECE)
   60 CONTINUE
C
      IF (NEXTC .LE. LENMSG) GO TO 50
      RETURN
      END
*DECK XERSVE
      SUBROUTINE XERSVE (LIBRAR, SUBROU, MESSG, KFLAG, NERR, LEVEL,
     +   ICOUNT)
C***BEGIN PROLOGUE  XERSVE
C***SUBSIDIARY
C***PURPOSE  Record that an error has occurred.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3
C***TYPE      ALL (XERSVE-A)
C***KEYWORDS  ERROR, XERROR
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C *Usage:
C
C        INTEGER  KFLAG, NERR, LEVEL, ICOUNT
C        CHARACTER * (len) LIBRAR, SUBROU, MESSG
C
C        CALL XERSVE (LIBRAR, SUBROU, MESSG, KFLAG, NERR, LEVEL, ICOUNT)
C
C *Arguments:
C
C        LIBRAR :IN    is the library that the message is from.
C        SUBROU :IN    is the subroutine that the message is from.
C        MESSG  :IN    is the message to be saved.
C        KFLAG  :IN    indicates the action to be performed.
C                      when KFLAG > 0, the message in MESSG is saved.
C                      when KFLAG=0 the tables will be dumped and
C                      cleared.
C                      when KFLAG < 0, the tables will be dumped and
C                      not cleared.
C        NERR   :IN    is the error number.
C        LEVEL  :IN    is the error severity.
C        ICOUNT :OUT   the number of times this message has been seen,
C                      or zero if the table has overflowed and does not
C                      contain this message specifically.  When KFLAG=0,
C                      ICOUNT will not be altered.
C
C *Description:
C
C   Record that this error occurred and possibly dump and clear the
C   tables.
C
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  I1MACH, XGETUA
C***REVISION HISTORY  (YYMMDD)
C   800319  DATE WRITTEN
C   861211  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900413  Routine modified to remove reference to KFLAG.  (WRB)
C   900510  Changed to add LIBRARY NAME and SUBROUTINE to calling
C           sequence, use IF-THEN-ELSE, make number of saved entries
C           easily changeable, changed routine name from XERSAV to
C           XERSVE.  (RWC)
C   910626  Added LIBTAB and SUBTAB to SAVE statement.  (BKS)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XERSVE
      PARAMETER (LENTAB=10)
      INTEGER LUN(5)
      CHARACTER*(*) LIBRAR, SUBROU, MESSG
      CHARACTER*8  LIBTAB(LENTAB), SUBTAB(LENTAB), LIB, SUB
      CHARACTER*20 MESTAB(LENTAB), MES
      DIMENSION NERTAB(LENTAB), LEVTAB(LENTAB), KOUNT(LENTAB)
      SAVE LIBTAB, SUBTAB, MESTAB, NERTAB, LEVTAB, KOUNT, KOUNTX, NMSG
      DATA KOUNTX/0/, NMSG/0/
C***FIRST EXECUTABLE STATEMENT  XERSVE
C
      IF (KFLAG.LE.0) THEN
C
C        Dump the table.
C
         IF (NMSG.EQ.0) RETURN
C
C        Print to each unit.
C
         CALL XGETUA (LUN, NUNIT)
         DO 20 KUNIT = 1,NUNIT
            IUNIT = LUN(KUNIT)
            IF (IUNIT.EQ.0) IUNIT = I1MACH(4)
C
C           Print the table header.
C
            WRITE (IUNIT,9000)
C
C           Print body of table.
C
            DO 10 I = 1,NMSG
               WRITE (IUNIT,9010) LIBTAB(I), SUBTAB(I), MESTAB(I),
     *            NERTAB(I),LEVTAB(I),KOUNT(I)
   10       CONTINUE
C
C           Print number of other errors.
C
            IF (KOUNTX.NE.0) WRITE (IUNIT,9020) KOUNTX
            WRITE (IUNIT,9030)
   20    CONTINUE
C
C        Clear the error tables.
C
         IF (KFLAG.EQ.0) THEN
            NMSG = 0
            KOUNTX = 0
         ENDIF
      ELSE
C
C        PROCESS A MESSAGE...
C        SEARCH FOR THIS MESSG, OR ELSE AN EMPTY SLOT FOR THIS MESSG,
C        OR ELSE DETERMINE THAT THE ERROR TABLE IS FULL.
C
         LIB = LIBRAR
         SUB = SUBROU
         MES = MESSG
         DO 30 I = 1,NMSG
            IF (LIB.EQ.LIBTAB(I) .AND. SUB.EQ.SUBTAB(I) .AND.
     *         MES.EQ.MESTAB(I) .AND. NERR.EQ.NERTAB(I) .AND.
     *         LEVEL.EQ.LEVTAB(I)) THEN
                  KOUNT(I) = KOUNT(I) + 1
                  ICOUNT = KOUNT(I)
                  RETURN
            ENDIF
   30    CONTINUE
C
         IF (NMSG.LT.LENTAB) THEN
C
C           Empty slot found for new message.
C
            NMSG = NMSG + 1
            LIBTAB(I) = LIB
            SUBTAB(I) = SUB
            MESTAB(I) = MES
            NERTAB(I) = NERR
            LEVTAB(I) = LEVEL
            KOUNT (I) = 1
            ICOUNT    = 1
         ELSE
C
C           Table is full.
C
            KOUNTX = KOUNTX+1
            ICOUNT = 0
         ENDIF
      ENDIF
      RETURN
C
C     Formats.
C
 9000 FORMAT ('0          ERROR MESSAGE SUMMARY' /
     +   ' LIBRARY    SUBROUTINE MESSAGE START             NERR',
     +   '     LEVEL     COUNT')
 9010 FORMAT (1X,A,3X,A,3X,A,3I10)
 9020 FORMAT ('0OTHER ERRORS NOT INDIVIDUALLY TABULATED = ', I10)
 9030 FORMAT (1X)
      END
*DECK XERHLT
      SUBROUTINE XERHLT (MESSG)
C***BEGIN PROLOGUE  XERHLT
C***SUBSIDIARY
C***PURPOSE  Abort program execution and print error message.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3C
C***TYPE      ALL (XERHLT-A)
C***KEYWORDS  ABORT PROGRAM EXECUTION, ERROR, XERROR
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C     Abstract
C        ***Note*** machine dependent routine
C        XERHLT aborts the execution of the program.
C        The error message causing the abort is given in the calling
C        sequence, in case one needs it for printing on a dayfile,
C        for example.
C
C     Description of Parameters
C        MESSG is as in XERMSG.
C
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  (NONE)
C***REVISION HISTORY  (YYMMDD)
C   790801  DATE WRITTEN
C   861211  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   900206  Routine changed from user-callable to subsidiary.  (WRB)
C   900510  Changed calling sequence to delete length of character
C           and changed routine name from XERABT to XERHLT.  (RWC)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XERHLT
      CHARACTER*(*) MESSG
C***FIRST EXECUTABLE STATEMENT  XERHLT
      STOP
      END
*DECK XGETUA
      SUBROUTINE XGETUA (IUNITA, N)
C***BEGIN PROLOGUE  XGETUA
C***PURPOSE  Return unit number(s) to which error messages are being
C            sent.
C***LIBRARY   SLATEC (XERROR)
C***CATEGORY  R3C
C***TYPE      ALL (XGETUA-A)
C***KEYWORDS  ERROR, XERROR
C***AUTHOR  Jones, R. E., (SNLA)
C***DESCRIPTION
C
C     Abstract
C        XGETUA may be called to determine the unit number or numbers
C        to which error messages are being sent.
C        These unit numbers may have been set by a call to XSETUN,
C        or a call to XSETUA, or may be a default value.
C
C     Description of Parameters
C      --Output--
C        IUNIT - an array of one to five unit numbers, depending
C                on the value of N.  A value of zero refers to the
C                default unit, as defined by the I1MACH machine
C                constant routine.  Only IUNIT(1),...,IUNIT(N) are
C                defined by XGETUA.  The values of IUNIT(N+1),...,
C                IUNIT(5) are not defined (for N .LT. 5) or altered
C                in any way by XGETUA.
C        N     - the number of units to which copies of the
C                error messages are being sent.  N will be in the
C                range from 1 to 5.
C
C***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC
C                 Error-handling Package, SAND82-0800, Sandia
C                 Laboratories, 1982.
C***ROUTINES CALLED  J4SAVE
C***REVISION HISTORY  (YYMMDD)
C   790801  DATE WRITTEN
C   861211  REVISION DATE from Version 3.2
C   891214  Prologue converted to Version 4.0 format.  (BAB)
C   920501  Reformatted the REFERENCES section.  (WRB)
C***END PROLOGUE  XGETUA
      DIMENSION IUNITA(5)
C***FIRST EXECUTABLE STATEMENT  XGETUA
      N = J4SAVE(5,0,.FALSE.)
      DO 30 I=1,N
         INDEX = I+4
         IF (I.EQ.1) INDEX = 3
         IUNITA(I) = J4SAVE(INDEX,0,.FALSE.)
   30 CONTINUE
      RETURN
      END
