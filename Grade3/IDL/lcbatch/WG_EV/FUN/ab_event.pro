pro ab_event,ev
  widget_control, ev.TOP, get_uvalue = pw
  set_win = widget_base(group_leader = ev.TOP, $
    xoffset = 400, yoffset =400,$
    xsize = 800, ysize = 210,$
    tlb_frame_attr = 1,$
    /base_align_center, /column, /floating, /modal,$
    title = 'About author')
  label = widget_label(set_win, /align_left, value = '')
  txt = 'Author: Yue H.W. Luo, School of Geography and Planning, Sun-Yatsen University'+string(13B)+string(10B)
  txt += 'Website: http://rimoe.ml'+string(13B)+string(10B)
  txt += 'E-mail: yue.rimoe@gmail.com'+string(13B)+string(10B)+string(13B)+string(10B)
  txt += 'License: Apache v2.0'+string(13B)+string(10B)
  txt += 'TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION'+string(13B)+string(10B)
  txt += 'Copyright 2017 Yue H.W. Luo, yue.rimoe@gmail.com .'+string(13B)+string(10B)+string(13B)+string(10B)
  txt += 'Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the '+string(13B)+string(10B)
  txt += 'License. You may obtain a copy of the License at'+string(13B)+string(10B)
  txt += 'http://www.apache.org/licenses/LICENSE-2.0'+string(13B)+string(10B)
  txt += 'Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" '+string(13B)+string(10B)
  txt += 'BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific '+string(13B)+string(10B)
  txt += 'language governing permissions and limitations under the License.'
  text = widget_text(set_win,scr_xsize=760,ysize=12, value = txt)

  label = widget_label(set_win, /align_left, value = '')
  widget_control, set_win, /realize
end