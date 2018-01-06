pro cvc_event,ev
  widget_control, ev.TOP, get_uvalue = pt
  (*(*pt).pw).cv = ev.select
end