pro set_point_event,ev

  widget_control, ev.TOP, get_uvalue = pt
  pwt = (*pt).pw
  widget_control, (*pt).x1, get_value = tx1
  widget_control, (*pt).y1, get_value = ty1
  widget_control, (*pt).x2, get_value = tx2
  widget_control, (*pt).y2, get_value = ty2

  (*pwt).x1=string(tx1)
  (*pwt).y1=string(ty1)
  (*pwt).x2=string(tx2)
  (*pwt).y2=string(ty2)
    if (*pwt).cv then begin
      widget_control, (*pwt).cvrt , set_value = 'Lat/Lon'
    endif else begin
      widget_control, (*pwt).cvrt , set_value = 'X/Y'
    endelse
  
  widget_control, (*pwt).x1_text, set_value = tx1
  widget_control, (*pwt).y1_text, set_value = ty1
  widget_control, (*pwt).x2_text, set_value = tx2
  widget_control, (*pwt).y2_text, set_value = ty2
  ptr_free, pt
  widget_control, ev.TOP, /destroy
  
end