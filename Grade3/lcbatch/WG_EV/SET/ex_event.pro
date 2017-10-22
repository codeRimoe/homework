pro ex_event,ev
  widget_control, ev.id, get_uvalue = ex
  widget_control, ev.TOP, get_uvalue = pt
  (*pt).img[0]=ex
end