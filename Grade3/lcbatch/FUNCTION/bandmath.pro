function bandmath,raster,pt,name

  FORWARD_FUNCTION ENVIPixelwiseBandMathRaster
  bm = ENVIPixelwiseBandMathRaster(raster,(*pt).band)

  newFile = (*pt).path + '\bandmath\bm_' + name + (*pt).fn + '.TIF'
  bm.export, newFile, 'TIFF'
  return, bm

end