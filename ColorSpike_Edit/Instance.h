class Instance
{
    String TypeY;
    float XoffsetY;
    float YoffsetY;
    float ScaleY;
    float SpeedY;
    float temp;
    float DutyY;
    String TypeW;
    float XoffsetW;
    float YoffsetW;
    float ScaleW;
    float SpeedW;
    float DutyW;
    
    float squAng(float angle, float D)
    {
     if(angle<0)
     angle=angle+1800;
     
     while(angle>360)
     angle=angle-360;
     
     if((360*D)>=angle)
     return 1;
     else
     return -1;
    }
    float triAng(float angle, float D)
    {
     if(angle<0)
     angle=angle+1800;
     
     while(angle>360)
     angle=angle-360;
     
     if(angle<=(360*D))
     return (((2*angle)/(360*D))-1);
     else
     return -(((angle-360)/(180*(1-D)))+1);
    }
    
    
  public:
  Instance(String Tc, float Xc, float Yc, float Scc, float Spc,String Tw, float Xw, float Yw, float Scw, float Spw)
  {
   TypeY = Tc;
   XoffsetY = Xc;
   YoffsetY = Yc;
   ScaleY = Scc;
   SpeedY = Spc;
   DutyY = 0.5;
   TypeW = Tw;
   XoffsetW = Xw;
   YoffsetW = Yw;
   ScaleW = Scw;
   SpeedW = Spw;
   DutyW = 0.5;
  }

  int getY(float x)
  {
   /* HERE LIES SINE CODE*/
   if(TypeY=="Sine")
   {  
    x = (SpeedY*x)+XoffsetY;
    x = x * 0.0174533;
    temp=YoffsetY+(72+(ScaleY*72*sin(x)));
   }
   /* HERE LIES Static CODE*/
   if(TypeY=="Static")
   {
     temp=YoffsetY;
   }
   /*Here Lies Square Code*/
   if(TypeY=="Square")
   {
    x = (SpeedY*x)+XoffsetY;
    temp = YoffsetY+(72+(ScaleY*72*squAng(x,DutyY)));
   }
   /*Here Lies Triangular Code*/
   if(TypeY=="Triangular")
   {
    x = (SpeedY*x)+XoffsetY;
    temp = YoffsetY+(72+(ScaleY*72*triAng(x,DutyY)));
   }
   return temp/2;
  }
  
  int getW(float x)
  {
   /* HERE LIES SINE CODE*/
   if(TypeW=="Sine")
   {  
    x = (SpeedW*x)+XoffsetW;
    x = x * 0.0174533;
    temp=YoffsetW+(72+(ScaleW*72*sin(x)));
   }
   /* HERE LIES Static CODE*/
   if(TypeW=="Static")
   {
     temp=YoffsetW;
   }
   /*Here Lies Square Code*/
   if(TypeW=="Square")
   {
    x = (SpeedW*x)+XoffsetW;
    temp = YoffsetW+(72+(ScaleW*72*squAng(x,DutyW)));
   }
   /*Here Lies Triangular Code*/
   if(TypeW=="Triangular")
   {
    x = (SpeedW*x)+XoffsetW;
    temp = YoffsetW+(72+(ScaleW*72*triAng(x,DutyW)));
   }
   return temp/2;
  }
  
  void setTypeY(String t)
  {
    TypeY = t;
  }
  void setXoffsetY(float v)
  {
    XoffsetY = v;
  }
  void setYoffsetY(float v)
  {
    YoffsetY = v;
  }
  void setScaleY(float v)
  {
    ScaleY = v;
  }
  void setSpeedY(float v)
  {
    SpeedY = v;
  }
  void setDutyY(float v)
  {
    if(v<0.05)
    v=0;
    if(v>0.95)
    v=1;
    DutyY = v;
  }
    void setTypeW(String t)
  {
    TypeW = t;
  }
  void setXoffsetW(float v)
  {
    XoffsetW = v;
  }
  void setYoffsetW(float v)
  {
    YoffsetW = v;
  }
  void setScaleW(float v)
  {
    ScaleW = v;
  }
  void setSpeedW(float v)
  {
    SpeedW = v;
  }
  void setDutyW(float v)
  {
    if(v<0.05)
    v=0;
    if(v>0.95)
    v=1;
    DutyW = v;
  }
};
