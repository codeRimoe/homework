pro exitpro_event,ev
  ret = dialog_message('Are you sure to exit?',title = 'Exit', /question)
  if ret eq 'No' then return
  widget_control, ev.TOP, get_uvalue = pw
  (*pw).e.close
  ptr_free, pw
  widget_control, ev.top, /destroy
  return
end