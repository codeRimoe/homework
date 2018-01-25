#include "StdAfx.h"
#include "Fill.h"

CFill::CFill(void): color(RGB(0,0,0)),dc(NULL){
}


CFill::~CFill(void){
}

void CFill::setColor(COLORREF c){
    color = c;
}

void CFill::setDC(CClientDC* d){
    dc = d;
}

void CFill::fill(CPoint seed){
    // Scan Line Seed Fill Algorithm
    COLORREF dcolor = dc->GetPixel(seed);
    int xr=0,xl=0;
    fill_pix.push(seed);
    while(!fill_pix.empty()){
        CPoint save = fill_pix.top(), temp = save;
        fill_pix.pop();
        while(dc->GetPixel(temp)==dcolor){
            dc->SetPixel(temp, color);
            ++temp.x;
        }
        xr=temp.x-1;  // save the extreme right pixel
        temp=save;    // reset the temp_point to the value for the save_point
        --temp.x;
        while(dc->GetPixel(temp)==dcolor){
            dc->SetPixel(temp, color);
            --temp.x;
        }
        xl=temp.x+1;  // save the extreme right pixel
        temp=save;    // reset the temp_point to the value for the save_point

        // check that the scan the above is neither a polygon boundary nor has been previously filled;
        // if not, seed the scan line
        // start at the left edge of the scan line subspan

        temp.x = xl;
        temp.y = save.y-1;
        while(temp.x<=xr){
            //seed the scan line above
            bool Pflag=false;
            while(dc->GetPixel(temp)==dcolor && temp.x<=xr){
                if(!Pflag) Pflag=true;
                temp.x++;
            }
            //push the extreme right pixel onto the stack
            if(Pflag){
                if(!(dc->GetPixel(temp)==dcolor && temp.x==xr))
                    fill_pix.push(temp);
                else{
                    --temp.x;
                    fill_pix.push(temp);
                    ++temp.x;
                }
            }
            // continue checking in case the span is interrupted
            int xe = temp.x;
            while(dc->GetPixel(temp)==dcolor && temp.x<=xr)
                ++temp.x;
            // make sure that pixel coordinate is incremented
            if(temp.x=xe)temp.x=temp.x+1;
        }
                temp.x = xl;
        temp.y = save.y+1;
        while(temp.x<=xr){
            //seed the scan line above
            bool Pflag=false;
            while(dc->GetPixel(temp)==dcolor && temp.x<=xr){
                if(!Pflag) Pflag=true;
                temp.x++;
            }
            //push the extreme right pixel onto the stack
            if(Pflag){
                if(!(dc->GetPixel(temp)==dcolor && temp.x==xr))
                    fill_pix.push(temp);
                else{
                    --temp.x;
                    fill_pix.push(temp);
                    ++temp.x;
                }
            }
            // continue checking in case the span is interrupted
            int xe = temp.x;
            while(dc->GetPixel(temp)==dcolor && temp.x<=xr)
                ++temp.x;
            // make sure that pixel coordinate is incremented
            if(temp.x=xe)temp.x=temp.x+1;
        }
    }

}