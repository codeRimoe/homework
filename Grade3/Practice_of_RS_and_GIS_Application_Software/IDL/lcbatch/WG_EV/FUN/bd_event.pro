pro bd_event,ev
  widget_control, ev.TOP, get_uvalue = pw
  widget_control, (*pw).bm_math, get_value = b
  (*pw).band = b
end