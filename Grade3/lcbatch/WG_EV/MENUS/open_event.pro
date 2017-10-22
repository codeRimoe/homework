pro open_event,ev
  FORWARD_FUNCTION envi_pickfile
  files = envi_pickfile(/multiple,title = 'Select the Iutput File Path',filter = ['*_mtl.txt'])
  widget_control, ev.TOP, get_uvalue = pw
  if (files[0] eq '') then return
  foreach file, files do begin
    file = strjoin(strsplit(file,'\', /EXTRACT), '\')
    foreach i, *(*pw).files do begin
      if (i eq file) then begin
        return
      endif
    endforeach
    *(*pw).files = [*(*pw).files,file]
  endforeach
  widget_control, (*pw).wl, set_value = *(*pw).files
end
