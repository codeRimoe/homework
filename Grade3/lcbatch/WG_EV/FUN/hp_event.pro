pro hp_event,ev
  widget_control, ev.TOP, get_uvalue = pw
  set_win = widget_base(group_leader = ev.TOP, $
    xoffset = 400, yoffset =400,$
    xsize = 750, ysize = 310,$
    tlb_frame_attr = 1,$
    /base_align_center, /column, /floating, /modal,$
    title = 'Help')
  label = widget_label(set_win, /align_left, value = '')
  
  txt = 'Landsat Batch v0.5.4_release'+string(13B)+string(10B)
  txt += string(13B)+string(10B)
  txt += 'This is a programe for pre-processing Landsat(Mul) Image, develop based on ENVI API.'+string(13B)+string(10B)
  txt += 'Batch task is supoorted, which is convenient to study.'+string(13B)+string(10B)
  txt += 'Now Landsat 4-5/7/8 is supported.'+string(13B)+string(10B)
  txt += string(13B)+string(10B)
  txt += 'To pre-procesing the image, you can:'+string(13B)+string(10B)
  txt += '1. Import the imsges files you going to process, `*_MTL.txt` file needed.'+string(13B)+string(10B)
  txt += '   Files list will display in the list widget, double click the file you can preview the images in overview widget.'+string(13B)+string(10B)
  txt += '2. Set the output file path.'+string(13B)+string(10B)
  txt += '3. a) Clip: Set the coordinate of UpperLeft Point and LowerRight Point.'+string(13B)+string(10B)
  txt += '            Both geographic coordinates and map coordinates is supported.'+string(13B)+string(10B)
  txt += '            If you do not want to clip the images, set the coordinates as 0, or just do not set them.'+string(13B)+string(10B)
  txt += '            You can choose which bands is going to be reserves.'+string(13B)+string(10B)
  txt += '   b) Atmospheric correction: Now only QUAC is supported.'+string(13B)+string(10B)
  txt += '   c) Band Math: Input the expression and Press `OK`.'+string(13B)+string(10B)
  txt += '                 If you do not need to calculate anything, just set the expression as nothing(``) or do not click `OK`.'+string(13B)+string(10B)
  txt += '4. Press `Proceed`, a confirm window will display, check your setting, and press `Proceed Now` to start proceed.'+string(13B)+string(10B)
  txt += '5. TIFF files will be ouputed.'+string(13B)+string(10B)
  txt += string(13B)+string(10B)
  txt += 'LICENSE: Apache v2.0 http://www.apache.org/licenses/LICENSE-2.0'+string(13B)+string(10B)
  txt += 'Copyright 2017 Yue H.W. Luo, yue.rimoe@gmail.com'+string(13B)+string(10B)
  text = widget_text(set_win,scr_xsize=720,ysize=19, value = txt)
  label = widget_label(set_win, /align_left, value = '')
  widget_control, set_win, /realize
end