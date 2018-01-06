pro path_event,ev
  FORWARD_FUNCTION envi_pickfile
  widget_control, ev.TOP, get_uvalue = pw
  (*pw).path = envi_pickfile( /directory,title = 'Select the Output File Path')
  widget_control, (*pw).save_path, set_value = (*pw).path
end