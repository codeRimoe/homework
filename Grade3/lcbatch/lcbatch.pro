pro lcbatch
  ENVI, /restore_base_save_files
  ENVI_batch_init
  e = envi(/headless)
  files = []
  
  base_win = widget_base(xoffset = 200, yoffset =200,$
    xsize = 808, ysize = 510,$
    mbar = mbar,$
    tlb_frame_attr = 11,$
    /base_align_center, /row,$
    title = 'Landset batch')
  
  menu = widget_button(mbar, value = 'File')
  about = widget_button(mbar, value = 'About')
  ab = widget_button(about, value = 'Author...')
  hp = widget_button(about, value = 'Help...')
  fmenu_open = widget_button(menu, value = 'Add files to List...')
  fmenu_path = widget_button(menu, value = 'Set save path...')
  fmenu_exit = widget_button(menu, value = 'Exit', /separator)
  xmanager, 'ab', ab
  xmanager, 'hp', hp
  xmanager, 'open', fmenu_open
  xmanager, 'path', fmenu_path
  xmanager, 'exitpro', fmenu_exit
  
  filebase_frame = widget_base(base_win,$
    xsize = 400, ysize = 500,$
    /column)
  
  file_frame = widget_base(filebase_frame,$
    xsize = 392, ysize = 490,$
    /base_align_center, /column, /frame)
  label = widget_label(file_frame, value = ' ')
  label = widget_label(file_frame, /align_center, value = 'File List')
  wl = widget_list(file_frame, value = files,$
    scr_xsize = 360,scr_ysize = 340)
  label = widget_label(file_frame, /align_center, value = 'You can double click the file to see overview.')
  xmanager, 'wl', wl
  
  label = widget_label(file_frame, value = ' ')
  save_frame = widget_base(file_frame,/row)
  label = widget_label(save_frame, /align_left, value = 'Save path:')
  save_text = widget_text(save_frame,scr_xsize=300,ysize=1)
  
  ;file
  label = widget_label(file_frame, value = ' ')
  file_pro_frame = widget_base(file_frame,/row)
  add_file = widget_button(file_pro_frame,value="Add Files...")
  save_path = widget_button(file_pro_frame,value="Set Path...")
  proceed = widget_button(file_pro_frame,value="Proceed")
  xmanager, 'pro', proceed
  xmanager, 'open', add_file
  xmanager, 'path', save_path
    
  pro_frame = widget_base(base_win,$
    xsize = 400, ysize = 500,$
    /column)
    
  tab_frame = widget_base(pro_frame,$
    xsize = 392, ysize = 150,$
    /align_center,/column, /frame)
  label = widget_label(tab_frame, /align_left, value = 'Batch process setting:')
  wt = widget_tab(tab_frame, uname = 'tab', ysize = 30)
  w1 = widget_base(wt, title = 'Clip')
  w2 = widget_base(wt, title = 'Atmo Corr')
  w3 = widget_base(wt, title = 'Band math')
  bt = widget_label(tab_frame, /align_center, xsize=550, value = 'No band is selected.')
  ex = widget_base(tab_frame,/align_center, /exclusive,/row)
  ex5 = widget_button(ex, value = "Landsat4-5/TM", uvalue=5)
  ex7 = widget_button(ex, value = "Landsat7/ETM+", uvalue=7)
  ex8 = widget_button(ex, value = "Landsat8/OLI", uvalue=8)
  nex1 = widget_base(tab_frame,/align_center, /nonexclusive,/row)
  B = widget_button(nex1, value = "B", uvalue=1)
  G = widget_button(nex1, value = "G", uvalue=2)
  R = widget_button(nex1, value = "R", uvalue=3)
  NIR = widget_button(nex1, value = "NIR", uvalue=4)
  SWIR1 = widget_button(nex1, value = "SWIR1/B5", uvalue=5)
  SWIR2 = widget_button(nex1, value = "SWIR2/B7", uvalue=6)
  
  xmanager, 'ex', ex5
  xmanager, 'ex', ex7
  xmanager, 'ex', ex8
  xmanager, 'band', B
  xmanager, 'band', G
  xmanager, 'band', R
  xmanager, 'band', NIR
  xmanager, 'band', SWIR1
  xmanager, 'band', SWIR2
  
  ;clip
  clip_frame = widget_base(w1, /align_center,/row)
  label = widget_label(clip_frame, /align_left, value = ' UL')
  x1_text = widget_text(clip_frame,scr_xsize=40,ysize=1)
  y1_text = widget_text(clip_frame,scr_xsize=40,ysize=1)
  label = widget_label(clip_frame, /align_left, value = ' LR')
  x2_text = widget_text(clip_frame,scr_xsize=40,ysize=1)
  y2_text = widget_text(clip_frame,scr_xsize=40,ysize=1)
  label = widget_label(clip_frame, /align_left, value = '  Conv')
  cvrt_text = widget_text(clip_frame,scr_xsize=60,ysize=1)
  label = widget_label(clip_frame, /align_left, value = '  ')
  clip_data = widget_button(clip_frame,value="Set..")
  xmanager, 'clip_data', clip_data
  
  ;quac
  quac_frame = widget_base(w2, /align_center, /row)
  label = widget_label(quac_frame, /align_left, value = '       ')
  quac_base = widget_base(quac_frame, /nonexclusive)
  quac_btn = widget_button(quac_base, value="QUAC")
  xmanager, 'quac', quac_btn
  
  ;band math
  bm_frame = widget_base(w3, /align_center,/row)
  bm_math = widget_text(bm_frame, /editable,scr_xsize=340,ysize=1)
  bm_btn = widget_button(bm_frame, value="OK")
  xmanager, 'bd', bm_btn
  
  label = widget_label(pro_frame, value = ' ')
  
  draw_frame = widget_base(pro_frame,$
    xsize = 392, ysize = 322,$
    /align_center,/column, /frame)
  label = widget_label(draw_frame, value = 'Overview',/align_center)
  preview = widget_draw(draw_frame,$
    xsize = 300, ysize = 300,$
    /align_center)
    
  pf = ptr_new(files)
  wids = {e:e,fn:'',bt:bt,$
    files:pf,path:'',$
    save_path:save_text,$
    cv:0,img:[0,0,0,0,0,0,0],$
    x1:0.0,y1:0.0,x2:0.0,y2:0.0,$
    x1_text:x1_text,y1_text:y1_text,$
    x2_text:x2_text,y2_text:y2_text,$
    cvrt:cvrt_text,$
    quac:0,$
    bm_math:bm_math,band:'',$
    wl:wl}
  pw = ptr_new(wids)
  widget_control, base_win, set_uvalue = pw
  widget_control, base_win, /realize
end