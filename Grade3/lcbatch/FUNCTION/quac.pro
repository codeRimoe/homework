function quac,raster,pt,name

  FORWARD_FUNCTION ENVIQUACRaster

  quacb = ENVIQUACRaster(raster)

  newFile = (*pt).path + '\quac\quac_' + name + (*pt).fn + '.TIF'
  quacb.export, newFile, 'TIFF'
  return, quacb

end