pro wl_event,ev
  FORWARD_FUNCTION ENVIEqualizationStretchRaster
  if ev.clicks eq 2 then begin
    widget_control, ev.TOP, get_uvalue = pw
    e = (*pw).e
    file = (*((*pw).files))[ev.index]
    raster = e.openraster(file)
    b = ['b1*1','b2*1','b3*1']
    if max(raster[0].getdata(bands=1)) gt 255 then begin
      b=['b2/255','b3/255','b4/255']
    endif
    r0 = ENVIPixelwiseBandMathRaster(raster[0],b[0])
    r1 = ENVIPixelwiseBandMathRaster(raster[0],b[1])
    r2 = ENVIPixelwiseBandMathRaster(raster[0],b[2])
    foreach r, raster do begin
      r.close
    endforeach
    sr0 = ENVIEqualizationStretchRaster(r0, MIN=0, MAX=255)
    sr1 = ENVIEqualizationStretchRaster(r1, MIN=0, MAX=255)
    sr2 = ENVIEqualizationStretchRaster(r2, MIN=0, MAX=255)
    data0= congrid(sr0.getdata(bands=0),300,300)
    data1= congrid(sr1.getdata(bands=0),300,300)
    data2= congrid(sr2.getdata(bands=0),300,300)
    
    data = [[[data2]],[[data1]],[[data0]]]
    tv, data, true=3

  endif
end
