function clip,raster,pt,bds,name

  FORWARD_FUNCTION ENVISubsetRaster
  
  if (*pt).cv then begin
    ; This is the area of interest:
    UpperLeftLat = (*pt).y1
    UpperLeftLon = (*pt).x1
    LowerRightLat = (*pt).y2
    LowerRightLon = (*pt).x2

    ; Get the spatial reference of the raster
    SpatialRef = raster[0].SPATIALREF

    ; Convert from Lon/Lat to MapX/MayY
    SpatialRef.ConvertLonLatToMap, UpperLeftLon, UpperLeftLat, ULMapX, ULMapY
    SpatialRef.ConvertLonLatToMap, LowerRightLon, LowerRightLat, LRMapX, LRMapY
    
  endif else begin
    ULMapX = (*pt).x1
    LRMapY = (*pt).y1
    LRMapX = (*pt).x2
    ULMapY = (*pt).y2
  endelse

  ; Define the geographic subset
  
  subset = ENVISubsetRaster(Raster, SPATIALREF=SpatialRef,$
    SUB_RECT=[ULMapX, LRMapY, LRMapX, ULMapY], BANDS=bds)
  newFile = (*pt).path + '\clip\clip_' + name + (*pt).fn + '.TIF'
  subset.export, newFile, 'TIFF'
  return, subset
  
end