pro pro_event,ev
  widget_control, ev.TOP, get_uvalue = pw
  e = (*pw).e
  com_win = widget_base(group_leader = ev.TOP, $
    xoffset = 400, yoffset =400,$
    xsize = 500, ysize = 220,$
    tlb_frame_attr = 1,$
    /base_align_left, /column, /floating, /modal,$
    title = 'Confirm')
  
  clip = ''
  if (*pw).cv then begin
    clip = 'Lat/Lon'
  endif else clip = 'X/Y'
  
  x = '  Satellite: Landsat'
  img = (*pw).img
  case img[0] of
    5:x+='4-5/TM'
    7:x+='7/ETM+'
    8:x+='8/OLI'
    else:x='  Please choose a Satellite!'
  endcase
  
  f = '' 
  i = 1
  foreach ix, img[1:*] do begin
    txt = ''
    case i of
      1:txt='_B'
      2:txt='_G'
      3:txt='_R'
      4:txt='_NIR'
      5:txt='_SWIR1'
      6:txt='_SWIR2'
    endcase
    i++
    if ix eq 1 then f+=txt
  endforeach
  quac = ' No'
  cali = ' No'
  case (*pw).quac of
    0:quac=' Not applied'
    1:quac=' QUAC'
  endcase

  label = widget_label(com_win, value = ' ')
  label = widget_label(com_win, value = '  To do List:' + string(n_elements(*(*pw).files)) + ' Files.')
  label = widget_label(com_win, value = ' ')
  label = widget_label(com_win, value = '  Save Path: ' + (*pw).path)
  label = widget_label(com_win, value = ' ')
  label = widget_label(com_win, value = '  1.Clip:'+clip+string((*pw).x1)+string((*pw).y1)+string((*pw).x2)+string((*pw).y2))
  label = widget_label(com_win, value = '  2.Calibration:'+cali)
  label = widget_label(com_win, value = '  3.Atomspheric Correction:'+quac)
  label = widget_label(com_win, value = '  4.Bandmath: ' + (*pw).band)
  label = widget_label(com_win, value = ' ')
  label = widget_label(com_win, value = x)
  label = widget_label(com_win, value = '  Bands'+f)
  label = widget_label(com_win, value = ' ')
  cvc = widget_button(com_win,/align_center, value = "Proceed Now", uvalue=pw)
  (*pw).fn = f
  widget_control, com_win, /realize
  xmanager, 'run', cvc

end