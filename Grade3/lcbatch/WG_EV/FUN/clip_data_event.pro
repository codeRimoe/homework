pro clip_data_event,ev
  widget_control, ev.TOP, get_uvalue = pw
  set_win = widget_base(group_leader = ev.TOP, $
    xoffset = 400, yoffset =400,$
    xsize = 300, ysize = 200,$
    tlb_frame_attr = 1,$
    /base_align_center, /column, /floating, /modal,$
    title = 'Set Point...')
  label = widget_label(set_win, /align_left, value = ' ')
  label = widget_label(set_win, /align_left, value = ' UpperLeft Point:')
  row1 = widget_base(set_win,/row)
  label = widget_label(set_win, /align_left, value = ' ')
  label = widget_label(set_win, /align_left, value = ' LowerRight Point:')
  row2 = widget_base(set_win,/row)
  label = widget_label(set_win, /align_left, value = ' ')

  label = widget_label(row1, /align_left, value = 'X/Col/Lon:')
  x1_text = widget_text(row1,/editable,scr_xsize=40,ysize=1)
  label = widget_label(row1, /align_left, value = '  Y/Row/Lat:')
  y1_text = widget_text(row1,/editable,scr_xsize=40,ysize=1)
  label = widget_label(row2, /align_left, value = 'X/Col/Lon:')
  x2_text = widget_text(row2,/editable,scr_xsize=40,ysize=1)
  label = widget_label(row2, /align_left, value = '  Y/Row/Lat:')
  y2_text = widget_text(row2,/editable,scr_xsize=40,ysize=1)
  cvf = widget_base(set_win,/align_center, /nonexclusive,/row)
  cvc = widget_button(cvf,/align_center, value = "Convert from Lat/Lon", uvalue=4)
  (*pw).cv = 0
  xmanager, 'cvc',cvc

  widget_control, x1_text, get_value = x1
  widget_control, y1_text, get_value = y1
  widget_control, x2_text, get_value = x2
  widget_control, y2_text, get_value = y2
  
  widget_control, set_win, /realize
  btn_s = {pw:pw,$
    x1:x1_text,y1:y1_text,$
    x2:x2_text,y2:y2_text}
  btn_p = ptr_new(btn_s,/no_copy)
  btn = widget_button(set_win,value='Set Point')
  widget_control, set_win, set_uvalue = btn_p
  xmanager, 'set_point',btn
  
end