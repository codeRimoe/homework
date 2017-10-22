pro run_event,ev

  widget_control, ev.ID, get_uvalue = pt

  e=(*pt).e

  p_win = widget_base(group_leader = ev.TOP, $
    xoffset = 400, yoffset =600,$
    xsize = 500, ysize = 20,$
    ;tlb_frame_attr = 11,$
    /base_align_left, /column, /floating, /modal,$
    title = 'Processing...')
  protxt = widget_label(p_win, xsize=500, value = 'Start Processing...')
  widget_control, p_win, /realize
  
  files = *((*pt).files)
  foreach file, files do begin
    xf = strsplit(file,'\',/EXTRACT)
    name =  strsplit(xf[N_elements(xf)-1],'.',/EXTRACT)
    name = name[0]
    
    ;set bands
    img = (*pt).img
    pbs = []
    if img[0] eq 8 then i = 1 else i = 0
    foreach ix, img[1:*] do begin
      if ix then pbs = [pbs,i]
      i++
    endforeach
    
    raster = []
    widget_control, protxt, set_value = 'Reading File: ' + file
    raster = e.openraster(file)
    
    if ((*pt).x1 and (*pt).y1 and (*pt).x2 and (*pt).y1) then begin
      widget_control, protxt, set_value = 'Clip File: ' + file
      file_mkdir, (*pt).path+'\clip'
      subset = clip(raster[0],pt,pbs,name)
    endif else subset = raster[0]
    
    if (*pt).quac then begin
      widget_control, protxt, set_value = 'QUAC File: ' + file
      file_mkdir, (*pt).path+'\quac'
      quacb = quac(subset,pt,name)
    endif else quacb=subset
    
    if (*pt).band eq "" then begin
    endif else begin
      widget_control, protxt, set_value = 'BandMath File: ' + file
      file_mkdir, (*pt).path+'\bandmath'
      bd = bandmath(quacb,pt,name)
    endelse
    widget_control, protxt, set_value = 'Close File: ' + file
    foreach r, raster do r.close
  endforeach
  widget_control, protxt, set_value = 'Done!'
  widget_control, p_win, /destroy
  widget_control, ev.TOP, /destroy
  
end