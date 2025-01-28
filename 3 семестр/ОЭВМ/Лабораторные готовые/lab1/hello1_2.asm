   DOSSEG                                      
   .MODEL  SMALL                            
   .STACK  100h                               
   .DATA                                       
Greeting  LABEL  BYTE                          
   DB 'Вас приветствует ст.гр.3303 - Пупкин',13,10,'$'
   
Force LABEL BYTE
   DB 'Да пребудет с тобой сила $'
	
   .CODE                                
   mov  ax,@data                        
   mov  ds,ax                          
   mov  dx,OFFSET Greeting              
   
DisplayGreeting:
   mov  ah,9                           
   int  21h 							
   
   mov  dx,OFFSET Force  
DisplayForce:
   mov  ah,9                            
   int  21h 
   mov  ah,4ch                        
   int  21h                             
   END
