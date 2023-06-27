!FULL
!    DO I=1,N
!        DO J=1,N
!            KMAX=MIN(I,J)-1
!            MATRIX(I,J)=MATRIX(I,J)-SUM(MATRIX(I,1:KMAX)*MATRIX(1:KMAX,J))
!            IF(I>J) MATRIX(I,J)=MATRIX(I,J)/MATRIX(J,J)
!        ENDDO
!    ENDDO
!
!BAND
!    DO I=1,N
!        JMIN=MAX(I-(P-1),1)
!        JMAX=MIN(I+(Q-1),N)
!        DO J=JMIN,JMAX
!            KMIN=MAX(JMIN,J-(Q-1))
!            KMAX=MIN(I,J)-1
!            MATRIX(I,J)=MATRIX(I,J)-SUM(MATRIX(I,KMIN:KMAX)*MATRIX(KMIN:KMAX,J))
!            IF(I>J) MATRIX(I,J)=MATRIX(I,J)/MATRIX(J,J)
!        ENDDO
!    ENDDO
!
!BAND,COMPRESSED
    DO I=1,N
        JMIN=MAX(I-(P-1),1)
        JMAX=MIN(I+(Q-1),N)
        DO J=JMIN,JMAX
            KMIN=MAX(JMIN,J-(Q-1))
            KMAX=MIN(I,J)-1
            A=0.
            DO K=KMIN,KMAX
                A=A+MATRIX(I,K-I+P)*MATRIX(K,J-K+P)
            ENDDO
            MATRIX(I,J-I+P)=MATRIX(I,J-I+P)-A
            IF(I>J) MATRIX(I,J-I+P)=MATRIX(I,J-I+P)/MATRIX(J,P)
        ENDDO
    ENDDO
