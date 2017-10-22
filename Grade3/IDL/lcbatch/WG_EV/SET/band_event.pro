pro band_event,ev
  widget_control, ev.id, get_uvalue = b
  widget_control, ev.TOP, get_uvalue = pt
  (*pt).img[b]=ev.select
  i = 1
  k = 0
  btxt = ''
  nx=['1','2','3','4','5','6']
  foreach ix, (*pt).img[1:*] do begin
    txt = ''
    case i of
      1:txt=':B'
      2:txt=':G'
      3:txt=':R'
      4:txt=':NIR'
      5:txt=':SWIR1'
      6:txt=':SWIR2'
    endcase
    i++
    if ix eq 1 then btxt+='  b'+nx[k++]+txt
  endforeach
  widget_control, (*pt).bt, set_value = btxt
  
end