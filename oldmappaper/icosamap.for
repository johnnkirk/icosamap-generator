      Program prjctn
      real*4 vcoord(12,2),fcoord(22,2),hold,x1,y1,x2,y2,x3,y3,x4,y4
      real*4 trm1(22),trm2(22),lat(7),lon(7),transx(22),transy(22)
      real*4 trm3(22),trm4(22),coord,p1,p2,p3,p4,base,height,factor
      real*4 llat,llon,p5,p6
      integer*4 i,ii,face,cardno,nexfac,island,ffff,buffer(4000)
      integer*4 count(1000),prefac
101   format(i7,3x,14f5.2)
102   format(i5,2f25.16)
103   format(3i5)
104   format(' ',f20.15,20x,f20.15)
105   format('1','vcoord1',33x,'vcoord2')
106   format('1')
107   format(i2)
108   format(' ',i5,6f15.10)
c
c initialize plot
c
      call plots(buffer,4000)
      mult=3.0
      call plot(10.0*mult,-11.0*mult,3)
      call plot(10.0*mult,-5.0*mult,-3)
c
c read parameters
c
      read(1,102) (i,vcoord(i,1),vcoord(i,2),ii=1,12)
      read(1,102) (i,fcoord(i,1),fcoord(i,2),ii=1,22)
      read(1,102) (i,trm3(i),trm4(i),ii=1,22)
      read(2,102) (i,trm1(i),trm2(i),ii=1,22)
      base=1.323164552735024
      height=base*sqrt(3.0e0)/2.0e0
      factor=(10.0e0/(3.0e0*height))*mult
      base=factor*base
      height=factor*height
      p1=5.0e0*height/3
      p2=2.0e0*height/3
      p4=-height/3.0e0
      p5=base/4.0e0
      p6=height/6.0e0
c
c draw outline
c
      call plot( 0            -p5, p2                  -p6,3)
      call plot( base         -p5, p2                  -p6,2)
      call plot( 1.5e0*base   -p5, p1                  -p6,2)
      call plot( 2.0e0*base   -p5, p2                  -p6,2)
      call plot( 2.5e0*base   -p5, p1                  -p6,2)
      call plot( 3.0e0*base   -p5, p2                  -p6,2)
      call plot( 3.0e0*base   -p5, p3                  -p6,2)
      call plot( 1.5e0*base   -p5, p3                  -p6,2)
      call plot( 2.0e0*base   -p5, p4                  -p6,2)
      call plot( base         -p5, p4                  -p6,2)
      call plot( 0.5e0*base   -p5, p3                  -p6,2)
      call plot( 0            -p5, p4                  -p6,2)
      call plot( -0.5e0*base  -p5, -height             -p6,2)
      call plot( -0.5e0*base  -p5, p3                  -p6,2)
      call plot( -base        -p5, -p2                 -p6,2)
      call plot( -base        -p5, p4                  -p6,2)
      call plot( -2.0e0*base  -p5, p4                  -p6,2)
      call plot( -1.75e0*base -p5, -5.0e0*height/6.0e0 -p6,2)
      call plot( -2.5e0*base  -p5, p3                  -p6,2)
      call plot( -1.5e0*base  -p5, p3                  -p6,2)
      call plot( -2.0e0*base  -p5, p2                  -p6,2)
      call plot( -base        -p5, p2                  -p6,2)
      call plot( -1.5e0*base  -p5, p1                  -p6,2)
      call plot( 0.5e0*base   -p5, p1                  -p6,2)
      call plot( 0            -p5, p2                  -p6,2)
c
c draw boundaries inside outline
c
      call plot( -1.75e0*base -p5, -5.0e0*height/6.0e0 -p6,3)
      call plot( -0,5e0*base  -p5, p1                  -p6,2)
      call plot( 0            -p5, p2                  -p6,2)
      call plot( -base        -p5, p2                  -p6,2)
      call plot( -0.5e0*base  -p5, p3                  -p6,2)
      call plot( -1.5e0*base  -p5, p3                  -p6,2)
      call plot( -base        -p5, p4                  -p6,2)
      call plot( 0            -p5, p4                  -p6,3)
      call plot( -0.5e0*base  -p5, p3                  -p6,2)
      call plot( 0            -p5, p2                  -p6,2)
      call plot( 0.5e0*base   -p5, p3                  -p6,2)
      call plot( -0.5e0*base  -p5, p3                  -p6,2)
      call plot( 0.5e0*base   -p5, p3                  -p6,3)
      call plot( base         -p5, p2                  -p6,2)
      call plot( 3.0e0*base   -p5, p2                  -p6,2)
      call plot( 2.5e0*base   -p5, p3                  -p6,2)
      call plot( 2.0e0*base   -p5, p2                  -p6,2)
      call plot( base         -p5, p4                  -p6,2)
      call plot( 0.5e0*base   -p5, p3                  -p6,3)
      call plot( 1.5e0*base   -p5, p3                  -p6,2)
      call plot( base         -p5, p2                  -p6,2)
6     continue
      write(6,122)
      prefac=0
c
c read card with 7 points, EOF?
c
      do 2 i=1,7
c
c test for (0,180), end of island?
c
      if(abs(lat(i)).gt.1.0e-4.or.abs(lon(i)-180.0e0).gt.1.0e-4)
     *  goto 7
c
c housekeep new island marker
c
      nexfac=0
      go to 15
c
c subtract lon from 180
c
7     continue
      lon(i)=180.0e0-lon(i)
c
c take radian measure
c
      lon(i)=rad(lon(i))
      lat(i)=rad(lat(i))
c
c housekeep new island marker
c
      if(nexfac.eq.1) nexfac=2
      if(nexfac.eq.0) nexfac=1
c
c find triangle the point belongs in
c
      hold=100.0
      prefac=face
      do 4 ffff=1,20
      coord=dist(lat(i),lon(i),fcoord(ffff,1),fcoord(ffff,2))
      if(hold.le.coord) goto 3
      face=ffff
      hold=coord
3     continue
4     continue
c
c check whether belongs in 21, 22 (other halves of 5, 17)
c
      if(face.eq.17.and.dist(lat(i),lon(i),vcoord(4,1),vcoord(4,2)).lt.
     *  dist(lat(i),lon(i),vcoord(9,1),vcoord(9,2))) face=22
      if(face.eq.5.and.dist(lat(i),lon(i),vcoord(4,1),vcoord(4,2)).gt.
     *  dist(lat(i),lon(i),vcoord(12,1),vcoord(12,2)).and.
     *  dist(lat(i),lon(i),vcoord(4,1),vcoord(4,2)).gt.
     *  dist(lat(i),lon(i),vcoord(2,1),vcoord(2,2))) face=21
      if(face.ne.prefac) nexfac=1
c
c apply step 1, part 1 formula
c
      x1=-cos(lat(i))*sin(lon(i)-fcoord(face,2))/
     *    sin(lat(i))*sin(fcoord(face,1))+
     *    cos(lat(i))*cos(fcoord(face,1))*
     *    cos(lon(i)-fcoord(face,2)))
      y1=( sin(lat(i))*cos(fcoord(face,1))-
     *     cos(lat(i))*sin(fcoord(face,1))*cos(lon(i)-fcoord(face,2)))/
     *   ( sin(lat(i))*sin(fcoord(face,1))+
     *     cos(lat(i))*cos(fcoord(face,1))*cos(lon(i)-fcoord(face,2)))
c
c apply step 1, part 2 formula
c
      x2= trm3(face)*x1+trm4(face)*y1
      y2=-trm4(face)*x1+trm3(face)*y1
c
c apply step 2, part 1 formula
c
      x3= trm1(face)*x2+trm2(face)*y2
      y3=-trm2(face)*x2+trm1(face)*y2
c
c apply step 2, part 2 formula
c
      x4=x3+transx(face)
      y4=y3+transy(face)
c
c apply scaling factor
c
      llat=y4*factor
      llon=x4*factor
c
c plot point
c
      ii=4-nexfac
      call plot(llon,llat,ii)
15    continue
2     continue
c
c end of 7 points? if yes:
c
      goto 5
c
c close plot, write summaries (none here now)
c
1     continue
      call plot(0.0,0.0,999)
12    continue
      stop
      end
c
c function to compute the angular great circle distance between two points
c
      real function dist*4 (lat1,lon1,lat2,lon2)
      real*4 lat1,lon1,lat2,lon2
      dist=arcos(cos(lat1)*cos(lat2)*cos(lon2-lon1)+
     *           sin(lat1)*sin(lat2))
      return
      end
c
c function to take the radian measure of any angle expressed in degrees
c
      real function rad*4 (coord)
      real*4 coord
      rad=(coord/180.0e0)*3.141592653589793e0
      return
      end
