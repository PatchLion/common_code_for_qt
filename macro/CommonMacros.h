#ifndef CommonMacros_h__
#define CommonMacros_h__

///delete a pointer and make it null
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete ((p));     (p)=0;}   }
#endif    

///delete an array pointer and make it null
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] ((p));   (p)=0; } }
#endif    
#endif // CommonMacros_h__
