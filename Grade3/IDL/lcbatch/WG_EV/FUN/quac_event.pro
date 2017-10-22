pro quac_event,ev
  widget_control, ev.TOP, get_uvalue = pt
  (*pt).quac=ev.select
end