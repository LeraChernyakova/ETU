   DOSSEG                                      
   .MODEL  SMALL                            
   .STACK  100h                               
   .DATA                                       
Greeting  LABEL  BYTE                          
   DB '��� �ਢ������ ��.��.3303 - �㯪��',13,10,'$'
   
Force LABEL BYTE
   DB '�� �ॡ㤥� � ⮡�� ᨫ� $'
	
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
